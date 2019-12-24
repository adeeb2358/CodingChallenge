//
//  main.cpp
//  CodingChallenge
//
//  Created by adeeb mohammed on 22/12/19.
//  Copyright © 2019 adeeb mohammed. All rights reserved.
//
// final coding challenge

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include<algorithm>

using namespace std;
/*
 final interview questtion
 find out the most frequently used N toys in the list
    of quotes
 Input 1:- the number of toys
 Input 2:- the top n toys to be returned
 Input 3:- toy names array
 input 4:- no of quotes about the toys
 input 5:- toy name quotes
 
 Additional consideration
 1) The comparison of strings is case insensitive
 2) if top toys is more than the number of toys return the
    number of toys mentioned in the array
 
 Approach :
    1) maintain a hash map for storing the occurence of each
        toy string
    2) sort the array to find out the top n items if
        the array size is greatr other wise retrurn
        the items only mentioned in the string
 */

// this function is for case insensitive matching
std::string convertToLowerCase(std::string inputString){
    std::transform(inputString.begin(),inputString.end(),inputString.begin(),::tolower);
    return inputString;
}

// count frequencey
size_t countFreq(string &pat, string &txt)
{
    size_t M = pat.length();
    size_t N = txt.length();
    int res = 0;
    
    /* A loop to slide pat[] one by one */
    for (size_t i = 0; i <= N - M; i++)
    {
        /* For current index i, check for
           pattern match */
        size_t j;
        for (j = 0; j < M; j++)
            if (txt[i+j] != pat[j])
                break;
   
        // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
        if (j == M)
        {
           res++;
           j = 0;
        }
    }
    return res;
}

// this function is to sort the number of occurance
std::vector<std::string> sortToysMap(std::map<std::string,size_t> toyOccuranceMap){
    std::vector<std::string> toysVector;
    // reversing the key and value inorder to find the most number of occurance
    // map sort the elements based on its keys
    std::map<size_t,std::string> sortMap;
    for(std::map<std::string,size_t>::iterator it = toyOccuranceMap.begin();
        it != toyOccuranceMap.end(); ++it){
        sortMap.insert(std::make_pair(it->second, it->first));
    }
    // storing the elements in the final vector
    // problem with the coding challenge
    for(std::map<size_t,std::string>::reverse_iterator it = sortMap.rbegin() ; it != sortMap.rend();
        ++it){
        toysVector.push_back(it->second);
    }
    
    sortMap.clear();
    return toysVector;
}

std::vector<std::string> popularNToys(int numToys, int topToys,
                               std::vector<std::string> toys,
                               int numQuotes,
                               std::vector<std::string> quotes){
    std::vector<std::string> popToys;
    // store the toy names in a hash map and set its occurance to zero
    std::map<std::string,size_t> toyOccuranceMap;
    std::string oneToyName = "";
    for(std::vector<std::string>::iterator it = toys.begin();it != toys.end() ;++it){
        oneToyName = convertToLowerCase(*it);
        toyOccuranceMap[oneToyName] = (size_t)0;
    }
    
    std::string oneString = "";
    size_t numberOfOccur = 0;
    std::string toyName = "";
    // iterating through each quotes and finding the number of occurance
    for(std::vector<std::string>::iterator it = quotes.begin(); it != quotes.end(); ++it ){
        oneString = *it;
        oneString = convertToLowerCase(oneString);
        // updating the occurance map
       for(std::map<std::string,size_t>::iterator it_1 = toyOccuranceMap.begin();
            it_1 != toyOccuranceMap.end(); ++it_1){
            toyName = it_1->first;
            numberOfOccur = countFreq(toyName, oneString);
            it_1->second = it_1->second + numberOfOccur;
        }
    }
    
    // number of toys less than top toys
    popToys = sortToysMap(toyOccuranceMap);
    if(numToys < topToys){
        toyOccuranceMap.clear();
        return popToys;
    }
    // number of toys greater than top toys
    std::vector<std::string> topToysTemp;
    int count = 0;
    for(std::vector<std::string>::iterator it = popToys.begin(); it!=popToys.end(); ++it ){
        if(count == topToys){
            break;
        }
        topToysTemp.push_back(*it);
        count++;
    }
    toyOccuranceMap.clear();
    return topToysTemp;
}
 
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "find out popular toys\n";
    return 0;
}
