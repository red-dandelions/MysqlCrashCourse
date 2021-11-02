MYSQL_CONCPP_DIR=/usr/include/mysql-cppconn
CPPFLAGS= -I $(MYSQL_CONCPP_DIR)
LDLIBS= -lmysqlcppconn8
CXXFLAGS= -std=c++11

main : main.o
	g++ main.o $(LDLIBS) -o main
main.o : main.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c main.cpp
clean:
	rm main main.o
