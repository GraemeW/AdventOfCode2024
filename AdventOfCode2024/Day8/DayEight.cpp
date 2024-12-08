//
//  DayEight.cpp
//  AdventOfCode2024
//

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include "DayEight.hpp"

bool FilterBounds::CheckWithinBounds(std::vector<int> position)
{
    if (position[0] < cornerTopLeft[0] || position[0] >= cornerBottomRight[0]) { return false; }
    if (position[1] < cornerTopLeft[1] || position[1] >= cornerBottomRight[1]) { return false; }
    return true;
}

void AntennaNode::AddMatchNode(AntennaNode* matchNode, bool addToFullSetOnly)
{
    if  (!addToFullSetOnly) { oneSidedMatchNodes.push_back(matchNode); }
    fullSetMatchNodes.push_back(matchNode);
}

std::vector<int> AntennaNode::GetAntiNodePosition(std::vector<int> antennaNodeAPosition, std::vector<int> antennaNodeBPosition)
{
    int rowPos = antennaNodeAPosition[0] + (antennaNodeAPosition[0] - antennaNodeBPosition[0]);
    int colPos = antennaNodeAPosition[1] + (antennaNodeAPosition[1] - antennaNodeBPosition[1]);
    return {rowPos, colPos};
}

std::vector<std::vector<int>> AntennaNode::GetHarmonicAntiNodePositions(AntennaNode* antennaNodeA, AntennaNode* antennaNodeB, FilterBounds* filterBounds)
{
    std::vector<std::vector<int>> harmonicAntiNodePositions;
    harmonicAntiNodePositions.push_back(antennaNodeA->GetPosition());
    harmonicAntiNodePositions.push_back(antennaNodeB->GetPosition());
    
    // Two-sided, once for A, once for B
    std::vector<int> refAntiNodePosition;
    std::vector<int> baseAntiNodePosition;
    for (int i = 0; i < 2; i++)
    {
        if (i == 0) { refAntiNodePosition = antennaNodeA->GetPosition(); baseAntiNodePosition = antennaNodeB->GetPosition(); }
        else if (i == 1) { refAntiNodePosition = antennaNodeB->GetPosition(); baseAntiNodePosition = antennaNodeA->GetPosition(); }
        
        std::vector<int> newAntiNodePosition = GetAntiNodePosition(refAntiNodePosition, baseAntiNodePosition);
        while(filterBounds->CheckWithinBounds(newAntiNodePosition))
        {
            harmonicAntiNodePositions.push_back(newAntiNodePosition);
            std::vector<int> temp(newAntiNodePosition);
            newAntiNodePosition = GetAntiNodePosition(newAntiNodePosition, refAntiNodePosition);
            refAntiNodePosition = temp;
        }
    }
    
    return harmonicAntiNodePositions;
}

int AntennaNode::CalculateAntiNodePositions(FilterBounds* filterBounds, std::map<string, bool>& uniqueAntiNodePositions, std::vector<std::vector<int>>& antiNodePositions, bool useOneSidedMatch)
{
    std::vector matchNodes = oneSidedMatchNodes; // Default behavior to avoid double counts when simple iterating
    if (!useOneSidedMatch) { matchNodes = fullSetMatchNodes; }
    
    int antiNodePositionCount = 0;
    for (const auto &matchNode : matchNodes)
    {
        std::vector<int> antiNodePosition;
        for (int i = 0; i < 2; i++) {
            // Two anti-nodes to generate per pair (each delta direction)
            if (i == 0) { antiNodePosition = GetAntiNodePosition(this->GetPosition(), matchNode->GetPosition()); }
            else if (i == 1) { antiNodePosition = GetAntiNodePosition(matchNode->GetPosition(), this->GetPosition()); }
            
            if (!filterBounds->CheckWithinBounds(antiNodePosition)) { continue; }
            
            // Cannot place anti-node on same spot twice (regardless of frequency)
            string uniqueAntiNodeKey = std::to_string(antiNodePosition[0]) + '-' + std::to_string(antiNodePosition[1]);
            if (uniqueAntiNodePositions.find(uniqueAntiNodeKey) == uniqueAntiNodePositions.end()) {
                uniqueAntiNodePositions[uniqueAntiNodeKey] = true;
                antiNodePositions.push_back(antiNodePosition); antiNodePositionCount++;
            }
        }
    }
    return antiNodePositionCount;
}

int AntennaNode::CalculateAntiNodePositionsWithHarmonics(FilterBounds* filterBounds, std::map<string, bool>& uniqueAntiNodePositions, std::vector<std::vector<int>>& antiNodePositions, bool useOneSidedMatch)
{
    std::vector matchNodes = oneSidedMatchNodes; // Default behavior to avoid double counts when simple iterating
    if (!useOneSidedMatch) { matchNodes = fullSetMatchNodes; }
    
    int antiNodePositionCount = 0;
    for (const auto &matchNode : matchNodes)
    {
        for (const auto& antiNodePosition : GetHarmonicAntiNodePositions(this, matchNode, filterBounds)) {
            // Note:  Logic on bounds moved to GetHarmonicAntiNodePositions()
            
            // Cannot place anti-node on same spot twice (regardless of frequency)
            string uniqueAntiNodeKey = std::to_string(antiNodePosition[0]) + '-' + std::to_string(antiNodePosition[1]);
            if (uniqueAntiNodePositions.find(uniqueAntiNodeKey) == uniqueAntiNodePositions.end()) {
                uniqueAntiNodePositions[uniqueAntiNodeKey] = true;
                antiNodePositions.push_back(antiNodePosition); antiNodePositionCount++;
            }
        }
    }
    return antiNodePositionCount;
}

