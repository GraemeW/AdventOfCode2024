//
//  DayOne.hpp
//  AdventOfCode2024
//
#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include "../Day.h"

#ifndef DayOne_hpp
#define DayOne_hpp
class DayOne : public Day
{
private:
    string inputPath = "Resources/DayOneInput.txt";
    void GetVectorsFromInput(string& input, std::vector<int> &list1, std::vector<int> &list2);
    
public:
    // Methods
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};
#endif /* DayOne_hpp */
