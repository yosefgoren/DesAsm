#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

fstream lout;

/**
 * execute the command 'cmd' on the command line (windows).
 */
int execute_command(string cmd) {
	return system(cmd.c_str());
}

/**
 * open html file on 'path' on firefox.
 */
int open_html_file(string path) {
	string cmd = "start firefox " + path;
	return execute_command(cmd);
}

/**
 * copy file from 'src' path to 'dst' path.
 * without printing anything.
 */
void copy_file(string src, string dst) {
	fstream instream(src, ios::in);
	if(!instream.is_open()){
		throw std::runtime_error("failed to open: '"+src+"'");
	}
	fstream outstream(dst, ios::out);
	if(!outstream.is_open()){
		throw std::runtime_error("failed to open: '"+dst+"'");
	}
	
	string line;
	while (getline(instream, line)) {
		outstream << line << "\n";
	}
}

/**
 * write 'content' to file 'path'.
 * override content if file already exists, create the file if not exists.
 */
void write_file(string path, string content) {
	ofstream file(path);
	file << content;
	file.close();
}

/**
 * read entier file and return its content as string.
 */
string read_file(string path) {
	ifstream file(path);
	string content;
	string line;
	while (getline(file, line)) {
		content += line + "\n";
	}
	file.close();
	return content;
}

/**
 * insert 'content' into 'path' file after first instance of 'insert_after' string.
 */
bool insert_into_file(string path, string delimiter, string content){
	string file_content = read_file(path);
	size_t pos = file_content.find(delimiter);
	if (pos == string::npos) {
		return false;
	}
	string before = file_content.substr(0, pos);
	string after = file_content.substr(pos+delimiter.length());
	write_file(path, before + content + after);

	return true;
}

string doubleBackslashes(string s) {
	string res = "";
	for (char c : s) {
		res += c;
		if (c == '\\')
			res += '\\';
	}
	return res;
}

/**
 * given a string or raw latex code, create a html file with the latex content
 * inserted to a 'desmos calculator' instance and open the html file on firefox.
 */
void display_latex(string latex_filename){
	static const string media_path = "..\\BrowserDisp\\media";
	static const string template_path = media_path+"\\template.html";
	static const string output_path = media_path+"\\webapp.html";

	copy_file(template_path, output_path);
	
	vector<string> latex_statments;
	//open 'latex_file' and insert each line into 'latex_statments':
	ifstream file(latex_filename);
	if(!file.is_open()){
		throw std::runtime_error("failed to open source latex file: '"+latex_filename+"'");
	}
	string line;
	while(getline(file, line)){
		//since the latex goes through another evaluation in html file, we need to double the backslashes:
		latex_statments.push_back(doubleBackslashes(line));
	}

	//insert the latex content into the html file:
	string js_commands = "\n";
	for (string statment : latex_statments) {
		js_commands += "calculator.setExpression({latex:\"" + statment + "\"});\n";
	}
	if(!insert_into_file(output_path, "insert after this @@@:\n", js_commands)){
		throw std::runtime_error("failed to insert content to file: could not find insertion delimiter.");
	}

	open_html_file(output_path);
}