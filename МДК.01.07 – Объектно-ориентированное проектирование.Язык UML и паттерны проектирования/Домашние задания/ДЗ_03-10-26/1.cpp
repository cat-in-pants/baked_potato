#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

class Room {
public:
    string roomId;
    bool isAvailable;

    Room(string id, bool avail) {
        roomId = id;
        isAvailable = avail;
    }

    bool checkStatus() {
        return isAvailable;
    }

    void updateAvailability(bool status) {
        isAvailable = status;
    }
};

class Notification {
public:
    void send(const char* message) {
        cout << "Уведомление: " << message << endl;
    }
};

class Booking {
public:
    string status;
    string startDate;
    string endDate;

    void createBooking() {
        status = "Pending";
    }

    string getStatus() {
        return status;
    }
};

class BookingSystem {
public:
    Notification notify;

    bool checkAvailability(Room& room) {
        return room.checkStatus();
    }

    void confirmBooking(Booking& booking, Room& room) {
        booking.status = "Confirmed";
        room.updateAvailability(false);
        notify.send("Бронирование подтверждено");
    }

    void rejectBooking(Booking& booking) {
        booking.status = "Rejected";
        notify.send("Бронирование отклонено: номеров нет");
    }
};

class Client {
public:
    string name;

    Client(string n) {
        name = n;
    }

    void selectDates(string& start, string& end) {
        string input;
        cout << "Введите даты (начало-конец, например 12-25): ";
        cin >> input;

        size_t pos = input.find('-');
        if (pos != string::npos && pos > 0 && pos < input.length() - 1) {
            start = input.substr(0, pos);
            end = input.substr(pos + 1);
            cout << "Даты выбраны: " << start << " - " << end << endl;
        } else {
            start = "01";
            end = "02";
            cout << "Неверный формат. Даты установлены: " << start << " - " << end << endl;
        }
    }

    int selectRoom(int maxRooms) {
        int choice;
        cout << "Выберите номер (1-" << maxRooms << "): ";
        cin >> choice;
        return choice;
    }
};

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    vector<Room> rooms;
    rooms.push_back(Room("101", true));
    rooms.push_back(Room("102", true));
    rooms.push_back(Room("103", false));

    BookingSystem system;
    Client client("Клиент");

    int action;
    while (true) {
        cout << "\n1. Забронировать номер\n2. Показать номера\n3. Выход\nВыбор: ";
        cin >> action;

        if (action == 1) {
            string startDate, endDate;
            client.selectDates(startDate, endDate);
            int roomIdx = client.selectRoom(rooms.size()) - 1;

            if (roomIdx >= 0 && roomIdx < rooms.size()) {
                Booking booking;
                booking.startDate = startDate;
                booking.endDate = endDate;
                booking.createBooking();

                if (system.checkAvailability(rooms[roomIdx])) {
                    system.confirmBooking(booking, rooms[roomIdx]);
                } else {
                    system.rejectBooking(booking);
                }
                cout << "Статус: " << booking.getStatus() << endl;
                cout << "Период: " << booking.startDate << " - " << booking.endDate << endl;
            } else {
                cout << "Неверный номер." << endl;
            }
        } else if (action == 2) {
            for (int i = 0; i < rooms.size(); i++) {
                cout << "Номер " << rooms[i].roomId << " - " << (rooms[i].isAvailable ? "Свободен" : "Занят") << endl;
            }
        } else if (action == 3) {
            break;
        }
    }
    return 0;
}
