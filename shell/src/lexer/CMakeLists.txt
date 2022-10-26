add_library( lexer
	lexer.cpp)

target_link_libraries( lexer
	PRIVATE
	token)

target_include_directories( lexer
	PUBLIC
	"${PROJECT_SOURCE_DIR}/shell/include/shell")
