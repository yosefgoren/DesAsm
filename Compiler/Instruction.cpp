#include "Instruction.h"
#include <map>

using namespace std;
unsigned Instruction::global_id = 0;

Instruction::Instruction(bool hidden)
    :id(global_id++), elems({
        {"type", "\"expression\""},
        {"color", "\"#c74440\""},
        {"hidden", hidden ? "true" : "false"}
}){
    elems.insert({{"id", '"'+to_string(id)+'"'}});
}

std::string Instruction::getJson() const {
    return createJson(elems);
}

unsigned Instruction::getId() const {
    return id;
}

string Instruction::createJson(const map<string, string>& items, const std::string& newline_prefix){
    std::string out = newline_prefix+"{\n";
    int cnt = 0;
    for(const auto& [key, value]: items) {
        out += newline_prefix+"\t\"" + key + "\":" + value + (++cnt != items.size() ? "," : "" ) + "\n";
    }
    out += newline_prefix+"}";
    return out;
}

LatexInstruction::LatexInstruction(const std::string& expression, bool hidden, const std::tuple<std::string, std::string>* domain)
    :Instruction(hidden), expression(expression){
    elems.insert({"latex", '"'+expression+'"'});
    if (domain != nullptr) {
        string domain_str = createJson({
            {"min", '"'+std::get<0>(*domain)+'"'},
            {"max", '"'+std::get<1>(*domain)+'"'}
        });
        elems.insert({"parametricDomain", domain_str});
    }
}

SliderInstruction::SliderInstruction(
    const std::string& symbol,
    const std::string& init_val,
    const std::string& start,
    const std::string& end,
    const std::string& step,
    const std::string& period,
    bool running
):
    LatexInstruction(symbol+"="+init_val),
    symbol(symbol),
    init_val(init_val),
    start(start),
    end(end),
    step(step),
    period(period),
    is_running(running)
{
    string slider_str = createJson({
        {"hardMin", "true"},
        {"hardMax", "true"},
        {"loopMode", "\"LOOP_FORWARD\""},
        {"min", '"'+start+'"'},
        {"max", '"'+end+'"'},
        {"step", '"'+step+'"'},
        {"animationPeriod", period},
        {"isPlaying", string(is_running ? "true" : "false")},
    });
    elems.insert({"slider", slider_str});
}

RawJsonInstruction::RawJsonInstruction(const std::string& content)
    :content(content){}

std::string RawJsonInstruction::getJson() const {
    return content;
}