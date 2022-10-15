#include <string>

#pragma once

enum ResultState {
    Ok,
    Error,
};

class Result {
    public:
        Result(ResultState res, std::string data);
        ~Result();

        bool isOk();
        std::string unwrap();

    private:
        ResultState m_state;
        std::string m_data;
};
