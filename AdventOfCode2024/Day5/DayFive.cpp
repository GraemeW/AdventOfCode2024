//
//  DayFive.cpp
//  AdventOfCode2024
//
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include "DayFive.hpp"

void DayFive::ParseLineForRuleMaps(string const& line, std::map<int, std::vector<int>>& forwardRuleMap, std::map<int, std::vector<int>>& backwardRuleMap)
{
    int leadEntry = -1;
    int followEntry = -1;
    std::istringstream segmentStream(line);
                
    for (std::string segment; std::getline(segmentStream, segment, ruleMatch); )
    {
        if (leadEntry == -1) { leadEntry = stoi(segment); }
        else if (followEntry == -1) {followEntry = stoi(segment); }
    }
    AddToRuleMap(forwardRuleMap, leadEntry, followEntry);
    AddToRuleMap(backwardRuleMap, followEntry, leadEntry); // Not needed -- added for error checking
}

void DayFive::ParseLineForEntry(string const& line, std::vector<std::vector<int>>& printEntries)
{
    std::istringstream segmentStream(line);

    std::vector<int> printEntry;
    for (std::string pageNumber; std::getline(segmentStream, pageNumber, entryMatch); )
    {
        printEntry.push_back(stoi(pageNumber));
    }
    printEntries.push_back(printEntry);
}

void DayFive::AddToRuleMap(std::map<int, std::vector<int>>& ruleMap, int leadEntry, int followEntry)
{
    if (!ruleMap.count(leadEntry))
    {
        std::vector<int> ruleEntry;
        ruleEntry.push_back(followEntry);
        ruleMap[leadEntry] = ruleEntry;
    }
    else { ruleMap[leadEntry].push_back(followEntry); }
}

bool DayFive::IsRuleMapCriteriaMet(std::vector<int>& printEntry, std::map<int, std::vector<int>> const& ruleMap, std::vector<int>& pageUpdate)
{
    int brokenPageNumber = -1;
    int brokenIndex = -1;
    int updatedIndex = -1;
    for (int iPageNumber = 0; iPageNumber < printEntry.size(); iPageNumber++)
    {
        int pageNumber = printEntry[iPageNumber];
        for (int const& ruleEntry : ruleMap.at(pageNumber))
        {
            auto it = std::find(printEntry.begin(), printEntry.end(), ruleEntry);
            if (it == printEntry.end()) { continue; } // rule is not in printEntry
            
            int iRuleEntry = (int)std::distance(printEntry.begin(), it);
            if (iRuleEntry < iPageNumber)
            {
                brokenPageNumber = pageNumber;
                brokenIndex = iPageNumber;
                updatedIndex = iRuleEntry;
                break;
            }
        }
        if (brokenIndex != -1) { break; }
    }
    
    // Pass-Back Update Terms
    if (brokenIndex != -1)
    {
        pageUpdate = { brokenPageNumber, brokenIndex, updatedIndex };
        return false;
    }
    
    return true;
}

void DayFive::UpdatePrintEntry(std::vector<int>& printEntry, int pageNumber, int oldIndex, int newIndex)
{
    // Note:  Since newIndex is guaranteed < oldIndex, can erase then insert without concern
    printEntry.erase(printEntry.begin() + oldIndex);
    printEntry.insert(printEntry.begin() + newIndex, pageNumber);
}

void DayFive::CrunchPartOne(string& input)
{
    std::map<int, std::vector<int>> forwardRuleMap;
    std::map<int, std::vector<int>> backwardRuleMap;
    std::vector<std::vector<int>> printEntries;
    
    // Read out input into friendlier containers
    std::istringstream lineStream(input);
    for (std::string line; std::getline(lineStream, line); )
    {
        if (line.find(ruleMatch) != std::string::npos)
        {
            ParseLineForRuleMaps(line, forwardRuleMap, backwardRuleMap);
        }
        else if (line.find(entryMatch) != std::string::npos)
        {
            ParseLineForEntry(line, printEntries);
        }
    }
    
    // Check which entries are sorted, increment
    int midPageSum = 0;
    std::vector<std::vector<int>> sortedPrintEntries;
    for (auto const& printEntry : printEntries)
    {
        std::vector<int> localPrintEntry(printEntry); // Local copy
        std::vector<int> pageUpdate; // pageNumber, oldIndex, newIndex
        
        if (IsRuleMapCriteriaMet(localPrintEntry, forwardRuleMap, pageUpdate))
        {
            int midIndex = floor(localPrintEntry.size() / 2);
            midPageSum += localPrintEntry[midIndex];
        }
    }
    
    //Output
    std::cout << "Valid mid-page sum is:" << std::endl;
    std::cout << midPageSum << std::endl;
}

void DayFive::CrunchPartTwo(string& input)
{
    std::map<int, std::vector<int>> forwardRuleMap;
    std::map<int, std::vector<int>> backwardRuleMap;
    std::vector<std::vector<int>> printEntries;
    
    // Read out input into friendlier containers
    std::istringstream lineStream(input);
    for (std::string line; std::getline(lineStream, line); )
    {
        if (line.find(ruleMatch) != std::string::npos)
        {
            ParseLineForRuleMaps(line, forwardRuleMap, backwardRuleMap);
        }
        else if (line.find(entryMatch) != std::string::npos)
        {
            ParseLineForEntry(line, printEntries);
        }
    }
    
    // Check which entries are sorted, increment
    std::vector<std::vector<int>> sortedPrintEntries;
    for (auto const& printEntry : printEntries)
    {
        std::vector<int> localPrintEntry(printEntry); // Local copy
        std::vector<int> pageUpdate; // pageNumber, oldIndex, newIndex
        
        // Skip sorted entries
        if (IsRuleMapCriteriaMet(localPrintEntry, forwardRuleMap, pageUpdate)) { continue; }
        
        // Wholly unnecessary, reading comprehension fail
        int sortIterations = 0;
        // Complex sorting criteria, will require multiple passes
        while (!IsRuleMapCriteriaMet(localPrintEntry, forwardRuleMap, pageUpdate))
        {
            UpdatePrintEntry(localPrintEntry, pageUpdate[0], pageUpdate[1], pageUpdate[2]);
            
            if (sortIterations > maxSortIterations) {
                std::cout << "WARNING:  Max iteration count reached, exiting.";
                break;
            }
            sortIterations++;
        }

        sortedPrintEntries.push_back(localPrintEntry);
    }
    
    // Calculate sum (could also just do this in-line in above loop)
    int sortedMidPageSum = 0;
    for  (auto const& sortedPrintEntry : sortedPrintEntries)
    {
        int midIndex = floor(sortedPrintEntry.size() / 2);
        sortedMidPageSum += sortedPrintEntry[midIndex];
        
        if (verbose) {
            std::cout << "Sorted Print Entry:";
            for (auto const& pageNumber : sortedPrintEntry) {
                std::cout << pageNumber << ",";
            }
            std::cout << std::endl;
            std::cout << ", with mid-value: " << sortedPrintEntry[midIndex] << std::endl;
        }
        if (verbose) { std::cout << "Sum @ " << sortedMidPageSum << std::endl; }
    }
    
    //Output
    std::cout << "Valid mid-page sum is:" << std::endl;
    std::cout << sortedMidPageSum << std::endl;
}
