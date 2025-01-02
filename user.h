#ifndef USER_H
#define USER_H

#include"DataBase.h"
#include"book.h"
#include<unordered_map>
#include<vector>

using std::vector;
using std::unordered_map;

class user_operation {
public:
    static bool check_User_id(const char x[31]) {
        for (int a=0;x[a]!='\0';a++) {
            if (!(x[a]=='_'||('a'<=x[a]&&x[a]<='z')||('A'<=x[a]&&x[a]<='Z')||('0'<=x[a]&&x[a]<='9'))){
                return true;
            }
        }
        return false;
    }

    static bool check_User_name(const char x[31]) {
        for (int a=0;x[a]!='\0';a++) {
            if (!(32<=x[a]&&x[a]<=126)){
                return true;
            }
        }
        return false;
    }
    static void _login(char user_id[31], const string &password) {
        if (check_User_id(user_id)) {
            throw std::runtime_error("");
        }
        if (check_User_id(password.c_str())) {
            throw std::runtime_error("");
        }
        const auto user_info = user_file.search(user_id);
        if (user_info.empty()) {
            throw std::runtime_error("");
        }
        if (strcmp(user_storage.read(user_info[0]).password, password.data()) != 0) {
            throw std::runtime_error("");
        }
        login_map[user_id]++;
        login_status.emplace_back(char_more<char[31]>(user_id).get_char().data(), user_storage.read(user_info[0]).privilege);
    }

    static void _login(char user_id[31]) {
        if (check_User_id(user_id)) {
            throw std::runtime_error("");
        }
        const auto user_info = user_file.search(user_id);
        if (user_info.empty()) {
            throw std::runtime_error("");
        }
        if (login_status.empty()) {
            throw std::runtime_error("");
        }
        if (user_storage.read(user_info[0]).privilege >= login_status.back().privilege) {
            throw std::runtime_error("");
        } //判断目前账号权限是否高于目标
        login_map[user_id]++;
        login_status.emplace_back(char_more<char[31]>(user_id).get_char().data(), user_storage.read(user_info[0]).privilege);
    }

    static void _logout() {
        if (login_status.empty()) {
            throw std::runtime_error("");
        }
        login_map[login_status.back().id]--;
        login_status.pop_back();
    }

    static void _register(char user_id[31], char password[31], char username[31]) {
        if (check_User_id(user_id)) {
            throw std::runtime_error("");
        }
        if (check_User_id(password)) {
            throw std::runtime_error("");
        }
        if (check_User_name(username)) {
            throw std::runtime_error("");
        }
        if (!user_file.search(user_id).empty()) {
            throw std::runtime_error("");
        }
        user_file.insert(user_id, user_storage.size());
        user_storage.write(name_and_password(password, username, 1));
    }

    static void _modify(char user_id[31], const string & current_password, char new_password[31]) {
        if (check_User_id(user_id)) {
            throw std::runtime_error("");
        }
        if (check_User_id(current_password.data())) {
            throw std::runtime_error("");
        }
        if (check_User_id(new_password)) {
            throw std::runtime_error("");
        }
        if (login_status.empty()) {
            throw std::runtime_error("");
        }
        const auto user_info = user_file.search(user_id);
        if (user_info.empty()) {
            throw std::runtime_error("");
        }
        if (strcmp(user_storage.read(user_info[0]).password, current_password.data())!=0) {
            throw std::runtime_error("");
        }
        if (login_status.empty()) {
            throw std::runtime_error("");
        }
        auto a=user_storage.read(user_info[0]);
        strcpy(a.password,new_password);
        user_storage.update(a,user_info[0]);
    }

    static void _modify(char user_id[31], char new_password[31]) {
        if (check_User_id(user_id)) {
            throw std::runtime_error("");
        }
        if (check_User_id(new_password)) {
            throw std::runtime_error("");
        }
        if (login_status.empty()) {
            throw std::runtime_error("");
        }
        const auto user_info = user_file.search(user_id);
        if (user_info.empty()) {
            throw std::runtime_error("");
        }
        if (login_status.back().privilege != 7) {
            throw std::runtime_error("");
        }
        auto a=user_storage.read(user_info[0]);
        strcpy(a.password,new_password);
        user_storage.update(a,user_info[0]);
    }

    static void _useradd(char user_id[31], char password[31], const int privilege, char username[31]) {
        if (check_User_id(user_id)) {
            throw std::runtime_error("");
        }
        if (check_User_id(password)) {
            throw std::runtime_error("");
        }
        if (check_User_name(username)) {
            throw std::runtime_error("");
        }
        if (login_status.empty()) {
            throw std::runtime_error("");
        }
        if (const auto user_info = user_file.search(user_id); !user_info.empty()) {
            throw std::runtime_error("");
        }
        if (!(login_status.back().privilege >= 3 && login_status.back().privilege > privilege)) {
            throw std::runtime_error("");
        }
        user_file.insert(user_id, user_storage.size());
        user_storage.write(name_and_password(password, username, privilege));
    }

    static void _delete(char user_id[31]) {
        if (check_User_id(user_id)) {
            throw std::runtime_error("");
        }
        if (login_map[string(user_id)]) {
            throw std::runtime_error("");
        }
        if (login_status.empty()||login_status.back().privilege != 7) {
            throw std::runtime_error("");
        }
        const auto user_info = user_file.search(user_id);
        if (user_info.empty()) {
            throw std::runtime_error("");
        }
        user_file.Val_delete(user_id, user_info[0]);
    }
};
#endif //USER_H
