#include <iostream>
#include <string>
using namespace std;

// definisikan struktur untuk buku
struct Buku
{
    string judul;
    int tahun_terbit;
};

// deklarasi fungsi partition
int partition(Buku daftarBuku[], int low, int high);

// fungsi untuk menampilkan daftar buku
void tampilkanDaftarBuku(Buku daftarBuku[], int jumlah)
{
    cout << "Daftar Buku:\n";
    for (int i = 0; i < jumlah; i++)
    {
        cout << i + 1 << ". " << daftarBuku[i].judul << " (" << daftarBuku[i].tahun_terbit << ")\n";
    }
}

// fungsi untuk mengurutkan dengan bubble Sort
void bubbleSort(Buku daftarBuku[], int jumlah)
{
    for (int i = 0; i < jumlah - 1; i++)
    {
        for (int j = 0; j < jumlah - i - 1; j++)
        {
            if (daftarBuku[j].tahun_terbit > daftarBuku[j + 1].tahun_terbit)
            {
                // tukar buku
                Buku temp = daftarBuku[j];
                daftarBuku[j] = daftarBuku[j + 1];
                daftarBuku[j + 1] = temp;
            }
        }
    }
}

// fungsi untuk mengurutkan dengan quick Sort
void quickSort(Buku daftarBuku[], int low, int high)
{
    if (low < high)
    {
        int p = partition(daftarBuku, low, high);
        quickSort(daftarBuku, low, p - 1);
        quickSort(daftarBuku, p + 1, high);
    }
}

// fungsi untuk partisi quick Sort
int partition(Buku daftarBuku[], int low, int high)
{
    int pivot = daftarBuku[high].tahun_terbit;
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (daftarBuku[j].tahun_terbit < pivot)
        {
            i++;
            Buku temp = daftarBuku[i];
            daftarBuku[i] = daftarBuku[j];
            daftarBuku[j] = temp;
        }
    }
    Buku temp = daftarBuku[i + 1];
    daftarBuku[i + 1] = daftarBuku[high];
    daftarBuku[high] = temp;
    return i + 1;
}

// fungsi untuk pencarian sequential
void sequentialSearch(Buku daftarBuku[], int jumlah, int tahun)
{
    for (int i = 0; i < jumlah; i++)
    {
        if (daftarBuku[i].tahun_terbit == tahun)
        {
            cout << "Buku ditemukan: " << daftarBuku[i].judul << " (" << tahun << ")\n";
            return;
        }
    }
    cout << "Buku dengan tahun terbit " << tahun << " tidak ditemukan.\n";
}

// fungsi untuk pencarian binary
int binarySearch(Buku daftarBuku[], int low, int high, int tahun)
{
    if (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (daftarBuku[mid].tahun_terbit == tahun)
        {
            return mid;
        }
        if (daftarBuku[mid].tahun_terbit > tahun)
        {
            return binarySearch(daftarBuku, low, mid - 1, tahun);
        }
        return binarySearch(daftarBuku, mid + 1, high, tahun);
    }
    return -1;
}

int main()
{
    const int MAX_BUKU = 100;
    Buku daftarBuku[MAX_BUKU];
    int jumlahBuku = 0;
    int pilihan;

    do
    {
        cout << "\n=== Menu ===\n";
        cout << "1. Input Data Buku\n";
        cout << "2. Tampilkan Data Buku\n";
        cout << "3. Urutkan Buku dengan Bubble Sort\n";
        cout << "4. Urutkan Buku dengan Quick Sort\n";
        cout << "5. Cari Buku dengan Sequential Search\n";
        cout << "6. Cari Buku dengan Binary Search\n";
        cout << "7. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            if (jumlahBuku < MAX_BUKU)
            {
                cout << "Masukkan Judul Buku: ";
                cin >> ws;
                getline(cin, daftarBuku[jumlahBuku].judul);
                cout << "Masukkan Tahun Terbit: ";
                cin >> daftarBuku[jumlahBuku].tahun_terbit;
                jumlahBuku++;
            }
            else
            {
                cout << "Daftar buku sudah penuh!\n";
            }
            break;

        case 2:
            tampilkanDaftarBuku(daftarBuku, jumlahBuku);
            break;

        case 3:
            cout << "Sebelum sorting:\n";
            tampilkanDaftarBuku(daftarBuku, jumlahBuku);
            bubbleSort(daftarBuku, jumlahBuku);
            cout << "Setelah sorting dengan Bubble Sort:\n";
            tampilkanDaftarBuku(daftarBuku, jumlahBuku);
            break;

        case 4:
            cout << "Sebelum sorting:\n";
            tampilkanDaftarBuku(daftarBuku, jumlahBuku);
            quickSort(daftarBuku, 0, jumlahBuku - 1);
            cout << "Setelah sorting dengan Quick Sort:\n";
            tampilkanDaftarBuku(daftarBuku, jumlahBuku);
            break;

        case 5:
        {
            int tahun;
            cout << "Masukkan tahun yang dicari: ";
            cin >> tahun;
            sequentialSearch(daftarBuku, jumlahBuku, tahun);
            break;
        }

        case 6:
        {
            int tahun;
            cout << "Masukkan tahun yang dicari: ";
            cin >> tahun;
            int result = binarySearch(daftarBuku, 0, jumlahBuku - 1, tahun);
            if (result != -1)
            {
                cout << "Buku ditemukan: " << daftarBuku[result].judul << " (" << tahun << ")\n";
            }
            else
            {
                cout << "Buku dengan tahun terbit " << tahun << " tidak ditemukan.\n";
            }
            break;
        }

        case 7:
            cout << "Keluar dari program.\n";
            break;

        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 7);

    return 0;
}