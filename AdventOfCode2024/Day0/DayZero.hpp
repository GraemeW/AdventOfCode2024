//
//  DayZero.hpp
//  AdventOfCode2024
//
#pragma once
#include <stdio.h>
#include <string>
#include "../Day.h"

#ifndef DayZero_hpp
#define DayZero_hpp
class DayZero : public Day
{
private:
    string inputPath = "";

public:
    // Methods
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};
#endif /* DayZero_hpp */
