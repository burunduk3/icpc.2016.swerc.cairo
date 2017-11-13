/*
 * Решение от команды PetrSU Bonus Round (Ермишин, Кобелева, Ермолин)
 */
//#pragma GCC target("sse4.1")
//#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define mp make_pair
#define pb push_back


const int MAXN = 300;
const int MAXM = 300;
const int MAXV = (int) 2e5;

int a[MAXN][MAXM], b[MAXN][MAXM];
int n, m, cntV;
int L, R, D, U;

unordered_set <int> gr[MAXV];
int was[MAXV], cnt;
set <int> comp[MAXV];


void addEdge (int x, int y) {
	gr[x].insert (y);
}

int getV (int i, int j, int Type) {
	return i * 2 * m + j * 2 + Type;
}

void gor (int i, int j) {
	int numA = getV (i, j, 0);
	int numB = getV (i, j, 1);

	// a 
	if (!a[i][j]) {
		if (!b[i][j])
			addEdge (numA, numB);
		if (j - 1 >= 0) {
			if (!a[i][j - 1])
				addEdge (numA, getV (i, j - 1, 0));
			if (!b[i][j - 1])
				addEdge (numA, getV (i, j - 1, 1));
		}
		if (i - 1 >= 0 && !b[i - 1][j])
			addEdge (numA, getV (i - 1, j, 1));
		if (i + 1 < n && !a[i + 1][j]) 
			addEdge (numA, getV (i + 1, j, 0));
	}
	// b
	if (!b[i][j]) {
		if (!a[i][j])
			addEdge (numB, numA);
		if (j + 1 < m) {
			if (!a[i][j + 1])
				addEdge (numB, getV (i, j + 1, 0));
			if (!b[i][j + 1])
				addEdge (numB, getV (i, j + 1, 1));
		}
		if (i - 1 >= 0 && !b[i - 1][j])
			addEdge (numB, getV (i - 1, j, 1));
		if (i + 1 < n && !a[i + 1][j])
			addEdge (numB, getV (i + 1, j, 0));		
	}
}

void vert (int i, int j) {
	int numA = getV (i, j, 0);
	int numB = getV (i, j, 1);

	// a 
	if (!a[i][j]) {
		if (!b[i][j])
			addEdge (numA, numB);
		if (i - 1 >= 0) {
			if (!a[i - 1][j])
				addEdge (numA, getV (i - 1, j, 0));
	        if (!b[i - 1][j])
				addEdge (numA, getV (i - 1, j, 1));
		}
		if (j - 1 >= 0 && !b[i][j - 1]) 
			addEdge (numA, getV (i, j - 1, 1));
		if (j + 1 < m && !a[i][j + 1]) 
			addEdge (numA, getV (i, j + 1, 0));
	}

	// b
	if (!b[i][j]) {
		if (!a[i][j])
			addEdge (numB, numA);
		if (i + 1 < n) {
		    if (!a[i + 1][j])
				addEdge (numB, getV (i + 1, j, 0));
			if (!b[i + 1][j])
				addEdge (numB, getV (i + 1, j, 1));
		}
		if (j - 1 >= 0 && !b[i][j - 1])
			addEdge (numB, getV (i, j - 1, 1));
		if (j + 1 < m && !a[i][j + 1])
			addEdge (numB, getV (i, j + 1, 0));			
	}
}

void build () {
	cntV = 2 * n * m;
	L = cntV++;
	R = cntV++;
	D = cntV++;
	U = cntV++;
 	for (int i = 0; i < cntV; i++) {
    	gr[i].clear ();
    	comp[i].clear ();
    }
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < m; j++) {
    		if ((i + j) & 1) {
    			vert (i, j);
    			if (!i && !a[i][j]) {
    				addEdge (getV (i, j, 0), U);
    				addEdge (U, getV (i, j, 0));   
    			}
    			if (!j) {
    				if (!a[i][j]) {
    					addEdge (getV (i, j, 0), L);
    					addEdge (L, getV (i, j, 0));   
    				}
    				if (!b[i][j]) {
    					addEdge (getV (i, j, 1), L);
    					addEdge (L, getV (i, j, 1));   		
    				}
    			}
    			if (i == n - 1 && !b[i][j]) {
    				addEdge (getV (i, j, 1), D);
    				addEdge (D, getV (i, j, 1));   
    			}
    			if (j == m - 1) {
    				if (!a[i][j]) {
    					addEdge (getV (i, j, 0), R);
    					addEdge (R, getV (i, j, 0));   
    			    }
    			    if (!b[i][j]) {
    					addEdge (getV (i, j, 1), R);
    					addEdge (R, getV (i, j, 1));   		
    				}
    			}
    		} else {
    			gor (i, j);
    			if (!j && !a[i][j]) {
    				addEdge (getV (i, j, 0), L);
    				addEdge (L, getV (i, j, 0));   
    			}
    			if (!i) {
    				if (!a[i][j]) {
    					addEdge (getV (i, j, 0), U);
    					addEdge (U, getV (i, j, 0));   
    				}
    				if (!b[i][j]) {
    					addEdge (getV (i, j, 1), U);
    					addEdge (U, getV (i, j, 1));   		
    				}
    			}
    			if (j == m - 1 && !b[i][j]) {
    				addEdge (getV (i, j, 1), R);
    				addEdge (R, getV (i, j, 1));   
    			}
    			if (i == n - 1) {
    				if (!a[i][j]) {
    					addEdge (getV (i, j, 0), D);
    					addEdge (D, getV (i, j, 0));   
    			    }
    			    if (!b[i][j]) {
    					addEdge (getV (i, j, 1), D);
    					addEdge (D, getV (i, j, 1));   		
    				}
    			}
    		}
    	}
    }	
}

