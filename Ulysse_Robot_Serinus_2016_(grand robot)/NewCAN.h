//----------------------------------------------------------------------//
//                                NewCAN                                //
//                                                    version 16.05.04  //
//                                             date 04/05/2016 - 17h45  //
//----------------------------------------------------------------------//
//  Surcouche pour la communication CAN                                 //
//----------------------------------------------------------------------//
//                                      Julien GODET & Valentin LORTET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//----------------------------------------------------------------------//

#ifndef __NEWCAN_H__
#define __NEWCAN_H__

#include "due_can.h" // Utulisation de Can0 et Can1

#define MAX_CAN_ID 1024

class NewCAN {
  private:
    static bool isInitCan0var;
    static bool isInitCan1var;
    
    static CAN_FRAME can0Data[MAX_CAN_ID];
    static long can0Time[MAX_CAN_ID];
    
    static CAN_FRAME can1Data[MAX_CAN_ID];
    static long can1Time[MAX_CAN_ID];
	
  public:
    void step();
    
    void initCan0();
    void initCan1();
    
    bool isInitCan0();
    bool isInitCan1();
    
    CAN_FRAME readCan0( int adr );
//    BytesUnion readCan0Val( int adr );
    byte readCan0Byte( int adr, char byte );
    long readCan0Low( int adr );
    long readCan0High( int adr );
    long getCan0Time( int adr );
    void sendCan0Frame( CAN_FRAME frame );
    void sendCan0Frame( int id, int length, byte seven, byte six, byte five, byte four, byte three, byte two, byte one, byte zero );
    void sendCan0Frame( int id, byte zero );
    void sendCan0Frame( int id, byte one, byte zero );
    void sendCan0Frame( int id, byte two, byte one, byte zero );
    void sendCan0Frame( int id, byte three, byte two, byte one, byte zero );
    void sendCan0Frame( int id, byte four, byte three, byte two, byte one, byte zero );
    void sendCan0Frame( int id, byte five, byte four, byte three, byte two, byte one, byte zero );
    void sendCan0Frame( int id, byte six, byte five, byte four, byte three, byte two, byte one, byte zero );
    void sendCan0Frame( int id, byte seven, byte six, byte five, byte four, byte three, byte two, byte one, byte zero );
    
    CAN_FRAME readCan1( int adr );
//    BytesUnion readCan1Val( int adr );
    byte readCan1Byte( int adr, char byte );
    long readCan1Low( int adr );
    long readCan1High( int adr );
    long getCan1Time( int adr );
    void sendCan1Frame( CAN_FRAME frame );
    void sendCan1Frame( int id, int length, byte seven, byte six, byte five, byte four, byte three, byte two, byte one, byte zero );
    void sendCan1Frame( int id, byte zero );
    void sendCan1Frame( int id, byte one, byte zero );
    void sendCan1Frame( int id, byte two, byte one, byte zero );
    void sendCan1Frame( int id, byte three, byte two, byte one, byte zero );
    void sendCan1Frame( int id, byte four, byte three, byte two, byte one, byte zero );
    void sendCan1Frame( int id, byte five, byte four, byte three, byte two, byte one, byte zero );
    void sendCan1Frame( int id, byte six, byte five, byte four, byte three, byte two, byte one, byte zero );
    void sendCan1Frame( int id, byte seven, byte six, byte five, byte four, byte three, byte two, byte one, byte zero );
};

#endif
