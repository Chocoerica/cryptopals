
#include <iostream>
#include <string>
#include  <bits/stdc++.h> 

int part1(){
    int sum = 0;
    
    std::string line;
    while(getline(std::cin, line))
    {
        int colonPos = line.find(':');
        std::string gameStr = line.substr(5, colonPos-5);   
        //printf("%s\n", gameStr.c_str());
        
        bool anySubsetInvalid = false;
        
        line = line.substr(colonPos + 2, line.length()-colonPos -1);
        int foundPos = line.find(';');
        int subLen = 0;
        std::string subset;
        while (line.length() > 0 && anySubsetInvalid == false)
        {
            if (foundPos == std::string::npos)
            {
                subset = line;
                //printf("%s | %d \n", subset.c_str(), foundPos);
                line = "";
            }
            else{
                subset = line.substr(0, foundPos); 
                line = line.substr(foundPos + 2, line.length()-2-foundPos);
                //printf("%s | %d | %s\n", subset.c_str(), foundPos, line.c_str());
                foundPos = line.find(';');
            }
            // Given subset, parse how many red, green, blue
            std::string ssSet, colour, number;
            int num;
            int foundPos2=-1;
            while (subset.length() > 0 && anySubsetInvalid == false){
                foundPos2 = subset.find(',');
                if (foundPos2 == std::string::npos)
                {
                    ssSet = subset;
                    //printf("%s-%d\n", ssSet.c_str(), foundPos2);
                    subset = "";
                }
                else{
                    ssSet = subset.substr(0, foundPos2); 
                    subset = subset.substr(foundPos2 + 2, subset.length()-2-foundPos2);
                    foundPos2 = subset.find(',');
                }
                
                foundPos2 = ssSet.find(' ');
                colour = ssSet.substr(foundPos2+1, ssSet.length()-1-foundPos2);
                number = ssSet.substr(0, foundPos2);
                num = std::stoi(number);
                //printf("//%s//%s//%d//%d\n", colour.c_str(), number.c_str(), num, foundPos2);
                if (colour == "red" && num > 12)
                {
                    anySubsetInvalid = true;
                }
                else if (colour == "green" && num > 13)
                {
                    anySubsetInvalid = true;
                }
                else if (colour == "blue" && num > 14)
                {
                    anySubsetInvalid = true;
                }
            }
        }
        if (anySubsetInvalid == false){
            sum += std::stoi(gameStr.c_str());
        }
        else{
            anySubsetInvalid = false;
        }
    }
    
    return sum;
}

int part2(){
    int sumPow = 0;
    
    std::string line;
    
    while(getline(std::cin, line))
    {
        int rgb[3] = {0,0,0};
        int colonPos = line.find(':');
        line = line.substr(colonPos + 2, line.length()-colonPos -1);
        int foundPos = line.find(';');
        int subLen = 0;
        std::string subset;
        while (line.length() > 0)
        {
            if (foundPos == std::string::npos)
            {
                subset = line;
                //printf("%s | %d \n", subset.c_str(), foundPos);
                line = "";
            }
            else{
                subset = line.substr(0, foundPos); 
                line = line.substr(foundPos + 2, line.length()-2-foundPos);
                //printf("%s | %d | %s\n", subset.c_str(), foundPos, line.c_str());
                foundPos = line.find(';');
            }
            // Given subset, parse how many red, green, blue
            std::string ssSet, colour, number;
            int num;
            int foundPos2=-1;
            while (subset.length() > 0){
                foundPos2 = subset.find(',');
                if (foundPos2 == std::string::npos)
                {
                    ssSet = subset;
                    //printf("%s-%d\n", ssSet.c_str(), foundPos2);
                    subset = "";
                }
                else{
                    ssSet = subset.substr(0, foundPos2); 
                    subset = subset.substr(foundPos2 + 2, subset.length()-2-foundPos2);
                    foundPos2 = subset.find(',');
                }
                
                foundPos2 = ssSet.find(' ');
                colour = ssSet.substr(foundPos2+1, ssSet.length()-1-foundPos2);
                number = ssSet.substr(0, foundPos2);
                num = std::stoi(number);
                //printf("//%s//%s//%d//%d\n", colour.c_str(), number.c_str(), num, foundPos2);
                if (colour == "red")
                {
                    if (num > rgb[0])
                    {
                        rgb[0] = num;
                    }
                }
                else if (colour == "green")
                {
                    if (num > rgb[1])
                    {
                        rgb[1] = num;
                    }
                }
                else if (colour == "blue")
                {
                    if (num > rgb[2])
                    {
                        rgb[2] = num;
                    }
                }
            }
            
        }
        sumPow += rgb[0] * rgb[1] * rgb[2];
    }

int main()
{
    //printf("%d\n", part1());
    printf("%d\n", part2());
    return 0;
}
