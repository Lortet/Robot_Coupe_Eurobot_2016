#include "Interval.h"
#include "Movement.h"
#include "SerialBuffer.h"

Interval interval( false, 0 );
Movement move;
SerialBuffer blueSerial( 3, '\n', 300, 25 );

int stepNumber = 0;
int run = false;

void setup(){
  move.stop();
  blueSerial.begin(115200);
  //blueSerial.buffWait( "START" );

  interval.start();
}

void loop(){
  if( move.getState() == Asservissement::STATE_ARRET ){
    //delay( 2000 );
    
    switch( stepNumber ){
      case 0:
        move.goToXY( Codeurs::TICKS_BY_METER/2, 0 );
        break;
      case 1:
        move.goToXY( Codeurs::TICKS_BY_METER/2, Codeurs::TICKS_BY_METER/2 );
        break;
  	  case 2:
       move.goToXY( 0, Codeurs::TICKS_BY_METER/2 );
  	    break;
      case 3:
        move.goToXY( 0, 0 );
        break;
  	  default:
  	    stepNumber = -1;
  	}
  	stepNumber++;
  }
 
  move.step();
  interval.waitIntervalEnding();
}
