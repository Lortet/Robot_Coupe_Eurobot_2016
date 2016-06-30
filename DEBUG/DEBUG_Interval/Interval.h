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

#ifndef __INTERVAL_H__                      // Si la constante n'est pas définie
#define __INTERVAL_H__                      // On la définie de manière à ce que le fichier ne soit plus inclus

#include <Arduino.h>

class Interval{
  
  public:
    Interval( boolean micro, long delay );  // Initialise le systme d'intervalle en definissant le temps d'attente
    
    void setInterval( long delay );         // Défini le temps d'attente
    
    void start();                           // Demarre le system d'intervalle
    void stop();                            // Stop le système d'intervalle
    void waitIntervalEnding();              // Effectue la pause pour correspondre à l'intervalle
    
    char getState();                        // Retourne l'état du comtpeur : 0 => Pause; 1 => Run;
    
    boolean isMicro();                      // Retourne si les temps sont en millisecondes ou microsecondes : 0 => millisecondes; 1 => microsecondes;
    unsigned long getTime();                      // Retourne le temps en millisecondes ou microsecondes suivant micro
    
    unsigned long getIntervalEnding();      // Retourne la valeur de temps pour correspondre à l'intervalle
    
    unsigned long getMinTime();             // Retourne la valeur de temps minimale effectuée
    unsigned long getMaxTime();             // Retourne la valeur de temps maximale effectuée
    
  private:
    char state;                             // Sauvegarde l'état du comtpeur : 0 => Pause; 1 => Run;
    
    boolean micro;                          // Si les temps sont en millisecondes ou microsecondes : 0 => millisecondes; 1 => microsecondes;
    
    unsigned long intervalTime;             // Sauvegarde la valeur de temps des intervalles demandées en millisecondes ou microsecondes
    unsigned long lastIntervalTime;         // Sauvegarde la valeur de temps de la dernière boucle
    
    unsigned long minTime;                  // Sauvegarde la valeur de temps minimale effectuée
    unsigned long maxTime;                  // Sauvegarde la valeur de temps maximale effectuée
};

#endif


