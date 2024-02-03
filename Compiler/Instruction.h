#pragma once
#include <string>
#include <map>

struct Instruction{
    Instruction();
    virtual std::string getJson() const;
    static void resetGlobalId();

protected:
    static std::string createJson(const std::map<std::string, std::string>& items, const std::string& newline_prefix = "");
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
        const std::string& init_val = "0",
        const std::string& start = "0",
        const std::string& end = "1",
        const std::string& step = "0",
        const std::string& period = "1000",
        bool is_running = true
    );
private:
    std::string symbol;
    const std::string& init_val = "0";
    const std::string& start = "0";
    const std::string& end = "1";
    const std::string& step = "0";
    const std::string& period = "1000";
    bool is_running = true;
};

struct RawJsonInstruction : public Instruction {
    RawJsonInstruction(const std::string& content);
    virtual std::string getJson() const override;

private:
    std::string content;
};