add_library( result
	result.cpp)

target_include_directories( result
	PUBLIC
	"${PROJECT_SOURCE_DIR}/shell/include/shell")
