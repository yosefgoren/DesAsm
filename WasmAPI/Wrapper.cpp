#include <emscripten/emscripten.h>
#include <sstream>

extern "C" {
    #define COMM_BUF_SIZE 1024

    char* output_buffer;

    EMSCRIPTEN_KEEPALIVE char* init(){
        output_buffer = (char*)malloc(sizeof(char)*COMM_BUF_SIZE);
    }

    EMSCRIPTEN_KEEPALIVE void destroy(){
        free(output_buffer);
    }

    EMSCRIPTEN_KEEPALIVE char* compile(char* input_dasm){
        sstream is(input_dasm);
        sstream os;

        compile(is, os);

        strncpy(output_buffer, os.string().c_str(), COMM_BUF_SIZE);
        return output_buffer;
    }
}