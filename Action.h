#ifndef ACTION_H_
#define ACTION_H_

#include "List.h"
#include <iostream>

using namespace std;

	/* Clasa care retine informatii despre o operatie */

class Action {

	private:
	
		string data; // cuvintele modificare
	
		int start, stop; //  index
	
		int type;
		// 0 - cut 			(sterse)
		// 1 - add / paste 	(adaugate)
	
	public:
	
		Action();

		Action( int start, int stop, int type);
	
		~Action();
	
		void addData(string data);
	
		int getStart();
		
		int getStop();
		
		int getType();
	
		string getData();
	
		void operator=(Action &b);
	
		friend ostream& operator<<(ostream& out, Action& a);
};

inline ostream& operator<<(ostream& out, Action& a){

	out<<a.getData()<<' '<<a.getType();
	return out;
}

#endif
