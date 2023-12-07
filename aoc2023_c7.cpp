#include "day6To8.h"
#include <string>
#include <iostream> //cin or printf
#include <vector> //vector
#include <algorithm> //max
#include <sstream> //stringstream
#include <cmath> // pow
#include <map> // map

class cardHand
{
public:
    const int NUMCARDS = 5;
    std::vector<int> cards {-1,-1,-1,-1,-1};
    HandType handType;
    bool itsJokerTime;
    
    cardHand (std::string inputSuits, bool isItJokerTime)
    {
        itsJokerTime = isItJokerTime; // if True, use Joker rules
        const std::map < char, int >suitToInt{{'A', 14}, {'K', 13}, {'Q', 12},
            {'J', 11}, {'T', 10}};
        const std::map < char, int >jSuitToInt{{'A', 14}, {'K', 13}, {'Q', 12},
            {'J', 1}, {'T', 10}};
        // Take the first 5 characters of the input as ints
        for (int i = 0; i < NUMCARDS; i++)
        {
            char inputCard = inputSuits[i];
            if (isdigit (inputCard))
            {
                this->cards[i] = (inputCard - '0');
            }
            else
            {
                if (itsJokerTime)
                {
                    int cardNum = jSuitToInt.find(inputCard)->second;
                    this->cards[i] = cardNum;
                }
                else
                {
                    int cardNum = suitToInt.find(inputCard)->second;
                    this->cards[i] = cardNum;
                }
                
            }
        } 

        // Identify type
        // 5 of a kind - AAAAA
        // 4 of a kind - AAAA0 or 0AAAA
        // 3 of a kind - AAA00 or 00AAA -> can then also check for full FullHouse
        // pairs are harder AA000 or 0AA00 or 00AA0 or 000AA
        handType = HandType::HighCard;
        int numPairs = 0;
        int numJokers = 0;
        for (int i=0; i < NUMCARDS; i++)
        {
            if (cards[i] == 1)
            {
                numJokers++;
            }
        }
        for (int i=0; i<NUMCARDS-1; i++)
        {
            int matches = 0;
            int currCard = cards[i];
            
            for (int j=i+1; j<NUMCARDS; j++)
            {
                if (currCard == cards[j])
                {
                    if ((itsJokerTime && currCard != 1)||(itsJokerTime && cards[j] != 1))
                    {
                        matches++;
                    }
                    else if (!itsJokerTime)
                    {
                        matches++;
                    }
                }
            }
            if (handType != HandType::FiveOfaKind)
            {
                if (matches == 4)
                {
                    handType = HandType::FiveOfaKind;
                }
                else if (matches == 3)
                {
                    handType = HandType::FourOfaKind;
                }
                else if (handType != HandType::FourOfaKind && matches == 2)
                {
                    handType = HandType::ThreeOfaKind;
                }
                else if (handType != HandType::FourOfaKind && matches == 1)
                {
                    numPairs++;
                }
            }
        }
        // so numPairs 
        if (handType == HandType::ThreeOfaKind)
        {
            if (numPairs == 2) // it will get an extra pair from triplet
            {
                handType = HandType::FullHouse;
            }
        }
        else{
            if (numPairs == 2)
            {
                handType = HandType::TwoPair;
            }
            else if (numPairs == 1)
            {
                handType = HandType::OnePair;
            }
        }
        if (itsJokerTime && numJokers > 0)
        {
            // joker time can only improve hands
            //printf("%d\n", handType);
            if (handType == HandType::FourOfaKind && numJokers == 1 ||
                handType == HandType::ThreeOfaKind && numJokers == 2 ||
                handType == HandType::OnePair && numJokers == 3 ||
                handType == HandType::HighCard && numJokers == 4 ||
                handType == HandType::HighCard && numJokers == 5)
            {
                handType = HandType::FiveOfaKind;
            }
            else if (handType == HandType::ThreeOfaKind && numJokers == 1 ||
                    handType == HandType::OnePair && numJokers == 2 ||
                    handType == HandType::HighCard && numJokers == 3)
            {
                handType = HandType::FourOfaKind;
            }
            else if (handType == HandType::TwoPair && numJokers == 1 ||
                    handType == HandType::OnePair && numJokers == 2 ||
                    handType == HandType::OnePair && numJokers == 3)
            {
                handType = HandType::FullHouse;
            }
            else if (handType == HandType::OnePair && numJokers == 1 ||
                    handType == HandType::HighCard && numJokers == 2)
            {
                handType = HandType::ThreeOfaKind;
            }
            else if (handType == HandType::HighCard && numJokers == 1)
            {
                handType = HandType::OnePair;
            }
        }
    }
    
