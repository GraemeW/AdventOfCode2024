//
//  DayOne.cpp
//  AdventOfCode2024
//

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "DayOne.hpp"

void DayOne::CrunchPartOne(string& input)
{
    std::vector<int> list1;
    std::vector<int> list2;
 
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
    
    // Sort
    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());
    
    // Iterate over lists and compare + sum
    int listDisparitySum = 0;
    for (int i = 0; i < list1.size(); i++)
    {
        std::cout << list1[i] << "\n";
        std::cout << list2[i] << "\n";
        listDisparitySum += abs(list1[i] - list2[i]);
    }
    
    // Print output
    std::cout << "Summed disparity in lists is:\n";
    std::cout << listDisparitySum;
    std::cout << "\n";
}

void DayOne::CrunchPartTwo(string& input)
{
    std::cout << input;
}
