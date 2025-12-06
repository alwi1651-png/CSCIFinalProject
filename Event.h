#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
class Event {
    private: 
        std::string description;
        int pathType;        // 0 = Training Fellowship; 1 = Direct Lab Assignment
        int advisor;         // 0 = none; 1 = Dr. Aliquot; 2 = Dr. Assembler; etc.
        int discoveryPoints; // can be negative

    public:
        Event(std::string parseLine) {
            std::stringstream ss(parseLine);
            std::string token;

            if (std::getline(ss, token, '|')) {
                description = token;
            }
            if (std::getline(ss, token, '|')) {
                pathType = std::stoi(token);
            }
            if (std::getline(ss, token, '|')) {
                advisor = std::stoi(token);
            }
            if (std::getline(ss, token, '|')) {
                discoveryPoints = std::stoi(token);
            }

        }
        int getAdvisor() {
            return advisor;
        }
        int getPathType() {
            return pathType;
        }
        int getDiscoveryPoints() {
            return discoveryPoints;
        }
        std::string getDescription() {
            return description;
        }
        void setDescription(std::string desc) {
            description = desc;
        }
        void setPathType(int pType) {
            pathType = pType;
        }
        void setAdvisor(int adv) {
            advisor = adv;
        }
        void setDiscoveryPoints(int dp) {
            discoveryPoints = dp;
        }

};
#endif