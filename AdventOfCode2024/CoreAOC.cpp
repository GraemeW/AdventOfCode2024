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
    std::cout << "Loading file:" << std::endl;
    std::cout << inputPath << std::endl;
    
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
        case CoreAOC::AdventDay::AdventDayTwo:
        {
            DayTwo* dayTwo = new DayTwo();
            return dayTwo;
        }
        case CoreAOC::AdventDay::AdventDayThree:
        {
            DayThree* dayThree = new DayThree();
            return dayThree;
        }
        case CoreAOC::AdventDay::AdventDayFour:
        {
            DayFour* dayFour = new DayFour();
            return dayFour;
        }
        case CoreAOC::AdventDay::AdventDayFive:
        {
            DayFive* dayFive = new DayFive();
            return dayFive;
        }
    }
    DayZero* dayZero = new DayZero();
    return dayZero;
}
