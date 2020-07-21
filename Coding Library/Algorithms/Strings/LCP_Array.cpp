#include<string>
using namespace std;

void buildLCParray(string* s,int* suffixArray,int* lcp) // lcp[i] = LCP(order[i],order[i+1])
{
    int rank[s->length()];
    for (int i = 0; i < s->length(); i++)
    {
        rank[*(suffixArray + i)] = i;
    }
    int k=0;
    for (int i = 0; i < s->length(); i++)
    {
        if(rank[i] == s->length()-1)
        {
            k=0;
            continue;
        }
        int j = *(suffixArray + rank[i] + 1);
        while(i + k < s->length() && j + k < s->length() && s->at(i+k) == s->at(j+k))
            k++;
        lcp[rank[i]] = k;
        k = max(0,k-1);
    }    
}