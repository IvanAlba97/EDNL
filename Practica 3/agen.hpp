#ifndef AGEN_H
#define AGEN_H
#include <cassert>
template <typename T> class Agen {
	struct celda; // declaraci�n adelantada privada
	public:
		typedef celda* nodo;
		static const nodo NODO_NULO;
		Agen(); // constructor
		void insertarRaiz(const T& e);
		void insertarHijoIzqdo(nodo n, const T& e);
		void insertarHermDrcho(nodo n, const T& e);
		void eliminarHijoIzqdo(nodo n);
		void eliminarHermDrcho(nodo n);
		void eliminarRaiz();
		bool arbolVacio() const;
		const T& elemento(nodo n) const; // acceso a elto, lectura
		T& elemento(nodo n); // acceso a elto, lectura/escritura
		nodo raiz() const;
		nodo padre(nodo n) const;
		nodo hijoIzqdo(nodo n) const;
		nodo hermDrcho(nodo n) const;
		Agen(const Agen<T>& a); // ctor. de copia
		Agen<T>& operator =(const Agen<T>& a); // asignaci�n de �rboles
		~Agen();
	private:
		struct celda {
			T elto;
			nodo padre, hizq, heder;
			celda(const T& e, nodo p = NODO_NULO): elto(e),
			padre(p), hizq(NODO_NULO), heder(NODO_NULO) {}
		};
		nodo r; // nodo ra�z del �rbol
		void destruirNodos(nodo& n);
		nodo copiar(nodo n);
};

/* Definici�n del nodo nulo */
template <typename T>
const typename Agen<T>::nodo Agen<T>::NODO_NULO(0);

template <typename T>
inline Agen<T>::Agen() : r(NODO_NULO) {}

template <typename T>
inline void Agen<T>::insertarRaiz(const T& e){
	assert(r == NODO_NULO); // �rbol vac�o
	r = new celda(e);
}

template <typename T>
inline void Agen<T>::insertarHijoIzqdo(Agen<T>::nodo n, const T& e){
	assert(n != NODO_NULO);
	nodo hizqdo = n->hizq; // hijo izqdo actual
	n->hizq = new celda(e, n);
	n->hizq->heder = hizqdo; // El actual hijo izqdo. se convierte en
	// hermano drcho. del nuevo hijo
}

template <typename T>
inline void Agen<T>::insertarHermDrcho(Agen<T>::nodo n, const T& e){
	assert(n != NODO_NULO);
	assert(n != r); // n no es la ra�z
	nodo hedrcho = n->heder;
	n->heder = new celda(e, n->padre);
	n->heder->heder = hedrcho; // El actual hermano drcho. se convierte
	// en hermano drcho. del nuevo
}

template <typename T>
inline void Agen<T>::eliminarHijoIzqdo(Agen<T>::nodo n){
	nodo hizqdo;
	assert(n != NODO_NULO);
	hizqdo = n->hizq;
	assert(hizqdo != NODO_NULO); // existe hijo izqdo.
	assert(hizqdo->hizq == NODO_NULO); // hijo izqdo. es hoja
	// el hermano drcho. pasa a ser el nuevo hijo izqdo.
	n->hizq = hizqdo->heder;
	delete(hizqdo);
}

template <typename T>
inline void Agen<T>::eliminarHermDrcho(Agen<T>::nodo n){
	nodo hedrcho;
	assert(n != NODO_NULO);
	hedrcho = n->heder;
	assert(hedrcho != NODO_NULO); // existe hermano drcho.
	assert(hedrcho->hizq == NODO_NULO); // hermano drcho. es hoja
	// el hermano del hermano se convierte en el
	// nuevo hermano drcho. de n
	n->heder = hedrcho->heder;
	delete(hedrcho);
}

template <typename T>
inline void Agen<T>::eliminarRaiz(){
	assert(r != NODO_NULO); // �rbol no vac�o
	assert(r->hizq == NODO_NULO); // la ra�z es hoja
	delete(r);
	r = NODO_NULO;
}

template <typename T>
inline bool Agen<T>::arbolVacio() const{
	return (r == NODO_NULO);
}

template <typename T>
inline const T& Agen<T>::elemento(Agen<T>::nodo n) const{
	assert(n != NODO_NULO);
	return n->elto;
}

template <typename T>
inline T& Agen<T>::elemento(Agen<T>::nodo n){
	assert(n != NODO_NULO);
	return n->elto;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::raiz() const{
	return r;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::padre(Agen<T>::nodo n) const{
	assert(n != NODO_NULO);
	return n->padre;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::hijoIzqdo(Agen<T>::nodo n) const{
	assert(n != NODO_NULO);
	return n->hizq;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::hermDrcho(Agen<T>::nodo n) const{
	assert(n != NODO_NULO);
	return n->heder;
}

template <typename T>
Agen<T>::Agen(const Agen<T>& a){
	r = copiar(a.r);
}

template <typename T>
Agen<T>& Agen<T>::operator =(const Agen<T>& a){
	if (this != &a) { // evitar autoasignaci�n
		this->~Agen(); // vaciar el �rbol
		r = copiar(a.r);
	}
	return *this;
}

template <typename T>
inline Agen<T>::~Agen(){
	destruirNodos(r); // vac�a el �rbol
}

// M�todos privados
// Destruye un nodo y todos sus descendientes
template <typename T>
void Agen<T>::destruirNodos(Agen<T>::nodo& n){
	if (n != NODO_NULO){
		if (n->hizq != NODO_NULO){ // destruir hermanos del hijo izqdo.
			nodo hedrcho = n->hizq->heder;
			while (hedrcho != NODO_NULO){
				n->hizq->heder = hedrcho->heder;
				destruirNodos(hedrcho);
				hedrcho = n->hizq->heder;
			}
		destruirNodos(n->hizq); // destruir el hijo izqdo.
		}
		delete(n);
		n = NODO_NULO;
	}
}

// Devuelve una copia de un nodo y todos sus descendientes
template <typename T>
typename Agen<T>::nodo Agen<T>::copiar(Agen<T>::nodo n){
	nodo m = NODO_NULO;
	if (n != NODO_NULO){
		m = new celda(n->elto); // copiar n
		if (n->hizq != NODO_NULO){ // n tiene descendientes
			m->hizq = copiar(n->hizq); // copiar primer sub�rbol
			m->hizq->padre = m;
			// copiar el resto de sub�rboles
			nodo hijo = m->hizq; // �ltimo sub�rbol copiado
			nodo hedrcho = n->hizq->heder; // siguiente sub�rbol a copiar
			while (hedrcho != NODO_NULO){
				hijo = hijo->heder = copiar(hedrcho);
				hijo->padre = m;
				hedrcho = hedrcho->heder;
			}
		}
	}
	return m;
}
#endif // AGEN_H
