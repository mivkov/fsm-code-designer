#include <iostream>
#include "formal_dfa.h"

void DFA::validate() {
	if (states->states->find(start_label) == states->states->end()) {
		throw "Invalid start label";
	}
	for (auto it = alphabet->begin(); it != alphabet->end(); ++it) {
		for (auto it2 = states->states->begin(); it2 != states->states->end(); ++it2) {
			if (states->states->find(transition(it2->first, *it)) == states->states->end()) {
				throw "State with label " + it2->first + "does not have valid transition on character" + *it;
			}
		}
	}
}

DFA::DFA(dfa::state_t *formal_states, std::size_t num_states, dfa::transition_fn transitionfn, dfa::state_t start_state) {
	states = new dfa::state_set;
	states->num_states = num_states;
	states->states = new std::map<std::string, dfa::state_t>();
	for(std::size_t i = 0; i < num_states; i++) {
		(*states->states)[formal_states[i]->label] = formal_states[i];
	}
	transition = transitionfn;
	alphabet = new std::set<char>();
	(*alphabet).insert('0');
	(*alphabet).insert('1');
	start_label = start_state->label;
	validate();
}

DFA::DFA(dfa::state_t *formal_states,
		 std::size_t num_states,
		 dfa::transition_fn* transitionfn,
		 char* provided_alphabet,
		 std::size_t alphabet_size,
		 dfa::state_t start_state) {
	states = new dfa::state_set;
	states->num_states = num_states;
	states->states = new std::map<std::string, dfa::state_t>();
	for(std::size_t i = 0; i < num_states; i++) {
		(*states->states)[formal_states[i]->label] = formal_states[i];
	}
	transition = transitionfn;
	alphabet = new std::set<char>();
	for (std::size_t i = 0; i < alphabet_size; i++) {
		(*alphabet).insert(provided_alphabet[i]);
	}
	start_label = start_state->label;
	validate();
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
	std::string label = start_label;
	for ( std::size_t i = 0; i < str_len; i++) {
		char c = s[i];
		if ((*alphabet).find(c) != (*alphabet).end()) {
			label = transition(label, c);
		} else {
			throw "No such character in the alphabet";
		}
	}
	return (*states->states)[label];
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

std::string DFA::get_start() {
	return start_label;
}
