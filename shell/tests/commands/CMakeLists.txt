add_executable(WordCountCommandTest0 wc0.cpp)
target_link_libraries(WordCountCommandTest0 PRIVATE command)
add_test( NAME WordCountCommand:test0 COMMAND $<TARGET_FILE:WordCountCommandTest0>)

add_executable(WordCountCommandTest1 wc1.cpp)
target_link_libraries(WordCountCommandTest1 PRIVATE command)
add_test( NAME WordCountCommand:test1 COMMAND $<TARGET_FILE:WordCountCommandTest1>)

add_executable(WordCountCommandTest2 wc2.cpp)
target_link_libraries(WordCountCommandTest2 PRIVATE command)
add_test( NAME WordCountCommand:test2 COMMAND $<TARGET_FILE:WordCountCommandTest2>)

add_executable(GrepCommandTest grepAll.cpp)
target_link_libraries(GrepCommandTest PRIVATE command)
add_test( NAME GrepCommandTest:test COMMAND $<TARGET_FILE:GrepCommandTest>)

add_executable(ExternalCommandTest0 ext0.cpp)
target_link_libraries(ExternalCommandTest0 PRIVATE command)
add_test( NAME ExternalCommand:test0 COMMAND $<TARGET_FILE:ExternalCommandTest0>)

add_executable(AssignmentCommandTest0 assn0.cpp)
target_link_libraries(AssignmentCommandTest0 PRIVATE command)
add_test( NAME AssignmentCommand:test0 COMMAND $<TARGET_FILE:AssignmentCommandTest0>)

add_executable(AssignmentCommandTest1 assn1.cpp)
target_link_libraries(AssignmentCommandTest1 PRIVATE command)
add_test( NAME AssignmentCommand:test1 COMMAND $<TARGET_FILE:AssignmentCommandTest1>)

add_executable(AssignmentCommandTest2 assn2.cpp)
target_link_libraries(AssignmentCommandTest2 PRIVATE command)
add_test( NAME AssignmentCommand:test2 COMMAND $<TARGET_FILE:AssignmentCommandTest2>)

add_executable(CatCommandTest0 cat0.cpp)
target_link_libraries(CatCommandTest0 PRIVATE command)
add_test( NAME CatCommand:test0 COMMAND $<TARGET_FILE:CatCommandTest0>)

add_executable(CatCommandTest1 cat1.cpp)
target_link_libraries(CatCommandTest1 PRIVATE command)
add_test( NAME CatCommand:test1 COMMAND $<TARGET_FILE:CatCommandTest1>)

add_executable(CatCommandTest2 cat2.cpp)
target_link_libraries(CatCommandTest2 PRIVATE command)
add_test( NAME CatCommand:test2 COMMAND $<TARGET_FILE:CatCommandTest2>)

add_executable(EchoCommandTest0 echo0.cpp)
target_link_libraries(EchoCommandTest0 PRIVATE command)
add_test( NAME EchoCommand:test0 COMMAND $<TARGET_FILE:EchoCommandTest0>)

add_executable(PwdCommandTest0 pwd0.cpp)
target_link_libraries(PwdCommandTest0 PRIVATE command)
add_test( NAME PwdCommand:test0 COMMAND $<TARGET_FILE:PwdCommandTest0>)

add_executable(ExitCommandTest0 exit0.cpp)
target_link_libraries(ExitCommandTest0 PRIVATE command)
add_test( NAME ExitCommand:test0 COMMAND $<TARGET_FILE:ExitCommandTest0>)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testInput.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testInput1.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testInput2.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testInput3.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
