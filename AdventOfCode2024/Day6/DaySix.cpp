//
//  DaySix.cpp
//  AdventOfCode2024
//
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
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

void DaySix::ReadInputToFacilityLayout(string const& input, std::vector<int>& guardStartPosition)
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

bool DaySix::IsGuardInBounds(int guardRow, int guardCol)
{
    if (guardRow < facilityRowBounds[0] || guardRow >= facilityRowBounds[1]) { return false; }
    if (guardCol < facilityColBounds[0] || guardCol >= facilityColBounds[1]) {return false; }
    return true;
}

string DaySix::GetNamedDirection(DaySix::Direction direction)
{
    switch(direction) {
        case DaySix::Direction::North: return "North";
        case DaySix::Direction::East: return "East";
        case DaySix::Direction::South: return "South";
        case DaySix::Direction::West: return "West";
    }
}

DaySix::Direction DaySix::GetNextDirection(DaySix::Direction direction, bool isClockwise)
{
    if (isClockwise) {
        switch (direction) {
            case DaySix::Direction::North: return DaySix::Direction::East;
            case DaySix::Direction::East: return DaySix::Direction::South;
            case DaySix::Direction::South: return DaySix::Direction::West;
            case DaySix::Direction::West: return DaySix::Direction::North;
        }
    }
    else {
        switch (direction) {
            case DaySix::Direction::North: return DaySix::Direction::West;
            case DaySix::Direction::West: return DaySix::Direction::South;
            case DaySix::Direction::South: return DaySix::Direction::East;
            case DaySix::Direction::East: return DaySix::Direction::North;
        }
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

std::vector<int> DaySix::GetTestObstacleOffset(DaySix::Direction direction, int currentObstacleRow, int currentObstacleCol, int offsetPolarity)
{
    std::vector<int> testObstaclePosition = {currentObstacleRow, currentObstacleCol};
    switch(direction) {
        case DaySix::Direction::North: testObstaclePosition[0] += offsetPolarity; break;
        case DaySix::Direction::South: testObstaclePosition[1] -= offsetPolarity; break;
        case DaySix::Direction::East: testObstaclePosition[1] -= offsetPolarity; break;
        case DaySix::Direction::West: testObstaclePosition[1] += offsetPolarity; break;
    }
    return testObstaclePosition;
}

bool DaySix::IsPositionInHistory(int guardRow, int guardCol, bool isTestLoop)
{
    string guardHistoryEntry = std::to_string(guardRow) + historyDelimiter + std::to_string(guardCol);
    bool isPositionInHistory = false;
    if (!isTestLoop) {
        isPositionInHistory =(guardPositionHistory.find(guardHistoryEntry) != guardPositionHistory.end());
        guardPositionHistory[guardHistoryEntry]++;
    }
    else {
        isPositionInHistory =(testLoopHistory.find(guardHistoryEntry) != testLoopHistory.end());
        testLoopHistory[guardHistoryEntry]++;
    }
    return isPositionInHistory;
}

bool DaySix::AddObstacleToHistory(int obstacleRow, int obstacleCol)
{
    string obstacleHistoryEntry = std::to_string(obstacleRow) + historyDelimiter + std::to_string(obstacleCol);
    bool isPositionInHistory =(testLoopObstacleHistory.find(obstacleHistoryEntry) != testLoopObstacleHistory.end());
    testLoopObstacleHistory[obstacleHistoryEntry]++;
    return isPositionInHistory;
}

void DaySix::ResetTestLoop(std::vector<int>& resetGuardPosition, DaySix::Direction& resetDirection)
{
    std::vector<int> testLoopPositionCopy(testLoopStartPosition);
    Direction testLoopDirectionCopy(testLoopStartDirection);
    facilityLayout[testLoopPositionCopy[0]][testLoopPositionCopy[1]] = facilityOpenLoopTested;
    
    resetGuardPosition = testLoopPositionCopy;
    resetDirection = testLoopDirectionCopy;
}

void DaySix::CrunchPartOne(string& input)
{
    std::vector<std::vector<int>> facilityLayout;
    std::vector<int> guardStartPosition = {0, 0};
    ReadInputToFacilityLayout(input, guardStartPosition);
    
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
    std::vector<int> guardStartPosition = {0, 0};
    ReadInputToFacilityLayout(input, guardStartPosition);
    facilityRowBounds[1] = (int)facilityLayout.size();
    facilityColBounds[1] = (int)facilityLayout[0].size();

    // Note:  Only loops accessible by the guard path are valid, so still follow guard
    Direction direction = guardStartDirection;
    std::vector<int> guardPosition(guardStartPosition);
    
    // Tracking items
    int obstaclesEncountered = 0;
    int totalGuardPositions = 1;
    int loopObstaclesPlaceable = 0;
    
    // Toggle to enter/exit test loop for obstacle placement
    bool isTestLoop = false;
    
    while (true)
    {
        // Check for obstacles
        std::vector<int> translationDirection = GetTranslationDirection(direction);
        int tentativeGuardRow = guardPosition[0] + stepSize * translationDirection[0];
        int tentativeGuardCol = guardPosition[1] + stepSize * translationDirection[1];
        
        if (!IsGuardInBounds(tentativeGuardRow, tentativeGuardCol))
        {
            // Break early, otherwise addressing below fails
            if (!isTestLoop) { break; }
            else
            {
                ResetTestLoop(guardPosition, direction);
                isTestLoop = false;
                std::cout << "Exiting test loop" << std::endl;
                continue;
            }
        }
        
        if (facilityLayout[tentativeGuardRow][tentativeGuardCol] == facilityBlockedSpace)
        {
            if (verbose) { std::cout<< "Obstacle @ " << tentativeGuardRow << "," << tentativeGuardCol << std::endl; }
            
            if (isTestLoop) { AddObstacleToHistory(tentativeGuardRow, tentativeGuardCol); }
            obstaclesEncountered++;
            direction = GetNextDirection(direction);
            continue;
        }
        
        // Place test loop obstacle
        if (!isTestLoop && facilityLayout[tentativeGuardRow][tentativeGuardCol] == facilityOpenSpace)
        {
            // Add the obstacle and loop through
            isTestLoop = true;
            std::cout << "Entering test loop" << std::endl;
            testLoopStartPosition = {tentativeGuardRow, tentativeGuardCol};
            testLoopStartDirection = direction;
            std::map<string, int> mapCopy(guardPositionHistory);
            testLoopHistory = mapCopy;
            
            facilityLayout[tentativeGuardRow][tentativeGuardCol] = facilityBlockedSpace;
            testLoopObstacleHistory.clear();
            
            continue;
        }
        
        // Check for looping condition in test loop
        if (isTestLoop) {
            bool isObstacleRepeating = false;
            for (auto const& [key, val] : testLoopObstacleHistory) {
                if (val > 1) { isObstacleRepeating = true; }
            }
            
            if (isObstacleRepeating) { loopObstaclesPlaceable++; }
            if (isObstacleRepeating || testLoopObstacleHistory.size() > 10) {
                ResetTestLoop(guardPosition, direction);
                isTestLoop = false;
                if (verbose) { std::cout << "Exiting test loop" << std::endl; }
                continue;
            }
        }

        // Step
        guardPosition = {tentativeGuardRow, tentativeGuardCol};
        if (verbose) { std::cout<< "Guard @ " << tentativeGuardRow << "," << tentativeGuardCol << std::endl; }
        
        // Check for history --
        if (!IsPositionInHistory(guardPosition[0], guardPosition[1], isTestLoop)) { totalGuardPositions++; }
    }
    
    //Output
    std::cout << "Total loop objects placeable:" << std::endl;
    std::cout << loopObstaclesPlaceable << std::endl;
}
