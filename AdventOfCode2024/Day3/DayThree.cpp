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
    std::regex exp(matchExpression1);
    
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
    int totalProduct = 0;
    
    // Matching on mul(<1-3 digit number>,<1-3 digit number>)
    std::smatch match;
    std::regex exp(matchExpression2);
    
    // Define iterator to loop over input
    int subMatches[] = { 0, 1, 2 }; // triplet entries (whole match, sub1, sub2)
    std::regex_token_iterator<std::string::iterator> matchIterator (input.begin(), input.end(), exp, subMatches);
    std::regex_token_iterator<std::string::iterator> rend;     // default constructor = end-of-sequence:
    
    // New logic for skips
    int subMatchStep = 0; // triplets, as above
    bool doEnabled = true;
    bool skipNextSubMatches = false;
    int firstEntry = 0; // Memory for storing first entry in mul(x,y)
    while (matchIterator!=rend)
    {
        std::string subMatchEntry = *matchIterator++;
        
        if (subMatchStep == 0)
        {
            // Handling for toggling disable / enable on mul(x,y)
            if (subMatchEntry.find(mulDisableCommand) != std::string::npos) { doEnabled = false; skipNextSubMatches = true; }
            if (subMatchEntry.find(mulEnableCommand) != std::string::npos) { doEnabled = true; skipNextSubMatches = true; }
        }
        else
        {
            if (doEnabled && !skipNextSubMatches)
            {
                if (subMatchStep == 1) { firstEntry = stoi(subMatchEntry); }
                else if (subMatchStep == 2) { totalProduct += (stoi(subMatchEntry) * firstEntry); }
            }
        }
        
        // Increment sub-match -- comes in triplets based on subMatches, as above
        if (subMatchStep == 2) { subMatchStep = 0; skipNextSubMatches = false; }
        else { subMatchStep++; }
    }
    
    //Output
    std::cout << "Total product is:" << std::endl;
    std::cout << totalProduct << std::endl;
}
