#include <bits/stdc++.h>
#define dprintf(...) //printf(__VA_ARGS__)
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

struct Solver {
  int n, nped, ncar;
  vector<vector<int>> adj;
  vector<int> dist;
  vector<int> pedmask;  // [u] => 1 << p | ...
  vector<int> u_car, u_ped;
  vector<vector<int>> u2cars;
  vector<vector<int>> car2masks;

  void solve() {
    read();

    {
      dist.assign(n, INT_MAX);
      dist[0] = 0;

      queue<int> Q;
      Q.push(0);
      while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int v : adj[u]) {
          if (dist[u] + 1 < dist[v]) {
            dist[v] = dist[u] + 1;
            Q.push(v);
          }
        }
      }
    }

    ncar = u_car.size();
    car2masks.assign(ncar, vector<int>());
    {
      // (u, mask)
      map<PII, int> dist2;
      queue<PII> Q;
      Q.push(PII(0, 0));
      dist2[PII(0, 0)] = 0;

      while (!Q.empty()) {
        PII p = Q.front(); Q.pop();
        int u = p.first;
        int mask = p.second;
        //dprintf("(u=%d,mask=%d):%d\n", u, mask, dist2[p]);
        for (int car_idx : u2cars[u]) {
          car2masks[car_idx].push_back(mask);
        }

        for (int v : adj[u]) {
          if (dist[v] != dist[u] + 1) continue;
          PII q(v, mask | pedmask[v]);
          if (dist2.count(q) == 0 || dist2[p] + 1 < dist2[q]) {
            dist2[q] = dist2[p] + 1;
            Q.push(q);
          }
        }
      }
    }

    for (auto& cm : car2masks) {
      sort(cm.begin(), cm.end());
      cm.erase(unique(cm.begin(), cm.end()), cm.end());
    }

    /*
    {dprintf("i:    "); for (int i = 0; i < n; i++) dprintf(" %d", i); dprintf("\n");}
    {dprintf("dist: "); for (auto d:dist) dprintf(" %d", d); dprintf("\n");}
    {dprintf("pedms:"); for (int i = 0; i < n; i++) dprintf(" %d", pedmask[i]); dprintf("\n");}
    {dprintf("u_car:"); for (auto u:u_car) dprintf(" %d", u); dprintf("\n");}
    {dprintf("u_ped:"); for (auto u:u_ped) dprintf(" %d", u); dprintf("\n");}
    {dprintf("carms:"); 
     for (auto v:car2masks) {
        dprintf(" [");
        for(auto m:v) {
          for (int i = 0; i < nped; i++) if (m & (1 << i)) dprintf("%d+", i);
          dprintf(" ");
        }
        dprintf("]");
     }
     dprintf("\n");
    }
    dprintf("nped=%d\n", nped);
    printf("\n\n");*/

    // [caridx][mask];
    vector<vector<int>> dp(ncar+1, vector<int>(1<<nped, 0));
    for (int car_idx = ncar; car_idx >= 0; car_idx--) {
      for (int mask = 0; mask < (1 << nped); mask++) {
        int& res = dp[car_idx][mask];
        if (car_idx == ncar) {
          res = 0;
          for (int i = 0; i < nped; i++) {
            if ((mask & (1 << i)) == 0) res++;
          }
        } else {
          res = nped;
          for (int m : car2masks[car_idx]) {
            res = min(res, dp[car_idx+1][mask|m]);
          }
        }
      }
    }

    printf("%d\n", dp[0][0]);
  }

  void read() {
    int m;
    cin >> n >> m;
    adj.assign(n, vector<int>());

    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v; --u; --v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    vector<int> houses, ped;
    {
      int f; cin >> f;
      houses.resize(f);
      for (int i = 0; i < f; i++) { cin >> houses[i]; --houses[i]; }
    }
    {
      cin >> nped;
      ped.resize(nped);
      for (int i = 0; i < nped; i++) { cin >> ped[i]; --ped[i]; }
    }

    pedmask.assign(n, 0);
    u2cars.assign(n, vector<int>());

    for (int i = 0; i < houses.size(); i++) {
      int u = houses[i];
      int p = -1;
      for (int j = 0; j < ped.size(); j++) {
        if (ped[j] == i) p = j;
      }

      if (p >= 0) {
        u_ped.push_back(u);
        pedmask[u] |= 1 << p;
      } else {
        int car_idx = u_car.size();
        u_car.push_back(u);
        u2cars[u].push_back(car_idx);
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false); cin.tie(0);

  int T; cin >> T;
  for (int cs = 1; cs <= T; cs++) {
    Solver solver;
    solver.solve();
  }
}
