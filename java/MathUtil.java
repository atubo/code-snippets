public class MathUtil {
    // a ^ b mod n
    private static int modExp(int a, int b, int n) {
        long c = 0;
        long d = 1;
        ArrayList<Integer> bRep = new ArrayList<Integer>();
        int bp = b;
        while (bp > 0) {
            bRep.add(bp & 1);
            bp = bp >> 1;
        }
        for (int i = bRep.size() - 1; i >= 0; i--) {
            c *= 2;
            d = (d * d) % n;
            if (bRep.get(i) == 1) {
                c += 1;
                d = (d * a) % n;
            }
        }
        
        return (int)d;
    }
}
