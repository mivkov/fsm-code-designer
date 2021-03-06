#include <experimental/iterator>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "script_utils.h"

std::string generatePythonCode(DFA dfa) {
	std::stringstream builder;
	std::vector<std::string> acceptors;

	std::set<char> alphabet = dfa.get_alphabet();
	dfa::states_t states = dfa.get_states();
	std::map<std::string, dfa::state_t> state_set = *(states->states);
	dfa::transition_fn *transition_fn = dfa.get_transition_fn();
	for (auto it = state_set.begin(); it != state_set.end(); ++it) {
		if (it->second->accepting) {
			acceptors.push_back("'" + it->first + "'");
		}
	}

	builder << "#!/usr/bin/python" << "\n";
	builder << "# Autogenerated DFA code using fsm-code-designer" << "\n\n";
	builder << "import sys" << "\n\n";
	builder << "def step(label, c):" << "\n";
	builder << "\t" << "'''" << "\n";
	builder << "\t" << "Finds the next label to be accessed while" << "\n";
	builder << "\t" << "stepping through the DFA." << "\n";
	builder << "\t" << "@param label: the current label/state the DFA is on" << "\n";
	builder << "\t" << "@param c: the next read character" << "\n";
	builder << "\t" << "'''" << "\n";
	for (auto it = alphabet.begin(); it != alphabet.end(); ++it) {
		char c = *it;
		for (auto it2 = state_set.begin(); it2 != state_set.end(); ++it2) {
			std::string label = it2->first;
			builder << "\t" << "if c == '" << c << "' and label == '" << label << "':" << "\n";
			builder << "\t\t" << "return '" << transition_fn(label, c) << "'\n";
		}
	}
	builder << "\t" << "sys.exit('invalid label')" << "\n\n\n";

	builder << "def run(string):" "\n";
	builder << "\t" << "'''" << "\n";
	builder << "\t" << "Runs the given DFA on a certain string." << "\n";
	builder << "\t" << "@param string: the string to run the DFA on" << "\n";
	builder << "\t" << "'''" << "\n";
	builder << "\t" << "state = '" << dfa.get_start() << "'\n";
	builder << "\t" << "for c in string:" << "\n";
	builder << "\t\t" << "state = step(state, c)" << "\n";
	builder << "\t" << "return state in [";
	std::copy(acceptors.begin(), acceptors.end(), std::experimental::ostream_joiner<std::string>(builder, ", "));
	builder << "]" << std::endl;

	builder << "\n\n";
	builder << "if __name__ == '__main__':" << "\n";
	builder << "\t" << "if len(sys.argv) <= 1:" << "\n";
	builder << "\t\t" << "sys.exit('No string provided to run against.')" << "\n";
	builder << "\t" << "print(run(sys.argv[1]))" << std::endl;

	std::string generated = builder.str();
	return generated;
}

void writeCodeToFile(DFA dfa, std::string filename) {
	std::ofstream out (filename);
	out << generatePythonCode(dfa);
	out.close();
	return;
}
