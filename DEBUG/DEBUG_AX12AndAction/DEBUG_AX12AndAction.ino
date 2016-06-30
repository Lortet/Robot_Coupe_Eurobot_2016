#include "MoteursNoCoeffs.h"
#include "Action.h"
#include "AX12_CAN.h"

Moteurs mot;
Action action;
AX12_CAN AX12;

int stepNumber = -1;

void setup(){
  Serial.begin(115200);
}

void loop(){
  if( action.getState() == Action::STATE_ARRET ){
    stepNumber++;
    
    int i = 0;
    if( stepNumber == i++ ) {
      Serial.println( "Descendre cannes" );
      action.setAX12("cannes", Action::AX12_DOWN);
    }
    else if( stepNumber == i++ ) {
      Serial.println( "Monter cannes" );
      action.setAX12("cannes", Action::AX12_UP);
    }
    else if( stepNumber == i++ ) {
      Serial.println( "Ranger cannes" );
      action.setAX12("cannes", Action::AX12_STORE);
    }
    else if( stepNumber == i++ ) {
      Serial.println( "Ouvrir porte" );
      action.setAX12("porte1", Action::AX12_OPEN);
    }
    else if( stepNumber == i++ ) {
      Serial.println( "Fermer porte" );
      action.setAX12("porte1", Action::AX12_CLOSE);
    }
    else if( stepNumber == i++ ) {
      Serial.println( "Parasol couché" );
      action.setAX12("parasol1", Action::AX12_LEAN);
    }
    else if( stepNumber == i++ ) {
      Serial.println( "Parasol sortie" );
      action.setAX12("parasol1", Action::AX12_DEPLOY);
    }
    else stepNumber = -1;
    
    delay( 500 );
  }
  
  delay( 500 );
  
  if( action.getState() != Action::STATE_ARRET ) action.step();
}


