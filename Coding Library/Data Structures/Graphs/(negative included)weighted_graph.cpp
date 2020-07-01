#include<vector>
#include<iostream>
#include<climits>
using namespace std;
struct Weighted_Graph{
    int size;
    bool directed;
    vector<bool> visited;
    vector<long long int> dist;
    vector<int> prev;
    vector<vector<int>>graph;
    vector<vector<int>>weight;
    Weighted_Graph(int SIZE,bool isDirected)
    {
        size = SIZE;
        directed = isDirected;
        graph = decltype(graph)(size);
        weight = decltype(weight)(size);
        visited = decltype(visited)(size);
        dist = decltype(dist)(size);
        prev = decltype(prev)(size);
    }
};
void addEdge(Weighted_Graph* g,int nodeA,int nodeB,int weight)
{
    if(g->directed)
    {
        g->graph[nodeA].emplace_back(nodeB);
        g->weight[nodeA].emplace_back(weight);
    }
    else
    {
        g->graph[nodeA].emplace_back(nodeB);
        g->graph[nodeB].emplace_back(nodeA);
        g->weight[nodeA].emplace_back(weight);
        g->weight[nodeB].emplace_back(weight);
    }
}
void ipgraph(Weighted_Graph* g,int m)
{
    for(int i=0;i<m;i++)
    {
        int u,v,weight;
        cin>>u>>v>>weight;
        u--,v--;
        addEdge(g,u,v,weight);
    }

}
void explore(Weighted_Graph* g,int nodeS)
{
    g->visited[nodeS]=true;
    for(auto&it:g->graph[nodeS])
        if(!g->visited[it])
            explore(g,it);
    
}
void dfs(Weighted_Graph* g)
{
    for (int i = 0; i < g->size; i++)
       g->visited[i]=false;
    for (int i = 0; i < g->size; i++)
    {
        if(!g->visited[i])
            explore(g,i);
    }
}
vector<int> getConnectedComponents(Weighted_Graph* g)
{
  for (int i = 0; i < g->size; i++)
        g->visited[i]=false;
    vector<int>res;
    for (int i = 0; i < g->size; i++)
        if(!g->visited[i])
        res.emplace_back(i),explore(g,i);
    return res;
}
void BellManFord(Weighted_Graph* g,int nodeS)//no negative cycles in graph
{
    for (int i = 0; i < g->size; i++)
        g->dist[i] = LONG_LONG_MAX;
    g->dist[nodeS] = 0;
    g->prev[nodeS] = -1;
    bool f = true;
   while(f)
    {
        
        f = false;
      for (int i = 0; i < g->size; i++)
        {
            auto nodes = g->graph[i].begin();
            auto cost = g->weight[i].begin();
            if(g->dist[i]!=LONG_LONG_MAX)
            {
                while(nodes!=g->graph[i].end())
                {
                    if((g->dist[*nodes])>(g->dist[i]+(*cost)))
                    {
                        g->dist[*nodes] = g->dist[i]+(*cost);
                        g->prev[*nodes] = i;
                        f = true;
                    }
                    nodes++;
                    cost++;
                }
            }
        }
    }
}
bool hasNegativeCycle(Weighted_Graph* g)
{
    for (int i = 0; i < g->size; i++)
        g->visited[i] = false;
    vector<int>space = getConnectedComponents(g);
    for(auto&node:space)
    {
       for (int i = 0; i < g->size; i++)
            g->dist[i] = LONG_LONG_MAX;
        g->dist[node] = 0;
        int c = g->size;
        c--;
        bool f=true;
        while((c--)&&f)
        {
            f=false; 
            for (int i = 0; i < g->size; i++)
            {
                auto nodes = g->graph[i].begin();
                auto cost = g->weight[i].begin();
                if(g->dist[i]!=LONG_LONG_MAX)
                {
                    while(nodes!=g->graph[i].end())
                    {
                        if((g->dist[*nodes])>(g->dist[i]+(*cost)))
                        {
                            f=true;
                            g->dist[*nodes] = g->dist[i]+(*cost);
                        }
                        nodes++;
                        cost++;
                    }
                }
            }
        }
        for (int i = 0; i < g->size; i++)
        {
            auto nodes = g->graph[i].begin();
            auto cost = g->weight[i].begin();
            if(g->dist[i]!=LONG_LONG_MAX)
            {
                while(nodes!=g->graph[i].end())
                {
                    if((g->dist[*nodes])>(g->dist[i]+(*cost)))
                    {
                        return true;
                    }
                    nodes++;
                    cost++;
                }
            }
        }
    }
    return false;
}
