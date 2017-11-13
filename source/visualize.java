/*
  Visualizer for icpc.2016.swerc.cairo
  To use with showme library: https://github.com/mikhail-dvorkin/showme

  SWERC 2016 
  Problem G - Cairo Corridor

  @author: Oleg Davydov burunduk3@gmail.com
  @date: 2017-11-13
 */

import java.awt.Color;
import java.io.*;
import java.util.*;

import showme.figure.*;
import showme.framework.Visualizer;

public class visualize implements Visualizer {
    int n, m;
    boolean[][] a;
    boolean[][] b;
    int node_mask[];
    ArrayList <Integer> g[];
    boolean c[], f[];
    int h[], d[];
    ArrayList <Integer> tmp;

    // nodes numeration
    int node ( int is_b, int i, int j ) {
      // System.err.println ("[debug] node (" + is_b + ", " + i + ", " + j + ")");
      if (i < 0)
        return -1;
      if (j < 0)
        return -2;
      if (i >= n)
        return -3;
      if (j >= m)
        return -4;
      if ((is_b == 1 ? b : a)[i][j])
        return -5;
      return is_b * n * m + i * m + j;
    }

    void edge ( int x, int y ) {
      if (x == -5 || y == -5)
        return;
      if (y < 0) {
        node_mask[x] |= (1 << (-y - 1));
        return;
      }
      g[x].add (y);
    }

    int dfs ( int u, int p, int uh ) {
      c[u] = true;
      h[u] = uh;
      d[u] = uh;
      tmp.add (u);
      int mask = node_mask[u];
      int unique = mask;
      int cnt = 0;
      for (int i = 0; i < g[u].size (); i++) {
        int v = g[u].get (i);
        if (v == p)
          continue;
        if (c[v]) {
          d[u] = Math.min (d[u], h[v]);
          continue;
        }
        int res = dfs (v, u, uh + 1);
        if (++cnt >= 2 && p == -1)
          f[u] = true;
        if (d[v] >= h[u] && p != -1)
          f[u] = true;
        d[u] = Math.min (d[u], d[v]);
        unique &= ~(res & 15);
        unique |= (res >> 4) & ~mask;
        mask |= res & 15;
      }
      return mask | (unique << 4);
    }

    int[][] solve () {
      int nodes = 2 * n * m;
      node_mask = new int[nodes];
      Arrays.fill (node_mask, 0);
      g = new ArrayList[nodes];
      for (int i = 0; i < nodes; i++)
        g[i] = new ArrayList <Integer> ();
    
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
          if ((i ^ j) % 2 == 1) { // vertical
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

      c = new boolean[nodes];
      f = new boolean[nodes];
      h = new int[nodes];
      d = new int[nodes];

      tmp = new ArrayList <Integer> ();

      int result[][] = new int[n][m];
      // Hope Java does this automatically.
      // Arrays.fill (result, 0);

      boolean found = false;
      for (int u = 0; u < nodes; u++) {
        if (c[u] || g[u].size () == 0)
          continue;
        tmp.clear ();
        int res = dfs (u, -1, 0);
        if ((res & 15) != 15)
          continue;
        for (int i = 0; i < tmp.size (); i++) {
          int v = tmp.get (i);
          int node_j = v % m;
          int node_i = v / m % n;
          int node_k = v / m / n;
          result[node_i][node_j] |= 1 << (node_k * 2);
        }
        int unique = res >> 4;
        for (int i = 0; i < tmp.size (); i++) {
          int v = tmp.get (i);
          if ((unique & node_mask[v]) != 0)
            continue;
          if (g[v].size () == 1 || !f[v]) {
            int node_j = v % m;
            int node_i = v / m % n;
            int node_k = v / m / n;
            result[node_i][node_j] |= 2 << (node_k * 2);
          }
        }
      }
      return result;
    }

    @Override
    public List <Figure> process ( File f ) throws IOException {
        List <Figure> figures = new ArrayList <Figure> ();
        Scanner in = new Scanner (f);
        int tn = in.nextInt ();
        double x0 = 0.0, y0 = 0.0;
        for (int tt = 0; tt < tn; tt++) {
          n = in.nextInt ();
          m = in.nextInt ();
          in.nextLine ();
          a = new boolean[n][m];
          b = new boolean[n][m];
          for (int i = 0; i < n; i++) {
            String line = in.nextLine ();
            for (int j = 0; j < m; j++) {
              a[i][j] = line.charAt (2 * j) == '1';
              b[i][j] = line.charAt (2 * j + 1) == '1';
            }
          }

          if (n > 20 || m > 20) {
            // test too large
            continue;
          }

          int[][] res = solve ();

          double cs = Math.sqrt (3.0) / 2.0;
          double sn = 0.5;
          double dd = Math.sqrt (3.0);
          for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
              double y = -y0 - 2.0 - dd * (i + 1);
              double x = x0 + 2.0 + dd * (j + 1);
              if ((i + j) % 2 == 0) {
                double xs1[] = {x + -sn-cs, x + -cs, x + 0.0, x + 0.0, x + -cs};
                double ys1[] = {y + 0.0, y - cs, y - (cs-sn), y - (sn-cs), y - -cs};
                Color color = a[i][j] ? Color.GRAY : Color.WHITE;
                if ((res[i][j] & 3) == 1)
                  color = Color.YELLOW;
                if ((res[i][j] & 3) == 3)
                  color = Color.RED;
                figures.add (new Polygon (xs1, ys1).setFillColor (color).setFillOpacity (1));
                double xs2[] = {x + sn+cs, x + cs, x + 0.0, x + 0.0, x + cs};
                double ys2[] = {y + 0.0, y - cs, y - (cs-sn), y - (sn-cs), y - -cs};
                color = b[i][j] ? Color.GRAY : Color.WHITE;
                if ((res[i][j] & 12) == 4)
                  color = Color.YELLOW;
                if ((res[i][j] & 12) == 12)
                  color = Color.RED;
                figures.add (new Polygon (xs2, ys2).setFillColor (color).setFillOpacity (1));
              } else {
                double xs1[] = {x + 0.0, x + cs, x + cs-sn, x + sn-cs, x + -cs};
                double ys1[] = {y + (sn+cs), y - -cs, y + 0.0, y + 0.0, y - -cs};
                Color color = a[i][j] ? Color.GRAY : Color.WHITE;
                if ((res[i][j] & 3) == 1)
                  color = Color.YELLOW;
                if ((res[i][j] & 3) == 3)
                  color = Color.RED;
                figures.add (new Polygon (xs1, ys1).setFillColor (color).setFillOpacity (1));
                double xs2[] = {x + 0.0, x + cs, x + cs-sn, x + sn-cs, x + -cs};
                double ys2[] = {y - (sn+cs), y - cs, y + 0.0, y + 0.0, y - cs};
                color = b[i][j] ? Color.GRAY : Color.WHITE;
                if ((res[i][j] & 12) == 4)
                  color = Color.YELLOW;
                if ((res[i][j] & 12) == 12)
                  color = Color.RED;
                figures.add (new Polygon (xs2, ys2).setFillColor (color).setFillOpacity (1));
              }
            }
          }
          x0 += dd * m + 5.0;
        }
        // figures.add (new Circle (2.0, 2.0, 1.0).setFillColor (Color.MAGENTA).setFillOpacity (1));
        return figures;
    }
}

