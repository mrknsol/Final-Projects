#include <iostream>
#include <fstream>

using namespace std;

const int name_length = 150;
const int descryption_length = 250;

struct Task {
    char name[name_length];
    int priority;
    char description[descryption_length];
    int dateTime;
};

struct TaskList {
    Task* tasks;
    int count;
    int capacity;
};

void initializeTaskList(TaskList& taskList) {
    taskList.count = 0;
    taskList.capacity = 10;
    taskList.tasks = new Task[taskList.capacity];
}

void addTask(TaskList& taskList) {
    if (taskList.count >= taskList.capacity) {
        taskList.capacity *= 2;
        Task* newTasks = new Task[taskList.capacity];
        copy(taskList.tasks, taskList.tasks + taskList.count, newTasks);
        taskList.tasks = newTasks;
        delete[] taskList.tasks;

    }

    Task newTask{};
    cout << "Enter task name: ";
    cin.getline(newTask.name, name_length);
    cout << "Enter priority: ";
    cin >> newTask.priority;
    cin.ignore();
    cout << "Enter task description: ";
    cin.getline(newTask.description, descryption_length);
    cout << "Enter\n1.Day\n2.Weak\n3.Month\nChoose: ";
    cin >> newTask.dateTime;

    taskList.tasks[taskList.count] = newTask;
    taskList.count++;

    cout << "Task added successfully.\n";
}

void removeTask(TaskList& taskList, const char* taskName) {
    bool found = false;
    for (int i = 0; i < taskList.count; i++) {
        if (strcmp(taskList.tasks[i].name, taskName) == 0) {
            found = true;
            for (int j = i; j < taskList.count - 1; j++) {
                taskList.tasks[j] = taskList.tasks[j + 1];
            }
            taskList.count--;
            break;
        }
    }

    if (found) {
        cout << "Task removed\n";
    }
    else {
        cout << "Task not found.\n";
    }
}

void saveTasksToFile(const TaskList& taskList, const char* filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << taskList.count << '\n';
        for (int i = 0; i < taskList.count; i++) {
            file << taskList.tasks[i].name << '\n';
            file << taskList.tasks[i].priority << '\n';
            file << taskList.tasks[i].description << '\n';
            file << taskList.tasks[i].dateTime << '\n';
        }
        file.close();
        cout << "Tasks saved successfully.\n";
    }
    else {
        cout << "Unable to open the file for saving tasks.\n";
    }
}

void loadTasksFromFile(TaskList& taskList, const char* filename) {
    ifstream file(filename);
    if (file.is_open()) {
        int count;
        file >> count;
        file.ignore();

        delete[] taskList.tasks;
        taskList.count = count;
        taskList.capacity = count + 10;
        taskList.tasks = new Task[taskList.capacity];

        for (int i = 0; i < count; i++) {
            file.getline(taskList.tasks[i].name, name_length);
            file >> taskList.tasks[i].priority;
            file.ignore();
            file.getline(taskList.tasks[i].description, descryption_length);
            file >> taskList.tasks[i].dateTime;
        }
        file.close();
        cout << "Tasks loaded successfully" << endl;
    }
    else {
        cout << "Error!!\n";
    }
}

void displayTasks(const TaskList& taskList) {
    if (taskList.count == 0) {
        cout << "No any tasks\n";
        return;
    }
    int choose{};
    cout << "Enter\n1.For Daily Tasks\n2.For Weakly Tasks\n3.For Monthly Tasks\nChoose: ";
    cin >> choose;
    for (int i = 0; i < taskList.count; i++)
        if (taskList.tasks[i].dateTime == choose)
        {
            cout << "Task's Name: " << taskList.tasks[i].name << endl;
            cout << "Priority: " << taskList.tasks[i].priority << endl;
            cout << "Description: " << taskList.tasks[i].description << endl;
            cout << "Date and Time: " << taskList.tasks[i].dateTime << endl;
        }
}
void searchTasks(TaskList* tasklist)
{
    char search[1001]{};
    int len{};
    if (tasklist->count == NULL)
        return;

    int choice{};
    cout
        << "Enter choice: " << endl
        << "1. Search by name" << endl
        << "2. Search by Priority (1.if important -- 2.if unimportant)" << endl
        << "3. Search by description" << endl
        << "4. Search by date (1.if daily -- 2.if weakly -- 3.if monthly)" << endl
        << "Enter: ";
    cin >> choice;
    cin.ignore();
    cout << "Enter search word: ";
    cin.getline(search, 1000);

    while (search[len] != '\0')
        len++;
    int a{};
    for (size_t i = 0; i < tasklist->count; i++)
    {
        switch (choice)
        {
        case 1:

            for (size_t j = 0; j < len; j++)
            {
                if (tasklist[i].tasks->name[j] == search[j]) {
                    a++;
                }
            }
            break;
        case 2:
            for (size_t j = 0; j < len; j++)
            {
                if (tasklist[i].tasks->description[j] == search[j])
                    a++;
            }
            break;
        }
        if (len == a)
        {
            cout << "yeah" << endl;
        }
        else
        {
            cout << "No results" << endl;
        }
    }
}
int main() {
    TaskList taskList{};
    initializeTaskList(taskList);
    while (true) {
        cout << "1. Add Task\n";
        cout << "2. Remove Task\n";
        cout << "3. Load Tasks from File\n";
        cout << "4. Display Tasks\n";
        cout << "5. For Search\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 0:
            system("cls");
            cout << "Enter filename to save tasks: ";
            char saveFilename[name_length];
            cin.getline(saveFilename, name_length);
            saveTasksToFile(taskList, saveFilename);
            cout << "Bye Bye!!\n";
            delete[] taskList.tasks;
            return 0;
        case 1:
            system("cls");
            addTask(taskList);
            break;
        case 2:
            system("cls");
            cout << "Enter task's name to remove: ";
            char removeName[name_length];
            cin.getline(removeName, name_length);
            removeTask(taskList, removeName);
            break;
        case 3: {
            system("cls");
            cout << "Enter filename to load tasks: ";
            char loadFilename[name_length];
            cin.getline(loadFilename, name_length);
            loadTasksFromFile(taskList, loadFilename);
            break;
        }
        case 4:
            system("cls");
            displayTasks(taskList);
            break;
        case 5:
            system("cls");
            searchTasks(&taskList);
            break;
        default:
            cout << "Error!!\n";
            break;
        }
    }
}
