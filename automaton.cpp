#include "automaton.h"

using namespace std;

Automaton::Automaton()
{
	// ...
}

Automaton::~Automaton()
{
	// ...
}

/**
 * load Automaton configuration file (.atm file)
 * 载入自动机配置文件(.atm文件)
 */
void Automaton::load(const string path)
{
	ifstream in( path.c_str() );

	if( !in.is_open() )
	{
		cerr << "[Automaton::load] Cannot open file: " << path << endl;
		exit(1);
	}

	// read alphabets
	in >> alphabets_;

	int cnt;
	string state;

	// read number of states
	in >> cnt;
	// read each state
	for(int i = 0; i < cnt; i++)
	{
		in >> state;
		addNewState(state);
	}

	// read start state
	in >> state;
	setStartState(state);

	// read number of accept states
	in >> cnt;
	for(int i = 0; i < cnt; i++)
	{
		in >> state;
		setAcceptedState(state);
	}

	// read number of transitions
	in >> cnt;
	for(int i = 0; i < cnt; i++)
	{
		string a, b;
		char ch;
		in >> a >> b >> ch;
		addTransition(a, b, ch);
	}

	in.close();
}

/**
 * save current automaton settings into a file
 * 将当前自动机配置保存到文件中
 */
void Automaton::save(const string path)
{
	// ...
}

/**
 * Show a prief description of current Automaton
 * 输出当前自动机内容
 */
void Automaton::showAutomaton()
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
	cout << "\tepsilon" << endl;

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

		if( _isTransitionExist(states_[i], '*') )
			cout << "\t   " << transitions_[ PSC(states_[i], '*') ] << endl;
		else
			cout << "\t   -" << endl;
	}
}

/**
 * Add a new state node
 * 添加新的状态
 */
void Automaton::addNewState(string newState)
{
	// Check Duplicate
	for(unsigned int i = 0; i < states_.size(); i++)
	{
		if(states_[i] == newState)
		{
			cerr << "[Automaton::addNewState] Duplicate state: " << newState << endl;
			exit(1);
		}
	}

	states_.push_back(newState);
}

/**
 * Add a new transition
 * 添加新的状态转移
 */
void Automaton::addTransition(string a, string b, char ch)
{	
	if( !_isStateExist(a) )
	{
		cerr << "[Automaton::addTransition] state " << a << " is \
			NOT defined in previous states" << endl;
		exit(1);
	}

	if( !_isStateExist(b) )
	{
		cerr << "[Automaton::addTransition] state " << b << " is \
			NOT defined in previous states" << endl;
		exit(1);
	}

	// Check if alphabet ch exist
	if( !_isAlphabetExist(ch) )
	{
		cerr << "[Automaton::addTransition] Do not have such alphabet " << ch << endl;
		exit(1);
	}

	if(transitions_.find(PSC(a, ch)) != transitions_.end())
	{
		cerr << "[Automaton::addTransition] Duplicate transition: (" << a << ", ";
		cerr << b << ", " << ch << ")" << endl;
		exit(1);
	}

	transitions_[PSC(a, ch)] = b;
}

/**
 * Set Start State
 * 设置初始状态
 */
void Automaton::setStartState(string startState)
{
	if( !_isStateExist(startState) )
	{
		cerr << "[Automaton::setStartState] start state " << startState << " is \
			NOT defined in previous states" << endl;
		exit(1);
	}

	startState_ = startState;
}

/**
 * Set final state
 * 设置接受状态
 */
void Automaton::setAcceptedState(string acc_state)
{
	if( !_isStateExist(acc_state) )
	{
		cerr << "[Automaton::setAcceptedState] final state " << acc_state << " is \
			NOT defined in previous states" << endl;
		exit(1);
	}

	acceptedStates_[acc_state] = true;
}

/**
 * Set Alphabets set
 * 设置字符集
 */
void Automaton::setAlphabets(string alphabets)
{
	alphabets_ = alphabets;
}

/**
 * Check if curState is a final state
 * 判断当前状态是否被接受
 */
bool Automaton::_isAccepted(string curState)
{
	if(acceptedStates_.find(curState) != acceptedStates_.end())
		return true;
	else
		return false;
}

/**
 * Get the next state when current state read in `alphabet`
 * 找出当前节点读入alphabet后的下一节点
 */
string Automaton::_getNextState(string curState, char alphabet)
{
	if( _isTransitionExist(curState, alphabet) )
		return transitions_[ PSC(curState, alphabet) ];
	else
		return "";
}

bool Automaton::_isStateExist(string state)
{
	for(unsigned int i = 0; i < states_.size(); i++)
	{
		if(states_[i] == state)
			return true;
	}

	return false;
}

bool Automaton::_isTransitionExist(string state, char ch)
{
	if(transitions_.find( PSC(state, ch) ) == transitions_.end())
		return false;
	else
		return true;
}

bool Automaton::_isAlphabetExist(char ch)
{
	if(ch != '*' && alphabets_.find(ch) ==  string::npos)
		return false;
	else
		return true;		
}