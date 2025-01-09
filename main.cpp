#include <crow.h>
#include "routes/disciplines.h"
#include "routes/tests.h"
#include "routes/results.h"
#include "routes/questions.h"

int main() {
    crow::SimpleApp app;

    // Подключение маршрутов
    setup_disciplines_routes(app);
    setup_tests_routes(app);
    setup_results_routes(app);
    setup_questions_routes(app);  // Новый маршрут для вопросов

    app.port(8080).multithreaded().run();
    return 0;
}
