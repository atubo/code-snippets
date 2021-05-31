
class EulerSieve {
 private:
  int n_;
  void alloc() {
    isPrime = new bool[n_+1]{};
    memset(isPrime, 1, (n_+1)*sizeof(bool));
    mu = new int[n_+1]{};
    phi = new int[n_+1]{};
    sigma = new int[n_+1]{};
  }

  void dealloc() {
    delete[] isPrime;
    delete[] mu;
    delete[] phi;
    delete[] sigma;
  }
 public:
  bool* isPrime;
  int* mu;
  int* phi;
  int* sigma;
  vector<int> primes;

  EulerSieve(int N) : n_(N) {
    assert(N > 1);

    alloc();

    // local variable to calculate sigma (divisor function)
    // i = pj^k * ..., and pi(i) = (1 + pj + pj^2 + ...)
    vector<int> pi(N+1);

    isPrime[0] = isPrime[1] = false;
    mu[1] = 1;
    phi[1] = 1;
    sigma[1] = 1;
    for (int i = 2; i <= N; i++) {
      if (isPrime[i]) {
        primes.push_back(i);
        mu[i] = -1;
        phi[i] = i - 1;
        sigma[i] = pi[i] = i + 1;
      }

      for (int j = 0; j < (int)primes.size(); j++) {
        int64_t t = (int64_t)i * primes[j];
        if ( t > N) break;
        isPrime[t] = false;
        if (i % primes[j] == 0) {
          mu[t] = 0;
          phi[t] = phi[i] * primes[j];
          pi[t] = pi[i] * primes[j] + 1;
          sigma[t] = sigma[i]/pi[i] * pi[t];
          break;
        } else {
          mu[t] = -mu[i];
          phi[t] = phi[i] * (primes[j] - 1);
          pi[t] = primes[j] + 1;
          sigma[t] = sigma[primes[j]] * sigma[i];
        }
      }
    }
  }

  ~EulerSieve() {
    dealloc();
  }
};
