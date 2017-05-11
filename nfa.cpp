/*********************************************************************
 * MODULE: nfa.cpp
 * PURPOSE: Implement NFA class here
 * AUTHER: Zeyu Zhang
 * DATE STARTED: 2017-05-11
 *********************************************************************/
#include "nfa.h"

using namespace std;

NFA::NFA()
{
	// ...
}

NFA::~NFA()
{
	// ...
}

void NFA::convert2DFA(DFA &dfa)
{
	queue<string> state_queue;
	map<string, bool> checked_states;
	map<PSC, string> new_transitions;

	state_queue.push( _epsilonClosure(startState_) );
	checked_states[_epsilonClosure(startState_)] = true;

	while( !state_queue.empty() )
	{
		string cur_state = state_queue.front();
		state_queue.pop();

		// cout << "pop: " << cur_state << endl;

		for(int i = 0; i < alphabets_.size(); i++)
		{
			// cerr << "current: " << cur_state;

			string next_state = _gotoNextStates(cur_state, alphabets_[i]);

			// cerr << " read: " << alphabets_[i];

			next_state = _epsilonClosure(next_state);

			if(checked_states.find(next_state) == checked_states.end())
			{
				state_queue.push(next_state);
				checked_states[next_state] = true;
				// cerr << " push: " << next_state << endl;
			}

			new_transitions[PSC(cur_state, alphabets_[i])] = next_state;
		}
	}

	_generateDFA(dfa, checked_states, new_transitions);
}

string NFA::_epsilonClosure(string state)
{
	vector<string> split_states;
	map<string, bool> closure;

	_splitState(state, split_states);

	for(int i = 0; i < split_states.size(); i++)
	{
		closure[split_states[i]] = true;
	}

	for(int i = 0; i < split_states.size(); i++)
	{
		// epsilone transition exists
		if( _isTransitionExist(split_states[i], '*') )
		{
			string new_state = transitions_[ PSC(split_states[i], '*') ];

			// check if new state already exists in the closure
			if(closure.find(new_state) == closure.end())
			{
				split_states.push_back( new_state );
				closure[new_state] = true;
			}
		}
	}

	return _mergeState(split_states);
}

void NFA::_splitState(const string &src_state, vector<string> &dst_states)
{
	string str = "";

	dst_states.clear();

	for(int i = 0; i < src_state.size(); i++)
	{
		if(src_state[i] != '-')
			str += src_state[i];
		else
		{
			dst_states.push_back(str);
			str = "";
		}
	}

	dst_states.push_back(str);

	sort(dst_states.begin(), dst_states.end());
}

string NFA::_mergeState(vector<string> &src_states)
{
	string dst_state = "";

	if(src_states.size() == 0)
		return "";

	sort(src_states.begin(), src_states.end());

	for(int i = 0; i < src_states.size() - 1; i++)
	{
		dst_state += src_states[i] + '-';
	}

	dst_state += src_states.back();

	return dst_state;
}

string NFA::_gotoNextStates(string state, char ch)
{
	vector<string> split_states;

	_splitState(state, split_states);

	for(vector<string>::iterator iter = split_states.begin(); iter != split_states.end(); iter++)
	{
		if( _isTransitionExist(*iter, ch) )
			*iter = transitions_[ PSC(*iter, ch) ];
		else
		{
			iter = split_states.erase(iter);
			iter--;
		}
	}

	return _mergeState(split_states);
}

void NFA::_generateDFA(DFA &dfa, map<string, bool> new_states, map<PSC, string> new_transitions)
{
	map<string, string> renaming_table;
	int state_cnt = 0;

	for(map<string, bool>::iterator iter = new_states.begin(); iter != new_states.end(); iter++)
	{
		renaming_table[iter->first] = int2string(state_cnt);

		// set new states
		dfa.addNewState(int2string(state_cnt++));

		// set final states
		vector<string> split_states;
		_splitState(iter->first, split_states);
		for(int i = 0; i < split_states.size(); i++)
		{
			if( _isAccepted(split_states[i]) )
			{
				dfa.setAcceptedState( int2string(state_cnt - 1) );
				break;
			}
		}
	}

	// set start states
	dfa.setStartState( renaming_table[_epsilonClosure(startState_)] );

	// set alphabets
	dfa.setAlphabets(alphabets_);

	// add transitions
	for(map<PSC, string>::iterator iter = new_transitions.begin(); iter != new_transitions.end(); iter++)
		dfa.addTransition(renaming_table[iter->first.first], renaming_table[iter->second], iter->first.second);
}

string int2string(int n)
{
	string ret = "";

	do
	{
		ret += char(n % 10 + '0');
		n /= 10;
	}while(n);

	int i = 0, j = ret.length() - 1;

	while(i < j)
	{
		int tmp = ret[i];
		ret[i++] = ret[j];
		ret[j--] = tmp;
	}

	return ret;
}