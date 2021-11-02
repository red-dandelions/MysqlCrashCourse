#include <mysqlx/xdevapi.h>

#include <string>
#include <iostream>
#include <list>
#include <iomanip>
#include <algorithm>
#include <sstream>

using namespace std;
using namespace mysqlx;

const std::string USR = "vanilla";
const std::string PWD = "123456";
const std::string tableName = "products";

void func(Session &sess);
void print(std::string str);
void output(vector<std::string>&, list<Row>&);

int main() {

    print("Start connecting to mysql...");
    Session sess("localhost", 33060, USR, PWD);
    print("connect to mysql is successful!");
    cout << endl;

    func(sess);

    sess.close();
    print("close to mysql...");

    return 0;
}

void func(Session &sess) {
    //connect to Database;
    print("Start connecting to database...");
    Schema db = sess.getSchema("test");
    sess.sql("use test").execute();
    print("connect to database: " + std::string(db.getName()));
    cout << endl;

    //connect to table;
    print("Start connecting to table...");
    Table tb = db.getTable(tableName);
    print("connect to table: " + tableName);
    cout << endl;

    RowResult res;
    list<Row> rows;
    cout << setiosflags(ios::fixed) << setprecision(2) << setiosflags(ios::left);
    

    //4-2
    //select prod_name from products;
    print("4-2");
    cout << "sql: select prod_name from products;" << endl;
    res = tb.select("prod_name").execute();
    rows = res.fetchAll();

    vector<std::string> s;
    s.push_back("prod_name");
    output(s, rows);

    //4-3
    //select prod_id, prod_name, prod_price from products;
    print("4-3");
    cout << "sql: select prod_id, prod_name, prod_price from products;" << endl;
    res = tb.select("prod_id", "prod_name", "prod_price").execute();
    rows = res.fetchAll();

    s.clear();
    s.push_back("prod_id");
    s.push_back("prod_name");
    s.push_back("prod_price");
    output(s, rows);


    //4-4
    //select * from products;
    print("4-4");
    cout << "sql: select * from products;" << endl;
    res = sess.sql("select * from products").execute();
    rows = res.fetchAll();

    s.clear();
    s.push_back("prod_id");
    s.push_back("vend_id");
    s.push_back("prod_name");
    s.push_back("prod_price");
    s.push_back("prod_desc");
    output(s, rows);


    //4-5
    //select DISTINCT vend_id from products;
    print("4-5");
    cout << "sql: select distinct vend_id from products;" << endl;
    res = sess.sql("select DISTINCT vend_id from products").execute();
    rows = res.fetchAll();

    s.clear();
    s.push_back("vend_id");
    output(s, rows);


    //4-6
    //select prod_name from products limit 5;
    print("4-6");
    cout << "sql: select prod_name from products limit 10;" << endl;
    res = tb.select("prod_name").limit(10).execute();
    rows = res.fetchAll();

    s.clear();
    s.push_back("prod_name");
    output(s, rows);

    //select prod_name from products limit 5 offset 5;
    cout << "sql: select prod_name from products limit 5 offset 5;" << endl;
    res = tb.select("prod_name").limit(5).offset(5).execute();
    rows = res.fetchAll();
    output(s, rows);

    //4-7
    //限定名
    //select products.prod_name from test.products;
}

void print(std::string str) {
    std::string s(10, '-');
    s += "  " + str + "  ";
    int len = 80 - s.size();
    if (len > 0) {
        std::string tmp(len, '-');
        s += tmp;
    }
    cout << s << endl;
}

void output(vector<std::string>& col, list<Row>& rows) {
    int cols = col.size();
    vector<int> columnlen(cols, 20);
    auto updateCol = [&]() {
        for (const auto &row : rows) {
            for (int i = 0; i < cols; ++i) {
                std::string tmp;
                stringstream strm;
                strm << row[i] << endl;
                getline(strm, tmp);
                columnlen[i] = max(columnlen[i], int(tmp.size() + 2));
            }
        }
    };
    auto line = [](int len) {
        cout << "+" << std::string(len - 2,'-');
    };
    auto outline = [&]() {
        for (const int &i : columnlen)  line(i);
        cout << "+" << endl;
    };
    auto outcol = [&]() {
        for (int i = 0; i < cols; ++i) {
            cout << setw(columnlen[i] - 1) << "| " + col[i];
        }
        cout << "|" << endl;
    };
    auto outdata = [&]() {
        for (const auto &row : rows) {
            for(int i = 0; i < cols; ++i) {
                cout << "|" << setw(columnlen[i] - 2) << row[i];
            }
            cout << "|" << endl;
        }
    };
    updateCol();
    outline();
    outcol();
    outline();
    outdata();
    outline();
    cout << endl;
}
