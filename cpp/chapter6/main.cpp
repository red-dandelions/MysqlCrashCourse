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

    //6-1
    //select prod_name, prod_price
    //from products
    //where prod_price = 2.50;
    print("6-1");
    cout << "sql: select prod_name, prod_price "
            "from products "
            "where prod_price = 2.50;;" << endl;
    res = tb.select("prod_name", "prod_price")
            .where("prod_price = :price")
            .bind("price", 2.50)
            .execute();
    output(res);
    cout << endl;

    //6-2
    //=, <>, !=, <, <=, >, >=, between
    //6-2-1
    print("6-2");
    cout << "sql: select prod_name, prod_price "
            "from products "
            "where prod_name = 'fuses;" << endl;
    res = tb.select("prod_name", "prod_price")
            .where("prod_name = :name")
            .bind("name", "fuses")
            .execute();
    output(res);
    cout << endl;

    //select prod_name, prod_price
    //from products
    //where prod_price < 10;
    cout << "sql: select prod_name, prod_price "
            "from products "
            "where prod_price < 10;" << endl;
    res = tb.select("prod_name", "prod_price")
            .where("prod_price < :price")
            .bind("price", 10)
            .execute();
    output(res);
    cout << endl;

    //select prod_name, prod_price
    //from products
    //where prod_price <= 10;
    cout << "sql: select prod_name, prod_price "
            "from products "
            "where prod_price <= 10;" << endl;
    res = tb.select("prod_name", "prod_price")
            .where("prod_price <= :price")
            .bind("price", 10)
            .execute();
    output(res);
    cout << endl;

    //6-2-2
    //select vend_id, prod_name
    //from products
    //where vend_id <> 1003;
    cout << "sql: select vend_id, prod_name "
            "from products "
            "where vend_id <> 1003;" << endl;
    res = tb.select("vend_id", "prod_name")
            .where("vend_id <> :id")
            .bind("id", 1003)
            .execute();
    output(res);
    cout << endl;

    //6-2-3
    //select prod_name, prod_price
    //from products
    //where prod_price between 5 and 10
    cout << "sql: select prod_name, prod_price "
            "from products "
            "where prod_price between 5 and 10;" << endl;
    res = tb.select("prod_name", "prod_price")
            .where("prod_price between :begin and :end")
            .bind("begin", 5).bind("end", 10)
            .execute();
    output(res);
    cout << endl;

    //6-2-4
    //select cust_id
    //from customers
    //where cust_email is null;
    std::string tbname = "customers";
    tb = db.getTable(tbname);
    cout << "sql: select cust_id "
            "from customers "
            "where cust_email is null;" << endl;
    res = tb.select("cust_id")
            .where("cust_email is null")
            .execute();
    output(res);
    cout << endl;

}
