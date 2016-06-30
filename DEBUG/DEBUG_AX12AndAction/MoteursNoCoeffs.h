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

#ifndef __MOTEURS_H__                                     // Si la constante n'est pas définie
#define __MOTEURS_H__                                     // On la définie de manière à ce que le fichier ne soit plus inclus

#include <Arduino.h>

#define pin uint8_t

class Moteurs{
  
  public:
    Moteurs();                                            // Initialisation
    
    void set( pin moteur, int consigne );                 // Définit le PWM d'un moteur
    void setAll( int consigne );                          // Définit le PWM des moteurs
    
    void stop();                                          // Stoppe les moteurs
    
    static const pin LEFT = 3;
    static const pin RIGHT = 2;    
    
  private:
    static const boolean PWM_REVERSE = true;              // Inversion des PWM (false => PWM 0 = arret & PWM max = vitesse max; true => PWM 0 = vitesse max & PWM max = arret)
    
    static const pin IN1_L = 24;                          // Pin 1 moteur gauche
    static const pin IN2_L = 22;                          // Pin 2 moteur gauche
    
    static const pin IN1_R = 28;                          // Pin 1 moteur droit
    static const pin IN2_R = 26;                          // Pin 2 moteur droit
};

#endif

