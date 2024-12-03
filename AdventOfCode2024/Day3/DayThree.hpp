//
//  DayThree.hpp
//  AdventOfCode2024
//
#pragma once
#include <stdio.h>
#include <string>
#include <list>
#include <vector>
#include "../Day.h"

#ifndef DayThree_hpp
#define DayThree_hpp
class DayThree : public Day
{
private:
    string inputPath = "Resources/DayThreeInput.txt";
    
public:
    // Methods
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};
#endif /* DayThree_hpp */
