#include <mysqlx/xdevapi.h>
#include <iostream>
#include "util.h"

using namespace std;
using namespace mysqlx;

const std::string USR       = "vanilla";
const std::string PWD       = "123456";
const std::string HOST      = "localhost";
const std::string DATABASE  = "test";
const std::string TABLECUST = "customers";
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
    Schema db = sess.getSchema(DATABASE);
    print("connect to database: " + DATABASE);
    cout << endl;
    Table tb = db.getTable(TABLECUST);
    print("connect to table: " + TABLECUST);
    cout << endl;
    


    print("19");
    cout << "sql: insert into customers(cust_name, cust_address, cust_city, cust_state, "
            "cust_zip, cust_country) "
            "values('Pep E. LaPew', '100 Main Street', 'Los Angeles', 'CA', '90046', 'USA'), "
            "values('M.Martian', '42 Galaxy Way', 'New York', 'NY', '11213', 'USA')" << endl;
    auto ans = tb.insert("cust_name", "cust_address", "cust_city", "cust_state", "cust_zip", "cust_country")
            .values("Pep E. LaPew", "100 Main Street", "Los Angeles", "CA", "90046", "USA")
            .values("M.Martian", "42 Galaxy Way", "New York", "NY", "11213", "USA")
            .execute();
    cout << endl;

}
