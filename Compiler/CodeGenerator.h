#pragma once

#include "Instruction.h"
#include <vector>
#include <memory>

struct CodeGenrator {
    void addLatex(const std::string& latex);
    void addSlider(
        const std::string& symbol,
        double init_val = 0,
        double start = 0,
        double end = 1,
        double step = 0,
        double period = 1000,
        bool is_running = true
    );
    void addRawJson(const std::string& content);

    std::string generate() const;
    void reset();

private:
    std::vector<std::unique_ptr<Instruction>> instructions;
};