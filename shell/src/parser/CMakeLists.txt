add_library( parser
	parser.cpp)

target_link_libraries( parser
	PRIVATE
	commandData
	token)

target_include_directories( parser
	PUBLIC
	"${PROJECT_SOURCE_DIR}/shell/include/shell")
