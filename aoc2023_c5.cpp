#include <iostream> //cin or printf
#include <string>
#include <sstream> //stringstream
#include <vector>

long day5Part1(){
    //first we want to parse the input
    // seedToSoil, then soilToFert, then fertToWater
    // then waterToLight then lightToTemp, then tempToHum, then humToLoc
    std::string line;
    std::vector<coolMap> seedToSoil, soilToFert, fertToWater, waterToLight, lightToTemp, tempToHum, humToLoc;
    const int numMaps = 7;
    std::vector<std::vector<coolMap>*> Maps = {&seedToSoil, &soilToFert, &fertToWater, 
        &waterToLight, &lightToTemp, &tempToHum, &humToLoc};
    std::vector<long> seedNums;
    std::vector<long> currNums;
    // Get Seed Numbers
    if (getline(std::cin, line)){
        line = line.substr(6, line.length()-6);
        //std::printf("%s\n", line.c_str());
        std::stringstream seedStream(line);
        
        std::string n;
        while (getline(seedStream, n, ' ')) {
            if (!n.empty())
            {
                long actualNum = 0;
                for(int i=0; i< n.length();i++){
                    actualNum = actualNum*10 + (n[i]-'0');
                }
                seedNums.push_back(actualNum);
                currNums.push_back(actualNum);
            }
        }
    }
    //Test print
    //
    for (int i=0; i<currNums.size();i++){
        printf("%ld|", currNums[i]);
    }
    printf("\n");
    //
    
    int mapNum = -1;
    while(getline(std::cin, line))
    {
        if (isdigit(line[0]) && mapNum >=0 && mapNum <numMaps){
            // first find correct map
            std::vector<coolMap>* mapToAddTo = Maps[mapNum];
            // add coolMap to that
            std::stringstream lineStream(line);
            std::string n;
            long source = -1;
            long dest = -1;
            long ran = -1;
            while (getline(lineStream, n, ' ')) {
                if (!n.empty())
                {
                    long actualNum = 0;
                    for(int i=0; i< n.length();i++){
                        actualNum = actualNum*10 + (n[i]-'0');
                    }
                    if (dest == -1){
                        dest = actualNum;
                    }
                    else if (source == -1){
                        source = actualNum;
                    }
                    else{
                        ran = actualNum;
                    }
                }
            }
            coolMap val(source, dest, ran);
            mapToAddTo->push_back(val);
        }
        // if line contains the word "map", then switch to next map
        if (line.find("map") != std::string::npos){
            mapNum++;
        }
    }
    
    // check if maps are correct?
    /*
    for (int i=0; i < numMaps; i++){
        std::vector<coolMap>* mapToCheck = Maps[i];
        int len = mapToCheck->size();
        coolMap last = mapToCheck->at(len-1);
        printf("%ld, %ld, %ld\n", last.sourceStart,last.destStart, last.rangeLen);
    }*/
    
    // go through each of the maps
    for (int i=0; i< numMaps; i++){
        printf("newMap\n");
        std::vector<coolMap>* mapToCheck = Maps[i];
        int len = mapToCheck->size();
        // for each in currNums, findDestIfMatch
        for (int j = 0; j < currNums.size(); j++ )
        {
            long currNum = currNums[j];
            long nextNum = -1;
            for (coolMap currMapping : *mapToCheck)
            {
                nextNum = currMapping.findDestIfMatch(currNum);
                if (nextNum!= -1){
                    //found it!
                    currNums[j] = nextNum;
                    break;
                }
            }
            printf("%d:%ld| ", j, currNums[j]);
            
        }
        printf("\n");
        
    }
    long lowestLoc = currNums[0];
    for (long loc : currNums){
        if (loc < lowestLoc)
        {
            lowestLoc = loc;
        }
    }
    return lowestLoc;
}

