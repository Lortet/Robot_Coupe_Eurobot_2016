//----------------------------------------------------------------------//
//                            ASSERVISSEMENT                            //
//                                                    version 16.04.24  //
//                                             date 24/04/2016 - 12h44  //
//----------------------------------------------------------------------//
//  Permet de déplacer le robot à l'aide d'une commande en rotation et  //
//  distance.                                                           //
//----------------------------------------------------------------------//
//                                 Benjamin BROSSEAU & Valentin LORTET  //
//                             Pour l'IUT de Nantes et le club Serinus  //
//        Adapté des travaux de Kevin LE MOGUEN et Thibault d'ARTIGUES  //
//----------------------------------------------------------------------//

#include "Asservissement.h"  //Utilisation de Asservissement()

Asservissement::Asservissement(){
  state = STATE_ARRET;
  setConsigne(0, 0);
}

void Asservissement::setConsigneRot(long rotation){
  consigneRot = rotation;
  
  if( state < STATE_ROTATION ) state = STATE_ROTATION;
}
void Asservissement::setConsigneTra(long translation){
  consigneTra = translation;
  
  if( state < STATE_TRANSLATION ) state = STATE_TRANSLATION;
}
void Asservissement::setConsigne(long rotation, long translation){
  setConsigneRot(rotation);
  setConsigneTra(translation);
  
  if( state < STATE_ROTATION ) state = STATE_ROTATION;
}

void Asservissement::addConsigneRot(long rotation){
  consigneRot += rotation;
  
  if( state < STATE_ROTATION ) state = STATE_ROTATION;
}
void Asservissement::addConsigneTra(long translation){
  consigneTra += translation;
  
  if( state < STATE_TRANSLATION ) state = STATE_TRANSLATION;
}
void Asservissement::addConsigne(long rotation, long translation){
  addConsigneRot(rotation);
  addConsigneTra(translation);
  
  if( state < STATE_ROTATION ) state = STATE_ROTATION;
}

void Asservissement::step(long codeurL, long codeurR){
  long tempConsigneRot = consigneRot;
  long tempConsigneTra = consigneTra;
  
  if( state == STATE_ROTATION ) tempConsigneTra = (codeurL + codeurR);                                      // Si l'étape de rotation est en cours, on surcharge la commande de translation
  
  //ecart en angle
  float erreurRot = tempConsigneRot - (codeurL - codeurR);
  float SerreursRot = SerreursRot + erreurRot;
  float erreur_precedenteRot = erreurRot;
  float variation_erreurRot = erreurRot - erreur_precedenteRot;
  
  //commande en rotation
  float commandeRot = KpRot * erreurRot + KiRot * SerreursRot + KdRot * variation_erreurRot;
  erreur_precedenteRot = erreurRot;
  
  //saturation en de la commande en  rotation
  if (commandeRot > SATURATION_COMMANDE) commandeRot = SATURATION_COMMANDE;
  else if (commandeRot < -SATURATION_COMMANDE) commandeRot = -SATURATION_COMMANDE;
  
  //Écart en translation
  float erreurTra = tempConsigneTra - (codeurL + codeurR);
  float SerreursTra = SerreursTra + erreurTra;
  float erreur_precedenteTra = erreurTra;
  float variation_erreurTra = erreurTra - erreur_precedenteTra;
  
  //commande en translation
  float commandeTra = KpTra * erreurTra + KiTra * SerreursTra + KdTra * variation_erreurTra;
  erreur_precedenteTra = erreurTra;
  
  //saturation en commande translation
  if (commandeTra > SATURATION_COMMANDE) commandeTra = SATURATION_COMMANDE;
  else if (commandeTra < -SATURATION_COMMANDE) commandeTra = -SATURATION_COMMANDE;
  
  //commande moteur.
  int commandeL = commandeTra + commandeRot;
  int commandeR = commandeTra - commandeRot;
  //la gestion des saturations de commandes est dans le driver du moteur.
  
  //arret a destination (evite les vibrations).
  if (abs(commandeL) < SEUIL_COMMANDE) commandeL = 0;
  if (abs(commandeR) < SEUIL_COMMANDE) commandeR = 0;
  
  if(state == STATE_ROTATION && commandeL == 0 && commandeR == 0) state = STATE_TRANSLATION; // Si l'etape de rotation est terminée, on attaque la translation
  else if(state == STATE_TRANSLATION && commandeL == 0 && commandeR == 0) state = STATE_ARRET; // Si l'étape de translation est terminée, on arrête le mouvement
  
  moteurs.set( Moteurs::LEFT, commandeL );
  moteurs.set( Moteurs::RIGHT, commandeR );
}
char Asservissement::getState(){
  return state;
}
void Asservissement::allowArc(){
  state = STATE_TRANSLATION;
}
void Asservissement::stop( long codeurL, long codeurR ){
  stopMoteurs();
  setConsigne( (codeurL - codeurR), (codeurL + codeurR) );
  
  state = STATE_ARRET;
}
void Asservissement::stopMoteurs(){
  moteurs.stop();
}
