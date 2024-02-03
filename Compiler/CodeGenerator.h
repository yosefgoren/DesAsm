#pragma once

#include "Instruction.h"
#include <vector>
#include <memory>

struct CodeGenrator {
    void addLatex(const std::string& latex);
    void addSlider(
        const std::string& symbol,
        const std::string& init_val = "0",
        const std::string& start = "0",
        const std::string& end = "1",
        const std::string& step = "0",
        const std::string& period = "1000",
        bool is_running = true
    );
    void addRawJson(const std::string& content);

    std::string generate() const;
    void reset();

private:
    std::vector<std::unique_ptr<Instruction>> instructions;
};