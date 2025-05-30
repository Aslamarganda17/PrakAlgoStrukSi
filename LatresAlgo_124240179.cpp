#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct Node
{
    string nama;
    string posisi;
    float nominal;
    Node *left, *right;

    Node(const string &n, const string &p, float d)
        : nama(n), posisi(p), nominal(d), left(nullptr), right(nullptr) {}
};

struct Action
{
    enum Type
    {
        ADD,
        REMOVE
    } type;
    string nama, posisi;
    float nominal;

    Action(Type t, const string &n, const string &p, float d)
        : type(t), nama(n), posisi(p), nominal(d) {}
};

Node *insert(Node *root, const string &nama, const string &posisi, float nominal)
{
    if (root == nullptr)
        return new Node(nama, posisi, nominal);
    if (nama < root->nama)
        root->left = insert(root->left, nama, posisi, nominal);
    else if (nama > root->nama)
        root->right = insert(root->right, nama, posisi, nominal);
    return root;
}

Node *findMin(Node *node)
{
    while (node && node->left)
        node = node->left;
    return node;
}

Node *remove(Node *root, const string &nama, stack<Action> &undoStack)
{
    if (root == nullptr)
        return nullptr;

    if (nama < root->nama)
        root->left = remove(root->left, nama, undoStack);
    else if (nama > root->nama)
        root->right = remove(root->right, nama, undoStack);
    else
    {
        undoStack.push(Action(Action::REMOVE, root->nama, root->posisi, root->nominal));

        if (root->left == nullptr)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }

        Node *temp = findMin(root->right);
        root->nama = temp->nama;
        root->posisi = temp->posisi;
        root->nominal = temp->nominal;
        root->right = remove(root->right, temp->nama, undoStack);
    }
    return root;
}

void inorder(Node *root)
{
    if (root)
    {
        inorder(root->left);
        cout << "Nama: " << root->nama << ", Posisi: " << root->posisi
             << ", Nominal: Rp " << root->nominal << endl;
        inorder(root->right);
    }
}

Node *undo(Node *root, stack<Action> &undoStack)
{
    if (undoStack.empty())
    {
        cout << "Tidak ada aksi untuk dibatalkan.\n";
        return root;
    }

    Action last = undoStack.top();
    undoStack.pop();

    if (last.type == Action::ADD)
    {
        root = remove(root, last.nama, undoStack);
        cout << "Undo berhasil: data '" << last.nama << "' dihapus kembali.\n";
    }
    else if (last.type == Action::REMOVE)
    {
        root = insert(root, last.nama, last.posisi, last.nominal);
        cout << "Undo berhasil: data '" << last.nama << "' dikembalikan.\n";
    }

    return root;
}

int main()
{
    Node *bst = nullptr;
    stack<Action> undoStack;

    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Tambah data terduga\n";
        cout << "2. Hapus data terduga\n";
        cout << "3. Tampilkan daftar pelaku\n";
        cout << "4. Undo aksi terakhir\n";
        cout << "5. Keluar\n";
        cout << "Pilih opsi: ";
        int pilihan;
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1)
        {
            string nama, posisi;
            float nominal;
            cout << "Nama pelaku: ";
            getline(cin, nama);
            cout << "Posisi dalam yayasan: ";
            getline(cin, posisi);
            cout << "Nominal dana yang diduga digelapkan: Rp ";
            cin >> nominal;
            cin.ignore();

            bst = insert(bst, nama, posisi, nominal);
            undoStack.push(Action(Action::ADD, nama, posisi, nominal));
            cout << "Data berhasil ditambahkan.\n";
        }
        else if (pilihan == 2)
        {
            string nama;
            cout << "Nama pelaku yang dihapus: ";
            getline(cin, nama);
            bst = remove(bst, nama, undoStack);
            cout << "Data berhasil dihapus.\n";
        }
        else if (pilihan == 3)
        {
            cout << "\nDaftar terduga pelaku penggelapan dana:\n";
            inorder(bst);
        }
        else if (pilihan == 4)
        {
            bst = undo(bst, undoStack);
        }
        else if (pilihan == 5)
        {
            break;
        }
        else
        {
            cout << "Pilihan tidak valid.\n";
        }
    }
    return 0;
}
