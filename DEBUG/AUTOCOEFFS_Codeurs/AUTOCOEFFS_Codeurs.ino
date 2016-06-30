#include "Configuration.h"  // IMPORTANT DE VERIFIER LE CONTENU

#include "Codeurs.h" // Utilisation de getItcks
#include "SerialBuffer.h" // Utilisation de getItcks

Codeurs codeurs;
SerialBuffer blueSerial( 3, '\n', 200, 32 );

void setup() {
  blueSerial.begin( 115200 );
  
  delay( 1000 );
}

void loop() {
  long lastCodeurL, lastCodeurR;
  long codeurL, codeurR;

  while( 1 ) {
    
    waitCodeursStop();
    codeurs.updateAndGetTicks( &codeurL, &codeurR );
    
    if( codeurL != lastCodeurL || codeurR != lastCodeurR ) {
      blueSerial.println( "NB TICKS : gauche -> " + String( codeurL ) + " ; droite -> " + String( codeurR ) + " ;" );
      blueSerial.println( "" );
      
      lastCodeurL = codeurL;
      lastCodeurR = codeurR;
    }
    
  }
}

void waitCodeursStop() {
  long codeurL, codeurR;
  long lastCodeurL, lastCodeurR;

  codeurs.updateAndGetTicks( &codeurL, &codeurR );
  
  do {
    lastCodeurL = codeurL;
    lastCodeurR = codeurR;

    delay( 25 );
    
    codeurs.updateAndGetTicks( &codeurL, &codeurR );
  }
  while( codeurL != lastCodeurL || codeurR != lastCodeurR );
}
