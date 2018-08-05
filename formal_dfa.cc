#include "formal_dfa.h"

DFA::DFA(dfa::states_t formal_states, dfa::transition_fn transitionfn) {
	states = formal_states;
	transition = transitionfn;
	alphabet = new std::set<char>();
	(*alphabet).insert('0');
	(*alphabet).insert('1');
	start_index = 0;
}

DFA::DFA(dfa::states_t formal_states,
		 dfa::transition_fn* transitionfn,
		 char* provided_alphabet,
		 std::size_t alphabet_size) {
	states = formal_states;
	transition = transitionfn;
	alphabet = new std::set<char>();
	for (std::size_t i = 0; i < alphabet_size; i++) {
		(*alphabet).insert(provided_alphabet[i]);
	}
	start_index = 0;
}

DFA::DFA(dfa::states_t formal_states, dfa::transition_fn transitionfn, dfa::state_t start_state) {
	states = formal_states;
	transition = transitionfn;
	alphabet = new std::set<char>();
	(*alphabet).insert('0');
	(*alphabet).insert('1');

	bool dirty = false; // check if changed
	for(std::size_t i = 0; i < states->num_states; i++) {
		if (start_state->label.compare(states->states[i]->label) == 0) {
			start_index = i;
			dirty = true;
			break;
		}
	}
	if (!dirty) {
		throw "Starting state is not in the state set.";
	}
}

DFA::DFA(dfa::states_t formal_states,
		 dfa::transition_fn* transitionfn,
		 char* provided_alphabet,
		 std::size_t alphabet_size,
		 dfa::state_t start_state) {
	states = formal_states;
	transition = transitionfn;
	alphabet = new std::set<char>();
	for (std::size_t i = 0; i < alphabet_size; i++) {
		(*alphabet).insert(provided_alphabet[i]);
	}

	bool dirty = false;
	for(std::size_t i = 0; i < states->num_states; i++) {
		if (start_state->label.compare(states->states[i]->label) == 0) {
			start_index = i;
			dirty = true;
			break;
		}
	}
	if (!dirty) {
		throw "Starting state is not in the state set.";
	}
}

//DFA::~DFA() {
//	for (std::size_t i = 0; i < states->num_states; i++) {
//		delete states->states[i];
//	}
//	delete states;
//	delete alphabet;
//}

dfa::state_t DFA::run(std::string s) {
	std::size_t str_len = s.length();
	std::size_t current = start_index;
	for ( std::size_t i = 0; i < str_len; i++) {
		char c = s[i];
		if ((*alphabet).find(c) != (*alphabet).end()) {
			current = transition(states, current, c);
		} else {
			throw "No such character in the alphabet";
		}
	}
	return states->states[current];
}

bool DFA::accepts(std::string s) {
	return DFA::run(s)->accepting;
}

dfa::states_t DFA::get_states() {
	return states;
}

dfa::transition_fn* DFA::get_transition_fn() {
	return transition;
}

std::set<char> DFA::get_alphabet() {
	return *alphabet;
}

std::size_t DFA::get_start() {
	return start_index;
}
