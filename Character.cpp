#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Character.h"


Character::Character() {
    


    isFellowship=true;
    std::ifstream file("characters.txt");
    std::string line;
    std::cout << "Whats your name bruh?  ";
    std::cin >> playerName;
    

    // Skip header
    getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;

        // Expected 6 fields: name | exp | acc | eff | insight | dp
        std::vector<std::string> fields;
        while (std::getline(ss, token, '|')) {
            fields.push_back(token);
        }

        if (fields.size() != 6) {
            std::cerr << "Malformed line: " << line << "\n";
            continue;
        }

        names.push_back(fields[0]);
        experience.push_back(std::stoi(fields[1]));
        accuracy.push_back(std::stoi(fields[2]));
        efficiency.push_back(std::stoi(fields[3]));
        insight.push_back(std::stoi(fields[4]));
        discoveryPoints.push_back(std::stoi(fields[5]));
    }
    
    // Print character info using stored vectors
    std::cout << "\nAVAILABLE CHARACTERS\n";
    std::cout << "------------------------------------------------------------------\n";
    for (size_t i = 0; i < names.size(); ++i) {
        std::cout 
            << "Choice Number: "<< i<< "\n"
            <<"Name: " << names[i] <<"\n"
            <<"Experience: "<< experience[i] <<"\n"
            << "Accuracy: "<<accuracy[i]<<"\n"
            << "Efficiency: "<<efficiency[i] <<"\n"
            << "Insight: "<< insight[i] <<"\n"
            << "Discovery points: " << discoveryPoints[i] << "\n";

        std::cout << "------------------------------------------------------------------\n";
    }
    // These vectors now hold all character data for later use

    std::cout << "\n";

    //prompt user to select character
    int choice = -1;

    while (choice < 0 || choice >= static_cast<int>(names.size())) {
        std::cout << "\nSelect your character by entering the corresponding number (0-" 
                << names.size() - 1 << "): ";
        std::cin >> choice;

        if (!std::cin) { // input failed (not a number)
            std::cin.clear(); // reset cin
            std::cin.ignore(1000, '\n'); // discard up to 1000 characters until newline
            std::cout << "Invalid input. Please enter a number.\n";
            choice = -1; // reset choice so loop continues
            continue;
        }

        if (choice < 0 || choice >= static_cast<int>(names.size())) {
            std::cout << "Number out of range. Try again.\n";
        }
    }

    std::cout << "You selected: " << names[choice] << "\n";
    characterName = names[choice];
    characterExperience = experience[choice];   
    characterAccuracy = accuracy[choice];
    characterEfficiency = efficiency[choice];
    characterInsight = insight[choice];
    characterDiscoveryPoints = discoveryPoints[choice];

   
    int pathChoice = -1;
    while (pathChoice < 0 || pathChoice >= 2) {
        std::cout << R"(
            Choose a path type for your character:

            0. Training Fellowship:
            This path equips your scientist with essential traits accuracy, efficiency,
            and insight needed for future challenges. The training requires an investment
            of -5,000 Discovery Points from the starting number of Discovery Points.
            This symbolizes the time and resources dedicated to developing these skills.
            This path also adds 500 Accuracy Points, 500 Efficiency Points, and 1,000
            Insight Points to the starting amount of your character’s traits before you 
            start the journey.

            1. Direct Lab Assignment:
            This option lets your scientist jump directly into the life of DNA sequencing
            with an immediate boost of +5,000 Discovery Points from the starting number of
            Discovery Points. This path also adds 200 Accuracy Points, 200 Efficiency
            Points, and 200 Insight Points before you start the journey.
            Although this path offers a strong head start, it lacks long-term resilience
            and special abilities that could be gained through mentorship in Training 
            Fellowship, making it a riskier approach to become a Lead Genomicist. Also, 
            you will not get an initial advisor if you choose this path.
            )" << "\n";

        std::cin >> pathChoice;

        if (!std::cin) { // input failed (not a number)
            std::cin.clear(); // reset cin
            std::cin.ignore(1000, '\n'); // discard up to 1000 characters until newline
            std::cout << "Invalid input. Please enter a number.\n";
            pathChoice = -1; // reset choice so loop continues
            continue;
        }

        if (pathChoice < 0 || pathChoice >= 2) {
            std::cout << "Number out of range. Try again.\n";
        }
    }
    if(pathChoice == 0){
        std::cout << "You selected Training Fellowship path.\n";
    } else {
        std::cout << "You selected Direct Lab Assignment path.\n";
        isFellowship=false;
    }

    if(isFellowship){
        characterDiscoveryPoints -= 5000;
        characterAccuracy += 500;
        characterEfficiency += 500;
        characterInsight += 1000;
        std::cout << "As part of the Training Fellowship, you must choose an advisor to guide you through your journey.\n";
        std::cout << "Choose an advisor:\n";
        std::cout << R"(
            0. Dr. Aliquot: A master of the 'wet lab', assisting in avoiding contamination.
            1. Dr. Assembler: An expert who helps improve efficiency and streamlines pipelines.
            2. Dr. Pop-Gen: A genetics specialist with insight for identifying rare genetic variants.
            3. Dr. Bio-Script: The genius behind the data analysis, helps debug code.
            4. Dr. Loci: Your biggest supporter assisting you in learning the equipment)"<< "\n";
        int advisorChoice = -1;
        while (advisorChoice < 0 || advisorChoice >= 5) {
            std::cin >> advisorChoice;

            if (!std::cin) { // input failed (not a number)
                std::cin.clear(); // reset cin
                std::cin.ignore(1000, '\n'); // discard up to 1000 characters until newline
                std::cout << "Invalid input. Please enter a number.\n";
                advisorChoice = -1; // reset choice so loop continues
                continue;
            }

            if (advisorChoice < 0 || advisorChoice >= 5) {
                std::cout << "Number out of range. Try again.\n";
            }
        }
        switch (advisorChoice) {
            case 0:
                std::cout << "You selected Dr. Aliquot as your advisor.\n";
                advisorID = 0;
                break;
            case 1:
                std::cout << "You selected Dr. Assembler as your advisor.\n";
                advisorID = 1;
                break;
            case 2:
                std::cout << "You selected Dr. Pop-Gen as your advisor.\n";
                advisorID = 2;
                break;
            case 3:
                std::cout << "You selected Dr. Bio-Script as your advisor.\n";
                advisorID = 3;
                break;
            case 4:
                std::cout << "You selected Dr. Loci as your advisor.\n";
                advisorID = 4;
                break;
        }
    }

    else {
        // Direct Lab Assignment path chosen
        characterDiscoveryPoints += 5000;
        characterAccuracy += 200;
        characterEfficiency += 200;
        characterInsight += 200;
        advisorID = -1; // No advisor assigned

    }
}


