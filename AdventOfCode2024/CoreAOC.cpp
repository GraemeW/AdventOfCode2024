//
//  CoreAOC.cpp
//  AdventOfCode2024
//
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "CoreAOC.hpp"

string CoreAOC::GetAdventDayInput(string const& inputPath)
{
    std::cout << "Loading file:\n";
    std::cout << inputPath;
    std::cout << "\n";
    
    std::ifstream in(inputPath);
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string contents(buffer.str());
    return contents;
}

Day* CoreAOC::GetDaySelectors(CoreAOC::AdventDay adventDay)
{
    switch (adventDay)
    {
        case CoreAOC::AdventDay::AdventDayOne:
        {
            DayOne* dayOne = new DayOne();
            return dayOne;
        }
    }
    DayZero* dayZero = new DayZero();
    return dayZero;
}
