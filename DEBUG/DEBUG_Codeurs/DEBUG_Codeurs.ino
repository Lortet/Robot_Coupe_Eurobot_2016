#include "Configuration.h"  // IMPORTANT DE VERIFIER LE CONTENU

#include "Interval.h"
#include "Codeurs.h"
#include "MoteursNoCoeffs.h"

Moteurs mot;
Interval interval( false, 250 );
Codeurs codeurs;

void setup() {
  Serial.begin(115200);
  
  interval.start();
}

void loop() {
  long codeurL, codeurR;

  while( 1  ) {
    
    codeurs.updateAndGetTicks( &codeurL, &codeurR );
    
    Serial.println( "\nNB TICKS : gauche -> " + String( codeurL ) + " ; droite -> " + String( codeurR ) + " ;" );
    
    interval.waitIntervalEnding();

  }
}
