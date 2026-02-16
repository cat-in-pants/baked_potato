import sys
sys.path.append('c:/бяка/c/task_manager/db')
from connection import get_connection
import pandas as pd
from sqlalchemy import text

class TaskRepository:
    def get_all(self):
        engine = get_connection()
        query = "SELECT * FROM app.tasks"
        df = pd.read_sql(query, engine)
        return df
    
    def delete(self, task_id):
        engine = get_connection()
        with engine.connect() as conn:
            conn.execute(text("DELETE FROM app.tasks WHERE id = :task_id"),
                         {"task_id": task_id})
            conn.commit()
            print(f"задача {task_id} удалена\n")
        
        tasks_cnt = len(self.get_all())
        if tasks_cnt == 0:
            self.reset_seq()

        return self.get_all()
    
    def add(self, title, description, status, priority):
        engine = get_connection()
        with engine.connect() as conn:
            conn.execute(text("""INSERT INTO app.tasks (title, description, status, priority)
                              VALUES (:title, :description, :status, :priority)"""),
                         {"title": title, "description": description, "status": status, "priority": priority})
            conn.commit()
        print(f"задача {title} добавлена\n")
        return self.get_all()
    
    def get_by_status(self, status):
        engine = get_connection()
        query = "SELECT * FROM app.tasks WHERE status = %s"
        df = pd.read_sql(query, engine, params=(status,))
        print(f"найденные по стат. задачи - {status}:")
        return df
    
    def update_status(self, task_id, new_status):
        engine = get_connection()
        with engine.connect() as conn:
            conn.execute(text("UPDATE app.tasks SET status = :new_status WHERE id = :task_id"),
                         {"new_status": new_status, "task_id": task_id})
            conn.commit()
        print(f"статус задачи {task_id} обновлен на: {new_status}\n")
        return self.get_all()
    
    def reset_seq(self):
        engine = get_connection()
        with engine.connect() as conn:
            conn.execute(
                text("SELECT setval('app.tasks_id_seq', 1, false)")
            )
            conn.commit()
        print("счётчик сброшен")
