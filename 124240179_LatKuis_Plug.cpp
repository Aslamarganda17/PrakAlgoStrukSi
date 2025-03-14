#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

const int MAX_TASKS = 100;

struct Task
{
    string name;
    string category;
    string deadline; // format: DD/MM/YYYY
    string status;   // default: "belum selesai"
};

// fungsi untuk menyimpan tugas ke dalam file
void saveTasks(Task *tasks, int taskCount)
{
    ofstream file("WorkTracker.dat");
    for (int i = 0; i < taskCount; ++i)
    {
        file << tasks[i].name << ";" << tasks[i].category << ";" << tasks[i].deadline << ";" << tasks[i].status << endl;
    }
    file.close();
}

// fungsi untuk membaca tugas dari file
int loadTasks(Task *tasks)
{
    int taskCount = 0;
    ifstream file("WorkTracker.dat");
    string line;
    while (getline(file, line) && taskCount < MAX_TASKS)
    {
        size_t pos = 0;
        Task task;
        pos = line.find(";");
        task.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(";");
        task.category = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(";");
        task.deadline = line.substr(0, pos);
        line.erase(0, pos + 1);

        task.status = line;
        tasks[taskCount++] = task;
    }
    file.close();
    return taskCount;
}
// untuk mengubah string deadline menjadi time_t
time_t convertToTimeT(const string &deadline)
{
    int day, month, year;
    sscanf(deadline.c_str(), "%d/%d/%d", &day, &month, &year);
    tm taskDeadline = {0};
    taskDeadline.tm_mday = day;
    taskDeadline.tm_mon = month - 1;
    taskDeadline.tm_year = year - 1900;
    return mktime(&taskDeadline);
}
// untuk mengurutkan tugas menggunakan Bubble Sort
void bubbleSort(Task *tasks, int taskCount)
{
    for (int i = 0; i < taskCount - 1; i++)
    {
        for (int j = 0; j < taskCount - i - 1; j++)
        {
            if (convertToTimeT(tasks[j].deadline) > convertToTimeT(tasks[j + 1].deadline))
            {
                swap(tasks[j], tasks[j + 1]);
            }
        }
    }
}
// untuk mengurutkan tugas menggunakan Quick Sort
void quickSort(Task *tasks, int low, int high)
{
    if (low < high)
    {
        time_t pivot = convertToTimeT(tasks[high].deadline);
        int i = (low - 1);
        for (int j = low; j < high; j++)
        {
            if (convertToTimeT(tasks[j].deadline) < pivot)
            {
                i++;
                swap(tasks[i], tasks[j]);
            }
        }
        swap(tasks[i + 1], tasks[high]);
        int pi = i + 1;

        quickSort(tasks, low, pi - 1);
        quickSort(tasks, pi + 1, high);
    }
}

// untuk menampilkan daftar tugas
void displayTasks(Task *tasks, int taskCount)
{
    cout << "\nPilih metode pengurutan:\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Quick Sort\n";
    cout << "Pilihan: ";
    int pilihan;
    cin >> pilihan;

    if (pilihan == 1)
    {
        bubbleSort(tasks, taskCount);
    }
    else if (pilihan == 2)
    {
        quickSort(tasks, 0, taskCount - 1);
    }
    else
    {
        cout << "Pilihan tidak valid! Menggunakan Bubble Sort sebagai default.\n";
        bubbleSort(tasks, taskCount);
    }

    cout << "Daftar Tugas (diurutkan berdasarkan deadline):" << endl;
    for (int i = 0; i < taskCount; ++i)
    {
        cout << "Nama Tugas: " << tasks[i].name
             << ", Kategori: " << tasks[i].category
             << ", Deadline: " << tasks[i].deadline
             << ", Status: " << tasks[i].status << endl;
    }
}

// fungsi untuk menambahkan tugas baru
void addTask(Task *tasks, int &taskCount)
{
    if (taskCount >= MAX_TASKS)
    {
        cout << "tidak dapat menambahkan tugas lagi, kapasitas penuh!" << endl;
        return;
    }

    Task newTask;
    cout << "Masukkan Nama Tugas: ";
    cin.ignore();
    getline(cin, newTask.name);
    cout << "Masukkan Kategori Tugas: ";
    getline(cin, newTask.category);
    cout << "Masukkan Deadline (DD/MM/YYYY): ";
    getline(cin, newTask.deadline);

    // cek apakah tugas sudah ada
    for (int i = 0; i < taskCount; ++i)
    {
        if (tasks[i].name == newTask.name)
        {
            cout << "tugas ini sudah terdaftar!" << endl;
            return;
        }
    }

    newTask.status = "Belum Selesai";
    tasks[taskCount++] = newTask;
    saveTasks(tasks, taskCount);
}

