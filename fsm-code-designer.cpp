#include <iostream>
#include "formal_dfa.hpp"

dfa::state_t transition(dfa::state_t state, bool value) {
	if (value) {
		return state->if_true;
	} else {
		return state->if_false;
	}
}

int main(int argc, char **argv) {
	std::string test = "0";
	if (argc > 1) {
		test = argv[1];
	}

	dfa::state_t starting_state = new dfa::state;
	dfa::state_t other_state = new dfa::state;
	starting_state->if_true = other_state;
	starting_state->if_false = starting_state;
	other_state->if_true = starting_state;
	other_state->if_false = other_state;
	starting_state->accepting = true;
	other_state->accepting = false;
	dfa::states_t states = new dfa::state_set;
	states->states = new dfa::state_t[2];
	states->states[0] = starting_state;
	states->states[1] = other_state;
	states->num_states = 2;

	DFA fsm(states, &transition);
	std::cout << fsm.accepts(test) << std::endl;
}
