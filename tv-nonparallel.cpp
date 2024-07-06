#include <bits/stdc++.h>
#include <omp.h>
#include <chrono>
    
using namespace std;
#define int long long
    
vector<vector<int>> graph;
vector<pair<int,int>> edges;
vector<int> pre, par, depth, parskip;
vector<int> vis;
vector<vector<int>> binlift;
map<pair<int,int>,int> edgeinfo, visited;
map<pair<int,int>,vector<pair<int,int>>> ngraph;
map<pair<int,int>,int> edgeadded;
vector<vector<int>> BCCs;
    
int n, m, LOG;
    
void initialize() {
    cin >> n >> m;
    graph.assign(n, vector<int>(0));
    pre.assign(n,0);
    par.assign(n,0);                           // parent of root(0) will be 0
    parskip.assign(n,0);
    vis.assign(n,0);
    depth.assign(n,0);
    LOG = 1;
    for (int t = 1; t <= n; t <<= 1) LOG++;
    binlift.assign(n,vector<int>(LOG));         
    for (int i = 0; i < n; i++) pre[i] = i;
    for (int i = 0; i < m; i++){
        int x, y; cin >> x >> y;
        if (x > y) swap(x,y);
        if (x == y) continue;                   // self loop
        if (edgeinfo[{x,y}] == 1) continue;     // multiple edges
        graph[x].push_back(y);
        graph[y].push_back(x);
        edgeinfo[{x,y}] = 1;
        edges.push_back({x,y});
    }
}
    
void create_spanning_tree() {                   // random spanning tree (not bfs)
    vector<int> q;
    q.push_back(0); vis[0] = 1;
    while (q.size()){
        vector<int> nq;
        for (int i = 0; i < q.size(); i++) {
            int x = q[i];
            // #pragma omp parallel for
            for (int j = 0; j < graph[x].size(); j++) {
                int y = graph[x][j];
                bool toinsert = false;
                if (!vis[y]) {
                    // #pragma omp critical
                    {
                        if (!vis[y]) toinsert = true;
                        vis[y] = 1;
                    }
                }
                if (toinsert) {
                    // #pragma omp critical
                    {
                    par[y] = x;
                    parskip[y] = y;
                    depth[y] = depth[x] + 1;        // no race condition since y is not yet added to queue
                    int u = x, v = y;
                    if (u > v) swap(u,v);
                    edgeinfo[{u,v}] = 2;            // edge part of spanning tree
                    nq.push_back(y);
                    }
                }
            }
        }
        // #pragma omp barrier
        q = nq;
    }
}
    
void create_binlift() {
    // #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        binlift[i][0] = par[i];
    }
    for (int j = 1; j < LOG; j++) {
        // #pragma omp parallel for
        for (int i = 0; i < n; i++) {
            binlift[i][j] = binlift[binlift[i][j - 1]][j - 1];
        }
    }
}
    
int LCA(int a, int b) {
    if (depth[a] > depth[b]) swap(a,b);
    int t = LOG - 1;
    while (depth[b] > depth[a]) {
        int sub = 1ll << t;
        if (depth[b] - sub < depth[a]){
            t--;
            continue;
        }
        b = binlift[b][t];
        t--;
    }
    if (a == b) return a;
    for (int i = LOG - 1; i >= 0; i--) {
        if (binlift[a][i] == binlift[b][i]) continue;
        a = binlift[a][i]; b = binlift[b][i];
    }
    return binlift[a][0];
}
    
void add_edge (int a1, int a2, int b1, int b2) {
    ngraph[{min(a1,a2),max(a1,a2)}].push_back({min(b1,b2),max(b1,b2)});
    ngraph[{min(b1,b2),max(b1,b2)}].push_back({min(a1,a2),max(a1,a2)});
}
    
