#include <iostream>
#include "HashSet.h"

int main(){
	HashSet s;
	s.insert("shit");
	std::cout << s.lookup("shit");

}