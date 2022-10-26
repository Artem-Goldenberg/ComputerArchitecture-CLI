add_library( commandData
	commandData.cpp)

target_include_directories( commandData
	PUBLIC
	"${PROJECT_SOURCE_DIR}/shell/include/shell")
