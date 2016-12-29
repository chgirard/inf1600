#include "lib_dir/Settings.h"
#include "lib_dir/Util.h"
#include "lib_dir/Timer.h"
#include "lib_dir/PulseWidthModulation.h"
#include "lib_dir/Dell.h"
#include "ColorDetector.h"
#include "LineFollower.h"
#include "RoomFinder.h"

volatile bool tick = false;
volatile uint16_t colorFrequencyCounter = 0;

enum Etats {
  FINI, FOLLOW_LINE, DETECT_COLOR_PATTERN, ENTERING_ROOM, EXITING_ROOM, TAKE_ROOM_SAMPLES, FINISHED_ROOM_SAMPLING
};

// Minuterie au 5 millisecondes
ISR(TIMER1_COMPA_vect){
  tick = true;
}

// Color sensor sends square waves that we count frequency
// Frequency proportional to intensity [higher intensity -> higher frequency]
ISR(INT0_vect){
	colorFrequencyCounter++;
}

int main()
{
  // Set les ports
  initialization();

  // minuterie 1 au 5 millisecondes
  startTimer(5);

  Etats etat = FOLLOW_LINE;

  Piece::Piece suitePiece[3] = {Piece::UNKNOWN, Piece::UNKNOWN, Piece::UNKNOWN};

  // Contrôleur pour suivre les lignes
  LineFollower ligneux;
  // Interface to detect the room shapes
  RoomFinder roomFinder;
  // Interface to detect colours
  ColorDetector colorDetector;

  uint8_t noPiece = 0;

  // Delay to not turn right (300 * 5 millisecondes = 1.5 secondes)
  uint16_t delay = 0;

  uint8_t colorCounter = 0;
  Color::Color colorPattern[3];

  /*while(true){
    uint8_t distance = roomFinder.getDistanceCm();
    transmissionUART(distance);
    if(distance < 10 || distance > 40)
    setLight(Dell::OFF);
    else if((distance/2)%2==0)
    setLight(Dell::GREEN);
    else
    setLight(Dell::RED);
  }*/

  // MAIN ROUTINE
  while (true) {
    // À chaque 5 millisecondes, la boucle va exécuter [tick devient true à chaque 5 ms]
    if (tick) {
      tick = false;
      delay++;

      switch (etat) {
        case FOLLOW_LINE: {
          // delay was initialized at 0, so it takes 5 * 300 milliseconds (1.5 seconds) to reach 300
          // ligneur.followLine() is true when it detects an intersection
          if (ligneux.followLine( true) && (delay > 300)) {
            ligneux.rightTurn();
            etat = ENTERING_ROOM;
            delay = 0;
          }
          break;
        }
        case ENTERING_ROOM: {
          float distanceToWall = roomFinder.getDistanceCm();
          // When the distance to wall is less than 21 centimeters, the robot stops
          if (ligneux.followLine(distanceToWall, true)) {
            if (delay > 100) { // only if 500 ms has elapsed
              etat = TAKE_ROOM_SAMPLES;
              roomFinder.reset();
            }
          }
          break;
        }
        case TAKE_ROOM_SAMPLES: {
          roomFinder.addSample();
          if (ligneux.uTurn()) {
            etat = FINISHED_ROOM_SAMPLING;
          }
          break;
        }
        case FINISHED_ROOM_SAMPLING: {
          if (ligneux.uTurn()) {
            etat = EXITING_ROOM;

            suitePiece[noPiece] = roomFinder.getShape();
            switch (suitePiece[noPiece]) {
              case Piece::CERCLE: {
                setLight(Dell::GREEN);
                break;
              }
              case Piece::CARRE: {
                soundOn(69);
                break;
              }
              case Piece::OCTOGONE: {
                setLight(Dell::RED);
                break;
              }
            }
            _delay_ms(2000);
            setLight(Dell::OFF);
            soundOff();
            noPiece++;
          }
          break;
        }
        case EXITING_ROOM: {
          if (ligneux.followLine( true)) {
            // more rooms left to explore
            if (noPiece < 3) {
              ligneux.rightTurn();
              etat = FOLLOW_LINE;
            }
            // found all three rooms, go back
            else {
              ligneux.leftTurn();
              etat = DETECT_COLOR_PATTERN;
              colorDetector.openDell();
            }
          }
          break;
        }
        case DETECT_COLOR_PATTERN: {
          ligneux.followLine(false);
          colorDetector.addSample(colorFrequencyCounter);
          bool colorChanged = false;
          // hasn't detected first color of the 3-color pattern
          if (colorCounter == 0) {
            // detected the first color of the pattern
            if (colorDetector.getColor() != Color::WHITE) {
              colorPattern[colorCounter++] = colorDetector.getColor();
              colorChanged = true;
            }
          }
          // has already detected the first color of the pattern
          else {
            // int(colorPattern[colorCounter - 1]) -> previously detected color
            if (int(colorPattern[colorCounter - 1]) != int(colorDetector.getColor())) {
              if (int(colorDetector.getColor()) != int(Color::WHITE)) {
                // add the newly detected color to the pattern table
                colorPattern[colorCounter++] = colorDetector.getColor();
              }
              else {
                // reset color pattern (back to white)
                // after checking room-pattern with color-pattern, it sets first color of pattern-table
                // to last color of the pattern
                // we reset back to 0 when it leaves the color-pattern square
                // additionally, if the circuit had decoys [single color islands], it'd be able to handle them
                colorCounter = 0;
              }
              colorChanged = true;
            }
          }
          if (colorChanged) {
            switch (colorPattern[colorCounter - 1]) {
              case Color::RED: {
                setLight(Dell::RED);
                soundOff();
                break;
              }
              case Color::GREEN: {
                setLight(Dell::GREEN);
                soundOff();
                break;
              }
              case Color::BLUE: {
                setLight(Dell::OFF);
                soundOn(69);
                break;
              }
              default: {
                setLight(Dell::OFF);
                soundOff();
                break;
              }
            }
            // we got the 3-color pattern
            if (colorCounter == 3) {
              uint8_t matches = 0;
              if (int(suitePiece[0]) == int(colorPattern[2])) {
                matches++;
              }
              if (int(suitePiece[1]) == int(colorPattern[1])) {
                matches++;
              }
              if (int(suitePiece[2]) == int(colorPattern[0])) {
                matches++;
              }
              // color-pattern matches room-pattern
              if (matches == 3) {
                etat = FINI;
              }
              else {
                colorCounter = 0;
              }
            }
          }
          colorFrequencyCounter = 0;
          break;
        }
        case FINI: {
          ligneux.stop();
          setLight(Dell::OFF);
          soundOff();
          colorDetector.closeDell();
          // shut down robot
          return 0;
        }
      }
    }
  }
  return 0;
}
