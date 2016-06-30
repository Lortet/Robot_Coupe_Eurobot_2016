//----------------------------------------------------------------------//
//                                NewCAN                                //
//                                                    version 16.05.04  //
//                                             date 04/05/2016 - 17h45  //
//----------------------------------------------------------------------//
//  Surcouche pour la communication CAN                                 //
//----------------------------------------------------------------------//
//                                      Julien GODET & Valentin LORTET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//----------------------------------------------------------------------//

#include "NewCAN.h"

void NewCAN::initCan0() {
  if( isInitCan0var ) return;
  
  Serial.println( "Initialisation Can0" );
  for( int i = 0; i < MAX_CAN_ID; i++ ) can0Time[i] = 0;
  
  Can0.begin(CAN_BPS_100K, 5);
  Can0.watchFor();
  
  isInitCan0var = true;
  Serial.println( "Can0 initialisé" );
}
void NewCAN::initCan1() {
  if( isInitCan1var ) return;
  
  Serial.println( "Initialisation Can1" );
  for( int i = 0; i < MAX_CAN_ID; i++ ) can1Time[i] = 0;
  
  Can1.begin(CAN_BPS_100K, 5);
  Can1.watchFor();
  
  isInitCan1var = true;
  Serial.println( "Can1 initialisé" );
}

void NewCAN::step() {
  long startTime;
  int maxTime = 1000;
  
  Serial.println( "CAN STEP" );

  CAN_FRAME frame;
  
  if( isInitCan0() ){
    Serial.println( "Verification Available Can0" );
    startTime = micros();
    while( micros()-startTime < maxTime && Can0.available() ) {
      Serial.println( "Message disponible" );
      Can0.read( frame );
      if( frame.id < MAX_CAN_ID ) { // < 0x400
        can0Time[ frame.id ] = micros();
        can0Data[ frame.id ] = frame;
      }
    }
  }
  else Serial.println( "Can0 non initialisé" );
  
  if( isInitCan1() ){
    Serial.println( "Verification Available Can1" );
    startTime = micros();
    while( micros()-startTime < maxTime && Can1.available() ) {
      Serial.println( "Message disponible" );
      Can1.read( frame );
      if( frame.id < MAX_CAN_ID ) {
        can1Time[ frame.id ] = micros();
        can1Data[ frame.id ] = frame;
      }
    }
  }
  else Serial.println( "Can1 non initialisé" );
}

bool NewCAN::isInitCan0() {
  return isInitCan0var;
}
bool NewCAN::isInitCan1() {
  return isInitCan1var;
}

CAN_FRAME NewCAN::readCan0( int adr ) {
  return can0Data[ adr ];
}
//long NewCAN::readCan0Val( int adr ) {
//  return can0Data[ adr ].data.value;
//}
byte NewCAN::readCan0Byte( int adr, char byte ) {
  return readCan0( adr ).data.byte[ byte ];
}
long NewCAN::readCan0Low( int adr ) {
  return readCan0( adr ).data.low;
}
long NewCAN::readCan0High( int adr ) {
  return readCan0( adr ).data.high;
}
long NewCAN::getCan0Time( int adr ) {
  return can0Time[ adr ];
}
void NewCAN::sendCan0Frame( CAN_FRAME frame ) {
  Can0.sendFrame( frame );
}
void NewCAN::sendCan0Frame( int id, int length, byte seven, byte six, byte five, byte four, byte three, byte two, byte one, byte zero ) {
  CAN_FRAME frame;
  frame.id = id;
  frame.length = length;
  frame.data.byte[0] = zero;
  if( length >= 2 ) frame.data.byte[1] = one;
  if( length >= 3 ) frame.data.byte[2] = two;
  if( length >= 4 ) frame.data.byte[3] = three;
  if( length >= 5 ) frame.data.byte[4] = four;
  if( length >= 6 ) frame.data.byte[5] = five;
  if( length >= 7 ) frame.data.byte[6] = six;
  if( length >= 8 ) frame.data.byte[7] = seven;
  sendCan0Frame( frame );
}
void NewCAN::sendCan0Frame( int id, byte zero ) {
  sendCan0Frame( id, 1, 0, 0, 0, 0, 0, 0, 0, zero );
}
void NewCAN::sendCan0Frame( int id, byte one, byte zero ) {
  sendCan0Frame( id, 2, 0, 0, 0, 0, 0, 0, one, zero );
}
void NewCAN::sendCan0Frame( int id, byte two, byte one, byte zero ) {
  sendCan0Frame( id, 3, 0, 0, 0, 0, 0, two, one, zero );
}
void NewCAN::sendCan0Frame( int id, byte three, byte two, byte one, byte zero ) {
  sendCan0Frame( id, 4, 0, 0, 0, 0, three, two, one, zero );
}
void NewCAN::sendCan0Frame( int id, byte four, byte three, byte two, byte one, byte zero ) {
  sendCan0Frame( id, 5, 0, 0, 0, four, three, two, one, zero );
}
void NewCAN::sendCan0Frame( int id, byte five, byte four, byte three, byte two, byte one, byte zero ) {
  sendCan0Frame( id, 6, 0, 0, five, four, three, two, one, zero );
}
void NewCAN::sendCan0Frame( int id, byte six, byte five, byte four, byte three, byte two, byte one, byte zero ) {
  sendCan0Frame( id, 7, 0, six, five, four, three, two, one, zero );
}
void NewCAN::sendCan0Frame( int id, byte seven, byte six, byte five, byte four, byte three, byte two, byte one, byte zero ) {
  sendCan0Frame( id, 8, seven, six, five, four, three, two, one, zero );
}

