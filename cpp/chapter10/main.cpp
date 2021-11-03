#include <mysqlx/xdevapi.h>
#include <iostream>
#include "util.h"

using namespace std;
using namespace mysqlx;

const std::string USR       = "vanilla";
const std::string PWD       = "123456";
const std::string TABLENAME = "vendors";
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
    Table t1 = db.getTable(TABLEITEM);
    print("connect to table: " + TABLEITEM);
    cout << endl;


    //10-2
    //select concat(vend_name, ' (', vend_country, ')')
    //from vendors
    //order by vend_name;
    print("10-2");
    cout << "sql: select concat(vend_name, ' (', vend_country, ')') "
            "from vendors "
            "order by vend_name;" << endl;
    res = tb.select("concat(vend_name, ' (', vend_country, ')')")
            .orderBy("vend_name")
            .execute();
    output(res);
    cout << endl;

    //select concat(rtrim(vend_name), ' (', rtrim(vend_country), ')')
    //from vendors
    //order by vend_name;
    print("10-2");
    cout << "sql: select concat(rtrim(vend_name), ' (', rtrim(vend_country), ')') "
            "from vendors "
            "order by vend_name;" << endl;
    res = tb.select("concat(rtrim(vend_name), ' (', rtrim(vend_country), ')')")
            .orderBy("vend_name")
            .execute();
    output(res);
    cout << endl;

    //select concat(rtrim(vend_name), ' (', rtrim(vend_country), ')') AS vend_title
    //from vendors
    //order by vend_name;
    print("10-2");
    cout << "sql: select concat(rtrim(vend_name), ' (', rtrim(vend_country), ')') AS vend_title "
            "from vendors "
            "order by vend_name;" << endl;
    res = tb.select("concat(rtrim(vend_name), ' (', rtrim(vend_country), ')') AS vend_title")
            .orderBy("vend_name")
            .execute();
    output(res);
    cout << endl;

    //10-3
    //select prod_id, quantity, item_price
    //from orderitems
    //where order_num = 20005;
    print("10-3");
    cout << "sql: select prod_id, quantity, item_price "
            "from orderitems "
            "where order_num = 20005;" << endl;
    res = t1.select("prod_id", "quantity", "item_price")
            .where("order_num = :num")
            .bind("num", 20005)
            .execute();
    output(res);
    cout << endl;

    //select prod_id, quantity, item_price, quantity * item_price as expanded_price
    //from orderitems
    //where order_num = 20005;
    print("10-3");
    cout << "sql: select prod_id, quantity, item_price, quantity * item_price as expanded_price "
            "from orderitems "
            "where order_num = 20005;" << endl;
    res = t1.select("prod_id", "quantity", "item_price", "quantity * item_price as expanded_price")
            .where("order_num = :num")
            .bind("num", 20005)
            .execute();
    output(res);
    cout << endl;


}
