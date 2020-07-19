/*
KMP Algorithm
find occurences of pattern in text in O(|text|+|pattern|) time.
*/
#include<string>
#include<iostream>
#include<vector>

using namespace std;

void ComputePrefixFunction(string* pattern,int* s) // compute lengths of borders of the prefixes of a string and stores in s
{
    *(s) = 0;
    int border = 0;
    for (int i = 1; i < pattern->length(); i++)
    {
        while(border > 0 && pattern->at(i) != pattern->at(border))
        {
            border = *(s+border-1);
        }
        if(pattern->at(i) == pattern->at(border))
            border++;
        else border = 0;
        *(s+i) = border;
    }
    return; 
}
void KMP(string* text,string* pattern,vector<int>*result) //stores occurences of pattern in text in result
{
    string target = pattern->substr() + '$' + text->substr();
    int s[target.length()];
    ComputePrefixFunction(&target,s);
    for (int i = pattern->length()+1; i < target.length(); i++)
    {
        if(s[i] == pattern->length())
            result->emplace_back(i-2*pattern->length());
    }
    return;
}