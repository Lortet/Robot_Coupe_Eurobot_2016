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

#include "EEPROMLong.h"

void EEPROMLong::write( int address, long value ) {
	byte four = (value & 0xFF);
	byte three = ((value >> 8) & 0xFF);
	byte two = ((value >> 16) & 0xFF);
	byte one = ((value >> 24) & 0xFF);

	EEPROM.write(address, four);
	EEPROM.write(address + 1, three);
	EEPROM.write(address + 2, two);
	EEPROM.write(address + 3, one);
}

long EEPROMLong::read( int address ) {
	long four = EEPROM.read(address);
	long three = EEPROM.read(address + 1);
	long two = EEPROM.read(address + 2);
	long one = EEPROM.read(address + 3);
	
	return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

