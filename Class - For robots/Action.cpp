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

#include "Action.h"
#include "SerialBuffer.h"
SerialBuffer debugSerialAc( 0, '\n', 300, 25 );

Action::Action(){  
  #ifdef HAS_AX12
    AX12Init();
  #endif
  
  #ifdef HAS_EA
    EAInit();
  #endif

  state = Action::STATE_ACTION;
}

void Action::step(){
  step( true, true );
}

void Action::step( bool AX12, bool EA ){
  bool finished = true;
  
  #ifdef HAS_AX12
    if( AX12 ) finished &= AX12Step();
  #endif
  
  #ifdef HAS_EA
    if( EA ) finished &= EAStep();
  #endif

  if( finished ) state = Action::STATE_ARRET;
}

char Action::getState(){
  return state;
}

int Action::receiveStart() {  
  int id = 0x008;
  
  if( can.getCan0Time( id ) == 0 ) return 65535; // Si le message n'a jamais été récupéré
  
  return can.readCan0( id ).data.byte[0];
}
void Action::validStart( bool val ) {
  /* for( int i = 0; i < 256; i++ ) */ can.sendCan0Frame( 0x009, val );
}

#ifdef HAS_AX12
  void Action::setAX12( unsigned char id, int position ){
    AX12.setPosition( id, position, 145, 1023 );

    state = Action::STATE_ACTION;

    AX12Pos[ id ] = position;
  }
  void Action::setAX12( String group, int position ){
    if( group == "all" ) { // Raccourci 200
      for( unsigned char i = 0; i < 200; i++ ) {
        if( AX12Id & 1<<i ) AX12Pos[ i ] = position;
      }
      setAX12( 200, position );
    }
    
    else if( group == "cannes" ) { // Raccourci 201
      AX12Pos[ 1 ] = position;
      AX12Pos[ 2 ] = position;
      AX12Pos[ 3 ] = position;
      AX12Pos[ 4 ] = position;
      setAX12( 201, position );
    }
    else if( group == "canne1" ) setAX12( 1, position );
    else if( group == "canne2" ) setAX12( 2, position );
    else if( group == "canne3" ) setAX12( 3, position );
    else if( group == "canne4" ) setAX12( 4, position );
    
    else if( group == "portes" ) { // Raccourci 202
      AX12Pos[ 5 ] = position;
      setAX12( 202, position );
    }
    else if( group == "porte1" ) setAX12( 5, position );
    
    else if( group == "parasols" ) { // Raccourci 203
      AX12Pos[ 6 ] = position;
      setAX12( 203, position );
    }
    else if( group == "parasol1" ) setAX12( 6, position );
    
  }
  void Action::setAllAX12( int position ){
    for( unsigned char i = 0; i < 200; i++ ) {
      if( AX12Id & 1<<i ) {
        setAX12( i, position );
      }
    }
  }
  
  void Action::AX12Init(){
    AX12Id = 1<<1 | 1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6; // Des AX12 aux adresses 1, 2, 3 et 4

    //AX12.enableTorque( 254, 1023 );
    setAX12( "cannes", Action::AX12_STORE );
    setAX12( "porte1", Action::AX12_CLOSE );
    setAX12( "parasol1", Action::AX12_LEAN );
  }
  
  bool Action::AX12Step(){
    bool finished = false;
    
    bool exitFor = false;
    for( unsigned char i = lastAX12IdVerif+1; i < 8 && !exitFor; i++ ) {
      if( AX12Id & 1<<i ){

        debugSerialAc.println( "AX12 n" + String( i ) + " : Ask position" );
        
        int realPos = AX12.receivePosition( i );
        int wishPos = AX12Pos[ i ];
        
        debugSerialAc.println( "AX12 n" + String( i ) + " : Position received = " + String( realPos ) + " (whish pos = " + String( wishPos ) + ")" );
        
        if( realPos == 65535 || abs( realPos - wishPos ) > 70 ){
          setAX12( i, AX12Pos[ i ] );
          if( realPos != 65535 ) tempAX12Finished = false;
        }
        
        lastAX12IdVerif = i; // On se souvient du dernier id verifié
        exitFor = true;      // On quitte la boucle
      }
      else debugSerialAc.println( "No AX12 " + String( i ) );
      
      if( i == 8-1 ){
        debugSerialAc.println( "Finished forloop" );
        if( tempAX12Finished ) finished = true;
        tempAX12Finished = true;
        lastAX12IdVerif = -1;
      }
    }
    
    debugSerialAc.println( "End forloop" );

    return finished;
  }
#endif

#ifdef HAS_EA
  int Action::receiveEA() {
    return EA.receiveEA();
  }
  void Action::setEA( int state ) {
    EA.setEA( state );
    
    state = Action::STATE_ACTION;
    
    EAState == state;
  }
  void Action::EAInit(){
    EA.setEA( EA_OFF );
  }
  bool Action::EAStep(){
    bool finished = false;
    
    int EArec = EA.receiveEA();
    
    
    debugSerialAc.println( "EA State = " + String( EArec ) );
    
    if( EArec != EAState ) {
      debugSerialAc.println( "EA Mauvais" );
      EA.setEA( EAState );
    }
    else{
      debugSerialAc.println( "EA Bon" );
      finished = true;
    }

    return finished;
  }
#endif

#ifdef HAS_SWITCH
  int Action::receiveSwitch( int id ) {
    return SWITCH.receiveSwitch( id );
  }
#endif

#ifdef HAS_SONAR
  int Action::receiveSonarPWM() {
    return SONAR.receiveSonarPWM();
  }
  int Action::receiveSonarClassic() {
    return SONAR.receiveSonarClassic();
  }
#endif

