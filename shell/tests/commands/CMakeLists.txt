add_executable(WordCountCommandTest0 test0.cpp)
target_link_libraries(WordCountCommandTest0 PRIVATE command)
add_test( NAME WordCountCommand:test0 COMMAND $<TARGET_FILE:WordCountCommandTest0>)