void DayEight::CrunchPartOne(string& input)
{
    std::map<char, std::vector<AntennaNode*>> cityAntennaMap;
    std::vector<AntennaNode*> allAntennaNodes;
    int cityWidth = -1;
    int cityHeight = 0;
    
    // Build up all the antenna nodes into cityAntennaMap
    int row = 0;
    std::istringstream lineStream(input);
    for (std::string line; std::getline(lineStream, line); ) {
        if (cityWidth == -1) {cityWidth = (int)line.size(); }
        cityHeight++;
        
        int col = 0;
        for(char& antennaFrequency : line) {
            if (antennaFrequency == skipEntry) { col++; continue; }
            
            AntennaNode* newAntennaNode = new AntennaNode(antennaFrequency, {row, col});
            
            if (cityAntennaMap.find(antennaFrequency) == cityAntennaMap.end()) {
                // Frequency not yet encountered
                std::vector<AntennaNode*> antennaNodes;
                cityAntennaMap[antennaFrequency] = antennaNodes;
            }
            else {
                // Run through existing antenna nodes to add new entry to their local memory
                for (const auto &antennaNode : cityAntennaMap[antennaFrequency]) {
                    antennaNode->AddMatchNode(newAntennaNode);
                    newAntennaNode->AddMatchNode(antennaNode, true); // Add to full set (not used in P1)
                }
            }
            
            cityAntennaMap[antennaFrequency].push_back(newAntennaNode);
            allAntennaNodes.push_back(newAntennaNode);
            
            col++;
        }
        row++;
    }
    
    // Crunch antiNodes
    int totalAntiNodeCount = 0;
    std::vector<std::vector<int>> antiNodePositions;
    
    // Set city bounds to filter entries
    FilterBounds* filterBounds = new FilterBounds({0,0}, {cityHeight, cityWidth});
    
    std::map<string, bool> uniqueAntiNodePositions;
    for (const auto& [antennaFrequency, antennaNodes] : cityAntennaMap)
    {
        for (const auto& antennaNode : antennaNodes) {
            totalAntiNodeCount += antennaNode->CalculateAntiNodePositions(filterBounds, uniqueAntiNodePositions, antiNodePositions);
        }
    }
    
    if (verbose) {
        std::cout << "Anti-nodes at:" << std::endl;
        for (const auto& antiNodePosition : antiNodePositions) {
            std::cout << "(" << antiNodePosition[0] << "," << antiNodePosition[1] << "), ";
        }
    }
    
    // Output
    std::cout << "Total antiNode count is:" << std::endl;
    std::cout << totalAntiNodeCount << std::endl;
    
    // Clean up
    free(filterBounds);
    for (const auto &antennaNode : allAntennaNodes) { free(antennaNode); }
}

void DayEight::CrunchPartTwo(string& input)
{
    std::map<char, std::vector<AntennaNode*>> cityAntennaMap;
    std::vector<AntennaNode*> allAntennaNodes;
    int cityWidth = -1;
    int cityHeight = 0;
    
    // Build up all the antenna nodes into cityAntennaMap
    int row = 0;
    std::istringstream lineStream(input);
    for (std::string line; std::getline(lineStream, line); ) {
        if (cityWidth == -1) {cityWidth = (int)line.size(); }
        cityHeight++;
        
        int col = 0;
        for(char& antennaFrequency : line) {
            if (antennaFrequency == skipEntry) { col++; continue; }
            
            AntennaNode* newAntennaNode = new AntennaNode(antennaFrequency, {row, col});
            
            if (cityAntennaMap.find(antennaFrequency) == cityAntennaMap.end()) {
                // Frequency not yet encountered
                std::vector<AntennaNode*> antennaNodes;
                cityAntennaMap[antennaFrequency] = antennaNodes;
            }
            else {
                // Run through existing antenna nodes to add new entry to their local memory
                for (const auto &antennaNode : cityAntennaMap[antennaFrequency]) {
                    antennaNode->AddMatchNode(newAntennaNode);
                    newAntennaNode->AddMatchNode(antennaNode, true); // Add to full set (not used in P1)
                }
            }
            
            cityAntennaMap[antennaFrequency].push_back(newAntennaNode);
            allAntennaNodes.push_back(newAntennaNode);
            
            col++;
        }
        row++;
    }
    
    // Crunch antiNodes
    int totalAntiNodeCount = 0;
    std::vector<std::vector<int>> antiNodePositions;
    
    // Set city bounds to filter entries
    FilterBounds* filterBounds = new FilterBounds({0,0}, {cityHeight, cityWidth});
    
    std::map<string, bool> uniqueAntiNodePositions;
    for (const auto& [antennaFrequency, antennaNodes] : cityAntennaMap)
    {
        for (const auto& antennaNode : antennaNodes) {
            totalAntiNodeCount += antennaNode->CalculateAntiNodePositionsWithHarmonics(filterBounds, uniqueAntiNodePositions, antiNodePositions);
        }
    }
    
    if (verbose) {
        std::cout << "Anti-nodes at:" << std::endl;
        for (const auto& antiNodePosition : antiNodePositions) {
            std::cout << "(" << antiNodePosition[0] << "," << antiNodePosition[1] << "), ";
        }
    }
    
    // Output
    std::cout << "Total antiNode count is:" << std::endl;
    std::cout << totalAntiNodeCount << std::endl;
    
    // Clean up
    free(filterBounds);
    for (const auto &antennaNode : allAntennaNodes) { free(antennaNode); }
}
