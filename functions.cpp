#include <iostream>
#include <string.h>
#include "List.h"
#include "functions.h"

string getText(LinkedList<string> &text){
//  returneaza un string format din cuvintele din lista
	
	string a;
	if( text.isEmpty() ){
		return a;
	}
	
	a = text.view(0);
	a.push_back(' ');
	// pune primul cuvant
	
	for(int i = 1 ; i < text.getSize() ; i++){
		a += text.view(i);
		a.push_back(' ');
		// adauga cuvantul si spatiu la sfarsit
	}
	
	return a;
}

void getList (LinkedList<string> &text, string a){
//  pune in lista data cuvintele care se afla in stringul [a]

	text.~LinkedList();
	// goleste lista
	
	int poz = 0, size = 0;
	// pozitia de start a unui cuvant si lungimea sa
	
	for(int i = 0 ; i < (int)a.length() ; i++){
		if (a[i] == ' '){
			// daca e spatiu inseamna ca s-a ajuns la un nou cuvant
			// adauga-l in lista
			text.addLast( a.substr(poz,size) );
			
			//pozitia de start a noului cuvant
			poz = i+1;
			size = 0;
		}
		else {
			// daca nu, creste lungimea cuvantului
			size++;
		}
	}

}

int getIndex(LinkedList<string> &text, int k, int &poz){
//  returneaza indexul valid din lista corespunzator celui dat
	
	int i=0;
	if(k > 0 && !text.isEmpty()) {
		while( k > 0 && i <= (text.getSize()-1) ){
			k -= (text.view(i).length()+1);
			i++;
		}
	}
	// k este negativ si reprezinta pozitia din cuvant la care a fost dat
	// indexul initial
	poz = k;
	return i;

}

int check(LinkedList<string> &text, int &i, int &j, int poz_i, int start, int stop){
//	verifica posibilitatea realizarii funciilor Cut / Copy

	if(start < 0){
		start = 0;
		poz_i = 0;
	}
	
	// start = pozitia valida din text (pe litere si spatii, nu din lista)
	start = start - poz_i;
	
	if(start > stop)
		return 0;
	
	j=i;
	
	if((start == 0) && (stop > (int)text.view(0).length()) && (text.getSize() == 1))
		// daca se selecteaza primul cuvant cu un index de stop mai mare decat
		// lungimea sa
		return 1;
	
	start += text.view(i).length();
	if(start+1 == stop )
		return 1;
	
	while(start < stop && j+1<text.getSize() ){
	
		start += text.view(j+1).length()+1;
		// adauga in start lungimea cuvantului curent
		j++;
		
		if(start+1 == stop)
			// daca este inclus acest cuvant
			return 1;
		if(stop < start+1){
			// daca nu a fost inclus
			j--;
			return 1;
		}
		// altfel, mergi la urmatorul cuvnt
	}
	
	if((start+1 <= stop) && i != j){
		// daca a fost inclus si ultimul cuvant
		return 1;	
	}
	
	else {
		j--;
		return 0;
	}
}
	
