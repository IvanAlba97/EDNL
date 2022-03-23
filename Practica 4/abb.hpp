#ifndef ABB_H
#define ABB_H
#include <cassert>

template <typename T>
class Abb {
	public:
		Abb(); // constructor
		const Abb& buscar(const T& e) const;
		void insertar(const T& e);
		void eliminar(const T& e);
		bool vacio() const;
		const T& elemento() const;
		const Abb& izqdo() const;
		const Abb& drcho() const;
		Abb(const Abb& A);	//ctor. de copia
		Abb& operator =(const Abb& A);	//asig. �rboles
		~Abb();	//destructor
		void poda(const T& e);	//P4Ej1
	private:
		struct arbol {
			T elto;
			Abb izq, der;
			arbol(const T& e): elto(e) {}
		};
		arbol* r;	//ra�z del �rbol
		T borrarMin();
		void copiar(const Abb& A);
};

template <typename T>
inline Abb<T>::Abb() : r(0) {}

template <typename T>
inline bool Abb<T>::vacio() const{
return r == 0;
}

template <typename T>
const Abb<T>& Abb<T>::buscar(const T& e) const{
	if (r == 0)	//�rbol vac�o, e no encontrado
		return *this;
	else if (e < r->elto)	//buscar en sub�rbol izqdo.
		return r->izq.buscar(e);
	else if (r->elto < e)	// buscar en sub�rbol drcho.
		return r->der.buscar(e);
	else	// encontrado e en la ra�z
		return *this;
}

template <typename T>
void Abb<T>::eliminar(const T& e){
	if(r != 0){	//arbol no vacio
		if(e < r->elto){	//quitar e del subarbol izquierdo
			r->izq.eliminar(e);
		}else if(r->elto < e){	//quitar e del subarbol derecho
			r->der.eliminar(3);
		}
	}else if(r->izq.r == 0 && r->der.r == 0){ //1. Raiz es hoja
		delete(r);
		r = 0;	//el arbol queda vacio
	}else if(r->der.r == 0){	//2. Raiz solo tiene hijo izquierdo
		arbol* a = r->izq.r;
		r->izq.r = 0;	//impide destruir el subarbol izquierdo
		delete(r);
		r = a;
	}else if(r->izq.r == 0){	//3. Raiz solo tiene hijo derecho
		arbol* a = r->der.r;
		r->der.r = 0;	//impide destruir el subarbol derecho
		delete(r);
		r = a;
	}else{	//4. Raiz tiene dos hijos
			//Eliminar el minimo del subarbol derecho y sustituir
			//el elemento de la raiz por este
		r->elto = r->der.borrarMin();
	}
}

/*
	Metodo privado
	Elimina el nodo que almacena el menor elemento del arbol
	Devuelve el elemento del nodo eliminado
*/
template <typename T>
T Abb<T>::borrarMin(){
	if(r->izq.r == 0){	//subarbol izquierdo vacio
		T e = r->elto;
		arbol* hd = r->der.r;
		r->der.r = 0;	//impide destruir el subarbol derecho
		delete(r);
		r = hd;	//sustituir r por el subarbol derecho
		return e;
	}else{
		return r->izq.borrarMin();
	}
}

template <typename T>
inline const T& Abb<T>::elemento() const{
	assert(r != 0);
	return r->elto;
}

template <typename T>
inline const Abb<T>& Abb<T>::izqdo() const{
	assert(r != 0);
	return r->izq;
}

template <typename T>
inline const Abb<T>& Abb<T>::drcho() const{
	assert(r != 0);
	return r->der;
}

template <typename T>
inline Abb<T>::Abb(const Abb<T>& A): r(0){
	copiar(A);
}

template <typename T>
Abb<T>& Abb<T>::operator =(const Abb<T>& A){
	if (this != &A){	//evitar autoasignaci�n
		this->~Abb();	//vaciar el �rbol
		copiar(A);
	}
	return *this;
}

template <typename T>
Abb<T>::~Abb(){
	if (r != 0) { // �rbol no vac�o
		delete r; // llama a r->izq.~Abb() y a r->der.~Abb()
		r = 0; // el �rbol queda vac�o
	}
}

/*
	M�todo privado
	Copia el �rbol a en *this
*/
template <typename T>
void Abb<T>::copiar(const Abb<T>& A){
	if (A.r != 0) { // �rbol no vac�o
		r = new arbol(A.r->elto); // copiar ra�z
		r->izq.copiar(A.r->izq); // copiar sub�rbol izqdo.
		r->der.copiar(A.r->der); // copiar sub�rbol drcho.
	}
}

#endif // ABB_H
