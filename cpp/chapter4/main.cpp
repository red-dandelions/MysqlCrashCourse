#include <mysqlx/xdevapi.h>
#include <iostream>
#include "util.h"

using namespace std;
using namespace mysqlx;

const std::string USR       = "vanilla";
const std::string PWD       = "123456";
const std::string TABLENAME = "products";
const std::string HOST      = "localhost";
const std::string DATABASE  = "test";
const int PORT              = 33060;

RowResult res;

void func(Session&);

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

   // cout << setiosflags(ios::fixed) << setprecision(2) << setiosflags(ios::left);

    //4-2
    //select prod_name from products;
    print("4-2");
    cout << "sql: select prod_name from products;" << endl;
    res = tb.select("prod_name").execute();
    output(res);
    cout << endl;

    //4-3
    //select prod_id, prod_name, prod_price from products;
    print("4-3");
    cout << "sql: select prod_id, prod_name, prod_price from products;" << endl;
    res = tb.select("prod_id", "prod_name", "prod_price").execute();
    output(res);
    cout << endl;

    //4-4
    //select * from products;
    print("4-4");
    cout << "sql: select * from products;" << endl;
    res = sess.sql("select * from products").execute();
    output(res);
    cout << endl;

    //4-5
    //select DISTINCT vend_id from products;
    print("4-5");
    cout << "sql: select distinct vend_id from products;" << endl;
    res = sess.sql("select DISTINCT vend_id from products").execute();
    output(res);
    cout << endl;

    //4-6
    //select prod_name from products limit 5;
    print("4-6");
    cout << "sql: select prod_name from products limit 10;" << endl;
    res = tb.select("prod_name").limit(10).execute();
    output(res);
    cout << endl;

    //select prod_name from products limit 5 offset 5;
    cout << "sql: select prod_name from products limit 5 offset 5;" << endl;
    res = tb.select("prod_name").limit(5).offset(5).execute();
    output(res);
    cout << endl;

    //4-7
    //限定名
    //select products.prod_name from test.products;

}
