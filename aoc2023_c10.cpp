#include <string>
#include <iostream>		//cin or printf
#include <vector>		//vector
#include <map> // map

std::pair<int,int> findNextDirection(std::vector<std::string>& maze, std::pair<int,int> coords, char& prevDir)
{
    char pipeSegment;
    pipeSegment = maze[coords.second][coords.first];
    // pipeSegment | = north and south.
    // - = east west
    // L = north east
    // J = north west
    // 7 = south west
    // F = south east
    // . = no pipe, S = start
    // given prevDir and pipeSegment, get next direction 
    char nextDir;
    std::map<char,char> directions;
    switch(prevDir)
    {
    case 'N':
        // From north - L = East, J = West,| = South
        directions= {{'L','E'},{'J','W'},{'|','S'}};
        break;
    case 'S':
        // From south - F = East, 7 = West,| = North
        directions= {{'F','E'},{'7','W'},{'|','N'}};
        break;
    case 'E':
        // From East - L = North, F = South, - = West
        directions= {{'L','N'},{'F','S'},{'-','W'}};
        break;
    case 'W':
        // From West - 7 = South, J = North, - = East
        directions= {{'7','S'},{'J','N'},{'-','E'}};
        break;
    }
    auto it = directions.find(pipeSegment);
    if (it != directions.end())
    {
        nextDir = it->second;
    }
    //printf(" was %c going %c \n", prevDir, nextDir);
    std::map<char,char> oppositeDir = {{'N','S'},{'S','N'},{'W','E'},{'E','W'}};
    auto it2 = oppositeDir.find(nextDir);
    if (it2 != oppositeDir.end())
    {
        prevDir = it2->second;
    }
    
    // Now given nextDir, return new coords
    
    std::pair<int,int> retCoords;
    switch(nextDir)
    {
    case 'N':
        retCoords = {coords.first, coords.second - 1};
        break;
    case 'S':
        retCoords = {coords.first, coords.second + 1};
        break;
    case 'E':
        retCoords = {coords.first + 1, coords.second};
        break;
    case 'W':
        retCoords = {coords.first - 1, coords.second};
        break;
    }
    return retCoords;
}

long day10(bool isPart2)
{
    std::vector<std::string> maze;
    std::string row;
    std::pair<int,int> start(-1,-1);
    int rowNum = 0;
    while (getline (std::cin, row))
    {
        for (int i=0; i<row.length(); i++)
        {
            char pipeSegment = row[i];
            
            // turn row into vector
            if (pipeSegment == 'S')
            {
                start.first = i; //east to west
                start.second = rowNum; // north to south
            }
        }
        rowNum++;
        maze.push_back(row);
    }
    std::vector<std::vector<char>> maze2(rowNum, std::vector<char>(maze[0].length(),'0')); // to mark loop for part 2
    maze2[start.second][start.first]= '*';
    
    //printf("S:%d|%d\n", start.first, start.second);
    // see 4 sides of S to find next 2 parts
    
    char prevPart1Direction, prevPart2Direction;
    std::pair<int,int> part1(-1,-1);
    std::pair<int,int> part2(-1,-1);
    if (start.first - 1 > 0)
    {
        // look at west -,L or F
        char pipeSegment = maze[start.second][start.first-1];
        if (pipeSegment == '-' || pipeSegment == 'L'|| pipeSegment == 'F')
        {
            prevPart1Direction = 'E';
            part1.first = start.first - 1;
            part1.second = start.second;
        }
    }
    if (start.first + 1 < maze[0].size())
    {
        // look at east
        char pipeSegment = maze[start.second][start.first+1];
        if (pipeSegment == '-' || pipeSegment == 'J'|| pipeSegment == '7')
        {
            if (part1.first == -1)
            {
                prevPart1Direction = 'W';
                part1.first = start.first + 1;
                part1.second = start.second;
            }
            else 
            {
                prevPart2Direction = 'W';
                part2.first = start.first + 1;
                part2.second = start.second;
            }
        }
    }
    if (start.second - 1 > 0)
    {
        // look at north
        char pipeSegment = maze[start.second - 1][start.first];
        if (pipeSegment == '|' || pipeSegment == '7'|| pipeSegment == 'F')
        {
            if (part1.first == -1)
            {
                prevPart1Direction = 'S';
                part1.first = start.first;
                part1.second = start.second - 1;
            }
            else
            {
                prevPart2Direction = 'S';
                part2.first = start.first;
                part2.second = start.second - 1;
            }
        }
    }
    if (start.second + 1 < maze.size())
    {
        // look at south
        char pipeSegment = maze[start.second + 1][start.first];
        if (pipeSegment == '|' || pipeSegment == 'L'|| pipeSegment == 'J')
        {
            if (part1.first == -1)
            {
                prevPart1Direction = 'N';
                part1.first = start.first;
                part1.second = start.second + 1;
            }
            else
            {
                prevPart2Direction = 'N';
                part2.first = start.first;
                part2.second = start.second + 1;
            }
        }
    }
    printf("1:%d|%d\n", part1.first, part1.second);
    printf("2:%d|%d\n", part2.first, part2.second);
    maze2[part1.second][part1.first]= '*';
    maze2[part2.second][part2.first]= '*';
    
    bool finishedLoop = false;
    long stepNum = 0;
    std::pair<int,int> prevPart1(-1,-1);

    // either part1 == part2 done now or part2 = prevPart1 already done
    while (!finishedLoop)
    {
        // check if finished
        if (part2.first == prevPart1.first && part2.second == prevPart1.second)
        {
            finishedLoop = true;
            break;
        }
        if (part1.first == part2.first && part1.second == part2.second)
        {
            finishedLoop = true;
            stepNum++;
            break;
        }
        // move part1 and 2 to next ones
        // given, prevPart1Direction, prevPart2Direction;
        // look at next direction given what pipe is
        part1 = findNextDirection(maze, part1, prevPart1Direction);
        part2 = findNextDirection(maze, part2, prevPart2Direction);
        if (isPart2)
        {
            maze2[part1.second][part1.first]= '*';
            maze2[part2.second][part2.first]= '*';
        }
        //printf("(%d,%d) (%d,%d)\n", part1.first, part1.second, part2.first, part2.second);
        stepNum++;
    }
    if (!isPart2)
    {
        return stepNum;
    }
    
    // Part 2 looking at what's inside by seeing vertical lines
    long numFilled = 0;
    for (int i=0;i<maze2.size();i++)
    {
        bool inside = false;
        char prevBend = 'L';
        for (int j=0; j<maze2[0].size();j++)
        {
            if (maze2[i][j] == '*')
            {
                char thing = maze[i][j];
                if (thing != '-')
                //FJ, L7 = vertical pipe, as well as |
                {
                    if ((thing == 'J' && prevBend == 'F') || (thing == '7' && prevBend == 'L') || thing == '|')
                    {
                        inside = !inside;
                    }
                    prevBend = thing;
                }
                
            }
            else if (inside)
            {
                maze2[i][j] = 'X';
                numFilled++;
            }
        }
    }
    
    /*for (int i=0;i<maze2.size();i++)
    {
        for (int j=0; j<maze2[0].size();j++)
        {
            if (maze2[i][j] == '*')
            {
                printf("%c", maze[i][j]);
            }
            else
            {
                printf("%c",maze2[i][j]);
            }
        }
        printf("\n");
    }*/
    return numFilled;    
}