#include "formal_dfa.hpp"

DFA::DFA(dfa::states_t formal_states, dfa::transition_fn transitionfn) {
	states = formal_states;
	transition = transitionfn;
}

dfa::state_t DFA::run(std::string s) {
	std::size_t str_len = s.length();
	dfa::state_t current = states->states[0];
	for ( std::size_t i = 0; i < str_len; i++) {
		char c = s[i];
		switch(c) {
		case '1':
			current = transition(current, true);
			break;
		case '0':
			current = transition(current, false);
			break;
		default:
			throw "Invalid command!";
		}
	}
	return current;
}

bool DFA::accepts(std::string s) {
	return DFA::run(s)->accepting;
}
