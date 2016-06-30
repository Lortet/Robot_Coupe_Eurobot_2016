#include "Configuration.h"  // IMPORTANT DE VERIFIER LE CONTENU

#include "MoteursNoCoeffs.h"

Moteurs moteurs;

void setup() {
}

void loop() {
  // Mode 1 (Fait avancer puis reculer les moteurs progressivement)
  // Mode 2 (Fait avancer puis reculer le moteur gauche progressivement)
  // Mode 3 (Fait avancer puis reculer le moteur droit progressivement)
  
  // Mode 4 (Fait avancer les moteurs à la vitesse maximum)
  // Mode 5 (Fait reculer les moteurs à la vitesse maximum)
  
  // Mode 6 (Fait reculer les moteurs à la vitesse moyenne)
  // Mode 7 (Fait reculer les moteurs à la vitesse moyenne)
  
  // Mode 8 (Arrêt)
  
  // Mode 9 (PERSO)
  
  int mode = 1;

  while( 1 ) {
    
    switch( mode ) {
      case 1:
      case 2:
      case 3:
      
        /* Vitesse de 0 à 255 */
        for( int pwm = 0; pwm <= 255; pwm++ ) {
          if(mode != 3) moteurs.set( Moteurs::LEFT, pwm );
          if(mode != 2) moteurs.set( Moteurs::RIGHT, pwm );
          delay( 15 );
        }    
        /* Vitesse de 255 à 0 */
        for( int pwm = 255; pwm >= 0; pwm-- ) {
          if(mode != 3) moteurs.set( Moteurs::LEFT, pwm );
          if(mode != 2) moteurs.set( Moteurs::RIGHT, pwm );
          delay( 5 );
        }
        
        delay( 750 );
      
        /* Vitesse de 0 à -255 */
        for( int pwm = 0; pwm >= -255; pwm-- ) {
          if(mode != 3) moteurs.set( Moteurs::LEFT, pwm );
          if(mode != 2) moteurs.set( Moteurs::RIGHT, pwm );
          delay( 5 );
        }
        /* Vitesse de -255 à 0 */
        for( int pwm = -255; pwm <= 0; pwm++ ) {
          if(mode != 3) moteurs.set( Moteurs::LEFT, pwm );
          if(mode != 2) moteurs.set( Moteurs::RIGHT, pwm );
          delay( 5 );
        }
        
        if( mode == 1 ){
          delay( 750 );
          
          /* Vitesse de 0 à 255 */
          for( int pwm = 0; pwm <= 255; pwm++ ) {
            moteurs.set( Moteurs::LEFT, pwm );
            delay( 5 );
          }    
          /* Vitesse de 255 à 0 */
          for( int pwm = 255; pwm >= 0; pwm-- ) {
            moteurs.set( Moteurs::LEFT, pwm );
            delay( 5 );
          }
          
          delay( 750 );
          
          /* Vitesse de 0 à 255 */
          for( int pwm = 0; pwm <= 255; pwm++ ) {
            moteurs.set( Moteurs::RIGHT, pwm );
            delay( 5 );
          }    
          /* Vitesse de 255 à 0 */
          for( int pwm = 255; pwm >= 0; pwm-- ) {
            moteurs.set( Moteurs::RIGHT, pwm );
            delay( 5 );
          }
          
          delay( 750 );
          
          /* Vitesse de 0 à 255 & 0 à -255 */
          for( int pwm = 0; pwm <= 255; pwm++ ) {
            moteurs.set( Moteurs::LEFT, pwm );
            moteurs.set( Moteurs::RIGHT, -pwm );
            delay( 5 );
          }    
          /* Vitesse de 255 à 0 & -255 à 0 */
          for( int pwm = 255; pwm >= 0; pwm-- ) {
            moteurs.set( Moteurs::LEFT, pwm );
            moteurs.set( Moteurs::RIGHT, -pwm );
            delay( 5 );
          }
        }
        
        delay( 5000 );
        
        break;
        
      case 4:
        moteurs.set( Moteurs::LEFT, 255 );
        moteurs.set( Moteurs::RIGHT, 255 );
        break;
        
      case 5:
        moteurs.set( Moteurs::LEFT, -255 );
        moteurs.set( Moteurs::RIGHT, -255 );
        break;
        
      case 6:
        moteurs.set( Moteurs::LEFT, 127 );
        moteurs.set( Moteurs::RIGHT, 127 );
        break;
        
      case 7:
        moteurs.set( Moteurs::LEFT, -127 );
        moteurs.set( Moteurs::RIGHT, -127 );
        break;
        
      case 8:
        moteurs.set( Moteurs::LEFT, 0 );
        moteurs.set( Moteurs::RIGHT, 0 );
        break;
        
      case 9:
        break;
    }

  }
}
