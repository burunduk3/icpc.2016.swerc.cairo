#include <cassert>
#include <cstdio>
#include <cstdlib>

int main ( int argc, char **argv ) {
  assert (argc == 4);
  int t = atoi (argv[1]);
  int type = atoi (argv[2]);
  int n = atoi (argv[3]);
  int a[n][n];
  int b[n][n];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      a[i][j] = b[i][j] = 1;
      if (i == 0 && j != 0 && j != n - 1 && (type < 2 || j >= n - 2)) {
        a[i][j] = 0;
        b[i][j] = j % 2;
      }
      if (i == n - 1 && j != 0 && j != n - 1) {
        a[i][j] = j % 2;
        b[i][j] = 0;
      }
      if (j == 0 && i != 0 && i != n - 1 && (type < 2 || i >= n - 2)) {
        a[i][j] = 0;
        b[i][j] = !(i % 2);
      }
      if (j == n - 1 && i != 0 && i != n - 1) {
        a[i][j] = !(i % 2);
        b[i][j] = 0;
      }
    }
  if (type == 0) {
    b[0][0] = 0;
  }
  b[n - 1][0] = 0;
  a[0][n - 1] = 0;
  a[n - 1][n - 1] = 0;

  printf ("%d\n", t);
  for (int tt = 0; tt < t; tt++) {
    printf ("%d %d\n", n, n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++)
        printf ("%d%d", a[i][j], b[i][j]);
      puts ("");
    }
  }
  return 0;
}
