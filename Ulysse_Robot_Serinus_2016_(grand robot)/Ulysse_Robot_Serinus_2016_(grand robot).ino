#include <Arduino.h>
#include "Configuration.h"
#include "Interval.h"
#include "Movement.h"
#include "Action.h"
#include "NewCAN.h"
#include "SerialBuffer.h"

Interval interval( true, 2000 );
Movement move;
Action action;
NewCAN can;
SerialBuffer debugSerial( 0, '\n', 300, 25 );

bool run = true;
int stepNumber = -1;

void setup(){
  move.stopMoteurs();
  move.stop();
  debugSerial.begin(115200);
  can.initCan0();
  
  debugSerial.println( "--- START ---" );
}

void loop(){  
  // Récupération du premier état du start (La prise doit être branchée avant alimentation pour être utilisable)
  debugSerial.println( "Is Connected Start ?" ); 
  
  int START_WAIT = 0, START_START = 1;
  
  debugSerial.println( "Attente Prise (Is Connected Start ?)" ); 
  while( action.receiveStart() == 65535 ) {
     debugSerial.println( "Step JACK (Is Connected Start ?)" );
     can.step();
  };
  bool connectedStart = (( action.receiveStart() == START_WAIT )? true : false ); // Si la prise n'est pas branchée, elle ne sera pas utiliser pour démarrer et seul le port série fonctionnera
  
  debugSerial.println( "Connected Start : " + String( connectedStart ) + " (Is Connected Start ?)" );
  
  
  
  // Récupération des switchs (Les switch doivent être configurés avant alimentation) ------------------------
  debugSerial.println( "Recuperation des switchs" ); 
  
  int SWITCH_COLOR = 0x002, COLOR_PURPLE = 0, COLOR_GREEN = 1; // Configuration du switch de couleur
  int SWITCH_CONFIG = 0x001, CONFIG_125 = 1, CONFIG_34 = 0; // Configuration du switch de configuration
  
  int COLOR = 65535, CONFIG = 65535;
  while( COLOR == 65535 || CONFIG == 65535 ){
    debugSerial.println( "Mise à jour CAN (Recuperation des switchs)" ); 
    can.step();
    
    COLOR = action.receiveSwitch( SWITCH_COLOR );
    CONFIG = action.receiveSwitch( SWITCH_CONFIG );
    
    debugSerial.println( "Color : " + String( COLOR ) + " ; Config : " + String( CONFIG ) + " (Recuperation des switchs)" ); 
  }
  
  move.setReverseYAxis( (( COLOR == COLOR_PURPLE )? false : true ) );
  debugSerial.println( "Validation (Recuperation des switchs)" ); 
  
  
  
  // Initialisation Action
  debugSerial.println( "Initialisation des actions" ); 
  
  while( action.getState() != Action::STATE_ARRET ){
    debugSerial.println( "Step (Initialisation des actions)" );
    action.step( true, false );
    can.step();
  }
  debugSerial.println( "Validation (Initialisation des actions)" );
  
  // Attente de la consigne de démarrage (Prise ou START) -------------------------------------------------------------
  debugSerial.println( "Attente start" );
  
  // Attente du retrait de la prise si elle était connectée au démarrage ou de la commande START
  while( !( connectedStart && action.receiveStart() == START_START || debugSerial.buffStepAndIsCompleted() && debugSerial.buffRead() == "START" ) ) {
    Serial.println( "Mise à jour CAN (Attente start)" );
    
    // if( action.receiveStart() == START_WAIT ) connectedStart = true; // Autoriser rebranchement puis debranchement de la prise
    
    can.step();
  };

  debugSerial.println( "Validation du start (Attente start)" ); 
  


  // Initialisation ---------------------------------------------------------------------------------------------------
  debugSerial.println( "Changement etat init/strategie" );
  
  long startTime = millis(); // Temps afin de valider les 90/95 secondes
  
  // Si les sonars ne sont pas recu, les 
  while( action.receiveSonarPWM() == 65535 ) {
      debugSerial.println( "Demande (Changement etat init/strategie)" );
      action.validStart( 1 ); // Demande d'envois des sonars et autres composants non utile au demarrage
      
      debugSerial.println( "Mise à jour CAN (Changement etat init/strategie)" );
      can.step();
  }
  
  debugSerial.println( "Validation (Changement etat init/strategie)" );
  
  
  
  // Code de stratégie ------------------------------------------------------------------------------------------------
  
  debugSerial.println( "Strategie" );
  
  // bool run = true; // Remplacé par une variable global pour contrôle par Bluetooth
  // int stepNumber = -1; // Remplacé par variable global pour contrôle par Bluetooth
  
  // Raccourcis
  float MM = Codeurs::TICKS_BY_MM;
  float DEG = Codeurs::TICKS_BY_DEG;
    
  bool allowSonars = true; // Sonars activés par defaut

  interval.start(); // Demarrage du compteur de regularité des boucles

  long tempTime;

  // Boucle d'execution de la stratégie  
  // while( run ) { // Boucle sans delais
  while( run &&  ( millis()-startTime ) < 90*1000 ) { // Boucle s'arrêtant au maximum 90 secondes après execution
    if( move.getState() == Asservissement::STATE_ARRET && action.getState() == Action::STATE_ARRET ){ // Si le mouvement ou l'action actuelle est terminée
      stepNumber++;
      debugSerial.println( "Etape " + String( stepNumber ) );
  
      int i = 0;
      
      
      // ---- PARCOURS -----------------------------------------------------------------------------------------------------------------------------
      
      if( CONFIG == CONFIG_125 ) { // --------------------------------------------------------------------------------------------------------------
          
          
          // Monticule (12345)
          if( stepNumber == i++ ) {
            allowSonars = false;
            move.setSpeed( 1.45 );
            move.goToXY( 400*MM, -55*MM );
          }
          else if( stepNumber == i++ ) {
            move.setSpeed( 0.8 );
            move.goToXY( 550*MM, -55*MM );
          }
          else if( stepNumber == i++ ) move.goToXY( 900*MM, 45*MM );
          else if( stepNumber == i++ ) {
            move.setSpeed( 1.45 );
            move.addConsigneTra( -250*MM );
          }
          
          // Coquillage
          else if( stepNumber == i++ ) {
            move.setSpeed( 1.25 );
            action.setAX12( "porte1", Action::AX12_OPEN );
            move.goToXY( 850*MM, 150*MM );
            allowSonars = true;
          }
          else if( stepNumber == i++ ) {
            move.setSpeed( 1.45 );
            move.goToXY( 800*MM, 445*MM );
          }
          
          // Peche poisson 1
          else if( stepNumber == i++ ) move.goToXY( 570*MM, 615*MM );
          else if( stepNumber == i++ ) {
            move.setSpeed( 1.1 );
            if( COLOR == COLOR_PURPLE ) move.goToXY( 570*MM, 730*MM );
            else move.goToXY( 570*MM, 690*MM );
          }
          else if( stepNumber == i++ ) {
            allowSonars = false;
            move.stop();
            action.setAX12( "porte1", Action::AX12_CLOSE );
          }
          else if( stepNumber == i++ ) {
            move.setSpeed( 1.1 );
            move.addConsigneTra( 500*MM);
            move.step();
            interval.waitIntervalEnding();
            
            tempTime = millis();
            
            while( !move.isStopped() && millis()-tempTime < 1750  ) {
              move.step();
              interval.waitIntervalEnding(); // Afin de conserver la régularité d'execution des actions (important car deplacement)
            }
            move.stop();            
          }
          else if( stepNumber == i++ ) {  
            action.setEA( true );
            while( action.getState() != Action::STATE_ARRET ){ // Tant que les actions ne sont pas validée et donc que les aimants ne sont pas allumés
              can.step();
              action.step();
            }
          }
          else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_DOWN );
          else if( stepNumber == i++ ) {
            move.setSpeed( 0.5 );
            move.addConsigneTra( -85*MM );
          }
//          else if( stepNumber == i++ ) {
//            move.stop();
//            delay( 1250 );
//          }
          else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_UP );
          else if( stepNumber == i++ ) {
            move.setSpeed( 1 );
            move.addConsigneTra( -100*MM );
          }
          
          // Poisson filet 1
          else if( stepNumber == i++ ) move.goToXY( 1060*MM, 695*MM );
          else if( stepNumber == i++ ) move.goToXY( 1060*MM, 830*MM );
          else if( stepNumber == i++ ) {  
            action.setEA( false );
            while( action.getState() != Action::STATE_ARRET ){
              can.step();
              action.step();
            }
          }
          else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_UP );
          else if( stepNumber == i++ ) move.addConsigneTra( -100*MM );
          
          // Peche poisson 2
          else if( stepNumber == i++ ) {
            move.setSpeed( 1.3 );
            move.goToXY( 640*MM, 695*MM );
          }
          else if( stepNumber == i++ ) {
            move.setSpeed( 1 );
            move.goToXY( 640*MM, 840*MM );
          }
          else if( stepNumber == i++ ) {
            move.addConsigneTra( 500*MM);
            move.step();
            interval.waitIntervalEnding();
            
            tempTime = millis();
            
            while( !move.isStopped() && millis()-tempTime < 2500  ) {
              move.step();
              interval.waitIntervalEnding(); // Afin de conserver la régularité d'execution des actions (important car deplacement)
            }
            move.stop();            
          }
          else if( stepNumber == i++ ) {  
            action.setEA( true );
            while( action.getState() != Action::STATE_ARRET ){
              can.step();
              action.step();
            }
          }
          else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_DOWN );
          else if( stepNumber == i++ ) {
            move.setSpeed( 0.5 );
            move.addConsigneTra( -85*MM );
          }
