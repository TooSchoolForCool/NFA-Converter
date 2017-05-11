# NFA Converter

> This is a NFA converter, through which you can convert your NFA to a optimized DFA.



## How to Compile this project

Make the target executable file:
```shell
make
```

Make the target executable file and RUN it
```shell
make run
```

Clean the target executable file and clean all the object file (.obj)
```shell
make clean
```

## The format of .atm file

ab			// line #1: the alphabets set

4			// line #2: the number of states

0 1 2 3		// line #3: the identifier of each state(number only), seperated by a space

0			// line #4: the start state

1			// line #5: the number of accept states

3			// line #6: the identifier of accept state, seperated by a space

8			// line #7: the number of state transitions

0 1 a  		// from state_0 to state_1 when read in a

0 2 b

1 3 a

1 2 b

2 1 a

2 3 b

3 3 a

3 3 b

***Note: For $\epsilon$ transition, use \* to represent.***