#include "abb.hpp"
#include "abin_E-S.h"

#include <iostream>
#include <vector>

using namespace std;

/**
 * Problema 1
 * Implementa una nueva operación del TAD Abb que tomando un elemento del mismo
 * elimine al completo el subárbol que cuelga de él.
 */

template <typename T>
void poda(const T& e, const Abb<T>& A) {
    Abb B = A.buscar(e);
    if(B.vacio()) {
        cout << "El elemento dado no existe en este árbol." << endl;
    } else {
        int aux;
        while(!B.vacio()) {
            aux = B.elemento();
            A.eliminar(aux);
            B.eliminar(aux);
        }
    }
}

/**
 * Problema 2
 * Un árbol binario de búsqueda se puede equilibrar realizando el recorrido en inorden
 * del árbol para obtener el listado ordenado de sus elementos y a continuación, repartir
 * equitativamente los elementos a izquierda y derecha colocando la mediana en la raíz y
 * construyendo recursivamente los subárboles izquierdo y derecho de cada nodo.
 * Implementa este algoritmo para equilibrar un ABB.
 */

template <typename T>
void equilibrar(Abb<T>& A) {
    vector<T> eltos;
    Abb<T> aux;
    int inicio, fin;
    if(!A.vacio()) {
        inorden(eltos, A);
        inicio = 0;
        fin = eltos.size() - 1;
        pasarAEquilibrado(inicio, fin, eltos, aux);
        A = aux;
    }
}

template <typename T>
void inorden(vector<T>& eltos, const Abb<T>& A) {
    if(!A.vacio()) {
        inorden(eltos, A.izqdo());
        eltos.push_back(A.elemento());
        inorden(eltos, A.drcho());
    }
}

template <typename T>
void pasarAEquilibrado(int inicio, int fin, vector<T>& eltos, Abb<T>& A) {
    int mediana;
    if(inicio < fin) {
        mediana = (inicio + fin) / 2;
        A.insertar(eltos[mediana]);
        pasarAEquilibrado(inicio, mediana-1, eltos, A);
        pasarAEquilibrado(mediana+1, fin, eltos, A);
    }
}

/**
 * Problema 3
 * Dados dos conjuntos representados mediante árboles binarios de búsqueda,
 * implementa la operación unión de dos conjuntos que devuelva como resultado otro
 * conjunto que sea la unión de ambos, representado por un ABB equilibrado.
 */

template <typename T>
Abb<T> union(const Abb<T>& A, const Abb<T>& B) {
    Abb<T> C;
    vector<T> vA, vB, vC;
    inorden(vA, A);
    inorden(vB, B);
    vC.insert(vC.end(), vA.begin(), vA.end());
    vC.insert(vC.end(), vB.begin(), vB.end());
    vC.sort(vC.begin(), vC.end());  // Ordena en orden ascendente.
    for(auto i = vC.begin(); i < vC.end(); i++) {
        C.insertar(vC[i]);
    }
    equilibrar(C);
    return C;
}

/**
 * Problema 4
 * Dados dos conjuntos representados mediante árboles binarios de búsqueda,
 * implementa la operación intersección de dos conjuntos, que devuelva como resultado
 * otro conjunto que sea la intersección de ambos. El resultado debe quedar en un árbol
 * equilibrado.
 */

template <typename T>
Abb<T> interseccion(const Abb<T>& A, const Abb<T>& B) {
    Abb<T> C;
    vector<T> vA, vB, vC;
    inorden(vA, A);
    inorden(vB, B);
    sort(vA.begin(), vA.end());
    sort(vB.begin(), vB.end());
    set_intersection(vA.begin(), vA.end(), vB.begin(), vB.end(), back_inserter(vC));
    for(auto i = vC.begin(), i < vC.end(); i++) {
        C.insertar(vC[i]);
    }
    equilibrar(C);
    return C;
}

/**
 * Problema 5
 * Implementa el operador rombo para conjuntos definidos como A Rombo B = (A union B) - (A interseccion B).
 * La implementación del operador rombo debe realizarse utilizando obligatoriamente la operación
 * pertenece, que nos indica si un elemento dado pertenece o no a un conjunto. La
 * representación del tipo Conjunto debe ser tal que la operación de pertenencia esté en
 * el caso promedio en O(log n).
 */

// PISTA: La función recibe 2 conjuntos y devuelve 1 conjunto
template <typename T>
Abb<T> rombo(const Abb<T>& A, const Abb<T>& B) {
    
}

/**
 * Programa principal
 */

int main() {

}