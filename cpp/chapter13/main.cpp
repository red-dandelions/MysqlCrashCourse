#include <mysqlx/xdevapi.h>
#include <iostream>
#include "util.h"

using namespace std;
using namespace mysqlx;

const std::string USR       = "vanilla";
const std::string PWD       = "123456";
const std::string TABLENAME = "products";
const std::string TABLEOR   = "orders";
const std::string TABLEITEM = "orderitems";
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
    Table t1 = db.getTable(TABLEOR);
    print("connect to table: " + TABLEOR);
    Table t2 = db.getTable(TABLEITEM);
    print("connect to table: " + TABLEITEM);
    cout << endl;

    //13-2
    //select vend_id, count(*) as num_prods
    //from products
    //group by vend_id;
    print("13-2");
    cout << "sql: select vend_id, count(*) as num_prods "
            "from products "
            "group by vend_id;" << endl;
    res = tb.select("vend_id", "count(*) as num_prods")
            .groupBy("vend_id")
            .execute();
    output(res);
    cout << endl;
    
    //13-3
    //select cust_id, count(*) as orders
    //from orders
    //group by cust_id
    //having count(*) >= 2;
    print("13-3");
    cout << "sql: select cust_id, count(*) as orders "
            "from orders "
            "group by cust_id "
            "having count(*) >= 2;" << endl;
    res = t1.select("cust_id", "count(*) as orders")
            .groupBy("cust_id")
            .having("count(*) >= 2")
            .execute();
    output(res);
    cout << endl;

    //select vend_id, count(*) as num_prods
    //from products
    //where prod_price >= 10
    //group by vend_id
    //having count(*) >= 2;
    cout << "sql: select vend_id, count(*) as num_prods "
            "from products "
            "where prod_price >= 10 "
            "group by cust_id "
            "having count(*) >= 2;" << endl;
    res = tb.select("vend_id", "count(*) as num_prods")
            .where("prod_price >= :price")
            .groupBy("vend_id")
            .having("count(*) >= 2")
            .bind("price", 10)
            .execute();
    output(res);
    cout << endl;

    //select vend_id, count(*) as num_prods
    //from products
    //group by vend_id
    //having count(*) >= 2;
    cout << "sql: select vend_id, count(*) as num_prods "
            "from products "
            "group by cust_id "
            "having count(*) >= 2;" << endl;
    res = tb.select("vend_id", "count(*) as num_prods")
            .groupBy("vend_id")
            .having("count(*) >= 2")
            .execute();
    output(res);
    cout << endl;

    //13-4
    //select order_num, sum(quantity * item_price) as ordertotal
    //from orderitems
    //group by order_num
    //having sum(quantity * item_price) >= 50;
    print("13-4");
    cout << "sql: select order_num, sum(quantity * item_price) as ordertotal "
            "from orderitems "
            "group by order_num "
            "having sum(quantity * item_price) >= 50;" << endl;
    res = t2.select("order_num", "sum(quantity * item_price) as ordertotal")
            .groupBy("order_num")
            .having("sum(quantity * item_price) >= 50")
            .execute();
    output(res);
    cout << endl;

    //select order_num, sum(quantity * item_price) as ordertotal
    //from orderitems
    //group by order_num
    //having sum(quantity * item_price) >= 50
    //order by ordertotal;
    print("13-4");
    cout << "sql: select order_num, sum(quantity * item_price) as ordertotal "
            "from orderitems "
            "group by order_num "
            "having sum(quantity * item_price) >= 50 " 
            "order by ordertotal;" << endl;
    res = t2.select("order_num", "sum(quantity * item_price) as ordertotal")
            .groupBy("order_num")
            .having("sum(quantity * item_price) >= 50")
            .orderBy("ordertotal")
            .execute();
    output(res);
    cout << endl;


}
