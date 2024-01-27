cmake_minimum_required(VERSION 3.0.0)
project(dasm VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-D_CRT_SECURE_NO_WARNINGS)
add_executable(dasm parser.tab.cpp Exceptions.cpp lex.yy.cpp Symtab.cpp Compiler.cpp BrowserDisp/BrowserDisp.cpp)
add_executable(Prepr Prepr/CinManager.cpp Prepr/Prepr.cpp)
set(SLASH "\\")

add_custom_command(OUTPUT lex.yy.cpp
	COMMAND ..${SLASH}..${SLASH}flexBison${SLASH}win_flex.exe ..${SLASH}scanner.lex
	COMMAND copy lex.yy.c ..${SLASH}lex.yy.cpp
	COMMAND copy lex.yy.c lex.yy.cpp
	DEPENDS scanner.lex
)

add_custom_command(OUTPUT parser.tab.cpp
	COMMAND ..${SLASH}..${SLASH}flexBison${SLASH}win_bison.exe -Wcounterexamples -d ..${SLASH}parser.ypp
	COMMAND copy parser.tab.cpp ..
	COMMAND copy parser.tab.hpp ..
	DEPENDS parser.ypp
)

include_directories(C:${SLASH}Users${SLASH}yosef${SLASH}Desktop${SLASH}Side-Projects${SLASH}DesAsm)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
