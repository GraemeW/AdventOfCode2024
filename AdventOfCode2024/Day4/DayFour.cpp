//
//  DayFour.cpp
//  AdventOfCode2024
//
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "DayFour.hpp"

void DayFour::GetWordMatchMatrix(string& input, std::vector<std::vector<char>>& wordMatchMatrix)
{
    int lineLength = -1;
    
    std::istringstream lineStream(input);
    for (std::string line; std::getline(lineStream, line); )
    {
        if (lineLength == -1)
        {
            // Define line length -- input + 2x buffer on cols
            lineLength = (int)line.length() + 2*lineBufferLength;
            
            // Add in start buffer rows
            std::vector<char> dummyLine(lineLength, dummyChar);
            for (int i = 0; i < lineBufferLength; i++)
            {
                wordMatchMatrix.push_back(dummyLine);
            }
        }
        
        // Initialize line
        std::vector<char> wordMatchLine;
        std::vector<char> dummyCols(lineBufferLength, dummyChar);
        
        // Add in data set w/ dummy cols on either side
        wordMatchLine.insert(std::end(wordMatchLine), std::begin(dummyCols), std::end(dummyCols));
        std::copy(line.begin(), line.end(), std::back_inserter(wordMatchLine));
        wordMatchLine.insert(std::end(wordMatchLine), std::begin(dummyCols), std::end(dummyCols));
        wordMatchMatrix.push_back(wordMatchLine);
    }
    
    // Add in end buffer rows -- Unused in Part1, necessary for Part2
    std::vector<char> dummyLine(lineLength, dummyChar);
    for (int i = 0; i < lineBufferLength; i++)
    {
        wordMatchMatrix.push_back(dummyLine);
    }
    
    if (verbose)
    {
        // Verify vectors match expectation
        for (int i = 0; i < wordMatchMatrix.size(); i++) {
            for (int j = 0; j < wordMatchMatrix[i].size(); j++) {
                std::cout << wordMatchMatrix[i][j] << " ";
            }
            std::cout << std::endl;
            std::cout << "Line Length: " << wordMatchMatrix[i].size() << std::endl;
        }
    }
}

void DayFour::GetSupersetMatchStrings(std::vector<string> matchStrings, std::vector<string>& supersetMatchStrings)
{
    // Add in reverse strings for checks
    for (int i = 0; i < matchStrings.size(); i++)
    {
        supersetMatchStrings.push_back(matchStrings[i]);
        
        string reverseString = string(matchStrings[i].rbegin(), matchStrings[i].rend());
        supersetMatchStrings.push_back(reverseString);
    }
    
    if (verbose)
    {
        for (int i = 0; i < supersetMatchStrings.size(); i++)
        {
            std::cout << supersetMatchStrings[i] << std::endl;
        }
    }
}

std::vector<int> DayFour::GetRowColPreMultipliers(DayFour::CheckDirection checkDirection)
{
    std::vector<int> rowColPreMultipliers = {0, 0};
    switch (checkDirection)
    {
        case DayFour::CheckDirection::NorthWest:
        {
            rowColPreMultipliers[0] = -1;
            rowColPreMultipliers[1] = -1;
            break;
        }
        case DayFour::CheckDirection::North:
        {
            rowColPreMultipliers[0] = -1;
            rowColPreMultipliers[1] = 0;
            break;
        }
        case DayFour::CheckDirection::NorthEast:
        {
            rowColPreMultipliers[0] = -1;
            rowColPreMultipliers[1] = 1;
            break;
        }
        case DayFour::CheckDirection::West:
        {
            rowColPreMultipliers[0] = 0;
            rowColPreMultipliers[1] = -1;
            break;
        }
    }
    return rowColPreMultipliers;
}

bool DayFour::CheckWordMatch(const std::vector<std::vector<char>>& wordMatchMatrix, string matchString, int row, int col, DayFour::CheckDirection checkDirection)
{
    std::vector<int> rowColPreMultipliers = GetRowColPreMultipliers(checkDirection);
    
    bool isMatch = true;
    for(int i = 0; i < matchString.size(); ++i)
    {
        int rowCheckOffset = rowColPreMultipliers[0] * i;
        int colCheckOffset = rowColPreMultipliers[1] * i;
        
        if (matchString[i] != wordMatchMatrix[row + rowCheckOffset][col + colCheckOffset])
        {
            isMatch = false;
            break;
        }
    }
    return isMatch;
}

