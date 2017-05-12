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

void DFA::minimize()
{
	vector<vector<string> > partition_sets;

	_partition(partition_sets);

	_updateDFA(partition_sets);
}

bool DFA::checkString(string str)
{
	string cur_state = startState_;

	for(unsigned int i = 0; i < str.length(); i++)
	{
		cur_state = _getNextState(cur_state, str[i]);
	}

	return _isAccepted(cur_state);
}

void DFA::_partition(std::vector<std::vector<std::string> > &dst)
{
	vector<string> final_set, non_final_set;

	// initilize final/non_final set
	for(int i = 0; i < states_.size(); i++)
	{
		if( _isAccepted(states_[i]) )
			final_set.push_back(states_[i]);
		else
			non_final_set.push_back(states_[i]);
	}

	vector<vector<string> > set_queue;
	set_queue.push_back(final_set);
	set_queue.push_back(non_final_set);
	
	while( set_queue.size() != 0 )
	{
		vector<string> cur_set( set_queue.back() );
		set_queue.pop_back();

		if(cur_set.size() == 1)
		{
			dst.push_back( cur_set );
			continue;	// do next iteration
		}

		vector<string> set_a, set_b;
		vector<vector<string> > lookup_dict(set_queue);
		lookup_dict.insert(lookup_dict.end(), dst.begin(), dst.end());

		_separate(cur_set, set_a, set_b, lookup_dict);

		if(set_a.size() == 0)
			dst.push_back(set_b);
		else if(set_b.size() == 0)
			dst.push_back(set_a);
		else
		{
			set_queue.push_back(set_a);
			set_queue.push_back(set_b);
		}
	}
}

void DFA::_separate(vector<string> &src, vector<string> &dst_a, 
	vector<string> &dst_b, const vector<vector<string> > &lookup_dict)
{
	map<PSC, int> match_table;

	// check src empty

	for(unsigned int i = 0; i < src.size(); i++)
	{
		string cur_state = src[i];

		for(unsigned int j = 0; j < alphabets_.length(); j++)
		{
			string next_state = transitions_[ PSC(cur_state, alphabets_[j]) ];
			match_table[ PSC(cur_state, alphabets_[j]) ] = _getIndexInLookupDict(lookup_dict, next_state);
		}
	}

	dst_a.push_back( src[0] );
	for(unsigned int i = 1; i < src.size(); i++)
	{
		int j = 0;
		
		while( j < alphabets_.length() )
		{
			if(match_table[ PSC(src[i], alphabets_[j]) ] != match_table[ PSC(src[0], alphabets_[j]) ])
				break;
			else
				j++;
		}
		
		if(j == alphabets_.length())
			dst_a.push_back( src[i] );
		else
			dst_b.push_back( src[i] );
	}
}

int DFA::_getIndexInLookupDict(const vector<vector<string> > &lookup_dict, string state)
{
	for(unsigned int i = 0; i < lookup_dict.size(); i++)
	{
		const vector<string> &cur_set = lookup_dict[i];
		for(unsigned int j = 0; j < cur_set.size(); j++)
		{
			if(cur_set[j] == state)
				return i;
		}
	}
	return -1;
}

void DFA::_updateDFA(vector<vector<string> > &partition)
{
	vector<string> new_states;
	map<string, bool> new_acc_states;
	map<PSC, string> new_transitions;
	string new_start;

	// initilize states
	for(unsigned int i = 0; i < partition.size(); i++)
		new_states.push_back( int2string(i) );

	// find all accepted states & the new start state
	for(unsigned int i = 0; i < partition.size(); i++)
	{
		vector<string> &cur_set = partition[i];
		for(unsigned int j = 0; j < cur_set.size(); j++)
		{
			if( cur_set[j] == startState_ )
				new_start = int2string(i);

			if( _isAccepted(cur_set[j]) )
			{
				new_acc_states[ int2string(i) ] = true;
				break;
			}
		}
	}

	// update new transitions, pick the first item in each
	// partition as the represent item
	for(unsigned int i = 0; i < new_states.size(); i++)
	{
		string represent_state = partition[i][0];

		for(unsigned int j = 0; j < alphabets_.length(); j++)
		{
			string next_state = transitions_[ PSC(represent_state, alphabets_[j]) ];

			string next_state_index = int2string( _getIndexInLookupDict(partition, next_state) );
			
			new_transitions[ PSC(int2string(i), alphabets_[j]) ] =  next_state_index;
		}
	}

	// update start state
	startState_ = new_start;
	// update accepted states
	acceptedStates_.swap(new_acc_states);
	// update all states
	states_.swap(new_states);
	// update transitions
	transitions_.swap(new_transitions);
}