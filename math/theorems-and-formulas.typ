#let sq(n, k) = math.vec(n, k, delim: "[")
#let br(n, k) = math.vec(n, k, delim: "{")
#let iff = math.arrow.double.l.r
#set align(center)

$n! space ~ space sqrt(2 pi n) (n/e)^n$

$sum_(i=0)^k binom(n+i, i) = binom(n+k+1, k)$

$sq(n, k) =$ perm of $n$ elements with $k$ cycles

$sq(n+1, k) = n sq(n, k) + sq(n, k-1)$

$br(n, k) =$ partitions of an $n$-element set into $k$ parts

$br(n, k) = 1/k! sum_(i=0)^k (-1)^i binom(k, i) (k-i)^n$

$br(n+1, k) = k br(n, k) + br(n, k-1)$

Integers $d_1 >= dots.c >= d_n >= 0$ can be the degree sequence of
a finite simple graph on $n$ vertices $iff d_1 + dots.c + d_n$ is even and for every $k$ in $1 <= k <= n $

$sum_(i=1)^k d_i <= k (k-1) + sum_(i=k+1)^n min(d_i,k)$

$a^n = a^(phi(m)+n mod phi(m)) (mod m) "if" n > lg(m)$

Misere Nim: if $exists a_i > 1$ then normal nim; else the condition is reversed.

Derangements: Num of permutations of $n=0,1,2,dots$ elements without fixed points is
$1,0,1,2,9,44,265,1854,14833,dots$ Recurrence: $D_n = (n-1)(D_(n-1)+D_(n-2)) = n*D_(n-1)+(-1)^n$

Collary: number of permutations with exactly $k$ fixed points $binom(n, k) D_(n-k)$

Eulerian numbers: $E(n,k)$ is the number of permutations with exactly $k$ descents ($i:pi_i < pi_(i+1)$),
ascents ($pi_i > pi_(i+1)$) / excedances ($pi > i$) / $k+1$ weak excedances ($pi >= i$).

$E_(n,k) = (k+1) E_(n-1,k) + (n-k)E_(n-1,k-1)$
