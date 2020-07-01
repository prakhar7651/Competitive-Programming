#include<vector>
#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;
struct Graph{
    int size;
    bool directed;
    bool isBipartite;
    vector<bool> visited;
    vector<int> pre;
    vector<int> post;
    vector<long long int> dist;
    vector<int> prev;
    int clk=1;
    vector<vector<int>>graph;
    Graph(int SIZE,bool isDirected)
    {
        size = SIZE;
        directed = isDirected;
        isBipartite = true;
        graph = decltype(graph)(size);
        visited = decltype(visited)(size);
        pre = decltype(pre)(size);
        post = decltype(post)(size);
        dist = decltype(dist)(size);
        prev = decltype(prev)(size);
    }
};
void addEdge(Graph* g,int nodeA,int nodeB)
{
    if(g->directed) 
        g->graph[nodeA].emplace_back(nodeB);
    else
         g->graph[nodeA].emplace_back(nodeB),g->graph[nodeB].emplace_back(nodeA);
}
void ipgraph(Graph* g,int m)
{
    for (int i = 0; i < m; i++)
    {
        int u,v;
        cin>>u>>v;
        u--,v--;
        addEdge(g,u,v);
    }
}
void preVisit(Graph* g,int node)
{
    g->pre[node]=(g->clk)++;
}
void postVisit(Graph* g,int node)
{
    g->post[node] = (g->clk)++;
}
void explore(Graph*g,int node)
{
    g->visited[node]=true;
    preVisit(g,node);
    for(auto&it:g->graph[node])
        if(!g->visited[it])
            explore(g,it);
    postVisit(g,node);
}
void dfs(Graph* g)
{
    for (int i = 0; i < g->size; i++)
    {
        if(!g->visited[i])
        {
            explore(g,i);
        }
    }
}
void bfs(Graph* g,int nodeS)
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
vector<int> getShortestPath(Graph* g,int nodeS,int nodeT)
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
bool isBipartite(Graph*g)
{
    bfs(g,0);
    return g->isBipartite;
}