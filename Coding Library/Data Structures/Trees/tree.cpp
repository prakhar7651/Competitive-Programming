#include<bits/stdc++.h>
#define eb emplace_back
#define mp make_pair
#define ll long long
#define ull unsigned ll
#define rep(i,n) for(int i = 0;i<n;i++)
#define REP(i,k,n) for(int i=k;i<n;i++)
#define sz(x) ((int)x.size())
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define b_search binary_search
#define largest *max_element
#define smallest *min_element
using namespace std;
ll int Min(ll a,ll b){return a<b?a:b;}
ll int Max(ll a,ll b){return a>b?a:b;}
ll int Abs(ll a){ return a<0?-a:a;}
ll int GIF(ll a,ll b){return a/b+(a%b!=0);}
class  Node{
public:
    bool isNull = true;
    bool isLeftNull = true;
    bool isRightNull = true;
    bool isParentNull = true;
    Node* left;
    Node* right;
    Node* parent;
    int height =0;
    int key = -999999999;
};
bool isLeaf(Node* N)
{
    if(N->isLeftNull&&N->isRightNull)
        return true;
    else
        return false;
}
void SetHeight(Node* N)
{
    if(isLeaf(N)) {
        N->height = 1;
    }
    else
    {
        if(N->isLeftNull)
            N->height+=N->right->height;
        else
            if(N->isRightNull)
                N->height+=N->left->height;
            else
                N->height = 1+max(N->left->height,N->right->height);
    }
}
Node* Find(int key,Node* root)
{
    if(root->key==key)
        return root;
    if(root->key>key) {
        if(!root->isLeftNull)
            return Find(key, root->left);
        else
        {
            return root;
        }
    }
    else {
        if(!root->isRightNull)
            return Find(key, root->right);
        else
        {
            return root;
        }
    }
}
Node* LeftDescendent(Node* N)
{
    if(!N->isLeftNull)
        return LeftDescendent(N->left);
    else
        return N;
}
Node* RightAncestor(Node* N)
{
    if(N->isParentNull)
        return N;
    if(N->parent->key>N->key)
        return N->parent;
    else
        return RightAncestor(N->parent);
}
Node* Next(Node* N)
{
    if(!N->isRightNull)
        return LeftDescendent(N->right);
    else
        return RightAncestor(N);
}
vector<Node*> RangeSearch(int x,int y,Node* root)
{
    vector<Node*> result;
    Node* N = Find(x,root);
    while(N->key<=y)
    {
        if(N->key>=x)
            result.eb(N);
        Node* P = Next(N);
        if(N->key==P->key)
            break;
        else
            N=P;
    }
    return result;
}
void RotateRight(Node* X)
{
    Node* P = X->parent;
    Node* Y = X->left;
    Node* B = X->right;
    Y->parent = P;
    if(!X->isParentNull)
    if(P->left->key==X->key)
        P->left = Y;
    else
        P->right = Y;
    Y->parent = P;
    Y->isParentNull = X->isParentNull;
    X->parent = Y;
    Y->right = X;
    B->parent = X;
    X->left = B;
    X->isLeftNull = B->isNull;
    SetHeight(Y);
    SetHeight(X);
}
void RotateLeft(Node* X)
{
    Node* P = X->parent;
    Node* Y = X->right;
    Node* A = Y->left;
    if(!X->isParentNull)
    if(P->left->key==X->key)
        P->left = Y;
    else
        P->right = Y;
    Y->parent = P;
    Y->isParentNull = X->isParentNull;
    X->isParentNull = false;
    X->parent = Y;
    Y->left = X;
    Y->isLeftNull = false;
    A->parent = X;
    X->right = A;
    X->isRightNull = A->isNull;
    SetHeight(X);
    SetHeight(Y);
}
void RebalanceRight(Node* N)
{
    Node* M = N->left;
    if(M->right->height>M->left->height)
        RotateLeft(M);
    RotateRight(N);
}
void RebalanceLeft(Node* N)
{
    Node* M = N->right;
    if(M->left->height>M->right->height)
        RotateRight(M);
    RotateLeft(N);
}
void Rebalance(Node* N)
{
    Node*P;
    bool temp = N->isParentNull;
    if(!temp)
         P = N->parent;
    if(N->isLeftNull) {
        Node* X = new Node();
        X->isParentNull = false;
        X->parent = N;
        X->height = 0;
        N->left = X;
    }
    if(N->isRightNull) {
        Node* X = new Node();
        X->isParentNull = false;
        X->parent = N;
        X->height = 0;
        N->right = X;
    }
    if(N->left->height>(N->right->height+1))
        RebalanceRight(N);
    if(N->right->height>(N->left->height+1))
        RebalanceLeft(N);
    SetHeight(N);
    if(!temp)
        Rebalance(P);
}
void Insert(int key,Node* root)
{
    Node* N = Find(key,root);
    if(N->key==key)
        return;
    else
    {
        Node* X = new Node();
        X->key = key;
        X->parent = N;
        X->isNull = false;
        X->isParentNull = false;
        X->height = 1;
        if(N->key>key)
        {
            N->isLeftNull = false;
            N->left = X;

        } else
        {
            N->isRightNull = false;
            N->right = X;
        }
    }
    Rebalance(N);
}
Node* getRoot(Node* X)
{
    if(X->isParentNull)
        return X;
    else return getRoot(X->parent);
}
string getString(int n,int len)
{
    int x = log10(abs(n))+1;
    string a(len-x,' ');
    return a;
}
void print(vector<Node> nodes, int height,int cons,int len) {
    string space(len,' ');
    for(int i=0;i<pow(2,height-1)-1;i++)
    cout<<space;
    string s((pow(2,height)-1)*len,' ');
    for(int i=0;i<nodes.size();i++)
    {
        if(nodes[i].key==cons)
            cout<<space;
        else
            cout<<nodes[i].key<<getString(nodes[i].key,len);
        cout<<s;
    }
    cout<<endl<<endl;
    if(height==1)
        return;
    vector<Node>pass;
    for(int i=0;i<nodes.size();i++)
    {
        if(nodes[i].isLeftNull)
        {
           Node X;
           X.key = cons;
           pass.eb(X);
        } else
            pass.eb(*nodes[i].left);
        if(nodes[i].isRightNull)
        {
            Node X;
            X.key = cons;
            pass.eb(X);
        } else
            pass.eb(*nodes[i].right);
    }
    print(pass,height-1,cons,len);
}
void printInOrder(Node node) {
    if(!node.isLeftNull)
        printInOrder(*node.left);
    cout<<node.key<<" ";
    if(!node.isRightNull)
        printInOrder(*node.right);
}
int fake_main()
{
    int n;
    cin>>n;
    /*
    Node X;
    X.key = 1;
    X.height = 1;
    X.isNull = false;
    X.isRightNull = true;
    X.isLeftNull = true;
    X.isParentNull = true;
    loop(n-1)
    {
        Insert(i+2,getRoot(&X));
    }*/
    int key;
    cin>>key;
    Node X;
    X.key = key;
    X.height = 1;
    X.isNull = false;
    X.isRightNull = true;
    X.isLeftNull = true;
    X.isParentNull = true;
    for(int i=0;i<n-1;i++)
    {
        int x;
        cin >> x;
        key = max(key,x);
        Insert(x,getRoot(&X));
    }
    Node root = X;
    while(!root.isParentNull)
        root = *root.parent;
    vector<Node> nodes;
    nodes.eb(root);
    printInOrder(root);
    cout<<endl;
    int cons = -999999999;
    int len = log10(abs(key))+1;
    print(nodes,root.height,cons,len);
    return 0;
}
void solve()
{
    fake_main();
}
int32_t main()
{
    IOS;
    //freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
    int tc = 1;
    cin >> tc;
    while(tc--)
    {
        solve();
    }
    return 0;
}