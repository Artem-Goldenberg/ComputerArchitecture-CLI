add_library( shell
	shell.cpp)

target_link_libraries( shell
	PRIVATE
	io
	preprocessor
	lexer
	parser
	commandExecutor)

target_include_directories( shell
	PUBLIC
	"${PROJECT_SOURCE_DIR}/shell/include/"
  	PRIVATE
	"${PROJECT_SOURCE_DIR}/shell/include/shell")
