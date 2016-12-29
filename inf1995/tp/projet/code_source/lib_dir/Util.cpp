#include "Util.h"

bool debounce() {
  _delay_ms(10); // debounce
  return PIND & 0x04;
}

bool isButtonPressed() {
  if (!(PIND & 0x04))
  {
    return false;
  }

  return debounce(); // Rechecks in 10 ms and returns the value
}

void initialization() {
  cli();

  //Set Input / Output for the PINS *See Settings.h for details*
  DDRA = PA;
  DDRB = PB;
  DDRC = PC;
  DDRD = PD;

  EIMSK |= _BV(INT0);
  EICRA |= (1 << ISC00); //Trigger on any logical change of INT0

	// 2400 bauds
	UBRR0H = 0;
	UBRR0L = 0xCF;

	// permettre la reception et la transmission par le UART0
  // TXEN0 = transmission enable
  // RXEN0 = receive enable
	UCSR0B = _BV(TXEN0)|_BV(RXEN0);

	// Format des trames: 8 bits, 1 stop bits, none parity
	UCSR0C = _BV(UCSZ01)|_BV(UCSZ00);

  sei();

  //Define the frequency range for the color controler
  PORTC |= (1 << 4); // s0 = 1; | 10kHz min, 12kHz typ.
  PORTC &= ~(1 << 5);  // s1 = 0; |


  // Initialization music
  soundOn(48);
  _delay_ms(225);
  soundOn(48);
  _delay_ms(225);
  soundOn(52);
  _delay_ms(225);
  soundOn(55);
  _delay_ms(340);
  soundOn(52);
  _delay_ms(225);
  soundOn(55);
  _delay_ms(450);
  soundOff();

}

void clearInterruptions() {
  EIFR |= (1 << INTF0); // Clear interruptions for external interrupts
}

void transmissionUART ( uint8_t donnee ) {
	while (!(UCSR0A & _BV(UDRE0))); // wait until UDRE0 is set into UCSR0A = Data Register empty -> new data can be transmitted
	UDR0=donnee; // USART Data Register (write 1 byte at a time)
}

uint8_t ajustValueWithPercentage ( uint8_t valeur, uint8_t pourcentage ) {
  return uint8_t((pourcentage * uint16_t(valeur)) / 100); //Calculate the appropriate porcentage
}