void load () {
	cin >> n >> m;
	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;         
		for (int j = 0; j < (m << 1); j += 2) {
			a[i][j >> 1] = s[j] - '0';
			b[i][j >> 1] = s[j + 1] - '0';			
		}
	}        
	build ();
} 
   
bool isBoard (int v) {
	return v == U || v == D || v == L || v == R;
}

set <int> qq;

void dfs1 (int v) {
	was[v] = 1;
	comp[cnt].insert (v);
	for (auto to : gr[v]) {
		if (isBoard (to))
			comp[cnt].insert (to);
		if (!was[to])
			dfs1 (to);
	}
}

void dfs2 (int v) {
	was[v] = 1;
	for (auto to : gr[v]) {
		if (isBoard (to))
			qq.insert (to);
		if (!was[to]) 
			dfs2 (to);
	}
}

vector <int> lst;
unordered_set <int> cgr[MAXV];

int solve () {
	memset (was, 0, sizeof (was));
	was[L] = was[R] = was[U] = was[D] = 1;
	cnt = 0;
	for (int i = 0; i < cntV; i++)
		if (!was[i]) {
			dfs1 (i);
			cnt++;
		}
	int ix = -1;
	for (int i = 0; i < cnt; i++) {
		if (comp[i].count (L) && comp[i].count (R) && comp[i].count (D) && comp[i].count (U)) 
			ix = i;
	}
	//cerr << "here1\n";	
	if (ix == -1)
		return -1;	
	memset (was, 0, sizeof (was));
	int v1 = -1, v2 = -1;
	for (auto v : comp[ix]) {
		if (!isBoard (v)) {
			v2 = v1;
			v1 = v;
		}
	}
	for (int i = 0; i < MAXV; i++) {
		cgr[i] = gr[i];
		cgr[i].erase (U);
		cgr[i].erase (D);
		cgr[i].erase (R);
		cgr[i].erase (L);		
	}

  lst.clear ();
  bool flag = false;
  for (auto v : comp[ix]) {
  	if (isBoard (v)) continue;
  	if (cgr[v].size () == 2u && !flag) {
  		lst.pb (v);
  		flag = true;
  	}
  	if (cgr[v].size () == 1u || cgr[v].size () >= 3u) {
   	  //cerr << (v / (2 * m)) << ' ' << (v % (2 * m)) << endl;
   		lst.pb (v);		
   	}
   	if (cgr[v].size () >= 3) {
   		for (auto it : cgr[v])
   			lst.pb (it);
   	}
   	
  }
  for (auto v : lst) {
   	qq.clear ();
   	memset (was, 0, sizeof (was));
  	was[v] = was[U] = was[D] = was[R] = was[L] = 1;
  	if (v == v1)
    	dfs2 (v2);
    else dfs2 (v1);
    if (qq.count (U) && qq.count (D) && qq.count (L) && qq.count (R)) {
      cerr << (v / (2 * m)) << ' ' << (v % (2 * m)) << endl;
    	return -1;
    }
  }

  int ans = comp[ix].size () - 4;
  return ans;
}
	
int main () {
	ios_base::sync_with_stdio (false);
	cin.tie (0);
#ifdef LOCAL            
	auto ___ = freopen ("file.in", "r", stdin);
	___ = freopen ("file.out", "w", stdout);
	assert (___);
	double st = clock ();
#endif

	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		load ();
		int ans = solve ();
		if (ans == -1) {
			cout << "NO MINIMAL CORRIDOR\n";
		} else {
			cout << ans << '\n';
		}
	}

#ifdef LOCAL
	clog << (clock () - st) / CLOCKS_PER_SEC << endl;
#endif

	return 0;
}
