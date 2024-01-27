#include <emscripten/emscripten.h>
#include <string>
#include <stdexcept>

std::string compile(const char* input_dasm, bool printstdlib);

extern "C" {
    #define COMM_BUF_SIZE 10000

    char* output_buffer;

    EMSCRIPTEN_KEEPALIVE void init(){
        output_buffer = (char*)malloc(sizeof(char)*COMM_BUF_SIZE);
    }

    EMSCRIPTEN_KEEPALIVE void destroy(){
        free(output_buffer);
    }

    EMSCRIPTEN_KEEPALIVE char* compileDasm(char* input_dasm){
        std::string res = "";
        try {
            res = compile(input_dasm, true);
            if(res.size() >= COMM_BUF_SIZE){
                throw std::runtime_error("compiled output exceeds buffer size.");
            }
        } catch (std::runtime_error& err) {
            fprintf(stderr, "Dasm Compiler failed due to runtime error: '%s'\n", err.what());
        } catch (...) {
            fprintf(stderr, "Dasm Compiler failed due to unknown error.\n");
        }
        strncpy(output_buffer, res.c_str(), COMM_BUF_SIZE);
        // printf("compileDasm returning: %s\n", output_buffer);
        return output_buffer;
    }
}