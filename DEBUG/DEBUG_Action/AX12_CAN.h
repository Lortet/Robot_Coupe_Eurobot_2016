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

class AX12_CAN {
  private:
	  //Test Reception
	  int CANReception();
	
  public:
    //Initialisation
    AX12_CAN();
      
	  //Emission
    void setPosition( int msg, int idTransmit, int positionTransmit, int vitesseTransmit, int coupleTransmit);
    void setPosition( int idTransmit, int positionTransmit, int vitesseTransmit, int coupleTransmit);
    void setPosition( int idTransmit, int positionTransmit, int vitesseTransmit);
    void setPosition( int idTransmit, int positionTransmit);

    /* Retro-compatibilité */
    void AX12_set_position3( int idTransmit, int positionTransmit, int vitesseTransmit, int coupleTransmit); // Remplacé par setPosition( params )
    void AX12_set_position2( int idTransmit, int positionTransmit, int vitesseTransmit);                     // Remplacé par setPosition( params )
    void AX12_set_position1( int idTransmit, int positionTransmit);                                          // Remplacé par setPosition( params )
    /* !Retro-compatibilité */
      
    void enableTorque( int idTransmit, int activeCouple);
	
    //Reception
    int receive(int mes1, int mes2, int id);
    int receivePosition(int id);
    int receiveVitesse(int id);
    int receiveCouple(int id);
    
    /* Retro-compatibilité */
    int Receive(int mes1, int mes2, int id);
    int Receive_position(int id);
    int Receive_vitesse(int id);
    int Receive_couple(int id);
    /* !Retro-compatibilité */
};

#endif
