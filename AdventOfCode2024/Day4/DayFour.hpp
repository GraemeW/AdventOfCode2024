//
//  DayFour.hpp
//  AdventOfCode2024
//
#pragma once
#include <stdio.h>
#include <string>
#include <list>
#include <vector>
#include "../Day.h"

#ifndef DayFour_hpp
#define DayFour_hpp
class DayFour : public Day
{
private:
    // Tunables
    string inputPath = "Resources/DayFourInput.txt";
    bool verbose = false;
    int lineBufferLength = 3;
    std::vector<string> matchStrings = {"XMAS"}; // Note:  Will use below method to build superset match (e.g. incl. reverse)
    char matchCharacterPartTwo = 'A';
    std::vector<string> matchStringsPartTwo = {"MAS"};
    
    enum CheckDirection { NorthWest, North, NorthEast, West };
    char dummyChar = 'O';
    
    // Methods
    void GetWordMatchMatrix(string& input, std::vector<std::vector<char>>& wordMatchMatrix);
    void GetSupersetMatchStrings(std::vector<string> matchStrings, std::vector<string>& supersetMatchStrings);
    std::vector<int> GetRowColPreMultipliers(DayFour::CheckDirection checkDirection);
    bool CheckWordMatch(const std::vector<std::vector<char>>& wordMatchMatrix, string matchString, int row, int col, CheckDirection checkDirection);
    bool CheckXMatch(const std::vector<std::vector<char>>& wordMatchMatrix, string matchString, int row, int col, bool fromTop);
    
public:
    // Methods
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};
#endif /* DayFour_hpp */
