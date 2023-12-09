#include <string>
#include <iostream>		//cin or printf
#include <vector>		//vector
#include <algorithm>		//max
#include <sstream>		//stringstream
#include <cmath>		// pow
#include <map> // map

int getNumFromString(std::string t){
    int actualNum = 0;
	for (int i = 0; i < t.length(); i++)
	{
	    if (isdigit (t[i]))
		{
		    actualNum = actualNum * 10 + (t[i] - '0');
		}
	}
	return actualNum;
}

void LineToNumVectBySpaces (std::string line, std::vector < int >&vec)
{
    std::stringstream sStream (line);
    std::string t;
    while (getline (sStream, t, ' '))
    {
        // store token string in the vector
        if (!t.empty ())
	    {
	        int sign = 1;
	        if (t[0] == '-')
	        {
	            sign = -1;
	        }
	        int actualNum = getNumFromString(t) * sign;
	        vec.push_back (actualNum);
	    }
    }
}

void LineToVectBySpacesIgnoringPunct (std::string line, std::vector <std::string>&vec, std::string puncToIgnore)
{
    std::string t;
    bool ignoreChar;
    for (int i = 0; i < line.size(); i++) 
    {
        ignoreChar = false;
        for (int j = 0; j < puncToIgnore.size(); j++)
        {
            if (line[i] == puncToIgnore[j])
            {
                ignoreChar = true;
            }
        }
        if (ignoreChar)
        {
            if (t.length() > 0)
            {
                vec.push_back(t);
                t = "";
            }
        }
        else
        {
            t += line[i];
        }
    }
}
