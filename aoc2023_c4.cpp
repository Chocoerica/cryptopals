#include <iostream> //cin or printf
#include <string>
#include <sstream> //stringstream
#include <vector>

int day4Part1(){
    int points;
    std::string line;
    while(getline(std::cin, line))
    {
        // part 1: splice between : and |
        int colonPos = line.find(':');
        int linePos = line.find('|');
        std::string winningNumStr = line.substr(colonPos + 2, linePos-colonPos-2);
        std::string cardNumStr = line.substr(linePos + 2, line.length()-colonPos -1);
        //printf("%s\n", line.c_str());
        
        // part 2: splice between spaces to get all numbers into an array
        std::stringstream winNumsStream(winningNumStr);
        std::vector<int> winNums;
        std::string num;
        while (getline(winNumsStream, num, ' ')) {
            // store token string in the vector
            if (!num.empty())
            {
                int actualNum = 0;
                for(int i=0; i< num.length();i++){
                    actualNum = actualNum*10 + (num[i]-'0');
                }
                winNums.push_back(actualNum);
            }
        }
        std::stringstream cardNumStream(cardNumStr);
        std::vector<int> cardNums;
        std::string n;
        while (getline(cardNumStream, n, ' ')) {
            if (!n.empty())
            {
                int actualNum = 0;
                for(int i=0; i< n.length();i++){
                    actualNum = actualNum*10 + (n[i]-'0');
                }
                cardNums.push_back(actualNum);
            }
        }
        /*
        for (int i=0; i<winNums.size();i++){
            printf("|%d", winNums[i]);
        }
        printf("\n");
        for (int i=0; i<cardNums.size();i++){
            printf("|%d", cardNums[i]);
        }
        printf("\n");
        */
        // part 3: get matches between two lists
        int cardPoint = 0;
        for (int winNum: winNums)
        {
            if(std::find(cardNums.begin(), cardNums.end(), winNum) != cardNums.end())
            {
                //printf("Match ");
                if(cardPoint == 0)
                {
                    cardPoint = 1;
                }
                else
                {
                    cardPoint = cardPoint*2;
                }
            }
        }
        //printf("%d\n", cardPoint);
        points += cardPoint;
    }
    return points;
}

int day4Part2(){
    int totCards = 0;
    std::vector<int> numCards(192, 1);
    std::string line;
    int cardIdx = 0;
    while(getline(std::cin, line))
    {
        // part 1: splice between : and |
        int colonPos = line.find(':');
        int linePos = line.find('|');
        
        std::string winningNumStr = line.substr(colonPos + 2, linePos-colonPos-2);
        std::string cardNumStr = line.substr(linePos + 2, line.length()-colonPos -1);
        
        std::stringstream winNumsStream(winningNumStr);
        std::vector<int> winNums;
        std::string num;
        while (getline(winNumsStream, num, ' ')) {
            // store token string in the vector
            if (!num.empty())
            {
                int actualNum = 0;
                for(int i=0; i< num.length();i++){
                    actualNum = actualNum*10 + (num[i]-'0');
                }
                winNums.push_back(actualNum);
            }
        }
        std::stringstream cardNumStream(cardNumStr);
        std::vector<int> cardNums;
        std::string n;
        while (getline(cardNumStream, n, ' ')) {
            if (!n.empty())
            {
                int actualNum = 0;
                for(int i=0; i< n.length();i++){
                    actualNum = actualNum*10 + (n[i]-'0');
                }
                cardNums.push_back(actualNum);
            }
        }
        
        // Get num matches between two lists
        int numMatches = 0;
        for (int winNum: winNums)
        {
            if(std::find(cardNums.begin(), cardNums.end(), winNum) != cardNums.end())
            {
                numMatches++;
            }
        }
        //printf("%d: %d*%d=", cardIdx, numCards[cardIdx], numMatches);
        // numMatches is how many of the cards you have to add numCopies (numCards[cardIdx] to
        for (int i=0; i<numMatches; i++){
            int idxToChange = cardIdx + i + 1;
            if (idxToChange < 192)
            {
                numCards[idxToChange]+= numCards[cardIdx];
                //printf("|%d|", idxToChange);
            }
        }
        cardIdx++;
    }
    for(int i=0; i<192; i++){
        totCards += numCards[i];
    }
    return totCards;
}


int main()
{
    printf("%d\n", day4Part2());
    return 0;
}