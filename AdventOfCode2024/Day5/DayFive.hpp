//
//  DayFive.hpp
//  AdventOfCode2024
//
#pragma once
#include <stdio.h>
#include <string>
#include <map>
#include <vector>
#include "../Day.h"

#ifndef DayFive_hpp
#define DayFive_hpp
class DayFive : public Day
{
private:
    // Tunables
    string inputPath = "Resources/DayFiveInput.txt";
    char ruleMatch = '|';
    char entryMatch = ',';
    bool doSortOnUnsorted = false;
    int maxSortIterations = 10000;
    
    bool verbose = false;
    
    // Methods
    void ParseLineForRuleMaps(string const& line, std::map<int, std::vector<int>>& forwardRuleMap, std::map<int, std::vector<int>>& backwardRuleMap);
    void ParseLineForEntry(string const& line, std::vector<std::vector<int>>& printEntries);
    void AddToRuleMap(std::map<int, std::vector<int>>& ruleMap, int leadEntry, int followEntry);
    bool IsRuleMapCriteriaMet(std::vector<int>& printEntry, std::map<int, std::vector<int>> const& ruleMap, std::vector<int>& pageUpdate);
    void UpdatePrintEntry(std::vector<int>& printEntry, int pageNumber, int oldIndex, int newIndex);
    
public:
    // Methods
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};
#endif /* DayFive_hpp */
