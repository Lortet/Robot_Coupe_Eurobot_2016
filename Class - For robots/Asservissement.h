//----------------------------------------------------------------------//
//                            ASSERVISSEMENT                            //
//                                                    version 16.04.02  //
//                                             date 02/04/2016 - 00h57  //
//----------------------------------------------------------------------//
//  Permet de déplacer le robot à l'aide d'une commande en rotation et  //
//  distance.                                                           //
//----------------------------------------------------------------------//
//                                 Benjamin BROSSEAU & Valentin LORTET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//        Adapté des travaux de Kevin LE MOGUEN et Thibault d'ARTIGUES  //
//----------------------------------------------------------------------//

#ifndef __ASSERVISSEMENT_H__                             // Si la constante n'est pas définie
#define __ASSERVISSEMENT_H__                             // On la définit de manière à ce que le fichier ne soit plus inclus

#include <Arduino.h>                                     // Utilisation de la fonction abs()
#include "Codeurs.h"                                     // Utilisation de setMoteurDroit() et setMoteurGauche()
#include "Moteurs.h"                                     // Utilisation de setMoteurDroit() et setMoteurGauche()

class Asservissement{
  public:
    static const byte STATE_ARRET = 0;                   // Mouvement terminé
    static const byte STATE_TRANSLATION = 1;             // Translation en cours et rotation terminée
    static const byte STATE_ROTATION = 2;                // Rotation en cours
    static const byte STATE_TROUBLE = 3;                 // 
    
    Asservissement();                                    // Initialisation
    
    void setConsigneRot( long rotation );                // Permet de définir la consigne en rotation
    void setConsigneTra( long translation );             // Permet de définir la consigne en translation
    void setConsigne( long rotation, long translation ); // Permet de définir la consigne en rotation et translation
    
    void addConsigneRot( long rotation );                // Permet d'ajouter des contraintes à la consigne actuelle en rotation
    void addConsigneTra( long translation );             // Permet d'ajouter des contraintes à la consigne actuelle en translation
    void addConsigne( long rotation, long translation ); // Permet d'ajouter des contraintes à la consigne actuelle en rotation et translation
    
    void step( long codeurL, long codeurR );             // Permet d'effectuer un pas de l'asservissement
    char getState();                                     // 0 : A terminé le mouvement actuel; 1 : En cours de translation; 2 : En cours de rotation; X : Indéfini
    void allowArc();                                     // Autorise la rotation et la translation en simultané
    void stop( long codeurL, long codeurR );             // Permet de forcer la fin du mouvement actuel
    void stopMoteurs();                                  // Stoppe les moteurs
    void setSpeed( float speed );                        // Permet de modifier la vitesse des moteurs
    
    void detectTroubles( long codeurL, long codeurR, int commandeL, int commandeR );   // Detection des erreus d'asservissement (tranblement, obstacles, decolement des roues
    void takenTroubles();                                //
    
  private:
    Moteurs moteurs;                                     // Instantiation de la classe Moteurs
    
    char state;                                          // Stocke l'étape du mouvement
    long consigneRot;                                    // Stocke la consigne en rotation
    long consigneTra;                                    // Stocke la consigne en translation
    
    int lastCommandeL;                                   // Stocke la dernière commande du moteur gauche
    int lastCommandeR;                                   // Stocke la dernière commande du moteur droit
    
    long lastCodeurL;                                    // Stocke le dernier tick du codeur gauche
    long lastCodeurR;                                    // Stocke le dernier tick du codeur droit
    
    long lastTime;                                       // Stocke le dernier temps en millisecondes de l'appel de la fondion step
    
    int troubleCompteur;                                 // Stocke les erreurs

    float COEFF_TICKS_BY_COMMANDE_MOTEUR = 1;
    
    const byte SATURATION_COMMANDE = 153;                // = 255*60%; Défini le niveau de saturation des commandes de rotation et translation
    const byte SEUIL_COMMANDE_ROT = 15;                  // Defini le seuil d'erreur de commande en rotation pour éviter les tremblements
    const byte SEUIL_COMMANDE_TRA = 20;                  // Defini le seuil d'erreur de commande en translation pour éviter les tremblements
    
    const float KpTra = 0.04;
    const float KiTra = 0;
    const float KdTra = 0;
    
    const float KpRot = 0.2;
    const float KiRot = 0;
    const float KdRot = 0;
};

#endif
