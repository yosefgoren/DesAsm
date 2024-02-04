#pragma once

#include "Instruction.h"
#include <vector>
#include <memory>

struct CodeGenrator {
    void addLatex(const std::string& latex, bool hidden = true);
    void addSlider(
        const std::string& symbol,
        const std::string& init_val = "0",
        const std::string& start = "0",
        const std::string& end = "1",
        const std::string& step = "0",
        const std::string& speed = "1",
        /*
        speed to 'animationPeriod' pattern extrapolation:
        f(0.5) = 8000
        f(0.75) = 5333.333333333333
        f(1.5) = 2666.6666666666665
        f(2.0) = 2000

        f(x) = 4000/x
        */
        bool is_running = true
    );
    void addRawJson(const std::string& content);

    std::string generate() const;
    void reset();

private:
    std::vector<std::unique_ptr<Instruction>> instructions;
};