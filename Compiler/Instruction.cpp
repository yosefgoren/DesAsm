#include "Instruction.h"
#include <map>

using namespace std;

unsigned Instruction::global_id = 0;

Instruction::Instruction()
    :id(global_id++), elems({
        {"type", "expression"},
        {"color", "#c74440"}
}){
    elems.insert({{"id", to_string(id)}});
}

std::string Instruction::getJson() const {
    return createJson(elems);
}

unsigned Instruction::getId() const {
    return id;
}

string Instruction::createJson(const map<string, string>& items){
    std::string out = "{\n";
    int cnt = 0;
    for(const auto& [key, value]: items) {
        out += "\t\"" + key + "\":\"" + value + "\"" + (++cnt != items.size() ? "," : "" ) + "\n";
    }
    out += "}";
    return out;
}

LatexInstruction::LatexInstruction(const std::string& expression)
    :expression(expression){
    elems.insert({"latex", expression});
}

SliderInstruction::SliderInstruction(
    const std::string& symbol,
    double init_val,
    double start,
    double end,
    double step,
    double period,
    bool running
):
    LatexInstruction(symbol+"="+to_string(init_val)),
    symbol(symbol),
    init_val(init_val),
    start(start),
    end(end),
    step(step),
    period(period),
    is_running(running)
{
    string slider_str = createJson({
        {"min", to_string(start)},
        {"max", to_string(end)},
        {"step", to_string(step)},
        {"animationPeriod", to_string(period)},
        {"isPlaying", to_string(is_running)},
    });
    elems.insert({"slider", slider_str});
}

RawJsonInstruction::RawJsonInstruction(const std::string& content)
    :content(content){}

std::string RawJsonInstruction::getJson() const {
    return content;
}