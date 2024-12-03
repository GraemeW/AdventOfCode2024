//
//  DayTwo.cpp
//  AdventOfCode2024
//

#include <string>
#include <iostream>
#include <sstream>
#include "DayTwo.hpp"

bool DayTwo::CheckCriteria(int currentEntry, int lastEntry, bool isSequenceIncrementing, bool verbose)
{
    // Criteria One
    if (isSequenceIncrementing != (currentEntry > lastEntry))
    {
        if (verbose) { std::cout << "Warning[Not Continuous] - " << std::endl; }
        return false;
    }
    
    // Criteria Two
    int deltaEntry = abs(currentEntry - lastEntry);
    if ((deltaEntry < minDifferLevel) || (deltaEntry > maxDifferLevel))
    {
        if (verbose) { std::cout << "Warning[Limit Violation] - " << std::endl; }
        return false;
    }
    return true;
}

void DayTwo::CrunchPartOne(string& input)
{
    int safeReportCount = 0;
    
    std::istringstream lineStream(input);
    for (std::string line; std::getline(lineStream, line); )
    {
        if (verbose) { std::cout << line << " - "; }
        
        bool isReportSafe = true; // initialize, override below if unsafe
        
        // Pop entries off of an iStringStream
        std::istringstream wordStream(line);
        int lastEntry;
        int currentEntry;
        
        // To define initial polarity, pop twice
        wordStream >> lastEntry;
        wordStream >> currentEntry;
        bool isSequenceIncrementing = currentEntry > lastEntry;
        
        // Check criteria on first two entries, skip through if failing
        if (!CheckCriteria(currentEntry, lastEntry, isSequenceIncrementing, verbose))
        {
            continue;
        }
        
        // Iterate and check if levels are safe
        int token;
        while (wordStream >> token)
        {
            lastEntry = currentEntry;
            currentEntry = token;
            
            if (!CheckCriteria(currentEntry, lastEntry, isSequenceIncrementing, verbose))
            {
                isReportSafe = false;
                break;
            }
        }
        
        if (isReportSafe) { safeReportCount++; }
        if (verbose) { std::cout << safeReportCount << std::endl; }
    }
    
    // Print output
    std::cout << "Safe report count is:" << std::endl;
    std::cout << safeReportCount << std::endl;
}

void DayTwo::CrunchPartTwo(string& input)
{
    std::cout << input;
}
