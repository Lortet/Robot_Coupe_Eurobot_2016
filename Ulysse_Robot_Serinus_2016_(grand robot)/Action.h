//----------------------------------------------------------------------//
//                               MOVEMENT                               //
//                                                    version 16.04.25  //
//                                             date 25/04/2016 - 22h51  //
//----------------------------------------------------------------------//
//  Permet de contrôller les actions du robot.                          //
//----------------------------------------------------------------------//
//                                                     Valentin LORTET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//----------------------------------------------------------------------//

#ifndef __ACTION_H__                                   // Si la constante n'est pas définie
#define __ACTION_H__                                   // On la définie de manière à ce que le fichier ne soit plus inclus

#include <Arduino.h>                                   // Utilisation de Asservissement
#include "Configuration.h"                             // Utilisation de Asservissement
#include "due_can.h"                                   // Utilisation de Asservissement

#include "AX12_CAN.h"                                  // Utilisation de Asservissement
#include "EA_CAN.h"                                    // Utilisation de Asservissement
#include "SWITCH_CAN.h"                                // Utilisation de Asservissement
#include "SONAR_CAN.h"                                 // Utilisation de Asservissement

class Action{
  public:
    static const byte STATE_ARRET = 0;                 // Action terminée
    static const byte STATE_ACTION = 1;                // Action en cours

    #ifdef HAS_AX12
      static const int AX12_STORE = 580;               // Canne AX12 rangée
      static const int AX12_UP = 380;                  // Canne AX12 en haut
      static const int AX12_DOWN = 240;                // Canne AX12 en bas
      
      static const int AX12_OPEN = 531;                // Porte AX12 ouverte
      static const int AX12_CLOSE = 216;               // Porte AX12 fermée
      
      static const int AX12_LEAN = 200;                // Parasol couché
      static const int AX12_DEPLOY = 500;              // Parasol sorti
    #endif

    #ifdef HAS_EA
      static const int EA_ON = 1;                     // Canne AX12 rangée
      static const int EA_OFF = 0;                    // Canne AX12 en haut
    #endif
    
    Action();
    
    void step();                                       // Appel des fonctions de mises à jour des actions
    void step( bool AX12, bool EA );                   // Appel des fonctions de mises à jour des actions
    char getState();                                   // Retourne l'état des actions ( 0 : A terminé l'ation actuelle; 1 : En cours d'action; X : Indéfini )
    int receiveStart();
    void validStart( bool val );

    #ifdef HAS_AX12
      void setAX12( unsigned char id, int consigne );  // Permet de définir la position d'un AX12
      void setAX12( String group, int consigne );      // Permet de définir la position d'un d'AX12 ou groupe d'AX12 à l'aide d'un nom
      void setAllAX12( int consigne );                 // Permet de définir la position de tout les AX12
    #endif
    
    #ifdef HAS_EA
      int receiveEA();                                 // Permet de récuperer l'état des electro-aimants
      void setEA( int state );                        // Permet de définir l'état des electro-aimants
    #endif
    
    #ifdef HAS_SWITCH
      int receiveSwitch( int id );
    #endif
    
    #ifdef HAS_SONAR
      int receiveSonarPWM();
      int receiveSonarClassic();
    #endif
    
  private:
    #ifdef HAS_AX12
      bool tempAX12Finished = true;                    // Sauvegarde de l'état des AX12 déjà verifiés
      int lastAX12IdVerif = -1;                        // Sauvegarde de l'id du dernier AX12 verifié
      int AX12Id;                                      // Sauvegarde l'id des AX12 activés
      int AX12Pos[254];                                // Sauvegarde la position demandée aux AX12
      
      AX12_CAN AX12;                                   // Instantiation de la classe AX12_CAN

      void AX12Init();                                 // Initialisation des paramètres liés aux AX12
      bool AX12Step();                                 // Appel des fonctions de mises à jour des AX12
    #endif
    
    #ifdef HAS_EA
      bool EAState;
      
      EA_CAN EA;                                       // Instantiation de la classe EA_CAN
      
      void EAInit();                                   // Initialisation des paramètres liés aux EA
      bool EAStep();                                   // Appel des fonctions de mises à jour des EA
    #endif
    
    #ifdef HAS_SWITCH
      SWITCH_CAN SWITCH;                               // Instantiation de la classe SWITCH_CAN
    #endif
    
    #ifdef HAS_SONAR
      SONAR_CAN SONAR;                                 // Instantiation de la classe EA_CAN
    #endif
    
    char state;                                        // Stocke l'état des actions ( 0 : A terminé l'ation actuelle; 1 : En cours d'action; X : Indéfini )
    
    NewCAN can;
};

#endif
