//----------------------------------------------------------------------//
//                               MOVEMENT                               //
//                                                    version 16.04.02  //
//                                             date 02/04/2016 - 00h57  //
//----------------------------------------------------------------------//
//  Permet de déplacer le robot suivant un système d'axes.              //
//----------------------------------------------------------------------//
//                                                     Valentin LORTET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//----------------------------------------------------------------------//

#ifndef __MOVEMENT_H__                                                                                // Si la constante n'est pas définie
#define __MOVEMENT_H__                                                                                // On la définie de manière à ce que le fichier ne soit plus inclus

#include <Arduino.h>                                                                                  // Utilisation de PI
#include "Asservissement.h"                                                                           // Utilisation de Asservissement
#include "Odometrie.h"                                                                                // Utilisation de Odometrie()
#include "Position.h"                                                                                 // Utilisation de Position
#include "Codeurs.h"                                                                                  // Utilisation de Codeurs

class Movement{
  
  public:
    void step();                                                                                      // Permet d'effectuer un pas de l'asservissement
    char getState();                                                                                  // 0 : A terminé le mouvement actuel; 1 : En cours de translation; 2 : En cours de rotation; X : Indéfini
    void goToXY(double x, double y);                                                                  // Se rend aux coordonnées demandées
    static void deltaCoord(double x, double y, double o, double targetX, double targetY, double *rotation, double *translation);  // Retourne la différence de rotation et de translation séparant deux coordonnées x,y
    void allowArc();                                                                                  // Autorise la rotation et la translation en simultané
    void stop();                                                                                      // Force la fin du mouvement actuel
    void stopMoteurs();                                                                               // Force l'arret des moteurs
    void waitStop();                                                                                  // Force et attend la fin du mouvement actuel
    boolean isStopped();                                                                              // Retourne si le robot est en mouvement ou non
    
    void setConsigneRot( long rotation );                                                             // Permet de définir la consigne en rotation
    void setConsigneTra( long translation );                                                          // Permet de définir la consigne en translation
    void setConsigne( long rotation, long translation );                                              // Permet de définir la consigne en rotation et translation
    
    void addConsigneRot( long rotation );                                                             // Permet d'ajouter des contraintes à la consigne actuelle en rotation
    void addConsigneTra( long translation );                                                          // Permet d'ajouter des contraintes à la consigne actuelle en translation
    void addConsigne( long rotation, long translation );                                              // Permet d'ajouter des contraintes à la consigne actuelle en rotation et translation
    
    void setSpeed( float speed );                               						              // Permet de modifier la vitesse des moteurs
    
    void takenTroubles();                                                                             // Permet de valider la detection d'un problème (et donc le considérer comme résolu)
    
    void setReverseXAxis( bool reverse );
    void setReverseYAxis( bool reverse );
    
    Position getPos();                                                                                // Récupere la position
    
  private:
    bool reverseXAxis = false;
    bool reverseYAxis = false;
    
    Codeurs codeurs;                                                                                  // Instantiation de la classe Codeurs
    Asservissement asser;                                                                             // Instantiation de la classe Asservissement
    Odometrie odom;                                                                                   // Instantiation de la classe Odometrie
};

#endif
