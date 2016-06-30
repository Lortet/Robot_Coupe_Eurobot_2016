//----------------------------------------------------------------------//
//                              AX12_CAN.cpp                            //
//                                                    version 03.02.16  //
//                                             date 03/02/2016 - 10h00  //
//----------------------------------------------------------------------//
//  Permet de communiquer sur le bus CAN                                //
//----------------------------------------------------------------------//
//                                                        Julien GODET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//----------------------------------------------------------------------//

#ifndef __SWITCHCAN_H__
#define __SWITCHCAN_H__

#include "NewCAN.h"

class SWITCH_CAN {
  public:
    SWITCH_CAN();
    
    int receiveSwitch( int id );
    
  private:
    NewCAN can;
};

#endif