//          else if( stepNumber == i++ ) {
//            move.stop();
//            delay( 1250 );
//          }
          else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_UP );
          else if( stepNumber == i++ ) {
            move.setSpeed( 1 );
            move.addConsigneTra( -100*MM );
          }
          
          // Poisson filet 2
          else if( stepNumber == i++ ) move.goToXY( 1060*MM, 695*MM );
          else if( stepNumber == i++ ) move.goToXY( 1060*MM, 830*MM );
          //else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_DOWN );
          else if( stepNumber == i++ ) {  
            action.setEA( false );
            while( action.getState() != Action::STATE_ARRET ){
              can.step();
              action.step();
            }
          }
          else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_UP );
          else if( stepNumber == i++ ) move.addConsigneTra( -100*MM );
          
          // Peche poisson 3
          else if( stepNumber == i++ ) {
            move.setSpeed( 1.3 );
            move.goToXY( 600*MM, 695*MM );
          }
          else if( stepNumber == i++ ) {
            move.setSpeed( 1 );
            move.goToXY( 600*MM, 840*MM );
          }
          else if( stepNumber == i++ ) {
            move.addConsigneTra( 500*MM);
            move.step();
            interval.waitIntervalEnding();
            
            tempTime = millis();
            
            while( !move.isStopped() && millis()-tempTime < 2500  ) {
              move.step();
              interval.waitIntervalEnding(); // Afin de conserver la régularité d'execution des actions (important car deplacement)
            }
            move.stop();            
          }
          else if( stepNumber == i++ ) {  
            action.setEA( true );
            while( action.getState() != Action::STATE_ARRET ){
              can.step();
              action.step();
            }
          }
          else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_DOWN );
          else if( stepNumber == i++ ) {
            move.setSpeed( 0.5 );
            move.addConsigneTra( -85*MM );
          }
