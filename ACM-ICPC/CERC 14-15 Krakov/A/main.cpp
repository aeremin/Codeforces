#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <string>
#include <algorithm>
#include <set>
#include <cstdint>
#include <limits>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<bool> vb;
typedef int64_t ll;

bool parade[1000][1000];
vb alive(1000, true);
vvi child(1000);
vi par(1000);

void mortify(int x){
    if (alive[x]) {
        for (int i = 0; i < child[x].size(); i++) {
            mortify(child[x][i]);
        }
        alive[x] = false;
    }
}

void parsoc(int n, vb & used, vvi & edge, vector<pair<int,int>> & best){
    best.clear();
    int v = 0;
    while ((v < n) && (used[v])) v++;
    if (v == n) return;
    //vector<pair<int, int>> besttry;
    used[v] = true;
    vi posedge;
    for (int i = 0; i < edge[v].size(); i++) {
        int u = edge[v][i];
        if (!used[u]) posedge.push_back(u);
    }
    if (posedge.size() == 0) {
        parsoc(n, used, edge, best);
    }
    else{
        int uu = posedge[0];
        used[uu] = true;
        parsoc(n, used, edge, best);
        used[uu] = false;
        best.push_back(make_pair(uu, v));

        int maxans = best.size();
        vector<pair<int, int>> atry;
        for (int i = 1; i < posedge.size(); i++) {
            int u = posedge[i];
            used[u] = true;
            parsoc(n, used, edge, atry);
            used[u] = false;
            if (atry.size() >= maxans) {
                best = atry;
                best.push_back(make_pair(v, u));
                maxans = best.size();
                break;
            }
        }
    }
    used[v] = false;
}

int main()
{
    //freopen("problem.in", "rt", stdin);
    //freopen("problem.out", "wt", stdout);
    int t;
    cin >> t;
    for (int iuc = 0; iuc < t; iuc++) {
        for (int i = 0; i < 1000; i++) {
            child[i].clear();
            alive[i] = true;
        }
        int n;
        cin >> n;
        vvi e(n);
        for (int j = 0; j < n - 1; j++) {
            int x, y;
            
            cin >> x >> y;
            x--; y--;
            e[x].push_back(y);
            e[y].push_back(x);
        }
        vvi potom(n);
        vi lvl(n);
        vb c(n, false);
        vvi v_lvl(n+1);
        par[0] = -1;
        deque<int> poisk;
        poisk.push_back(0);
        int l = 0;
        c[0] = true;
        while (poisk.size()>0){
            l++;
            int s = poisk.size();
            for (int i = 0; i < s; i++){
                int v = poisk.front();
                poisk.pop_front();
                lvl[v] = l;
                v_lvl[l].push_back(v);
                for (int j = 0; j < e[v].size(); j++){
                    if (!c[e[v][j]]) {
                        c[e[v][j]] = true;
                        poisk.push_back(e[v][j]);
                        par[e[v][j]] = v;
                        child[v].push_back(e[v][j]);
                    }
                }
            }
        }
        
        for (int i = l; i >= 1; i--) {
            for (int j = 0; j < v_lvl[i].size(); j++){
                int v = v_lvl[i][j];
                for (int k = 0; k < child[v].size(); k++) {
                    for (int h = 0; h < potom[child[v][k]].size(); h++) {
                        potom[v].push_back(potom[child[v][k]][h]);
                    }
                }
                potom[v].push_back(v);
            }
        }

        for (int i = 0; i < 1000; i++){
            for (int j = 0; j < 1000; j++){
                parade[i][j] = false;
            }

        }
        int m;
        cin >> m;
        for (int i = 0; i < m; i++) {
            int x, y;
            scanf("%d %d\n", &x, &y);
            x--; y--;
            parade[x][y] = true;
            parade[y][x] = true;
        }

        int ans = 0;
        

        for (int i = l; i >= 1; i--) {
            for (int j = 0; j < v_lvl[i].size(); j++){

                int v = v_lvl[i][j];
                for (int k = 0; k < potom[v].size(); k++) {
                    int u = potom[v][k];
                    if ((alive[u]) && (parade[u][v])) {
                        ans++;
                        while (par[u] != v) u = par[u];
                        mortify(u);
                    }
                }
                vi alivechild;
                for (int k = 0; k < child[v].size(); k++) {
                    if (alive[child[v][k]]) alivechild.push_back(child[v][k]);
                }
                int w = alivechild.size();
                vvi new_e(w);
                for (int k = 0; k < w; k++){
                    for (int h = k + 1; h < w; h++){
                        int p = alivechild[k];
                        int q = alivechild[h];
                        bool flag = false;
                        for (int x = 0; x < potom[p].size(); x++){
                            if (flag) break;
                            int xx = potom[p][x];
                            for (int y = 0; y < potom[q].size(); y++){
                                int yy = potom[q][y];
                                if (alive[xx] && alive[yy] && parade[xx][yy]){
                                    new_e[k].push_back(h);
                                    new_e[h].push_back(k);
                                    flag = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                vector<pair<int, int>> best;
                //vb used(w, false);
                vi para(w, -1);
                //parsoc(w, used, new_e, best);
                for (int k = 0; k < w; k++) {
                    if (para[k] == -1) {
                        vb used(w, false);
                        vi prev(w, -1);
                        used[k] = true;
                        deque<int> ps;
                        ps.push_back(k);
                        while (ps.size()>0){
                            int s = ps.size();
                            for (int h = 0; h < s; h++){
                                int f = ps.front();
                                ps.pop_front();
                                bool flag = false;
                                for (int po = 0; po < new_e[f].size(); po++){
                                    int g = new_e[f][po];
                                    if (para[g] == -1){
                                        while (f != -1){
                                            para[g] = f;
                                            int newg = para[f];
                                            int swap = prev[f];
                                            para[f] = g;
                                            f = swap;
                                            g = newg;
                                        }
                                        flag = true;
                                        break;
                                    }
                                    else{
                                        if (!used[para[g]]){
                                            ps.push_back(para[g]);
                                            used[para[g]] = true;
                                            prev[para[g]] = f;
                                        }
                                    }
                                }
                                if (flag) break;
                            }
                        }
                    }
                }
                int ansplus = 0;
                for (int k = 0; k < w; k++) {
                    if (para[k] != -1){
                        mortify(alivechild[k]);
                        ansplus++;
                    }
                }
                ans+=ansplus / 2;
                /*for (int k = 0; k < best.size(); k++) {
                    mortify(alivechild[best[k].first]);
                    mortify(alivechild[best[k].second]);
                    ans++;
                }*/


            }
        }
        cout << ans << endl;


    }
    return 0;
}