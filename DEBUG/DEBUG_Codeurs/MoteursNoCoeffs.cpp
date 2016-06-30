//----------------------------------------------------------------------//
//                           MOTEURS NO COEFFS                          //
//                                                    version 16.04.25  //
//                                             date 25/04/2016 - 23h01  //
//----------------------------------------------------------------------//
//  Permet de mettre en mouvement les moteurs du robot (pour le DEBUG.  //
//----------------------------------------------------------------------//
//                                                     Valentin LORTET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//        Adapté des travaux de Kevin LE MOGUEN et Thibault d'ARTIGUES  //
//----------------------------------------------------------------------//

#include "MoteursNoCoeffs.h"

Moteurs::Moteurs(){
  // Pins des moteurs
  pinMode( LEFT, OUTPUT );
  pinMode( IN1_L, OUTPUT );
  pinMode( IN2_L, OUTPUT );
  
  pinMode( RIGHT, OUTPUT );
  pinMode( IN1_R, OUTPUT );
  pinMode( IN2_R, OUTPUT );
  
  stop();
}

void Moteurs::set( pin moteur, int consigne ) {
  pin IN1, IN2;
  if( moteur == Moteurs::LEFT ) {
    IN1 = IN1_L;
    IN2 = IN2_L;
  }
  else if( moteur == Moteurs::RIGHT ) {
    IN1 = IN1_R;
    IN2 = IN2_R;
  }
  else return;
  
  digitalWrite( IN1, (( consigne >= 0 )? HIGH : LOW ) );
  digitalWrite( IN2, (( consigne >= 0 )? LOW : HIGH ) );

  if( consigne != 0 ) consigne = abs( consigne );
  if( consigne > 255 ) consigne = 255;
  
  analogWrite( moteur, (( PWM_REVERSE )? 255-consigne : consigne ) );
}

void Moteurs::setAll( int consigne ) {
  set( Moteurs::LEFT, consigne );
  set( Moteurs::RIGHT, consigne );
}

void Moteurs::stop() {
  setAll( 0 );
}
