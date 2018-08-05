#!/usr/bin/python
# Autogenerated DFA code using fsm-code-designer

import sys

def run(string):
	'''
	Runs the given DFA on a certain string
	@param string: the string to run the DFA on
	'''
	curr = 'State 0'
	for c in string:
		if c == '0' and curr == 'State 0':
			curr = 'State 0'
			continue
		if c == '0' and curr == 'State 1':
			curr = 'State 1'
			continue
		if c == '1' and curr == 'State 0':
			curr = 'State 1'
			continue
		if c == '1' and curr == 'State 1':
			curr = 'State 0'
			continue
		if c == '2' and curr == 'State 0':
			curr = 'State 0'
			continue
		if c == '2' and curr == 'State 1':
			curr = 'State 1'
			continue
	return curr in ['State 0']


if __name__ == '__main__':
	if len(sys.argv) <= 1:
		sys.exit('No string provided to run against.')
	print(run(sys.argv[1]))
