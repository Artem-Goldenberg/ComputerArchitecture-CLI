add_executable(ParserTest0 test0.cpp)
target_link_libraries(ParserTest0 PRIVATE parser)
add_test( NAME Parser:test0 COMMAND $<TARGET_FILE:ParserTest0>)

