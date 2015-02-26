#ifndef __STACK__H
#define __STACK__H

#include <iostream>
#include "List.h"

using namespace std;

	/* Stiva pe baza de lista */
 
template<typename T>
class Stack {

	public:
	
		Stack() {
		}
 
		~Stack() {
		}
 
		void push(T x) {
			L.addLast(x);
		}
 
		T pop() {
			return L.removeLast();
		}
 
		T peek() {
			return L.viewLast();
		}
 
		int isEmpty() {
			return L.isEmpty();
		}
		
		void print(){
			if(L.isEmpty()){
				cout<<"The Stack is empty!"<<endl;
				return;
			}
			L.printList();
		}
 
	private:
	
		LinkedList<T> L;
};
 
#endif // __STACK__H
