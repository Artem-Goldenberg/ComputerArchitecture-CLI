add_executable(IntegrationShellTest0 test0.cpp)
target_link_libraries(IntegrationShellTest0 PRIVATE shell)
add_test( NAME IntegrationShell:test0 COMMAND $<TARGET_FILE:IntegrationShellTest0>)

add_executable(IntegrationShellTest1 test1.cpp)
target_link_libraries(IntegrationShellTest1 PRIVATE shell)
add_test( NAME IntegrationShell:test1 COMMAND $<TARGET_FILE:IntegrationShellTest1>)

add_executable(IntegrationShellTest2 test2.cpp)
target_link_libraries(IntegrationShellTest2 PRIVATE shell)
add_test( NAME IntegrationShell:test2 COMMAND $<TARGET_FILE:IntegrationShellTest2>)

add_executable(IntegrationShellTest3 test3.cpp)
target_link_libraries(IntegrationShellTest3 PRIVATE shell)
add_test( NAME IntegrationShell:test3 COMMAND $<TARGET_FILE:IntegrationShellTest3>)

add_executable(IntegrationShellTest4 test4.cpp)
target_link_libraries(IntegrationShellTest4 PRIVATE shell)
add_test( NAME IntegrationShell:test4 COMMAND $<TARGET_FILE:IntegrationShellTest4>)

add_executable(IntegrationShellTest5 test5.cpp)
target_link_libraries(IntegrationShellTest5 PRIVATE shell)
add_test( NAME IntegrationShell:test5 COMMAND $<TARGET_FILE:IntegrationShellTest5>)

add_executable(IntegrationShellTest6 test6.cpp)
target_link_libraries(IntegrationShellTest6 PRIVATE shell)
add_test( NAME IntegrationShell:test6 COMMAND $<TARGET_FILE:IntegrationShellTest6>)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/test2.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})