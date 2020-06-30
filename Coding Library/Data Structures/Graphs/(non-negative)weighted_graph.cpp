#include<iostream>
#include<vector>
#include<climits>
#include<queue>
#include<algorithm>
using namespace std;
struct Weighted_Graph{
    int size;
    bool directed;
    bool isBipartite;
    vector<bool> visited;
    vector<int> pre;
    vector<int> post;
    vector<int> dist;
    vector<int> prev;
    int clk=1;
    vector<vector<int>>graph;
    vector<vector<int>>weight;
    Weighted_Graph(int SIZE,bool isDirected)
    {
        size = SIZE;
        directed = isDirected;
        isBipartite = true;
        graph = decltype(graph)(size);
        weight = decltype(weight)(size);
        visited = decltype(visited)(size);
        pre = decltype(pre)(size);
        post = decltype(post)(size);
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
void preVisit(Weighted_Graph* g,int node)
{
    g->pre[node]=(g->clk)++;
}
void postVisit(Weighted_Graph* g,int node)
{
    g->post[node] = (g->clk)++;
}
void explore(Weighted_Graph*g,int node)
{
    g->visited[node]=true;
    preVisit(g,node);
    for(auto&it:g->graph[node])
        if(!g->visited[it])
            explore(g,it);
    postVisit(g,node);
}
void dfs(Weighted_Graph* g)
{
    for (int i = 0; i < g->size; i++)
        g->visited[i] = false;
    for (int i = 0; i < g->size; i++)
    {
        if(!g->visited[i])
        {
            explore(g,i);
        }
    }
}
void bfs(Weighted_Graph* g,int nodeS)
{
    int nlm = g->size;
    for (int i = 0; i < g->size; i++)
        g->dist[i] = -1;
    queue<int>q;
    q.push(nodeS);
    g->dist[nodeS] = 0;
    g->prev[nodeS] = -1;
    while(!q.empty())
    {
        nodeS = q.front();
        q.pop();
        for(auto&it:g->graph[nodeS])
        {
            if(g->dist[it]==-1)
            {
                q.push(it);
                g->dist[it] = g->dist[nodeS]+1;
                g->prev[it] = nodeS;
            }
            else
            {
                int par1 = (g->dist[nodeS]+1)%2;
                int par2 = (g->dist[it])%2;
                if(par1!=par2)
                    g->isBipartite = false;
            }
        }
    }
}
vector<int> getShortestPath(Weighted_Graph* g,int nodeS,int nodeT)
{
    vector<int>result;
    bfs(g,nodeS);
    if(g->dist[nodeT]==-1)
    {
        result.emplace_back(-1);
        return result;
    }
    while(g->prev[nodeT]!=-1)
    {
        result.emplace_back(nodeT);
        nodeT = g->prev[nodeT];
    }
    result.emplace_back(nodeT);
    reverse(result.begin(),result.end());
    return result;
}
bool isBipartite(Weighted_Graph*g)
{
    bfs(g,0);
    return g->isBipartite;
}
void Dijkstra(Weighted_Graph* g,int nodeS)
{
    for (int i = 0; i < g->size; i++)
    {  
         g->dist[i] = INT_MAX;
        g->visited[i] = false;
    }
    g->dist[nodeS] = 0;
    g->prev[nodeS]=-1;
    while(true)
    {
        int nodeU;
        vector<int>unVisited;
        for (int i = 0; i < g->size; i++)
        {
            if(!g->visited[i])
                unVisited.emplace_back(i);
        }
        if(unVisited.empty())
            break;
        nodeU=unVisited[0];
        for (int i = 0; i < unVisited.size(); i++)
        {
            if(g->dist[unVisited[i]]<g->dist[nodeU])
                nodeU=unVisited[i];
        }
        g->visited[nodeU]=true;
        auto nodes = g->graph[nodeU].begin();
        auto cost  = g->weight[nodeU].begin();
        while((g->dist[nodeU]!=INT_MAX)&&(nodes!=g->graph[nodeU].end()))
        {
            if((g->dist[*nodes])>(g->dist[nodeU]+(*cost)))
            {
                g->dist[*nodes] = g->dist[nodeU]+*cost;
                g->prev[*nodes] = nodeU;
            }
            advance(nodes,1);
            advance(cost,1);
        }
    }
}
vector<int> getFastesetPath(Weighted_Graph* g,int nodeS,int nodeT)
{
    Dijkstra(g,nodeS);
    vector<int>result;
    if(g->dist[nodeT]==INT_MAX)
    {
        result.emplace_back(-1);
        return result;
    }
    while(g->prev[nodeT]!=-1)
    {
        result.emplace_back(nodeT);
        nodeT = g->prev[nodeT];
    }
    result.emplace_back(nodeT);
    reverse(result.begin(),result.end());
    return result;
}
