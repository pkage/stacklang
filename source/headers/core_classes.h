#ifndef SL_CORE_CLASSES
#define SL_CORE_CLASSES

#include <string.h>
#include <vector>
#include <fstream>
#include "core_tools.h"

class MemorySlot {
public:
	// info
	int type; // 0 = float; 1 = char; 2 = string
	
	// data
	float f;
	char c;
	std::string s;
	void write(float fl) {
		type = 0;
		f = fl;
	}
	void write(char ch) {
		type = 1;
		c = ch;
	}
	void write(std::string str) {
		type = 2;
		s = str;
	}
	void read(float &fl) {fl = f;}
	void read(char &ch) {ch = c;}
	void read(std::string &str) {str = s;}
	void init() {f = 0.0; c = '\0'; s = "";}
	std::string stringify(int type) {
		if (type == 0) {
			return tools::itos(f);
		} else if (type == 1) {
			std::string tmp = ""; tmp += c;
			return std::string(tmp);
		} else if (type == 2) {
			return s;
		} else {
			return "";
		}
	}
	void trim() {
		switch (type) {
			case 0:	
				c = '\0'
				s = "";
				break;
			case 1:
				f = 0.0;
				s = "";
				break;
			case 2:
				f = 0.0;
				c = '\0';
				break;
		}
		return;
	}
};

class ProgramFile { // utility class to load entire files into memory before execution
private:
	std::vector<std::string> contents;
	bool valid;
	std::string filename;
	std::string args;
public:
	ProgramFile() {valid = false;}
	void set_filename(std::string fname) {filename = fname;}
	std::string get_filename() {return filename;}
	bool load_file() {
		std::ifstream ifile;
		ifile.open(filename.c_str());
		if (!ifile) {
			valid = false;
			return false;
		}
		std::string line;
		while (!ifile.eof()) {
			std::getline(ifile, line);
			contents.push_back(line);
		}
		ifile.close();
		valid = true;
		return true;
	}
	bool is_valid() {return valid;}
	std::string get_line(int line) {
		if (line >= contents.size() || line < 0) {
			return "";
		}
		return contents.at(line);
	}
	void set_args(std::string args) {
		this->args = args;
	}
	int get_length() {return contents.size();}
	std::string get_args() {return args;}
};


class Parser { // utility class for handling lines
private:
	std::vector<std::string> args;
	std::string orig;
public:
	void parse(std::string command) { // parse a command and dump it into the vector
		orig = command;
		while (command.find(" ") != -1) {
			args.push_back(command.substr(0, command.find(" ")));
			command = command.substr(command.find(" ") + 1);
		}
		args.push_back(command);
	}
	void reset() {
		orig = "";
		args.clear();
	}
	std::string get_original() {return orig;}
	int arg_count() {
		return args.size();
	}
	std::string get_arg(int a) {
		if (a > arg_count()) {
			return "";
		}
		return args.at(a);
	}
	std::string get_all_args() {
		std::string tmp = "";
		for (int c = 1; c < arg_count(); c++) {
			if (c == 1) {
				tmp += get_arg(c);
			} else {
				tmp += " " + get_arg(c);
			}
		}
		return tmp;
	}
/*	void DBG_print() { // debug function
		cout << "\n{";
		for (int c = 0; c < args.size(); c++) {
			cout << "[" << args.at(c) << "]";
		}
		cout << "}\n";
	} */
};

#endif
