//----------------------------------------------------------------------//
//                               AX12_CAN                               //
//                                                    version 16.04.26  //
//                                             date 26/04/2016 - 21h10  //
//----------------------------------------------------------------------//
//  Permet de contrôler les AX12 via le bus CAN                         //
//----------------------------------------------------------------------//
//                                                        Julien GODET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//----------------------------------------------------------------------//

#ifndef __AX12CAN_H__
#define __AX12CAN_H__

#include "NewCAN.h"

class AX12_CAN {
  public:
    //Initialisation
    AX12_CAN();
      
    //Emission
    void setPosition( int msg, int idTransmit, int positionTransmit, int vitesseTransmit, int coupleTransmit);
    void setPosition( int idTransmit, int positionTransmit, int vitesseTransmit, int coupleTransmit);
    void setPosition( int idTransmit, int positionTransmit, int vitesseTransmit);
    void setPosition( int idTransmit, int positionTransmit);
      
    void enableTorque( int idTransmit, int activeCouple);
	
    //Reception
    int receive(int mes1, int mes2, int id);
    int receivePosition(int id);
    int receiveVitesse(int id);
    int receiveCouple(int id);
    
  private:
    NewCAN can;
};

#endif

