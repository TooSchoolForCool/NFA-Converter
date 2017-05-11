/*********************************************************************
 * MODULE: dfa.cpp
 * PURPOSE: Implement class DFA here
 * AUTHER: Zeyu Zhang
 * DATE STARTED: 2017-05-12
 *********************************************************************/
#include "dfa.h"

using namespace std;

DFA::DFA()
{
	// ...
}

DFA::~DFA()
{
	// ...
}

/**
 * Show a prief description of current Automaton
 * 输出当前自动机内容
 */
void DFA::showAutomaton()
{
	string stars(43, '*');

	cout << stars << endl;
	cout << "\tBrief Automaton Description" << endl;
	cout << stars << endl;

	cout << "* Alphabests: " << alphabets_ << endl;

	cout << "* Start State: " << startState_ << endl;

	cout << "* Accepted States: ";
	for(map<string, bool>::iterator iter = acceptedStates_.begin(); 
		iter != acceptedStates_.end(); iter++)
	{
		cout << iter->first << " ";
	}
	cout << endl;

	cout << "* Transitions Table:" << endl;
	cout << "\tState";
	for(unsigned int i = 0; i < alphabets_.size(); i++)
	{
		printf("\t%c", alphabets_[i]);
	}
	cout << endl;

	for(unsigned int i = 0; i < states_.size(); i++)
	{
		cout << "\t" << states_[i];
		for(unsigned int j = 0; j < alphabets_.size(); j++)
		{
			if( _isTransitionExist(states_[i], alphabets_[j]) )
				cout << "\t" << transitions_[ PSC( states_[i], alphabets_[j] ) ];
			else
				cout << "\t-";
		}
		cout << endl;
	}
	
	cout << stars << endl;
}