#include <crow.h>
#include "../database/db_connection.h"

void setup_results_routes(crow::SimpleApp& app) {
    // Сохранить результаты
    app.route_dynamic("/results").methods("POST"_method)(
        [](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body || !body["test_id"] || !body["username"] || !body["score"]) {
                return crow::response(400, "Invalid JSON");
            }

            try {
                pqxx::connection& conn = DBConnection::getInstance();
                pqxx::work txn(conn);

                int test_id = body["test_id"].i();
                std::string username = body["username"].s();
                int score = body["score"].i();

                txn.exec0("INSERT INTO results (test_id, username, score) VALUES (" +
                          txn.quote(test_id) + ", " + txn.quote(username) + ", " + txn.quote(score) + ")");
                txn.commit();

                return crow::response(201, "Result saved");
            } catch (const std::exception& e) {
                return crow::response(500, e.what());
            }
        });
}
