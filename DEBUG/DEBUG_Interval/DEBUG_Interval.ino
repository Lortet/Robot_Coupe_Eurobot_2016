#include "Interval.h"

Interval interval( false, 10 );

void setup() {
  Serial.begin( 115200 );
  
  interval.start();
}

void loop() {
  int i = 0;

  while( 1 ){
  
    Serial.println( "(" + String( interval.getMicro()? micros() : millis() ) + ") : Nouvelle boucle" );
    
    Serial.println( "Programme de : " + String( i ) + ( interval.getMicro()? " microseconde(s)" : " milliseconde(s)" ) );
    
    if( interval.getMicro() ) delayMicroseconds( i );
    else delay( i );
    
    Serial.println( "(" + String( interval.getMicro()? micros() : millis() ) + ") : Temps min -> " + String( interval.getMinTime() ) );
    Serial.println( "(" + String( interval.getMicro()? micros() : millis() ) + ") : Temps max -> " + String( interval.getMaxTime() ) );
    
    Serial.println();
    
    interval.waitIntervalEnding();
  
  }
}
