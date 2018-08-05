#include <cstdint>
#include <string>
#include <set>

namespace dfa {
	// TYPEDEFS
	typedef struct state state;
	typedef struct state* state_t;
	typedef struct state_set* states_t;
	typedef struct state_set state_set;
	typedef std::size_t transition_fn(states_t states, std::size_t curr_index, char transition);

	// STRUCTS
	struct state {
		std::string label;
		bool accepting;
	};

	struct state_set {
		state_t *states;
		std::size_t num_states;
	};
}

// CLASSES
class DFA {
	dfa::states_t states;
	dfa::transition_fn* transition;
	std::set<char> *alphabet;
	std::size_t start_index;
	public:
		DFA(dfa::states_t states, dfa::transition_fn* transition);
		DFA(dfa::states_t states, dfa::transition_fn* transition, dfa::state_t start_state);
		DFA(dfa::states_t states,
			dfa::transition_fn *transition,
			char *alphabet,
			std::size_t alphabet_size);
		DFA(dfa::states_t states,
			dfa::transition_fn *transition,
			char *alphabet,
			std::size_t alphabet_size,
			dfa::state_t start_state);
		// ~DFA(); TODO: fix deletion!!!
		dfa::state_t run(std::string s);
		bool accepts(std::string s);
		dfa::states_t get_states();
		dfa::transition_fn *get_transition_fn();
		std::set<char> get_alphabet();
		std::size_t get_start();

};
