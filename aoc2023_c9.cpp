#include "day9.h"
#include "day6To8.h"
#include <string>
#include <iostream>		//cin or printf
#include <vector>		//vector

bool getDiffOfVect(std::vector<int> vec, std::vector<int>& output)
{
    for (int i=1; i<vec.size();i++)
    {
        output.push_back(vec[i] - vec[i-1]);
    }
    for (int i=0; i<output.size();i++)
    {
        if (output[i] != 0)
        {
            return false;
        }
    }
    return true;
}

int extrapolateVec(std::vector<int> vec)
{
    std::vector<int> diffOutput;
    if (getDiffOfVect(vec, diffOutput))
    {
        // base case, no difference
        return vec[0];
    }
    else
    {
        /*printf("inEx");
        for (int i=0; i<diffOutput.size();i++)
        {
            printf("[%d]", diffOutput[i]);
        }
        printf("\n");*/
        return extrapolateVec(diffOutput) + vec[vec.size()-1];
    }
}

int extrapolateBackwardsVec(std::vector<int> vec)
{
    std::vector<int> diffOutput;
    if (getDiffOfVect(vec, diffOutput))
    {
        // base case, no difference
        return vec[0];
    }
    else
    {
        return vec[0] - extrapolateBackwardsVec(diffOutput);
    }
}

long day9(bool isPart2)
{
    long totPredictions = 0;
    std::string line;

    while (getline (std::cin, line))
    {
        std::vector<int> readings;
        LineToNumVectBySpaces(line, readings);
        /*for (int i=0; i< readings.size(); i++){
            printf("|%d", readings[i]);
        }
        printf("\n");*/
        if (!isPart2)
        {
            int prediction = extrapolateVec(readings);
            totPredictions += prediction;
        }
        else
        {
            int prediction = extrapolateBackwardsVec(readings);
            totPredictions += prediction;
        }
        
    }
    return totPredictions;
}