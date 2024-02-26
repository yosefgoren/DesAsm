#include <emscripten/emscripten.h>
#include <string>

std::string compile(const char* input_dasm, bool printstdlib, bool instructions_only);


extern "C" {
    #define COMM_BUF_SIZE 100000
    #include <stdexcept>
    
    char* output_buffer;

    char* retOnBuf(const char* data) {
        strncpy(output_buffer, data, COMM_BUF_SIZE);
        return output_buffer;
    }

    EMSCRIPTEN_KEEPALIVE void init(){
        output_buffer = (char*)malloc(sizeof(char)*COMM_BUF_SIZE);
    }

    EMSCRIPTEN_KEEPALIVE void destroy(){
        free(output_buffer);
    }

    EMSCRIPTEN_KEEPALIVE char* compileDasm(char* input_dasm){
        std::string res = "";
        try {
            res = compile(input_dasm, true, false);
            if(res.size() >= COMM_BUF_SIZE){
                throw std::runtime_error("compiled output exceeds buffer size.");
            }
        } catch (std::runtime_error& err) {
            // fprintf(stderr, "Dasm Compiler failed due to runtime error: '%s'\n", err.what());
            return retOnBuf(("!Dasm Compiler failed due to runtime error:\n\t'"+std::string(err.what())+"'").c_str());
        } catch (...) {
            // fprintf(stderr, "Dasm Compiler failed due to unknown error.\n");
            return retOnBuf("!Dasm Compiler failed due to unknown error.");
        }
        return retOnBuf(res.c_str());
    }
}