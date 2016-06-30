//----------------------------------------------------------------------//
//                               ODOMETRIE                              //
//                                                    version 16.04.25  //
//                                             date 25/04/2016 - 23h06  //
//----------------------------------------------------------------------//
//  Permet de repérer le robotsur le plateau à l'aide des codeurs       //
//----------------------------------------------------------------------//
//                                 Benjamin BROSSEAU & Valentin LORTET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//        Adapté des travaux de Kevin LE MOGUEN et Thibault d'ARTIGUES  //
//----------------------------------------------------------------------//

#ifndef __ODOMETRIE_H__                                // Si la constante n'est pas définie
#define __ODOMETRIE_H__                                // On la définie de manière à ce que le fichier ne soit plus inclus

#include "Arduino.h"                                   //Utilisation de la constante PI
#include "Codeurs.h"                                   //Utilisation de TICKS_BY_TURN
#include "Position.h"                                  //Utilisation de Position

class Odometrie{
  public:
    Odometrie();                                       // Initialisation (=reset())

    Position getPos();                                 // Récupere la position

    void updatePosition( long codeurL, long codeurR ); // Cette fonction a appeler sert à calculer la position du robot sur le terrain

    void reset();                                      // Réinitialise l'odométrie

  private:
    Position pos;

    void calcDeltaTicks( long codeurL, long codeurR, long *deltaAngleTicks, long *deltaDistanceTicks );
    void calcAndSavePosition( long codeurL, long codeurR, long deltaAngleTicks, long deltaDistanceTicks );

    long lastCodeurL;
    long lastCodeurR;
};

#endif

