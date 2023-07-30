
#include "common.h"

// compute the prefix function for string `s`:
// for every character substring [0 : i] (both inclusive), compute the longest proper prefix that
// is also a suffix.
// O(N)
//
// computing `prefunc` on a string of the type `wwww#ttttttt` will give for
// every `t` the amount of characters from `w` that match (ie. search for the
// string `w` inside the string `t`).
void prefunc(const string &s, vector<int> &p)
{
    int N = s.size(), j;
    p.resize(N), p[0] = 0;
    repx(i, 1, N)
    {
        for (j = p[i - 1]; j > 0 && s[j] != s[i];)
            j = p[j - 1];
        p[i] = j + (s[j] == s[i]);
    }
}
