#include <string>
#include <iostream>		//cin or printf
#include <vector>		//vector
#include <algorithm>		//max
#include <sstream>		//stringstream
#include <cmath>		// pow
#include <map> // map

int convertNodeToInt(std::string node)
{
    if (node.size() == 3)
    {
        int nodeNumA = node[0]-'A';
        int nodeNumB = node[1]-'A';
        int nodeNumC = node[2]-'A';
        //printf("%d|%d|%d\n", nodeNumA, nodeNumB, nodeNumC);
        int retVal = nodeNumA*(26*26) + nodeNumB*(26) + nodeNumC;
        return retVal;
    }
    return -1;
}

bool allEndInZ(std::vector<int> nodes)
{
    for (int i=0; i<nodes.size(); i++)
    {
        if (nodes[i]%26 != 25)
        {
            return false;
        }
    }
    return true;
}

long gcd(long a, long b) 
{
    if (b == 0) 
    {
        return a; 
    }
    return gcd(b, a % b); 
} 

long day8(bool isPart2)
{
    long numSteps = 0;
    std::string line;
    std::string puncToIgnore = " =(,)";
    std::map<int, std::pair<int, int>> graph;
    
    std::string instructions;
    getline (std::cin, instructions);
    int instructSize = instructions.length();
    std::vector<int> currNodes;
    while (getline (std::cin, line))
    {
        std::vector<std::string> node;
        
        LineToVectBySpacesIgnoringPunct(line, node, puncToIgnore);
        if (node.size() == 3)
        {
            //printf("%s,%s,%s|%d\n", node[0].c_str(),node[1].c_str(),node[2].c_str(),node.size());
            // let's convert + save them as base 10 int so AAA = 0 and ZZZ = 26^2 + 26^1 + 26
            std::pair<int,int> nodeOut(convertNodeToInt(node[1]),convertNodeToInt(node[2]));
            int nodeNum = convertNodeToInt(node[0]);
            if (isPart2 && nodeNum%26 == 0){
                printf("A: %d\n", nodeNum);
                currNodes.push_back(nodeNum);
            }
            graph.emplace(nodeNum, nodeOut);
            
        }
    }
    
    int instructIdx = 0;
    if (!isPart2)
    {
        int currNode = 0;
        
        while (currNode != 17575) // not ZZZ
        {
            // find base node, then if L use first, if right use second of pair
            std::map<int, std::pair<int, int>>::iterator it = graph.find(currNode);
            if (it != graph.end())
            {
                if (instructions[instructIdx] == 'L')
                {
                    currNode = it->second.first;
                }
                else
                {
                    currNode = it->second.second;
                }
                instructIdx++;
                if (instructIdx >= instructSize)
                {
                    instructIdx = 0;
                }
                numSteps++;
            }
            else
            {
                printf("ONNNO");
                break;
            }
        }
    
        return numSteps;
    }
    
    // Part 2  find numSteps for all nodes ending with A to simultaniously go to node ending in Z
    bool done = false;
    bool error = false;
    // loop until we go back to start for each node
    std::vector<int> numStepsToGetZ; // number of steps to get Z
    for (int i=0; i<currNodes.size(); i++){
        std::vector<int> emptyVector;
        //numStepsToGetZ.push_back(emptyVector);
        numStepsToGetZ.push_back(-1);
    }
    
    while (!allEndInZ(currNodes) && !done && !error)
    {
        for (int i = 0; i < currNodes.size(); i++){
            // for each of the current nodes
            int currNode = currNodes[i];
            if (currNode%26 == 25)
            {
                numStepsToGetZ[i] = numSteps;
            }
            std::map<int, std::pair<int, int>>::iterator it = graph.find(currNode);
            if (it != graph.end())
            {
                if (instructions[instructIdx] == 'L')
                {
                    currNodes[i] = it->second.first;
                }
                else
                {
                    currNodes[i] = it->second.second;
                }
            }
            else
            {
                printf("ONNO\n");
                error = true;
                break;
            }
        }

        // check if we've looped back yet
        int numAlreadyFilled = 0;
        for (int i=0; i< currNodes.size(); i++)
        {
            if (numStepsToGetZ[i] != -1)
            {
                numAlreadyFilled++;
            }
        }
        if (numAlreadyFilled == currNodes.size())
        {
            done = true;
            break;
        }
        
        instructIdx++;
        if (instructIdx >= instructSize)
        {
            instructIdx = 0;
        }
        numSteps++;
        
    }
    if (done)
    {
        long LCM = 1;
        for (int i=0; i<currNodes.size();i++)
        {
            long GCD = gcd(LCM, numStepsToGetZ[i]);
            LCM = (LCM / GCD)* numStepsToGetZ[i];
        }
        // need to find gcd of all numbers, then use that for lcm
        return LCM;
    }
    return numSteps;
}
