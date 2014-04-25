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
	bool strip_quotes(std::string &str) {
		if (str.at(0) == '\"' && str.at(str.length() - 1) == '\"') {
			str = str.substr(1, str.length() - 2);
			return true;
		} else {
			return false;
		}	
	}

}


#endif
