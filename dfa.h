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
	void minimize();
	bool checkString(std::string str);
	
private:
	void _partition(std::vector<std::vector<std::string> > &dst);
	void _separate(std::vector<std::string> &src, std::vector<std::string> &dst_a,
		std::vector<std::string> &dst_b, const std::vector<std::vector<std::string> > &lookup_dict);
	int _getIndexInLookupDict(const std::vector<std::vector<std::string> > &lookup_dict, std::string state);
	void _updateDFA(std::vector<std::vector<std::string> > &partition);
};

#endif	//	_DFA_H