//
// core function implementations
// created 4/25/14
// by patrick kage
//



#ifndef SL_CORE_IMPL
#define SL_CORE_IMPL

#include "core_io.h"
#include "core_tools.h"

namespace impl {
	void print(std::string str) {
		if (tools::strip_quotes(str)) {
			for (int c = 0; c < str.length(); c++) {
				if (str.at(c) == '\\') {
					if (str.at(c + 1) == 'n') {
						io::print('\n'); c++;	
					} else if (str.at(c + 1) == 'r') {
						io::print('\r'); c++;
					}
				} else {
					io::print(str.at(c));
				}
			}
		}
	}
	

}


#endif
