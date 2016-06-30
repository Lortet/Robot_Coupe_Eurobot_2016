//----------------------------------------------------------------------//
//                                CODEURS                               //
//                                                    version 16.04.29  //
//                                             date 29/04/2016 - 16h07  //
//----------------------------------------------------------------------//
//  Permet de lire la valeur des codeurs du robot.                      //
//----------------------------------------------------------------------//
//                                                     Valentin LORTET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//        Adapté des travaux de Kevin LE MOGUEN et Thibault d'ARTIGUES  //
//----------------------------------------------------------------------//

#include "Codeurs.h"

Codeurs::Codeurs(){
  // Data
  pinMode( BIT1, INPUT_PULLUP );
  pinMode( BIT2, INPUT_PULLUP );
  pinMode( BIT3, INPUT_PULLUP );
  pinMode( BIT4, INPUT_PULLUP );
  pinMode( BIT5, INPUT_PULLUP );
  pinMode( BIT6, INPUT_PULLUP );
  pinMode( BIT7, INPUT_PULLUP );
  pinMode( BIT8, INPUT_PULLUP );
 
  pinMode( SELBYTE1, OUTPUT );
  pinMode( SELBYTE2, OUTPUT );
 
  pinMode( OUTEN, OUTPUT );
  
  pinMode( SELREG, OUTPUT );
  
  pinMode( RST, OUTPUT );

  // Init
  resetTicks();
  digitalWrite( OUTEN, LOW );
}

void Codeurs::update() {
  digitalWrite( SELREG, LOW );
  leftTicks = (long)-readCurrentRegister();
  
  digitalWrite( SELREG, HIGH );
  rightTicks = (long)readCurrentRegister();
}
void Codeurs::getTicks( long *leftT, long *rightT ) {
  *leftT = leftTicks;
  *rightT = rightTicks;
}
void Codeurs::updateAndGetTicks( long *leftT, long *rightT ) {
  update();
  getTicks( &*leftT, &*rightT );
}

unsigned char Codeurs::readCurrentByte() {
   unsigned char result = 0;
 
  if( digitalRead( BIT1 ) == HIGH ) result |= 1;
  if( digitalRead( BIT2 ) == HIGH ) result |= 2;
  if( digitalRead( BIT3 ) == HIGH ) result |= 4;
  if( digitalRead( BIT4 ) == HIGH ) result |= 8;
  if( digitalRead( BIT5 ) == HIGH ) result |= 16;
  if( digitalRead( BIT6 ) == HIGH ) result |= 32;
  if( digitalRead( BIT7 ) == HIGH ) result |= 64;
  if( digitalRead( BIT8 ) == HIGH ) result |= 128;
 
  return result;
}

unsigned int Codeurs::readCurrentRegister() {
  unsigned int result;
  
  digitalWrite( OUTEN, HIGH );
  
  digitalWrite( SELBYTE1, HIGH );
  digitalWrite( SELBYTE2, LOW );
  result = readCurrentByte() << 24;
  
  digitalWrite( SELBYTE1, LOW );
  result |= readCurrentByte() << 16;
  
  digitalWrite( SELBYTE1, HIGH );
  digitalWrite( SELBYTE2, HIGH );
  result |= readCurrentByte() << 8;
   
  digitalWrite( SELBYTE1, LOW );
  result |= readCurrentByte();
  
  digitalWrite( OUTEN, LOW );
  
  return (long)result;
}

void Codeurs::resetTicks() {
  digitalWrite( RST, HIGH );
  delayMicroseconds( 1 ); // au moins 10 ns
  digitalWrite( RST, LOW );
}
