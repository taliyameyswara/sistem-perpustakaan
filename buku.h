/*
    Tugas Kelompok ALPRO - A11.4205
    1. Taliya Meyswara - A11.2022.14163
    2. Mushafa Fadzan A - A11.2022.14171
    3. Indra Fadillah - A11.2022.14186
    4. Lukmanul Hakim - A11.2022.14197

    buku.h

    Spesifikasi:
    1. terdapat fungsi utk melakukan CRUD data buku
    2. terdapat fungsi utk mengurangi/menambahkan stok buku yg digunakan pd fitur peminjaman

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Buku{
public:
    int id_buku;
    string judul;
    string pengarang;
    string penerbit;
    int stokBuku;
    vector<Buku> daftarBuku;

public:
    // namafile utk menyimpan data buku
    string namaFile = "dataBuku.txt";

    // fungsi utk menambah data buku
    void tambahBuku()
    {
        Buku info; // objek buku utk menyimpan data buku

        system("cls");
        cout << "==== Input data buku ====" << endl;
        cout << "ID Buku\t\t: ";
        cin >> info.id_buku;
        cin.ignore();
        cout << "Judul Buku\t: ";
        getline(cin, info.judul);
        cout << "Pengarang\t: ";
        getline(cin, info.pengarang);
        cout << "Penerbit\t: ";
        getline(cin, info.penerbit);

        cout << "Stok Buku\t: ";
        cin >> info.stokBuku;

        // menambahkan data buku dari 'info' ke dalam vektor daftarBuku
        daftarBuku.push_back(info);

        system("cls");
        cout << "Buku berhasil ditambahkan!" << endl;
        simpanKeFile(); // simpan data yg sudah diinput ke file
    }

    // fungsi utk menyimpan data buku ke file
    void simpanKeFile()
    {
        // buka file
        ofstream file(namaFile);

        // jika file gagal dibuka
        if (!file)
        {
            cout << "Gagal membuka file!" << endl;
            return;
        }

        // proses menyimpan data buku dari vektor 'daftarBuku' ke dalam file
        for (const Buku &info : daftarBuku)
        {
            file << info.id_buku << endl;
            file << info.judul << endl;
            file << info.pengarang << endl;
            file << info.penerbit << endl;
            file << info.stokBuku << endl;
        }

        file.close(); // menutup file

        cout << "Data buku berhasil disimpan dalam file." << endl;
    }

    // fungsi utk menampilkan semua data buku
    void tampilkanDaftarBuku()
    {
        bacaDariFile();
        // jika tdk ada data buku
        if (daftarBuku.empty())
        {
            system("cls");
            cout << "Tidak ada buku dalam daftar!" << endl;
        }
        else
        {
            system("cls");
            cout << "==== Daftar Buku ====\n"
                 << endl;
            for (int i = 0; i < daftarBuku.size(); i++)
            {
                cout << "ID Buku\t\t: " << daftarBuku[i].id_buku << endl;
                cout << "Judul Buku\t: " << daftarBuku[i].judul << endl;
                cout << "Pengarang\t: " << daftarBuku[i].pengarang << endl;
                cout << "Penerbit\t: " << daftarBuku[i].penerbit << endl;
                cout << "Stok Buku\t: " << daftarBuku[i].stokBuku << endl;

                cout << endl;
            }
        }
    }

    // fungsi utk menampilkan data buku
    void tampilkanBuku() const
    {
        cout << "==== Data Buku ====\n" << endl;
        cout << "ID Buku\t\t: " << id_buku << endl;
        cout << "Judul Buku\t: " << judul << endl;
        cout << "Pengarang\t: " << pengarang << endl;
        cout << "Penerbit\t: " << penerbit << endl;
        cout << "Stok Buku\t: " << stokBuku << endl;

        cout << endl;
    }

    // fungsi utk membaca data buku dari file, sekaligus utk mencetak daftar data buku
    void bacaDariFile()
    {
        // kamus lokal
        string judul, pengarang, penerbit, stok;
        int id_buku;
        Buku info; //'info' sbg objek buku

        // membuka file
        ifstream file(namaFile);

        // jika gagal membuka file
        if (!file)
        {
            system("cls");
            cout << "Gagal membuka file!" << endl;
            return;
        }

        // hapus data buku dalam vektor daftarBuku
        // utk memastikan vektor daftarBuku hanya berisi data dalam file
        daftarBuku.clear();

        // mproses membaca data dr file
        while (file >> id_buku)
        {
            getline(file >> ws, judul);
            getline(file >> ws, pengarang);
            getline(file >> ws, penerbit);
            getline(file >> ws, stok);

            // menyimpan data dlm objek
            info.id_buku = id_buku;
            info.judul = judul;
            info.pengarang = pengarang;
            info.penerbit = penerbit;
            info.stokBuku = stoi(stok);

            // menambahkan data buku dari 'info' ke dalam vektor daftarBuku
            daftarBuku.push_back(info);
        }

        file.close();          // menutup file
    }

    // fungsi utk mendapatkan data buku berdasarkan id buku
    Buku getBukuById(int idBuku)
    {
        Buku returnBuku;
        int x;
        for (x = 0; x < getDaftarBuku().size(); x++)
        {
            if (getDaftarBuku()[x].id_buku == idBuku)
            {
                returnBuku = getDaftarBuku()[x];
            };
        }

        return returnBuku;
    }

    // fungsi utk mengurangi stok buku
    bool kurangiStock(int idBuku)
    {
        bool adaStock = false;

        int x;
        daftarBuku = getDaftarBuku();
        for (x = 0; x < daftarBuku.size(); x++)
        {
            if (daftarBuku[x].id_buku == idBuku)
            {
                if (daftarBuku[x].stokBuku >= 1)
                {
                    adaStock = true;
                    daftarBuku[x].stokBuku--;
                    simpanKeFile();
                }
            };
        }

        return adaStock;
    }

    // fungsi utk menambah stok buku
    void tambahStock(int idBuku)
    {

        int x;
        daftarBuku = getDaftarBuku();
        for (x = 0; x < daftarBuku.size(); x++)
        {
            if (daftarBuku[x].id_buku == idBuku)
            {
                daftarBuku[x].stokBuku++;
                simpanKeFile();
            }
        };
    }

    // fungsi utk mendapatkan daftarbuku
    vector<Buku> getDaftarBuku()
    {
        // kamus lokal
        string judul, pengarang, penerbit, stock;
        int id_buku;
        Buku info; //'info' sbg objek buku

        // membuka file
        ifstream file(namaFile);

        // jika gagal membuka file
        if (!file)
        {
            system("cls");
            cout << "Gagal membuka file!" << endl;
            return daftarBuku;
        }

        // hapus data buku dalam vektor daftarBuku
        // utk memastikan vektor daftarBuku hanya berisi data dalam file
        daftarBuku.clear();

        // mproses membaca data dr file
        while (file >> id_buku)
        {
            getline(file >> ws, judul);
            getline(file >> ws, pengarang);
            getline(file >> ws, penerbit);
            getline(file >> ws, stock);

            // menyimpan data dlm objek
            info.id_buku = id_buku;
            info.judul = judul;
            info.pengarang = pengarang;
            info.penerbit = penerbit;
            info.stokBuku = stoi(stock);

            // menambahkan data buku dari 'info' ke dalam vektor daftarBuku
            daftarBuku.push_back(info);
        }

        file.close(); // menutup file
        return daftarBuku;
    }

    // fungsi utk mengedit data buku
    void ubahBuku()
    {
        system("cls");

        // panggil fungsi baca file
        bacaDariFile();

        // jika tdk ada data buku
        if (daftarBuku.empty())
        {
            system("cls");
            cout << "Tidak ada buku dalam daftar!" << endl;
            return;
        }

        tampilkanDaftarBuku();
        cout << "Masukkan ID buku yang ingin diedit: ";
        int id;
        cin >> id;
        cin.ignore();

        // inisialisasi bukuKetemu dgn false
        bool bukuKetemu = false;

        // proses mencari data buku berdasarkan id
        for (Buku &info : daftarBuku)
        {
            // jika id ada
            if (info.id_buku == id)
            {
                bukuKetemu = true; // ubah bukuKetemu mjd true
                int opsiEdit;
                bool selesai = false;

                do
                {
                    system("cls");
                    // tampilkan info buku
                    cout << "==== Informasi Buku ====\n"
                         << endl;
                    cout << "ID Buku\t\t: " << info.id_buku << endl;
                    cout << "Judul Buku\t: " << info.judul << endl;
                    cout << "Pengarang\t: " << info.pengarang << endl;
                    cout << "Penerbit\t: " << info.penerbit << endl;

                    cout << "\nApa yang ingin diedit?\n";
                    cout << "1. Judul\n";
                    cout << "2. Pengarang\n";
                    cout << "3. Penerbit\n";
                    cout << "4. Semua data\n";
                    cout << "0. Kembali\n";
                    cout << "Pilihan: ";
                    cin >> opsiEdit;
                    cin.ignore();

                    switch (opsiEdit)
                    {
                    case 1:
                        cout << "Masukkan judul buku baru: ";
                        getline(cin, info.judul);
                        cout << "Judul buku berhasil diedit!" << endl;
                        break;
                    case 2:
                        cout << "Masukkan nama pengarang baru: ";
                        getline(cin, info.pengarang);
                        cout << "Nama pengarang berhasil diedit!" << endl;
                        break;
                    case 3:
                        cout << "Masukkan nama penerbit baru: ";
                        getline(cin, info.penerbit);
                        cout << "Nama penerbit berhasil diedit!" << endl;
                        break;
                    case 4:
                        cout << "\nSilakan masukkan data baru" << endl;
                        cout << "Judul\t\t: " ; getline(cin, info.judul);
                        cout << "Pengarang\t: " ; getline(cin, info.pengarang);
                        cout << "Penerbit\t: " ; getline(cin, info.penerbit);
                        cout << "\nSemua data berhasil diedit!" << endl;
                        break;
                    case 0:
                        selesai = true;
                        break;
                    default:
                        cout << "Pilihan tidak valid!" << endl;
                        break;
                    }
                } while (!selesai);
                system("cls");
                cout << "Buku berhasil diedit!\n"
                     << endl;
                // simpan hasil edit
                simpanKeFile();
                break;
            }
        }

        // jika id buku tdk ketemu
        if (!bukuKetemu)
        {
            system("cls");
            cout << "Buku dengan ID tersebut tidak ditemukan!" << endl;
        }
    }

    // fungsi utk menghapus data buku
    void hapusBuku()
    {
        system("cls");
        // panggil fungsi utk membaca data buku dr file
        bacaDariFile();

        // jk tdk ada data buku
        if (daftarBuku.empty())
        {
            system("cls");
            cout << "Tidak ada buku dalam daftar!" << endl;
            return;
        }

        cout << "Masukkan ID buku yang ingin dihapus: ";
        int id;
        cin >> id;
        cin.ignore();

        // inisialisasi bukuKetemu dgn false
        bool bukuKetemu = false;

        // inisialisasi index dgn -1
        int index = -1;

        // proses cari data buku berdasarkan id
        for (int i = 0; i < daftarBuku.size(); i++)
        {
            // jika id sada
            if (daftarBuku[i].id_buku == id)
            {
                bukuKetemu = true; // buku ketemu ubah jd true
                index = i;         // simpan idx buku ke var index
                break;
            }
        }

        // jika buku ditemukan
        if (bukuKetemu)
        {
            // proses penghapusan buku
            daftarBuku.erase(daftarBuku.begin() + index);
            system("cls");
            cout << "Buku berhasil dihapus!" << endl;
            simpanKeFile(); // simpan data buku terbaru (yg sudah terhapus) ke file
        }
        else
        { // jika buku tdk ditemukan
            system("cls");
            cout << "Buku dengan ID tersebut tidak ditemukan!" << endl;
        }
    }

    // fungsi utk mencari buku berdasarkan id
    void cariBukuById()
    {
        system("cls");
        bacaDariFile();

        // untuk menampung id yng akan diacari
        int cariIdBuku;

        // meminta user menasukkan id ynag akan dicari
        cout << "Masukkan ID buku yang akan dicari : ";

        // mengirim hasil inputan ke variabel CariIdBuku
        cin >> cariIdBuku;

        // nilai awal dari setatus IdBukuDitemukna
        bool IdBukuDitemukan = false;

        // objek dataBukuYangDicari berdasarkan class Buku
        Buku DatabukuYangDiCari;

        // proses pencarian
        for (const Buku &buku : daftarBuku)
        {
            if (buku.id_buku == cariIdBuku)
            {
                // jika ditemukan makan sttaus tadi diubah menjadi true
                IdBukuDitemukan = true;

                // mengisi object dengan data buku berdasarkan id yang dicari
                DatabukuYangDiCari = buku;
                break;
            }
        }

        // jika status tadi true maka tampilkan data buku yang dicari
        if (IdBukuDitemukan)
        {
            DatabukuYangDiCari.tampilkanBuku();
        }
        else
        {
            cout << "Buku dengan ID tersebut tidak ditemukan!" << endl;
        }
    }

     // Fungsi untuk mengubah string menjadi lowercase
    void lowercase(string& target) {
        for (char& c : target) {
            c = tolower(c);
        }
    }

    // Fungsi untuk mencari buku berdasarkan judul
    void cariBukuByJudul()
    {
        system("cls");
        bacaDariFile();

        // untuk menampung judul buku yng akan dicari
        string cariJudulBuku;

        // meminta user menasukkan judul buku  akan dicari
        cout << "Masukkan judul buku yang dicari : ";

        // kirim hasil inputan ke variabel cariJudulBuku
        getline(cin, cariJudulBuku);

        lowercase(cariJudulBuku);

        // nilai awal status dibuat jadi false
        bool judulBukuDitemukan = false;

        for (const Buku &buku : daftarBuku) // mereferensikan buku ke vektor daftarBuku shg tidak perlu membuat salianan data di objek buku
        {
            string lowercaseJudul = buku.judul;
            lowercase(lowercaseJudul);

            if (lowercaseJudul == cariJudulBuku)
            {
                buku.tampilkanBuku();
                judulBukuDitemukan = true;
            }
        }

        if (!judulBukuDitemukan)
        {
            cout << "Buku dengan judul \"" << cariJudulBuku << "\" tidak ditemukan." << endl;
        }
    }
};
