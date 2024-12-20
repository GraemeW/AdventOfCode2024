//
//  DayTwo.hpp
//  AdventOfCode2024
//
#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include "../Day.h"

#ifndef DayTwo_hpp
#define DayTwo_hpp
class DayTwo : public Day
{
private:
    string inputPath = "Resources/DayTwoInput.txt";
    bool verbose = false;
    int minDifferLevel = 1;
    int maxDifferLevel = 3;
    int problemDampenerAllowance = 1;
    
    bool CheckCriteria(int currentEntry, int lastEntry, bool isIncrementing, bool verbose);
    void GetReportVector(string& line, std::vector<int>& reportVector);
    
public:
    // Methods
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};
#endif /* DayTwo_hpp */
