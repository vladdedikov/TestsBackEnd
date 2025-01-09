# **API для управления тестами студентов**

Данный проект предоставляет RESTful API для управления дисциплинами, тестами, вопросами, ответами и результатами тестов. Система предназначена для упрощения создания, управления и оценки тестов в образовательных учреждениях. API построен с использованием **Crow C++ Framework** и подключается к базе данных PostgreSQL.

---

## **Функциональность**

1. **Управление дисциплинами**:
   - Получение списка всех дисциплин.
   - Добавление новых дисциплин.

2. **Управление тестами**:
   - Получение тестов для конкретной дисциплины.
   - Добавление новых тестов для дисциплины.

3. **Управление вопросами и ответами**:
   - Получение списка вопросов и ответов для конкретного теста.
   - Добавление новых вопросов к тесту.

4. **Управление результатами тестов**:
   - Сохранение результатов прохождения тестов пользователями.
   - Получение результатов пользователя.

---

## **Технический стек**

- **Фреймворк:** Crow (C++)  
- **База данных:** PostgreSQL  
- **Среда развертывания:** Railway  
- **Формат данных:** JSON  

---

## **API Эндпоинты**

### **1. Управление дисциплинами**
- **GET /disciplines** – Получение списка всех дисциплин.  
  Пример ответа:
  ```json
  {
    "disciplines": [
      {
        "id": 1,
        "title": "Математика",
        "description": "Основы алгебры и анализа"
      }
    ]
  }
  ```

- **POST /disciplines** – Добавление новой дисциплины.  
  Пример запроса:
  ```bash
  curl -X POST https://testback-production-a036.up.railway.app/disciplines \
  -H "Content-Type: application/json" \
  -d '{
    "title": "Программирование",
    "description": "Основы C++"
  }'
  ```
  Пример ответа:
  ```text
  Discipline created
  ```

---

### **2. Управление тестами**
- **GET /tests/:discipline_id** – Получение тестов по дисциплине.  
  Пример запроса:
  ```bash
  curl -X GET https://testback-production-a036.up.railway.app/tests/1
  ```
  Пример ответа:
  ```json
  {
    "tests": [
      {
        "id": 1,
        "title": "Основы математического анализа"
      }
    ]
  }
  ```

- **POST /tests** – Добавление нового теста.  
  Пример запроса:
  ```bash
  curl -X POST https://testback-production-a036.up.railway.app/tests \
  -H "Content-Type: application/json" \
  -d '{
    "discipline_id": 1,
    "title": "Линейная алгебра"
  }'
  ```
  Пример ответа:
  ```text
  Test created
  ```

---

### **3. Управление вопросами и ответами**
- **GET /questions/:test_id** – Получение вопросов и ответов для теста.  
  Пример запроса:
  ```bash
  curl -X GET https://testback-production-a036.up.railway.app/questions/1
  ```
  Пример ответа:
  ```json
  {
    "questions": [
      {
        "id": 1,
        "content": "Чему равна производная функции y = x^2?",
        "answers": [
          {
            "id": 1,
            "content": "2x",
            "is_correct": true
          },
          {
            "id": 2,
            "content": "x^2",
            "is_correct": false
          }
        ]
      }
    ]
  }
  ```

---

### **4. Управление результатами тестов**
- **POST /results** – Сохранение результата прохождения теста.  
  Пример запроса:
  ```bash
  curl -X POST https://testback-production-a036.up.railway.app/results \
  -H "Content-Type: application/json" \
  -d '{
    "test_id": 1,
    "username": "student1",
    "score": 85
  }'
  ```
  Пример ответа:
  ```text
  Result saved
  ```

- **GET /results/:username** – Получение результатов пользователя.  
  Пример запроса:
  ```bash
  curl -X GET https://testback-production-a036.up.railway.app/results/student1
  ```
  Пример ответа:
  ```json
  {
    "results": [
      {
        "test_id": 1,
        "score": 85,
        "completed_at": "2025-01-09T12:00:00Z"
      }
    ]
  }
  ```

---

## **Примечания**
- Базовый URL: `https://testback-production-a036.up.railway.app`
- В случае ошибок возвращается сообщение об ошибке (например, `Invalid JSON` или `Internal Server Error`).
- Для POST-запросов данные должны передаваться в формате JSON.