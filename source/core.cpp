#include <iostream>
#include <string.h>

// begin header-fu
#include "headers/core_classes.h"
#include "headers/pp_defs.h"
int fprompt(ProgramFile pf);
int iprompt();
MemorySlot reg[SL_STACKSIZE];
#include "headers/allheaders.h"

using namespace std;


// prototypes
int director(Parser ps);
int find_label(ProgramFile &pf, string term);
void init_stack();

int main(int argc, char** argv) {
	init_stack();
	return ahndlr::director(argc, argv);
}

int fprompt(ProgramFile pf) {
	// validity checks
	if (pf.get_filename() == "") {
		io::log::error("No file to open!");
		return 1;
	}
	if (!pf.load_file()) {
		io::log::error(string("Unable to open file ") + pf.get_filename() + "!");
		return 1;
	}
	// end validity checks

	Parser ps;
	string line;
	int tmp;

	for (int c = 0; c < pf.get_length(); c++) { // run through file
		ps.reset();
		line = pf.get_line(c);
		ps.parse(line);
		if (ps.get_arg(0) == "goto") {
			tmp = find_label(pf, ps.get_arg(1));
			if (tmp != -1) {
				c = tmp;
			} else {
				err::throw_error(string("no label \"") + ps.get_arg(1), true);
			}
		} else {
			director(ps);
		}
		if (err::error_thrown) {
			if (err::fatal) {
				io::log::fatal(err::error_description + " [line " + tools::itos(c + 1) + "]");
				return 1;
			} else {
				io::log::error(err::error_description + " [line " + tools::itos(c + 1) + "] [attempting to continue execution]");
			}
		}
	}
	return 0;
}

int iprompt() {
	io::log::error("Interactive mode is not yet implemented!");
	return 1;
}

int director(Parser ps) {
	if (ps.get_arg(0) == "" || ps.get_arg(0) == "label") {
		// do nothing
	} else if (ps.get_arg(0) == "print") {
		impl::print(ps.get_all_args());
	} else {
		err::throw_error("unknown function or operator \"" + ps.get_original() + "\"", true);
		return 1;
	}
	return 0;
}

int find_label(ProgramFile &pf, string term) {
	Parser ps;
	for (int c = 0; c < pf.get_length(); c++) {
		ps.reset();
		ps.parse(pf.get_line(c));
		if (ps.get_arg(0) == "label" && ps.get_arg(1) == term) {
			return c;	
		}
	}
	return -1;
}

void init_stack() {
	for (int c = 0; c < SL_STACKSIZE; c++) {
		reg[c].init();
	}
}
