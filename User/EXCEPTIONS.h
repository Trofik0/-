#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

// Исключение для ошибок аутентификации
class AuthenticationException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Ошибка аутентификации пользователя.";
    }
};

// Исключение для ошибок отправки сообщения
class MessageSendingException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Ошибка отправки сообщения.";
    }
};

#endif // EXCEPTIONS_H



