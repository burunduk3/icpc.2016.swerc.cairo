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
    /*
    char a[n][m], b[n][m];
    memset (a, 0, sizeof (a[0][0]) * n * m);
    memset (b, 0, sizeof (b[0][0]) * n * m);
     */
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

    bool c[nodes], f[nodes];
    int h[nodes], d[nodes];
    memset (c, 0, sizeof (c[0]) * nodes);
    memset (f, 0, sizeof (f[0]) * nodes);
    vector <int> tmp;

    function <int (int, int, int)> dfs;
    // auto dfs = [&]( auto& dfs, int u, int p, int uh ) {
    dfs = [&]( int u, int p, int uh ) {
      c[u] = true;
      h[u] = uh;
      d[u] = uh;
      tmp.push_back (u);
      // fprintf (stderr, "u=%d (%d %d %d)\n", u, u / (n * m), u / m % n, u % m);
      int mask = node_mask[u];
      int unique = mask;
      int cnt = 0;
      for (auto v : g[u]) {
        // fprintf (stderr, "  --> v=%d (%d %d %d)\n", v, v / (n * m), v / m % n, v % m);
        if (v == p)
          continue;
        if (c[v]) {
          d[u] = min (d[u], h[v]);
          continue;
        }
        // int res = dfs (dfs, v, u, uh + 1);
        int res = dfs (v, u, uh + 1);
        if (++cnt >= 2 && p == -1)
          f[u] = true;
        if (d[v] >= h[u] && p != -1)
          f[u] = true;
        d[u] = min (d[u], d[v]);
        unique &= ~(res & 15);
        unique |= (res >> 4) & ~mask;
        mask |= res & 15;
      }
      /*
      if (p != -1)
        f[u] = d[u] >= h[u];
       */
      return mask | (unique << 4);
    };
    bool found = false;
    for (int u = 0; u < nodes; u++) {
      if (c[u] || g[u].size () == 0)
        continue;
      tmp.clear ();
      // int res = dfs (dfs, u, -1, h);
      int res = dfs (u, -1, 0);
      // fprintf (stderr, "[u=%d] nodes=%d res=%#02x\n", u, (int)tmp.size (), res);
      // if (tmp.size () == 10)
      //   return 1;
      // return 1;
      if ((res & 15) != 15)
        continue;
      int unique = res >> 4;
      bool ok = true;
      for (auto v : tmp) {
        if (unique & node_mask[v])
          continue;
        if (g[v].size () == 1 || !f[v]) {
          // fprintf (stderr, "extra point: v=%d (%d %d %d), mask=%d, deg=%d, f=%c\n", v, v / (n * m), v / m % n, v % m, node_mask[v], (int)g[v].size (), "NY"[f[v]]);
          ok = false;
          break;
        }
      }
      if (!ok)
        continue;
      printf ("%d\n", (int)tmp.size ());
      found = true;
      break;
    }
    if (!found)
      puts ("NO MINIMAL CORRIDOR");
  }
  return 0;
}

