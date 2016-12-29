#include "Util.h"

bool debounce() {
  _delay_ms(10);
  return PIND & 0x04;
}

bool isButtonPressed() {
  if (!(PIND & 0x04))
  {
    return false;
  }

  return debounce();
}

void initialisation() {
  cli();
  DDRA = PA;
  DDRB = PB;
  DDRC = PC;
  DDRD = PD;

	PORTD  |= (1 << 0); // allume DEL senseur couleur
	PORTC |=  (1 << 4); // s0 = 1; | 10kHz min, 12kHz typ.
	PORTC &= ~(1 << 5); // s1 = 0; |

  PORTA &= ~(0 << 2);

  EIMSK |= _BV(INT0) | (1 << INT2); // intEn pour INT0 et INT2(couleurs)
  EICRA |= (1 << ISC00) | (1 << ISC21); //Trigger on any logical change of INT0
                                        // et aux fonts descendants d'INT2 (couleurs)
  //TEST_COULEURS//EICRA |= (1 << ISC00);

	// 2400 bauds. Nous vous donnons la valeur des deux
	// premier registres pour vous �viter des complications
	UBRR0H = 0;
	UBRR0L = 0xCF;
	// permettre la reception et la transmission par le UART0
	//UCSR0A = ;
  // TXEN0 = transmission enable
  // RXEN0 = receive enable
	UCSR0B = _BV(TXEN0)|_BV(RXEN0);
	// Format des trames: 8 bits, 1 stop bits, none parity
	UCSR0C = _BV(UCSZ01)|_BV(UCSZ00);

  sei();

  // Musique d'initialisation
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

void clairInterruptions() {
  EIFR |= (1 << INTF0); // Clear interruptions pour les external interrupts
}

void transmissionUART ( uint8_t donnee ) {
	while (!(UCSR0A & _BV(UDRE0))); // attendre que le UDRE0 dans le registre UCSR0A est set = Data Register empty -> new data can be transmitted
	UDR0=donnee; // USART Data Register (write 1 byte at a time)
}
