#include "result.h"

Result::Result(ResultState res, std::string data) :
    m_state(res), m_data("") {}

Result::~Result() {}

bool Result::isOk() {
    return m_state == Ok;
}

std::string Result::unwrap() {
    return m_data;

}
