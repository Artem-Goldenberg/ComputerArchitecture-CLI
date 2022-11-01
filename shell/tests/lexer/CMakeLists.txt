add_executable(LexerTest0 test0.cpp)
target_link_libraries(LexerTest0 PRIVATE lexer)
add_test( NAME Lexer:test0 COMMAND $<TARGET_FILE:LexerTest0>)

add_executable(LexerTest1 test1.cpp)
target_link_libraries(LexerTest1 PRIVATE lexer)
add_test( NAME Lexer:test1 COMMAND $<TARGET_FILE:LexerTest1>)

add_executable(LexerTest2 test2.cpp)
target_link_libraries(LexerTest2 PRIVATE lexer)
add_test( NAME Lexer:test2 COMMAND $<TARGET_FILE:LexerTest2>)

add_executable(LexerTest3 test3.cpp)
target_link_libraries(LexerTest3 PRIVATE lexer)
add_test( NAME Lexer:test3 COMMAND $<TARGET_FILE:LexerTest3>)

add_executable(LexerTest4 test4.cpp)
target_link_libraries(LexerTest4 PRIVATE lexer)
add_test( NAME Lexer:test4 COMMAND $<TARGET_FILE:LexerTest4>)

add_executable(LexerTest5 test5.cpp)
target_link_libraries(LexerTest5 PRIVATE lexer)
add_test( NAME Lexer:test5 COMMAND $<TARGET_FILE:LexerTest5>)

add_executable(LexerTest6 test6.cpp)
target_link_libraries(LexerTest6 PRIVATE lexer)
add_test( NAME Lexer:test6 COMMAND $<TARGET_FILE:LexerTest6>)

add_executable(LexerTest7 test7.cpp)
target_link_libraries(LexerTest7 PRIVATE lexer)
add_test( NAME Lexer:test7 COMMAND $<TARGET_FILE:LexerTest7>)

add_executable(LexerTest8 test8.cpp)
target_link_libraries(LexerTest8 PRIVATE lexer)
add_test( NAME Lexer:test8 COMMAND $<TARGET_FILE:LexerTest8>)

add_executable(LexerTest9 test9.cpp)
target_link_libraries(LexerTest9 PRIVATE lexer)
add_test( NAME Lexer:test9 COMMAND $<TARGET_FILE:LexerTest9>)

add_executable(LexerTest10 test10.cpp)
target_link_libraries(LexerTest10 PRIVATE lexer)
add_test( NAME Lexer:test10 COMMAND $<TARGET_FILE:LexerTest10>)