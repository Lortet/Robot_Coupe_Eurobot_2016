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

#include "Movement.h"

void Movement::step(){
  long codeurG;
  long codeurD;

  codeurs.updateAndGetTicks( &codeurG, &codeurD );
  
  odom.updatePosition( codeurG, codeurD );
  asser.step( codeurG, codeurD );
}

char Movement::getState(){
  return asser.getState();
}
void Movement::goToXY(double x, double y){
  double rotation;
  double translation;

  stop();

  Position pos = getPos();
  
  deltaCoord( pos.getX(), pos.getY(), pos.getO(), x, y, &rotation, &translation );
  
  addConsigne( rotation/TWO_PI*Codeurs::TICKS_BY_TURN, translation );
}
void Movement::deltaCoord(double x, double y, double o, double targetX, double targetY, double *rotation, double *translation){
  double angle;
  
  double d_x = targetX - x;
  double d_y = targetY - y;
  
  *translation = sqrt( d_x*d_x + d_y*d_y );
  
  if( d_x == 0 ){
    if( d_y == 0 ) angle = 0;
    else if( d_y >= 0 ) angle = PI/2;
    else angle = -PI/2;
  }
  else angle = atan( d_y / d_x );
  
  if( d_x < 0 ) angle += PI;
  
  *rotation = Position::deltaRad( o, angle );
}
void Movement::allowArc(){
  asser.allowArc();
}
void Movement::stop(){
  long codeurL, codeurR;

  codeurs.updateAndGetTicks( &codeurL, &codeurR );
  asser.stop( codeurL, codeurR );
}
void Movement::waitStop(){
  long codeurL, codeurR;

  asser.stopMoteurs();
  
  while( !isStopped() );
  
  stop();
}
boolean Movement::isStopped(){
  long codeurL, codeurR;
  long lastCodeurL, lastCodeurR;

  codeurs.updateAndGetTicks( &lastCodeurL, &lastCodeurR );
  
  delay( 5 );
  
  codeurs.updateAndGetTicks( &codeurL, &codeurR );
  
  if( codeurL == lastCodeurL || codeurR == lastCodeurR ) return true;
  else return false;
}

void Movement::setConsigneRot(long rotation){
  asser.setConsigneRot( rotation );
}
void Movement::setConsigneTra(long translation){
  asser.setConsigneTra( translation );
}
void Movement::setConsigne(long rotation, long translation){
  asser.setConsigne( rotation, translation );
}

void Movement::addConsigneRot(long rotation){
  asser.addConsigneRot( rotation );
}
void Movement::addConsigneTra(long translation){
  asser.addConsigneTra( translation );
}
void Movement::addConsigne(long rotation, long translation){
  asser.addConsigne( rotation, translation );
}

Position Movement::getPos(){
  return odom.getPos();
}
