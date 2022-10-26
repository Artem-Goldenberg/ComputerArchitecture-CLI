add_library( environment
	environment.cpp)

target_include_directories( environment
	PUBLIC
	"${PROJECT_SOURCE_DIR}/shell/include/shell")
