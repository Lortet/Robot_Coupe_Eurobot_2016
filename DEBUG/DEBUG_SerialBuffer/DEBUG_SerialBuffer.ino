#include <Arduino.h>
#include "SerialBuffer.h"

SerialBuffer termSerial( 0, '\n', 5000, 16 );

void setup() {
  termSerial.begin( 115200 );
}

void loop() {
  serialBufferEvent();
}

void serialBufferEvent() {
  if( termSerial.buffStepAndIsCompleted() ) termSerialEvent();
}

void termSerialEvent() {
  if( termSerial.buffRead() == "START" || termSerial.buffRead() == "STOP" ) termSerial.println( "OK_" + termSerial.buffRead() );
  else termSerial.println( "NO_" + termSerial.buffRead() );
}

