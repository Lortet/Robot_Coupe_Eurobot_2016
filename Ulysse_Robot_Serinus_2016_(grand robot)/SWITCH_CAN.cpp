//----------------------------------------------------------------------//
//                              AX_12CAN.cpp                            //
//                                                    version 03.02.16  //
//                                             date 03/02/2016 - 10h00  //
//----------------------------------------------------------------------//
//  Permet de communiquer sur le bus CAN                                //
//----------------------------------------------------------------------//
//                                                        Julien GODET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//----------------------------------------------------------------------//

#include "SWITCH_CAN.h"

SWITCH_CAN::SWITCH_CAN() {
  //can.initCan0();
}

int SWITCH_CAN::receiveSwitch( int id ) {
  if( can.getCan0Time( id ) == 0 ) return 65535; // Si le message n'a jamais été récupéré
  
  CAN_FRAME frame = can.readCan0( id );
  
  return (( ( frame.data.byte[0] << 8 | frame.data.byte[1] ) < 500 )? 0 : 1 );
}

