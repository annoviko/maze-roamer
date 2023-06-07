#include "graphic_error.h"


graphic_error::graphic_error(const std::string& p_message) :
    m_message(p_message)
{ }


graphic_error::~graphic_error() { }


char const* graphic_error::what() const {
    return m_message.c_str();
}
