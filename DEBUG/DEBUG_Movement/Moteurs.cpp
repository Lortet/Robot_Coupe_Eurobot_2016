//----------------------------------------------------------------------//
//                                MOTEURS                               //
//                                                    version 16.04.29  //
//                                             date 29/04/2016 - 16h13  //
//----------------------------------------------------------------------//
//  Permet de mettre en mouvement les moteurs du robot.                 //
//----------------------------------------------------------------------//
//                                                     Valentin LORTET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//        Adapté des travaux de Kevin LE MOGUEN et Thibault d'ARTIGUES  //
//----------------------------------------------------------------------//

#include "Moteurs.h"

Moteurs::Moteurs(){
  // Broches du moteur gauche
  pinMode( LEFT, OUTPUT );
  pinMode( IN1_L, OUTPUT );
  pinMode( IN2_L, OUTPUT );
  
  // Broches du moteur droit
  pinMode( RIGHT, OUTPUT );
  pinMode( IN1_R, OUTPUT );
  pinMode( IN2_R, OUTPUT );
  
  stop();
}

void Moteurs::set( pin moteur, int consigne ) {
  pin IN1, IN2;
  int MIN_PWM, MAX_PWM;
  if( moteur == Moteurs::LEFT ) {
    IN1 = IN1_L;
    IN2 = IN2_L;

    MIN_PWM = MIN_PWM_L;
    MAX_PWM = MAX_PWM_L;
  }
  else if( moteur == Moteurs::RIGHT ) {
    IN1 = IN1_R;
    IN2 = IN2_R;

    MIN_PWM = MIN_PWM_R;
    MAX_PWM = MAX_PWM_R;
  }
  else return;
  
  digitalWrite( IN1, (( consigne >= 0 )? HIGH : LOW ) );
  digitalWrite( IN2, (( consigne >= 0 )? LOW : HIGH ) );
  
  if( consigne != 0 ) consigne = (int)( (float)abs( consigne )/255 * ( MAX_PWM-MIN_PWM ) + MIN_PWM );
  if( consigne > MAX_PWM ) consigne = MAX_PWM;
  
  analogWrite( moteur, (( PWM_REVERSE )? 255-consigne : consigne ) );
}

void Moteurs::setAll( int consigne ) {
  set( Moteurs::LEFT, consigne );
  set( Moteurs::RIGHT, consigne );
}

void Moteurs::stop() {
  setAll( 0 );
}
