//
//  DayFive.hpp
//  AdventOfCode2024
//
#pragma once
#include <stdio.h>
#include <string>
#include "../Day.h"

#ifndef DayFive_hpp
#define DayFive_hpp
class DayFive : public Day
{
private:
    string inputPath = "Resources/DayFiveInput.txt";
    
public:
    // Methods
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};
#endif /* DayFive_hpp */
