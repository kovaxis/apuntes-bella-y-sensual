Burnside lemma
Tomemos imagenes x en X y operaciones (g: X -> X) en G.
Si #g es la cantidad de imagenes que son puntos fijos de g,
entonces la cantidad de objetos es `(sum_{g in G} #g) / |G|`
Es requisito que G tenga la operacion identidad, que toda
operacion tenga inversa y que todo par de operaciones tenga
su combinacion.

Rational root theorem
Las raices racionales de un polinomio de orden n con
coeficientes enteros A[i] son de la forma p / q, donde p y q
son coprimos, p es divisor de A[0] y q es divisor de A[n].
Notar que si A[0] = 0, cero es raiz, se puede dividir el
polinomio por x y aplica nuevamente el teorema.

Petersens theorem
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