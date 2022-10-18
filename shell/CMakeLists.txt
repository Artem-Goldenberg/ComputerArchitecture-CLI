add_library(shell
    "${CMAKE_CURRENT_SOURCE_DIR}/src/lexer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/result.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/token.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/commandData.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/commandExecutor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/parser.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/environment.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/preprocessor.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/io.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/shell.cpp")

target_include_directories(shell
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/shell"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include/private"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/shell/shell")