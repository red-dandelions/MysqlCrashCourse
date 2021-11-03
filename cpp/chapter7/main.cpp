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

    //7-1-1
    //select prod_id, prod_price, prod_name
    //from products
    //where vend_id = 1003 and prod_price <= 10;
    print("7-1-1");
    cout << "sql: select prod_id, prod_price, prod_name "
            "from products "
            "where vend_id = 1003 and prod_price <= 10;" << endl;
    res = tb.select("prod_id","prod_price", "prod_name")
            .where("vend_id = :id and prod_price <= :price")
            .bind("id", 1003).bind("price", 10)
            .execute();
    output(res);
    cout << endl;

    //7-1-2
    //select prod_name, prod_price
    //from products
    //where vend_id = 1002 or vend_id = 1003;
    print("7-1-2");
    cout << "sql: select prod_name, prod_price "
            "from products "
            "where vend_id = 1002 or vend_id = 1003;" << endl;
    res = tb.select("prod_name", "prod_price")
            .where("vend_id = :id1 or vend_id = :id2")
            .bind("id1", 1002).bind("id2", 1003)
            .execute();
    output(res);
    cout << endl;

    //7-1-3
    //select prod_name, prod_price
    //from products
    //where (vend_id = 1002 or vend_id = 1003) and prod_price >= 10;
    print("7-1-3");
    cout << "sql: select prod_name, prod_price "
            "from products "
            "where (vend_id = 1002 or vend_id = 1003) and prod_price >= 10;" << endl;
    res = tb.select("prod_name", "prod_price")
            .where("(vend_id = :id1 or vend_id = :id2) and prod_price >= :price")
            .bind("id1", 1002).bind("id2", 1003).bind("price", 10)
            .execute();
    output(res);
    cout << endl;

    //7-2
    //select prod_name, prod_price
    //from products
    //where vend_id in (1002, 1003)
    //order by prod_name;
    print("7-2");
    cout << "sql: select prod_name, prod_price "
            "from products "
            "where vend_id in (1002, 1003) "
            "order by prod_name;" << endl;
    res = tb.select("prod_name", "prod_price")
            .where("vend_id in (:id1, :id2)")
            .orderBy("prod_name")
            .bind("id1", 1002).bind("id2", 1003)
            .execute();
    output(res);
    cout << endl;

    //7-3
    //select prod_name, prod_price
    //from products
    //where vend_id not in (1002, 1003)
    //order by prod_name;
    print("7-3");
    cout << "sql: select prod_name, prod_price "
            "from products "
            "where vend_id not in (1002, 1003) "
            "order by prod_name;" << endl;
    res = tb.select("prod_name", "prod_price")
            .where("vend_id not in (:id1, :id2)")
            .orderBy("prod_name")
            .bind("id1", 1002).bind("id2", 1003)
            .execute();
    output(res);
    cout << endl;

}
