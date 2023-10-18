Burnside lemma
For a set X, with members x in X, and a group G, with
operations g in G, where g(x): X -> X.
F_g is the set of x which are fixed points of g (ie.
{ x in X / g(x) = x }).
The number of orbits (connected components in the
graph formed by assigning each x a node and
a directed edge between x and g(x) for every g) is
called M.
M = the average of the fixed points of all
g = (|F_g1| + |F_g2| + ... + |F_gn|) / |G|
If x are images and g are simmetries, then M
corresponds to the amount of objects, |G|
corresponds to the amount of simmetries, and F_g
corresponds to the amount of simmetrical images under
the simmetry g.

Rational root theorem
All rational roots of the polynomials with integer coefficients:
a0 * x^0 + a1 * x^1 + a2 * x^2 + ... + an * x^n = 0
If these roots are represented as p / q, with p and q coprime,
- p is an integer factor of a0
- q is an integer factor of an
Note that if a0 = 0, then x = 0 is a root, the polynomial can be divided by x and the theorem
applies once again.

Petersen's theorem
Every cubic and bridgeless graph has a perfect matching.

Number of divisors for powers of 10
(0,1) (1,4) (2,12) (3,32) (4,64) (5,128) (6,240) (7,448)
(8,768) (9,1344) (10,2304) (11,4032) (12,6720) (13,10752)
(14,17280) (15,26880) (16,41472) (17,64512) (18,103680)

Kirchoff Theorem: Sea A la matriz de adyacencia del multi-
grafo (A[u][v] indica la cantidad de aristas entre u y v)
Sea D una matriz diagonal tal que D[v][v] es igual al grado
de v (considerando auto aristas y multi aristas). Sea
L = A - D. Todos los cofactores de L son iguales y equivalen
a la cantidad de Spanning Trees del grafo. Un cofactor (i,j)
de L es la multiplicación de (-1)^{i + j} con el determinant
de la matriz al quitar la fila i y la columna j

Prufer Code: Dado un árbol con los nodos indexados: busca la
hoja de menor índice, bórrala y anota el índice del nodo al
que estaba conectado. Repite el paso anterior n-2 veces. Lo 
anterior muestra una biyección entre los arreglos de tamaño
n-2 con elementos en [1, n] y los árboles de n nodos, por lo
que hay n^{n-2} spanning trees en un grafo completo.
Corolario: Si tenemos k componentes de tamaños s1,s2,...,sk
entonces podemos hacerlos conexos agregando k-1 aristas
entre nodos de s1*s2*...*sk*n^{k-2} formas