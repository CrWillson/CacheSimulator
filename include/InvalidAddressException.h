#pragma once

#include <exception>
#include <string>

class InvalidAddressException : public std::exception
{
public:
    InvalidAddressException(const std::string& message) : message_(message) {}
    const char* what() const noexcept override
    {
        return message_.c_str();
    }

private:
    std::string message_;
};