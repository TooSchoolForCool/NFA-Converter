#ifndef _AUTOMATON_H
#define _AUTOMATON_H

// C++ library
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

// C library
#include <stdio.h>
#include <stdlib.h>

typedef std::pair<std::string, char> PSC;

class Automaton
{
public:
	Automaton();
	~Automaton();

public:
	/**
	 * load Automaton configuration file (.automaton file)
	 * 载入自动机配置文件(.dfa文件)
	 */
	void load(const std::string path);
	/**
	 * save current automaton settings into a file
	 * 将当前自动机配置保存到文件中
	 */
	void save(const std::string path);
	/**
	 * Show a prief description of current Automaton
	 * 输出当前自动机内容
	 */
	void showAutomaton();
	/**
	 * Add a new state node
	 * 添加新的状态
	 */
	void addNewState(std::string newState);
	/**
	 * Add a new transition
	 * 添加新的状态转移
	 */
	void addTransition(std::string a, std::string b, char ch);
	/**
	 * Initialize start state
	 * 设置开始状态
	 */
	void setStartState(std::string startState);
	/**
	 * Set final state
	 * 设置接受状态
	 */
	void setAcceptedState(std::string acc_state);
	/**
	 * Set Alphabets set
	 * 设置字符集
	 */
	void setAlphabets(std::string alphabets);

protected:
	/**
	 * Check if curState is a final state
	 * 判断当前状态是否被接受
	 */
	bool _isAccepted(std::string curState);
	/**
	 * Get the next state when current state read in `alphabet`
	 * 找出当前节点读入alphabet后的下一节点
	 */
	std::string _getNextState(std::string curState, char alphabet);

	bool _isStateExist(std::string state);

	bool _isTransitionExist(std::string state, char ch);

	bool _isAlphabetExist(char ch);

protected:
	// store alphabets set 保存字符集
	std::string alphabets_;

	// stored state
	std::vector<std::string> states_;

	// transition table
	std::map<PSC, std::string> transitions_;
	
	// Start State 初始状态
	std::string startState_;

	// Final(Accepted) State 接受状态
	std::map<std::string, bool> acceptedStates_;
};

#endif 	// _AUTOMATON_H