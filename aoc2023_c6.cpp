#include "day6To8.h"
#include <string>
#include <iostream> //cin or printf
#include <vector> //vector
#include <algorithm> //max
#include <sstream> //stringstream
#include <cmath> // pow

void LineToNumVectBySpaces(std::string line, std::vector<int>& vec){
    std::stringstream sStream(line);
    std::string t;
    while (getline(sStream, t, ' ')) {
            // store token string in the vector
            if (!t.empty())
            {
                int actualNum = 0;
                for(int i=0; i< t.length();i++){
                    if (isdigit(t[i])){
                        actualNum = actualNum*10 + (t[i]-'0');
                    }
                }
                vec.push_back(actualNum);
            }
        }
}

int day6Part1()
{
    int prodWays = 1;
    std::string timeLine, distLine;
    getline(std::cin, timeLine);
    getline(std::cin, distLine);
    timeLine = timeLine.substr(timeLine.find(':')+1,timeLine.length()- timeLine.find(':')-1);
    distLine = distLine.substr(distLine.find(':')+1,distLine.length()- distLine.find(':')-1);
    std::vector<int> times;
    std::vector<int> recordDists;
    LineToNumVectBySpaces(timeLine, times);
    LineToNumVectBySpaces(distLine, recordDists);
    
    // each way gets a speed = time held
    // dist travelled = speed * (time-timeheld) = timeHeld * (Totime-timeHeld)
    // when 40x - x^2 > 233
    // so when -x^2 + 40x - 233 > 0
    for (int i=0; i<times.size(); i++){
        // for each race get # of ways to win
        int a = -1;
        int b = times[i];
        int c = -1 * recordDists[i];
        int discrim = std::pow(b,2) - 4*a*c;
        //printf("%d, %d, %d: %d |", a,b,c, discrim);
        int firstSol = -1;
        int secondSol = -1;
        
        if (discrim >=0){
            float sol1 = (-b + std::pow(discrim,0.5f)) / (2 * a);
            float sol2 = (-b - std::pow(discrim,0.5f)) / (2 * a);
            firstSol = std::ceil(sol1);
            secondSol = std::floor(sol2);
        }
        printf("%d, %d: ", times[i], recordDists[i]);
        printf("%d < x < %d\n", firstSol, secondSol);
        
        int ways = secondSol - firstSol +1;
        printf("%d\n", ways);
        prodWays = prodWays * ways;
    }
    return prodWays;
}

long day6Part2()
{
    // I'm too lazy to parse 2 inputs from all that
    long actualTime = 40828492;
    long recordDists = 233101111101487;
    long a = -1;
    long b = actualTime;
    long c = -1 * recordDists;
    long discrim = std::pow(b,2) - 4*a*c;
    //printf("%d, %d, %d: %d |", a,b,c, discrim);
    long firstSol = -1;
    long secondSol = -1;
    
    if (discrim >=0){
        float sol1 = (-b + std::pow(discrim,0.5f)) / (2 * a);
        float sol2 = (-b - std::pow(discrim,0.5f)) / (2 * a);
        firstSol = std::ceil(sol1);
        secondSol = std::floor(sol2);
    }
    printf("%d < x < %d\n", firstSol, secondSol);
    
    long ways = secondSol - firstSol +1;
    printf("%d\n", ways);
    return ways;
}