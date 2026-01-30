import sys

import json

from PyQt6.QtWidgets import (

    QApplication,

    QWidget,

    QLabel,

    QListWidget,

    QLineEdit,

    QVBoxLayout,

    QHBoxLayout,

    QComboBox,

    QPushButton,

    QMessageBox,

    QDialog,

    QFormLayout,

    QSpinBox,

    QTextEdit,

    QTableWidget,

    QTableWidgetItem,

    QHeaderView,

    QGroupBox,

    QDialogButtonBox

)

from PyQt6.QtCore import Qt, pyqtSignal

from PyQt6.QtGui import QCloseEvent



PATH = 'playlist.json'



class MusicService:

    def __init__(self):

        self.playlist = {}

        self.load_playlist()



    def load_playlist(self):

        try:

            with open(PATH, 'r', encoding='UTF-8') as file:

                self.playlist = json.load(file)

        except (FileNotFoundError, json.JSONDecodeError):

            self.playlist = {

                "Bohemian Rhapsody": {

                    "jenre": ["Рок", "Прогрессивный рок"],

                    "author": {

                        "name": "Queen",

                        "birth_year": 1970

                    }

                },

                "Shape of You": {

                    "jenre": ["Поп", "Тропический хаус"],

                    "author": {

                        "name": "Ed Sheeran",

                        "birth_year": 1991

                    }

                }

            }

            self.save_playlist()



    def save_playlist(self):

        with open(PATH, 'w', encoding='utf-8') as file:

            json.dump(self.playlist, file, ensure_ascii=False, indent=4)

    

    def get_tracks(self, genre_filter=None, search_filter=None):

        results = []

        for name, info in self.playlist.items():

            if genre_filter and genre_filter != "Все" and genre_filter not in info['jenre']:

                continue

            if search_filter and search_filter.lower() not in name.lower():

                continue

            results.append(name)

        return results

    

    def get_track_detail(self, name):

        if name in self.playlist:

            track = self.playlist[name]

            genres = ", ".join(track['jenre'])

            author = track['author']['name']

            birth_year = track['author']['birth_year']

            return f"Жанры: {genres}\nИсполнитель: {author}\nГод основания/рождения: {birth_year}"

        return "Трек не найден"

    

    def add_track(self, name, genres, author_name, author_birth_year):

        if name in self.playlist:

            return False

        self.playlist[name] = {

            "jenre": genres,

            "author": {

                "name": author_name,

                "birth_year": author_birth_year

            }

        }

        self.save_playlist()

        return True

    

    def edit_track(self, old_name, new_name, genres, author_name, author_birth_year):

        if old_name != new_name and new_name in self.playlist:

            return False, "Трек с таким названием уже существует"

        

        if old_name != new_name:

            del self.playlist[old_name]

        

        self.playlist[new_name] = {

            "jenre": genres,

            "author": {

                "name": author_name,

                "birth_year": author_birth_year

            }

        }

        self.save_playlist()

        return True, ""

    

    def delete_track(self, name):

        if name in self.playlist:

            del self.playlist[name]

            self.save_playlist()

            return True

        return False

    

    def get_all_genres(self):

        genres = set()

        for track in self.playlist.values():

            genres.update(track['jenre'])

        return sorted(list(genres))

    

    def get_statistics(self):

        stats = {

            "total_tracks": len(self.playlist),

            "genres": {},

            "oldest_artist": {"name": "", "year": 3000},

            "youngest_artist": {"name": "", "year": 0},

            "average_year": 0

        }

        

        total_years = 0

        artist_count = 0

        

        for track_name, track_info in self.playlist.items():

            for genre in track_info['jenre']:

                if genre in stats["genres"]:

                    stats["genres"][genre] += 1

                else:

                    stats["genres"][genre] = 1

            

            artist_name = track_info['author']['name']

            birth_year = track_info['author']['birth_year']

            

            if birth_year < stats["oldest_artist"]["year"]:

                stats["oldest_artist"] = {"name": artist_name, "year": birth_year}

            

            if birth_year > stats["youngest_artist"]["year"]:

                stats["youngest_artist"] = {"name": artist_name, "year": birth_year}

            

            total_years += birth_year

            artist_count += 1

        

        if artist_count > 0:

            stats["average_year"] = round(total_years / artist_count)

        

        return stats





