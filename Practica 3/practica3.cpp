#include "agen.hpp"
#include "agen_E-S.h"

#include <fstream>

using namespace std;

/**
 * Problema 1
 * Implementa un subprograma que dado un árbol general nos calcule su grado.
 */

template <typename T>
int grado(const Agen<T>& A) {
    if(A.arbolVacio()) return 0;
    else return grado_rec(A.raiz(), A);
}

template <typename T>
int grado_rec(typename Agen<T>::nodo n, const Agen<T>& A) {
    int gradoMax = nHijos(n, A);
    typename Agen<T>::nodo aux = A.hijoIzqdo(n);
    int grado;
    while(aux != Agen<T>::NODO_NULO) {
        grado = grado_rec(aux, A);
        gradoMax = max(grado, gradoMax);
        aux = A.hermDrcho(aux);
    }
    return gradoMax;
}

template <typename T>
int nHijos(typename Agen<T>::nodo n, const Agen<T>& A) {
    int contador = 0;
    typename Agen<T>::nodo aux = A.hijoIzqdo(n);
    while(aux != Agen<T>::NODO_NULO) {
        contador++;
        aux = A.hermDrcho(aux);
    }
    return contador;
}

/**
 * Problema 2
 * Implementa un subprograma que dados un árbol y un nodo dentro de dicho árbol determine
 * la profundidad de éste nodo en el árbol.
 */

template <typename T>
int profundidad(typename Agen<T>::nodo n, const Agen<T>& A) {
    if(n == Agen<T>::NODO_NULO) return -1;
    else return 1 + profundidad(A.padre(n), A);
}

/**
 * Problema 3
 * Se define el desequilibrio de un árbol general como la máxima diferencia entre las alturas
 * de los subárboles más bajo y más alto de cada nivel. Implementa un subprograma que calcule
 * el grado de desequilibrio de un árbol general.
 */

template <typename T>
T Max(const T& valor1, const T& valor2) { return (valor1 > valor2) ? valor1 : valor2; }

template <typename T>
T Min(const T& valor1, const T& valor2) { return (valor1 < valor2) ? valor1 : valor2; }

template <typename T>
int desequilibrio(const Agen<T> A) {
    if(A.arbolVacio()) return 0;
    else return desequilibrio_rec(A.raiz(), A);
}

template <typename T>
int desequilibrio_rec(typename Agen<T>::nodo n, const Agen& A) {
    if(n == Agen<T>::NODO_NULO) return 0;
    else {
        int min = altura(A);
        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while(A.hermDrcho(hijo) != Agen<T>::NODO_NULO) {
            min = min(min, altura(hijo));
            hijo = A.hermDrcho(hijo);
        }
        return abs(altura(A) - min);
    }
}

/**
 * Problema 4
 * Dado un árbol de enteros A y un entero x, implementa un subprograma que realice la poda
 * de A a partir de x. Se asume que no hay elementos repetidos en A.
 */

// PISTA: SE PARECE A LA FUNCION DESTRUIR NODOS DEL TAD, HACERLO EN POSTORDEN

typename Agen<int>::nodo buscar(int x, const Agen<int>& A) {
    if(A.arbolVacio()) return Agen<int>::NODO_NULO;
    else return buscar_rec(int x, A.raiz(), A);
}

typename Agen<int>::nodo buscar_rec(int x, typename Agen<int>::nodo n, const Agen<int>& A) {
    if(n == Agen<int>::NODO_NULO) return Agen<int>::NODO_NULO;
    else if(A.elemento(n) == x) return n;
    else {
        typename Agen<int>::nodo hijo, aux;
        hijo = A.hijoIzqdo(n);
        aux = Agen<int>::NODO_NULO;
        while(hijo != Agen<int>::NODO_NULO && aux == Agen<int>::NODO_NULO) {
            aux = buscar_rec(x, hijo, A);
            hijo = A.hermDrcho(hijo);
        }
        return aux;
    }
}

void eliminarHoja(typename Agen<int>::nodo n, Agen<int>& A) {
    typename Agen<int>::nodo hijo;
    if(n != Agen<int>::NODO_NULO) {
        if(A.padre(n) != Agen<int>::NODO_NULO) {
            hijo = A.hijoIzqdo(A.padre(n));
            if (hijo == n) A.eliminarHijoIzqdo(A.padre(n));
            else {
                while(A.hermDrcho(hijo) != n) hijo = A.hermDrcho(hijo);
                A.eliminarHermDrcho(hijo);
            }
        } else A.eliminarRaiz();
    }
}

void poda(int x, Abin<int>& A) {
    Agen<T>::nodo n;
    n = buscar(x, A);
    poda_rec(n, A);
}

void poda_rec(Agen<T>::nodo n, Agen<int>& A) {
    if(n != Agen<int>::NODO_NULO) {
        while(A.hijoIzqdo(n) != Agen<int>::NODO_NULO) poda_rec(A.hijoIzqdo(n), A);
        eliminarHoja(n, A);
    }
}

/**
 * Programa principal
 */

int main() {
    Agen<char> A;
    ifstream fA("agen.dat");
    rellenarAgen(fA, A);
    cout << "Grado del arbol: " << grado(A) << endl;
    cout << "Profundidad del nodo: " << profundidad(A.hijoIzqdo(A.raiz()), A) << endl;
    //cout << "Desequilibrio del arbol: " << desequilibrio(A);
    Agen<int> B;
    ifstream fB("agen_int.dat");
    rellenarAgen(fB, B);
    cout << "\nArbol antes de la poda:" << endl;
    imprimirAbin(A);
    poda(18, B);
    cout << "\nArbol despues de la poda:" << endl;
    imprimirAbin(A);
}