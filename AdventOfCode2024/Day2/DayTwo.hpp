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
    void GetVectorsFromInput(string& input, std::vector<int> &list1, std::vector<int> &list2);
    
public:
    // Methods
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};
#endif /* DayTwo_hpp */
