# Используем базовый образ с GCC и CMake
FROM gcc:12

# Устанавливаем необходимые пакеты
RUN apt-get update && apt-get install -y cmake libpqxx-dev

# Создаем рабочую директорию
WORKDIR /app

# Копируем все файлы в контейнер
COPY . .

# Сборка проекта
RUN cmake . && make

# Указываем порт для приложения
EXPOSE 8080

# Команда запуска
CMD ["./StudentAPI"]
