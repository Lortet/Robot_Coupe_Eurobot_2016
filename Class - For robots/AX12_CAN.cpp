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

#include "AX12_CAN.h"

AX12_CAN::AX12_CAN() {
  //can.initCan0();
}

void AX12_CAN::setPosition( int idMsg, int idTransmit, int positionTransmit, int vitesseTransmit, int coupleTransmit ) {
  int msgLength;
  if( vitesseTransmit < 0 ) msgLength = 5;
  else if( coupleTransmit < 0 ) msgLength = 6;
  else msgLength = 7;
  
  for( int i = 0; i < 5; i++ ) {
    can.sendCan0Frame( idMsg, msgLength, 0, coupleTransmit, coupleTransmit >> 8, vitesseTransmit, vitesseTransmit >> 8, positionTransmit, positionTransmit  >> 8, idTransmit );
    delay( 20 );
  }
}
void AX12_CAN::setPosition( int idTransmit, int positionTransmit, int vitesseTransmit, int coupleTransmit ) {
  if((idTransmit >= 1) && (idTransmit <= 4)) {
    idTransmit = 201;
  }
  setPosition( 0x100, idTransmit, positionTransmit, vitesseTransmit, coupleTransmit );
}
void AX12_CAN::setPosition( int idTransmit, int positionTransmit, int vitesseTransmit) {
  setPosition( 0x101, idTransmit, positionTransmit, vitesseTransmit, -1 );
}
void AX12_CAN::setPosition( int idTransmit, int positionTransmit) {
  setPosition( 0x102, idTransmit, positionTransmit, -1, -1 );
}

void AX12_CAN::enableTorque( int idTransmit, int activeCouple) {
  /*
  CAN_FRAME enableTorque;
  enableTorque.id = 0x109;
  enableTorque.length = 2;
  enableTorque.data.byte[0] = idTransmit;
  enableTorque.data.byte[1] = activeCouple;
  Can0.sendFrame(enableTorque);
  */
  
  can.sendCan0Frame( 0x109, activeCouple, idTransmit );
}

int AX12_CAN::receive(int mes1, int mes2, int id) {
  /*
  int value = 65535;
  int nb_buf;
  CAN_FRAME incoming; 
  
  if((id==0) || (id == 4)) nb_buf = 0;
  else if((id==1) || (id == 5)) nb_buf = 2;
  else if((id==2) || (id == 6)) nb_buf = 4;
  else if((id==3) || (id == 7)) nb_buf = 6;
  
  if((id >= 0) && (id <= 3)) {
    do {
      while( !Can0.available() ); //attente reception
      Can0.read( incoming );
    } while( incoming.id != mes1 );
  }
  else if((id>=4) && (id <= 7)) {
    do {
      while( !Can0.available() ); //attente reception
      Can0.read( incoming );
    } while( incoming.id != mes2 );
  }
  
  value = incoming.data.byte[nb_buf] << 8 | incoming.data.byte[nb_buf+1];
  
  return value;
  */
  
  int nb_buf = 0;
  CAN_FRAME frame; 
  
  if( (id==0) || (id == 4) ) nb_buf = 0;
  else if( (id==1) || (id == 5) ) nb_buf = 2;
  else if( (id==2) || (id == 6) ) nb_buf = 4;
  else if( (id==3) || (id == 7) ) nb_buf = 6;
  else return 65533;
  
  if( (id >= 0) && (id <= 3) ) frame = can.readCan0( mes1 );
  else if( (id >= 4) && (id <= 7) ) frame = can.readCan0( mes2 );
  else return 65534;
  
  return frame.data.byte[nb_buf] << 8 | frame.data.byte[nb_buf+1];
}

int AX12_CAN::receivePosition(int id) {
  return receive( 0x103, 0x104, id );
}
int AX12_CAN::receiveVitesse(int id) {
  return receive( 0x105, 0x106, id );
}
int AX12_CAN::receiveCouple(int id) {
  return receive( 0x107, 0x108, id );
}

