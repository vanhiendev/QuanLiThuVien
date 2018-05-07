#include<iostream>
#include<string.h>

using namespace std;

#define NUMBER_TYPE 0
#define ALPHABET_TYPE 1

struct EditText{
	int x ;
	int y ;
	int length;
	bool *isError;
	string *value;
	int type; // default
};
