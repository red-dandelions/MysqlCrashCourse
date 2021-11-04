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
    res = sess.sql("select cust_name, cust_contact "
                   "from customers as c, orders as o, orderitems as oi "
                   "where c.cust_id = o.cust_id "
                   "and oi.order_num = o.order_num "
                   "and prod_id = 'TNT2'").execute();
    output(res);
    cout << endl;

    print("16-2-1");
    res = sess.sql("select p1.prod_id, p1.prod_name "
                   "from products as p1, products as p2 "
                   "where p1.vend_id = p2.vend_id "
                   "and p2.prod_id = 'DTNTR'").execute();
    output(res);
    cout << endl;

    print("16-2-2");
    res = sess.sql("select c.*, o.order_num, o.order_date, oi.prod_id, "
                   "oi.quantity, oi.item_price "
                   "from customers as c, orders as o, orderitems as oi "
                   "where c.cust_id = o.cust_id "
                   "and oi.order_num = o.order_num "
                   "and prod_id = 'FB'").execute();
    output(res);
    cout << endl;

    print("16-2-3");
    res = sess.sql("select customers.cust_id, orders.order_num "
                   "from customers left outer join orders "
                   "on customers.cust_id = orders.cust_id").execute();
    output(res);
    cout << endl;

    print("16-3");
    res = sess.sql("select customers.cust_name, customers.cust_id, count(orders.order_num) as num_ord "
                   "from customers inner join orders "
                   "on customers.cust_id = orders.cust_id "
                   "group by customers.cust_id").execute();
    output(res);
    cout << endl;

    res = sess.sql("select customers.cust_name, customers.cust_id, count(orders.order_num) as num_ord "
                   "from customers left outer join orders "
                   "on customers.cust_id = orders.cust_id "
                   "group by customers.cust_id").execute();
    output(res);
    cout << endl;

}