class TrackDetailDialog(QDialog):

    def __init__(self, parent=None, track_name="", track_data=None):

        super().__init__(parent)

        self.setWindowTitle(f"Подробная информация: {track_name}")

        self.setModal(False)

        self.resize(400, 300)

        

        layout = QVBoxLayout()

        

        title_label = QLabel(f"<h2>{track_name}</h2>")

        title_label.setAlignment(Qt.AlignmentFlag.AlignCenter)

        layout.addWidget(title_label)

        

        info_group = QGroupBox("Информация о треке")

        info_layout = QFormLayout()

        

        info_layout.addRow("Название:", QLabel(track_name))

        

        genres = ", ".join(track_data['jenre']) if track_data else ""

        info_layout.addRow("Жанры:", QLabel(genres))

        

        author_name = track_data['author']['name'] if track_data else ""

        info_layout.addRow("Исполнитель:", QLabel(author_name))

        

        birth_year = str(track_data['author']['birth_year']) if track_data else ""

        info_layout.addRow("Год рождения/основания:", QLabel(birth_year))

        

        info_group.setLayout(info_layout)

        layout.addWidget(info_group)

        

        if track_data:

            extra_info = QTextEdit()

            extra_info.setReadOnly(True)

            extra_info.setPlainText(

                f"Количество жанров: {len(track_data['jenre'])}\n"

                f"Основной жанр: {track_data['jenre'][0] if track_data['jenre'] else 'Не указан'}"

            )

            layout.addWidget(QLabel("<b>Дополнительная информация:</b>"))

            layout.addWidget(extra_info)

        

        buttons = QDialogButtonBox(QDialogButtonBox.StandardButton.Close)

        buttons.rejected.connect(self.reject)

        layout.addWidget(buttons)

        

        self.setLayout(layout)





class StatisticsDialog(QDialog):

    def __init__(self, parent=None, statistics=None):

        super().__init__(parent)

        self.setWindowTitle("Статистика плейлиста")

        self.setModal(True)

        self.resize(500, 400)

        

        layout = QVBoxLayout()

        

        general_group = QGroupBox("Общая статистика")

        general_layout = QFormLayout()

        

        general_layout.addRow("Общее количество треков:", 

                             QLabel(str(statistics["total_tracks"])))

        general_layout.addRow("Самый старый исполнитель:", 

                             QLabel(f"{statistics['oldest_artist']['name']} ({statistics['oldest_artist']['year']})"))

        general_layout.addRow("Самый молодой исполнитель:", 

                             QLabel(f"{statistics['youngest_artist']['name']} ({statistics['youngest_artist']['year']})"))

        general_layout.addRow("Средний год рождения исполнителей:", 

                             QLabel(str(statistics["average_year"])))

        

        general_group.setLayout(general_layout)

        layout.addWidget(general_group)

        

        genres_group = QGroupBox("Распределение по жанрам")

        genres_layout = QVBoxLayout()

        

        if statistics["genres"]:

            table = QTableWidget(len(statistics["genres"]), 2)

            table.setHorizontalHeaderLabels(["Жанр", "Количество треков"])

            table.horizontalHeader().setSectionResizeMode(QHeaderView.ResizeMode.Stretch)

            

            for i, (genre, count) in enumerate(statistics["genres"].items()):

                table.setItem(i, 0, QTableWidgetItem(genre))

                table.setItem(i, 1, QTableWidgetItem(str(count)))

            

            genres_layout.addWidget(table)

        else:

            genres_layout.addWidget(QLabel("Нет данных о жанрах"))

        

        genres_group.setLayout(genres_layout)

        layout.addWidget(genres_group)

        

        buttons = QDialogButtonBox(QDialogButtonBox.StandardButton.Close)

        buttons.rejected.connect(self.reject)

        layout.addWidget(buttons)

        

        self.setLayout(layout)





