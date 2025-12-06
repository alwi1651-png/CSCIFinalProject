#ifndef CHARACTER_H
#define CHARACTER_H
#include <vector>
#include <string>
#include <fstream> 
#include <sstream>
#include <iostream>

class Character {
    private:
        std::vector<std::string> names;
        std::vector<int> experience;
        std::vector<int> accuracy;
        std::vector<int> efficiency;
        std::vector<int> insight;
        std::vector<int> discoveryPoints;

        std::string playerName; 
        std::string characterName;
        int characterExperience;
        int characterAccuracy;  
        int characterEfficiency;
        int characterInsight;
        int characterDiscoveryPoints;
        bool isFellowship;
        int advisorID;
        int playerIndex;
        static const int MIN_TRAIT_VALUE = 100;
        
        void enforceMinimumTraits();

    public:
        Character();
        Character(int playeridx);  // Constructor declaration

        std::string getCharacterName(); 
        std::string getPlayerName();
        int getCharacterExperience();

        int getCharacterAccuracy();
        int getCharacterEfficiency();
        int getCharacterInsight();
        int getCharacterDiscoveryPoints();
        bool hasAdvisor();
        int getAdvisorId();
        bool getIsFellowship();

        // Mutators
        void addDiscoveryPoints(int delta);
        void addAccuracy(int delta);
        void addEfficiency(int delta);
        void addInsight(int delta);

        int convertTraitsToDiscoveryPoints();
        void printSummary();
        int getPlayerIndex() {
            return playerIndex;
        }   
};

#endif
