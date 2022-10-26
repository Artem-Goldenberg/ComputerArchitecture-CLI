add_library( token
	token.cpp)

target_include_directories( token
	PUBLIC
	"${PROJECT_SOURCE_DIR}/shell/include/shell")
