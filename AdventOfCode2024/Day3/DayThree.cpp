//
//  DayThree.cpp
//  AdventOfCode2024
//
#include <string>
#include <iostream>
#include <regex>
#include "DayThree.hpp"

void DayThree::CrunchPartOne(string& input)
{
    int totalProduct = 0;
    
    // Matching on mul(<1-3 digit number>,<1-3 digit number>)
    std::smatch match;
    std::regex exp("mul\\(([0-9]{1,3}),([0-9]{1,3})\\)");
    
    // Define iterator to loop over input
    int subMatches[] = { 1, 2 };
    std::regex_token_iterator<std::string::iterator> matchIterator (input.begin(), input.end(), exp, subMatches);
    std::regex_token_iterator<std::string::iterator> rend;     // default constructor = end-of-sequence:
    
    bool subToggle = false;
    int firstEntry = 0;
    while (matchIterator!=rend)
    {
        if (!subToggle) { firstEntry = stoi(*matchIterator++); subToggle = true; }
        else
        {
            totalProduct += (stoi(*matchIterator++) * firstEntry);
            subToggle = false;
        }
    }
    
    //Output
    std::cout << "Total product is:" << std::endl;
    std::cout << totalProduct << std::endl;
}

void DayThree::CrunchPartTwo(string& input)
{
    std::cout << input;
}
