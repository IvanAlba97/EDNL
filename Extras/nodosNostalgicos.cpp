/**
 * Función que calcula el número de nodos nostálgicos. Un nodo nostálgico es aquel que tiene más
 * pasado que futuro, es decir, que tiene más antecedentes propios que descendientes propios.
 */

template <typename T>
int nDescendientes_rec(typename Abin<T>::nodo n, const Abin<T>& A) {
    if(n == Abin<T>::NODO_NULO) return 0;
    else return 1 + nDescendientes_rec(A.hijoIzqdoB(n), A) + nDescendientes_rec(A.hijoDrchoB(n), A);
}

template <typename T>
int nDescendientesPropios(typename Abin<T>::nodo n, const Abin<T>& A) {
    return nDescendientes_rec(A.hijoIzqdoB(n), A) + nDescendientes_rec(A.hijoDrchoB(n), A); 
}

template <typename T>
int nAntecedentesPropios_rec(typename Abin<T>::nodo n, const Abin<T>& A) {
    if(A.padreB(n) == Abin<T>::NODO_NULO) return 0;
    else return 1 + nAntecedentesPropios_rec(A.padreB(n), A);
}

template <typename T>
bool esNostalgico(typename Abin<T>::nodo n, const Abin<T>& A) {
    if(nAntecedentesPropios_rec(n, A) > nDescendientesPropios(n, A)) return true;
    else return false;
}

template <typename T>
int nNostalgicos_rec(typename Abin<T>::nodo n, const Abin<T>& A) {
    if(esNostalgico(n, A)) return 1 + nNostalgicos_rec(A.hijoIzqdoB(n), A) + nNostalgicos_rec(A.hijoDrchoB(n), A);
    else return nNostalgicos_rec(A.hijoIzqdoB(n), A) + nNostalgicos_rec(A.hijoDrchoB(n), A);
}

template <typename T>
int nNostalgicos(const Abin<T>& A) {
    if(!A.arbolVacioB()) return nNostalgicos_rec(A.raizB(), A);
}