// fungsi untuk memperbarui status tugas
void updateTaskStatus(Task *tasks, int taskCount)
{
    string taskName;
    cout << "masukkan Nama Tugas untuk memperbarui status: ";
    cin.ignore();
    getline(cin, taskName);

    for (int i = 0; i < taskCount; ++i)
    {
        if (tasks[i].name == taskName)
        {
            tasks[i].status = "Selesai";
            saveTasks(tasks, taskCount);
            cout << "status tugas telah diperbarui menjadi 'Selesai'." << endl;
            return;
        }
    }
    cout << "tugas tidak ditemukan!" << endl;
}

// fungsi untuk menghapus tugas yang sudah selesai
void deleteCompletedTask(Task *tasks, int &taskCount)
{
    string taskName;
    cout << "Masukkan nama tugas untuk dihapus: ";
    cin.ignore();
    getline(cin, taskName);

    for (int i = 0; i < taskCount; ++i)
    {
        if (tasks[i].name == taskName)
        {
            if (tasks[i].status == "Selesai")
            {
                for (int j = i; j < taskCount - 1; ++j)
                {
                    tasks[j] = tasks[j + 1];
                }
                --taskCount;
                saveTasks(tasks, taskCount);
                cout << "tugas telah dihapus." << endl;
                return;
            }
            else
            {
                cout << "tugas belum selesai, tidak dapat dihapus." << endl;
                return;
            }
        }
    }
    cout << "tugas tidak ditemukan!" << endl;
}

// fungsi untuk mencari tugas berdasarkan kategori
void searchTasksByCategory(Task *tasks, int taskCount)
{
    string category;
    cout << "Masukkan Kategori Tugas: ";
    cin.ignore();
    getline(cin, category);

    bool found = false;
    for (int i = 0; i < taskCount; ++i)
    {
        if (tasks[i].category == category)
        {
            cout << "Nama Tugas: " << tasks[i].name
                 << ", Kategori: " << tasks[i].category
                 << ", Deadline: " << tasks[i].deadline
                 << ", Status: " << tasks[i].status << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "tidak ada tugas dalam kategori ini!" << endl;
    }
}
// fungsi untuk menampilkan tugas yang melewati deadline
void displayOverdueTasks(Task *tasks, int taskCount)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    bool found = false;
    for (int i = 0; i < taskCount; ++i)
    {
        if (tasks[i].status == "Belum Selesai")
        {
            int day, month, year;
            sscanf(tasks[i].deadline.c_str(), "%d/%d/%d", &day, &month, &year);
            tm taskDeadline = {0};
            taskDeadline.tm_mday = day;
            taskDeadline.tm_mon = month - 1;
            taskDeadline.tm_year = year - 1900;

            if (difftime(mktime(&taskDeadline), now) < 0)
            {
                if (!found)
                {
                    cout << "Perhatian!! Tugas berikut sudah melewati deadline:" << endl;
                    found = true;
                }
                cout << "Nama Tugas: " << tasks[i].name
                     << ", Kategori: " << tasks[i].category
                     << ", Deadline: " << tasks[i].deadline
                     << ", Status: " << tasks[i].status << endl;
            }
        }
    }

    if (!found)
    {
        cout << "semua tugas masih dalam batas waktu." << endl;
    }
}

void exitProgram()
{
    cout << "Terima kasih telah menggunakan WorkTracker! Tetap produktif!" << endl;
}
// fungsi utama
int main()
{
    Task tasks[MAX_TASKS];
    int taskCount = loadTasks(tasks);
    int choice;

    do
    {
        cout << "\n=== WorkTracker Menu ===" << endl;
        cout << "1. Tambahkan Tugas Baru" << endl;
        cout << "2. Tampilkan Daftar Tugas" << endl;
        cout << "3. Mencari Tugas Berdasarkan Kategori" << endl;
        cout << "4. Menampilkan Tugas yang Melewati Deadline" << endl;
        cout << "5. Perbarui Status Tugas" << endl;
        cout << "6. Hapus Tugas yang Sudah Selesai" << endl;
        cout << "7. Keluar dari Program" << endl;
        cout << "Pilih menu: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addTask(tasks, taskCount);
            break;
        case 2:
            displayTasks(tasks, taskCount);
            break;
        case 3:
            searchTasksByCategory(tasks, taskCount);
            break;
        case 4:
            displayOverdueTasks(tasks, taskCount);
            break;
        case 5:
            updateTaskStatus(tasks, taskCount);
            break;
        case 6:
            deleteCompletedTask(tasks, taskCount);
            break;
        case 7:
            exitProgram();
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (choice != 7);

    return 0;
}