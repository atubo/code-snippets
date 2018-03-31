// note all indices are 1-based
class Fenwick3D {
public:
    const int Nx, Ny, Nz;
    int ***root;

    Fenwick3D(int Nx_, int Ny_, int Nz_): Nx(Nx_), Ny(Ny_), Nz(Nz_) {
        alloc();
    }

    ~Fenwick3D() {
        dealloc();
    }

    void add(int x, int y, int z, int t) {
        for (int i = x; i <= Nx; i += lowbit(i)) {
            addx(i, y, z, t);
        }
    }

    int query(int x1, int y1, int z1, int x2, int y2, int z2) const {
        if (x1 > x2 || y1 > y2 || z1 > z2) return 0;
        int res2 = query(x2, y2, z2) - query(x1-1, y2, z2) -
            query(x2, y1-1, z2) + query(x1-1, y1-1, z2);
        int res1 = query(x2, y2, z1-1) - query(x1-1, y2, z1-1) -
            query(x2, y1-1, z1-1) + query(x1-1, y1-1, z1-1);
        return res2 - res1;
    }

    // query range (1, 1) -> (x, y, z) inclusive
    int query(int x, int y, int z) const {
        int res = 0;
        while (x) {
            res += queryx(x, y, z);
            x -= lowbit(x);
        }
        return res;
    }

private:
    void alloc() {
        root = new int**[Nx+1];
        for (int i = 0; i <= Nx; i++) {
            root[i] = new int*[Ny+1];
            for (int j = 0; j <= Ny; j++) {
                root[i][j] = new int[Nz+1]{};
            }
        }
    }

    void dealloc() {
        for (int i = 0; i <= Nx; i++) {
            for (int j = 0; j <= Ny; j++) {
                delete[] root[i][j];
            }
            delete[] root[i];
        }
        delete[] root;
    }

    int lowbit(int x) const {return x & -x;}

    void addx(int x, int y, int z, int t) {
        for (int i = y; i <= Ny; i += lowbit(i)) {
            addy(x, i, z, t);
        }
    }

    void addy(int x, int y, int z, int t) {
        for (int i = z; i <= Nz; i+= lowbit(i)) {
            root[x][y][i] += t;
        }
    }

    int queryx(int x, int y, int z) const {
        int res = 0;
        while (y) {
            res += queryy(x, y, z);
            y -= lowbit(y);
        }
        return res;
    }

    int queryy(int x, int y, int z) const {
        int res = 0;
        while (z) {
            res += root[x][y][z];
            z -= lowbit(z);
        }
        return res;
    }
};
