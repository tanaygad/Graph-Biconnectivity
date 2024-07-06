#include<bits/stdc++.h>
using namespace std;
#define int long long
#define vi vector<int> 
#define vvi vector<vector<int>>
#define si set<int>
#define vsi vector<set<int>>
#define pb push_back
    
vector<vector<int>> graph;
vector<int> vis;
vector<int> tin, low;
int timer;
int n, m, LOG;
vvi Biconnected_components;
vi children;
stack<int> st;
    
void initialize() {
    cin >> n >> m;
    graph.assign(n, vector<int>(0));
    vis.assign(n,0);
    tin.assign(n,-1);
    low.assign(n,-1);
    children.assign(n,0);
    timer=0;
    for (int i = 0; i < m; i++){
        int x, y; cin >> x >> y;
        if (x > y) swap(x,y);
        if (x == y) continue;                   // self loop
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
}
    
    
void dfs(int v, int p = -1) 
{
    stack<pair<int,pair<int,int>>> stk;
    stk.push(make_pair(v,make_pair(-1,0)));
    int fl=0;
    
    
    while(stk.empty()==0)
    {
        auto val=stk.top();
        stk.pop();
        v=val.first;
        p=val.second.first;
        int iteration=val.second.second;
        if(v==1)
        {
            // cout << "Why\n";
        }
        if(vis[v]==0)
        {tin[v] = low[v] = timer++;st.push(v);}
        vis[v] = true;
        int ctr=0;
        for (int to : graph[v]) 
        {
            if (to == p) continue;
            if(ctr<iteration)
            {
                ctr++;
                continue;
            }
            if (vis[to]) 
            {
                low[v] = min(low[v], low[to]);
                st.push(v);
                if (low[to] >= tin[v] && p!=-1)
                {
                    // cout << v << " is an articulation point\n";
                    vi bi;
                    map<int,int> M;
                    M[v]=1;
                    bi.pb(v);
                    st.pop();
                    while(st.top()!=v)
                    {
                        if(!M[st.top()])
                        {bi.pb(st.top());
                        M[st.top()]=1;}
                        st.pop();
                    }
                    if(bi.size()>2)
                        Biconnected_components.pb(bi);
                }
                children[v]++;
                if(p==-1 and v==0 and children[v]>=2)
                {
                    vi bi;
                    map<int,int> M;
                    bi.pb(v);
                    M[v]=1;
                    st.pop();
                    while(st.top()!=v)
                    {
                        if(!M[st.top()])
                        {bi.pb(st.top());
                        M[st.top()]=1;}
                        st.pop();
                    }
                    if(bi.size()>2)
                        Biconnected_components.pb(bi);
                }
            } 
            else 
            {
                // dfs(to, v);
                stk.push(make_pair(v,make_pair(p,ctr)));
                stk.push(make_pair(to,make_pair(v,0)));
                fl=1;
                break;
            }
            ctr++;
        }
        if(fl)
            continue;   
    }
}
    
    
int32_t main(int argc, char* argv[])
{
    freopen(argv[1], "r", stdin); 
    // freopen("ouput.txt", "w", stdout); 
    initialize();
    auto start = std::chrono::high_resolution_clock::now();
    dfs(0);
    vi s;
    map<int,int> M;
    while(st.empty()==0)
    {
        if(!M[st.top()])
        {s.pb(st.top());
        M[st.top()]=1;}
        st.pop();
    }
    if(s.size()>2)
        Biconnected_components.pb(s);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << setprecision(8) << fixed << duration.count() << " seconds" << std::endl;
    // for(auto it:Biconnected_components)
    // {
    //     for(auto iter:it)
    //         cout << iter << " ";
    //     cout << "\n";
    // }
}