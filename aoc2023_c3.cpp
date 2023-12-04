#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

void GetNumsOfLine(std::string &line, std::vector<int>& nums, std::vector<int> &startIdx, std::vector<int> &endIdx){
    // part 1 get numbers in line
    // part 2 get start and end idx of numbers
    char prevChar= '.';
    int currNum = 0;
    char c;
    const int linLen = 140;
    for (int i=0; i< linLen; i++)
    {
        c = line[i];
        if (isdigit(c))
        {
            if (!isdigit(prevChar))
            {
                //start new number
                //printf("AAA ");
                currNum = (c - '0');
                startIdx.push_back(i);
            }
            else{
                //continue current number
                currNum = currNum*10 + (c - '0');
            }
        }
        else{
            // see if ending a number
            if (isdigit(prevChar))
            {
                nums.push_back(currNum);
                endIdx.push_back(i-1);
            }
        }
        prevChar = c;
    }
    // check last char
    if (isdigit(c))
    {
        nums.push_back(currNum);
        endIdx.push_back(139);
    }
}

int sumNumsCompareLines(std::string line, std::string upper, std::string lower, std::vector<int> nums, std::vector<int> startIndexes, std::vector<int> endIndexes)
{
    int sums = 0;
    // Given nums, start and end idx
    // see if there's a symbol in lines, upper or lower between startidx-1 to endidx+1
    // check if upper or lower are empty before doing anything
    for (int i=0; i< nums.size(); i++)
    {
        bool isPartNum = false;
        int startIdx = startIndexes[i];
        int endIdx = endIndexes[i];
        //check on same line
        if (startIdx - 1 >= 0 && !isdigit(line[startIdx-1]) && line[startIdx-1] != '.')
        {
            //printf("|Left%d|",startIdx-1);
            isPartNum = true;
        }
        if (endIdx + 1 <= 139 && !isdigit(line[endIdx+1]) && line[endIdx + 1] != '.')
        {
            //printf("|Right%d|", endIdx+1);
            isPartNum = true;
        }
        if (!isPartNum)
        {
            int startCheck = std::max(0,startIdx - 1);
            int endCheck = std::min(139, endIdx + 1);
            for (int idx = startCheck; idx<= endCheck; idx++){
                if(!upper.empty() && !isdigit(upper[idx]) && upper[idx] != '.')
                {
                    //printf("|upper%d|", idx);
                    isPartNum = true;
                    break;
                }
                if (!lower.empty() && !isdigit(lower[idx]) && lower[idx] != '.'){
                    //printf("|lower%d|", idx);
                    isPartNum = true;
                    break;
                }
            }
        }
        if (isPartNum)
        {
            //printf("%d ", nums[i]);
            sums += nums[i];   
        }
    }
    //printf("\n");
    return sums;
}

int day3Part1(){
    int sum = 0;
    std::string curr, prev, pp; //pp = prevprev
    const int linLen = 140;
    //int x=1;
    std::vector<int> nums, startIdx, endIdx;
    // we want to compare each line w/ it's prev and next lines
    // Or get curr line, then GetNums of prev, compare with curr and prev prev
    while(getline(std::cin, curr))
    {
        if (!prev.empty()){
            nums.clear();
            startIdx.clear();
            endIdx.clear();
            GetNumsOfLine(prev, nums, startIdx, endIdx);
            //printf("%s\n", prev.c_str());
            /*for (int i=0; i<nums.size(); i++)
            {
                printf("%d; ", nums[i]);
                //printf("%d %d %d; ", nums[i], startIdx[i], endIdx[i]);
            }
            printf("\n");
            */
            // part 3 for each num: compare with left, right
            // compare with prev with pp and prev with curr
            sum += sumNumsCompareLines(prev, pp, curr, nums, startIdx, endIdx);
        }
        pp = prev;
        prev = curr;
        //x++;
    }
    std::string emptyStr;
    // do compare with last line as well -> prev with pp
    nums.clear();
    startIdx.clear();
    endIdx.clear();
    GetNumsOfLine(curr, nums, startIdx, endIdx);
    //printf("%s\n", curr.c_str());
    sum += sumNumsCompareLines(curr, pp, emptyStr, nums, startIdx, endIdx);
    return sum;
}

