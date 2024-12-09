//
//  DayNine.cpp
//  AdventOfCode2024
//

#include <string>
#include <iostream>
#include <vector>
#include "DayNine.hpp"

void DayNine::CrunchPartOne(string& input)
{
    int currentID = 0;
    std::vector<int> outputWithSpacers;
    bool spacerToggle = false;
    
    // Strip newline characters
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.cend());
    
    // Step1 -- Parse input into fileID ++ positions
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
    
    // Step2 -- Condense the data vector
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
    
    // Step 3 -- Generate checksum
    long long checkSum = 0;
    for (int i = 0; i < condensedOutput.size(); i++) {
        checkSum += (i * condensedOutput[i]);
    }
     
    // Output
    std::cout << "CheckSum is:" << std::endl;
    std::cout << checkSum << std::endl;
}

void DayNine::CrunchPartTwo(string& input)
{
    std::cout << input;
}
