#include <mysqlx/xdevapi.h>

#include <string>
#include <iostream>
#include <list>
#include <iomanip>
#include <algorithm>
#include <sstream>

using namespace std;
using namespace mysqlx;

const std::string USR       = "vanilla";
const std::string PWD       = "123456";
const std::string TABLENAME = "products";
const std::string HOST      = "localhost";
const std::string DATABASE  = "test";
const int PORT              = 33060;

RowResult res;
list<Row> rows;

void func(Session&);
void print(std::string);
void output(RowResult&);

int main() {

    print("Start connecting to mysql...");
    Session sess(HOST, PORT, USR, PWD);
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
    Schema db = sess.getSchema(DATABASE);
    sess.sql("use test").execute();
    print("connect to database: " + DATABASE);
    cout << endl;

    //connect to table;
    print("Start connecting to table...");
    Table tb = db.getTable(TABLENAME);
    print("connect to table: " + TABLENAME);
    cout << endl;

    cout << setiosflags(ios::fixed) << setprecision(2) << setiosflags(ios::left);

    //5-1
    //select prod_name from products order by prod_name;
    print("5-1");
    cout << "sql: select prod_name from products order by prod_name;" << endl;
    res = tb.select("prod_name")
            .orderBy("prod_name")
            .execute();
    output(res);
    cout << endl;

    //5-2
    //select prod_id, prod_price, prod_name from products order by prod_price, prod_name;
    print("5-2");
    cout << "sql: select prod_id, prod_price, prod_name from products "
            "order by prod_price, prod_name;" << endl;
    res = tb.select("prod_id", "prod_price", "prod_name")
            .orderBy("prod_price", "prod_name")
            .execute();
    output(res);
    cout << endl;

    //5-3
    //select prod_id, prod_price, prod_name
    //from products
    //order by prod_price DESC;
    print("5-3");
    cout << "sql: select prod_id, prod_price, prod_name "
            "from products "
            "order by prod_price DESC;" << endl;
    res = tb.select("prod_id", "prod_price", "prod_name")
            .orderBy("prod_price DESC")
            //.bind("param", "DESC")
            .execute();
    output(res);
    cout << endl;

    cout << "sql: select prod_price from products order by prod_price DESC limit 1;" << endl;
    res = tb.select("prod_price")
            .orderBy("prod_price DESC")
            .limit(1)
            .execute();
    output(res);
    cout << endl;

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

void output(RowResult& rres) {

    int cols    = rres.getColumnCount();
    rows        = rres.fetchAll();
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
    auto outline = [&]() {
        for (const int &i : columnlen) {
            cout << "+" << std::string(i - 2,'-');
        }
        cout << "+" << endl;
    };
    auto outColumnName = [&]() {
        for (int i = 0; i < cols; ++i) {
            cout << "| " << setw(columnlen[i] - 3) << rres.getColumn(i).getColumnName();
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
    outColumnName();
    outline();
    outdata();
    outline();

}