void Character::enforceMinimumTraits() {

    if (characterAccuracy < MIN_TRAIT_VALUE) {
        characterAccuracy = MIN_TRAIT_VALUE;
    }
    if (characterEfficiency < MIN_TRAIT_VALUE) {
        characterEfficiency = MIN_TRAIT_VALUE;
    }
    if (characterInsight < MIN_TRAIT_VALUE) {
        characterInsight = MIN_TRAIT_VALUE;
    }
}

std::string Character::getCharacterName() {
    return characterName;
}
std::string Character::getPlayerName() {
    return playerName;
}
int Character::getCharacterExperience() {
    return characterExperience;
}
int Character::getCharacterAccuracy() {
    return characterAccuracy;
}
int Character::getCharacterEfficiency() {
    return characterEfficiency;
}
int Character::getCharacterInsight() {
    return characterInsight;
}
int Character::getCharacterDiscoveryPoints() {
    return characterDiscoveryPoints;
}

int Character::getAdvisorId() {
    if (!isFellowship) {
        return -1; // No advisor assigned
    }
    return advisorID;
}

bool Character::getIsFellowship() {
    return isFellowship;
}


void Character::addDiscoveryPoints(int delta) {
    characterDiscoveryPoints += delta;
}
void Character::addAccuracy(int delta) {
    characterAccuracy += delta;
    if (characterAccuracy < MIN_TRAIT_VALUE) characterAccuracy = MIN_TRAIT_VALUE;
}
void Character::addEfficiency(int delta) {
    characterEfficiency += delta;
    if (characterEfficiency < MIN_TRAIT_VALUE) characterEfficiency = MIN_TRAIT_VALUE;
}
void Character::addInsight(int delta) {
    characterInsight += delta;
    if (characterInsight < MIN_TRAIT_VALUE) characterInsight = MIN_TRAIT_VALUE;
}

// Convert each trait into discovery points as a final scoring mechanism
int Character::convertTraitsToDiscoveryPoints() {
    // Example conversion rates (you can adjust): accuracy/100 + efficiency/100 + insight/100, scaled
    int converted = (characterAccuracy / 10) + (characterEfficiency / 10) + (characterInsight / 10);
    characterDiscoveryPoints += converted;
    return converted;
}

// Summary print
void Character::printSummary() {
    std::cout << "Player: " << playerName << "\n";
    std::cout << "Character: " << characterName << " (" << characterExperience << ")\n";
    std::cout << "Discovery Points: " << characterDiscoveryPoints << "\n";
    std::cout << "Accuracy: " << characterAccuracy << "\n";
    std::cout << "Efficiency: " << characterEfficiency << "\n";
    std::cout << "Insight: " << characterInsight << "\n";
    std::cout << "Path: " << (isFellowship ? "Training Fellowship" : "Direct Lab Assignment") << "\n";
    if (isFellowship) {
        std::cout << "Advisor ID: " << advisorID << "\n";
    } else {
        std::cout << "No advisor assigned.\n";
    }
}