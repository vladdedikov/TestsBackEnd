#include <pqxx/pqxx>
#include <cstdlib>

class DBConnection {
public:
    static pqxx::connection& getInstance() {
        static pqxx::connection conn(
            "host=" + std::string(std::getenv("DB_HOST")) +
            " port=" + std::string(std::getenv("DB_PORT")) +
            " dbname=" + std::string(std::getenv("DB_NAME")) +
            " user=" + std::string(std::getenv("DB_USER")) +
            " password=" + std::string(std::getenv("DB_PASSWORD"))
        );
        return conn;
    }
};
