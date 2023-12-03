
#include <iostream>

int day1part1(){
    int sum = 0;
    char * line = new char[100];
    std::string str;
    while(scanf("%s", line) != EOF){
        int size = 0;
        int first = -1;
        int second = -1;
        char c = line[0];
        while (c != '\0'){
            c = line[size];
            if (first == -1 && isdigit(c)){
                first = c - '0';
            }
            size++;
        }
        while (size >=0){
            size--;
            c = line[size];
            if (second == -1 && isdigit(c)){
                second = c - '0';
            }
        }
        sum += first* 10 + second;
    }
    
    return sum;
}

int checkLastFive(char *fiveLet, char c,int& littleIdx)
{
    // clear everything if it's a digit
    if (isdigit(c))
    {
        littleIdx = 0;
        for (int i=0; i<5; i++)
        {
            fiveLet[i]='0';
        }
        return -1;
    }
    // get last 5 letters
    if (littleIdx == 5)
    {
        for (int i=1; i<=4; i++){
            fiveLet[i-1]=fiveLet[i];
        }
    }
    littleIdx = 4;
    fiveLet[littleIdx]= c;
    
    int retVal = -1;
    // check last 5 letters
    /*
    for (int i=0; i<5; i++)
    {
        printf("%c",fiveLet[i]);
    }
    printf("\n");*/
    
    // check last 3 (2,3,4) = one, two, six
    if(strcmp(&fiveLet[2],"one") == 0){
        retVal = 1;
    }
    if(strcmp(&fiveLet[2],"two") == 0){
        retVal = 2;
    }
    if(strcmp(&fiveLet[2],"six") == 0){
        retVal = 6;
    }
    
    //check last 4 (1,2,3,4)
    if(strcmp(&fiveLet[1],"four") == 0){
        retVal = 4;
    }
    if(strcmp(&fiveLet[1],"five") == 0){
        retVal = 5;
    }
    if(strcmp(&fiveLet[1],"nine") == 0){
        //printf("BBB");
        retVal = 9;
    }
    //check all five
    if(strcmp(fiveLet,"seven") == 0){
        retVal = 7;
    }
    if(strcmp(fiveLet,"eight") == 0){
        //printf("AAA");
        retVal = 8;
    }
    if(strcmp(fiveLet,"three") == 0){
        retVal = 3;
    }
    
    littleIdx++;
    return retVal;
}

int day1part2(){
    int sum = 0;
    
    char line[80];
    //testing 10
    int x = 0;
    while(scanf("%s", line) != EOF){
        int size = 0;
        int first = -1;
        int second = -1;
        int littleIdx = 0;
        char fiveLet [6] = "00000";
        char c = line[0];
        while (c != '\0'){
            if (isdigit(c))
            {
                if (first == -1){
                    first = c - '0';
                }
                else
                {
                    second = c - '0';
                }
            }
            
            if (first ==-1)
            {
                first = checkLastFive(fiveLet, c, littleIdx);
                
            }
            else{
                int tmpsecond = checkLastFive(fiveLet, c, littleIdx);
                if (tmpsecond != -1){
                    second = tmpsecond;
                }
            }
            
            size++;
            c = line[size];
        }
        if (second == -1){
            second = first;
        }
        //printf("%s", line);
        //printf(": %d%d\n", first, second);
        sum += first* 10 + second;
        //printf(" %d\n", sum);
        x++;
    }
    
    return sum;
}

int main()
{
    printf("%d", day1part1());
    printf("%d", day1part2());
    return 0;
}