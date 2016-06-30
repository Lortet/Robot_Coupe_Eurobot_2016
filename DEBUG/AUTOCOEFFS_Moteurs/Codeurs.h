//----------------------------------------------------------------------//
//                                CODEURS                               //
//                                                    version 16.04.29  //
//                                             date 29/04/2016 - 16h07  //
//----------------------------------------------------------------------//
//  Permet de lire la valeur des codeurs du robot.                      //
//----------------------------------------------------------------------//
//                                                     Valentin LORTET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//        Adapté des travaux de Kevin LE MOGUEN et Thibault d'ARTIGUES  //
//----------------------------------------------------------------------//

#ifndef __CODEURS_H__                                   // Si la constante n'est pas définie
#define __CODEURS_H__                                   // On la définit de manière à ce que le fichier ne soit plus inclus

#include "Configuration.h"
#include <Arduino.h>

#define pin uint8_t

class Codeurs{
  
  public:
    Codeurs();
    
    void getTicks( long *leftT,long *rightT );          // Retourne la valeur des codeurs [Valeurs de retour : (4 octets) -2,147,483,648 (-2^32) à 2,147,483,647 (2^32 - 1)]
    void update();                                      // Mets à jour la valeur des codeurs
	void updateAndGetTicks( long *leftT,long *rightT ); // Retourne la valeur des codeurs [Valeurs de retour : (4 octets) -2,147,483,648 (-2^32) à 2,147,483,647 (2^32 - 1)]
	
    #if ROBOT == Ulysse
      static const long TICKS_BY_TURN = 89226;
      static const long TICKS_BY_METER = 215529;
    #elif ROBOT == Nono
      static const long TICKS_BY_TURN = 15769;
      static const long TICKS_BY_METER = 69129;
    #endif
    
    static const long TICKS_BY_DEG = TICKS_BY_TURN/360;
    static const long TICKS_BY_MM = TICKS_BY_METER/1000;
    
  private:
    long leftTicks;
    long rightTicks;
    
    unsigned char readCurrentByte();                    // Lit un octet du registre [Valeur de retour : (1 octet) 0 à 255 (2^8 - 1)]
    unsigned int readCurrentRegister();                 // Lit un des registres [Valeur de retour : (4 octets) 0 à 4,294,967,295 (2^32 - 1)]
    
    void resetTicks();                                  // Mets à jour la valeur des codeurs
    
    static const pin OUTEN = 43;                        // Permet la lecture des registres
    
    static const pin SELREG = 41;                       // Selection du registre (LOW = Left, HIGH = Right)
    
    static const pin SELBYTE1 = 49;                     // Selection 1 de l'octet du registre courant
    static const pin SELBYTE2 = 47;                     // Selection 2 de l'octet du registre courant
    
    static const pin BIT1 = 37;                         // Bit 1 de l'octet
    static const pin BIT2 = 35;                         // Bit 2 de l'octet
    static const pin BIT3 = 33;                         // Bit 3 de l'octet
    static const pin BIT4 = 31;                         // Bit 4 de l'octet
    static const pin BIT5 = 29;                         // Bit 5 de l'octet
    static const pin BIT6 = 27;                         // Bit 6 de l'octet
    static const pin BIT7 = 25;                         // Bit 7 de l'octet
    static const pin BIT8 = 23;                         // Bit 8 de l'octet
    
    static const pin RST = 45;                          // Remise à zéro des ticks
};

#endif

