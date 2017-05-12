/*********************************************************************
 * MODULE: main.cpp
 * PURPOSE: main() function define here
 * AUTHER: Zeyu Zhang
 * DATE STARTED: 2017-05-11
 *********************************************************************/
#include <iostream>

#include "nfa.h"

using namespace std;

string manu()
{
	string str = "";

	str += "1. Show Original Automaton\n";
	str += "2. Show Intermediate DFA\n";
	str += "3. Minimized DFA\n";
	str += "4. Simulate\n";
	str += "Enter any other key to QUIT";

	return str;
}

int main()
{
	string atm_file_path = "";
	NFA nfa;
	DFA dfa, min_dfa;
	
	cout << "Please enter the path of the .atm file:" << endl;
	cin >> atm_file_path;
	getchar();

	nfa.load(atm_file_path);

	nfa.convert2DFA(dfa);

	nfa.convert2DFA(min_dfa);
	min_dfa.minimize();

	cout << manu() << endl;
	
	while(1)
	{
		

		char op;
		string str;

		op = getchar();

		for(int i = 0; i < 35; i++)
			putchar('\n');

		switch(op)
		{
			case '1':
				nfa.showAutomaton();
				break;
			case '2':
				dfa.showAutomaton();
				break;
			case '3':
				min_dfa.showAutomaton();
				break;
			case '4':
				cout << "Enter string: ";
				cin >> str;
				min_dfa.showAutomaton();
				cout << (min_dfa.checkString("aba") ? "Accepted" : "Refused") << endl;
				break;
			default:
				return 0;
				break;
		}
		getchar();
		cout << manu() << endl;
	}

	return 0;
}

