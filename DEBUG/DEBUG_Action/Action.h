//----------------------------------------------------------------------//
//                               MOVEMENT                               //
//                                                    version 16.04.25  //
//                                             date 25/04/2016 - 22h51  //
//----------------------------------------------------------------------//
//  Permet de déplacer le robot suivant un système d'axes.              //
//----------------------------------------------------------------------//
//                                                     Valentin LORTET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//----------------------------------------------------------------------//

#ifndef __ACTION_H__                                   // Si la constante n'est pas définie
#define __ACTION_H__                                   // On la définie de manière à ce que le fichier ne soit plus inclus

#include <Arduino.h>                                   // Utilisation de Asservissement
#include "Configuration.h"                             // Utilisation de Asservissement
#include "AX12_CAN.h"                                  // Utilisation de Asservissement

class Action{
  public:
    static const byte STATE_ARRET = 0;                 // Action terminée
    static const byte STATE_ACTION = 1;                // Action en cours

    #ifdef HAS_AX12
      static const int AX12_STORE = 620;               // Canne AX12 rangée
      static const int AX12_UP = 450;                  // Canne AX12 en haut
      static const int AX12_DOWN = 138;                // Canne AX12 en bas
      
      static const int AX12_OPEN = 531;                // Porte AX12 ouverte
      static const int AX12_CLOSE = 216;               // Porte AX12 fermée
      
      static const int AX12_LEAN = 0;                  // Parasol couché
      static const int AX12_DEPLOY = 200;              // Parasol sorti
    #endif
    
    Action();
    
    void step();                                       // Permet d'effectuer un pas de l'asservissement
    char getState();                                   // Retourne l'état des actions ( 0 : A terminé l'ation actuelle; 1 : En cours d'action; X : Indéfini )

    #ifdef HAS_AX12
      void setAX12( unsigned char id, int consigne );  // Permet de définir la position d'un AX12
      void setAX12( String group, int consigne );      // Permet de définir la position d'un d'AX12 ou groupe d'AX12 à l'aide d'un nom
      void setAllAX12( int consigne );                 // Permet de définir la position de tout les AX12
    #endif
    
  private:
    #ifdef HAS_AX12
      int AX12Id;                                      // Sauvegarde l'id des AX12 activés
      int AX12Pos[254];                                // Sauvegarde la position demandée aux AX12
      
      AX12_CAN AX12;                                   // Instantiation de la classe AX12_CAN

      void AX12Init();                                 // Initialisation des paramètres liés aux AX12
      bool AX12Step();                                 // Appel des fonctions de mises à jour des AX12
    #endif
    
    char state;                                        // Stocke l'état des actions ( 0 : A terminé l'ation actuelle; 1 : En cours d'action; X : Indéfini )
};

#endif
