/*********************************************************************
 * MODULE: dfa.h
 * PURPOSE: Define class DFA here, which is derived from Automaton
 * AUTHER: Zeyu Zhang
 * DATE STARTED: 2017-05-12
 *********************************************************************/
#ifndef _DFA_H
#define _DFA_H

#include "automaton.h"

#include <iostream>
#include <algorithm>
#include <queue>

class DFA: public Automaton
{
public:
	DFA();
	~DFA();

public:
	void showAutomaton();
	
private:
};

#endif	//	_DFA_H