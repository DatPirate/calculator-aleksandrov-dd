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
  В Yandex Tracker была создана очередь и сформированы задачи:
  1)Создать файл server.py
  2)Реализовать парсинг тела запросов
  3)Реализовать базовую обработку POST  запросов
  4)Реализовать интеграцию программы на C
  
  Исполнитель: Александров Данила Дмитриевич
  Выполнение:
  Задание: Создать файл server.py
  Статус: Выполнено
  Дата выполнения: [11.05.2025]
  Описание: Файл server.py был успешно создан в соответствии с поставленной задачей.
