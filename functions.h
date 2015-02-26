#ifndef __f_
#define __f_

#include <iostream>
#include <string.h>

string getText(LinkedList<string> &L);
// returneaza un string format din cuvintele din lista

void getList (LinkedList<string> &text, string a);
// pune in lista data cuvintele care se afla in stringul [a]

int getIndex(LinkedList<string> &L, int k, int &poz);
// returneaza indexul valid din lista corespunzator celui dat

int check(LinkedList<string> &text, int &i, int &j, int poz_i, int start, int stop);
// verifica posibilitatea realizarii funciilor Cut / Copy

#endif
