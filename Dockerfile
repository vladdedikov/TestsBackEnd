# Базовый образ
FROM gcc:12

# Установка необходимых пакетов
RUN apt-get update && apt-get install -y cmake libpqxx-dev git

# Копируем библиотеку Asio
COPY ./asio.hpp /usr/local/include/
COPY ./asio /usr/local/include/asio

# Копируем библиотеку Crow
COPY ./include /usr/local/include

# Устанавливаем рабочую директорию
WORKDIR /app

# Копируем файлы проекта
COPY . .

# Сборка проекта
RUN cmake . && make

# Экспонируем порт
EXPOSE 8080

# Запуск приложения
CMD ["./StudentAPI"]
