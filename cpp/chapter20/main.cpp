#include <mysqlx/xdevapi.h>
#include <iostream>
#include "util.h"

using namespace std;
using namespace mysqlx;

const std::string USR       = "vanilla";
const std::string PWD       = "123456";
const std::string HOST      = "localhost";
const std::string DATABASE  = "test";
const std::string TABLECUST = "customers";
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
    sess.sql("use " + DATABASE).execute();
    Schema db = sess.getSchema(DATABASE);
    print("connect to database: " + DATABASE);
    cout << endl;
    Table tb = db.getTable(TABLECUST);
    print("connect to table: " + TABLECUST);
    cout << endl;
    


    print("20-1");
    cout << "sql: update customers "
            "set cust_name = 'test Fudds, "
            "cust_email = 'test@fudd.com "
            "where cust_id = 10005;" << endl;
    auto ans = tb.update()
            .set("cust_name", "test Fudds")
            .set("cust_email", "test@fudd.com")
            .where("cust_id = :id")
            .bind("id", 10005)
            .execute();
    cout << endl;

    print("20-2");
    cout << "sql: delete from customers "
            "where cust_id = 10006;" << endl;
    tb.remove().where("cust_id = :id").bind("id", 10006).execute();
    cout << endl;

}
