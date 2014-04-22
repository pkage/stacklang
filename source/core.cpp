#include <iostream>
#include <string.h>

// begin header-fu
#include "headers/core_classes.h"
void fprompt(ProgramFile pf);
void iprompt();
#include "headers/allheaders.h"

using namespace std;

MemorySlot reg[SL_STACKSIZE];
void director() {}


int main(int argc, char** argv) {
	ahndlr::director(argc, argv);
	return 0;
}

void fprompt(ProgramFile pf) {
}

void iprompt() {}
