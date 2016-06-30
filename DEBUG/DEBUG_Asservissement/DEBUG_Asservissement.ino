#include "Configuration.h"  // IMPORTANT DE VERIFIER LE CONTENU

#include "Interval.h"       // Utilisation de Interval
#include "Asservissement.h" // Utilisation de Asservissement
#include "Codeurs.h"        // Utilisation de getItcks

Interval interval( false, 10 ); // Boucle principale s'executant toutes les X microsecondes
Asservissement asservissement;
Codeurs codeurs;

void setup(){
	interval.start();
}

void loop(){  
	asservissement.addConsigneTra( 0.5*Codeurs::TICKS_BY_METER );
	waitAsservissementArret();

	asservissement.addConsigneRot( Codeurs::TICKS_BY_TURN/4 );
	waitAsservissementArret();
}

void waitAsservissementArret() {
  do {
    long codeurL, codeurR;
      
    codeurs.updateAndGetTicks( &codeurL, &codeurR );  
    asservissement.step( codeurL, codeurR );
      
    interval.waitIntervalEnding();
  }
  while( asservissement.getState() != Asservissement::STATE_ARRET );
}
