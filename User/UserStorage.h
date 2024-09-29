#ifndef USERSTORAGE_H
#define USERSTORAGE_H

#include <unordered_map>
#include <vector>
#include "User.h"
using namespace std;
// Вспомогательный класс для хранения пользователей
template <typename T>
class UserStorage {
private:
    unordered_map<string, T> users;

public:
    // Добавление нового пользователя
    void addUser(const T& user) {
        users.emplace(user.login, user);
    }

    // Получение пользователя по логину или паролю
    T* getUserByLoginOrPassword(const string& loginOrPassword) {
        auto it = users.find(loginOrPassword);
        if (it != users.end()) {
            return &it->second;
        }
        return nullptr;
    }

    // Получение списка всех пользователей
    vector<T> getAllUsers() const {
        vector<T> userList;
        for (const auto& [key, user] : users) {
            userList.push_back(user);
        }
        return userList;
    }
};

#endif // USERSTORAGE_H
