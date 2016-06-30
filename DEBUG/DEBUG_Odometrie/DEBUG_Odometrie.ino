#include "Configuration.h"  // IMPORTANT DE VERIFIER LE CONTENU

#include "Position.h"       // Utilisation de Position
#include "Interval.h"       // Utilisation de Interval
#include "SerialBuffer.h"   // Utilisation de SerialBuffer
#include "Asservissement.h" // Utilisation de Asservissement
#include "Odometrie.h"      // Utilisation de Odometrie
#include "Codeurs.h"        // Utilisation de getItcks

Interval interval( false, 10 ); // Boucle principale s'executant toutes les X microsecondes
SerialBuffer blueSerial( 3, '\n', 200, 16 );
Asservissement asservissement;
Odometrie odometrie;
Codeurs codeurs;

void setup() {  
  blueSerial.begin( 115200 );
  blueSerial.buffWait( "START" );
  
  logCodeurs();
  interval.start();
}

void loop() {
  while( 1 ) {
    
    asservissement.addConsigneTra( 0.5*Codeurs::TICKS_BY_METER );
    waitAsservissementArretAndOdometrieStep();
    
    asservissement.addConsigneRot( Codeurs::TICKS_BY_TURN/4 );
    waitAsservissementArretAndOdometrieStep();

    logCodeurs();
    
    delay( 5000 );

  }
}

void waitAsservissementArretAndOdometrieStep() {
  do {
    long codeurL, codeurR;
      
    codeurs.updateAndGetTicks( &codeurL, &codeurR );  
     
    asservissement.step( codeurL, codeurR );
    odometrie.updatePosition( codeurL, codeurR );
      
    interval.waitIntervalEnding();
  }
  while( asservissement.getState() != Asservissement::STATE_ARRET );
}

void logCodeurs() {
  Position pos = odometrie.getPos();
  
  blueSerial.println( "X: " + String( pos.getX() ) );
  blueSerial.println( "Y: " + String( pos.getY() ) );
  blueSerial.println( "O: " + String( pos.getO() ) + "rad : " + String( pos.getDegO() ) + "deg" );
  blueSerial.println( "" );
  blueSerial.println( "" );
  blueSerial.println( "" );
}
