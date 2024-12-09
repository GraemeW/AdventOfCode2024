//
//  CoreAOC.hpp
//  AdventOfCode2024
//
#pragma once
#include <stdio.h>
#include <string>
#include "Day.h"
#include "Days.h"

#ifndef CoreAOC_hpp
#define CoreAOC_hpp
class CoreAOC
{
    // Attributes
    public:
        enum AdventDay { AdventDayOne, AdventDayTwo, AdventDayThree, AdventDayFour,
            AdventDayFive, AdventDaySix, AdventDaySeven, AdventDayEight, AdventDayNine };

    // Methods
    public:
        static string GetAdventDayInput(string const& inputPath);
        static Day* GetDaySelectors(AdventDay adventDay);
};
#endif /* CoreAOC_hpp */
