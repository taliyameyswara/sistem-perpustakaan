/*
    Tugas Kelompok ALPRO - A11.4205
    1. Taliya Meyswara - A11.2022.14163
    2. Mushafa Fadzan A - A11.2022.14171
    3. Indra Fadillah - A11.2022.14186
    4. Lukmanul Hakim - A11.2022.14197

    Program Manajemen Perpustkaan

    Spesifikasi:
    1. Manajemen Buku
    2. Manajemen Anggota
    3. Manajemen Perpustakaan
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include "peminjaman.h"


using namespace std;

// kamus global
Buku buku;
Anggota anggota;
Peminjaman peminjaman;

int pilihan;
int mainMenuOption;

int main(){

    do{
        system("cls");
        cout << "=== Sistem Manajemen Perpustakaan ===" << endl;
        cout << "1. Manajemen Data Buku\n2. Manajemen Data Anggota\n3. Manajemen Data Peminjaman\n0. Keluar\nPilih (1-3) : ";
        cin >> mainMenuOption;
        system("cls");

        switch (mainMenuOption){
            case 1:
                do{
                    cout << "==== Manajemen Buku ====" << endl;
                    cout << "Menu: " << endl;
                    cout << "1. Tambah Buku" << endl;
                    cout << "2. Tampilkan Daftar Buku" << endl;
                    cout << "3. Edit Data Buku" << endl;
                    cout << "4. Hapus Data Buku" << endl;
                    cout << "5. Cari Data Buku Berdasarkan ID" << endl;
                    cout << "6. Cari Data Buku Berdasarkan Judul" << endl;
                    cout << "0. Keluar" << endl;
                    cout << "Pilih menu: ";
                    cin >> pilihan;
                
                    cin.ignore();

                    switch (pilihan)
                    {
                    case 1:
                        buku.tambahBuku();
                        break;
                    case 2:
                        buku.tampilkanDaftarBuku();
                        break;
                    case 3:
                        buku.ubahBuku();
                        break;
                    case 4:
                        buku.hapusBuku();
                        break;
                    case 5:
                        buku.cariBukuById();
                        break;
                    case 6:
                        buku.cariBukuByJudul();
                        break;
                    case 0:
                        cout << "Terima kasih!" << endl;
                        break;
                    default:
                        cout << "Pilihan tidak valid!" << endl;
                        break;
                    }

                    cout << endl;
                } while (pilihan != 0);
                break;

            case 2:
                do{
                        cout << "==== Manajemen Anggota ====" << endl;
                        cout << "Menu: " << endl;
                        cout << "1. Tambah Anggota" << endl;
                        cout << "2. Tampilkan Daftar Anggota" << endl;
                        cout << "3. Edit Data Anggota" << endl;
                        cout << "4. Hapus Data Anggota" << endl;
                        cout << "5. Cari Anggota Berdasarkan Nama" << endl;
                        cout << "6. Cari Anggota Berdasarkan ID" << endl;
                        cout << "0. Keluar" << endl;
                        cout << "Pilih menu: ";
                        cin >> pilihan;
                    
                        cin.ignore();

                        switch (pilihan)
                        {
                        case 1:
                            anggota.tambahAnggota();
                            break;
                        case 2:
                            anggota.tampilkanDaftarAnggota();
                            break;
                        case 3:
                            anggota.ubahanggota();
                            break;
                        case 4:
                            anggota.hapusanggota();
                            break;
                        case 5:
                            anggota.cariAnggotaByNama();
                            break;
                        case 6:
                            anggota.cariAnggotaById();
                            break;
                        case 0:
                            cout << "Terima kasih!" << endl;
                            break;
                        default:
                            cout << "Pilihan tidak valid!" << endl;
                            break;
                        }

                        cout << endl;
                    }while (pilihan != 0);
                    break;
            case 3:
                do{
                        cout << "==== Manajemen Peminjaman ====" << endl;
                        cout << "Menu: " << endl;
                        cout << "1. Tambah Peminjaman" << endl;
                        cout << "2. Tampilkan Daftar Peminjaman" << endl;
                        cout << "3. Kembalikan Peminjaman" << endl;
                        cout << "4. Bayar Denda" << endl;
                        cout << "0. Keluar" << endl;
                        cout << "Pilih menu: ";
                        cin >> pilihan;
                    
                        cin.ignore();

                        switch (pilihan)
                        {
                        case 1:
                            peminjaman.pinjamBuku();
                            break;
                        case 2:
                            peminjaman.tampilkanDaftarPeminjaman();
                            break;
                        case 3:
                            peminjaman.kembaliBuku();
                            break;
                        case 4:
                            peminjaman.bayarDenda();
                            break;
                        case 0:
                            cout << "Terima kasih!" << endl;
                            break;
                        default:
                            cout << "Pilihan tidak valid!" << endl;
                            break;
                        }

                        cout << endl;
                    }while (pilihan != 0);
                    break;
            case 0: 
                cout << "Keluar dari program. Terima Kasih!" << endl;
                break;
            default:
                break;
        }
    }while(mainMenuOption!=0);

    return 0;
}
