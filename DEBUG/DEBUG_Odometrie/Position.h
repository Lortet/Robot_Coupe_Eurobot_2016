//----------------------------------------------------------------------//
//                               POSITION                               //
//                                                    version 16.04.24  //
//                                             date 24/04/2016 - 13h08  //
//----------------------------------------------------------------------//
//  Permet de manipuler des positions suivant les axes X et Y, ainsi    //
//  qu'un angle en radian ou degré.                                     //
//----------------------------------------------------------------------//
//                                                     Valentin LORTET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//----------------------------------------------------------------------//

#ifndef __POSITION_H__                                    // Si la constante n'est pas définie
#define __POSITION_H__                                    // On la définie de manière à ce que le fichier ne soit plus inclus

#include "Arduino.h"                                      // Utilisation de PI

class Position{
  public:
    Position();                                           // Initialisation (=reset())

    double getX();                                        // Récuperer l'axe x
    double getY();                                        // Récuperer l'axe y
    double getO();                                        // Récuperer l'angle
    double getDegO();                                     // Récuperer l'angle en degré

    void setX(double x);                                  // Définir l'axe x
    void setY(double y);                                  // Définir l'axe y
    void setO(double O);                                  // Définir l'angle
    void setDegO(double O);                               // Définir l'angle en degré

    void addX(double x);                                  // Incrémenter ou décrementer l'axe x
    void addY(double y);                                  // Incrémenter ou décrementer l'axe y
    void addO(double O);                                  // Incrémenter ou décrementer l'angle
    void addDegO(double O);                               // Incrémenter ou décrementer l'angle en degré

    void modO();                                          // Incrémenter ou décrementer l'angle en degré

    void reset();                                         // Réinitialise la position (x=0; y=0; O=0)

    static double degFromRad(double rad);                 // Retourne le résultat de la conversion de radians vers des degrés
    static double radFromDeg(double deg);                 // Retourne le résultat de la conversion de degrés vers des radians
    static double modRad(double rad);                     // Retourne le modulo des radians (<= PI && > -PI)
    static double deltaRad(double rad, double targetRad); // Retourne le delta le plus court entre deux angles en radian (-3.14 to 3.13 => -0.01)

  private:
    double x;                                             // Axe x
    double y;                                             // Axe y
    double O;                                             // Angle en radian
};

#endif
