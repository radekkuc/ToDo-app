#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <memory>
#include <stdexcept>

using namespace std;

// Klasa Task reprezentuje pojedyncze zadanie w ToDo List.
class Task {
private:
    string description;
    bool completed;

public:
    // Konstruktor inicjujący nowe zadanie z opisem.
    Task(string desc) : description(desc), completed(false) {}

    // Metoda zwracająca opis zadania.
    string getDescription() const {
        return description;
    }

    // Metoda sprawdzająca stan ukończenia zadania.
    bool isCompleted() const {
        return completed;
    }

    // Metoda oznaczająca zadanie jako ukończone.
    void markAsCompleted() {
        completed = true;
    }
};

// Klasa ToDoList zarządza listą zadań w ToDo List.
class ToDoList {
private:
    vector<shared_ptr<Task>> tasks;
    string filename;

public:
    // Konstruktor inicjujący listę zadań na podstawie pliku.
    ToDoList(string filename) : filename(filename) {
        loadTasksFromFile();
    }

    // Dodaje nowe zadanie do listy.
    void addTask(const string& description) {
        if (description.empty()) {
            throw invalid_argument("Task description cannot be empty.");
        }
        tasks.push_back(make_shared<Task>(description));
        saveTasksToFile();
    }

    // Oznacza wybrane zadanie jako ukończone.
    void markTaskAsCompleted(size_t index) {
        if (index < tasks.size()) {
            tasks[index]->markAsCompleted();
            saveTasksToFile();
        }
        else {
            throw out_of_range("Invalid task number.");
        }
    }

    // Wyświetla aktualną listę zadań.
    void displayTasks() const {
        cout << "Tasks:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". ";
            if (tasks[i]->isCompleted()) {
                cout << "[X] ";
            }
            else {
                cout << "[ ] ";
            }
            cout << tasks[i]->getDescription() << endl;
        }
    }

    // Wczytuje zadania z pliku.
    void loadTasksFromFile() {
        try {
            ifstream file(filename);
            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    addTask(line);
                }
                file.close();
            }
        }
        catch (const exception& e) {
            cerr << "Exception loading tasks from file: " << e.what() << endl;
        }
    }

    // Zapisuje zadania do pliku.
    void saveTasksToFile() const {
        try {
            ofstream file(filename);
            if (file.is_open()) {
                for (const auto& task : tasks) {
                    file << task->getDescription() << "\n";
                }
                file.close();
            }
        }
        catch (const exception& e) {
            cerr << "Exception saving tasks to file: " << e.what() << endl;
        }
    }
};


int main() {
    ToDoList todoList("tasks.txt");
    int choice;

    do {
        cout << "\n--- ToDo List ---\n";
        cout << "1. Add Task\n";
        cout << "2. Mark Task as Completed\n";
        cout << "3. Display Tasks\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        string input;
        getline(cin, input);

        try {
            if (input.size() != 1 || !isdigit(input[0])) {
                throw invalid_argument("Invalid choice. Please enter a valid number.");
            }

            choice = stoi(input);

            switch (choice) {
            case 1: {
                cout << "Enter task description: ";
                string description;
                getline(cin, description);
                todoList.addTask(description);
                break;
            }
            case 2: {
                todoList.displayTasks();
                cout << "Enter task number to mark as completed: ";
                string taskIndex;
                getline(cin, taskIndex);
                if (taskIndex.size() == 1 && isdigit(taskIndex[0])) {
                    size_t index = stoi(taskIndex);
                    todoList.markTaskAsCompleted(index - 1); // Adjust index for 0-based vector
                }
                else {
                    throw invalid_argument("Invalid input. Please enter a valid task number.");
                }
                break;
            }
            case 3:
                todoList.displayTasks();
                break;
            case 4:
                cout << "Exiting ToDo List application...\n";
                break;
            default:
                throw invalid_argument("Invalid choice. Please enter a valid number.");
            }
        }
        catch (const exception& e) {
            cerr << "Exception occurred: " << e.what() << endl;
        }
    } while (choice != 4);

    return 0;
}
