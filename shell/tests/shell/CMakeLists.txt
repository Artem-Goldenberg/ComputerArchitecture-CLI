add_executable(IntegrationShellTest0 test0.cpp)
target_link_libraries(IntegrationShellTest0 PRIVATE shell)
add_test( NAME IntegrationShell:test0 COMMAND $<TARGET_FILE:IntegrationShellTest0>)
