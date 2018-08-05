// Mostly just a test file at this point

#include <iostream>

#include "script_utils.h"

std::size_t transition(dfa::states_t states, std::size_t curr_index, char c) {
	return (curr_index + c) % states->num_states;
}

int main(int argc, char **argv) {
	std::string test = "0";
	if (argc > 1) {
		test = argv[1];
	}

	dfa::state_t starting_state = new dfa::state;
	dfa::state_t other_state = new dfa::state;
	starting_state->accepting = true;
	other_state->accepting = false;
	starting_state->label = "State 0";
	other_state->label = "State 1";
	dfa::states_t states = new dfa::state_set;
	states->states = new dfa::state_t[2];
	states->states[0] = starting_state;
	states->states[1] = other_state;
	states->num_states = 2;
	char *alphabet = "012";

	DFA fsm(states, &transition, alphabet, 3);
	// std::cout << fsm.accepts(test) << std::endl;
	std::cout << generatePythonCode(fsm) << std::endl;
	writeCodeToFile(fsm, "example.py");
}
