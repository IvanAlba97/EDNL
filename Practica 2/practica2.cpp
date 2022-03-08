#include "abin.h"
#include "abin_E-S.h"

#include <fstream>
#include <string>

using namespace std;

// Declaración adelantada porque, si no la pongo, me da un error diciendo que no existe la función.
double evaluarExpresion_rec(typename Abin<string>::nodo n, const Abin<string> &A);

/**
 * Problema 1
 * Dos árboles binarios son similares cuando tienen idéntica estructura de ramificación, 
 * es decir, ambos son vacíos o, en caso contrario, tienen subárboles izquierdo y derecho
 * similares. Implementa un subprograma que determine si dos árboles binarios son similares.
 */

template <typename T1, typename T2>
bool sonSimilares(const Abin<T1>& A, const Abin<T2>& B) {
    return sonSimilares_rec(A.raizB(), B.raizB(), A, B);
}

template <typename T1, typename T2>
bool sonSimilares_rec(typename Abin<T1>::nodo nA, typename Abin<T2>::nodo nB, const Abin<T1>& A, const Abin<T2>& B) {
    if(nA == Abin<T1>::NODO_NULO && nB == Abin<T2>::NODO_NULO) return true;
    else if(nA != Abin<T1>::NODO_NULO && nB != Abin<T2>::NODO_NULO) return sonSimilares_rec(A.hijoIzqdoB(nA), B.hijoIzqdoB(nB), A, B) && 
                                                                           sonSimilares_rec(A.hijoDrchoB(nA), B.hijoDrchoB(nB), A, B);
    else return false;
}

/**
 * Problema 2
 * Para un árbol binario B, podemos construir el árbol binario reflejado B' cambiando
 * los subárboles izquierdo y derecho en cada nodo. Implementa un subprograma que devuelva
 * el árbol binario reflejado de uno dado.
 */

template <typename T>
Abin<T>& reflejado(const Abin<T>& A) {
    Abin<T>* B = new Abin<T>;
    if(A.raizB() != Abin<T>::NODO_NULO) {
        B->insertarRaizB(A.elemento(A.raizB()));
        reflejado_rec(A.raizB(), B->raizB(), A, *B);
    }
    return *B;
}

template <typename T>
void reflejado_rec(typename Abin<T>::nodo nA, typename Abin<T>::nodo nB, const Abin<T>& A, Abin<T>& B) {
    if(A.hijoIzqdoB(nA) != Abin<T>::NODO_NULO) {
        B.insertarHijoDrchoB(nB, A.elemento(A.hijoIzqdoB(nA)));
        reflejado_rec(A.hijoIzqdoB(nA), B.hijoDrchoB(nB), A, B);
    }
    if(A.hijoDrchoB(nA) != Abin<T>::NODO_NULO) {
        B.insertarHijoIzqdoB(nB, A.elemento(A.hijoDrchoB(nA)));
        reflejado_rec(A.hijoDrchoB(nA), B.hijoIzqdoB(nB), A, B);
    }
}

/**
 * Problema 3
 * El TAD árbol binario puede albergar expresiones matemáticas mediante un árbol de
 * expresión. Dentro del árbol binario los nodos hojas contendrán los operandos, y el resto
 * de los nodos los operadores.
 *      a) Define el tipo de los elementos del árbol para que los nodos puedan almacenar 
 *         operadores y operandos.
 *      b) Implementa una función que tome un árbol binario de expresión (aritmética) y
 *         devuelva el resultado de la misma. Por simplificar el problema se puede asumir
 *         que el árbol representa una expresión correcta. Los operadores binarios posibles
 *         en la expresión aritmética serán suma, resta, multiplicación y división.
 */


void evaluarExpresion(const Abin<string>& A) {
    assert(!A.arbolVacioB());
    double res = evaluarExpresion_rec(A.raizB(), A);
    cout << " = " << res << endl;
}

double evaluarExpresion_rec(typename Abin<string>::nodo n, const Abin<string>& A) {
    assert(n != Abin<string>::NODO_NULO);
    double res;
    if(A.hijoIzqdoB(n) == Abin<string>::NODO_NULO && A.hijoDrchoB(n) == Abin<string>::NODO_NULO) {
        res = stod(A.elemento(n));
        cout << res;
    } else {
        cout << "(";
        double operandoIzq = evaluarExpresion_rec(A.hijoIzqdoB(n), A);
        cout << A.elemento(n)[0];
        double operandoDer = evaluarExpresion_rec(A.hijoDrchoB(n), A);
        cout << ")";
        switch(A.elemento(n)[0]) {
            case '+': res = operandoIzq + operandoDer; break;
            case '-': res = operandoIzq - operandoDer; break;
            case '*': res = operandoIzq * operandoDer; break;
            case '/': res = operandoIzq / operandoDer; break;
            default: cerr << "Error en el switch." << endl;
        }
    }
    return res;
}

/**
 * Problema 4
 * Una posible representación del TAD Arbol Binario consiste en almacenar los elementos del 
 * árbol en un vector cuyo tamaño depende de la altura máxima que pueda llegar a alcanzar
 * el árbol. Cada nodo del árbol se corresponde con una única posición del vector, la cual
 * viene determinada por el recorrido en inorden del árbol. Es decir, en el vector aparecen
 * primero los nodos del subárbol izquierdo en inorden, luego la raíz y a continuación los
 * nodos del subárbol derecho también en inorden.
 * Los hijos izquierdo y derecho de un nodo n corresponden, respectivamente, a las
 * posiciones n-(N+1)/2^(p+2) y n-(N+1)/2^(p+2), donde p es la profundidad de n y N es el 
 * número máximo de nodos del árbol, es decir, el tamaño del vector. Por tanto, el padre de
 * un nodo n se puede calcular de la siguiente forma:
 * 
 *            | n+(N+1)/2^(p+1) si n es hijo izquierdo
 * Padre(n) = |
 *            | n-(N+1)/2^(p+1) si n es hijo derecho
 * 
 * Un nodo n es hijo izquierdo de su padre si: n mod ((N+1)/(2^(p-1))) = ((N+1)/(2^(p-1))) - 1
 * 
 * a) Define la clase genérica Abin<T> para esta representación.
 * b) Implementa una función miembro privada que calcule la profundidad de un nodo de un 
 *    árbol binario representado de la forma descrita.
 * c) Para esta representación implementa, al menos, el constructor de árboles vacíos y 
 *    las operaciones insertarRaizB(), insertarHijoIzqdoB() y padreB(), según la 
 *    especificación del TAD Árbol Binario vista en clase.
 */



/**
 * Programa principal
 */

int main() {
    Abin<char> A;
    Abin<int> B;
    ifstream fA("abin1-char.txt");
    ifstream fB("abin1-int.txt");
    rellenarAbin(fA, A);
    rellenarAbin(fB, B);
    cout << "\nNodos del arbol A:" << endl;
    imprimirAbin(A);
    cout << "\nNodos del arbol B:" << endl;
    imprimirAbin(B);
    if(sonSimilares(A, B)) cout << "\nLos arboles son similares." << endl;
    else cout << "\nLos arboles no son similares." << endl;
    cout << "\nNodos del arbol A reflejado:" << endl;
    imprimirAbin(reflejado(A));
    Abin<string> C;
    ifstream fC("expresion1.txt");
    rellenarAbin(fC, C);
    cout << "\nEvaluacion de la expresion:" << endl;
    evaluarExpresion(C);

    cout << endl;
}