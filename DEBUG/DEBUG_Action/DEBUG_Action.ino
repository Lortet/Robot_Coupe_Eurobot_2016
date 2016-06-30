#include "Action.h"
#include "SerialBuffer.h"

Action action;
SerialBuffer blueSerial( 0, '\n', 300, 25 );

void setup(){
  blueSerial.begin(115200);
  blueSerial.buffWait( "START" );
  
  blueSerial.println( "START" );
}

void loop(){
  int stepNumber = -1;
  
  while( 1 ) {
    blueSerial.println( "Loop" );
    
    
    action.setAllAX12( Action::AX12_STORE );
    delay( 2500 );
    
    action.setAllAX12( Action::AX12_DOWN );
    delay( 2500 );
    
    action.setAllAX12( Action::AX12_UP );
    delay( 2500 );
      
    /*
    if( action.getState() == Action::STATE_ARRET ){
      stepNumber++;
      blueSerial.println( "Etape : " + String( stepNumber ) );
      
      switch( stepNumber ){
    	  case 0:
    	    action.setAllAX12( Action::AX12_STORE );
    	    break;
    	  case 1:
          action.setAllAX12( Action::AX12_DOWN );
    	    break;
    	  case 2:
          action.setAllAX12( Action::AX12_UP );
          break;
    	  default:
    	    stepNumber = -1;
    	}
    }
   
    blueSerial.println( "Step" );
    action.step();
    */
  }
}