    void print()
    {
        printf("[%d]", this->handType);
        for (int i=0; i<NUMCARDS; i++)
        {
            int ci = this->cards[i];
            if (itsJokerTime && ci == 1)
            {
                printf("J", ci);
            }
            else if (ci < 10 )
            {
                printf("%d", ci);
            }
            else if (ci == 10){
                printf("T");
            }
            else if (ci == 11 ){
                printf("J");
            }
            else if (ci == 12){
                printf("Q");
            }
            else if (ci == 13){
                printf("K");
            }
            else if (ci == 14){
                printf("A");
            }
        }
        printf("|");
    }
    
    bool operator< (const cardHand & rhs) const
    {
        if (this->handType != rhs.handType)
        {
            return (this->handType < rhs.handType);
        }
        else
        {
            for (int i = 0; i < NUMCARDS; i++)
            {
                char thisCard = this->cards[i];
                char rhsCard = rhs.cards[i];
                if (thisCard != rhsCard)
                {
            	    // compare based on A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2
            	    return (this->cards[i] < rhs.cards[i]);
                }
            }
        }
        // both are equal, return false
        return false;
    }
    
    cardHand& operator=(const cardHand& rhs)
    {
        handType = rhs.handType;
        for (int i=0; i< NUMCARDS; i++)
        {
            cards[i] = rhs.cards[i];
        }
        return *this;
    }
    ~cardHand ()
    {
        for (int i = 0; i < NUMCARDS; i++)
        {
            this->cards[i] = -1;
        }
    }
};
    
long day7(bool isPart2)
{
    long totWinnings = 0;
    std::string line;
    
    std::vector<cardHand> hands;
    std::vector<int> bids;
    //int x = 0;
    while (getline (std::cin, line))
    {
        int spaceIdx = line.find(' ');
        std::string actualHandStr = line.substr (0,5);
        std::string bidStr = line.substr(spaceIdx + 1, line.length()-spaceIdx-1);
        
        cardHand actualHand(actualHandStr, isPart2);
        hands.push_back(actualHand);
        
        LineToNumVectBySpaces(bidStr, bids);
        //x++;
    }
    
    // Get Ranking
    std::vector<std::pair<cardHand, int>> rankedHands;
    for (int i=0; i< hands.size(); i++)
    {
        std::pair<cardHand, int> handToOriginalIdx{hands[i], i};
        rankedHands.push_back(handToOriginalIdx);
    }

    std::sort(rankedHands.begin(), rankedHands.end(), 
        [] (const std::pair<cardHand, int>& lhs, const std::pair<cardHand, int>& rhs) 
            {return lhs.first < rhs.first;});
    
    // given original index, rearrange to get rankings
    std::vector<int> rankings(rankedHands.size());
    for (int i=0; i< rankedHands.size(); i++)
    {
        // here, i is the ranking, rankedHands[i].second() is idx
        int idx = rankedHands[i].second;
        rankings[idx] = i+1;
    }
    
    for (int i=0; i < hands.size(); i++)
    {
        hands[i].print();
        totWinnings += bids[i] * rankings[i];
        printf(" %d |", bids[i]);
        printf(" %d | %ld | %ld", rankings[i], bids[i] * rankings[i], totWinnings);
        printf("\n");
    }
    return totWinnings;
}