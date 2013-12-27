public class BIT {
    private final int N;
    private int[] tree;

    public BIT(int N) {
        this.N = N;
        tree = new int[N + 1];
    }

    private void set(int x, int v) {
        while (x <= N) {
            tree[x] += v;
            x += (x & -x);
        }
    }

    private int get(int x) {
        int res = 0;
        while (x != 0) {
            res += tree[x];
            x -= (x & -x);
        }
        return res;
    }
}
