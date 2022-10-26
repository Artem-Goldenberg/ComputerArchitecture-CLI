add_library( command
	command.cpp)

target_link_libraries( command
	PRIVATE
	environment
	result)

target_include_directories( command
	PUBLIC
	"${PROJECT_SOURCE_DIR}/shell/include/shell")
