#include <string>
#include <iostream>		//cin or printf
#include <vector>		//vector

long day11(bool isPart2)
{
    // empty rows are twice as big, empty columns are twice as big
    std::string universeRow;
    long sumPaths = 0;
    std::vector<bool> isColumnEmpty; // on first row, figure out how many colums
    bool first = true;
    long actualRowNum=0;
    std::vector<std::pair<int,int>> uniCoords; // in this case, do (y,x)
    while (getline (std::cin, universeRow))
    {
        if (first)
        {
            isColumnEmpty = std::vector<bool>(universeRow.length(), true);
            first = false;
        }
        bool rowEmpty = true;
        for (int i=0; i<universeRow.length(); i++)
        {
            if (universeRow[i]== '#')
            {
                rowEmpty = false;
                isColumnEmpty[i] = false;
                uniCoords.push_back(std::pair<int,int>(actualRowNum, i));
            }
        }
        // row expansion is easy, do now; column do later
        if (rowEmpty)
        {
            if (isPart2)
            {
                actualRowNum += 1000000;
            }
            else
            {
                actualRowNum += 2;
            }
        }
        else
        {
            actualRowNum++;
        }
        
    }
    
    //already row expanded, now need to adjust column coords of uniCoords
    std::vector<int> columnsEmpty; // ordered column numbers of empty columns
    for (int i=0; i< isColumnEmpty.size(); i++)
    {
        if (isColumnEmpty[i] == true)
        {
            columnsEmpty.push_back(i);
            printf("%d|",i);
        }
    }
    printf("\n");
    
    // for each uniCoords (y,x), check find r for largest r<x in columnsEmpty, 
    // index = how many to add to x for real x value
    std::vector<int>::iterator it;
    int allEmptyCols = columnsEmpty.size();
    for (int i=0; i < uniCoords.size();i++)
    {
        //printf("(%d,%d)", uniCoords[i].first, uniCoords[i].second);
        int oldColumnVal = uniCoords[i].second;
        int max_value = 6;
        it = std::lower_bound(columnsEmpty.begin(), columnsEmpty.end(), oldColumnVal);
        // (it - columnsEmpty.begin()) is actual number of columns to double
        if (it != columnsEmpty.end())
        {
            if (isPart2)
            {
                uniCoords[i].second += (it-columnsEmpty.begin()) * 999999;
            }
            else
            {
                uniCoords[i].second += it-columnsEmpty.begin();
            }
            
        }
        else 
        {
            if (isPart2)
            {
                uniCoords[i].second += allEmptyCols * 999999;
            }
            else
            {
                uniCoords[i].second += allEmptyCols;
            }
            
        }
        //printf("= (%d, %d)\n",uniCoords[i].first, uniCoords[i].second);
    }
    
    // path bet 2 points = (x2-x1) + (y2-y1)
    // find sum of all paths between every pair of universes
    for (int i=0; i < uniCoords.size()-1;i++)
    {
        for (int j = i+1; j<uniCoords.size();j++)
        {
            long path = abs(uniCoords[i].first - uniCoords[j].first) + abs(uniCoords[i].second - uniCoords[j].second);
            sumPaths+= path;
        }
    }
    return sumPaths;
}