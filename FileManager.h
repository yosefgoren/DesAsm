#include <string>
#include <fstream>
#include <vector>

class FileManager{
public:
	/**
	 * The manager will handle the values of the argument.
	 * making it point to different files as the program runs.
	 */
	FileManager(FILE** managed_file);

	/**
	 * read from the file 'input_filename' as stdin, 'popInputFile' is called: return to current file in progess.
	 */
	void pushInputFile(std::string input_filename);

	/**
	 * stop reading from top file in stack.
	 */
	void popInputFile();

	bool isEmpty() const;

	bool isFileOpened(std::string filename) const;

private:
	FILE** managed_file;

	struct InputFile{
		std::string filename;
		FILE* fobject;
	};
	std::vector<InputFile> open_files;
	//the initial value of the managed file.
    FILE* initial_file_value;
};