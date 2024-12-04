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
    string inputPath = "Resources/DayFourInput.txt";
    
public:
    // Methods
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};
#endif /* DayFour_hpp */
