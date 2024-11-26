#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// ���� "�������"
class Student {
private:
    string name; // ��'�
    int age; // ��
    double averageMark; // ������� ���

public:
    // ����������� �� �������������
    Student() {
        name = "Monkey";
        age = 123;
        averageMark = 0.0;
    }

    // ����� ��� ������ ���������� ��� �������� � ������� ����
    void saveToFile(const string& filename) const {
        ofstream outFile(filename, ios::binary);

        // �������� ��'�
        size_t nameSize = name.size();
        outFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
        outFile.write(name.c_str(), nameSize);

        // �������� ��
        outFile.write(reinterpret_cast<const char*>(&age), sizeof(age));

        // �������� ������� ���
        outFile.write(reinterpret_cast<const char*>(&averageMark), sizeof(averageMark));

        outFile.close();
        cout << "Info succesfully saved in file!!\n";
    }

    // ����� ��� ������� ���������� ��� �������� � �������� �����
    void loadFromFile(const string& filename) {
        ifstream inFile(filename, ios::binary);
        // ������� ��'�
        size_t nameSize;
        inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
        name.resize(nameSize);
        inFile.read(&name[0], nameSize);

        // ������� ��
        inFile.read(reinterpret_cast<char*>(&age), sizeof(age));

        // ������� ������� ���
        inFile.read(reinterpret_cast<char*>(&averageMark), sizeof(averageMark));

        inFile.close();
        cout << "Info succesfully read.\n";
        cout_info(); // ������� ���������� �� �������
    }

    // ����� ��� ��������� ���������� ��� ��������
    void cout_info() const {
        cout << "Name: " << name << "\n";
        cout << "Age: " << age << "\n";
        cout << "Average mark: " << averageMark << "\n";
    }

    // ����� ��� �������� ���������� ��� ��������
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

    // �������� ���������� ��� ��������
    student1.input();

    // ���������� ���������� � ����
    student1.saveToFile(filename);

    // ������� ���������� � �����
    Student loadedStudent;
    loadedStudent.loadFromFile(filename);
}
