# Yadro TATLIN Data Services (Тестовое задание)

## Сборка проектa
После клонирования репозитория достаточно вызвать bash скрипт по сборке проекта
```bash
bash build.sh
```

## Запуск
И bash скрипт для запуска (без перекомпиляции)
### Шаблон
```bash
bash start.sh <INPUT_FILENAME> <OUTPUT_FILENAME>
```
### Пример
Для примера необходимо создать хотя бы `input.txt` в корне проекта и заполнить его какой-нибудь последовательность чисел (без переноса в конце файла)
```bash
bash start.sh input.txt output.txt
```

## Запуск юнит тестов
Тоже через bash скрип (с перекомпиляцией)
```bash
bash test_start.sh
```

## Пример изменяймого файла конфигураций
Локальный путь: `src/configs/config.txt`
<p>Пеедаваемые значения в миллисекундах (мс)</p>

```
read_delay = 100
write_delay = 200
rewind_delay = 500
shift_delay = 50
```
