add_library( commandExecutor
	commandExecutor.cpp)

target_include_directories( commandExecutor
	PUBLIC
	"${PROJECT_SOURCE_DIR}/shell/include/shell")
