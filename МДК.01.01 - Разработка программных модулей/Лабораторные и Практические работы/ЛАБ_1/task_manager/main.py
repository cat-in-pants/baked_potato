import sys
sys.path.append('c:/бяка/разработка/task_manager/db')
from db.task_repository import TaskRepository

repo = TaskRepository()
tasks_df = repo.get_all()

def refresh_tasks():
    global tasks_df
    tasks_df = repo.get_all()
    print(tasks_df, "\n")

try:
    while(True):
        print("1 - Показать все задачи\n" \
        "2 - Добавить задачу\n" \
        "3 - Обновить статус\n" \
        "4 - Удалить задачу\n" \
        "5 - Фильтр по статусу\n" \
        "0 - Выход")
        action = int(input("выбор: "))

        try:
            if action == 1:
                print("\nзадачи:")
                refresh_tasks()

            if action == 2:
                title = input("\nназвание: ")
                description = input("описание: ")
                status = input("статус: ")
                priority = int(input("приоритет: "))
                repo.add(title, description, status, priority)
                refresh_tasks()

            if action == 3:
                id = int(input("\nайди задачи: "))
                status = input("новый статус: ")
                repo.update_status(id, status)
                refresh_tasks()

            if action == 4:
                id = int(input("\nайди задачи: "))
                repo.delete(id)
                refresh_tasks()

            if action == 5:
                status = input("\nстатус: ")
                repo.get_by_status(status)
                refresh_tasks()
            
            if action == 0:
                break

        except Exception as e:
            print("ошибка\n")

except Exception as e:
            print("ошибка меню\n")    
        
    
