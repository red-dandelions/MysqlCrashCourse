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

    //8-1
    //select prod_id, prod_name
    //from products
    //where prod_name like 'jet%';
    print("8-1-1");
    cout << "sql: select prod_id, prod_name "
            "from products "
            "where prod_name like 'jet%';" << endl;
    res = tb.select("prod_id", "prod_name")
            .where("prod_name like :param")
            .bind("param", "jet%")
            .execute();
    output(res);
    cout << endl;


    //select prod_id, prod_name
    //from products
    //where prod_name like '%anvil%';
    print("8-1-2");
    cout << "sql: select prod_id, prod_name "
            "from products "
            "where prod_name like '%anvil%';" << endl;
    res = tb.select("prod_id", "prod_name")
            .where("prod_name like :param")
            .bind("param", "%anvil%")
            .execute();
    output(res);
    cout << endl;

    //select prod_name
    //from products
    //where prod_name like 's%e';
    print("8-1-3");
    cout << "sql: select prod_name "
            "from products "
            "where prod_name like 's%e';" << endl;
    res = tb.select("prod_name")
            .where("prod_name like :param")
            .bind("param", "s%e")
            .execute();
    output(res);
    cout << endl;

    //select prod_id, prod_name
    //from products
    //where prod_name like '_ ton anvil';
    print("8-1-4");
    cout << "sql: select prod_id, prod_name "
            "from products "
            "where prod_name like '_ ton anvil';" << endl;
    res = tb.select("prod_id", "prod_name")
            .where("prod_name like :param")
            .bind("param", "_ ton anvil")
            .execute();
    output(res);
    cout << endl;

    //select prod_id, prod_name
    //from products
    //where prod_name like '% ton anvil';
    print("8-1-4");
    cout << "sql: select prod_id, prod_name "
            "from products "
            "where prod_name like '% ton anvil';" << endl;
    res = tb.select("prod_id", "prod_name")
            .where("prod_name like :param")
            .bind("param", "% ton anvil")
            .execute();
    output(res);
    cout << endl;


}
