//
//  DayEight.hpp
//  AdventOfCode2024
//
#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include "../Day.h"

#ifndef DayEight_hpp
#define DayEight_hpp

class DayEight : public Day
{
private:
    // Tunables
    string inputPath = "Resources/DayEightInput.txt";
    
public:
    // Methods
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};

#endif /* DayEight_hpp */