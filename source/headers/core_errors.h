#ifndef SL_CORE_ERRORS
#define SL_CORE_ERRORS

#include <cstring>

namespace err { // error messaging system
	bool error_thrown = false;
	std::string error_description;
	bool fatal = false;
	void throw_error(std::string error, bool fatal_) {
		error_thrown = true;
		error_description = error;
		fatal = fatal_;
	}
}

#endif
