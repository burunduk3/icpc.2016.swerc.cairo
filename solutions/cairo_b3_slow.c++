#include <cassert>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

const int maxn = 251;

int main () {
  int tn;
  assert (scanf ("%d", &tn) == 1);
  for (int tt = 0; tt < tn; tt++) {
    int n, m;
    assert (scanf ("%d%d", &n, &m) == 2);
    static char a[maxn][maxn], b[maxn][maxn];
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) {
        assert (scanf (" %c%c", &a[i][j], &b[i][j]) == 2);
        a[i][j] -= '0';
        b[i][j] -= '0';
      }

    // nodes numeration
    auto node = [&]( int is_b, int i, int j ) {
      if ((is_b ? b : a)[i][j])
        return -5;
      if (i < 0)
        return -1;
      if (j < 0)
        return -2;
      if (i >= n)
        return -3;
      if (j >= m)
        return -4;
      return is_b * n * m + i * m + j;
    };

    int nodes = 2 * n * m;
    int node_mask[nodes];
    memset (node_mask, 0, sizeof (node_mask[0]) * nodes);
    vector <int> g[nodes];

    auto edge = [&]( int x, int y ) {
      if (x == -5 || y == -5)
        return;
      if (y < 0) {
        node_mask[x] |= (1 << (-y - 1));
        return;
      }
      g[x].push_back (y);
    };

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) {
        if ((i ^ j) % 2) { // vertical
          edge (node (0, i, j), node (0, i - 1, j));
          edge (node (0, i, j), node (1, i - 1, j));
          edge (node (0, i, j), node (1, i, j - 1));
          edge (node (0, i, j), node (1, i, j));
          edge (node (0, i, j), node (0, i, j + 1));
          edge (node (1, i, j), node (0, i, j));
          edge (node (1, i, j), node (1, i, j - 1));
          edge (node (1, i, j), node (0, i + 1, j));
          edge (node (1, i, j), node (1, i + 1, j));
          edge (node (1, i, j), node (0, i, j + 1));
        } else {           // horizontal
          edge (node (0, i, j), node (1, i - 1, j));
          edge (node (0, i, j), node (0, i, j - 1));
          edge (node (0, i, j), node (1, i, j - 1));
          edge (node (0, i, j), node (0, i + 1, j));
          edge (node (0, i, j), node (1, i, j));
          edge (node (1, i, j), node (1, i - 1, j));
          edge (node (1, i, j), node (0, i, j));
          edge (node (1, i, j), node (0, i + 1, j));
          edge (node (1, i, j), node (0, i, j + 1));
          edge (node (1, i, j), node (1, i, j + 1));
        }
      }

    bool c[nodes];
    memset (c, 0, sizeof (c[0]) * nodes);
    vector <int> tmp;

    function <int (int)> dfs;
    dfs = [&]( int u ) {
      c[u] = true;
      tmp.push_back (u);
      int mask = node_mask[u];
      int unique = mask;
      for (auto v : g[u]) {
        if (c[v])
          continue;
        int res = dfs (v);
        unique &= ~(res & 15);
        unique |= (res >> 4) & ~mask;
        mask |= res & 15;
      }
      return mask | (unique << 4);
    };
    bool found = false;
    for (int u = 0; u < nodes; u++) {
      if (c[u] || g[u].size () == 0)
        continue;
      tmp.clear ();
      int res = dfs (u);
      if ((res & 15) != 15)
        continue;
      // fprintf (stderr, "base res=%d\n", res);
      vector <int> ans = tmp;
      bool ok = true;
      for (auto v : ans) {
        memset (c, 0, sizeof (c[0]) * nodes);
        c[v] = true;
        vector <int> gg = g[v];
        g[v].clear ();
        for (auto vv : ans) {
          if (c[vv])
            continue;
          int res = dfs (vv);
          if ((res & 15) != 15)
            continue;
          // fprintf (stderr, "kill n=%d m=%d v=%d, res=%d\n", n, m, v, res);
          ok = false;
          break;
        }
        if (!ok)
          break;
        g[v] = gg;
      }
      if (!ok)
        break;
      printf ("%d\n", (int)ans.size ());
      found = true;
      break;
    }
    if (!found)
      puts ("NO MINIMAL CORRIDOR");
  }
  return 0;
}

