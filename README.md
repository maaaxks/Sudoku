#################################################
#                   Sudoku                      #
#################################################

## Описание:
Данное консольное приложение позволяет:
1. Играть в судоку в ручном режиме с удобным управлением.
2. Решать судоку автоматически, используя пошаговую визуализацию.

Поддерживаются размеры сеток: **4x4**, **9x9**.

---

## Файлы проекта:
- **sudoku.c**: Главный файл программы, отвечающий за выбор режима работы.
- **handmode.h**: Логика и управление ручным режимом игры.
- **brutforce.h**: Реализация автоматического решения судоку.

---

## Функциональность:

### Ручной режим:
- **Управление:**
  - `W`, `A`, `S`, `D` — перемещение курсора по сетке.
  - `1-9` — ввод чисел в выбранную клетку.
  - `R` — сброс значения клетки.
  - `Q` — выход из ручного режима.
- Программа автоматически проверяет корректность ввода.

### Автоматический режим:
- Программа решает судоку самостоятельно.
- Каждое действие визуализируется: пустые клетки заполняются пошагово.
- Решение основывается на проверке уникальности чисел в строках, столбцах и блоках.

---

## Требования:
1. **Компилятор C** (например, GCC).
2. **Зависимости:**
   - `math.h` — для математических операций.
   - `conio.h` — обработка ввода в реальном времени (на Windows).
3. **ANSI escape-коды** — для цветного вывода (работает в большинстве современных терминалов).

---

## Установка и запуск:
1. **Сборка программы** (используя GCC):
```bash
gcc sudoku.c 
```
---

2. **Запуск программы:**
```bash
./a
```
## Автор:
Офицеров Максим
