#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

/**
 * execute the command 'cmd' on the command line (windows).
 */
void execute_command(string cmd) {
	system(cmd.c_str());
}

/**
 * open html file on 'path' on firefox.
 */
void open_html_file(string path) {
	string cmd = "start firefox " + path;
	execute_command(cmd);
}

/**
 * copy file from 'src' path to 'dst' path.
 * without printing anything.
 */
void copy_file(string src, string dst) {
	string cmd = "xcopy " + src + " " + dst + "/i /y /q";
	execute_command(cmd);
}

/**
 * copy all files from 'src' folder to 'dst' folder.
 */
void copy_folder(string src, string dst) {
	string cmd = "xcopy " + src + " " + dst + "/i /e /y";
	execute_command(cmd);
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
void insert_into_file(string path, string delimiter, string content){
	string file_content = read_file(path);
	size_t pos = file_content.find(delimiter);
	if (pos == string::npos)
		return;
	string before = file_content.substr(0, pos);
	string after = file_content.substr(pos+delimiter.length());
	write_file(path, before + content + after);
}

/**
 * given a string or raw latex code, create a html file with the latex content
 * inserted to a 'desmos calculator' instance and open the html file on firefox.
 */
void display_latex(vector<string> latex_statments){
	static const string display_base_root = "..\\..\\DsmApp";
	static const string display_tmp_root = "..\\display_tmp";
	
	static const string display_html_filename = "webapp.html";
	static const string display_html_filepath = display_tmp_root + "\\" + display_html_filename;

	//copy the display_base folder to the display_tmp folder:
	copy_folder(display_base_root, display_tmp_root);

	//insert the latex content into the html file:
	string js_commands = "\n";
	for (string statment : latex_statments) {
		js_commands += "calculator.setExpression({latex:\"" + statment + "\"});\n";
	}
	insert_into_file(display_html_filepath, "insert after this @@@:\n", js_commands);

	// open_html_file(display_html_filepath);
}