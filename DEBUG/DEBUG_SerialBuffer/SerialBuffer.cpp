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

#include "SerialBuffer.h"

SerialBuffer::SerialBuffer( int serialPort, char endChar, int maxTime, int maxChar ){
  this->serialPort = serialPort;
  
  this->endChar = endChar;
  this->maxTime = maxTime;
  this->maxChar = maxChar;
  
  this->buffReset();
}

void SerialBuffer::buffStep(){
  if( buffIsFinished() ) buffReset();
    
  if( buffSize() > 0 && maxTime != 0 && millis() > bufferDate + maxTime ) {
    avorted = true;
    return;
  }
  
  while( available() && !buffIsFinished() ){
    if( buffSize() == 0 ) bufferDate = millis();
    
    if( ( maxTime != 0 && millis() > bufferDate + maxTime ) || ( maxChar != 0 && buffSize() >= maxChar ) ) {
      avorted = true;
      return;
    }
    
    char c = read();
    
    if( c == endChar && buffSize() > 0 ) completed = true;
    else if( c != endChar ) buffer += c;
  }
}
boolean SerialBuffer::buffStepAndIsCompleted() {
  buffStep();
  
  return buffIsCompleted();
}
boolean SerialBuffer::buffStepAndIsAvorted() {
  buffStep();
  
  return buffIsAvorted();
}
boolean SerialBuffer::buffStepAndIsFinished() {
  buffStep();
  
  return buffIsFinished();
}

boolean SerialBuffer::buffIsCompleted() {
  return completed;
}
boolean SerialBuffer::buffIsAvorted() {
  return avorted;
}
boolean SerialBuffer::buffIsFinished() {
  return ( buffIsCompleted() || buffIsAvorted() );
}

String SerialBuffer::buffRead() {
  return buffer;
}
int SerialBuffer::buffSize() {
    return buffRead().length();
}

void SerialBuffer::buffWait( String string ) {
  while( !buffStepAndIsFinished() || buffRead() != "START" );
}

void SerialBuffer::begin( long bauds ){
  if( serialPort == 0 ) Serial.begin( bauds );
  
  //#if defined( HAVE_HWSERIAL3 )
    else if( serialPort == 1 ) Serial1.begin( bauds );
    else if( serialPort == 2 ) Serial2.begin( bauds );
    else if( serialPort == 3 ) Serial3.begin( bauds );
  //#endif
}
boolean SerialBuffer::available(){
  if( serialPort == 0 ) return Serial.available();
  
  //#if defined( HAVE_HWSERIAL3 )
    if( serialPort == 1 ) return Serial1.available();
    if( serialPort == 2 ) return Serial2.available();
    if( serialPort == 3 ) return Serial3.available();
  //#endif
  
  return false;
}
char SerialBuffer::read(){
  if( serialPort == 0 ) return Serial.read();
  
  //#if defined( HAVE_HWSERIAL3 )
    if( serialPort == 1 ) return Serial1.read();
    if( serialPort == 2 ) return Serial2.read();
    if( serialPort == 3 ) return Serial3.read();
  //#endif
  
  return ' ';
}
void SerialBuffer::print( String string ){  
  if( serialPort == 0 ) Serial.print( string );
  
  //#if defined( HAVE_HWSERIAL3 )
    else if( serialPort == 1 ) Serial1.print( string );
    else if( serialPort == 2 ) Serial2.print( string );
    else if( serialPort == 3 ) Serial3.print( string );
  //#endif
}
void SerialBuffer::println( String string ){
  if( serialPort == 0 ) Serial.print( string + endChar );
  else if( serialPort == 1 ) Serial1.print( string + endChar );
  else if( serialPort == 2 ) Serial2.print( string + endChar );
  else if( serialPort == 3 ) Serial3.print( string + endChar );
}

void SerialBuffer::buffReset() {
  bufferDate = 0;
  buffer = "";
  completed = false;
  avorted = false;
}

