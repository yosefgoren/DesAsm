#include <emscripten/emscripten.h>
#include <string>
#include <stdexcept>

std::string compile(const char* input_dasm, bool printstdlib);

extern "C" {
    #define COMM_BUF_SIZE 4096

    char* output_buffer;

    EMSCRIPTEN_KEEPALIVE void init(){
        output_buffer = (char*)malloc(sizeof(char)*COMM_BUF_SIZE);
    }

    EMSCRIPTEN_KEEPALIVE void destroy(){
        free(output_buffer);
    }

    EMSCRIPTEN_KEEPALIVE char* compileDasm(char* input_dasm){
        std::string res = compile(input_dasm, true);
        if(res.size() >= COMM_BUF_SIZE){
            throw std::runtime_error("compiled output exceeds buffer size.");
        }
        strncpy(output_buffer, res.c_str(), COMM_BUF_SIZE);
        return output_buffer;
    }
}