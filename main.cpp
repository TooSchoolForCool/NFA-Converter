#include <iostream>

#include "automaton.h"

using namespace std;

int main()
{
	Automaton atm;
	
	atm.load("./tests/nfa1.atm");

	atm.showAutomaton();

	return 0;
}