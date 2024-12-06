//
//  DaySix.cpp
//  AdventOfCode2024
//
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "DaySix.hpp"

int DaySix::ConvertInputToFacilityEntry(char const& inputCharacter)
{
    switch(inputCharacter) {
        case inputOpenSpace: return facilityOpenSpace;
        case inputBlockedSpace: return facilityBlockedSpace;
        case inputGuard: return facilityGuard;
    }
    return -1;
}

void DaySix::ReadInputToFacilityLayout(string const& input, std::vector<std::vector<int>>& facilityLayout, std::vector<int>& guardStartPosition)
{
    int facilityWidth = -1;
    
    std::istringstream lineStream(input);
    int row = 0;
    for (std::string line; std::getline(lineStream, line); ) {
        // Avoid dynamic allocation, pre-reserve the space
        if (facilityWidth == -1) { facilityWidth = (int)line.size(); }
        std::vector<int> facilityRow;
        facilityRow.reserve(facilityWidth);
        
        int col = 0;
        for(char& inputEntry : line) {
            int facilityEntry = ConvertInputToFacilityEntry(inputEntry);
            if (facilityEntry == facilityGuard) { guardStartPosition = {row, col}; }
            facilityRow.push_back(facilityEntry);
            col++;
        }
        facilityLayout.push_back(facilityRow);
        row++;
    }
}

std::vector<int> DaySix::GetTranslationDirection(DaySix::Direction direction)
{
    switch(direction) {
        case DaySix::Direction::North: return {-1, 0};
        case DaySix::Direction::East: return {0, 1};
        case DaySix::Direction::South: return {1, 0};
        case DaySix::Direction::West: return {0, -1};
    }
    return {0, 0};
}

DaySix::Direction DaySix::GetNextDirection(DaySix::Direction direction)
{
    switch (direction) {
        case DaySix::Direction::North: return DaySix::Direction::East;
        case DaySix::Direction::East: return DaySix::Direction::South;
        case DaySix::Direction::South: return DaySix::Direction::West;
        case DaySix::Direction::West: return DaySix::Direction::North;
    }
}

bool DaySix::IsGuardInBounds(int guardRow, int guardCol)
{
    if (guardRow < facilityRowBounds[0] || guardRow > facilityRowBounds[1]) { return false; }
    if (guardCol < facilityColBounds[0] || guardCol > facilityColBounds[1]) {return false; }
    return true;
}

bool DaySix::IsPositionInHistory(int guardRow, int guardCol)
{
    string guardHistoryEntry = std::to_string(guardRow) + historyDelimiter + std::to_string(guardCol);
    bool isPositionInHistory =(guardPositionHistory.find(guardHistoryEntry) != guardPositionHistory.end());
    guardPositionHistory[guardHistoryEntry]++;
    return isPositionInHistory;
}

void DaySix::CrunchPartOne(string& input)
{
    std::vector<std::vector<int>> facilityLayout;
    std::vector<int> guardStartPosition = {0, 0};
    ReadInputToFacilityLayout(input, facilityLayout, guardStartPosition);
    
    // N.B. Bounds set exit criteria (i.e. when guard traverses off of facility space)
    facilityRowBounds[1] = (int)facilityLayout.size();
    facilityColBounds[1] = (int)facilityLayout[0].size();
    
    // Traverse through guard path
    int totalGuardPositions = 1; // count the first position
    
    Direction direction = guardStartDirection;
    int guardRow = guardStartPosition[0];
    int guardCol = guardStartPosition[1];
    
    while (IsGuardInBounds(guardRow, guardCol))
    {
        // Check for obstacles
        std::vector<int> translationDirection = GetTranslationDirection(direction);
        int tentativeGuardRow = guardRow + stepSize * translationDirection[0];
        int tentativeGuardCol = guardCol + stepSize * translationDirection[1];
        if (!IsGuardInBounds(tentativeGuardRow, tentativeGuardCol)) { break; } // Break early, otherwise addressing below fails
        
        if (facilityLayout[tentativeGuardRow][tentativeGuardCol] == facilityBlockedSpace)
        {
            direction = GetNextDirection(direction);
            continue;
        }
        
        // Step
        guardRow = tentativeGuardRow;
        guardCol = tentativeGuardCol;
        
        // Check for history --
        if (!IsPositionInHistory(guardRow, guardCol)) { totalGuardPositions++; }
    }
    
    //Output
    std::cout << "Total guard positions is:" << std::endl;
    std::cout << totalGuardPositions << std::endl;
}

void DaySix::CrunchPartTwo(string& input)
{
    std::cout << input;
}