long day5Part2(){
    // Same as part 1 but currNums is ranges instead of numbers
    std::string line;
    std::vector<coolMap> seedToSoil, soilToFert, fertToWater, waterToLight, lightToTemp, tempToHum, humToLoc;
    const int numMaps = 7;
    std::vector<std::vector<coolMap>*> Maps = {&seedToSoil, &soilToFert, &fertToWater, 
        &waterToLight, &lightToTemp, &tempToHum, &humToLoc};
    std::vector<coolMap> currNums;
    
    // Get Seed Numbers
    if (getline(std::cin, line)){
        line = line.substr(6, line.length()-6);
        std::stringstream seedStream(line);
        std::string n;
        long seedSource = -1;
        long seedRange = -1;
        while (getline(seedStream, n, ' ')) {
            if (!n.empty())
            {
                long actualNum = 0;
                for(int i=0; i< n.length();i++){
                    actualNum = actualNum*10 + (n[i]-'0');
                }
                if (seedSource == -1){
                    seedSource = actualNum;
                }
                else {
                    seedRange = actualNum;
                }
                if (seedSource != -1 && seedRange != -1){
                    coolMap val(seedSource, seedRange);
                    currNums.push_back(val);
                    seedSource = -1;
                    seedRange = -1;
                }
            }
            
        }
    }
    
    int mapNum = -1;
    while(getline(std::cin, line))
    {
        if (isdigit(line[0]) && mapNum >=0 && mapNum <numMaps){
            // first find correct map
            std::vector<coolMap>* mapToAddTo = Maps[mapNum];
            // add coolMap to that
            std::stringstream lineStream(line);
            std::string n;
            long source = -1;
            long dest = -1;
            long ran = -1;
            while (getline(lineStream, n, ' ')) {
                if (!n.empty())
                {
                    long actualNum = 0;
                    for(int i=0; i< n.length();i++){
                        actualNum = actualNum*10 + (n[i]-'0');
                    }
                    if (dest == -1){
                        dest = actualNum;
                    }
                    else if (source == -1){
                        source = actualNum;
                    }
                    else{
                        ran = actualNum;
                    }
                }
            }
            coolMap val(source, dest, ran);
            mapToAddTo->push_back(val);
        }
        // if line contains the word "map", then switch to next map
        if (line.find("map") != std::string::npos){
            mapNum++;
        }
    }

    // go through each of the maps
    for (int i=0; i< numMaps; i++){
        printf("newMap\n");
        std::vector<coolMap>* mapToCheck = Maps[i];
        int len = mapToCheck->size();
        std::vector<coolMap> nextNums;
        // for each range in currNums, findDestIfMatch
        for (int j = 0; j < currNums.size(); j++ )
        {
            coolMap currNum = currNums[j];
            //printf("finding for %ld: ", currNum.sourceStart);
            coolMap nextNum;
            long destStart = 0;
            long foundRange = 0;
            std::vector<long> notFoundStarts;
            std::vector<long> notFoundRanges;
            bool didNotFindAny = true;
            for (coolMap currMapping : *mapToCheck)
            {
                if (didNotFindAny &&
                    currMapping.findDestGivenRanges(currNum.sourceStart, currNum.rangeLen,
                    destStart, foundRange, notFoundStarts, notFoundRanges))
                {
                    // At least partially found something
                    printf(" initialFind %ld, %ld, %ld ", destStart, currNum.sourceStart, foundRange);
                    printf("now finding for ranges: ");
                    
                    for (int notFoundIdx = 0; notFoundIdx< notFoundStarts.size(); notFoundIdx++)
                    {
                        printf(" %ld, %ld |", notFoundStarts[notFoundIdx], notFoundRanges[notFoundIdx]);
                    }
                    printf("\n");
                    didNotFindAny = false;
                    coolMap foundVal(destStart, foundRange);
                    nextNums.push_back(foundVal);
                }
                std::vector<int> idxToRemove;
                if (!didNotFindAny && !notFoundStarts.empty()){
                    // If notFoundStarts and notFoundRanges still have stuff, need to check those as well
                    int origSize = notFoundStarts.size();
                    /*printf("checking ");
                    for (int i=0; i< origSize; i++){
                        printf("%ld ",notFoundStarts[i]);
                        printf("%ld |",notFoundRanges[i]);
                    }
                    printf("\n");*/
                    for (int notFoundIdx = 0; notFoundIdx < origSize; notFoundIdx++)
                    {
                        if (currMapping.findDestGivenRanges(notFoundStarts[notFoundIdx], 
                        notFoundRanges[notFoundIdx], destStart, foundRange, notFoundStarts, 
                        notFoundRanges))
                        {
                            //printf("found %ld from %ld, %ld ", destStart, notFoundStarts[notFoundIdx], foundRange);
                            // At least partially found something 
                            didNotFindAny = false;
                            coolMap foundVal(destStart, foundRange);
                            nextNums.push_back(foundVal);
                            idxToRemove.push_back(notFoundIdx);
                        }
                        //printf("%d\n", notFoundIdx, notFoundStarts.size());
                    }
                    if (!idxToRemove.empty()){
                        for (int i = idxToRemove.size()-1; i>=0; i--)
                        {
                            printf("removing %d ", idxToRemove[i]);
                            notFoundStarts.erase(notFoundStarts.begin() + idxToRemove[i]);
                            notFoundRanges.erase(notFoundRanges.begin() + idxToRemove[i]);
                        }
                    }
                    
                }
            }
            if (didNotFindAny){
                nextNums.push_back(currNums[j]);
            }
            else{
                for (int notFoundIdx = 0; notFoundIdx< notFoundStarts.size(); notFoundIdx++)
                {
                    coolMap notFoundVal(notFoundStarts[notFoundIdx], notFoundRanges[notFoundIdx]);
                    nextNums.push_back(notFoundVal);
                }
            }
        }
        /*
        for (int i=0; i< nextNums.size(); i++)
        {
            printf("|%ld to %ld|", nextNums[i].sourceStart, nextNums[i].sourceStart+nextNums[i].rangeLen);
        }
        printf("\n");*/
        currNums = nextNums;
    }
    
    long lowestLoc = currNums[0].sourceStart;
    for (int i=1; i< currNums.size(); i++){
        long loc = currNums[i].sourceStart;
        if (loc < lowestLoc)
        {
            lowestLoc = loc;
        }
    }
    return lowestLoc;
}