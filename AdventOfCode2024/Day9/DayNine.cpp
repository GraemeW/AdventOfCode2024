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

std::vector<DataChunk*> DayNine::ParseFileIDsToChunks(string const& input)
{
    int iPosition = 0;
    int currentID = 0;
    std::vector<DataChunk *> outputWithSpacers;
    
    for(int i = 0; i < input.size(); ++i) {
        string entrySizeString = {input[i]};
        int freeSpace = stoi(entrySizeString);
        int iPositionAdder = freeSpace;
        
        std::vector<int> currentEntries;
        if (i % 2 == 0) {
            for (int j = 0; j < freeSpace; j++) { currentEntries.push_back(currentID);}
            freeSpace = 0;
        }
        
        DataChunk* dataChunk = new DataChunk(iPosition, freeSpace, currentEntries);
        outputWithSpacers.push_back(dataChunk);
        
        iPosition += iPositionAdder;
        if (i % 2 == 0) { currentID++; }
    }
    
    return outputWithSpacers;
}

std::vector<int> DayNine::ConvertDataChunkToVector(DataChunk *dataChunk, bool flipEntries)
{
    std::vector<int> output(dataChunk->currentEntries);
    for (int i = 0; i < dataChunk->freeSpace; i++) {
        output.push_back(spacerValue);
    }
    std::reverse(output.begin(), output.end());
    return output;
}

std::deque<int> DayNine::CondenseDataVectorWithoutSplitting(std::vector<DataChunk*> const& outputWithSpacers)
{
    std::vector<DataChunk*> localOutputWithSpacers(outputWithSpacers);
    std::deque<int> condensedOutput;
    
    int initialOutputSize = (int)(localOutputWithSpacers.size());
    for (int iDataChunk = initialOutputSize-1; iDataChunk >= 0; iDataChunk-- )
    {
        DataChunk* currentBackValue = localOutputWithSpacers.back();
        if (iDataChunk % 2 == 1) {
            for (const auto& entry : ConvertDataChunkToVector(currentBackValue, true)){
                condensedOutput.push_front(entry);
            }
            localOutputWithSpacers.pop_back();
            continue;
        }
        
        int iValidSpacer = 0;
        for (const auto& spacerCheckDataChunk : localOutputWithSpacers) {
            if (spacerCheckDataChunk->freeSpace >= currentBackValue->currentEntries.size() ) { break; }
            iValidSpacer++;
        }
            
        if (iValidSpacer < localOutputWithSpacers.size()) {
            DataChunk* spacerCheckDataChunk = localOutputWithSpacers[iValidSpacer];
            std::vector<int> copyEntries(currentBackValue->currentEntries);
            spacerCheckDataChunk->currentEntries.insert(end(spacerCheckDataChunk->currentEntries), begin(copyEntries), end(copyEntries));
            spacerCheckDataChunk->freeSpace -= currentBackValue->currentEntries.size();
        }
        else
        { // Otherwise build condensedOutput from the back->forward
            for (const auto& entry : ConvertDataChunkToVector(currentBackValue, true)){
                condensedOutput.push_front(entry);
            }
        }
        localOutputWithSpacers.pop_back();
    }
    
    // Add in residuals @ front
    while(localOutputWithSpacers.size() > 0) {
        DataChunk* currentBackValue = localOutputWithSpacers.back();
        
        for (const auto& entry : ConvertDataChunkToVector(currentBackValue, true)){
            condensedOutput.push_front(entry);
        }
        localOutputWithSpacers.pop_back();
    }
    
    return condensedOutput;
}

template<typename T> // Need to generalize input type since can receive either deque or vector
long long DayNine::GenerateCheckSum(T const& condensedOutput)
{
    long long checkSum = 0;
    for (int i = 0; i < condensedOutput.size(); i++) {
        if (condensedOutput[i] == spacerValue) { continue; }
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
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.cend());
    
    std::vector<DataChunk*> outputWithSpacers = ParseFileIDsToChunks(input);
    
    std::deque<int> condensedOutput = CondenseDataVectorWithoutSplitting(outputWithSpacers);
    
    long long checkSum = GenerateCheckSum(condensedOutput);
     
    // Output
    std::cout << "CheckSum is:" << std::endl;
    std::cout << checkSum << std::endl;
}