class EditTrackDialog(QDialog):

    data_changed = pyqtSignal(dict)

    

    def __init__(self, parent=None, track_name="", track_data=None):

        super().__init__(parent)

        self.setWindowTitle("Редактировать трек")

        self.setModal(True)

        self.has_changes = False

        self.original_data = {

            'name': track_name,

            'genres': track_data['jenre'] if track_data else [],

            'author_name': track_data['author']['name'] if track_data else "",

            'author_birth_year': track_data['author']['birth_year'] if track_data else 1900

        }

        

        layout = QFormLayout()

        

        self.name_input = QLineEdit(track_name)

        self.name_input.textChanged.connect(self._on_data_changed)

        layout.addRow("Название трека:", self.name_input)

        

        genres_text = ", ".join(track_data['jenre']) if track_data else ""

        self.genres_input = QLineEdit(genres_text)

        self.genres_input.setPlaceholderText("Введите жанры через запятую")

        self.genres_input.textChanged.connect(self._on_data_changed)

        layout.addRow("Жанры:", self.genres_input)

        

        author_name = track_data['author']['name'] if track_data else ""

        self.author_input = QLineEdit(author_name)

        self.author_input.textChanged.connect(self._on_data_changed)

        layout.addRow("Исполнитель:", self.author_input)

        

        birth_year = track_data['author']['birth_year'] if track_data else 1900

        self.year_input = QSpinBox()

        self.year_input.setRange(1900, 2100)

        self.year_input.setValue(birth_year)

        self.year_input.valueChanged.connect(self._on_data_changed)

        layout.addRow("Год рождения/основания:", self.year_input)

        

        button_layout = QHBoxLayout()

        self.save_button = QPushButton("Сохранить")

        self.cancel_button = QPushButton("Отмена")

        self.save_button.clicked.connect(self.accept)

        self.cancel_button.clicked.connect(self.reject)

        button_layout.addWidget(self.save_button)

        button_layout.addWidget(self.cancel_button)

        

        layout.addRow(button_layout)

        self.setLayout(layout)

    

    def _on_data_changed(self):

        self.has_changes = True

    

    def closeEvent(self, event: QCloseEvent):

        if self.has_changes:

            reply = QMessageBox.question(

                self,

                'Подтверждение',

                'У вас есть несохраненные изменения. Вы уверены, что хотите закрыть окно?',

                QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No,

                QMessageBox.StandardButton.No

            )

            

            if reply == QMessageBox.StandardButton.No:

                event.ignore()

                return

        

        event.accept()

    

    def get_data(self):

        genres = [g.strip() for g in self.genres_input.text().split(',') if g.strip()]

        return {

            'name': self.name_input.text().strip(),

            'genres': genres,

            'author_name': self.author_input.text().strip(),

            'author_birth_year': self.year_input.value()

        }





