/*
 * stacklang argument handlers
 * (c) Patrick Kage 2014
 */


#ifndef SL_CORE_AHANDLERS
#define SL_CORE_AHANDLERS

#include "pp_defs.h"
#include "core_io.h"
#include "core_classes.h"
#include "core_flags.h"

namespace ahndlr {
	namespace impl {
		void version() {
			io::print(std::string("stacklang version ") + SL_VERSION + "\nbuilt with " + SL_COMPILER + " at " + SL_DATE_COMPILED + "\n");
		}
	}


	int director(int argc, char** argv) { // toss main() args in here
		std::string arg;
		bool interactive = false;
		ProgramFile pf;
		for (int c = 1; c < argc; c++) { // starts at one to ignore invocations
			arg = argv[c];
			if (arg == "-v" || arg == "--version") {
				impl::version();
				return 0;
			}
			if ((arg == "-a" || arg == "--arguments") && c + 1 != argc) {
				pf.set_args(argv[c + 1]);
			}
			if ((arg == "-f" || arg == "--file") && c + 1 != argc) {
				pf.set_filename(argv[c + 1]);
			}
			if (arg == "-i" || arg == "--interactive") {
				interactive = true;
			}
			if (arg == "--fuckit") {
				flags::IGNORE_ERRORS = true;
				flags::SILENCE_ERRORS = true;
			}
			if (arg == "--silenterr") {
				flags::IGNORE_ERRORS = true;
			}
		}
		if (interactive) {
			return iprompt();
		} else {
			return fprompt(pf);
		}
	}

}


#endif
