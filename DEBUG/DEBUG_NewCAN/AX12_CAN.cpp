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

#include "due_can.h"
#include "AX12_CAN.h"

AX12_CAN::AX12_CAN() {
  Can0.begin(CAN_BPS_100K, 5); // Initialize CAN0 and CAN1, baudrate is 100kb
  Can0.watchFor();             //autorise tout le trafic en entree
}

void AX12_CAN::setPosition( int msg, int idTransmit, int positionTransmit, int vitesseTransmit, int coupleTransmit ) {
  CAN_FRAME frame;
  frame.id = msg;

  if( vitesseTransmit < 0 ) frame.length = 5;
  else if( coupleTransmit < 0 ) frame.length = 6;
  else frame.length = 7;
  
  frame.data.byte[0] = idTransmit;
  frame.data.byte[1] = positionTransmit  >> 8;
  frame.data.byte[2] = positionTransmit & 0x00FF;
  
  if( vitesseTransmit >= 0 ){
    frame.data.byte[3] = vitesseTransmit >> 8;
    frame.data.byte[4] = vitesseTransmit & 0x00FF;

    if( coupleTransmit >= 0 ){
      frame.data.byte[5] = coupleTransmit >> 8;
      frame.data.byte[6] = coupleTransmit & 0x00FF;
    }
  }
  
  Can0.sendFrame(frame);
}
void AX12_CAN::setPosition( int idTransmit, int positionTransmit, int vitesseTransmit, int coupleTransmit ) {
  setPosition( 0x100, idTransmit, positionTransmit, vitesseTransmit, coupleTransmit );
}
void AX12_CAN::setPosition( int idTransmit, int positionTransmit, int vitesseTransmit) {
  setPosition( 0x101, idTransmit, positionTransmit, vitesseTransmit, -1 );
}
void AX12_CAN::setPosition( int idTransmit, int positionTransmit) {
  setPosition( 0x102, idTransmit, positionTransmit, -1, -1 );
}

/* Retro-compatibilité */
void AX12_CAN::AX12_set_position3( int idTransmit, int positionTransmit, int vitesseTransmit, int coupleTransmit ) {
  setPosition( idTransmit, positionTransmit, vitesseTransmit, coupleTransmit );
}
void AX12_CAN::AX12_set_position2( int idTransmit, int positionTransmit, int vitesseTransmit) {
  setPosition( idTransmit, positionTransmit, vitesseTransmit );
}
void AX12_CAN::AX12_set_position1( int idTransmit, int positionTransmit) {
  setPosition( idTransmit, positionTransmit );
}
/* !Retro-compatibilité */

void AX12_CAN::enableTorque( int idTransmit, int activeCouple) {
  CAN_FRAME enableTorque;
  enableTorque.id = 0x109;
  enableTorque.length = 2;
  enableTorque.data.byte[0] = idTransmit;
  enableTorque.data.byte[1] = activeCouple;
  Can0.sendFrame(enableTorque);
  
  // can.sendCan0Frame( 0x109, activeCouple, idTransmit );
}

int AX12_CAN::CANReception() {
  CAN_FRAME incoming;
  while ( !Can0.available() ); //attente r�cpetion
  Can0.read(incoming);
  //Serial.println(Can0.get_status(),HEX);
  Serial.print("ID =");
  Serial.print(incoming.id,HEX);
  Serial.print("  - High =");
  Serial.print(incoming.data.high,HEX);
  Serial.print(" - Low =");
  Serial.println(incoming.data.low,HEX);
  int MessageR =  incoming.data.high << 8 + incoming.data.low;
  return MessageR;
}

int AX12_CAN::receive(int mes1, int mes2, int id) {
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

/* Retro-compatibilité */
int AX12_CAN::Receive_position(int id) {
  return receivePosition( id );
}
int AX12_CAN::Receive_vitesse(int id) {
  return receiveVitesse( id );
}
int AX12_CAN::Receive_couple(int id) {
  return receiveCouple( id );
}
/* !Retro-compatibilité */
