//
//  Day.h
//  AdventOfCode2024
//

#pragma once
using std::string;
#include <string>

#ifndef Day_h
#define Day_h
class Day
{
private:
    string inputPath = "";

public:
    virtual void CrunchPartOne(string& input) = 0;
    virtual void CrunchPartTwo(string& input) = 0;
    virtual string GetInputPath() { return inputPath; }
};
#endif /* Day_h */
