#include "Characters.h"
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>

Characters:: Characters(){ 
    playername = "";
    experience = 0 ;
    accuracy = 0;
    efficiency = 0 ;
    insight = 0 ;
    discoverypoints = 0; 
}
Characters:: Characters(string player_name, int _experience, int _accuracy, int _efficiency, int _insight, int _discoverypoints){
    playername = player_name;
    experience = _experience; 
    accuracy = _accuracy; 
    efficiency = _efficiency; 
    insight = _insight;
    discoverypoints = _discoverypoints;   
}
string Characters::getplayerName() const{
    return playername;
}
int Characters::getExperience() const{
return experience;
}
void Characters::setExperience( int _experience) {
experience = _experience;
}
int Characters::getAccuracy() const{
    return accuracy;
}
void Characters::setAccuracy(int _accuracy){
    accuracy = _accuracy;
    if(accuracy < 100){
        accuracy = 100;
    }
}
int Characters::getEfficiency() const{
    return efficiency;
}
void Characters::setEfficiency(int _efficiency){
    efficiency = _efficiency;
    if(efficiency < 100){
        efficiency = 100;
    }
}
int Characters:: getInsight() const{
    return insight;
}
void Characters::setInsight(int _insight){
insight = _insight;
if(insight < 100){
    insight = 100;
}
}
int Characters::getDiscoveryPoints() const{
    return discoverypoints;
}
void Characters::setDiscoveryPoints(int _discoverypoints){
    discoverypoints = _discoverypoints;
}
