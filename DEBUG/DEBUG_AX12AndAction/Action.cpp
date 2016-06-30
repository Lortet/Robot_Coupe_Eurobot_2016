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
SerialBuffer blueSerialAc( 0, '\n', 300, 25 );

Action::Action(){
  #ifdef HAS_AX12
    AX12Init();
  #endif

  state = Action::STATE_ACTION;
}

void Action::step(){
  bool error = false;
  
  #ifdef HAS_AX12
    error |= AX12Step();
  #endif

  if( !error ) state = Action::STATE_ARRET;
}

char Action::getState(){
  return state;
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
        Serial.println( "Set AX12 " + String( i ) + " : pos " + String( position ) );
      }
    }
  }
  
  void Action::AX12Init(){
    AX12Id = 1<<1 | 1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6; // Des AX12 aux adresses 1, 2, 3 et 4

    //AX12.enableTorque( 254, 1023 );
    setAX12( "cannes", Action::AX12_STORE ); //620
    setAX12( "porte1", Action::AX12_CLOSE ); //800
    setAX12( "parasol", Action::AX12_LEAN ); //0
  }
  bool Action::AX12Step(){
    bool error = false;
    
    for( unsigned char i = 0; i < 254; i++ ) {
      if( AX12Id & 1<<i ){
        blueSerialAc.println( "Has AX12 " + String( i ) );

        int realPos = AX12.receivePosition( i );
        
        blueSerialAc.println( "Position received AX12 " + String( i ) + " : " + String( realPos ) );
        
        int wishPos = AX12Pos[ i ];
        
        blueSerialAc.println( "Pos AX12 " + String( i ) + " = " + String( realPos ) + " VS " + String ( wishPos ) );
        if( realPos != 65535 && abs( realPos - wishPos ) > 70 ){
          setAX12( i, AX12Pos[ i ] );
          error = true;
          delay( 1000 );
        }
        
      }
    }

    return error;
  }
#endif

