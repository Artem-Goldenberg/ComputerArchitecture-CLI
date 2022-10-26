add_executable(PreprocessorTest1 test1.cpp)
target_link_libraries(PreprocessorTest1 PRIVATE preprocessor)
add_test( NAME Preprocessor:test1 COMMAND $<TARGET_FILE:PreprocessorTest1>)

add_executable(PreprocessorTest2 test2.cpp)
target_link_libraries(PreprocessorTest2 PRIVATE preprocessor)
add_test( NAME Preprocessor:test2 COMMAND $<TARGET_FILE:PreprocessorTest2>)

add_executable(PreprocessorTest3 test3.cpp)
target_link_libraries(PreprocessorTest3 PRIVATE preprocessor)
add_test( NAME Preprocessor:test3 COMMAND $<TARGET_FILE:PreprocessorTest3>)

add_executable(PreprocessorTest4 test4.cpp)
target_link_libraries(PreprocessorTest4 PRIVATE preprocessor)
add_test( NAME Preprocessor:test4 COMMAND $<TARGET_FILE:PreprocessorTest4>)
