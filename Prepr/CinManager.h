#include <string>
#include <fstream>
#include <vector>

class CinManager{
public:
	/**
	 * start to read from the file 'initial_input_filename' as stdin.
	 */
	CinManager(std::string initial_input_filename);

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
	struct InputFile{
		std::string filename;
		std::fstream stream;
	};
	std::vector<InputFile> open_files;
    std::streambuf* original_cinbuf;
};