int FindGears(std::string line, 
    std::vector<int> prevNums, std::vector<int> prevStartIndices, std::vector<int> prevEndIndices,
    std::vector<int> currNums, std::vector<int> currStartIndices, std::vector<int> currEndIndices,
    std::vector<int> nextNums, std::vector<int> nextStartIndices, std::vector<int> nextEndIndices)
{
    int sumProd = 0;
    
    // if get * on a line, see how many adjacent numbers
    for (int i = 0; i< 140; i++)
    {
        char c = line[i];
        if (c == '*')
        {
            
            int product = 1;
            int numAdjacent = 0;
            if (!prevNums.empty()){
                //see how many adjacent numbers
                // Doing a whole loop over all numbers doesn't take too long
                //... 
                //.*.
                //...
                //PREV
                for (int k = 0; k< prevStartIndices.size();k++)
                {
                    // start <= i+1 && end >= i-1
                    if (prevStartIndices[k] <= i+1 && prevEndIndices[k] >= i-1)
                    {
                        //printf("Prev(%d:%d:%d)", prevNums[k], prevStartIndices[k],prevEndIndices[k]);
                        numAdjacent++;
                        product = product * prevNums[k];
                    }
                }
                //CURR
            }
            for (int k = 0; k< currStartIndices.size();k++)
            {
                if (currStartIndices[k] == i+1 || currEndIndices[k] == i-1)
                {
                    //printf("curr(%d:%d:%d)", currNums[k], currStartIndices[k],currEndIndices[k]);
                    numAdjacent++;
                    product = product * currNums[k];
                }
            }
            if (!nextNums.empty())
            {
                //NEXT
                for (int k = 0; k< nextStartIndices.size();k++)
                {
                    if (nextStartIndices[k] <= i+1 && nextEndIndices[k] >= i-1)
                    {
                        //printf("next(%d:%d:%d)", nextNums[k], nextStartIndices[k],nextEndIndices[k]);
                        numAdjacent++;
                        product = product * nextNums[k];
                    }
                }
            }
            // if adjacent numbers == 2, return their product
            if (numAdjacent == 2)
            {
                sumProd += product;
            }
            //printf("\n");
        }
    }
    return sumProd;
    
}

int day3Part2(){
    // multiply two numbers where * is adjacent to exactly 2 numbers
    int sum = 0;
    std::string curr, prev, next;
    const int linLen = 140;
    //int x=1;
    std::vector<int> prevNums, prevStartIndices, prevEndIndices;
    std::vector<int> currNums, currStartIndices, currEndIndices;
    std::vector<int> nextNums, nextStartIndices, nextEndIndices;
    // we want to compare triples - curr, prev, next
    // Or get next line, GetNums of prev, curr, and next
    // Get Gear Ratios given *s of curr
    while(getline(std::cin, next))
    {
        // Get Data for Next
        nextNums.clear();
        nextStartIndices.clear();
        nextEndIndices.clear();
        GetNumsOfLine(next, nextNums, nextStartIndices, nextEndIndices);
        
        if (!curr.empty())
        {
            //compare prev, curr, next

            // part 3 for each num: compare with left, right
            // compare with curr with prev and next
            sum += FindGears(curr, prevNums, prevStartIndices, prevEndIndices, 
            currNums, currStartIndices, currEndIndices, 
            nextNums, nextStartIndices, nextEndIndices);
        }
        
        prev = curr;
        curr = next;
        // also move nums and EndIndices and StartIndices
        prevNums = currNums;
        prevEndIndices = currEndIndices;
        prevStartIndices = currStartIndices;
        currNums = nextNums;
        currEndIndices = nextEndIndices;
        currStartIndices = nextStartIndices;
        //x++;
    }
    std::string emptyStr;
    // do compare with prev and curr
    currNums.clear();
    currStartIndices.clear();
    currEndIndices.clear();
    nextNums.clear();
    nextStartIndices.clear();
    nextEndIndices.clear();
    GetNumsOfLine(curr, currNums, currStartIndices, currEndIndices);
    sum += FindGears(curr, prevNums, prevStartIndices, prevEndIndices, 
            currNums, currStartIndices, currEndIndices, 
            nextNums, nextStartIndices, nextEndIndices);
    return sum;
}

int main()
{
    //printf("%d\n", day3Part1());
    printf("%d\n", day3Part2());
    return 0;
}