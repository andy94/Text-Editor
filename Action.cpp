#include "List.h"
#include "Action.h"
#include <iostream>

using namespace std;

	/* Clasa care retine informatii despre o operatie */

Action::Action(){
}

Action::Action( int start, int stop, int type){
	this->start = start;
	this->stop = stop;
	this->type = type;
}
	
Action::~Action(){
	data.clear();
}
	
void Action::addData(string data){
//	adauga cuvant
	this->data+=data;
	this->data.push_back(' ');
}
	
int Action::getStart(){
	return start;
}
		
int Action::getStop(){
	return stop;
}
		
int Action::getType(){
	return type;
}
	
string Action::getData(){
	return data;
}
	
void Action::operator=(Action &b){
//	suprascriere operator "="
	this->data = b.data;
	this->start = b.start;
	this->stop = b.stop;
	this->type = b.type;
}

