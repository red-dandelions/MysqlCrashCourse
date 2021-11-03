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

    //9-2-1
    //select prod_name
    //from products
    //where prod_name regexp '1000'
    //order by prod_name;
    print("9-2-1");
    cout << "sql: select prod_name "
            "from products "
            "where prod_name regexp '1000' "
            "order by prod_name;" << endl;
    res = tb.select("prod_name")
            .where("prod_name regexp :param")
            .orderBy("prod_name")
            .bind("param", "1000")
            .execute();
    output(res);
    cout << endl;

    //select prod_name
    //from products
    //where prod_name regexp '.000'
    //order by prod_name;
    cout << "sql: select prod_name "
            "from products "
            "where prod_name regexp '.000' "
            "order by prod_name;" << endl;
    res = tb.select("prod_name")
            .where("prod_name regexp :param")
            .orderBy("prod_name")
            .bind("param", ".000")
            .execute();
    output(res);
    cout << endl;

    //9-2-2
    //select prod_name
    //from products
    //where prod_name regexp '1000|2000'
    //order by prod_name;
    print("9-2-2");
    cout << "sql: select prod_name "
            "from products "
            "where prod_name regexp '1000|2000' "
            "order by prod_name;" << endl;
    res = tb.select("prod_name")
            .where("prod_name regexp :param")
            .orderBy("prod_name")
            .bind("param", "1000|2000")
            .execute();
    output(res);
    cout << endl;

    //9-2-3
    //select prod_name
    //from products
    //where prod_name regexp '[123] Ton'
    //order by prod_name;
    print("9-2-3");
    cout << "sql: select prod_name "
            "from products "
            "where prod_name regexp '[123] Ton' "
            "order by prod_name;" << endl;
    res = tb.select("prod_name")
            .where("prod_name regexp :param")
            .orderBy("prod_name")
            .bind("param", "[123] Ton")
            .execute();
    output(res);
    cout << endl;

    //select prod_name
    //from products
    //where prod_name regexp '1|2|3 Ton'
    //order by prod_name;
    cout << "sql: select prod_name "
            "from products "
            "where prod_name regexp '1|2|3 Ton' "
            "order by prod_name;" << endl;
    res = tb.select("prod_name")
            .where("prod_name regexp :param")
            .orderBy("prod_name")
            .bind("param", "1|2|3 Ton")
            .execute();
    output(res);
    cout << endl;

    //9-2-4
    //select prod_name
    //from products
    //where prod_name regexp '[1-5] Ton'
    //order by prod_name;
    print("9-2-4");
    cout << "sql: select prod_name "
            "from products "
            "where prod_name regexp '[1-5] Ton' "
            "order by prod_name;" << endl;
    res = tb.select("prod_name")
            .where("prod_name regexp :param")
            .orderBy("prod_name")
            .bind("param", "[1-5] Ton")
            .execute();
    output(res);
    cout << endl;

    //9-2-5
    //select vend_name
    //from vendors
    //where vend_name regexp '.'
    //order by vend_name;
    std::string name = "vendors";
    auto vt = db.getTable(name);
    print("9-2-5");
    cout << "sql: select vend_name "
            "from vendors "
            "where vend_name regexp '.' "
            "order by vend_name;" << endl;
    res = vt.select("vend_name")
            .where("vend_name regexp :param")
            .orderBy("vend_name")
            .bind("param", ".")
            .execute();
    output(res);
    cout << endl;

    //select vend_name
    //from vendors
    //where vend_name regexp '\\.'
    //order by vend_name;
    cout << "sql: select vend_name "
            "from vendors "
            "where vend_name regexp '\\.' "
            "order by vend_name;" << endl;
    res = vt.select("vend_name")
            .where("vend_name regexp :param")
            .orderBy("vend_name")
            .bind("param", "\\.")
            .execute();
    output(res);
    cout << endl;

    //9-2-7
    //select prod_name
    //from products
    //where prod_name regexp '\\([0-9] sticks?\\)'
    //order by prod_name;
    print("9-2-7");
    cout << "sql: select prod_name "
            "from products "
            "where prod_name regexp '\\([0-9] sticks?\\)' "
            "order by prod_name;" << endl;
    res = tb.select("prod_name")
            .where("prod_name regexp :param")
            .orderBy("prod_name")
            .bind("param", "\\([0-9] sticks?\\)")
            .execute();
    output(res);
    cout << endl;

    //select prod_name
    //from products
    //where prod_name regexp '[[:digit:]]{4}'
    //order by prod_name;
    //
    //equal [0-9][0-9][0-9][0-9]
    cout << "sql: select prod_name "
            "from products "
            "where prod_name regexp '[[:digit:]]{4}' "
            "order by prod_name;" << endl;
    res = tb.select("prod_name")
            .where("prod_name regexp :param")
            .orderBy("prod_name")
            .bind("param", "[[:digit:]]{4}")
            .execute();
    output(res);
    cout << endl;

    //9-2-8
    //select prod_name
    //from products
    //where prod_name regexp '^[0-9\\.]'
    //order by prod_name;
    print("9-2-8");
    cout << "sql: select prod_name "
            "from products "
            "where prod_name regexp '^[0-9\\.]' "
            "order by prod_name;" << endl;
    res = tb.select("prod_name")
            .where("prod_name regexp :param")
            .orderBy("prod_name")
            .bind("param", "^[0-9\\.]")
            .execute();
    output(res);
    cout << endl;


}
