#include <crow.h>
#include "routes/disciplines.cpp"
#include "routes/tests.cpp"
#include "routes/results.cpp"

int main() {
    crow::SimpleApp app;

    // Подключение маршрутов
    setup_disciplines_routes(app);
    setup_tests_routes(app);
    setup_results_routes(app);

    // Запуск сервера
    app.port(8080).multithreaded().run();
    return 0;
}