//          else if( stepNumber == i++ ) {
//            move.stop();
//            delay( 1250 );
//          }
          else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_UP );
          else if( stepNumber == i++ ) {
            move.setSpeed( 1 );
            move.addConsigneTra( -100*MM );
          }
          
          // Poisson filet 3
          else if( stepNumber == i++ ) move.goToXY( 1060*MM, 695*MM );
          else if( stepNumber == i++ ) move.goToXY( 1060*MM, 830*MM );
          //else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_DOWN );
          else if( stepNumber == i++ ) {  
            action.setEA( false );
            while( action.getState() != Action::STATE_ARRET ){
              can.step();
              action.step();
            }
          }
          else if( stepNumber == i++ ) {
            move.setSpeed( 1.6 );
            move.addConsigneTra( -100*MM );
            action.setAX12( "cannes", Action::AX12_STORE );
            allowSonars = true;
          }
          
          // Retour
          else if( stepNumber == i++ ) move.goToXY( 500*MM, 800*MM );
          else if( stepNumber == i++ ) move.goToXY( 155*MM, 645*MM );
          else if( stepNumber == i++ ) move.goToXY( 155*MM, 25*MM );
          else if( stepNumber == i++ ) move.addConsigneRot( -90*DEG );
          else if( stepNumber == i++ ) {
            move.addConsigneTra( 500*MM);
            move.step();
            interval.waitIntervalEnding();
            
            tempTime = millis();
            
            while( !move.isStopped() && millis()-tempTime < 3000  ) {
              move.step();
              interval.waitIntervalEnding(); // Afin de conserver la régularité d'execution des actions (important car deplacement)
            }
            move.stop();            
          }
          /*
          // Portes
          else if( stepNumber == i++ ) {
            allowSonars = false;
            move.setSpeed( 2 );
            move.goToXY( 430*MM, -500*MM  );
          }
          else if( stepNumber == i++ ) move.goToXY( 430*MM, -700*MM );
          else if( stepNumber == i++ ) {
            move.setSpeed( 1 );
            move.goToXY( 430*MM, -1000*MM );
            move.step();
            interval.waitIntervalEnding();
            
            tempTime = millis();
            
            while( !move.isStopped() && millis()-tempTime < 1000  ) {
              move.step();
              interval.waitIntervalEnding(); // Afin de conserver la régularité d'execution des actions (important car deplacement)
            }
            move.stop();            
          }
          */
          
          // FIN (ne pas modifier)
          else {
            move.stop();
            move.stopMoteurs();
            run = false;
          }
          
          
      } // -----------------------------------------------------------------------------------------------------------------------------------------
      else if( CONFIG == CONFIG_34 ) { // ----------------------------------------------------------------------------------------------------------
      
          
          // Monticule (12345)
          if( stepNumber == i++ ) {
            allowSonars = false;
            move.setSpeed( 1.45 );
            move.goToXY( 400*MM, -55*MM );
          }
          else if( stepNumber == i++ ) {
            move.setSpeed( 0.8 );
            move.goToXY( 550*MM, -55*MM );
          }
          else if( stepNumber == i++ ) move.goToXY( 900*MM, 45*MM );
          else if( stepNumber == i++ ) {
            move.setSpeed( 1.45 );
            move.addConsigneTra( -250*MM );
          }
          
          // Coquillage 1
          else if( stepNumber == i++ ) {
            action.setAX12( "porte1", Action::AX12_OPEN );
            allowSonars = true;
          }
          else if( stepNumber == i++ ) move.goToXY( 1070*MM, 700*MM );
          else if( stepNumber == i++ ) action.setAX12( "porte1", Action::AX12_CLOSE );
          // Peche poisson 1
          else if( stepNumber == i++ ) move.goToXY( 570*MM, 615*MM );
          else if( stepNumber == i++ ) {
            move.setSpeed( 1.1 );
            move.goToXY( 570*MM, 730*MM );
          }
          else if( stepNumber == i++ ) {
            allowSonars = false;
            move.stop();
            action.setAX12( "porte1", Action::AX12_CLOSE );
          }
          else if( stepNumber == i++ ) {
            move.setSpeed( 1.3 );
            move.addConsigneTra( 500*MM);
            move.step();
            interval.waitIntervalEnding();
            
            tempTime = millis();
            
            while( !move.isStopped() && millis()-tempTime < 1750  ) {
              move.step();
              interval.waitIntervalEnding(); // Afin de conserver la régularité d'execution des actions (important car deplacement)
            }
            move.stop();            
          }
          else if( stepNumber == i++ ) {  
            action.setEA( true );
            while( action.getState() != Action::STATE_ARRET ){ // Tant que les actions ne sont pas validée et donc que les aimants ne sont pas allumés
              can.step();
              action.step();
            }
          }
          else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_DOWN );
          else if( stepNumber == i++ ) {
            move.setSpeed( 0.5 );
            move.addConsigneTra( -85*MM );
          }
