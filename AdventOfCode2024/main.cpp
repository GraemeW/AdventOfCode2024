//
//  main.cpp
//  AdventOfCode2024

#include <iostream>
#include "CoreAOC.hpp"

int main(int argc, const char * argv[]) {
    // Main Selection
    CoreAOC::AdventDay daySelector = CoreAOC::AdventDayTwo;
    int sectionSelector = 1;

    // Read out input data
    Day* day = CoreAOC::GetDaySelectors(daySelector);
    string inputPath = day->GetInputPath();
    string inputData = CoreAOC::GetAdventDayInput(day->GetInputPath());

    // Execution
    if (sectionSelector == 1)
    {
        day->CrunchPartOne(inputData);
    }
    else if (sectionSelector == 2)
    {
        day->CrunchPartTwo(inputData);
    }

    // Clean Up
    free(day);
}
