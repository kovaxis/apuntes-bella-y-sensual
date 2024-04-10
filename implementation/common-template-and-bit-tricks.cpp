#pragma GCC optimize("Ofast")
#pragma GCC target("bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)
// Command to check time and memory usage:
//      /usr/bin/time -v ./tmp
// See "Maximum resident set size" for max memory used
// Commands for interactive checker:
//      mkfifo fifo
//      (./solution < fifo) | (./interactor > fifo)
// Does not work on the Windows file system, i.e., /mnt/c/
// The special fifo file must be used, otherwise the
// solution will not wait for input and will read EOF
y = x & (x-1)  // Turn off rightmost 1bit
y = x & (-x)   // Isolate rightmost 1bit
y = x | (x-1)  // Right propagate rightmost 1bit(fill in 1s)
y = x | (x+1)  // Turn on rightmost 0bit
y = ~x & (x+1) // Isolate rightmost 0bit
// If x is of long type, use __builtin_popcountl(x)
// If x is of long long type, use __builtin_popcountll(x)
// 1. Counts the number of one’s(set bits) in an integer.
__builtin_popcount(x)
// 2. Checks the Parity of a number. Returns true(1) if the
// number has odd number of set bits, else it returns
// false(0) for even number of set bits.
 __builtin_parity(x) 
// 3. Counts the leading number of zeros of the integer.
__builtin_clz(x)
// 4. Counts the trailing number of zeros of the integer.
__builtin_ctz(x)
// 5. Returns 1 + the index of the least significant 1-bit.
__builtin_ffs(x) // If x == 0, returns 0.
// Iterate over non empty subsets of bitmask
for(int s=m;s;s=(s-1)&m) // Decreasing order
for(int s=0;s=s-m&m;) // Increasing order