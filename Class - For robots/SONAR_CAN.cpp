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

#include "SONAR_CAN.h"

SONAR_CAN::SONAR_CAN() {
  // can.initCan0();
}

int SONAR_CAN::receiveSonarPWM() {
  /*
  CAN_FRAME SonarPWM;
  int PosSonar = 65535;
  int nb_buf=0;  
  if (Can0.available() == 0) {
    Can0.read(SonarPWM);
    if (SonarPWM.id == 0x203) {
      PosSonar = SonarPWM.data.byte[nb_buf] << 8 | SonarPWM.data.byte[nb_buf+1];
    }
  }
  return PosSonar;
  */
  
  int id = 0x003;
  
  if( can.getCan0Time( id ) == 0 ) return 65535; // Si le message n'a jamais été récupéré
  
  CAN_FRAME frame = can.readCan0( id );
  
  //return (( ( frame.data.byte[0] << 8 | frame.data.byte[1] ) < 500 )? 0 : 1 );
  return frame.data.byte[0] << 8 | frame.data.byte[1];
}

int SONAR_CAN::receiveSonarClassic() {
  /*
  CAN_FRAME SonarClassic;
  int SonarC = 65535; 
  if (Can0.available() == 0) {
    Can0.read(SonarClassic);
    if (SonarClassic.id != 0x204) {
      SonarC = SonarClassic.data.byte[0];
    }
  }
  return SonarC;
  */
  
  int id = 0x004;
  
  if( can.getCan0Time( id ) == 0 ) return 65535; // Si le message n'a jamais été récupéré
  
  CAN_FRAME frame = can.readCan0( id );
  
  return frame.data.byte[0];
}
