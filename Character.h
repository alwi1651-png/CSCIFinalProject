#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Character {
private:
    // Static vectors shared across all Character instances
    static std::vector<std::string> names;
    static std::vector<int> experience;
    static std::vector<int> accuracy;
    static std::vector<int> efficiency;
    static std::vector<int> insight;
    static std::vector<int> discoveryPoints;
    static std::vector<bool> isCharacterTaken; // tracks if a character is already chosen

    // Instance-specific attributes
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
    // Constructors
    Character();
    Character(int playeridx);

    // Getters
    std::string getCharacterName();
    std::string getPlayerName();
    int getCharacterExperience();
    int getCharacterAccuracy();
    int getCharacterEfficiency();
    int getCharacterInsight();
    int getCharacterDiscoveryPoints();
    bool getIsFellowship();
    int getAdvisorId();
    bool hasAdvisor(); // true if the character has an advisor
    int getPlayerIndex() {
            return playerIndex;
        }   

    // Mutators
    void addDiscoveryPoints(int delta);
    void addAccuracy(int delta);
    void addEfficiency(int delta);
    void addInsight(int delta);
    void addExperience(int delta);

    // Conversion and display
    int convertTraitsToDiscoveryPoints();
    void printSummary();

    // Character selection utilities
    static bool isTaken(int choice); // check if a character is already taken
};

#endif
