#pragma once
#include <string>
#include <map>

struct Instruction{
    Instruction();
    virtual std::string getJson() const;
    static void resetGlobalId();

protected:
    static std::string createJson(const std::map<std::string, std::string>& items);
    unsigned getId() const;

    std::map<std::string, std::string> elems;

private:
    unsigned id;
    static unsigned global_id;
};

struct LatexInstruction : public Instruction {
    std::string expression;
    LatexInstruction(
        const std::string& expression
    );
};

struct SliderInstruction : public LatexInstruction {
    SliderInstruction(
        const std::string& symbol,
        double init_val = 0,
        double start = 0,
        double end = 1,
        double step = 0,
        double period = 1000,
        bool is_running = true
    );
private:
    std::string symbol;
    double init_val = 0;
    double start = 0;
    double end = 1;
    double step = 0;
    double period = 1000;
    bool is_running = true;
};

struct RawJsonInstruction : public Instruction {
    RawJsonInstruction(const std::string& content);
    virtual std::string getJson() const override;

private:
    std::string content;
};