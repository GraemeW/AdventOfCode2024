//
//  DaySeven.cpp
//  AdventOfCode2024
//
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "DaySeven.hpp"

long long DaySeven::GenerateEquationParts(string const& line, std::deque<int>& ropeBits)
{
    // Initialize
    long long bridgeOutput = 0;
    ropeBits.clear();
    
    // Crunch & Output
    int segmentIndex = 0;
    std::istringstream segmentStream(line);
    for (std::string segment; std::getline(segmentStream, segment, ' '); ) {
        if (segmentIndex == 0) {
            // Remove : operator from back of input
            segment.pop_back();
            
            // We need to use long long due to large #s -- casting via string stream
            std::stringstream bridgeOutputConvert(segment);
            long long temp;
            bridgeOutputConvert >> temp;
            bridgeOutput = temp;
        }
        else
        {
            ropeBits.push_back(stoi(segment));
        }
        segmentIndex++;
    }
    return bridgeOutput;
}

void Rope::AddToRope(long long nextRopeBit)
{
    std::vector<RopeNode*> newLeafNodes;
    if (leafNodes.size()==0) { leafNodes.push_back(root); }
    
    for (auto childRopeNode : leafNodes)
    {
        long long addOutput = (childRopeNode->ropeOutput) + nextRopeBit;
        long long multiplyOutput = (childRopeNode->ropeOutput) * nextRopeBit;
        
        root->addChild = new RopeNode(addOutput);
        root->multiplyChild = new RopeNode(multiplyOutput);
        
        newLeafNodes.push_back(root->addChild);
        newLeafNodes.push_back(root->multiplyChild);
    }
    
    leafNodes = newLeafNodes;
}

void DaySeven::CrunchPartOne(string& input)
{
    long long bridgeOutputSum = 0;
    
    std::istringstream lineStream(input);
    for (std::string line; std::getline(lineStream, line); )
    {
        std::deque<int> ropeBits;
        long long bridgeOutput = GenerateEquationParts(line, ropeBits);
        
        // Initialize Rope
        Rope* rope = new Rope(ropeBits.front());
        ropeBits.pop_front();
        
        // Iterate through remaining rope
        for (long long ropeBit : ropeBits) {
            rope->AddToRope(ropeBit);
        }
        
        // Iterate over children rope nodes && check
        for (RopeNode* childRopeNode : rope->GetLeafNodes()) {
            if (childRopeNode->ropeOutput == bridgeOutput)
            {
                bridgeOutputSum += bridgeOutput;
                break; // There can be multiple ways for add/multiply to result in same output
            }
        }
        free(rope);
    }
    
    //Output
    std::cout << "Bridge output sum is:" << std::endl;
    std::cout << bridgeOutputSum << std::endl;
}

void DaySeven::CrunchPartTwo(string& input)
{
    std::cout << input;
}
