//----------------------------------------------------------------------//
//                             CONFIGURATION                            //
//----------------------------------------------------------------------//
//  Permet de configurer les robots                                     //
//----------------------------------------------------------------------//
//                                                     Valentin LORTET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//----------------------------------------------------------------------//

#ifndef __CONFIGURATION_H__  // Si la constante n'est pas définie
#define __CONFIGURATION_H__  // On la définit de manière à ce que le fichier ne soit plus inclus

/* Ne pas toucher */
#define Ulysse 1
#define Nono 2
/* !Ne pas toucher */

#define ROBOT Ulysse         // Ulysse ou Nono

#define HAS_AX12             // A laisser si AX12, mettre en commentaire sinon
#define HAS_EA               // A laisser si Electro-Aimants, mettre en commentaire sinon
#define HAS_SWITCH           // A laisser si Switchs, mettre en commentaire sinon
#define HAS_SONAR            // A laisser si Sonars, mettre en commentaire sinon

#endif

