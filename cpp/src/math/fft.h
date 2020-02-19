
class Fft {
 public:
  constexpr const static double PI = 3.14159265359;
  static void four1(vector<double> &data, const int isign) {
    int nn = data.size() / 2;
    int n = nn << 1;
    int j = 1;
    for (int i = 1; i < n; i+=2) {
      if (j > i) {
        swap(data[j-1], data[i-1]);
        swap(data[j], data[i]);
      }
      int m = nn;
      while (m >= 2 && j > m) {
        j -= m;
        m >>= 1;
      }
      j += m;
    }

    int mmax = 2;
    while (n > mmax) {
      int istep = mmax << 1;
      double theta = isign * (2 * PI / mmax);
      double wtemp = sin(0.5 * theta);
      double wpr = - 2.0 * wtemp * wtemp;
      double wpi = sin(theta);
      double wr = 1.0;
      double wi = 0.0;
      for (int m = 1; m < mmax; m += 2) {
        for (int i = m; i <= n; i += istep) {
          j = i + mmax;
          double tempr = wr * data[j-1] - wi * data[j];
          double tempi = wr * data[j] + wi * data[j-1];
          data[j-1] = data[i-1] - tempr;
          data[j] = data[i] - tempi;
          data[i-1] += tempr;
          data[i] += tempi;
        }
        wr = (wtemp=wr)*wpr - wi*wpi + wr;
        wi = wi*wpr + wtemp*wpi + wi;
      }
      mmax = istep;
    }
  }

  static vector<double> innerProduct(const vector<double> &x,
      const vector<double> &y) {
    const int n = x.size() / 2;
    vector<double> ret(2*n);
    for (int i = 0; i < n; i++) {
      double a = x[2*i], b = x[2*i+1];
      double c = y[2*i], d = y[2*i+1];
      ret[2*i] = a*c - b*d;
      ret[2*i+1] = a*d + b*c;
    }
    return ret;
  }

  // f and g are real number coefficient polynomials
  // In the function we will expand them to complex number
  // and return another real number coefficient vector
  static vector<double> polynomialProduct(
      const vector<double>& f, const vector<double>& g) {
    int n1 = f.size();
    int n2 = g.size();
    int n = 1;
    while (n < n1+n2-1) n <<= 1;
    vector<double> fc(2*n, 0), gc(2*n, 0);
    for (int i = 0; i < n; i++) {
      fc[2*i] = (i < n1 ? f[i] : 0);
      gc[2*i] = (i < n2 ? g[i] : 0);
    }

    four1(fc, 1);
    four1(gc, 1);

    auto prod = innerProduct(fc, gc);

    four1(prod, -1);

    vector<double> ret(n1+n2-1);
    for (int i = 0; i < n1+n2-1; i++) {
      ret[i] = prod[2*i]/n;
    }
    return ret;
  }
};