//          else if( stepNumber == i++ ) {
//            move.stop();
//            delay( 1250 );
//          }
          else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_UP );
          else if( stepNumber == i++ ) {
            move.setSpeed( 1 );
            move.addConsigneTra( -100*MM );
          }
          
          // Poisson filet 1
          else if( stepNumber == i++ ) move.goToXY( 1060*MM, 695*MM );
          else if( stepNumber == i++ ) move.goToXY( 1060*MM, 830*MM );
          else if( stepNumber == i++ ) {  
            action.setEA( false );
            while( action.getState() != Action::STATE_ARRET ){
              can.step();
              action.step();
            }
          }
          else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_UP );
          else if( stepNumber == i++ ) move.addConsigneTra( -100*MM );
          
          // Peche poisson 2
          else if( stepNumber == i++ ) {
            move.setSpeed( 1.3 );
            move.goToXY( 640*MM, 695*MM );
          }
          else if( stepNumber == i++ ) {
            move.setSpeed( 1 );
            move.goToXY( 640*MM, 840*MM );
          }
          else if( stepNumber == i++ ) {
            move.addConsigneTra( 500*MM);
            move.step();
            interval.waitIntervalEnding();
            
            tempTime = millis();
            
            while( !move.isStopped() && millis()-tempTime < 2500  ) {
              move.step();
              interval.waitIntervalEnding(); // Afin de conserver la régularité d'execution des actions (important car deplacement)
            }
            move.stop();            
          }
          else if( stepNumber == i++ ) {  
            action.setEA( true );
            while( action.getState() != Action::STATE_ARRET ){
              can.step();
              action.step();
            }
          }
          else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_DOWN );
          else if( stepNumber == i++ ) {
            move.setSpeed( 0.5 );
            move.addConsigneTra( -85*MM );
          }
