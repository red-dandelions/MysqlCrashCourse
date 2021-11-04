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

    print("16-1");
    res = sess.sql("select vend_id, prod_id, prod_price "
                   "from products "
                   "where prod_price <= 5 "
                   "union "
                   "select vend_id, prod_id, prod_price "
                   "from products "
                   "where vend_id in (1001, 1002)").execute();
    output(res);
    cout << endl;

    res = sess.sql("select vend_id, prod_id, prod_price "
                   "from products "
                   "where prod_price <= 5 "
                   "union all "
                   "select vend_id, prod_id, prod_price "
                   "from products "
                   "where vend_id in (1001, 1002)").execute();
    output(res);
    cout << endl;

    res = sess.sql("select vend_id, prod_id, prod_price "
                   "from products "
                   "where prod_price <= 5 "
                   "union "
                   "select vend_id, prod_id, prod_price "
                   "from products "
                   "where vend_id in (1001, 1002) "
                   "order by vend_id, prod_price").execute();
    output(res);
    cout << endl;

}
