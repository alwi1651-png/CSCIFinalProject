#ifndef CHARACTERS_H
#define CHARACTERS_H
#include <iostream>
using namespace std;
class Characters{
    private:
    string playername;
    int experience;
    int accuracy;
    int efficiency;
    int insight;
    int discoverypoints;
public:
Characters();
Characters(string player_name, int _experience, int _accuracy, int _efficiency, int _insight, int _discoverypoints);
string getplayerName() const;
int getExperience() const;
void setExperience(int _experience);
int getAccuracy() const;
void setAccuracy(int _accuracy); 
int getEfficiency() const;
void setEfficiency( int _efficiency);
int getInsight() const;
void setInsight(int _insight);
int getDiscoveryPoints() const;
void setDiscoveryPoints(int _discoverypoints);
};


#endif