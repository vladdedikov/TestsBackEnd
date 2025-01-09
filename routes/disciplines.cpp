#include <crow.h>
#include "../database/db_connection.cpp"

void setup_disciplines_routes(crow::SimpleApp& app) {
    // Получить список дисциплин
    app.route_dynamic("/disciplines").methods("GET"_method)(
        [](const crow::request& req) {
            try {
                pqxx::connection& conn = DBConnection::getInstance();
                pqxx::work txn(conn);

                pqxx::result result = txn.exec("SELECT id, title, description FROM disciplines");
                crow::json::wvalue response;
                response["disciplines"] = crow::json::wvalue::list();

                for (auto row : result) {
                    crow::json::wvalue discipline;
                    discipline["id"] = row["id"].as<int>();
                    discipline["title"] = row["title"].c_str();
                    discipline["description"] = row["description"].c_str();
                    response["disciplines"].push_back(discipline);
                }

                return crow::response(200, response);
            } catch (const std::exception& e) {
                return crow::response(500, e.what());
            }
        });

    // Добавить новую дисциплину
    app.route_dynamic("/disciplines").methods("POST"_method)(
        [](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body || !body["title"]) {
                return crow::response(400, "Invalid JSON");
            }

            try {
                pqxx::connection& conn = DBConnection::getInstance();
                pqxx::work txn(conn);

                std::string title = body["title"].s();
                std::string description = body["description"].s();

                txn.exec0("INSERT INTO disciplines (title, description) VALUES (" +
                          txn.quote(title) + ", " + txn.quote(description) + ")");
                txn.commit();

                return crow::response(201, "Discipline created");
            } catch (const std::exception& e) {
                return crow::response(500, e.what());
            }
        });
}
