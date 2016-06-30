//----------------------------------------------------------------------//
//                              EEPROMLong                              //
//                                                    version 16.04.19  //
//                                             date 19/04/2016 - 21h09  //
//----------------------------------------------------------------------//
//  Permet de manipuler l'EEPROM avec des types long.                   //
//----------------------------------------------------------------------//
//                                                     Valentin LORTET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//   Adapté de : http://playground.arduino.cc/Code/EEPROMReadWriteLong  //
//----------------------------------------------------------------------//

#ifndef __EEPROMLONG_H__                          // Si la constante n'est pas définie
#define __EEPROMLONG_H__                          // On la définie de manière à ce que le fichier ne soit plus inclus

#include <Arduino.h>
#include <EEPROM.h> 

class EEPROMLong{
  
  public:
    static void write( int address, long value ); // Ecrit 4 octets dans la mémoire
    static long read( int address );              // Lit 4 octets de la mémoire
};

#endif
