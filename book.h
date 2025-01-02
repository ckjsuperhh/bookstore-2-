//
// Created by ckjsuperhh6602 on 24-12-23.
//

#ifndef BOOK_H
#define BOOK_H
#include <algorithm>
#include<vector>
#include<map>
#include<iostream>
#include"DataBase.h"

using std::vector;
using std::map;
using std::cout;

class book {
public:
    static bool check_ISBN(const char x[61]) {
        for (int a=0;x[a]!='\0';a++) {
            if (!(32<=x[a]&&x[a]<=126)){
                return true;
            }
        }
        return false;
    }
    static bool check_BookName(const char x[61]) {
        for (int a=0;x[a]!='\0';a++) {
            if (!(32<=x[a]&&x[a]<=126&&x[a]!='\"')){
                return true;
            }
        }
        return false;
    }
    static bool check_Author(const char x[61]) {
        for (int a=0;x[a]!='\0';a++) {
            if (!(32<=x[a]&&x[a]<=126&&x[a]!='\"')){
                return true;
            }
        }
        return false;
    }
    static bool check_KeyWord(const char x[61]) {
        for (int a=0;x[a]!='\0';a++) {
            if (!(32<=x[a]&&x[a]<=126&&x[a]!='\"')){
                return true;
            }
        }
        return false;
    }
    static bool check_Price(const char x[14]) {
        for (int a=0;x[a]!='\0';a++) {
            if (!('0'<=x[a]&&x[a]<='9')||x[a]=='.'){
                return true;
            }
        }
        return false;
    }
    static vector<string> find_KeyWord(const string &a) {
        if(a[0]=='|'||a.back()=='|'){
            throw std::runtime_error("");
        }
        vector<string> tmp;
        int l = 0;
        for (int o = 0; o < a.size(); o++) {
            if (a[o] == '|' || o == a.size() - 1) {
                if(o==a.size() - 1){
                    tmp.push_back(a.substr(l, o - l +1 ));
                }else{
                    tmp.push_back(a.substr(l, o - l ));
                }
                l = o+1;
            }
        }
        std::ranges::sort(tmp);
        for(const auto& x:tmp){
            if(x.empty()){
                throw std::runtime_error("");
            }
        }
        if (std::ranges::unique(tmp).begin() - tmp.begin() != tmp.size()) {
            throw std::runtime_error("");
        }
        return tmp;
    }

    static void ISBN_show(char ISBN_[21]) {
        if (check_ISBN(ISBN_)) {
            throw std::runtime_error("");
        }
        if (login_status.empty()) {
            throw std::runtime_error("");
        }
        auto ISBN_vector = ISBN_reference.search(ISBN_);
        if (ISBN_vector.empty()) {
            cout << '\n';
            return;
        }
        vector<book_info> tmp;
        for (const auto x: ISBN_vector) {
            tmp.push_back(ISBN.read(x));
        }
        std::ranges::sort(tmp, [](const book_info &a1, const book_info &a2)-> bool { return strcmp(a1.ISBN, a2.ISBN) > 0; });
        for (const auto x: tmp) {
            cout << x.ISBN << "\t" << x.BookName << "\t" << x.Author << "\t" << x.KeyWord << "\t" <<std::fixed<<std::setprecision(2)<< std::stod(x.Price) << "\t" << x.Storage << "\n";
        }
    }

    static void show() {
        if (login_status.empty()) {
            throw std::runtime_error("");
        }
        if (ISBN.empty()) {
            cout << '\n';
            return;
        }
        auto tmp = ISBN.get_vector();
        std::ranges::sort(tmp, [](const book_info &a1, const book_info &a2)-> bool { return strcmp(a1.ISBN, a2.ISBN) < 0; });
        for (const auto x: tmp) {
            cout << x.ISBN << "\t" << x.BookName << "\t" << x.Author << "\t" << x.KeyWord << "\t" <<std::fixed<<std::setprecision(2)<< std::stod(x.Price) << "\t" << x.Storage << "\n";
        }
    }

    static void other_show(char information[61], const string &a) {
        if (login_status.empty()) {
            throw std::runtime_error("");
        }
        if (a == "name") {
            if (check_BookName(information)) {
                throw std::runtime_error("");
            }
            auto ISBN_vector = BookName_reference.search(information);
            if (ISBN_vector.empty()) {
                cout << '\n';
                return;
            }
            vector<book_info> tmp;
            for (const auto x: ISBN_vector) {
                tmp.push_back(ISBN.read(x));
            }
            std::ranges::sort(tmp, [](const book_info &a1, const book_info &a2)-> bool { return strcmp(a1.ISBN, a2.ISBN) < 0; });
            for (const auto x: tmp) {
                cout << x.ISBN << "\t" << x.BookName << "\t" << x.Author << "\t" << x.KeyWord << "\t" <<std::fixed<<std::setprecision(2)<< std::stod(x.Price) << "\t" << x.Storage << "\n";
            }
        } else if (a == "author") {
            if (check_Author(information)) {
                throw std::runtime_error("");
            }
            auto ISBN_vector = Author_reference.search(information);
            if (ISBN_vector.empty()) {
                cout << '\n';
                return;
            }
            vector<book_info> tmp;
            for (auto x: ISBN_vector) {
                tmp.push_back(ISBN.read(x));
            }
            std::ranges::sort(tmp, [](const book_info &a1, const book_info &a2)-> bool { return strcmp(a1.ISBN, a2.ISBN) < 0; });
            for (const auto x: tmp) {
                cout << x.ISBN << "\t" << x.BookName << "\t" << x.Author << "\t" << x.KeyWord << "\t" <<std::fixed<<std::setprecision(2)<< std::stod(x.Price)<< "\t" << x.Storage << "\n";
            }
        } else if (a == "keyword") {
            if (check_KeyWord(information)) {
                throw std::runtime_error("");
            }
            if (const auto key = find_KeyWord(information); key.size() > 1 || key.empty()) {
                throw std::runtime_error("");
            }
            auto ISBN_vector = KeyWord_reference.search(information);
            if (ISBN_vector.empty()) {
                cout << '\n';
                return;
            }
            vector<book_info> tmp;
            for (auto x: ISBN_vector) {
                tmp.push_back(ISBN.read(x));
            }
            std::ranges::sort(tmp, [](const book_info &a1, const book_info &a2)-> bool { return strcmp(a1.ISBN, a2.ISBN) < 0; });
            for (const auto x: tmp) {
                cout << x.ISBN << "\t" << x.BookName << "\t" << x.Author << "\t" << x.KeyWord << "\t"<<std::fixed<<std::setprecision(2)<< std::stod(x.Price) << "\t" << x.Storage << "\n";
            }
        }
    }

