//----------------------------------------------------------------------//
//                                 EA_CAN                               //
//                                                    version 03.02.16  //
//                                             date 03/02/2016 - 10h00  //
//----------------------------------------------------------------------//
//  Permet de communiquer avec les electro-aimants sur le bus CAN.      //
//----------------------------------------------------------------------//
//                                                        Julien GODET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//----------------------------------------------------------------------//

#include "EA_CAN.h"

EA_CAN::EA_CAN() {
  // can.initCan0();
}

void EA_CAN::setEA(int ValEA) {
  /* for( int i = 0; i < 30 ; i++ ) */ can.sendCan0Frame( 0x006, ValEA );
}

int EA_CAN::receiveEA() {  
  int id = 0x007;
  
  if( can.getCan0Time( id ) == 0 ) return 65535; // Si le message n'a jamais été récupéré
  
  CAN_FRAME frame = can.readCan0( id );
  
  return frame.data.byte[0];
}
