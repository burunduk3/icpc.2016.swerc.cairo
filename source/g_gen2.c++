#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>

using namespace std;

int main ( int argc, char **argv ) {
  assert (argc == 4);
  int n = atoi (argv[1]);
  int m = atoi (argv[2]);
  int rotate = atoi (argv [3]);
  int a[n + 3][m + 3], b[n + 3][m + 3];

  memset (a, 0, sizeof (a[0][0]) * (n + 3) * (m + 3));
  memset (b, 0, sizeof (b[0][0]) * (n + 3) * (m + 3));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      a[i][j] = b[i][j] = 1;

  for (int j = 2; j < m; j += 3) {
    for (int i = 0; i < n; i++) {
      a[i][j] = 0;
      if ((i + j) % 2 == 1)
        b[i][j] = 0;
      if (j < m - 1) {
        if ((i + j) % 2 == 0)
          a[i][j + 1] = 0;
        b[i][j + 1] = 0;
      }
    }
    if (j % 2 == 0) {
      a[0][j - 1] = 0;
      if (j < m - 1)
        a[0][j + 1] = 1;
    } else {
      a[0][j - 1] = 0;
      b[0][j - 1] = 0;
      a[0][j] = 1;
    }
    if ((j + n - 1) % 2 == 1) {
      b[n - 1][j] = 1;
      if (j < m - 1) {
        b[n - 1][j + 1] = 1;
        a[n - 1][j + 1] = 0;
      }
    } else {
      a[n - 1][j] = 1;
      b[n - 1][j] = 0;
      if (j < m - 1)
        b[n - 1][j + 1] = 1;
    }
  }
  for (int i = 0; i < n; i++)
    a[i][m - 1] = b[i][m - 1] = 1;
  if (m % 3 == 1)
    if ((m + n) % 2 == 0)
      a[n - 1][m - 1] = b[n - 1][m - 1] = 0;
    else
      b[n - 1][m - 1] = 0;
  else if (m % 2 == 0)
    a[0][m - 1] = 0;
  else
    a[0][m - 1] = b[0][m - 1] = 0;
    
  b[0][0] = 0;
  a[1][0] = 0;
  a[1][1] = 0;
  a[2][1] = 0;

  printf ("%d\n", 1);
  if (rotate && (m + n) % 2 == 1)
    swap (n, m);
  printf ("%d %d\n", n, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int ii = i, jj = j;
      if (rotate) {
        if ((n + m) % 2 == 0)
          ii = n - 1 - i, jj = m - 1 - j;
        else
          jj = n - 1 - i, ii = m - 1 - j;
      }
      if (rotate)
        printf ("%d%d", b[ii][jj], a[ii][jj]);
      else
        printf ("%d%d", a[ii][jj], b[ii][jj]);
    }
    puts ("");
  }
  return 0;
}

