//pattern matching using suffix array O(nlog(n)+mlog(n))
#include<string>
#include<iostream>
using namespace std;
void Pattern_Matching(string* text,string* pattern,int*suffixArray)
{
    int l=0;
    int r = text->length()-1;
    int start = -1,end = -1;
    while(l<=r)
    {
        int m = (l+r)>>1;
        string temp = text->substr(*(suffixArray+m));
        if(temp.substr(0,pattern->length()) == pattern->substr()) {
            start = m;
            r=m-1;
        }else{
            if(temp<pattern->substr()) l=m+1;
            else r=m-1;
        }
    }
    l=0,r=text->length()-1;
    while(l<=r)
    {
        int m = (l+r)>>1;
        string temp = text->substr(*(suffixArray+m));
        if(temp.substr(0,pattern->length()) == pattern->substr()){ 
            end = m;
            l=m+1;
        }else{
            if(temp>pattern->substr()) r=m-1;
            else l=m+1;
        }
    }
    if(start!=-1)
    for(int i = start;i<=end;i++)
        cout<<*(suffixArray+i)<<" ";
    cout<<"\n";
    return;
}