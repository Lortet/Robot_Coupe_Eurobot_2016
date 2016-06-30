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

#ifndef __SONARCAN_H__
#define __SONARCAN_H__

#include "NewCAN.h"

class SONAR_CAN {
  public:
    SONAR_CAN();
  
    int receiveSonarPWM();
    int receiveSonarClassic();

  private:
    NewCAN can;
};

#endif
