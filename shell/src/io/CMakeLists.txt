add_library( io
	io.cpp)

target_include_directories( io
	PUBLIC
	"${PROJECT_SOURCE_DIR}/shell/include/shell")
