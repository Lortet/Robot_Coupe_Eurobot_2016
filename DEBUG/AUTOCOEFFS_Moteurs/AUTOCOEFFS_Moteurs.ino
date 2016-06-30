#include "Configuration.h"  // IMPORTANT DE VERIFIER LE CONTENU

#include "MoteursNoCoeffs.h" // Utilisation de set
#include "Codeurs.h" // Utilisation de getItcks
#include "SerialBuffer.h" // Utilisation de getItcks

Moteurs moteurs;
Codeurs codeurs;
SerialBuffer blueSerial( 0, '\n', 200, 16 );

void setup() {
  blueSerial.begin( 115200 );
  
  //while( !blueSerial.buffStepAndIsFinished() || blueSerial.buffRead() != "START" ){};

  blueSerial.println( "OK_START" );
}

void loop() {
  int MIN_L, MIN_R;
  int MAX_L, MAX_R;

  while( 1 ) {

    testSeuilPWM( Codeurs::TICKS_BY_METER/2000, &MIN_L, &MIN_R ); // PWM permettant plus de 1mm/sec
    waitMoteursStop();

    delay( 5*1000 );
    
    testSeuilPWM( Codeurs::TICKS_BY_METER/30, &MAX_L, &MAX_R ); // PWM permettant plus de 10cm/sec
    waitMoteursStop();

    blueSerial.println( "PWM MIN : gauche -> " + String( MIN_L ) + " ; droite -> " + String( MIN_R ) + " ;" );
    blueSerial.println( "PWM MAX : gauche -> " + String( MAX_L-1 ) + " ; droite -> " + String( MAX_R-1 ) + " ;" ); // "-1" afin de conserver en dessous de 10cm/sec
    blueSerial.println( "" );
    
    delay( 15*1000 );

  }
}

void waitMoteursStop() {
  long codeurL, codeurR;
  long lastCodeurL, lastCodeurR;

  moteurs.stop();

  codeurs.updateAndGetTicks( &codeurL, &codeurR );
  
  do {
    lastCodeurL = codeurL;
    lastCodeurR = codeurR;

    delay( 100 );
    
    codeurs.updateAndGetTicks( &codeurL, &codeurR );
  }
  while( codeurL != lastCodeurL || codeurR != lastCodeurR );
}

void testSeuilPWM( int SEUIL, int *PWM_LEFT, int *PWM_RIGHT ) {
  long codLeft, codRight;
  long lastCodLeft, lastCodRight;

  // Test moteur gauche
  for( int i = 1; i <= 255; i++ ) {
    waitMoteursStop();
    
    codeurs.updateAndGetTicks( &lastCodLeft, &lastCodRight );

    blueSerial.println( "Test GAUCHE n" + String( i ) );
    moteurs.set( Moteurs::LEFT, i );
    delay( 500 );
    waitMoteursStop();
    
    codeurs.updateAndGetTicks( &codLeft, &codRight );
    
    moteurs.set( Moteurs::LEFT, -i );
    delay( 500 );
    waitMoteursStop();
    
    if( codLeft-lastCodLeft > SEUIL ) {
      *PWM_LEFT = i;
      i = 256; // On arrête la boucle
    }
    else if( codLeft-lastCodLeft < 0 ) i--;
  }
  
  delay( 5*1000 );
  
  // Test moteur droit
  for( int i = 1; i <= 255; i++ ) {
    waitMoteursStop();
    
    codeurs.updateAndGetTicks( &lastCodLeft, &lastCodRight );
    
    blueSerial.println( "Test DROIT n" + String( i ) );
    moteurs.set( Moteurs::RIGHT, i );
    delay( 500 );
    waitMoteursStop();
    
    codeurs.updateAndGetTicks( &codLeft, &codRight );
    
    moteurs.set( Moteurs::RIGHT, -i );
    delay( 500 );
    waitMoteursStop();
    
    if( codRight-lastCodRight > SEUIL ) {
      *PWM_RIGHT = i;
      i = 256; // On arrête la boucle
    }
    else if( codRight-lastCodRight < 0 ) i--;
  }
}
