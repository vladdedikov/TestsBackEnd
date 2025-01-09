# Базовый образ
FROM gcc:12

# Установка необходимых пакетов
RUN apt-get update && apt-get install -y cmake libpqxx-dev git

# Скачиваем и устанавливаем Crow
RUN git clone https://github.com/CrowCpp/Crow.git /tmp/Crow && \
    mkdir -p /usr/local/include/crow && \
    cp -r /tmp/Crow/include/crow/* /usr/local/include/crow/ && \
    ls /usr/local/include/crow && \
    rm -rf /tmp/Crow

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
