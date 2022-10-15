#include <string>

class IO {
    public:
        IO();
        ~IO();

        std::string getRequest();
        void writeResponce(std::string ans);
};