//
//  DayTwo.cpp
//  AdventOfCode2024
//

#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include "DayTwo.hpp"

bool DayTwo::CheckCriteria(int currentEntry, int lastEntry, bool isIncrementing, bool verbose)
{
    // Criteria One
    if (isIncrementing != (currentEntry > lastEntry))
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

void DayTwo::GetReportVector(string& line, std::vector<int>& reportVector)
{
    std::istringstream wordStream(line);
    int token;
    while (wordStream >> token)
    {
        reportVector.push_back(token);
    }
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
        bool isIncrementing = currentEntry > lastEntry;
        
        // Check criteria on first two entries, skip through if failing
        if (!CheckCriteria(currentEntry, lastEntry, isIncrementing, verbose)) { continue; }
        
        // Iterate and check if levels are safe
        int token;
        while (wordStream >> token)
        {
            lastEntry = currentEntry;
            currentEntry = token;
            
            if (!CheckCriteria(currentEntry, lastEntry, isIncrementing, verbose))
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
    int safeReportCount = 0;
    
    std::istringstream lineStream(input);
    for (std::string line; std::getline(lineStream, line); )
    {
        if (verbose) { std::cout << line << " - "; }
        bool isReportSafe = false;
        
        std::vector<int> reportVector;
        GetReportVector(line, reportVector);
        
        // Since vector element count small ::
        // Generate all potential sequences without entries, find if any of them are OK
        // Exit early if any found OK
        for (int iElementRemoval = 0; iElementRemoval < reportVector.size(); iElementRemoval++)
        {
            isReportSafe = false; // Overall report - override below if safe
            
            std::vector<int> testVector(reportVector);
            testVector.erase(testVector.begin() + iElementRemoval);
            
            bool isStepSafe = true; // Step check - override below if unsafe
            bool isIncrementing = true; // override below at j == 1
            for (int j = 0; j < testVector.size(); j++)
            {
                if (j == 0) { continue; }
                
                int currentEntry = testVector[j];
                int lastEntry = testVector[j-1];
                if (j == 1) { isIncrementing = (currentEntry > lastEntry); }
                
                if (!CheckCriteria(currentEntry, lastEntry, isIncrementing, verbose))
                {
                    isStepSafe = false;
                    break;
                }
            }
            isReportSafe = isStepSafe;
            
            if (isReportSafe) break; // Exit early, safe combo found
        }
        if (isReportSafe) {safeReportCount++; }
    }

    // Print output
    std::cout << "Safe report count is:" << std::endl;
    std::cout << safeReportCount << std::endl;
}
