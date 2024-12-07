//
//  DaySix.hpp
//  AdventOfCode2024
//
#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include "../Day.h"

#ifndef DaySix_hpp
#define DaySix_hpp
class DaySix : public Day
{
private:
    // Tunables
    string inputPath = "Resources/DaySixInput.txt";
    enum Direction { North, East, South, West };
    
    static const char inputOpenSpace = '.';
    static const char inputBlockedSpace = '#';
    static const char inputGuard = '^';
    int facilityOpenSpace = 0;
    int facilityBlockedSpace = 1;
    int facilityGuard = 2;
    int facilityOpenLoopTested = 3;
    int stepSize = 1;
    std::string historyDelimiter = "-";
    Direction guardStartDirection = Direction::North;
    
    bool verbose = true;
    
    // State
    std::vector<std::vector<int>> facilityLayout;
    std::vector<int> facilityRowBounds = {0, 0};
    std::vector<int> facilityColBounds = {0, 0};
    std::map<string, int> guardPositionHistory;
    std::vector<int> testLoopStartPosition;
    Direction testLoopStartDirection;
    std::map<string, int> testLoopHistory;
    std::map<string, int> testLoopObstacleHistory;
    
    // Methods
    void ReadInputToFacilityLayout(string const& input, std::vector<int>& guardStartPosition);
    int ConvertInputToFacilityEntry(char const& inputCharacter);
    bool IsGuardInBounds(int guardRow, int guardCol);
    string GetNamedDirection(Direction direction);
    Direction GetNextDirection(Direction direction, bool isClockwise = true);
    std::vector<int> GetTranslationDirection(Direction direction);
    std::vector<int> GetTestObstacleOffset(Direction direction, int currentObstacleRow, int currentObstacleCol, int offsetPolarity = 1);
    bool IsPositionInHistory(int guardRow, int guardCol, bool isTestLoop = false);
    bool AddObstacleToHistory(int obstacleRow, int obstacleCol);
    void ResetTestLoop(std::vector<int>& resetGuardPosition, Direction& resetDirection);

public:
    // Methods
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};
#endif /* DaySix_hpp */
