//----------------------------------------------------------------------//
//                               Interval                               //
//                                                    version 16.04.19  //
//                                             date 19/04/2016 - 21h40  //
//----------------------------------------------------------------------//
//  Permet d'effectuer des actions à intervalle de temps régulier.      //
//----------------------------------------------------------------------//
//                                                     Valentin LORTET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//----------------------------------------------------------------------//

#include "Interval.h"

Interval::Interval( boolean m, long delay ) {  
  micro = m;
  state = 0;
  minTime = 0;
  maxTime = 0;
  
  setInterval( delay );
}

void Interval::setInterval( long delay ) {
  intervalTime = delay;
}

void Interval::start() {
  state = 1;
  
  lastIntervalTime = getTime();
}

void Interval::stop() {
  state = 0;
}

void Interval::waitIntervalEnding() {
  if( !state ) return;
  
  unsigned long time = getTime();
  
  if( ( time - lastIntervalTime ) < minTime ) minTime = time - lastIntervalTime;
  else if( ( time - lastIntervalTime ) > maxTime ) maxTime = time - lastIntervalTime;
  
  if( state && ( getTime() - lastIntervalTime ) < intervalTime ){
    if( micro ) delayMicroseconds( intervalTime - ( micros() - lastIntervalTime ) );
    else delay( intervalTime - ( millis() - lastIntervalTime ) );
  }
  
  lastIntervalTime = getTime();
}

char Interval::getState() {
  return state;
}

boolean Interval::isMicro() {
  return micro;
}
unsigned long Interval::getTime() {
  return (( micro )? micros() : millis() );
}

unsigned long Interval::getIntervalEnding() {
  if( ( getTime() - lastIntervalTime ) < intervalTime ){
    return intervalTime - ( getTime() - lastIntervalTime );
  }
  else return 0;
}

unsigned long Interval::getMinTime() {
  return minTime;
}

unsigned long Interval::getMaxTime() {
  return maxTime;
}


