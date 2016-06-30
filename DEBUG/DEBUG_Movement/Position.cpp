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

#include "Position.h"

Position::Position(){
  reset();
}

double Position::getX() {
  return x;
}
double Position::getY(){
  return y;
}
double Position::getO(){
  return O;
}
double Position::getDegO(){
  return degFromRad( getO() );
}

void Position::addX(double x) {
  this->x += x;
}
void Position::addY(double y){
  this->y += y;
}
void Position::addO(double O){
  this->O += O;
  modO();
}
void Position::addDegO(double O){
  addO( radFromDeg( O ) );
}

void Position::setX(double x) {
  this->x = x;
}
void Position::setY(double y){
  this->y = y;
}
void Position::setO(double O){
  this->O = O;
  modO();
}
void Position::setDegO(double O){
  setO( radFromDeg( O ) );
}

void Position::modO(){
  O = modRad( O );
}

void Position::reset(){
  x = 0;
  y = 0;
  O = 0;
}

double Position::degFromRad(double rad){
  return degrees( rad );
}
double Position::radFromDeg(double deg){
  return radians( deg );
}
double Position::modRad(double rad){
  if( rad > PI ) rad -= TWO_PI;
  else if( rad <= -PI) rad += TWO_PI;
  
  if( rad > PI || rad <= -PI ) rad = modRad( rad );
  
  return rad;
}
double Position::deltaRad(double actualRad, double destRad){
  return modRad( destRad - actualRad );
}
