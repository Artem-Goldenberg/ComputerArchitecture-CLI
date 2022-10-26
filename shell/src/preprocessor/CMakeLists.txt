add_library( preprocessor
	preprocessor.cpp)

target_link_libraries( preprocessor
	PRIVATE
	result
	environment)

target_include_directories( preprocessor
	PUBLIC
	"${PROJECT_SOURCE_DIR}/shell/include/shell")
