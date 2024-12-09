//
//  DayNine.hpp
//  AdventOfCode2024
//

#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include "../Day.h"

#ifndef DayNine_hpp
#define DayNine_hpp
class DayNine : public Day
{
private:
    // Tunables
    string inputPath = "Resources/DayNineInput.txt";
    int spacerValue = -1;
    
    bool verbose = false;
    
public:
    // Methods
    std::vector<int> ParseFileIDs(string const& input);
    std::vector<int> CondenseDataVector(std::vector<int> const& outputWithSpacers);
    long long GenerateCheckSum(std::vector<int> const& condensedOutput);
    
    // Default
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};
#endif /* DayNine_hpp */
