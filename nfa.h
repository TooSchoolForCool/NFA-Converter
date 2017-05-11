/*********************************************************************
 * MODULE: nfa.h
 * PURPOSE: Define DFA class which is derived from class Automaton
 * AUTHER: Zeyu Zhang
 * DATE STARTED: 2017-05-11
 *********************************************************************/
#ifndef _NFA_H
#define _NFA_H

#include "automaton.h"
#include "dfa.h"

#include <iostream>
#include <algorithm>
#include <queue>

std::string int2string(int n);

class NFA: public Automaton
{
public:
	NFA();
	~NFA();

public:
	void convert2DFA(DFA &dfa);

private:
	std::string _epsilonClosure(std::string);
	void _splitState(const std::string &src_state, std::vector<std::string> &dst_states);
	std::string _mergeState(std::vector<std::string> &src_states);
	std::string _gotoNextStates(std::string state, char ch);
	void _generateDFA(DFA &dfa, std::map<std::string, bool> new_states,
		std::map<PSC, std::string> new_transitions);
};

#endif	//	_NFA_H