// see https://www.felix021.com/blog/read.php?2040
namespace Manacher {
const int MAXN = 1000;

// p[i] stores maximum radius from position i (including i)
// in the *modified* string (including spaces between letters)
// note place before the first char is 1, first char is 2
// second char is 4, etc.
int p[2*MAXN+10];
char s[2*MAXN+10];
int maxlen[MAXN+10];

void manacher(const string &sin) {
    memset(p, 0, sizeof(p));
    memset(s, 0, sizeof(s));
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

// some utility functions
// find for each position the maximum lenght of the palindrom start there
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
}