CAN_FRAME NewCAN::readCan1( int adr ) {
  return can1Data[ adr ];
}
//long NewCAN::readCan1Val( int adr ) {
//  return can1Data[ adr ].data.value;
//}
byte NewCAN::readCan1Byte( int adr, char byte ) {
  return readCan1( adr ).data.byte[ byte ];
}
long NewCAN::readCan1Low( int adr ) {
  return readCan1( adr ).data.low;
}
long NewCAN::readCan1High( int adr ) {
  return readCan1( adr ).data.high;
}
long NewCAN::getCan1Time( int adr ) {
  return can1Time[ adr ];
}
void NewCAN::sendCan1Frame( CAN_FRAME frame ) {
  Can1.sendFrame( frame );
}
void NewCAN::sendCan1Frame( int id, int length, byte seven, byte six, byte five, byte four, byte three, byte two, byte one, byte zero ) {
  CAN_FRAME frame;
  frame.id = id;
  frame.length = length;
  frame.data.byte[0] = zero;
  if( length >= 2 ) frame.data.byte[1] = one;
  if( length >= 3 ) frame.data.byte[2] = two;
  if( length >= 4 ) frame.data.byte[3] = three;
  if( length >= 5 ) frame.data.byte[4] = four;
  if( length >= 6 ) frame.data.byte[5] = five;
  if( length >= 7 ) frame.data.byte[6] = six;
  if( length >= 8 ) frame.data.byte[7] = seven;
  sendCan1Frame( frame );
}
void NewCAN::sendCan1Frame( int id, byte zero ) {
  sendCan1Frame( id, 1, 0, 0, 0, 0, 0, 0, 0, zero );
}
void NewCAN::sendCan1Frame( int id, byte one, byte zero ) {
  sendCan1Frame( id, 2, 0, 0, 0, 0, 0, 0, one, zero );
}
void NewCAN::sendCan1Frame( int id, byte two, byte one, byte zero ) {
  sendCan1Frame( id, 3, 0, 0, 0, 0, 0, two, one, zero );
}
void NewCAN::sendCan1Frame( int id, byte three, byte two, byte one, byte zero ) {
  sendCan1Frame( id, 4, 0, 0, 0, 0, three, two, one, zero );
}
void NewCAN::sendCan1Frame( int id, byte four, byte three, byte two, byte one, byte zero ) {
  sendCan1Frame( id, 5, 0, 0, 0, four, three, two, one, zero );
}
void NewCAN::sendCan1Frame( int id, byte five, byte four, byte three, byte two, byte one, byte zero ) {
  sendCan1Frame( id, 6, 0, 0, five, four, three, two, one, zero );
}
void NewCAN::sendCan1Frame( int id, byte six, byte five, byte four, byte three, byte two, byte one, byte zero ) {
  sendCan1Frame( id, 7, 0, six, five, four, three, two, one, zero );
}
void NewCAN::sendCan1Frame( int id, byte seven, byte six, byte five, byte four, byte three, byte two, byte one, byte zero ) {
  sendCan1Frame( id, 8, seven, six, five, four, three, two, one, zero );
}

