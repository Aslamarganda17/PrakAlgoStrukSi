#include <iostream>
#include <string>
using namespace std;

//struct untuk menyimpan data pesanan
struct Pesanan{
  int id;
  string namaPelanggan;
  string makanan;
  int jumlah;
  int estimasiWaktu;
  Pesanan *next;
};

//pointer untuk menyimpan head dan tail dari linked list kepala ekor
Pesanan *head = nullptr;
Pesanan *tail = nullptr;

//variabel untuk menyimpan id pesanan selanjutnya
int nextId = 1;

//Fungsi untuk menyimpan data pesanan ke file data_pesanan.txt
void simpanKeFile(Pesanan *head){
  FILE *f = fopen("data_pesanan.txt", "w");
  if (f==NULL){
      cout << "Gagal membuka file untuk menyimpan data" << endl;
      return;
  }

  Pesanan *bantu = head;
    while (bantu != nullptr){
        fprintf(f, "%d,%s,%s,%d,%d\n", bantu->id, bantu->namaPelanggan.c_str(), bantu->makanan.c_str(), bantu->jumlah, bantu->estimasiWaktu);
        bantu = bantu->next;
    }
    fclose(f);
}

//Fungsi untuk menyimpan data pesanan yang sudah diproses ke file riwayat_pesanan.txt
void simpanKeRiwayat(Pesanan *pesanan, const string &hasilReview){
    FILE *f = fopen("riwayat_pesanan.txt", "a");
    if (f == NULL){
        cout << "Gagal membuka file untuk menyimpan riwayat pesanan"<<endl;
        return;
    }
    fprintf(f, "%d,%s,%s,%d,%d,%s\n", pesanan->id, pesanan->namaPelanggan.c_str(), 
    pesanan->makanan.c_str(), pesanan->jumlah, pesanan->estimasiWaktu, hasilReview.c_str());
    fclose(f);   
}
