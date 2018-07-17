// Hungarian method to find maximal match in bipartite graph
// using DFS, time complexity O(N^3)
class Hungarian {
private:
    static const int MAXN = 55;
    int nx_, ny_;
    int** g;

    int *cx, *cy;
    int *mk;

    void alloc() {
        g = new int*[nx_];
        for (int i = 0; i < nx_; i++) {
            g[i] = new int[ny_];
        }
        cx = new int[nx_];
        cy = new int[ny_];
        mk = new int[ny_];
    }

    void dealloc() {
        for (int i = 0; i < nx_; i++) {
            delete[] g[i];
        }
        delete[] g;

        delete[] cx;
        delete[] cy;
        delete[] mk;
    }

    int path(int u) {
        for (int v = 0; v < ny_; v++) {
            if (g[u][v] && !mk[v]) {
                mk[v] = 1;
                if (cy[v] == -1 || path(cy[v])) {
                    cx[u] = v;
                    cy[v] = u;
                    return 1;
                }
            }
        }
        return 0;
    }

public:
    Hungarian(int nx, int ny): nx_(nx), ny_(ny) {
        alloc();
        reset();
    }

    ~Hungarian() {
        dealloc();
    }

    void reset() {
        for (int i = 0; i < nx_; i++) {
            memset(g[i], 0, ny_ * sizeof(int));
        }
    }

    void addEdge(int x, int y) {
        g[x][y] = 1;
    }

    int maxMatch() {
        int res = 0;
        memset(cx, -1, nx_ * sizeof(int));
        memset(cy, -1, ny_ * sizeof(int));
        for (int i = 0; i < nx_; i++) {
            if (cx[i] == -1) {
                memset(mk, 0, ny_ * sizeof(int));
                res += path(i);
            }
        }
        return res;
    }
};