    static void buy(char ISBN_[21], const int quantity) {
        if (check_ISBN(ISBN_)) {
            throw std::runtime_error("");
        }
        if (login_status.empty()) {
            throw std::runtime_error("");
        }
        if (quantity <= 0) {
            throw std::runtime_error("");
        }
        const auto ISBN_vector = ISBN_reference.search(ISBN_);
        if (ISBN_vector.empty()) {
            throw std::runtime_error("");
        }
        if (ISBN.read(ISBN_vector[0]).Storage < quantity) {
            throw std::runtime_error("");
        }
        cout << std::fixed << std::setprecision(2) << std::stod(ISBN.read(ISBN_vector[0]).Price) * quantity << '\n';
        finance_list.write({std::stod(ISBN.read(ISBN_vector[0]).Price) * quantity, 0});
        auto a=ISBN.read(ISBN_vector[0]);
        a.Storage -= quantity;
        ISBN.update(a,ISBN_vector[0]);
    }

    static void select(char ISBN_[21]) {
        if (check_ISBN(ISBN_)) {
            throw std::runtime_error("");
        }
        if (login_status.empty()) {
            throw std::runtime_error("");
        }
        if (login_status.back().privilege < 3) {
            throw std::runtime_error("");
        }
        if (ISBN_reference.search(ISBN_).empty()) {
            ISBN_reference.insert(ISBN_, ISBN.size());
            ISBN.write(book_info(ISBN_));
        }
        login_status.back().num=ISBN_reference.search(ISBN_)[0];
    }

    static void modify_other(const string &a, char information[61]) {
        if (a == "name") {
            if (!BookName_reference.search(ISBN.read(login_status.back().num).BookName).empty()) {
                BookName_reference.Val_delete(ISBN.read(login_status.back().num).BookName, login_status.back().num);
            }
            auto tmp=ISBN.read(login_status.back().num);
            strcpy(tmp.BookName, information);
            ISBN.update(tmp,login_status.back().num);
            BookName_reference.insert(information, login_status.back().num);
        } else if (a == "author") {
            if (!Author_reference.search(ISBN.read(login_status.back().num).Author).empty()) {
                 Author_reference.Val_delete(ISBN.read(login_status.back().num).Author, login_status.back().num);
            }
            auto tmp=ISBN.read(login_status.back().num);
            strcpy(tmp.Author, information);
            ISBN.update(tmp,login_status.back().num);
            Author_reference.insert(information, login_status.back().num);
        } else if (a == "keyword") {
            const auto keys1=find_KeyWord(information);
            const auto keys2=find_KeyWord(ISBN.read(login_status.back().num).KeyWord);
            for (const auto& x:keys2) {
                KeyWord_reference.Val_delete(char_more<char[61]>(x).get_char().data(), login_status.back().num);
            }
            for (const auto& x:keys1) {
                KeyWord_reference.insert(char_more<char[61]>(x).get_char().data(), login_status.back().num);
            }
            auto tmp=ISBN.read(login_status.back().num);
            strcpy(tmp.KeyWord, information);
            ISBN.update(tmp,login_status.back().num);
        } else if (a == "price") {
            auto tmp=ISBN.read(login_status.back().num);
            strncpy(tmp.Price, information,14);
            ISBN.update(tmp,login_status.back().num);
        }
    }

    static void modify_ISBN(char ISBN_[21]) {
        ISBN_reference.Val_delete(ISBN.read(login_status.back().num).ISBN, login_status.back().num);
        auto tmp=ISBN.read(login_status.back().num);
        strcpy(tmp.ISBN, ISBN_);
        ISBN.update(tmp,login_status.back().num);
        ISBN_reference.insert(ISBN_, login_status.back().num);
    }

    static void import(const int quantity, double total_cost) {
        if (login_status.empty()||login_status.back().privilege < 3) {
            throw std::runtime_error("");
        }
        if (login_status.back().num == -1 || quantity <= 0 || total_cost <= 0) {
            throw std::runtime_error("");
        }
        finance_list.write({0, total_cost});
        auto a=ISBN.read(login_status.back().num);
        a.Storage += quantity;
        ISBN.update(a,login_status.back().num);
    }
};

#endif //BOOK_H
