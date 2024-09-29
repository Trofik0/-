#ifndef CHAT_H
#define CHAT_H

#include <iostream>
using namespace std;

#include <vector>
#include <string>
#include "User.h"
#include "UserStorage.h"
#include "Exceptions.h"

// Класс чата
template <typename T>
class Chat {
private:
    UserStorage<User<string>> userStorage;
   vector<string> messages;
    User<string>* currentUser = nullptr;

public:
    // Регистрация пользователя
    void registerUser(const string& login, const string& password, const string& name) {
        User<string> user(login, password, name);
        userStorage.addUser(user);
    }

    // Аутентификация пользователя
    bool loginUser(const string& loginOrPassword) {
        User<string>* user = userStorage.getUserByLoginOrPassword(loginOrPassword);
        if (user) {
            currentUser = user;
            cout << "Вход в чат успешен. Вы вошли как " << currentUser->name << "." << endl;
            return true;
        }

        cout << "Ошибка аутентификации пользователя." << endl;
        return false;
    }

    // Отправка сообщения конкретному пользователю
    void sendMessageToUser(const string& receiverLoginOrPassword, const string& message) {
        if (currentUser) {
            User<string>* receiver = userStorage.getUserByLoginOrPassword(receiverLoginOrPassword);
            if (receiver) {
                messages.emplace_back(currentUser->name + ": " + message);
                cout << "Сообщение отправлено пользователю " << receiver->name << "." << endl;

                cout << receiver->name << " получил сообщение: " << message << endl;
            }
            else {
                throw AuthenticationException();
            }
        }
        else {
            throw AuthenticationException();
        }
    }


    // Отправка сообщения всем пользователям
    void sendMessage(const string& message) {
        if (currentUser) {
            messages.emplace_back(currentUser->name + ": " + message);
            cout << "Сообщение отправлено всем пользователям." << endl;

            // Отправка сообщения всем пользователям
            vector<User<string>> users = userStorage.getAllUsers();
            for (const auto& user : users) {
                if (user.login != currentUser->login) {
                    cout << user.name << " получил сообщение: " << message << endl;
                }
            }
        }
        else {
            throw AuthenticationException();
        }
    }

    // Получение истории сообщений
    vector<string> getMessageHistory() const {
        return messages;
    }
};

#endif // CHAT_H