//          else if( stepNumber == i++ ) {
//            move.stop();
//            delay( 1250 );
//          }
          else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_UP );
          else if( stepNumber == i++ ) {
            move.setSpeed( 1 );
            move.addConsigneTra( -100*MM );
          }
          
          // Poisson filet 2
          else if( stepNumber == i++ ) move.goToXY( 1060*MM, 695*MM );
          else if( stepNumber == i++ ) move.goToXY( 1060*MM, 830*MM );
          //else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_DOWN );
          else if( stepNumber == i++ ) {  
            action.setEA( false );
            while( action.getState() != Action::STATE_ARRET ){
              can.step();
              action.step();
            }
          }
          else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_UP );
          else if( stepNumber == i++ ) move.addConsigneTra( -100*MM );
          
          // Peche poisson 3
          else if( stepNumber == i++ ) {
            move.setSpeed( 1.3 );
            move.goToXY( 600*MM, 695*MM );
          }
          else if( stepNumber == i++ ) {
            move.setSpeed( 1 );
            move.goToXY( 600*MM, 840*MM );
          }
          else if( stepNumber == i++ ) {
            move.addConsigneTra( 500*MM);
            move.step();
            interval.waitIntervalEnding();
            
            tempTime = millis();
            
            while( !move.isStopped() && millis()-tempTime < 2500  ) {
              move.step();
              interval.waitIntervalEnding(); // Afin de conserver la régularité d'execution des actions (important car deplacement)
            }
            move.stop();            
          }
          else if( stepNumber == i++ ) {  
            action.setEA( true );
            while( action.getState() != Action::STATE_ARRET ){
              can.step();
              action.step();
            }
          }
          else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_DOWN );
          else if( stepNumber == i++ ) {
            move.setSpeed( 0.5 );
            move.addConsigneTra( -85*MM );
          }
