#ifndef SL_TOOLS
#define SL_TOOLS

#include <sstream>
#include <cstdlib>

namespace tools {
	int stoi(std::string s) {
		return atoi(s.c_str());
	}
	string itos(float f) {
		stringstream ss;
		ss << f;
		return ss.str();
	}

}


#endif
