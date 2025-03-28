# calculator-aleksandrov-dd

## What has been done?

This is a simple C program that reads an arithmetic expression from standard input, parses it and evaluates the result. The program support the following operations on integers: `+`, `-`, `*`, `/` and parentheses (`(` and `)`). The result may be integer or float, depending on chosen mode.

### Features

- Supported operators: +, -, *, /, (, )
- Whitespace handling: Handles whitespace in the input expression
- Input validation: program handles nested parentheses and blocks invalid symbols or problematic constructs
- Output: The program outputs only the result without extra messages

## How to run/use it?

### Requirements
- gcc compiler
- Standard C library (libc)
- make
- Python 3 and pytest (for integration tests)

### Building and running
1. Clone the repository and run `make all` to build everything
2. Launch program:
   - Integer mode:
   	`make run-int`
   - Float mode:
   	`make run-float`

### Testing
- Unit tests:
	`make run-unit-test`
	
- Integration tests:
	`make run-integration-tests`

## How was it made?

### Technology
- Programming language: C (main code), C++ (unit tests), Python (integration tests).
- Instruments:
  - make (building automation)
  - clang-format (code formatting)
  - Google Test (unit tests)
  - pytest (integration tests)

### Sources
- Gpt
- habr.com
- cyberforum.ru

##  ДЗ 4
Дата начала выполнения работы: 11 марта 2025.

Администратор: Дорохов Антон Алексеевич
- В Yandex Tracker была создана очередь и сформированы задачи:
  - Создать файл server.py
  - Реализовать парсинг тела запросов
  - Реализовать базовую обработку POST  запросов
  - Реализовать интеграцию программы на C
  
Исполнитель: Александров Данила Дмитриевич
- Выполнение:
  - Задание: Создать файл server.py
  - Статус: Выполнено
  - Дата выполнения: [11.03.2025]
  - Описание: Файл server.py был успешно создан в соответствии с поставленной задачей.
 
  - Задание: Реализовать базовую обработку POST  запросов
  - Статус: Выполнено
  - Дата выполнения: [11.03.2025]
  - Описание: Реализована базовая обработка POST-запросов. При запросе сервер возвращает сообщение "request recieved" в формате json

12 марта 2025.

Администратор:
- Задача: Написать интеграционный тест.

13 марта 2025.

Администратор:
- Дата завершения задачи: [13.03.2025]
- Создание ноавх задач в Yandex Tracker:
  - Отредактировать сервер (Добавить проверку парсинга JSON в обработчик)
  - Закинуть интеграционный тест на github

Исполнитель: 
- Успешеное выполнение всех задач, поставленных администратором.

14 марта 2025.

Исполниетль:
- Задание: Реализовать парсинг тела запросов
  - Статус: Выполнено
  - Дата выполнения: [14.03.2025]
  - Описание: Реализован парсинг с новыми требованиями к запросу.
 
15 марта 2025.

Проведены необходимые тевсы.

18 марта 2025.

Исполнитель:
- Задание: Реализовать интеграцию программы на C
  - Статус: Выполнено
  - Дата выполнения: [18.03.2025]
  - Описание: Добавлена интеграция программы на С. Сервер возвращает вычисленное значение выражения.
 
23 марта 2025.

Администратор:
- Новое задание: Исправить тест - Неправильный вызов калькулятора, ввод и флаг float.

Исполнитель:
- Задание: Исправить тест
  - Статус: Выполнено
