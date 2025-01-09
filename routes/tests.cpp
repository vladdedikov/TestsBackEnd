#include <crow.h>
#include "../database/db_connection.h"

void setup_tests_routes(crow::SimpleApp& app) {
    // Получить список тестов по дисциплине
    app.route_dynamic("/tests/<int>").methods("GET"_method)(
        [](const crow::request& req, int discipline_id) {
            try {
                pqxx::connection& conn = DBConnection::getInstance();
                pqxx::work txn(conn);

                pqxx::result result = txn.exec("SELECT id, title FROM tests WHERE discipline_id = " + txn.quote(discipline_id));
                crow::json::wvalue response;
                response["tests"] = crow::json::wvalue::list();

                for (auto row : result) {
                    crow::json::wvalue test;
                    test["id"] = row["id"].as<int>();
                    test["title"] = row["title"].c_str();
response["tests"][response["tests"].size()] = std::move(test);
                }

                return crow::response(200, response);
            } catch (const std::exception& e) {
                return crow::response(500, e.what());
            }
        });

    // Добавить новый тест
    app.route_dynamic("/tests").methods("POST"_method)(
        [](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body || !body["discipline_id"] || !body["title"]) {
                return crow::response(400, "Invalid JSON");
            }

            try {
                pqxx::connection& conn = DBConnection::getInstance();
                pqxx::work txn(conn);

                int discipline_id = body["discipline_id"].i();
                std::string title = body["title"].s();

                txn.exec0("INSERT INTO tests (discipline_id, title) VALUES (" +
                          txn.quote(discipline_id) + ", " + txn.quote(title) + ")");
                txn.commit();

                return crow::response(201, "Test created");
            } catch (const std::exception& e) {
                return crow::response(500, e.what());
            }
        });
}
