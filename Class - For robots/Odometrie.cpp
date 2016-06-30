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

#include "Odometrie.h"                                     //Utilisation de Odometrie()

Odometrie::Odometrie(){
  reset();
}

Position Odometrie::getPos(){
  return pos;
}

void Odometrie::updatePosition( long codeurL, long codeurR ) {
  long deltaAngleTicks, deltaDistanceTicks;

  calcDeltaTicks( codeurL, codeurR, &deltaAngleTicks, &deltaDistanceTicks );

  calcAndSavePosition( codeurL, codeurR, deltaAngleTicks, deltaDistanceTicks );
}

void Odometrie::calcDeltaTicks( long codeurL, long codeurR, long *deltaAngleTicks, long *deltaDistanceTicks ) {
  long deltaRoueL = codeurL - lastCodeurL;
  long deltaRoueR = codeurR - lastCodeurR;

  *deltaAngleTicks = ( deltaRoueL - deltaRoueR );         // Calcul de la variation de l'angle
  *deltaDistanceTicks = ( deltaRoueL + deltaRoueR );      // Calcul de la variation de la distance

  lastCodeurL = codeurL;
  lastCodeurR = codeurR;
}

void Odometrie::calcAndSavePosition( long codeurL, long codeurR, long deltaAngleTicks, long deltaDistanceTicks ) {
  //pos.addO( (double)TWO_PI/Codeurs::TICKS_BY_TURN*deltaAngleTicks );    // Calcul de la valeur de l'angle en Radian
  pos.setO( (double)TWO_PI/Codeurs::TICKS_BY_TURN*((codeurL - codeurR)%Codeurs::TICKS_BY_TURN) );      // Calcul de la valeur de l'angle en Radian

  pos.addX( cos( pos.getO() )*deltaDistanceTicks );                     	// Valeur de X
  pos.addY( sin( pos.getO() )*deltaDistanceTicks ); 	                    // Valeur de Y
}

void Odometrie::reset(){
  this->lastCodeurL = 0;
  this->lastCodeurR = 0;
}
