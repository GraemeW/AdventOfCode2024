//
//  DayThree.hpp
//  AdventOfCode2024
//
#pragma once
#include <stdio.h>
#include <string>
#include "../Day.h"

#ifndef DayThree_hpp
#define DayThree_hpp
class DayThree : public Day
{
private:
    string inputPath = "Resources/DayThreeInput.txt";
    string matchExpression1 = "mul\\(([0-9]{1,3}),([0-9]{1,3})\\)";
    string matchExpression2 = "mul\\(([0-9]{1,3}),([0-9]{1,3})\\)|do\\(\\)|don't\\(\\)";
    string mulEnableCommand = "do()";
    string mulDisableCommand = "don't()";
    
public:
    // Methods
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};
#endif /* DayThree_hpp */
