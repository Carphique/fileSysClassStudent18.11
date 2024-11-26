#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// клас "Студент"
class Student {
private:
    string name; // ім'я
    int age; // вік
    double averageMark; // середній бал

public:
    // конструктор за замовчуванням
    Student() {
        name = "Monkey";
        age = 123;
        averageMark = 0.0;
    }

    // метод для запису інформації про студента у бінарний файл
    void saveToFile(const string& filename) const {
        ofstream outFile(filename, ios::binary);

        // записуємо ім'я
        size_t nameSize = name.size();
        outFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
        outFile.write(name.c_str(), nameSize);

        // записуємо вік
        outFile.write(reinterpret_cast<const char*>(&age), sizeof(age));

        // записуємо середній бал
        outFile.write(reinterpret_cast<const char*>(&averageMark), sizeof(averageMark));

        outFile.close();
        cout << "Info succesfully saved in file!!\n";
    }

    // метод для читання інформації про студента з бінарного файлу
    void loadFromFile(const string& filename) {
        ifstream inFile(filename, ios::binary);
        // зчитуємо ім'я
        size_t nameSize;
        inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        name.resize(nameSize);
        inFile.read(&name[0], nameSize);

        // зчитуємо вік
        inFile.read(reinterpret_cast<char*>(&age), sizeof(age));

        // зчитуємо середній бал
        inFile.read(reinterpret_cast<char*>(&averageMark), sizeof(averageMark));

        inFile.close();
        cout << "Info succesfully read.\n";
        cout_info(); // иводимо інформацію на консоль
    }

    // метод для виведення інформації про студента
    void cout_info() const {
        cout << "Name: " << name << "\n";
        cout << "Age: " << age << "\n";
        cout << "Average mark: " << averageMark << "\n";
    }

    // метод для введення інформації про студента
    void input() {
        cout << "Enter student's namw: ";
        cin >> name;
        cout << "Enter student's age: ";
        cin >> age;
        cout << "Enter average mark: ";
        cin >> averageMark;
    }
};

int main() {
    const string filename = "student.bin";

    Student student1;

    // введення інформації про студента
    student1.input();

    // збереження інформації у файл
    student1.saveToFile(filename);

    // читання інформації з файлу
    Student loadedStudent;
    loadedStudent.loadFromFile(filename);
}
