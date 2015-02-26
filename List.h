#ifndef __LIST__H
#define __LIST__H

#include <iostream>

using namespace std;

 	/* Lista dublu inlantuita simpla */
 
template <typename T>struct Node {
	T value;
	Node< T > *next;
	Node< T > *prev;
};
 
template <typename T>class LinkedList {
private:
	Node< T > *pFirst, *pLast;
	int size;
 
public:
	
	LinkedList(){
	// constructor
		pFirst = pLast = NULL;
		size = 0;
	}
	
	~LinkedList(){
	// destructor
		size = 0;
		if( !isEmpty() ){
			Node< T >* p = pFirst;
			while( p->next != NULL ){
				p = p->next;
				delete p->prev;
			}
			delete p;
		}
			pFirst = pLast = NULL;
	}
	
	void addFirst(T value){
	// adauga la inceputul listei
		
		Node< T > *aux = new Node< T >;
		aux->value = value;
		
		aux->prev = NULL;
		aux->next = pFirst;
		
		if( isEmpty() ){
			pFirst = pLast = aux;
		}
		else {
			pFirst->prev = aux;
			pFirst=aux;
		}
		
		size++;
	}
 
	void addLast( T value){
	// adauga la sfarsitul listei
		
		Node< T > *aux = new Node< T >;
		aux->value = value;
		
		aux->prev = pLast;
		aux->next = NULL;
		
		if (isEmpty()) {
			pFirst = pLast = aux;
        }
        else {
			pLast->next = aux;
			pLast = aux;
        }
        size++;
	}
	
	T view(int index){
	// vizualizare element (de pe pozitia index)
		if( isEmpty() ){
			cout<<"Error: the list is empty!\n";
			T x;
			return x;
		}
		int c = 0;
		Node< T > *aux = pFirst;
		while ( aux->next != NULL && c < index ) {
			aux = aux->next;
			c++;
		}
		return aux->value;
	}
	
	T viewLast(){
	// vizualizarea ultimului element
		if( isEmpty() ){
			T x;
			cout<<"Error: the list is empty!\n";
			return x;
		}
		
		return pLast->value;
	}
	
	T removeFirst(){
	// sterge primul element
		if( isEmpty() ){
			T x;
			cout<<"Error: the list is empty!\n";
			return x;
		}
		
		T x = pFirst->value;
		if ( pFirst->next != NULL ) {
			pFirst = pFirst->next;
			delete pFirst->prev;
			pFirst->prev=NULL;
		}
		else {
			delete pFirst;
			pFirst = pLast = NULL;
		}
		size--;
		return x;
		
	}
 
	T removeLast(){
	// sterge ultimul element
		if( isEmpty() ){
			T x;
			cout<<"Error: the list is empty!\n";
			return x;
		}
		
		T x = pLast->value;
		
		if( pLast->prev != NULL){
			pLast = pLast->prev;
			delete pLast->next;
			pLast->next = NULL;
		}
		else {
			delete pLast;
			pFirst = pLast = NULL;
		}
		size--;
		return x;
		
	}
 
	void insert( T value, int index){
	// insereaza un element cu vaoare [value] la pozitia [index]
		
		if( isEmpty() ){
			addLast( value );
			return;
		}
		int c = 0;
		Node< T > *aux = pFirst;
		while ( aux->next != NULL && c<index ) {
			aux = aux->next;
			c++;
		}
		
		if(index == 0){
			addFirst(value);
			return;
		}
		
		if(aux->next == NULL){
			if(c == index){
				T x = removeLast();
				addLast( value );
				addLast( x );
			}
			else {
				addLast( value );
			}
			
			return;
		}
		
		Node< T > *ins = new Node< T >;
		ins->value=value;
		ins->next=aux;
		ins->prev=aux->prev;
		aux->prev->next=ins;
		ins->next->prev=ins;
		
		size++;
	
	}
	
	void remove(int index){
	// sterge elementul de pe pozitia [index]
		
		if( isEmpty() ){
			cout<<"Error: the list is empty!\n";
			return;
		}
		
		int c = 0;
		Node< T > *aux = pFirst;
		while ( aux->next != NULL && c < index ) {
			aux = aux->next;
			c++;
		}
		
		if( c == 0 ){
			removeFirst();
			return;
		}
		
		if( aux->next == NULL ){
			removeLast();
			return;
		}
		
		aux->prev->next = aux->next;
		aux->next->prev = aux->prev;
		delete aux;
		
		size--;
	
	}

	void printList(){
	// afiseaza continutul
		if( isEmpty() ){
			cout<<"The list is empty!\n";
			return;
		}
		Node< T > *aux = pFirst;
		while( aux->next != NULL ){
			cout << aux->value << ' ';
			aux = aux->next;
		}
		cout << aux->value<<' ';
	}
 
	int isEmpty(){
	// 1 este goala / 0 in caz contrar
		return ( pFirst == NULL && pLast == NULL );
	}
	
	Node< T >* getPfirst(){
	// returneaza pFirst
		return pFirst;
	}
	
	int getSize(){
	// returneaza numarul de elemente
		return size;
	}
	
	void operator=(LinkedList<T> &B){
	// suprascriere operator "="
		
		this->~LinkedList();
		if( B.isEmpty() ){
			return;
		}
		Node< T > *p = B.getPfirst();
		
		int i=0;
		while ( p->next != NULL ){
			addLast( B.view(i) );
			p = p->next;
			i++;
		}
		addLast(B.view(i));
		this->size = B.size;
	}
	
};

#endif
