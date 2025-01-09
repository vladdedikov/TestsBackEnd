#include "questions.h"
#include "../database/db_connection.h"

void setup_questions_routes(crow::SimpleApp& app) {
    // Получить список вопросов и ответов по тесту
    app.route_dynamic("/questions/<int>").methods("GET"_method)(
        [](const crow::request& req, int test_id) {
            try {
                pqxx::connection& conn = DBConnection::getInstance();
                pqxx::work txn(conn);

                pqxx::result result = txn.exec(
                    "SELECT q.id AS question_id, q.content AS question_content, "
                    "a.id AS answer_id, a.content AS answer_content, a.is_correct "
                    "FROM questions q "
                    "LEFT JOIN answers a ON q.id = a.question_id "
                    "WHERE q.test_id = " + txn.quote(test_id)
                );

                crow::json::wvalue response;
                response["questions"] = crow::json::wvalue::list();

                for (const auto& row : result) {
                    int question_id = row["question_id"].as<int>();
                    crow::json::wvalue question;

                    question["id"] = question_id;
                    question["content"] = row["question_content"].c_str();
                    question["answers"] = crow::json::wvalue::list();

                    crow::json::wvalue answer;
                    answer["id"] = row["answer_id"].as<int>();
                    answer["content"] = row["answer_content"].c_str();
                    answer["is_correct"] = row["is_correct"].as<bool>();

                    question["answers"][question["answers"].size()] = std::move(answer);
                    response["questions"][response["questions"].size()] = std::move(question);
                }

                return crow::response(200, response);
            } catch (const std::exception& e) {
                return crow::response(500, e.what());
            }
        });

    // Добавить новый вопрос
    app.route_dynamic("/questions").methods("POST"_method)(
        [](const crow::request& req) {
            auto body = crow::json::load(req.body);
            if (!body || !body["test_id"] || !body["content"]) {
                return crow::response(400, "Invalid JSON");
            }

            try {
                pqxx::connection& conn = DBConnection::getInstance();
                pqxx::work txn(conn);

                int test_id = body["test_id"].i();
                std::string content = body["content"].s();

                txn.exec0("INSERT INTO questions (test_id, content) VALUES (" +
                          txn.quote(test_id) + ", " + txn.quote(content) + ")");
                txn.commit();

                return crow::response(201, "Question created");
            } catch (const std::exception& e) {
                return crow::response(500, e.what());
            }
        });
}
