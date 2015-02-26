#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "backend.h"
#include "List.h"
#include "Stack.h"
#include "Action.h"
#include "functions.h"

Backend::Backend()
{

}

Backend::~Backend()
{

}

void Backend::Cut(const int start, const int stop)
{
	// sterge clipboard
	if( !clipboard.isEmpty() ){
		clipboard.~LinkedList();
	}
	
	// daca este invalid din indecsii dati
	if(stop <= 0 || stop <= start || text.isEmpty()) return;

	// afla pozitiile indecsilor din lista
	int poz_i = 0,poz_j = 0;
	int i = getIndex(text, (int) start, poz_i);
	int j = getIndex(text, (int) stop, poz_j);
	
	// verifica daca se poate efectua
	if( !check(text, i, j, poz_i, (int) start, (int) stop) ){
		return;
	}
	
	// creeaza actiunea
	Action a(i, j, 0);

	int id = 0;
	for(int k = i ; k <= j ; k++){
		// adauga in clipboard cuvintele selectate
		clipboard.addLast(text.view(k-id));
		
		// adauga in actiune cuvintele selectate
		a.addData(clipboard.view(id));
		
		// sterge cuvintele selectate din text
		text.remove(k-id);id++;
	}
	
	// pune actiunea in undo
	undo.push(a);
	
	// se goleste redo
	while( !redo.isEmpty() ){
		redo.pop();
	}
}

void Backend::Copy(const int start, const int stop)
{
	// sterge clipboard
	if(!clipboard.isEmpty()){
		clipboard.~LinkedList();
	}
	
	// daca este invalid din indecsii dati
	if(stop <= 0 || stop <= start || text.isEmpty() )return;

	// afla pozitiile indecsilor din lista
	int poz_i = 0,poz_j = 0;
	int i = getIndex(text, (int) start, poz_i);
	int j = getIndex(text, (int) stop, poz_j);
	
	// verifica daca se poate efectua
	if( !check(text, i, j, poz_i, (int) start, (int) stop) ){
		return;
	}
	
	for(int k=i ; k<=j ; k++){
		// adauga in clipboard cuvintele selectate
		clipboard.addLast(text.view(k));
	}
}

void Backend::Paste(const int start)
{
	// daca nu avem cuvinte in clipboard
	if(clipboard.isEmpty()) {
		return;
	}

	// afla pozitia indexului din lista
	int poz=0;
	int i=getIndex(text, (int) start, poz);
	
	// creeaza actiunea
	Action a(i,i+clipboard.getSize()-1,1);

	int k=0;
	while (k<clipboard.getSize()){
		// adauga in text cuvintele
		text.insert(clipboard.view(k),i);
		
		// adauga in actiune cuvintele
		a.addData(clipboard.view(k));
		i++;
		k++;
	}
	
	// pune actiunea in undo
	undo.push(a);
	
	// se goleste redo
	while( !redo.isEmpty() ){
		redo.pop();
	}
}

void Backend::Undo(void)
{
	if(undo.isEmpty())
		return;
	
	Action a = undo.pop();
	redo.push(a);
	
	LinkedList<string> aux;
	getList(aux, a.getData());
	
	if(a.getType() == 1){
		// daca este de tip Add sau Paste
		
		for(int i = a.getStart() ; i <= a.getStop() ; i++){
			text.remove(i);
		}
	}
	
	int k = 0;
	if(a.getType() == 0){
		// daca este de tip Cut
		
		for(int i = a.getStart() ; i <= a.getStop() ; i++){
			text.insert(aux.view(k),i);
			k++;
		}
	}
}

void Backend::Redo(void)
{
	if(redo.isEmpty())
		return;
	
	Action a = redo.pop();
	undo.push(a);
	
	LinkedList<string> aux;
	getList(aux, a.getData());
	
	if(a.getType() == 0){
		// daca este de tip Cut
	
		for(int i = a.getStart() ; i <= a.getStop() ; i++){
			text.remove(i);
		}
	}
	int k = 0;
	if(a.getType() == 1){
		// daca este de tip Add sau Paste
	
		for(int i = a.getStart() ; i<=a.getStop() ; i++){
			text.insert(aux.view(k),i);
			k++;
		}
	}
}

void Backend::Add(const int index, const char *word)
{
	int poz=0;
	
	// afla indexul valid din lista
	int i=getIndex(text, (int) index, poz);
	
	string txt=(const char*)word;
	
	// adauga cuvantul in text
	text.insert(txt, i);
	
	// creeaza actiunea
	Action a(i,i,1);
	a.addData(txt);
	
	// pune actiunea in undo
	undo.push(a);
	
	// se goleste redo
	while( !redo.isEmpty() ){
		redo.pop();
	}
}

const char *Backend::GetText(void)
{
	buffer.clear();
	buffer=getText(text);
	
	return buffer.data();
}

