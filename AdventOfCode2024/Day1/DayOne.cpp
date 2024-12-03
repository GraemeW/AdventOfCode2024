//
//  DayOne.cpp
//  AdventOfCode2024
//

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "DayOne.hpp"

void DayOne::GetVectorsFromInput(string& input, std::vector<int> &list1, std::vector<int> &list2)
{
    // Iterate over each line
    std::istringstream lineStream(input);
    for (std::string line; std::getline(lineStream, line); )
    {
        std::istringstream wordStream(line);
        std::string token1;
        std::string token2;

        wordStream >> token1 >> token2;
        list1.push_back(stoi(token1));
        list2.push_back(stoi(token2));
    }
    
    // Double check on lengths
    if (list1.size() != list2.size())
    {
        throw std::invalid_argument("Input lists do not match in length, and so comparisons cannot be made");
    }
}

void DayOne::CrunchPartOne(string& input)
{
    std::vector<int> list1;
    std::vector<int> list2;
    GetVectorsFromInput(input, list1, list2);
    
    // Sort
    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());
    
    // Iterate over lists and compare + sum
    int listDisparitySum = 0;
    for (int i = 0; i < list1.size(); i++)
    {
        listDisparitySum += abs(list1[i] - list2[i]);
    }
    
    // Print output
    std::cout << "Summed disparity in lists is:" << std::endl;
    std::cout << listDisparitySum << std::endl;
}

void DayOne::CrunchPartTwo(string& input)
{
    std::vector<int> list1;
    std::vector<int> list2;
    GetVectorsFromInput(input, list1, list2);
    
    // Create map of second list instance count
    std::map<int, int> list2EntryFrequency;
    for (int i = 0; i < list2.size(); i++)
    {
        list2EntryFrequency[list2[i]]++;
    }
    
    // Iterate over first list, multiply out & add
    int similarityScore = 0;
    for (int i = 0; i < list1.size(); i++)
    {
        int entry = list1[i];
        
        int multiplier = 0;
        if (list2EntryFrequency.count(entry)) { multiplier = list2EntryFrequency[entry]; }
        
        similarityScore += entry * multiplier;
    }
    
    // Print output
    std::cout << "Similarity score is:" << std::endl;
    std::cout << similarityScore << std::endl;
}
