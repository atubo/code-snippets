#include <functional>
#include <vector>

using namespace std;

// Hungarian method to find maximal match in bipartite graph
// using DFS, time complexity O(N^3)
class Hungarian {
public:
	Hungarian(int nx_, int ny_):
		nx(nx_), ny(ny_), cx(nx_, -1), cy(ny_, -1), mk(ny_, false) {}

	int maxMatch(function<bool(int, int)> connect) {
		int res = 0;
		for (int i = 0; i < nx; i++) {
			if (cx[i] == -1) {
				mk.assign(ny, false);
				res += path(i, connect);
			}
		}
		return res;
	}

private:
	int path(int u, function<bool(int, int)> connect) {
		for (int v = 0; v < ny; v++) {
			if (!mk[v] && connect(u, v)) {
				mk[v] = true;
				if (cy[v] == -1 || path(cy[v], connect)) {
					cx[u] = v;
					cy[v] = u;
					return 1;
				}
			}
		}
		return 0;
	}

	int nx;
	int ny;
	vector<int> cx;
	vector<int> cy;
	vector<bool> mk;
};
