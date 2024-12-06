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
    int stepSize = 1;
    std::string historyDelimiter = "-";
    Direction guardStartDirection = Direction::North;
    
    // State
    std::map<string, int> guardPositionHistory;
    std::vector<int> facilityRowBounds = {0, 0};
    std::vector<int> facilityColBounds = {0, 0};
    
    // Methods
    void ReadInputToFacilityLayout(string const& input, std::vector<std::vector<int>>& facilityLayout, std::vector<int>& guardStartPosition);
    int ConvertInputToFacilityEntry(char const& inputCharacter);
    std::vector<int> GetTranslationDirection(Direction direction);
    Direction GetNextDirection(Direction direction);
    bool IsGuardInBounds(int guardRow, int guardCol);
    bool IsPositionInHistory(int guardRow, int guardCol);

public:
    // Methods
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};
#endif /* DaySix_hpp */
