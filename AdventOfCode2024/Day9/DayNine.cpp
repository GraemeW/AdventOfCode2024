//
//  DayNine.cpp
//  AdventOfCode2024
//

#include <string>
#include <iostream>
#include <vector>
#include "DayNine.hpp"

std::vector<int> DayNine::ParseFileIDs(string const& input)
{
    int currentID = 0;
    std::vector<int> outputWithSpacers;
    bool spacerToggle = false;

    for(int i = 0; i < input.size(); ++i) {
        int fileID = spacerValue;
        if (!spacerToggle) { fileID = currentID; }
        
        string entrySizeString = {input[i]};
        int entrySize = stoi(entrySizeString);
        
        for (int spacerCounter = 0; spacerCounter < entrySize; spacerCounter++) {
            outputWithSpacers.push_back(fileID);
        }
        
        if (!spacerToggle) { currentID++; }
        spacerToggle = !spacerToggle;
    }
    
    return outputWithSpacers;
}

std::vector<int> DayNine::CondenseDataVector(std::vector<int> const& outputWithSpacers)
{
    int i = 0;
    std::vector<int> condensedOutput(outputWithSpacers);
    while (true) {
        if (i >= condensedOutput.size()) {break; } // Check A
        if (condensedOutput[i] == spacerValue)
        {
            int backEntry = spacerValue;
            while (backEntry == spacerValue) {
                backEntry = condensedOutput.back();
                condensedOutput.pop_back();
            }
            if (i >= condensedOutput.size()) {break; } // Check B -- e.g. @ end of list
            condensedOutput[i] = backEntry;
        }
        i++;
    }
    return condensedOutput;
}

long long DayNine::GenerateCheckSum(std::vector<int> const& condensedOutput)
{
    long long checkSum = 0;
    for (int i = 0; i < condensedOutput.size(); i++) {
        checkSum += (i * condensedOutput[i]);
    }
    return checkSum;
}

void DayNine::CrunchPartOne(string& input)
{
    // Strip newline characters for safety on later int conversions
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.cend());
    
    std::vector<int> outputWithSpacers = ParseFileIDs(input);
    std::vector<int> condensedOutput = CondenseDataVector(outputWithSpacers);
    long long checkSum = GenerateCheckSum(condensedOutput);
     
    // Output
    std::cout << "CheckSum is:" << std::endl;
    std::cout << checkSum << std::endl;
}

void DayNine::CrunchPartTwo(string& input)
{
    std::cout << input;
}
