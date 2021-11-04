#include <mysqlx/xdevapi.h>
#include <iostream>
#include "util.h"

using namespace std;
using namespace mysqlx;

const std::string USR       = "vanilla";
const std::string PWD       = "123456";
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
    sess.sql("use " + DATABASE).execute();
    print("connect to database: " + DATABASE);
    cout << endl;

    print("15-2");
    res = sess.sql("select vend_name, prod_name, prod_price "
                   "from vendors, products "
                   "where vendors.vend_id = products.vend_id "
                   "order by vend_name, prod_name").execute();
    output(res);
    cout << endl;

    print("15-2-1");
    res = sess.sql("select vend_name, prod_name, prod_price "
                   "from vendors, products "
                   "order by vend_name, prod_name").execute();
    output(res);
    cout << endl;

    print("15-2-2");
    res = sess.sql("select vend_name, prod_name, prod_price "
                   "from vendors inner join products "
                   "on vendors.vend_id = products.vend_id").execute();
    output(res);
    cout << endl;

    print("15-2-3");
    res = sess.sql("select prod_name, vend_name, prod_price, quantity "
                   "from orderitems, products, vendors "
                   "where products.vend_id = vendors.vend_id "
                   "and orderitems.prod_id = products.prod_id "
                   "and order_num = 20005").execute();
    output(res);
    cout << endl;

}
