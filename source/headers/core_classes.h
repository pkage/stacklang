#ifndef SL_CORE_CLASSES
#define SL_CORE_CLASSES

#include <string.h>
#include <vector>
#include <fstream>

class MemorySlot {
public:
	// info
	int type; // 0 = int; 1 = float; 2 = char; 3 = string
	bool valid; //  is the slot valid. prevents reading stray bits
	
	// data
	int i;
	float f;
	char c;
	std::string s;
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
public:
	void parse(std::string command) { // parse a command and dump it into the vector
		while (command.find(" ") != -1) {
			args.push_back(command.substr(0, command.find(" ")));
			command = command.substr(command.find(" ") + 1);
		}
		args.push_back(command);
	}
	void reset() {
		args.clear();
	}
	int arg_count() {
		return args.size();
	}
	std::string get_arg(int a) {
		if (a > arg_count()) {
			return "";
		}
		return args.at(a);
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
