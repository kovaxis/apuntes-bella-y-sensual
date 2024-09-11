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

*Mobius Function*

$ mu(n) = cases(
    0 & n "is not square free",
    1 & n "has even number of prime factors",
    -1 quad & n "has odd number of prime factors",
) $

Mobius Inversion:

$ g(n) = sum_(d|n) f(d) <=> f(n) = sum_(d|n) mu(d) g(n/d) $

Other useful formulas/forms

$sum_(d|n) mu(d) = [n = 1]$ (very useful)

#text(size: 10pt, block(breakable: false)[
$g(n) = sum_(1 <= m <= n) f(floor(n/m)) <=> f(n) = sum_(1 <= m <= n) mu(m) g(floor(n/m))$
])

$g(n) = sum_(n|d) f(d) <=> f(n) = sum_(n|d) mu(d/n) g(d)$

*Partition function*

Number of ways of writing $n$ as a sum of positive integers, disregarding the order of the summands.

$ p(0) = 1, quad p(n) = sum_(k in ZZ \\ {0}) (-1)^(k+1) p(n-(k(3k-1))/2) $
$ p(n) approx 0.145 / n dot e^(2.56 sqrt(n)) $

#table(columns: 14, inset: 0.8mm,
    $n$, $0$, $1$, $2$, $3$, $4$, $5$, $6$ , $7$ , $8$ , $9$ , $20$ , $50$, $100$,
    $p(n)$, $1$, $1$, $2$, $3$, $5$, $7$, $11$, $15$, $22$, $30$, $627$, $approx 2 e 5$, $approx 2 e 8$,
)

*Bell numbers*

Total number of partitions of $n$ distinct elements. $B(n) =$
$1, 1, 2, 5, 15, 52, 203, 877, 4140, 21147, dots$.

For $p$ prime,
$ B(p^m+n) equiv m B(n)+B(n+1) quad (mod p) $

*Labeled unrooted trees*

\# on $n$ vertices: $n^(n-2)$

\# on $k$ existing trees of size $n_i$: $n_1 n_2 dots.c n_k n^(k-2)$

\# with degrees $d_i$: $(n-2)! / ((d_1-1)! dots.c (d_n-1)!)$

*Catalan numbers*

$ C_n=1/(n+1) binom(2n, n) = binom(2n, n)-binom(2n, n+1) = (2n)!/((n+1)! n!) $
$ C_0=1, quad C_(n+1) = (2(2n+1))/(n+2) C_n, quad C_(n+1)=sum C_i C_(n-i) $
#text(size: 10pt)[
$ C_n = 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786, dots $
- sub-diagonal monotone paths in an $n times n$ grid.
- strings with $n$ pairs of parenthesis, correctly nested.
- binary trees with with $n+1$ leaves (0 or 2 children).
- ordered trees with $n+1$ vertices.
- ways a convex polygon with $n+2$ sides can be cut into triangles by connecting vertices with straight lines.
- permutations of $[n]$ with no 3-term increasing subseq.
]

*Narayana Numbers*

$ N(n, k) = 1/n binom(n, k) binom(n, k - 1) $
