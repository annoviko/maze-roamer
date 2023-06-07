#pragma once

#include <exception>
#include <string>


class graphic_error : public std::exception {
private:
    std::string m_message;

public:
    graphic_error(const std::string& p_message);

    virtual ~graphic_error();

public:
    char const* what() const override;
};
