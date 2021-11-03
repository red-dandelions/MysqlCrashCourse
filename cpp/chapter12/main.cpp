#include <mysqlx/xdevapi.h>
#include <iostream>
#include "util.h"

using namespace std;
using namespace mysqlx;

const std::string USR       = "vanilla";
const std::string PWD       = "123456";
const std::string TABLENAME = "products";
const std::string TABLECUST = "customers";
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
    Table t1 = db.getTable(TABLECUST);
    print("connect to table: " + TABLECUST);
    Table t2 = db.getTable(TABLEITEM);
    print("connect to table: " + TABLEITEM);
    cout << endl;


    //avg()
    //count()
    //max()
    //min()
    //sum()
    //
    //12-1-1
    //select avg(prod_price) as avg_price
    //from products;
    print("12-1-1");
    cout << "sql: select avg(prod_price) as avg_price"
            "from products;" << endl;
    res = tb.select("avg(prod_price) as avg_price")
            .execute();
    output(res);
    cout << endl;

    //select avg(prod_price) as avg_price
    //from products
    //where vend_id = 1003;
    cout << "sql: select avg(prod_price) as avg_price"
            "from products "
            "where vend_id = 1003;" << endl;
    res = tb.select("avg(prod_price) as avg_price")
            .where("vend_id = :id")
            .bind("id", 1003)
            .execute();
    output(res);
    cout << endl;

    //12-1-2
    //select count(*) as num_cust
    //from customers;
    print("12-1-2");
    cout << "sql: select count(*) as num_cust"
            "from customers;" << endl;
    res = t1.select("count(*) as num_cust")
            .execute();
    output(res);
    cout << endl;

    //select count(cust_email) as num_cust
    //from customers;
    cout << "sql: select count(cust_email) as num_cust"
            "from customers;" << endl;
    res = t1.select("count(cust_email) as num_cust")
            .execute();
    output(res);
    cout << endl;

    //12-1-3
    //select max(prod_price) as max_price
    //from products;
    print("12-1-3");
    cout << "sql: select max(prod_price) as max_price"
            "from products;" << endl;
    res = tb.select("max(prod_price) as max_price")
            .execute();
    output(res);
    cout << endl;

    //12-1-4
    //select min(prod_price) as min_price
    //from products;
    print("12-1-4");
    cout << "sql: select min(prod_price) as min_price"
            "from products;" << endl;
    res = tb.select("min(prod_price) as min_price")
            .execute();
    output(res);
    cout << endl;

    //12-1-5
    //select sum(quantity) as item_ordered
    //from orderitems
    //where order_num = 20005;
    print("12-1-5");
    cout << "sql: select sum(quantity) as item_ordered"
            "from orderitems "
            "where order_num = 20005;" << endl;
    res = t2.select("sum(quantity) as item_ordered")
            .where("order_num = :num")
            .bind("num", 20005)
            .execute();
    output(res);
    cout << endl;

    //select sum(item_price * quantity) as total_price
    //from orderitems
    //where order_num = 20005;
    print("12-1-5");
    cout << "sql: select sum(item_price * quantity) as total_price"
            "from orderitems "
            "where order_num = 20005;" << endl;
    res = t2.select("sum(item_price * quantity) as total_price")
            .where("order_num = :num")
            .bind("num", 20005)
            .execute();
    output(res);
    cout << endl;

    //12-2
    //select avg(distinct prod_price) as avg_price
    //from products
    //where vend_id = 1003;
    print("12-2");
    cout << "sql: select avg(distinct prod_price) as avg_price"
            "from products "
            "where vend_id = 1003;" << endl;
    res = sess.sql("select avg(distinct prod_price) as avg_price "
                   "from products "
                   "where vend_id = 1003;").execute();
    output(res);
    cout << endl;

    //12-3
    //select count(*) as num_items,
    //       min(prod_price) as price_min,
    //       max(prod_price) as price_max,
    //       avg(prod_price) as price_avg
    //from products;
    print("12-3");
    cout << "sql: select count(*) as num_items, "
            "min(prod_price) as price_min, "
            "max(prod_price) as price_max, "
            "avg(prod_price) as price_avg "
            "from products;" << endl;
    res = tb.select("count(*) as num_items", "min(prod_price) as price_min",
                    "max(prod_price) as price_max", "avg(prod_price) as price_avg") 
            .execute();
    output(res);
    cout << endl;


}
