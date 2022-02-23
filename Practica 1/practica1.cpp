#include "abin.h"
#include "abin_E-S.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

/**
* Problema 1:
* Implementa un subprograma que calcule el número de nodos de un árbol binario.
*/

template <typename T>
int nNodos(const Abin<T>& A) {
    return nNodos_rec(A.raizB(), A);
}

template <typename T>
int nNodos_rec(typename Abin<T>::nodo n, const Abin<T>& A) {
    if(n == Abin<T>::NODO_NULO) return 0;
    else return 1 + nNodos_rec(A.hijoIzqdoB(n), A) + nNodos_rec(A.hijoDrchoB(n), A);
}

/**
 * Problema 2
 * Implementa un subprograma que calcule la altura de un árbol binario.
 */

template <typename T>
int altura(const Abin<T>& A) {
    return altura_rec(A.raizB(), A);
}

template <typename T>
int altura_rec(typename Abin<T>::nodo n, const Abin<T>& A) {
    if(n == Abin<T>::NODO_NULO) return -1;
    else return 1 + max(altura_rec(A.hijoIzqdoB(n), A), altura_rec(A.hijoDrchoB(n), A));
}

/**
 * Problema 3
 * Implementa un subprograma que, dados un árbol binario y un nodo del mismo, determine
 * la profundidad de este nodo en dicho árbol.
 */

template <typename T>
int profundidad(typename Abin<T>::nodo n, const Abin<T>& A) {
    if(n == Abin<T>::NODO_NULO) return -1;
    else return 1 + profundidad(A.padreB(n), A);
}

/**
 * Problema 6
 * Implementa un subprograma que determine el nivel de desequilibrio de un árbol binario,
 * definido como el máximo desequilibrio de todos sus nodos. El desequilibrio de un nodo se
 * define como la diferencia entre las alturas de los subárboles del mismo.
 */

template <typename T>
int desequilibrio(const Abin<T>& A) {
    return desequilibrio_rec(A.raizB(), A);
}

template <typename T>
int desequilibrio_rec(typename Abin<T>::nodo n, const Abin<T>& A) {
    if(n == Abin<T>::NODO_NULO) return 0;
    else return max(
            abs(altura_rec(A.hijoIzqdoB(n), A) - altura_rec(A.hijoDrchoB(n), A)),               //1º param. de max: desequilibrio de n
            max(desequilibrio_rec(A.hijoIzqdoB(n), A), desequilibrio_rec(A.hijoDrchoB(n), A))   //2º param. de max: maximo del desequilibrio entre sus hijos
        );
}

/**
 * Problema 7
 * Implemente un subprograma que determine si un árbol binario es o no pseudocompleto.
 * En este problema entenderemos que un árbol es pseudocompleto si en el penúltimo nivel
 * del mismo cada uno de los nodos tiene dos hijos o ninguno.
 */

template <typename T>
bool esPseudocompleto(const Abin<T>& A) {
    return esPseudocompleto_rec(A.raizB(), A, altura(A));
}

template <typename T>
bool esPseudocompleto_rec(typename Abin<T>::nodo n, const Abin<T>& A, int prof) {
    if(n != Abin<T>::NODO_NULO) return true;
    else if(prof == 0) return (contarHijos(n, A) != -1);
    else return (esPseudocompleto_rec(A.hijoIzqdoB(n), A, prof-1) && esPseudocompleto_rec(A.hijoDrchoB(n), A, prof-1));
}

template <typename T>
int contarHijos(typename Abin<T>::nodo n, const Abin<T> &A) {
    if(n == Abin<T>::NODO_NULO) return 0;
    else return (A.hijoIzqdoB(n) != Abin<T>::NODO_NULO) + (A.hijoDrchoB(n) != Abin<T>::NODO_NULO);
}

/**
 * Programa principal
 */

typedef char tElto;
tElto fin = '#';

int main() {
    Abin<tElto> A;
    ifstream fA("abin1-char.txt");
    rellenarAbin(fA, A);
    cout << "\nNodos del arbol:" << endl;
    imprimirAbin(A);
    cout << "\nNumero de nodos del arbol: " << nNodos(A) << endl;
    cout << "\nAltura del arbol: " << altura(A) << endl;
    cout << "\nProfundidad del nodo: " << profundidad(A.hijoIzqdoB(A.raizB()), A) << endl;
    cout << "\nDesequilibrio del arbol: " << desequilibrio(A) << endl;
    if(esPseudocompleto(A)) cout << "\nEl arbol es pseudocompleto." << endl;
    else cout << "\nEl arbol no es pseudocompleto." << endl;
    cout << endl;
    return 0;
}

/* PARA EJECUTAR
    g++ -o ejecutable .\practica1.cpp
    .\ejecutable
*/