//          else if( stepNumber == i++ ) {
//            move.stop();
//            delay( 1250 );
//          }
          else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_UP );
          else if( stepNumber == i++ ) {
            move.setSpeed( 1 );
            move.addConsigneTra( -100*MM );
          }
          
          // Poisson filet 3
          else if( stepNumber == i++ ) move.goToXY( 1060*MM, 695*MM );
          else if( stepNumber == i++ ) move.goToXY( 1060*MM, 830*MM );
          //else if( stepNumber == i++ ) action.setAX12( "cannes", Action::AX12_DOWN );
          else if( stepNumber == i++ ) {  
            action.setEA( false );
            while( action.getState() != Action::STATE_ARRET ){
              can.step();
              action.step();
            }
          }
          else if( stepNumber == i++ ) {
            move.setSpeed( 1.6 );
            move.addConsigneTra( -100*MM );
            action.setAX12( "cannes", Action::AX12_STORE );
            allowSonars = true;
          }
          
          // Retour
          else if( stepNumber == i++ ) move.goToXY( 500*MM, 800*MM );
          else if( stepNumber == i++ ) move.goToXY( 155*MM, 645*MM );
          else if( stepNumber == i++ ) move.goToXY( 155*MM, 25*MM );
          else if( stepNumber == i++ ) move.addConsigneRot( -90*DEG );
          else if( stepNumber == i++ ) {
            move.addConsigneTra( 500*MM);
            move.step();
            interval.waitIntervalEnding();
            
            tempTime = millis();
            
            while( !move.isStopped() && millis()-tempTime < 3000  ) {
              move.step();
              interval.waitIntervalEnding(); // Afin de conserver la régularité d'execution des actions (important car deplacement)
            }
            move.stop();            
          }
          
         
          
          // FIN (ne pas modifier)
          else {
            move.stop();
            move.stopMoteurs();
            run = false;
          }
      
      
      } // -----------------------------------------------------------------------------------------------------------------------------------------
      
      // ---- ! PARCOURS ---------------------------------------------------------------------------------------------------------------------------
    }
    else if( move.getState() == Asservissement::STATE_TROUBLE ) {
      debugSerial.println( "TROUBLE Step : " + String( stepNumber ) );
      stepNumber -= 2;
      move.stop();
      move.takenTroubles();
    }
   
    debugSerial.println( "Gestion boucle" );
    if( move.getState() == Asservissement::STATE_ARRET && action.getState() != Action::STATE_ARRET ) {
      move.stopMoteurs();
      //delay( 800 );
    }
    
    can.step();
    
    if( !allowSonars || ( !action.receiveSonarClassic() && action.receiveSonarPWM() > 100 ) ) {
      debugSerial.println( "Sonar classic & PWM : OK" );
      move.step();
    }
    else{
      debugSerial.println( "Sonar classic | PWM : Obstacle" );
      move.stopMoteurs();
    }
    
    if( action.getState() != Action::STATE_ARRET ) action.step( true, false );
    
    //debugSerial.println( "Loop duration : " + String( 2000-interval.getIntervalEnding() ) + " microseconds (" + String( millis() ) + " || " + String( millis()-startTime ) + ")" );
    //if( debugSerial.buffStepAndIsFinished() ) serialEvent();
    interval.waitIntervalEnding();
  }
  
  move.stopMoteurs();
  
  
  
  // Attente des 90 secondes ------------------------------------------------------------------------------------------
  debugSerial.println( "Attends les 90 secondes" );
  while( millis() - startTime < 90*1000 );
  debugSerial.println( "90 secondes passées" );
  
  
  
  // Levé du parasol jusqu'à 95 secondes ------------------------------------------------------------------------------
  debugSerial.println( "Sort le parasol" );
  for( int i = 0; i < 2 || millis() - startTime < 95*1000; i++ ) {
    action.setAX12( "parasol1", Action::AX12_DEPLOY );
  }
  debugSerial.println( "95 secondes passées" );
  
  
  
  // Fin du programme
  debugSerial.println( "Fin du programme" );
  while( 1 ) {
    move.stopMoteurs();
  }
}







