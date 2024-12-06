//
//  DaySix.hpp
//  AdventOfCode2024
//
#pragma once
#include <stdio.h>
#include <string>
#include "../Day.h"

#ifndef DaySix_hpp
#define DaySix_hpp
class DaySix : public Day
{
private:
    string inputPath = "Resources/DaySixInput.txt";

public:
    // Methods
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};
#endif /* DaySix_hpp */
