#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  for (int i = 0; i < patterns.size(); i++)
  {
        int x = 0;
        for (int j = 0; j < patterns[i].size(); j++)
        {
            bool match_found = false;
            if(x < t.size())
            {
                for(auto& k : t[x])
                {
                    if(k.first == patterns[i][j])
                    {
                        match_found = true;
                        x = k.second;
                        break;
                    }
                }
                if(!match_found)
                {
                    t[x].insert(make_pair(patterns[i][j],t.size()));
                    x = t.size();
                }
            }
            else
            {
                map<char,int>m;
                m[patterns[i][j]] = t.size()+1;
                t.emplace_back(m);
                x = t.size();
            }   
        }
        map<char,int>m;
        m['$'] = -1;
        t.emplace_back(m);
  }
  return t;
}
bool PrefixTrieMatching(string* text,trie* t)
{
  bool found = true;
  int c = 0;
  int x=0;
  while(true)
  {
    if((*t)[x].find('$')!=(*t)[x].end())
      break;
    if((*t)[x].find((*text)[c])!=(*t)[x].end())
    {
      x = (*t)[x].find((*text)[c])->second;
      c++;
    }
    else
    {
      found = false;
      break;
    }
  }
  return found;
}
void TrieMatching(string* text,trie* t)
{
  for (int i = 0; i < text->length(); i++)
  {
    string s = text->substr(i);
      if(PrefixTrieMatching(&s,t))
        cout<<i<<" ";    
  }
}
int main() {
  size_t n;
  string Text;
  cin>>Text;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    s+='$';
    patterns.push_back(s);
  }
  trie t = build_trie(patterns);
  TrieMatching(&Text,&t);
  return 0;
}