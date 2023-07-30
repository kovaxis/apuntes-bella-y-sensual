// Burnside lemma
//
//     For a set X, with members x in X, and a group G, with operations g in G, where g(x): X -> X.
//     F_g is the set of x which are fixed points of g (ie. { x in X / g(x) = x }).
//     The number of orbits (connected components in the graph formed by assigning each x a node and
//     a directed edge between x and g(x) for every g) is called M.
//     M = the average of the fixed points of all g = (|F_g1| + |F_g2| + ... + |F_gn|) / |G|
//
//     If x are images and g are simmetries, then M corresponds to the amount of objects, |G|
//     corresponds to the amount of simmetries, and F_g corresponds to the amount of simmetrical
//     images under the simmetry g.
//
// Rational root theorem
//
//     All rational roots of the polynomials with integer coefficients:
//
//     a0 * x^0 + a1 * x^1 + a2 * x^2 + ... + an * x^n = 0
//
//     If these roots are represented as p / q, with p and q coprime,
//     - p is an integer factor of a0
//     - q is an integer factor of an
//
//     Note that if a0 = 0, then x = 0 is a root, the polynomial can be divided by x and the theorem
//     applies once again.
//
// Legendre's formula
//
//     Considering a prime p, the largest power p^k that divides n! is given by:
//
//     k = floor(n/p) + floor(n/p^2) + floor(n/p^3) + ...
//
//     Which can be computed in O(log n / log p) time
