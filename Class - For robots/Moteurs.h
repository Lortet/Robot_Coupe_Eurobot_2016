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

#ifndef __MOTEURS_H__                                     // Si la constante n'est pas définie
#define __MOTEURS_H__                                     // On la définie de manière à ce que le fichier ne soit plus inclus

#include "Configuration.h"
#include <Arduino.h>

#define pin uint8_t

class Moteurs{
  
  public:
    Moteurs();                                            // Initialisation
    
    void set( pin moteur, long consigne );                // Définit le PWM d'un moteur
    void setAll( int consigne );                          // Définit le PWM des moteurs
    
    void setSpeed( float speed );                         // Définit la vitesse des moteurs
    
    void stop();                                          // Stoppe les moteurs
    
    static const pin LEFT = 3;
    static const pin RIGHT = 2;    
    
  private:
    static const boolean PWM_REVERSE = true;              // Inversion des PWM (false => PWM 0 = arret & PWM max = vitesse max; true => PWM 0 = vitesse max & PWM max = arret)
	
    #if ROBOT == Ulysse
	
      static const int MIN_PWM_L = 18;                    // PWM minimale permettant à la roue gauche de bouger (A determiner à l'aide du programme DEBUG_Moteurs_AutoCoeffs)
      static const int MAX_PWM_L = 114;                   // PWM maximale correspondant à la vitesse maximale de la roue gauche (A determiner à l'aide du programme DEBUG_Moteurs_AutoCoeffs)
      
      static const int MIN_PWM_R = 18;                    // PWM minimale permettant à la roue droite de bouger (A determiner à l'aide du programme DEBUG_Moteurs_AutoCoeffs)
      static const int MAX_PWM_R = 110;                   // PWM maximale correspondant à la vitesse maximale de la roue droite (A determiner à l'aide du programme DEBUG_Moteurs_AutoCoeffs)
	  
    #elif ROBOT == Nono
	  
      static const int MIN_PWM_L = 13;                    // PWM minimale permettant à la roue gauche de bouger (A determiner à l'aide du programme DEBUG_Moteurs_AutoCoeffs)
      static const int MAX_PWM_L = 46;                    // PWM maximale correspondant à la vitesse maximale de la roue gauche (A determiner à l'aide du programme DEBUG_Moteurs_AutoCoeffs)
      
      static const int MIN_PWM_R = 13;                    // PWM minimale permettant à la roue droite de bouger (A determiner à l'aide du programme DEBUG_Moteurs_AutoCoeffs)
      static const int MAX_PWM_R = 46;                    // PWM maximale correspondant à la vitesse maximale de la roue droite (A determiner à l'aide du programme DEBUG_Moteurs_AutoCoeffs)
	  
    #endif
    
    float moteursSpeed = 1;
    
    static const pin IN1_L = 24;                          // Pin 1 moteur gauche
    static const pin IN2_L = 22;                          // Pin 2 moteur gauche
    
    static const pin IN1_R = 28;                          // Pin 1 moteur droit
    static const pin IN2_R = 26;                          // Pin 2 moteur droit
};

#endif
