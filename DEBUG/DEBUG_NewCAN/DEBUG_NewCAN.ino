#include "NewCAN.h"

NewCAN can;

void setup(){
  Serial.begin( 115200 );
  
  Serial.println( "--- Start ---" );
  
  can.initCan0();
}

void loop(){
  can.step();
  
  int delayT = 200;
  
  for( int i = 0; i < 10; i++ ) {
    Serial.println( "9" );
    can.sendCan0Frame( 0x1, 0xF, 0xA, 0xc, 0xE, 0xB, 0xC, 0xA, 0xB );
  }
  
  for( int i = 0; i < 10; i++ ) {
    Serial.println( "9" );
    can.sendCan0Frame( 0x8, 0xF, 0xA, 0xc, 0xE, 0xB, 0xC, 0xA, 0xB );
  }
  
  for( int i = 0; i < 10; i++ ) {
    Serial.println( "9" );
    can.sendCan0Frame( 0x6, 0xF, 0xA, 0xc, 0xE, 0xB, 0xC, 0xA, 0xB );
  }
  
  for( int i = 0; i < 10; i++ ) {
    Serial.println( "9" );
    can.sendCan0Frame( 0x9, 0xF, 0xA, 0xc, 0xE, 0xB, 0xC, 0xA, 0xB );
  }
  
  
  can.step();
  
  
  Serial.println( "Verification des messages CAN" );
  for( int i = 0; i < MAX_CAN_ID; i++ ){
    if( can.getCan0Time( i ) != 0 ) {
      Serial.print( "Message " );
      Serial.print( i, HEX );
      Serial.print( " : " );
      Serial.print( can.readCan0High( i ), HEX );
      Serial.print( " " );
      Serial.print( can.readCan0Low( i ), HEX );
      Serial.println( " (" + String( can.getCan0Time( i ) ) + ")" );
    }
  }
  Serial.println( "Fin de verification" );
}

