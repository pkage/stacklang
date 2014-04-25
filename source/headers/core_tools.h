#ifndef SL_TOOLS
#define SL_TOOLS

#include <sstream>
#include <cstdlib>

namespace tools {
	int stoi(std::string s) {
		return std::atoi(s.c_str());
	}
	std::string itos(float f) {
		std::stringstream ss;
		ss << f;
		return ss.str();
	}

}


#endif
