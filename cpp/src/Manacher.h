// see https://www.felix021.com/blog/read.php?2040
struct Manacher {
    const int length_;
    // p[i] stores maximum radius from position i (including i)
    // in the *modified* string (including spaces between letters)
    // note place before the first char is 1, first char is 2
    // second char is 4, etc.
    int *p;
    char *s;
    int *maxlen;

    Manacher(const string &sin):length_(sin.length()) {
        alloc();

        // put special charaters at the begining and between letters
        s[0] = '$';
        s[1] = '#';
        for (int i = 0; i < (int)sin.length(); i++) {
            s[i*2+2] = sin[i];
            s[i*2+3] = '#';
        }

        int mx = 0, id = 0;
        for (int i = 1; s[i] != '\0'; i++) {
            p[i] = mx > i ? min(p[2*id-i], mx-i) : 1;
            while (s[i+p[i]] == s[i-p[i]]) p[i]++;
            if (i + p[i] > mx) {
                mx = i + p[i];
                id = i;
            }
        }
    }

    ~Manacher() {
        dealloc();
    }

    // some utility functions
    // find for each position the maximum length of the palindrom start there
    // note the index starts from 0
    void calcMaxlen() {
        for (int i = 1; s[i] != '\0'; i++) {
            int pos = (i - p[i]) / 2;
            maxlen[pos] = max(maxlen[pos], p[i]-1);
        }
        for (int i = 1; s[i] != '\0'; i++) {
            maxlen[i] = max(maxlen[i-1]-2, maxlen[i]);
        }
    }

private:
    void alloc() {
        p = new int[2*length_+10]{};
        s = new char[2*length_+10]{};
        maxlen = new int[length_+10]{};
    }

    void dealloc() {
        delete[] p;
        delete[] s;
        delete[] maxlen;
    }
};
