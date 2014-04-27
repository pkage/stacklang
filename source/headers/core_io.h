/*
 * stacklang core IO headers [core -> outside]
 * created 4/22
 */

#ifndef SL_IO
#define SL_IO

#include <iostream>
#include <sstream>

#include "core_classes.h"
#include "core_flags.h"

namespace io {
	void print(std::string s) {
		std::cout << s;
	}
	void print(float f) {
		std::stringstream ss; ss << f;
		std::cout << f;
	}
	void print(char c) {
		std::cout << c;
	}
	std::string get() {
		std::string tmp;
		std::getline(std::cin, tmp);
		return tmp;
	}
	std::string getw() {
		std::string tmp;
		std::cin >> tmp;
		return tmp;
	}
	namespace log {
		void error(std::string s) {
			if (!flags::SILENCE_ERRORS) {print("\n[ERROR]: " + s + "\n");}
		}
		void warning(std::string s) {
			if (!flags::SILENCE_ERRORS) {print("\n[WARNING]: " + s + "\n");}
		}
		void info(std::string s) {
			print("\n[INFO]: " + s + "\n");
		}
		void fatal(std::string s) {
			if (!flags::SILENCE_ERRORS) {print("\n[FATAL]: " + s + "\n");}
		}
	}
}

#endif
