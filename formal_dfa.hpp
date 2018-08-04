#include <cstdint>
#include <string>

namespace dfa {
	// TYPEDEFS
	typedef struct state state;
	typedef struct state* state_t;
	typedef struct state_set* states_t;
	typedef struct state_set state_set;
	typedef state_t transition_fn(state_t state, bool transition);

	// STRUCTS
	struct state {
		state_t if_true;
		state_t if_false;
		bool accepting;
	};

	struct state_set {
		state_t *states;
		std::size_t num_states;
	};

	// CLASSES
}

class DFA {
	dfa::states_t states;
	dfa::transition_fn* transition;
	public:
		DFA(dfa::states_t states, dfa::transition_fn* transition);
		dfa::state_t run(std::string s);
		bool accepts(std::string s);
};


