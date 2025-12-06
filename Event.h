#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
class Event {
public:
    std::string description;
    int pathType;        // 0 = Training Fellowship; 1 = Direct Lab Assignment
    int advisor;         // 0 = none; 1 = Dr. Aliquot; 2 = Dr. Assembler; etc.
    int discoveryPoints; // can be negative

    Event() : description(""), pathType(0), advisor(0), discoveryPoints(0) {}
};
#endif