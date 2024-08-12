#include <iostream>
#include <string>
#include "Chat.h"
using namespace std;
int main() {
    // Используем шаблон для создания чата с пользователями User
    Chat<User<string>> chat;

    try {
        // Регистрация пользователей
        string login, password, name;

        // Регистрация первого пользователя
        cout << "Регистрация первого пользователя:" << endl;
        cout << "Введите логин: ";
        getline(cin, login);
        cout << "Введите пароль: ";
        getline(cin, password);
        cout << "Введите имя: ";
        getline(cin, name);
        chat.registerUser(login, password, name);

        // Регистрация второго пользователя
        cout << "Регистрация второго пользователя:" << endl;
        cout << "Введите логин: ";
        getline(cin, login);
        cout << "Введите пароль: ";
        getline(cin, password);
        cout << "Введите имя: ";
        getline(cin, name);
        chat.registerUser(login, password, name);

        // Регистрация третьего пользователя
        cout << "Регистрация третьего пользователя:" << endl;
        cout << "Введите логин: ";
        getline(cin, login);
        cout << "Введите пароль: ";
        getline(cin, password);
        cout << "Введите имя: ";
        getline(cin, name);
        chat.registerUser(login, password, name);

        // Выбор отправки сообщения
        std::string senderLoginOrPassword, receiverLoginOrPassword, message;
        int choice;
        do {
            cout << "Выберите действие:" << endl;
            cout << "1. Отправить сообщение конкретному пользователю" << endl;
            cout << "2. Отправить сообщение всем пользователям" << endl;
            cout << "3. Выйти" << endl;
            cout << "Ваш выбор: ";
            cin >> choice;
            cin.ignore(); // Очищаем буфер ввода

            switch (choice) {
            case 1:
                cout << "Введите логин или пароль отправителя: ";
                getline(cin, senderLoginOrPassword);
                cout << "Введите логин или пароль получателя: ";
                getline(cin, receiverLoginOrPassword);
                cout << "Введите сообщение: ";
                getline(cin, message);
                chat.sendMessageToUser(senderLoginOrPassword, receiverLoginOrPassword, message);
                break;
            case 2:
                cout << "Введите логин или пароль отправителя: ";
                getline(cin, senderLoginOrPassword);
                cout << "Введите сообщение: ";
                getline(cin, message);
                chat.sendMessage(senderLoginOrPassword, message);
                break;
            case 3:
                cout << "Выход из программы." << endl;
                break;
            default:
                cout << "Неверный выбор. Попробуйте еще раз." << endl;
                break;
            }
        } while (choice != 3);

    }
    catch (const AuthenticationException& e) {
        cerr << e.what() << endl;
    }
    catch (const MessageSendingException& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
