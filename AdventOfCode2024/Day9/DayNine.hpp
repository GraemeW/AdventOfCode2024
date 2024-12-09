//
//  DayNine.hpp
//  AdventOfCode2024
//

#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include "../Day.h"

#ifndef DayNine_hpp
#define DayNine_hpp
struct DataChunk
{
    int iPosition;
    int freeSpace;
    std::vector<int> currentEntries;
    DataChunk(int iPosition, int freeSpace, std::vector<int> currentEntries) : iPosition(iPosition), freeSpace(freeSpace), currentEntries(currentEntries){};
};

class DayNine : public Day
{
private:
    // Tunables
    string inputPath = "Resources/DayNineInput.txt";
    int spacerValue = -1;
    
    bool verbose = false;
    
public:
    // Methods
    // Part 1
    std::vector<int> ParseFileIDs(string const& input);
    std::vector<int> CondenseDataVector(std::vector<int> const& outputWithSpacers);
    std::vector<int> ConvertDataChunkToVector(DataChunk* dataChunk, bool flipEntries);
    // Part 2
    std::vector<DataChunk*> ParseFileIDsToChunks(string const& input);
    std::deque<int> CondenseDataVectorWithoutSplitting(std::vector<DataChunk*> const& outputWithSpacers);
    // General
    template<typename T>
    long long GenerateCheckSum(T const& condensedOutput);
    
    // Default
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};
#endif /* DayNine_hpp */