void serialEvent(){
  if( debugSerial.buffRead() == "STOP" ) {
    move.stop();
    run = false;
    stepNumber = -1;
  }
  else if( debugSerial.buffRead() == "FREEZE" ) {
    move.stop();
    run = false;
    stepNumber--;
  }
  else if( debugSerial.buffRead() == "START" ) run = true;
  
  else if( debugSerial.buffRead() == "ADVANCE" ) move.addConsigneTra( Codeurs::TICKS_BY_METER/2 );
  else if( debugSerial.buffRead().startsWith( "ADVANCE" ) ) move.addConsigneTra( debugSerial.buffRead().substring( 8 ).toInt()*Codeurs::TICKS_BY_MM );
  
  else if( debugSerial.buffRead() == "BACK" ) move.addConsigneTra( -Codeurs::TICKS_BY_METER/2 );
  else if( debugSerial.buffRead().startsWith( "BACK" ) ) move.addConsigneTra( -debugSerial.buffRead().substring( 5 ).toInt()*Codeurs::TICKS_BY_MM );
  
  else if( debugSerial.buffRead() == "TURNLEFT" ) move.addConsigneRot( -Codeurs::TICKS_BY_TURN/4 );
  else if( debugSerial.buffRead().startsWith( "TURNLEFT" ) ) move.addConsigneTra( debugSerial.buffRead().substring( 9 ).toInt()*Codeurs::TICKS_BY_DEG );
  
  else if( debugSerial.buffRead() == "TURNRIGHT" ) move.addConsigneRot( Codeurs::TICKS_BY_TURN/4 );
  else if( debugSerial.buffRead().startsWith( "TURNRIGHT" ) ) move.addConsigneTra( -debugSerial.buffRead().substring( 10 ).toInt()*Codeurs::TICKS_BY_DEG );
  
  else if( debugSerial.buffRead().startsWith( "GOTOXY" ) && debugSerial.buffRead().indexOf( ":" ) >=0 ) {
    int sepPos = debugSerial.buffRead().indexOf( ":" );
    
    move.goToXY( debugSerial.buffRead().substring( 7, sepPos ).toInt()*Codeurs::TICKS_BY_MM, debugSerial.buffRead().substring( sepPos+1 ).toInt()*Codeurs::TICKS_BY_MM );
  }
  
  else if( debugSerial.buffRead() == "GETPOS" ) {
    Position pos = move.getPos();
    
    debugSerial.println( "X: " + String( pos.getX() ) + "; Y: " + String( pos.getY() ) + "; O: " + String( pos.getDegO() ) );
  }
  
  else if( debugSerial.buffRead() == "DOWN" ) action.setAX12( "cannes", Action::AX12_DOWN );
  else if( debugSerial.buffRead() == "UP" ) action.setAX12( "cannes", Action::AX12_UP );
  else if( debugSerial.buffRead() == "STORE" ) action.setAX12( "cannes", Action::AX12_STORE );
  
  else if( debugSerial.buffRead() == "PING" ) debugSerial.println( "PONG" );

  else debugSerial.println( "NO_" + debugSerial.buffRead() );
}

