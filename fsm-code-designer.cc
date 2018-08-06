// Mostly just a test file at this point

#include <iostream>

#include "script_utils.h"

std::string transition(std::string label, char c) {
	if (label[0] == '0') {
		return "1";
	} else {
		return "0";
	}
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
	starting_state->label = "0";
	other_state->label = "1";
	dfa::state_t states[2];
	states[0] = starting_state;
	states[1] = other_state;

	DFA fsm(states, 2, &transition, starting_state);
	std::cout << fsm.accepts(test) << std::endl;
	std::cout << generatePythonCode(fsm) << std::endl;
	writeCodeToFile(fsm, "example.py");
}
