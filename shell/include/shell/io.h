#include <string>


///Handles input and output of the `Shell`
class IO {
    public:
        IO();
        ~IO();

        /**
         Reads string from input
         - Returns: string from the input stream
         */
        std::string getRequest();
        /**
         Writes to the console
         - Parameter ans: string to be written
         */
        void writeResponce(std::string ans);
};
