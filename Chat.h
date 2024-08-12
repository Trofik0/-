#ifndef CHAT_H
#define CHAT_H

#include <vector>
#include <string>
#include <algorithm>
#include <mutex>
#include "User.h"
#include "Exceptions.h"
using namespace std;
// Класс чата
template <typename T>
class Chat {
private:
    vector<T> users;
    mutex chatMutex;

public:
    // Регистрация нового пользователя
    void registerUser(string login, string password, string name) {
        lock_guard<mutex> lock(chatMutex);
        // Проверяем, что пользователь с таким логином еще не зарегистрирован
        if (find_if(users.begin(), users.end(), [&](const T& user) {
            return user.login == login;
            }) != users.end()) {
            throw AuthenticationException();
        }

        // Создаем нового пользователя и добавляем его в список
        T newUser(login, password, name);
        users.push_back(newUser);
        cout << "Пользователь " << name << " успешно зарегистрирован." << endl;
    }

    // Аутентификация пользователя
    bool login(string loginOrPassword) {
        lock_guard<mutex> lock(chatMutex);
        // Ищем пользователя с указанным логином или паролем
        auto user = find_if(users.begin(), users.end(), [&](const T& user) {
            return user.login == loginOrPassword || user.password == loginOrPassword;
            });

        // Если пользователь найден, возвращаем true
        if (user != users.end()) {
            cout << "Пользователь " << user->name << " успешно вошел в чат." << endl;
            return true;
        }

        throw AuthenticationException();
    }

    // Отправка сообщения конкретному пользователю
    void sendMessageToUser(string senderLoginOrPassword, string receiverLoginOrPassword, string message) {
        lock_guard<mutex> lock(chatMutex);
        // Ищем отправителя
        auto sender = find_if(users.begin(), users.end(), [&](const T& user) {
            return user.login == senderLoginOrPassword || user.password == senderLoginOrPassword;
            });

        // Ищем получателя
        auto receiver = find_if(users.begin(), users.end(), [&](const T& user) {
            return user.login == receiverLoginOrPassword || user.password == receiverLoginOrPassword;
            });

        // Если отправитель и получатель найдены, отправляем сообщение
        if (sender != users.end() && receiver != users.end()) {
            cout << sender->name << " -> " << receiver->name << ": " << message << endl;
        }
        else {
            throw MessageSendingException();
        }
    }

    // Отправка сообщения всем пользователям
    void sendMessage(string senderLoginOrPassword, string message) {
        lock_guard<mutex> lock(chatMutex);
        // Ищем отправителя
        auto sender = find_if(users.begin(), users.end(), [&](const T& user) {

            return user.login == senderLoginOrPassword || user.password == senderLoginOrPassword;
            });

        // Если отправитель найден, отправляем сообщение всем пользователям
        if (sender != users.end()) {
            for (const auto& user : users) {
                cout << sender->name << " -> " << user.name << ": " << message << endl;
            }
        }
        else {
            throw MessageSendingException();
        }
    }

    // Получение списка пользователей
    vector<T> getUsers() {
        return users;
    }
};
#endif // CHAT_H

