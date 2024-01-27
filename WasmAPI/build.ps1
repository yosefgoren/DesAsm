emsdk_env.ps1
emcc -o output/dasm.html -g --shell-file template.html -s NO_EXIT_RUNTIME=1 -s NO_DISABLE_EXCEPTION_CATCHING -s EXPORTED_RUNTIME_METHODS='["cwrap"]' -std=c++17 -I.. Wrapper.cpp ../Compiler/Compiler.cpp ../Compiler/Exceptions.cpp ../Compiler/Symtab.cpp ../parser.tab.cpp ../build/lex.yy.cpp
