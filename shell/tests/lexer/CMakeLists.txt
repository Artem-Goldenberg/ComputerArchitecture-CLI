add_executable(LexerTest0 test0.cpp)
target_link_libraries(LexerTest0 PRIVATE lexer)
add_test( NAME Lexer:test0 COMMAND $<TARGET_FILE:LexerTest0>)

