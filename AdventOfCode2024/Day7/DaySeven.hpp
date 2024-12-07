//
//  DaySeven.hpp
//  AdventOfCode2024
//
#pragma once
#include <stdio.h>
#include <string>
#include "../Day.h"

#ifndef DaySeven_hpp
#define DaySeven_hpp
class DaySeven : public Day
{
private:
    // Tunables
    string inputPath = "Resources/DaySevenInput.txt";
    
public:
    // Methods
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};
#endif /* DaySeven_hpp */
