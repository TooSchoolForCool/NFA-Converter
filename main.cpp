/*********************************************************************
 * MODULE: main.cpp
 * PURPOSE: main() function define here
 * AUTHER: Zeyu Zhang
 * DATE STARTED: 2017-05-11
 *********************************************************************/
#include <iostream>

#include "nfa.h"

using namespace std;

int main()
{
	NFA nfa;
	DFA dfa;
	
	nfa.load("./tests/nfa1.atm");

	nfa.showAutomaton();

	nfa.convert2DFA(dfa);

	return 0;
}

