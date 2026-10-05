#include <iostream>
#include <string>
using namespace std;

struct Patient {
    char name[50];
    int age;
    int priority;
};

struct Node {
    Patient patient;
    Node* next;
    Node* prev;
};

struct List {
    Node* head = nullptr;
    Node* tail = nullptr;
};

void AddInStart(List& list, Patient patient) {
    Node* node = new Node;
    node->patient = patient;
    node->prev = nullptr;
    node->next = list.head;
    if (list.head != nullptr) {
        list.head->prev = node;
    }
    list.head = node;
    if (list.tail == nullptr) {
        list.tail = node;
    }
}

void AddInEnd(List& list, Patient patient) {
    Node* node = new Node;
    node->patient = patient;
    node->next = nullptr;
    node->prev = list.tail;
    if (list.tail != nullptr) {
        list.tail->next = node;
    }
    list.tail = node;
    if (list.head == nullptr) {
        list.head = node;
    }
}

void DeleteFirst(List& list) {
    if (list.head == nullptr) {
        cout << "список пуст" << endl;
        return;
    }
    Node* node = list.head;
    list.head = node->next;
    if (list.head != nullptr) {
        list.head->prev = nullptr;
    }
    else {
        list.tail = nullptr;
    }
    delete node;
    cout << "первый пациент удалён" << endl;
}
void DeleteLast(List& list) {
    if (list.tail == nullptr) {
        cout << "список пуст" << endl;
        return;
    }
    Node* node = list.tail;
    list.tail = node->prev;
    if (list.tail != nullptr) {
        list.tail->next = nullptr;
    }
    else {
        list.head = nullptr;
    }
    delete node;
    cout << "последний пациент удалён" << endl;
}

void PrintForward(List& list) {
    Node* node = list.head;
    while (node != nullptr) {
        cout << node->patient.name << ", возраст " << node->patient.age << ", приоритет " << node->patient.priority << endl;
        node = node->next;
    }
}

void PrintBackward(List& list) {
    Node* node = list.tail;
    while (node != nullptr) {
        cout << node->patient.name << ", возраст " << node->patient.age << ", приоритет " << node->patient.priority << endl;
        node = node->prev;
    }
}
Node* FindByName(List& list, string name) {
    Node* node = list.head;
    while (node != nullptr) {
        if (name == node->patient.name) {
            return node;
        }
        node = node->next;
    }
    return nullptr;
}

void DeleteNode(List& list, Node* node) {
    if (node->prev != nullptr) {
        node->prev->next = node->next;
    }
    else {
        list.head = node->next;
    }
    if (node->next != nullptr) {
        node->next->prev = node->prev;
    }
    else {
        list.tail = node->prev;
    }
    delete node;
}
void ClearList(List& list) {
    Node* node = list.head;
    while (node != nullptr) {
        Node* next = node->next;
        delete node;
        node = next;
    }
    list.head = nullptr;
    list.tail = nullptr;
}
Node* FindMaxPriority(List& list) {
    if (list.head == nullptr) {
        return nullptr;
    }
    Node* best = list.head;
    Node* node = list.head->next;
    while (node != nullptr) {
        if (node->patient.priority > best->patient.priority) {
            best = node;
        }
        node = node->next;
    }
    return best;
}
void DeleteYoungerThan(List& list, int age) {
    Node* node = list.head;
    while (node != nullptr) {
        Node* next = node->next;
        if (node->patient.age < age) {
            DeleteNode(list, node);
        }
        node = next;
    }
}
void MoveMaxPriorityToStart(List& list) {
    Node* best = FindMaxPriority(list);
    if (best == nullptr || best == list.head) {
        return;
    }
    best->prev->next = best->next;
    if (best->next != nullptr) {
        best->next->prev = best->prev;
    }
    else {
        list.tail = best->prev;
    }
    best->prev = nullptr;
    best->next = list.head;
    list.head->prev = best;
    list.head = best;
}
Patient ReadPatient() {
    Patient patient;
    cout << "Имя: ";
    cin.getline(patient.name, 50);
    cout << "Возраст: ";
    cin >> patient.age;
    cout << "Приоритет: ";
    cin >> patient.priority;
    cin.ignore();
    return patient;
}


int main()
{
    List list;
    int choice = -1;
    while (choice != 13) {
        cout << "1 - добавить пациента в начало" << endl;
        cout << "2 - добавить пациента в конец" << endl;
        cout << "3 - удалить первого пациента" << endl;
        cout << "4 - удалить последнего пациента" << endl;
        cout << "5 - вывести список от начала к концу" << endl;
        cout << "6 - вывести список от конца к началу" << endl;
        cout << "7 - найти пациента по имени" << endl;
        cout << "8 - удалить найденного пациента" << endl;
        cout << "9 - очистить список" << endl;
        cout << "10 - пациент с максимальным приоритетом" << endl;
        cout << "11 - удалить пациентов младше заданного возраста" << endl;
        cout << "12 - переместить пациента с максимальным приоритетом в начало" << endl;
        cout << "13 - выход" << endl;
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: {
            Patient patient = ReadPatient();
            AddInStart(list, patient);
            cout << "пациент добавлен в начало" << endl;
            break;
        }
        case 2: {
            Patient patient = ReadPatient();
            AddInEnd(list, patient);
            cout << "пациент добавлен в конец" << endl;
            break;
        }
        case 3: {
            DeleteFirst(list);
            break;
        }
        case 4: {
            DeleteLast(list);
            break;
        }
        case 5: {
            PrintForward(list);
            break;
        }
        case 6: {
            PrintBackward(list);
            break;
        }
        case 7: {
            string name;
            cout << "введите имя: ";
            getline(cin, name);
            Node* node = FindByName(list, name);
            if (node == nullptr) {
                cout << "пациент не найден" << endl;
            }
            else {
                cout << node->patient.name << ", возраст " << node->patient.age << ", приоритет " << node->patient.priority << endl;
            }
            break;
        }
        case 8: {
            string name;
            cout << "введите имя: ";
            getline(cin, name);
            Node* node = FindByName(list, name);
            if (node == nullptr) {
                cout << "пациент не найден" << endl;
            }
            else {
                DeleteNode(list, node);
                cout << "пациент удален" << endl;
            }
            break;
        }
        case 9: {
            ClearList(list);
            cout << "список очищен" << endl;
            break;
        }
        case 10: {
            Node* node = FindMaxPriority(list);
            if (node == nullptr) {
                cout << "список пуст" << endl;
            }
            else {
                cout << node->patient.name << ", приоритет " << node->patient.priority << endl;
            }
            break;
        }
        case 11: {
            int age;
            cout << "введите возраст: ";
            cin >> age;
            DeleteYoungerThan(list, age);
            cout << "пациенты младше " << age << " лет удалены" << endl;
            break;
        }
        case 12: {
            MoveMaxPriorityToStart(list);
            cout << "пациент с максимальным приоритетом теперь в начале" << endl;
            break;
        }
        case 13: {
            cout << "выход" << endl;
            break;
        }
        default: {
            cout << "такого пункта нет" << endl;
        }
        }
    }

    ClearList(list);
}