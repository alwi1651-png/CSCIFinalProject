#ifndef RIDDLE_H
#define RIDDLE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
class Riddle{
    private: 
        std::string question;
        std::string answer;
        std::string bonusQuestion;
        std::string bonusAnswer;

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
        std::string getQuestion(){
            return question;
        }
        std::string getAnswer(){
            return answer;
        }
    void bonusRiddle(std::string parseLine){
            std::stringstream ss(parseLine);
            std::string token;

            if (std::getline(ss, token, '|')) {
                bonusQuestion = token;
            }
            if (std::getline(ss, token, '|')) {
                bonusAnswer = token;
            }
    }
        std::string getBonusQuestion(){ 
            return bonusQuestion;
        }
        std::string getBonusAnswer(){
            return bonusAnswer;
        }
    
};
#endif