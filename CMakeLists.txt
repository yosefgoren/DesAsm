cmake_minimum_required(VERSION 3.0.0)
project(dasm VERSION 0.1.0)

include(CTest)
enable_testing()
# add_compile_options(-DYYDEBUG 1)
add_executable(dasm parser.tab.cpp Exceptions.cpp lex.yy.cpp Symtab.cpp utility.cpp display_latex.cpp)
add_executable(preprocessor CinManager.cpp preprocessor.cpp)
set(SLASH "\\")

add_custom_command(OUTPUT lex.yy.cpp
	COMMAND ..${SLASH}flexBison${SLASH}win_flex.exe ..${SLASH}scanner.lex
	COMMAND copy lex.yy.c ..${SLASH}lex.yy.cpp
	COMMAND copy lex.yy.c lex.yy.cpp
	DEPENDS scanner.lex
)

add_custom_command(OUTPUT parser.tab.cpp
	COMMAND ..${SLASH}flexBison${SLASH}win_bison.exe -Wcounterexamples -d ..${SLASH}parser.ypp
	COMMAND copy parser.tab.cpp ..
	COMMAND copy parser.tab.hpp ..
	DEPENDS parser.ypp
)

include_directories(C:${SLASH}Users${SLASH}pc${SLASH}Desktop${SLASH}Projects${SLASH}DesAsm)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
