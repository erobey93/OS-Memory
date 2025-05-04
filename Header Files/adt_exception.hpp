#ifndef ADT_EXCEPTION_HPP
#define ADT_EXCEPTION_HPP

#include <stdexcept>
#include <string>
#include <ostream>
#include <cstring>

class AdtException : public std::runtime_error {
public:
    explicit AdtException(const std::string& msg) : std::runtime_error(msg) {}

    std::wstring to_wstring() const {
        const char* message = what();
        std::wstring wide_message;
        wide_message.reserve(std::strlen(message));
        while (*message) {
            wide_message.push_back(static_cast<wchar_t>(static_cast<unsigned char>(*message)));
            ++message;
        }
        return wide_message;
    }

    friend std::ostream& operator<<(std::ostream& os, const AdtException& ex) {
        return os << ex.what();
    }
};

#endif // ADT_EXCEPTION_HPP