class MusicWindow(QWidget):

    def __init__(self):

        super().__init__()

        self.setWindowTitle('Музыкальный плейлист')

        self.resize(500, 600)

        self.service = MusicService()

        self.current_selected_track = None

        self.setup_ui()

        self.refresh_list()



    def setup_ui(self):

        main_layout = QVBoxLayout()

        

        search_layout = QHBoxLayout()

        self.search_input = QLineEdit()

        self.search_input.setPlaceholderText('Поиск по названию')

        self.search_input.textChanged.connect(self.on_search_changed)

        search_layout.addWidget(QLabel("Поиск:"))

        search_layout.addWidget(self.search_input)

        main_layout.addLayout(search_layout)



        filter_layout = QHBoxLayout()

        self.genre_filter = QComboBox()

        self.genre_filter.addItem('Все')

        self.genre_filter.addItems(self.service.get_all_genres())

        self.genre_filter.currentTextChanged.connect(self.on_filter_changed)

        filter_layout.addWidget(QLabel('Жанр:'))

        filter_layout.addWidget(self.genre_filter)

        main_layout.addLayout(filter_layout)

        

        self.list_widget = QListWidget()

        self.list_widget.currentTextChanged.connect(self.track_selected)

        main_layout.addWidget(self.list_widget)



        detail_layout = QVBoxLayout()

        detail_layout.addWidget(QLabel("<b>Информация о выбранном треке:</b>"))

        

        self.detail_label = QLabel('Выберите трек')

        self.detail_label.setWordWrap(True)

        self.detail_label.setStyleSheet("padding: 10px; border: 1px solid #ccc; background-color: #f9f9f9;")

        detail_layout.addWidget(self.detail_label)

        

        detail_buttons_layout = QHBoxLayout()

        self.detail_button = QPushButton('Подробнее')

        self.detail_button.clicked.connect(self.show_track_details)

        self.detail_button.setEnabled(False)

        detail_buttons_layout.addWidget(self.detail_button)

        detail_buttons_layout.addStretch()

        detail_layout.addLayout(detail_buttons_layout)

        

        main_layout.addLayout(detail_layout)



        button_layout = QHBoxLayout()

        

        self.edit_button = QPushButton('Редактировать')

        self.edit_button.clicked.connect(self.edit_track)

        self.edit_button.setEnabled(False)

        

        self.delete_button = QPushButton('Удалить')

        self.delete_button.clicked.connect(self.delete_track)

        self.delete_button.setEnabled(False)

        

        self.stats_button = QPushButton('Статистика')

        self.stats_button.clicked.connect(self.show_statistics)

        

        button_layout.addWidget(self.edit_button)

        button_layout.addWidget(self.delete_button)

        button_layout.addStretch()

        button_layout.addWidget(self.stats_button)

        main_layout.addLayout(button_layout)



        add_group = QGroupBox("Добавить новый трек")

        add_layout = QVBoxLayout()

        

        self.new_name = QLineEdit()

        self.new_name.setPlaceholderText('Название трека')

        add_layout.addWidget(QLabel("Название:"))

        add_layout.addWidget(self.new_name)

        

        self.new_genres = QLineEdit()

        self.new_genres.setPlaceholderText('Жанры через запятую (например: Рок, Поп)')

        add_layout.addWidget(QLabel("Жанры:"))

        add_layout.addWidget(self.new_genres)

        

        self.new_author = QLineEdit()

        self.new_author.setPlaceholderText('Исполнитель')

        add_layout.addWidget(QLabel("Исполнитель:"))

        add_layout.addWidget(self.new_author)

        

        year_layout = QHBoxLayout()

        year_layout.addWidget(QLabel("Год рождения/основания:"))

        self.new_year = QSpinBox()

        self.new_year.setRange(1900, 2100)

        self.new_year.setValue(2000)

        year_layout.addWidget(self.new_year)

        year_layout.addStretch()

        add_layout.addLayout(year_layout)

        

        self.add_button = QPushButton('Добавить трек')

        self.add_button.clicked.connect(self.add_track)

        add_layout.addWidget(self.add_button)

        

        add_group.setLayout(add_layout)

        main_layout.addWidget(add_group)

        

        self.setLayout(main_layout)



    def on_search_changed(self):

        self.refresh_list()



    def on_filter_changed(self):

        self.refresh_list()



    def refresh_list(self):

        genre = self.genre_filter.currentText()

        if genre == 'Все':

            genre = None

        search = self.search_input.text()

        tracks = self.service.get_tracks(genre_filter=genre, search_filter=search)

        

        self.list_widget.clear()

        self.list_widget.addItems(tracks)

        

        self.detail_label.setText('Выберите трек')

        self.detail_button.setEnabled(False)

        self.edit_button.setEnabled(False)

        self.delete_button.setEnabled(False)

        self.current_selected_track = None



    def update_genre_filter(self):

        current_genre = self.genre_filter.currentText()

        self.genre_filter.blockSignals(True)

        self.genre_filter.clear()

        self.genre_filter.addItem('Все')

        self.genre_filter.addItems(self.service.get_all_genres())

        

        index = self.genre_filter.findText(current_genre)

        if index >= 0:

            self.genre_filter.setCurrentIndex(index)

        self.genre_filter.blockSignals(False)



    def track_selected(self, name):

        if name:

            self.current_selected_track = name

            detail = self.service.get_track_detail(name)

            self.detail_label.setText(detail)

            self.detail_button.setEnabled(True)

            self.edit_button.setEnabled(True)

            self.delete_button.setEnabled(True)

        else:

            self.current_selected_track = None

            self.detail_button.setEnabled(False)

            self.edit_button.setEnabled(False)

            self.delete_button.setEnabled(False)



    def show_track_details(self):

        if not self.current_selected_track:

            return

            

        track_data = self.service.playlist[self.current_selected_track]

        dialog = TrackDetailDialog(self, self.current_selected_track, track_data)

        dialog.show()



    def show_statistics(self):

        statistics = self.service.get_statistics()

        dialog = StatisticsDialog(self, statistics)

        dialog.exec()



    def add_track(self):

        name = self.new_name.text().strip()

        genres_text = self.new_genres.text().strip()

        author_name = self.new_author.text().strip()

        author_birth_year = self.new_year.value()



        if not name or not genres_text or not author_name:

            QMessageBox.warning(self, "Ошибка", "Заполните все поля")

            return



        genres = [g.strip() for g in genres_text.split(',') if g.strip()]

        if not genres:

            QMessageBox.warning(self, "Ошибка", "Введите хотя бы один жанр")

            return



        if self.service.add_track(name, genres, author_name, author_birth_year):

            QMessageBox.information(self, "Успех", f"Трек '{name}' был добавлен")

            self.new_name.clear()

            self.new_genres.clear()

            self.new_author.clear()

            self.refresh_list()

            self.update_genre_filter()

        else:

            QMessageBox.warning(self, 'Ошибка', f'Трек \'{name}\' уже существует')



    def edit_track(self):

        if not self.current_selected_track:

            return

            

        track_data = self.service.playlist[self.current_selected_track]

        dialog = EditTrackDialog(self, self.current_selected_track, track_data)

        

        if dialog.exec():

            data = dialog.get_data()

            

            if not data['name'] or not data['genres'] or not data['author_name']:

                QMessageBox.warning(self, "Ошибка", "Заполните все поля")

                return

            

            success, message = self.service.edit_track(

                self.current_selected_track,

                data['name'],

                data['genres'],

                data['author_name'],

                data['author_birth_year']

            )

            

            if success:

                QMessageBox.information(self, "Успех", f"Трек был обновлен")

                self.refresh_list()

                self.update_genre_filter()

            else:

                QMessageBox.warning(self, 'Ошибка', message)



    def delete_track(self):

        if not self.current_selected_track:

            return

            

        reply = QMessageBox.question(

            self, 

            'Подтверждение', 

            f'Вы уверены, что хотите удалить трек "{self.current_selected_track}"?',

            QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No

        )

        

        if reply == QMessageBox.StandardButton.Yes:

            if self.service.delete_track(self.current_selected_track):

                QMessageBox.information(self, "Успех", f"Трек был удален")

                self.refresh_list()

                self.update_genre_filter()

            else:

                QMessageBox.warning(self, 'Ошибка', 'Трек не найден')





if __name__ == "__main__":

    app = QApplication(sys.argv)

    window = MusicWindow()

    window.show()

    sys.exit(app.exec())
