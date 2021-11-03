#include <mysqlx/xdevapi.h>
#include <iostream>
#include "util.h"

using namespace std;
using namespace mysqlx;

const std::string USR       = "vanilla";
const std::string PWD       = "123456";
const std::string TABLENAME = "vendors";
const std::string TABLECUST = "customers";
const std::string ORDER     = "orders";
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
    Table t2 = db.getTable(ORDER);
    print("connect to table: " + ORDER);
    cout << endl;


    //常见的文本处理函数
    //left()
    //length()
    //locate()
    //lower()
    //ltrim()
    //right()
    //rtrim()
    //soundex()
    //substring()
    //upper()
    //
    //11-2-1
    //select vend_name, upper(vend_name) as vend_name_upcase
    //from vendors
    //order by vend_name;
    print("11-2-1");
    cout << "sql: select vend_name, upper(vend_name) as vend_name_upcase "
            "from vendors "
            "order by vend_name;" << endl;
    res = tb.select("vend_name", "upper(vend_name) as vend_name_upcase")
            .orderBy("vend_name")
            .execute();
    output(res);
    cout << endl;

    //select cust_name, cust_contact
    //from customers
    //where cust_contact = 'Y. Lie';
    cout << "sql: select cust_name, cust_contact "
            "from customers "
            "where cust_contact = 'Y. Lie';" << endl;
    res = t1.select("cust_name", "cust_contact")
            .where("cust_contact = :contact")
            .bind("contact", "Y. Lie")
            .execute();
    output(res);
    cout << endl;

    //select cust_name, cust_contact
    //from customers
    //where soundex(cust_contact) = soundex('Y. Lie');
    cout << "sql: select cust_name, cust_contact "
            "from customers "
            "where soundex(cust_contact) = soundex('Y. Lie');" << endl;
    res = t1.select("cust_name", "cust_contact")
            .where("soundex(cust_contact) = soundex(:contact)")
            .bind("contact", "Y. Lie")
            .execute();
    output(res);
    cout << endl;

    //常见日期和时间处理函数
    //adddate()
    //addtime()
    //curdate()
    //curtime()
    //date()
    //datediff()
    //date_add()
    //date_format()
    //day()
    //dayofweek()
    //hour()
    //minute()
    //month()
    //now()
    //second()
    //time()
    //year()
    //
    //11-2-2
    //select cust_id, order_num
    //from orders
    //where order_date = '2005-09-01';
    print("11-2-2");
    cout << "sql: select cust_id, order_num "
            "from orders "
            "where order_date = '2005-09-01';" << endl;
    res = t2.select("cust_id", "order_num")
            .where("order_date = :date")
            .bind("date", "2005-09-01")
            .execute();
    output(res);
    cout << endl;

    //select cust_id, order_num
    //from orders
    //where date(order_date) = '2005-09-01';
    print("11-2-2");
    cout << "sql: select cust_id, order_num "
            "from orders "
            "where date(order_date) = '2005-09-01';" << endl;
    res = t2.select("cust_id", "order_num")
            .where("date(order_date) = :date")
            .bind("date", "2005-09-01")
            .execute();
    output(res);
    cout << endl;

    //select cust_id, order_num
    //from orders
    //where date(order_date) between '2005-09-01' and '2005-09-30';
    print("11-2-2");
    cout << "sql: select cust_id, order_num "
            "from orders "
            "where date(order_date) between '2005-09-01' and '2005-09-30';" << endl;
    res = t2.select("cust_id", "order_num")
            .where("date(order_date) between :date1 and :date2")
            .bind("date1", "2005-09-01").bind("date2", "2005-9-30")
            .execute();
    output(res);
    cout << endl;

    //select cust_id, order_num
    //from orders
    //where year(order_date) = 2005 and  month(order_date) = 9;
    print("11-2-2");
    cout << "sql: select cust_id, order_num "
            "from orders "
            "where year(order_date) = 2005 and  month(order_date) = 9;" << endl;
    res = t2.select("cust_id", "order_num")
            .where("year(order_date) = :date1 and month(order_date) = :date2")
            .bind("date1", 2005).bind("date2", 9)
            .execute();
    output(res);
    cout << endl;

    //常用数值处理函数
    //abs()
    //cos()
    //exp()
    //mod()
    //pi()
    //rand()
    //sin()
    //sqrt()
    //tan()

}