void create_ngraph() {
    // #pragma omp parallel for
    for (int i = 0; i < edges.size(); i++) {
        int t = edgeinfo[edges[i]];
        if (t == 2) continue;
        int x = edges[i].first, y = edges[i].second;
        int lca = LCA(x,y);
        if (lca == x || lca == y) {
            
        }
        else {
            // Case a
            int v = x, w = y;
            if (pre[v] > pre[w]) swap(v,w);
            int u = par[w];
            // #pragma omp critical
            {
                add_edge(x,y,u,w);
            }
            // Case b
            u = par[x], v = par[y];
            // #pragma omp critical
            {
                add_edge(u,x,v,y);
            }
        }
        // Case c
        int u = x, v = y;
        u = parskip[u], v = parskip[v];
        vector<int> val;
        while (depth[u] >= depth[lca]+2) {
            int a = par[u], b = par[par[u]];
            // #pragma omp critical
            {
            add_edge(u,a,a,b);
            }
            val.push_back(u);
            u = parskip[par[u]];
        }
        // #pragma omp critical
        {
            for (auto it: val){
                parskip[it] = u;
            } 
        }
        val.clear();
        while (depth[v] >= depth[lca]+2) {
            int a = par[v], b = par[par[v]];
            // #pragma omp critical
            {
            add_edge(v,a,a,b);
            }
            val.push_back(v);
            v = parskip[par[v]];
        }
        // #pragma omp critical
        {
            for (auto it: val){
                parskip[it] = v;
            } 
        }
    }
}
    
void find_components(int a, int b) {
    visited[{a,b}] = 1;
    if (ngraph[{a,b}].size()==0) return;
    vector<int> comp;
    vector<pair<int,int>> q;
    map<int,int> done;
    q.push_back({a,b}); 
    while (q.size()){
        vector<pair<int,int>> nq;
        // #pragma omp parallel for default(none) shared(q, nq, comp, done, visited, ngraph)
        for (int i = 0; i < q.size(); i++) {
            pair<int,int> x = q[i];
            int fl = 0;
            if (!done.count(x.first)) {
                // #pragma omp critical
                {
                    if (!done[x.first]) {
                        done[x.first] = 1;
                        fl = 1;
                    }
                }
            }
            if (fl){
                // #pragma omp critical
                {
                comp.push_back(x.first);
                }
            }
            fl = 0;
            if (!done.count(x.second)) {
                // #pragma omp critical
                {
                    if (!done[x.second]) {
                        done[x.second] = 1;
                        fl = 1;
                    }
                }
            }
            if (fl) {
                // #pragma omp critical
                {
                comp.push_back(x.second);
                }
            }
            for (int j = 0; j < ngraph[x].size(); j++) {

                auto y = ngraph[x][j];
                bool toinsert = false;
                if (!visited.count(y)) {
                    // #pragma omp critical
                    {
                        if (!visited[y]) {
                            toinsert = true;
                            visited[y] = 1;
                        }
                    }
                }
                if (toinsert) {
                    // #pragma omp critical
                    {
                        nq.push_back(y);
                    }
                }
            }

        }
        // // #pragma omp barrier
        q = nq;
    }
    BCCs.push_back(comp);
}

void output() {

    for (auto it: BCCs){
        for (auto itt:it){
            cout<<itt<<" ";
        }
        cout<<'\n';
    }
}

int32_t main(int argc, char* argv[]) 
{
    freopen(argv[1], "r", stdin); 
    // freopen("ouput.txt", "w", stdout); 
    initialize();
    auto start = std::chrono::high_resolution_clock::now();
    create_spanning_tree();
    
    //---------------------------------------------------------------------------------------
        
    create_binlift();
    //-----------------------------------------------------------------------------------------
        
    create_ngraph();
    //----------------------------------------------------------------------------------------
        
    for (auto it: edgeinfo) {
        int a = it.first.first, b = it.first.second;
        if (visited[{a,b}]) continue;
        find_components(a,b);
    }
    //----------------------------------------------------------------------------------------
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << setprecision(8) << fixed << duration.count() << " seconds" << std::endl;
    // output();
    // cout << BCCs.size()<<'\n';
    
}