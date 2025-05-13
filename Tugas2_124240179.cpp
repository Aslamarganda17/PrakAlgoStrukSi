#include <iostream>
#include <string>
#include <limits>
using namespace std;

// node untuk linked list ganda
class Node
{
public:
    string judul;
    float harga;
    Node *prev;
    Node *next;

    Node(string j, float h) : judul(j), harga(h), prev(nullptr), next(nullptr) {}
};

// class linked list ganda
class BukuList
{
private:
    Node *head;

public:
    BukuList() : head(nullptr) {}
    void tambahBuku(string judul, float harga)
    {
        Node *baru = new Node(judul, harga);
        if (!head)
        {
            head = baru;
        }
        else
        {
            Node *temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = baru;
            baru->prev = temp;
        }
    }
    void tampilkanBuku()
    {
        if (!head)
        {
            cout << "Belum ada data buku.\n";
            return;
        }
        cout << "\n=== Daftar Buku ===\n";
        Node *temp = head;
        while (temp)
        {
            cout << "Judul: " << temp->judul << ", Harga: Rp" << temp->harga << endl;
            temp = temp->next;
        }
    }
    void cariBuku(string target)
    {
        Node *temp = head;
        while (temp)
        {
            if (temp->judul == target)
            {
                cout << "Buku ditemukan: " << temp->judul << ", Harga: Rp" << temp->harga << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Buku dengan judul \"" << target << "\" tidak ditemukan.\n";
    }
    void sisipBuku(string judul, float harga, string posisi)
    {
        Node *baru = new Node(judul, harga);

        if (posisi == "depan")
        {
            if (head)
            {
                baru->next = head;
                head->prev = baru;
            }
            head = baru;
        }
        else if (posisi == "belakang")
        {
            tambahBuku(judul, harga);
        }
        else if (posisi == "tengah")
        {
            if (!head)
            {
                head = baru;
                return;
            }
            Node *slow = head;
            Node *fast = head;
            while (fast && fast->next)
            {
                slow = slow->next;
                fast = fast->next->next;
            }
            baru->next = slow->next;
            baru->prev = slow;
            if (slow->next)
                slow->next->prev = baru;
            slow->next = baru;
        }
        else
        {
            cout << "Posisi tidak valid.\n";
            delete baru;
        }
    }

    void hapusBuku(string target)
    {
        Node *temp = head;
        while (temp)
        {
            if (temp->judul == target)
            {
                if (temp->prev)
                    temp->prev->next = temp->next;
                else
                    head = temp->next;
                if (temp->next)
                    temp->next->prev = temp->prev;
                delete temp;
                cout << "buku berhasil dihapus.\n";
                return;
            }
            temp = temp->next;
        }
        cout << "buku tidak ditemukan.\n";
    }
    // destructor
    BukuList()
    {
        Node *temp = head;
        while (temp)
        {
            Node *hapus = temp;
            temp = temp->next;
            delete hapus;
        }
    }
};
void inputHarga(float &harga)
{
    while (!(cin >> harga) || harga < 0)
    {
        cout << "Input harga tidak valid. Ulangi: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
}
int main()
{
    BukuList daftarBuku;
    int menu;
    string judul;
    float harga;

    do
    {
        cout << "\n=== Menu ===\n";
        cout << "1. Tambahkan Buku\n";
        cout << "2. Tampilkan Seluruh Data buku\n";
        cout << "3. cari data buku\n";
        cout << "4. Sisip buku (Depan, Tengah, Belakang)\n";
        cout << "5. Hapus buku\n";
        cout << "6. Keluar\n";
        cout << "Pilih Menu: ";
        cin >> menu;
        cin.ignore();

        switch (menu)
        {
        case 1:
            cout << "Judul Buku: ";
            getline(cin, judul);
            cout << "Harga Buku: ";
            inputHarga(harga);
            daftarBuku.tambahBuku(judul, harga);
            break;

        case 2:
            daftarBuku.tampilkanBuku();
            break;

        case 3:
            cout << "Masukkan judul buku yang dicari: ";
            getline(cin, judul);
            daftarBuku.cariBuku(judul);
            break;

        case 4:
        {
            string posisi;
            cout << "Judul buku: ";
            getline(cin, judul);
            cout << "Harga buku: ";
            inputHarga(harga);
            cout << "Posisi (depan / tengah / belakang): ";
            getline(cin, posisi);
            daftarBuku.sisipBuku(judul, harga, posisi);
            break;
        }

        case 5:
            cout << "Masukkan Judul Buku yang Dihapus: ";
            getline(cin, judul);
            daftarBuku.hapusBuku(judul);
            break;

        case 6:
            cout << "Terima kasih telah menggunakan program!\n";
            break;

        default:
            cout << "Pilihan menu tidak valid. Coba lagi.\n";
        }
    } while (menu != 6);

    return 0;
}
