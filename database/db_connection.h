#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <pqxx/pqxx>
#include <stdexcept>
#include <cstdlib>
#include <string>

class DBConnection {
public:
    // Получить единственный экземпляр соединения
    static pqxx::connection& getInstance();
};

#endif // DB_CONNECTION_H
