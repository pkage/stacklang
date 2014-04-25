#include <iostream>
#include <string.h>

// begin header-fu
#include "headers/core_classes.h"
int fprompt(ProgramFile pf);
int iprompt();
#include "headers/allheaders.h"

using namespace std;

MemorySlot reg[SL_STACKSIZE];

// prototypes

int director(Parser ps);

int main(int argc, char** argv) {
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

	for (int c = 0; c < pf.get_length(); c++) {
		ps.reset();
		line = pf.get_line(c)
	}
	return 0;
}

int iprompt() {
	io::log::error("Interactive mode is not yet implemented!");
	return 1;
}

int director(Parser ps) {
	
}
