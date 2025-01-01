//
// Created by ckjsuperhh6602 on 24-12-23.
//

#ifndef LOG_H
#define LOG_H

#include <iomanip>
#include"DataBase.h"
#include"user.h"
#include<iostream>

class log {
public:
    static void show(const int count) {
        if (login_status.empty()) {
            throw std::runtime_error("");
        }
        if (login_status.back().privilege != 7) {
            throw std::runtime_error("");
        }
        if (finance_list.size() < count) {
            throw std::runtime_error("");
        }
        if (count == 0) {
            std::cout << '\n';
            return;
        }
        double income = 0, outcome = 0;
        for (int i = finance_list.size() - count; i < finance_list.size(); i++) {
            income += finance_list.read(i).income;
            outcome += finance_list.read(i).outcome;
        }
        std::cout << std::fixed << std::setprecision(2) << "+ " << income << " - " << outcome << '\n';
    }

    static void show() {
        if (login_status.empty()) {
            throw std::runtime_error("");
        }
        if (login_status.back().privilege != 7) {
            throw std::runtime_error("");
        }
        if (finance_list.empty()) {
            cout << "+ 0.00 - 0.00\n";
        }
        double income = 0, outcome = 0;
        for (int i=0;i<finance_list.size();i++) {
            income += finance_list.read(i).income;
            outcome += finance_list.read(i).outcome;
        }
        cout << std::fixed << std::setprecision(2) << "+ " << income << " - " << outcome << '\n';
    }
};
#endif //LOG_H
