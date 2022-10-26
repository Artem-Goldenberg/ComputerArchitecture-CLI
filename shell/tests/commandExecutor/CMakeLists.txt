add_executable(CommandExecutorTest0 test0.cpp)
target_link_libraries(CommandExecutorTest0 PRIVATE commandExecutor)
add_test( NAME CommandExecutor:test0 COMMAND $<TARGET_FILE:CommandExecutorTest0>)

