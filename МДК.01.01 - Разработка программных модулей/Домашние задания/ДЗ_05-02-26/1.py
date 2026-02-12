import psycopg2

conn = psycopg2.connect(
        dbname="lib",
        user="postgres",
        password="123",
        host="localhost",
        port=5432
)

cursor = conn.cursor()

print("Вывод записей:\n")

print("Жанры: ")
cursor.execute("SELECT name from categories")
result = cursor.fetchall()
print(result)

print("Авторы: ")
cursor.execute("SELECT name, description from authors")
result = cursor.fetchall()
for row in result:
    print(row)

print("Книги: ")
cursor.execute("SELECT name, description from books")
result = cursor.fetchall()
for row in result:
    print(row)

print("Добавление записей:\n")
print("Добавление записи (жанра):")
cursor.execute("""
    INSERT INTO categories(name) VALUES ('Классика')
    RETURNING id;
""")
category_id = cursor.fetchone()[0]
print(f"Создан жанр с ID: {category_id}")

print("Добавление записи (книги):")
cursor.execute("""
    INSERT INTO books (name, description, category_id, level) VALUES 
    ('Преступление и наказание', 'Роман Ф.М. Достоевского', %s, 'hard')
    RETURNING *;
""", (category_id,))
book_result = cursor.fetchone()
print(f"Добавлена книга: {book_result[1]}")

cursor.execute("""
    INSERT INTO authors (name, description) VALUES 
    ('Фёдор Достоевский', 'Русский писатель и мыслитель')
    RETURNING *;
""")
author_result = cursor.fetchone()
print(f"Добавлен автор: {author_result[1]}")

print("Обновление записей:\n")
print("Обновление записи (жанра):")
cursor.execute("""
    UPDATE categories
    SET name = 'Зарубежная классика'
    WHERE id = %s
    RETURNING id, name;
""", (category_id,))
updated_category = cursor.fetchone()
print(f"Обновлен жанр: ID={updated_category[0]}, Новое название = {updated_category[1]}")

print("Обновление записи (книги):")
cursor.execute("""
    UPDATE books
    SET name = 'Анна Каренина', description = 'Роман о любви и обществе', category_id = 1, level = 'medium'
    WHERE name = 'Преступление и наказание'
    RETURNING id, name, description, category_id, level;
""")
updated_book = cursor.fetchone()
if updated_book:
    print(f"Обновлена книга: {updated_book[1]}")
else:
    print("Книга 'Преступление и наказание' не найдена!")

print("Обновление записи (автора):")
cursor.execute("""
    UPDATE authors
    SET name = 'Антон Чехов', description = 'Русский писатель и драматург'
    WHERE name = 'Лев Толстой'
    RETURNING id, name, description;
""")
updated_author = cursor.fetchone()
if updated_author:
    print(f"Обновлен автор: {updated_author[1]}")
else:
    print("Автор 'Лев Толстой' не найден!")

print("Удаление записей:\n")


print("Удаление записей (книг) перед удалением жанра:")
cursor.execute("""
    DELETE FROM books
    WHERE category_id IN (SELECT id FROM categories WHERE name = 'Фантастика')
    RETURNING id, name;
""")
deleted_books = cursor.fetchall()
if deleted_books:
    for book in deleted_books:
        print(f"Удалена книга: {book[1]}")
else:
    print("Книги в жанре 'Фантастика' не найдены!")

print("Удаление записи (жанра):")
cursor.execute("""
    DELETE FROM categories
    WHERE name = 'Фантастика'
    RETURNING id, name;
""")
deleted_category = cursor.fetchone()
if deleted_category:
    print(f"Удален жанр: {deleted_category[1]}")
else:
    print("Жанр 'Фантастика' не найден!")

print("Удаление записи (книги):")
cursor.execute("""
    DELETE FROM books
    WHERE name = 'Война и мир'
    RETURNING id, name;
""")
deleted_book = cursor.fetchone()
if deleted_book:
    print(f"Удалена книга: {deleted_book[1]}")
else:
    print("Книга 'Война и мир' не найдена!")

print("Удаление записи (автора):")
cursor.execute("""
    DELETE FROM authors
    WHERE name = 'Агата Кристи'
    RETURNING id, name;
""")
deleted_author = cursor.fetchone()
if deleted_author:
    print(f"Удален автор: {deleted_author[1]}")
else:
    print("Автор 'Агата Кристи' не найден!")

conn.commit()
print("\nВсе изменения сохранены в БД")
cursor.close()
conn.close()
