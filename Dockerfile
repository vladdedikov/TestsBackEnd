# Базовый образ
FROM gcc:12

# Устанавливаем необходимые зависимости
RUN apt-get update && apt-get install -y cmake libpqxx-dev

# Устанавливаем рабочую директорию
WORKDIR /app

# Копируем файлы проекта
COPY . .

# Сборка проекта
RUN cmake . && make

# Экспонируем порт
EXPOSE 8080

# Запускаем приложение
CMD ["./StudentAPI"]
