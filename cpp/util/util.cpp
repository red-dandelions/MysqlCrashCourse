#include <mysqlx/xdevapi.h>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <list>

#include "util.h"

void print(std::string str) {

    std::string s(10, '-');
    s += "  " + str + "  ";
    int len = 80 - s.size();
    if (len > 0) {
        std::string tmp(len, '-');
        s += tmp;
    }

    std::cout << s << std::endl;

}

static void updateCol(std::vector<int>& arr, std::list<mysqlx::Row>& rows) {
    for (const auto &row : rows) {
        for (int i = 0; i < arr.size(); ++i) {
            std::string tmp;
            std::stringstream strm;
            strm << row[i] << std::endl;
            std::getline(strm, tmp);
            arr[i] = std::max(arr[i], int(tmp.size() + 2));
        }
    }
}
static void outline(std::vector<int>& arr) {
    for (const int &i : arr) {
        std::cout << "+" << std::string(i - 2,'-');
    }
    std::cout << "+" << std::endl;
}
static void outColumnName(std::vector<int>& arr, mysqlx::RowResult& rres) {
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << "| " << std::setw(arr[i] - 3) << rres.getColumn(i).getColumnName();
    }
    std::cout << "|" << std::endl;
}
static void outdata(std::vector<int>& arr, std::list<mysqlx::Row>& rows) {
    for (const auto &row : rows) {
        for(int i = 0; i < arr.size(); ++i) {
            std::cout << "|" << std::setw(arr[i] - 2) << row[i];
        }
        std::cout << "|" << std::endl;
    }
}

void output(mysqlx::RowResult& rres) {

    std::cout << setiosflags(std::ios::fixed) << std::setprecision(2) << setiosflags(std::ios::left);
    
    int cols    = rres.getColumnCount();
    std::list<mysqlx::Row> rows = rres.fetchAll();
    std::vector<int> columnlen(cols, 20);

    updateCol(columnlen, rows);
    outline(columnlen);
    outColumnName(columnlen, rres);
    outline(columnlen);
    outdata(columnlen, rows);
    outline(columnlen);

}
