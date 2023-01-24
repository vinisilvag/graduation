#include <bits/stdc++.h>
using namespace std;
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define forC(i,k,n) for(int i=k;i<n;i++)
#define forD(i,k,n) for(int i=k;i>=n;i--)
#define read(v) for(auto &elm : v) cin >> elm
#define readM(v) for(auto rr : vv) for(auto ee : rr) cin >> ee
#define ord(xx) sort(xx.begin(),xx.end())
#define print(var) cout << var << endl
#define printV(l) for(auto a : l) cout << a << " "; cout << endl
#define printM(mm) for(auto aaa : mm){ for(auto b : aaa) cout << b << " "; cout << endl;}  
#define hr cout << endl
#define dbg(x) cout << #x << " = " << x << endl
#define dbgV(l) cout << #l << endl; for(int i=0;i<l.size();i++) cout << #l << "[" << i<< "] : "<< l[i] << endl
#define dbgM(mm) cout << #mm << endl; for(auto aaa : mm){ for(auto b : aaa) cout << b << " "; cout << endl;}  
#define pb push_back
#define s second 
#define f first

typedef pair<int,int> ii;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const  ll LINF = 0x3f3f3f3f3f3f3f3fll;

vector<vector<int>> arestas(105);
vector<vector<int>> chs(105);
vector<bool> vis(100,false);

void dfs(int i){
    deque<int> dq;
    vis = vector(105,false);
    vis[i] = true;
    dq.pb(i);
    while(!dq.empty()){
        int a = dq.back();
        dq.pop_back();
        for(auto f : arestas[a]){
            if(vis[f]) continue;
            chs[i].pb(f);
            vis[f] = true;
            dq.pb(f);
        }
    }
}


void tc(int seed){
    srand(seed);
    int N = 100;
    int V = 1000;
    int Q = 1000;
    vector<tuple<int,int,int>> graph;
    forC(i,2,N+1){
        int v = rand()%(i-1) +1;
        int u = i;
        bool aponta = rand()%2;
        if(aponta){
            u = v;
            v = i;
        }
        arestas[v-1].pb(u-1);
        graph.emplace_back(v,u,rand()%10000 +1);
    }
    int ot = V-(N-1);
    while(ot--){
        int v = rand()%N + 1;
        int u = rand()%N + 1;
        while(u == v){
            u = rand()%N + 1;
        }
        arestas[v-1].pb(u-1);
        graph.emplace_back(v,u,rand()%10000 +1);
    }
    vector<int> vs;
    forC(i,0,N){
        dfs(i);
        vs.pb(i+1);
    }
    random_shuffle(vs.begin(),vs.end());
    set<ii> prs;
    int q=0;
    vector<ii> qrs;
    for(auto v : vs){
        if(!chs[v-1].size()) continue;
        random_shuffle(chs[v-1].begin(),chs[v-1].end());
        for(auto u : chs[v-1]){
            if(q == Q) break;
            q++;
            qrs.pb({v,u+1});
        }
        if(q == Q) break;
    }

    cout << N << " " << V << " " << q << endl;
    for(auto [u,v,p] : graph){
        cout << u << " " << v << " " << p << endl;
    }
    for(auto [u,v] : qrs){
        cout << u << " " << v << endl;
    }
    

}

int main(int argc, const char* argv[]){ _
    tc(atoi(argv[1]));
}