bool DayFour::CheckXMatch(const std::vector<std::vector<char>>& wordMatchMatrix, string matchString, int row, int col, bool fromTop)
{
    std::vector<int> rowColPreMultipliers = {1, 1};
    int startRow = row - 1;
    int startCol = col - 1;
    if (!fromTop)
    {
        rowColPreMultipliers[0] = -1;
        startRow = row + 1;
        startCol = col - 1;
    }
    
    bool isMatch = true;
    for(int i = 0; i < matchString.size(); ++i)
    {
        int rowCheckOffset = rowColPreMultipliers[0] * i;
        int colCheckOffset = rowColPreMultipliers[1] * i;
        
        if (matchString[i] != wordMatchMatrix[startRow + rowCheckOffset][startCol + colCheckOffset])
        {
            isMatch = false;
            break;
        }
    }
    return isMatch;
}

void DayFour::CrunchPartOne(string& input)
{
    int wordMatchCount = 0;
    
    // Convert input to 2D vector w/ row/col buffers
    std::vector<std::vector<char>> wordMatchMatrix;
    GetWordMatchMatrix(input, wordMatchMatrix);
    
    // Expand match strings to check reverse
    std::vector<string> supersetMatchStrings;
    GetSupersetMatchStrings(matchStrings, supersetMatchStrings);
    
    // Rastering NW -> SE
    for (int row = 0; row < wordMatchMatrix.size(); row++)
    {
        if (row < lineBufferLength) { continue; }
        for (int col = 0; col < wordMatchMatrix[row].size(); col++)
        {
            if (row < lineBufferLength) { continue; }
            if (row > (wordMatchMatrix[row].size() - lineBufferLength)) { continue; }
            
            for (int iMatchString = 0; iMatchString < supersetMatchStrings.size(); iMatchString++)
            {
                string matchString = supersetMatchStrings[iMatchString];
                
                // Check if first character of match string aligns to entry
                if (wordMatchMatrix[row][col] == supersetMatchStrings[iMatchString][0])
                {
                    if (CheckWordMatch(wordMatchMatrix, matchString, row, col, DayFour::CheckDirection::NorthWest)) {
                        if (verbose) { std::cout << matchString << " NW match found at (" << row << "," << col << ")" << std::endl; }
                        wordMatchCount++; }
                    if (CheckWordMatch(wordMatchMatrix, matchString, row, col, DayFour::CheckDirection::North)) {
                        if (verbose) { std::cout << matchString << " N match found at (" << row << "," << col << ")" << std::endl; }
                        wordMatchCount++; }
                    if (CheckWordMatch(wordMatchMatrix, matchString, row, col, DayFour::CheckDirection::NorthEast)) {
                        if (verbose) { std::cout << matchString << " NE match found at (" << row << "," << col << ")" << std::endl; }
                        wordMatchCount++; }
                    if (CheckWordMatch(wordMatchMatrix, matchString, row, col, DayFour::CheckDirection::West)) {
                        if (verbose) { std::cout << matchString << " W match found at (" << row << "," << col << ")" << std::endl; }
                        wordMatchCount++; }
                }
            }
        }
    }
    
    //Output
    std::cout << "Word match count is:" << std::endl;
    std::cout << wordMatchCount << std::endl;
}

void DayFour::CrunchPartTwo(string& input)
{
    int wordMatchCount = 0;
    
    // Convert input to 2D vector w/ row/col buffers
    std::vector<std::vector<char>> wordMatchMatrix;
    GetWordMatchMatrix(input, wordMatchMatrix);
    
    // Expand match strings to check reverse
    std::vector<string> supersetMatchStrings;
    GetSupersetMatchStrings(matchStringsPartTwo, supersetMatchStrings);
    
    // Rastering NW -> SE
    for (int row = 0; row < wordMatchMatrix.size(); row++)
    {
        if (row < lineBufferLength) { continue; }
        for (int col = 0; col < wordMatchMatrix[row].size(); col++)
        {
            if (row < lineBufferLength) { continue; }
            if (row > (wordMatchMatrix[row].size() - lineBufferLength)) { continue; }
            
            bool topMatch = false;
            bool bottomMatch = false;
            for (int iMatchString = 0; iMatchString < supersetMatchStrings.size(); iMatchString++)
            {
                string matchString = supersetMatchStrings[iMatchString];
                
                // Check if first character of match string aligns to entry
                if (wordMatchMatrix[row][col] == matchCharacterPartTwo)
                {
                    if (!topMatch && CheckXMatch(wordMatchMatrix, matchString, row, col, true)) { topMatch = true; }
                    if (!bottomMatch && CheckXMatch(wordMatchMatrix, matchString, row, col, false)) { bottomMatch = true; }
                }
            }
            if (topMatch && bottomMatch) { wordMatchCount++; }
        }
    }
    
    //Output
    std::cout << "Word match count is:" << std::endl;
    std::cout << wordMatchCount << std::endl;
}

