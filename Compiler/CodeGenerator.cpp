#include "CodeGenerator.h"

using namespace std;

string doubleBackslashes(string s) {
	string res = "";
	for (char c : s) {
		res += c;
		if (c == '\\')
			res += '\\';
	}
	return res;
}

void CodeGenrator::addLatex(const string& latex, bool hidden, const std::tuple<std::string, std::string>* domain) {
    instructions.push_back(unique_ptr<LatexInstruction>(new LatexInstruction(doubleBackslashes(latex), hidden, domain)));
}

void CodeGenrator::addSlider(
    const string& symbol,
    const string& init_val,
    const string& start,
    const string& end,
    const string& step,
    const string& speed,
    bool is_running
) {
    instructions.push_back(unique_ptr<SliderInstruction>(new SliderInstruction(
        symbol,
        init_val,
        start,
        end,
        step,
        to_string(4000.0/stod(speed)),
        is_running
    )));
}

void CodeGenrator::addRawJson(const string& content) {
    instructions.push_back(unique_ptr<RawJsonInstruction>(new RawJsonInstruction(content)));
}

string CodeGenrator::generate() const {
    string res = "[\n";
    int cnt = 0;
    for (const unique_ptr<Instruction>& instr: instructions) {
        res += instr->getJson();
        if (++cnt != instructions.size()) {
            res += ',';
        }
        res += '\n';
    }
    res += "]\n";
    return res;
}

void CodeGenrator::reset() {
    instructions.clear();
}