#include "db_connection.h"

pqxx::connection& DBConnection::getInstance() {
    static pqxx::connection conn(
        "host=" + std::string(std::getenv("DB_HOST") ? std::getenv("DB_HOST") : "") +
        " port=" + std::string(std::getenv("DB_PORT") ? std::getenv("DB_PORT") : "5432") +
        " dbname=" + std::string(std::getenv("DB_NAME") ? std::getenv("DB_NAME") : "") +
        " user=" + std::string(std::getenv("DB_USER") ? std::getenv("DB_USER") : "") +
        " password=" + std::string(std::getenv("DB_PASSWORD") ? std::getenv("DB_PASSWORD") : "")
    );

    if (!conn.is_open()) {
        throw std::runtime_error("Failed to connect to database");
    }

    return conn;
}
