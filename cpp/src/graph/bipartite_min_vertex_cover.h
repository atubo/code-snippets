
class BipartiteMinVertexCover {
private:
    const int nx_, ny_;
    const int *cx_, *cy_;
    const bool * const* g_;

    bool *mk_, *mkx_, *mky_;

    void path(int u) {
        mkx_[u] = true;
        for (int v = 0; v < ny_; v++) {
            if (g_[u][v] && !mk_[v]) {
                mk_[v] = true;
                if (cy_[v] != -1) {
                    mky_[v] = true;
                    path(cy_[v]);
                }
            }
        }
    }

public:
    BipartiteMinVertexCover(int nx, int ny,
                            const int *cx, const int *cy,
                            const bool *const *g)
        :nx_(nx), ny_(ny), cx_(cx), cy_(cy), g_(g) {
            mk_ = new bool[ny_]{};
            mkx_ = new bool[nx_]{};
            mky_ = new bool[ny_]{};
        }

    ~BipartiteMinVertexCover() {
        delete[] mky_;
        delete[] mkx_;
        delete[] mk_;
    }

    vector<int> calcMinVertexCover() {
        // [0, nx-1] means left side
        // [nx, nx+ny-1] means right side
        vector<int> ret;
        for (int i = 0; i < nx_; i++) {
            if (cx_[i] == -1) {
                memset(mk_, 0, ny_ * sizeof(bool));
                path(i);
            }
        }
        for (int i = 0; i < nx_; i++) {
            if (!mkx_[i]) {
                ret.push_back(i);
            }
        }
        for (int i = 0; i < ny_; i++) {
            if (mky_[i]) {
                ret.push_back(i+nx_);
            }
        }
        return ret;
    }
};
