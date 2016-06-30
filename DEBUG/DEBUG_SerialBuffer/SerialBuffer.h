//----------------------------------------------------------------------//
//                             SERIALBUFFER                             //
//                                                    version 16.04.25  //
//                                             date 25/04/2016 - 22h59  //
//----------------------------------------------------------------------//
//  Permet de gérer simplement les communications via un port série     //
//  ainsi que l'envoi et la récéption de commandes                      //
//----------------------------------------------------------------------//
//                                                     Valentin LORTET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//----------------------------------------------------------------------//

#ifndef SERIALBUFFER_H
#define SERIALBUFFER_H

#include <Arduino.h>

class SerialBuffer {
  public:
    // Init (set configuration)
    SerialBuffer( int serialPort, char endChar, int maxTime, int maxChar );

    // Set data
    void buffStep();
    boolean buffStepAndIsCompleted();
    boolean buffStepAndIsAvorted();
    boolean buffStepAndIsFinished();

    // Get data
    String buffRead();
    int buffSize();
    
    void buffWait( String string );

    // Get state
    boolean buffIsCompleted();
    boolean buffIsAvorted();
    boolean buffIsFinished();

    // Serial
    void begin( long bauds );
    boolean available();
    char read();
    void print( String string );
    void println( String string );

    // Reset
    void buffReset();
  
  private:
    // Data
    unsigned long bufferDate;
    String buffer;

    // State
    boolean completed;
    boolean avorted;

    // Configuration
    int serialPort;
    char endChar;
    int maxTime;
    int maxChar;
};

#endif

