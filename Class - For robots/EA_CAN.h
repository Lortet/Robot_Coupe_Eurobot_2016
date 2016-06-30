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

#ifndef __EACAN_H__
#define __EACAN_H__

#include "NewCAN.h"

class EA_CAN {
  public:
    EA_CAN();
  
    void setEA( int ValEA );
    int receiveEA();

  private:
    NewCAN can;
};

#endif
