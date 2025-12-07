#ifndef RIDDLE_H
#define RIDDLE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

class Riddle {
private:
    std::string question;
    std::string answer;
    std::string bonusQuestion;
    std::string bonusAnswer;

    // Helper: trim and lowercase for safe matching
    std::string normalize(std::string s) const {
        // Trim leading/trailing whitespace
        s.erase(0, s.find_first_not_of(" \t\r\n"));
        s.erase(s.find_last_not_of(" \t\r\n") + 1);

        // Lowercase
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

public:
    Riddle(std::string parseLine) {
        std::stringstream ss(parseLine);
        std::string token;

        if (std::getline(ss, token, '|')) {
            question = token;
        }
        if (std::getline(ss, token, '|')) {
            answer = token;
        }
    }

    std::string getQuestion() {
        return question;
    }

    // Return normalized answer for consistent comparisons
    std::string getAnswer() {
        return normalize(answer);
    }

    void bonusRiddle(std::string parseLine) {
        std::stringstream ss(parseLine);
        std::string token;

        if (std::getline(ss, token, '|')) {
            bonusQuestion = token;
        }
        if (std::getline(ss, token, '|')) {
            bonusAnswer = token;
        }
    }

    std::string getBonusQuestion() {
        return bonusQuestion;
    }

    // Return normalized bonus answer
    std::string getBonusAnswer() {
        return normalize(bonusAnswer);
    }
};

#endif
