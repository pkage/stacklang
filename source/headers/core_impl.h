//
// core function implementations
// created 4/25/14
// by patrick kage
//



#ifndef SL_CORE_IMPL
#define SL_CORE_IMPL

#include "core_io.h"
#include "core_tools.h"
#include "core_errors.h"
#include "core_classes.h"
#include <cmath>

namespace impl {
	void print(std::string str) {
		if (str.length() == 0 || str.length() == 1) {return;}
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
			return;
		}
		int tmp = tools::get_mem_slot(str);
		if (tmp != -1) {
			io::print(reg[tmp].stringify(reg[tmp].type));
			return;
		}
		err::throw_error("Invalid expression!", true);
		return;
	}
	void write(Parser ps) {
		if (ps.arg_count() != 3) {
			err::throw_error("Invalid syntax!", true); 
			return;	
		}
		std::string value, slot;
		value = ps.get_arg(1);
		slot = ps.get_arg(2); 
		if (slot.at(0) != '[' || slot.at(slot.length() - 1) != ']') { // check if slot has [ ]
			err::throw_error("Invalid slot!", true);
			return;
		}
		slot = slot.substr(1,slot.length() - 2); // trim down to slot num
		int addr = tools::stoi(slot); // get the slot as an integer
		if (addr == 0) {
			if (slot.at(0) == '[' && slot.at(slot.length() - 1) == ']') {
				slot = slot.substr(1,slot.length() - 2); // trim down to secondary slot #
				addr = tools::stoi(slot);
				if (addr < 0 || addr >= SL_STACKSIZE) {
					err::throw_error("Invalid address!");
					return;
				}
				if (reg[addr].type != 0) {
					err::throw_error("Nested slot has invalid type!");
					return;
				}
				if (reg[addr].type == 0) {
					float tfl = (float)addr;
					reg[addr].read(tfl);
					addr = (int)tfl;
				}
			} else {
				err::throw_error("Invalid nested address!");	
				return;
			}
		}
		if (value.at(0) == '\'' && value.at(value.length() - 1) == '\'' && value.length() == 3) {
			reg[addr].write(value.at(1));
		} else if (value.at(0) == '\"' && value.at(value.length() - 1) ) {
			reg[addr].write(value.substr(1, value.length() - 2));
		} else if (tools::isanum(value)) {
			reg[addr].write(tools::stof(value));
		} else {
			err::throw_error("Syntax error!");
			return;
		}
		return;
	}
	void math_handler(Parser ps) {
		if (ps.arg_count() != 3) {
			err::throw_error("Syntax error!");
			return;
		}
		std::string lvalue, operand = ps.get_arg(1), rvalue = ps.get_arg(2);
		float lvalue_real, rvalue_real;
		lvalue = ps.get_arg(0);
		if (lvalue.at(0) != '[' || lvalue.at(lvalue.length() - 1) != ']') {
			err::throw_error("Invalid lvalue!");
			return;
		}
		if (!tools::isanum(lvalue.substr(1,lvalue.length() - 2))) {
			err::throw_error("Invalid lvalue address!");
			return;
		}
		int addr = tools::stoi(lvalue.substr(1,lvalue.length() - 2));
		if (addr < 0 || addr >= SL_STACKSIZE) {
			err::throw_error("Invalid lvalue!");
			return;
		}
		reg[addr].read(lvalue_real);
	//	std::cout << "\nExtracted lvalue:" << lvalue_real << "\n";
		if (rvalue.at(0) == '[' && rvalue.at(rvalue.length() - 1) == ']') {
			if (tools::isanum(rvalue.substr(1,rvalue.length() - 2))) {
				reg[tools::stoi(rvalue.substr(1,rvalue.length() - 2))].read(rvalue_real);
			} else {
				err::throw_error("Invalid rvalue address!");
				return;
			}
		} else if (tools::isanum(rvalue)) {
			rvalue_real = tools::stof(rvalue);
		} else {
			err::throw_error("Invalid rvalue!");
		}
	//	std::cout << "\nExtracted rvalue:" << rvalue_real << "\n";
		if (operand == "=") {
			reg[addr].write(rvalue_real);
		} else if (operand == "+=") {
			reg[addr].write(lvalue_real + rvalue_real);
		} else if (operand == "-=") {
			reg[addr].write(lvalue_real - rvalue_real);
		} else if (operand == "*=") {
			reg[addr].write(lvalue_real * rvalue_real);
		} else if (operand == "/=") {
			if (rvalue_real == 0) {
				err::throw_error("Divide by zero!");
				return;
			}
			reg[addr].write(lvalue_real / rvalue_real);
		} else if (operand == "%=") {
			reg[addr].write((float)((int)floor(lvalue_real) % (int)floor(rvalue_real)));
		} else {
			err::throw_error("\"" + operand + "\" is not a valid operator!");
			return;
		}
		return;
	}
}


#endif
