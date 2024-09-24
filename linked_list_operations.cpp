#include <iostream>
#include <string>
using namespace std;


class Task {
    public:
    int taskID;          
    string description;  
    int priority;        
    Task* next;          

    Task(int id, string desc, int prio) : taskID(id), description(desc), priority(prio), next(nullptr) {}
};


class TaskList {
private:
    Task* head; 

public:
    
    TaskList() : head(nullptr) {}

    void addTask(int id, string desc, int prio) {
        Task* newTask = new Task(id, desc, prio);
    
        if (!head || head->priority < prio) {
            newTask->next = head;
            head = newTask;
        } else {
            Task* current = head;
           
            while (current->next && current->next->priority >= prio) {
                current = current->next;
            }
            newTask->next = current->next;
            current->next = newTask;
        }
        cout << "Task added successfully.\n";
    }

  
    void removeHighestPriorityTask() {
        if (!head) {
            cout << "No tasks to remove.\n";
            return;
        }
        Task* temp = head;
        head = head->next;
        cout << "Removed Task ID: " << temp->taskID << " (Highest Priority)\n";
        delete temp;
    }

  
    void removeTaskByID(int id) {
        if (!head) {
            cout << "No tasks to remove.\n";
            return;
        }
        if (head->taskID == id) {
            Task* temp = head;
            head = head->next;
            delete temp;
            cout << "Removed Task ID: " << id << "\n";
            return;
        }
        Task* current = head;
        while (current->next && current->next->taskID != id) {
            current = current->next;
        }
        if (!current->next) {
            cout << "Task ID not found.\n";
        } else {
            Task* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "Removed Task ID: " << id << "\n";
        }
    }

    
    void viewTasks() {
        if (!head) {
            cout << "No tasks to display.\n";
            return;
        }
        Task* current = head;
        cout << "Task List:\n";
        while (current) {
            cout << "ID: " << current->taskID << ", Description: " << current->description 
                 << ", Priority: " << current->priority << "\n";
            current = current->next;
        }
    }
};


class TaskManager {
private:
    TaskList taskList; 

public:
    
    void displayMenu() {
        int choice, id, priority;
        string desc;
        do {
            cout << "\nTask Management System\n";
            cout << "1. Add a new task\n";
            cout << "2. View all tasks\n";
            cout << "3. Remove the highest priority task\n";
            cout << "4. Remove a task by ID\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter Task ID: ";
                    cin >> id;
                    cin.ignore(); 
                    cout << "Enter Task Description: ";
                    getline(cin, desc);
                    cout << "Enter Priority Level: ";
                    cin >> priority;
                    taskList.addTask(id, desc, priority);
                    break;
                case 2:
                    taskList.viewTasks();
                    break;
                case 3:
                    taskList.removeHighestPriorityTask();
                    break;
                case 4:
                    cout << "Enter Task ID to remove: ";
                    cin >> id;
                    taskList.removeTaskByID(id);
                    break;
                case 5:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);
    }
};

int main() {
    TaskManager manager;
    manager.displayMenu();
    return 0;
}
