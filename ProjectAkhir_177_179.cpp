#include <iostream>
#include <string>
using namespace std;

//struct untuk menyimpan data pesanan
struct Pesanan{
  int id;
  string namaPelanggan;
  int jumlah;
  int estimasiWaktu;
  Pesanan *next;
};
