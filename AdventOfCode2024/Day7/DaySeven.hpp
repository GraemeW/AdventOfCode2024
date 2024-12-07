//
//  DaySeven.hpp
//  AdventOfCode2024
//
#pragma once
#include <stdio.h>
#include <string>
#include <vector>
#include "../Day.h"

#ifndef DaySeven_hpp
#define DaySeven_hpp
class DaySeven : public Day
{
private:
    // Tunables
    string inputPath = "Resources/DaySevenInput.txt";
    
    // Methods
    long long GenerateEquationParts(string const& line, std::deque<int>& ropeBits);
    
public:
    // Methods
    void CrunchPartOne(string& input) override;
    void CrunchPartTwo(string& input) override;
    string GetInputPath() override { return inputPath; }
};

class RopeNode {
public:
    // Properties
    long long ropeOutput;
    RopeNode* addChild;
    RopeNode* multiplyChild;

    RopeNode(long long value) : ropeOutput(value), addChild(nullptr), multiplyChild(nullptr) {}
    
    ~RopeNode()
    {
        free(addChild);
        free(multiplyChild);
    }
};

class Rope {
private:
    RopeNode* root; // root node
    std::vector<RopeNode*> leafNodes;
public:
    Rope(long long initialRope) {
        root = new RopeNode(initialRope);
    };
    
    ~Rope() { free(root); }
    
    void AddToRope(long long nextRopeBit);
    RopeNode* GetRootRopeNode() { return root; }
    std::vector<RopeNode*> GetLeafNodes() { return leafNodes; }
};
#endif /* DaySeven_hpp */
