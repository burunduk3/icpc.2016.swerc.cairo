#include <testlib.h>

const int limit_tests = 10;
const int limit_res = 250;

int main () {
  registerValidation ();
  int tn = inf.readInt (1, limit_tests, "T");
  inf.readEoln ();
  int sum_n = 0, sum_m = 0;
  for (int t = 0; t < tn; t++) {
    int n = inf.readInt (1, limit_res, format ("N_%d", t + 1));
    inf.readSpace ();
    int m = inf.readInt (1, limit_res, format ("M_%d",t + 1));
    inf.readEoln ();
    sum_n += n;
    sum_m += m;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int c1 = inf.readChar ();
        int c2 = inf.readChar ();
        ensuref (c1 == '0' || c1 == '1', "tiling should consist only from '0' and '1'");
        ensuref (c2 == '0' || c2 == '1', "tiling should consist only from '0' and '1'");
      }
      inf.readEoln ();
    }
  }
  ensuref (sum_n <= limit_res, "sum of N exceeds limit");
  ensuref (sum_m <= limit_res, "sum of M exceeds limit");
  inf.readEof ();
  return 0;
}

