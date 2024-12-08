//
//  DayEight.hpp
//  AdventOfCode2024
//
#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include "../Day.h"

#ifndef DayEight_hpp
#define DayEight_hpp

class DayEight : public Day
{
private:
    // Tunables
    string inputPath = "Resources/DayEightInput.txt";
    char skipEntry = '.';
    
    bool verbose = false;
    
public:
    // Methods
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};

class FilterBounds {
public:
    // Properties
    std::vector<int> cornerTopLeft;
    std::vector<int> cornerBottomRight;
    FilterBounds(std::vector<int> cornerTopLeft, std::vector<int> cornerBottomRight) : cornerTopLeft(cornerTopLeft), cornerBottomRight(cornerBottomRight){}

    // Methods
    bool CheckWithinBounds(std::vector<int> position);
};

class AntennaNode {
private:
    // Properties
    char nodeType;
    std::vector<int> position;
    std::vector<AntennaNode*> oneSidedMatchNodes;
    std::vector<AntennaNode*> fullSetMatchNodes; // Strictly - not necessary for p1
public:
    AntennaNode(char nodeType, std::vector<int> position) : nodeType(nodeType), position(position){}
    
    // Methods
    void AddMatchNode(AntennaNode* matchNode, bool addToFullSetOnly = false);
    std::vector<int> GetPosition() { return position; }
    std::vector<int> GetAntiNodePosition(AntennaNode* antennaNodeA, AntennaNode* antennaNodeB);
    int CalculateAntiNodePositions(FilterBounds* filterBounds, std::map<string, bool>& uniqueAntiNodePositions, std::vector<std::vector<int>>& antiNodePositions, bool useOneSidedMatch = true);
};
#endif /* DayEight_hpp */
