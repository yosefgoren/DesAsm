emsdk_env.ps1
emcc -o output/dasm.html -g --shell-file html_template/shell_minimal.html -s NO_EXIT_RUNTIME=1 -s NO_DISABLE_EXCEPTION_CATCHING -s EXPORTED_RUNTIME_METHODS='["cwrap"]' -std=c++17 Wrapper.cpp dummy_impl.cpp
