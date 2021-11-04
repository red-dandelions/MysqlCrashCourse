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
    sess.sql("use test").execute();
    print("connect to database: " + DATABASE);
    cout << endl;

    print("14-2");
    res = sess.sql("select order_num "
                   "from orderitems "
                   "where prod_id = 'TNT2';").execute();
    output(res);
    cout << endl;

    res = sess.sql("select cust_id "
                   "from orders "
                   "where order_num in (20005, 20007)").execute();
    output(res);
    cout << endl;

    res = sess.sql("select cust_id "
                   "from orders "
                   "where order_num in (select order_num "
                   "from orderitems "
                   "where prod_id = 'TNT2')").execute();
    output(res);
    cout << endl;

    res = sess.sql("select cust_name, cust_contact "
                   "from customers "
                   "where cust_id in (10001, 10004)").execute();
    output(res);
    cout << endl;

    res = sess.sql("select cust_name, cust_contact "
                   "from customers "
                   "where cust_id in "
                   "(select cust_id "
                   "from orders "
                   "where order_num in "
                   "(select order_num "
                   "from orderitems "
                   "where prod_id = 'TNT2'))").execute();
    output(res);
    cout << endl;

    print("14-3");
    res = sess.sql("select count(*) as orders "
                   "from orders "
                   "where cust_id = 10001").execute();
    output(res);
    cout << endl;
    
    res = sess.sql("select cust_name, cust_state, "
                   "(select count(*) "
                   "from orders "
                   "where orders.cust_id = customers.cust_id) as orders "
                   "from customers "
                   "order by cust_name").execute();
    output(res);
    cout << endl;

}
