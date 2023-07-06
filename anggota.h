/*
    Tugas Kelompok ALPRO - A11.4205
    1. Taliya Meyswara - A11.2022.14163
    2. Mushafa Fadzan A - A11.2022.14171
    3. Indra Fadillah - A11.2022.14186
    4. Lukmanul Hakim - A11.2022.14197

    Spesifikasi:
    1. Fitur CRUD terhadap data anggota
    2. Perhitungan lama Keanggotaan
    3. Fitur Pencarian data anggota berdasarkan ID dan nama
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class Anggota{
public:
    int id_anggota;
    string nama;
    string email;
    string tanggalDaftar;
    vector<Anggota> daftarAnggota;

public:
    // namafile utk menyimpan data anggota
    string namaFile = "dataanggota.txt";

    // fungsi utk menambah data anggota
    void tambahAnggota()
    {
        Anggota info; // objek anggota  utk menyimpan data anggota

        system("cls");
        cout << "==== Input data anggota ====" << endl;
        cout << "ID Anggota\t: ";
        cin >> info.id_anggota;
        cin.ignore();
        cout << "Nama\t\t: ";
        getline(cin, info.nama);
        cout << "Email\t\t: ";
        getline(cin, info.email);
        cout << "Tanggal Daftar (DD-MM-YYYY)\t: ";
        getline(cin, info.tanggalDaftar);

      //  hitungLamaKeanggotaan(info.tanggalDaftar);
        // menambahkan data anggota dari 'info' ke dalam vektor daftaranggota
        daftarAnggota.push_back(info);

        system("cls");
        cout << "Anggota berhasil ditambahkan!" << endl;
        simpanKeFile(); // simpan data yg sudah diinput ke file
    }

    // fungsi utk menghitung lama keanggotaan berdasarkan tanggal daftar
    string hitungLamaKeanggotaan(string tanggalDaftar)
    {
        time_t now = time(0); // mndptkan waktu saat ini
        tm* localTime = localtime(&now); // konversi waktu mjd timelocal

        int day, month, year;
        // mengambil tgl,bulan,tahun dari string tanggalDaftar
        sscanf(tanggalDaftar.c_str(), "%d-%d-%d", &day, &month, &year);

        tm date; // utk menyimpan waktu
        date.tm_year = year - 1900;
        date.tm_mon = month - 1;
        date.tm_mday = day;
        date.tm_hour = 0;
        date.tm_min = 0;
        date.tm_sec = 0;

        time_t t = mktime(&date); // konversi waktu dlm detik

        // hitung selisih waktu antara waktu saat ini dan tanggal daftar dalam detik
        double diff = difftime(now, t); 

        //hitung jml hari brdasarkan diff
        int days = static_cast<int>(diff / (60 * 60 * 24));

        int years = days / 365;  // hitung jml tahun berdasar jml hari
        days = days % 365; // sisa hari stlh tahun
        int months = days / 30; // hitung jml bulan berdsar sisa hari
        days = days % 30; // hitung sisa hari 

        stringstream ss;
        // konversi dlm string
        ss << days << " hari " << months << " bulan " << years << " tahun";

        return ss.str(); // return hasil dlm bentuk string
    }

    // fungsi utk menyimpan data ke file
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

        // proses menyimpan data anggota dari vektor 'daftarAnggota' ke dalam file
        for (const Anggota &info : daftarAnggota)
        {
            file << info.id_anggota << endl;
            file << info.nama << endl;
            file << info.email << endl;
            file << info.tanggalDaftar << endl;
           // file << info.lamaKeanggotaan << endl;
        }

        file.close(); // menutup file

        cout << "Data anggota berhasil disimpan dalam file." << endl;
    }

    // fungsi utk menampilkan semua data anggota
    void tampilkanDaftarAnggota()
    {
        // baca data dari file
        bacaDariFile();

        // jika tdk ada data anggota
        if (daftarAnggota.empty())
        {
            cout << "Tidak ada anggota dalam daftar!" << endl;
        }
        else
        {
            system("cls");
            cout << "==== Daftar anggota ====\n"
                 << endl;
            for (int i = 0; i < daftarAnggota.size(); i++)
            {
                string lamaKeanggotaan = hitungLamaKeanggotaan(daftarAnggota[i].tanggalDaftar);
                cout << "ID Anggota\t: " << daftarAnggota[i].id_anggota << endl;
                cout << "Nama\t\t: " << daftarAnggota[i].nama << endl;
                cout << "Email\t\t: " << daftarAnggota[i].email << endl;
                cout << "Tanggal Daftar\t: " << daftarAnggota[i].tanggalDaftar << endl;
                cout << "Lama Keanggotaan: " << lamaKeanggotaan << endl;
                cout << endl;
            }
        }
    }

    // fungsi utk menampilkan anggota
    void tampilkanAnggota()
    {
        cout << "==== Data anggota ====\n"<< endl;
        cout << "ID Anggota\t: " << id_anggota << endl;
        cout << "Nama\t\t: " << nama << endl;
        cout << "Email\t\t: " << email << endl;
        cout << "Tanggal Daftar\t: " << tanggalDaftar << endl;
        string lamaKeanggotaan = hitungLamaKeanggotaan(tanggalDaftar);
        cout << "Lama Keanggotaan: " << lamaKeanggotaan << endl;

    }

    // fungsi utk membaca data anggota dari file
    void bacaDariFile()
    {
        // kamus lokal
        string nama, email, tanggalDaftar;
        int id_anggota;
        Anggota info; //'info' sbg objek anggota

        // membuka file
        ifstream file(namaFile);

        // jika gagal membuka file
        if (!file)
        {
            system("cls");
            cout << "Gagal membuka file!" << endl;
            return;
        }

        // hapus data anggota dalam vektor daftarAnggota
        // utk memastikan vektor daftarAnggota hanya berisi data dalam file
        daftarAnggota.clear();

        // mproses membaca data dr file
        while (file >> id_anggota)
        {
            getline(file >> ws, nama);
            getline(file >> ws, email);
            getline(file >> ws, tanggalDaftar);
          //  file >> lamaKeanggotaan;

            // menyimpan data dlm objek
            info.id_anggota = id_anggota;
            info.nama = nama;
            info.email = email;
            info.tanggalDaftar = tanggalDaftar;
         //   info.lamaKeanggotaan = lamaKeanggotaan;

            // menambahkan data anggota dari 'info' ke dalam vektor daftarAnggota
            daftarAnggota.push_back(info);
        }

        file.close(); // menutup file
    }

    // fungsi utk mengambil data daftar anggota
    vector<Anggota> getDaftarAnggota()
    {
        // kamus lokal
        string nama, email, tanggalDaftar;
        int id_anggota;
        Anggota info; //'info' sbg objek anggota

        // membuka file
        ifstream file(namaFile);

        // jika gagal membuka file
        if (!file)
        {
            system("cls");
            cout << "Gagal membuka file!" << endl;
            return daftarAnggota;
        }

        // hapus data anggota dalam vektor daftarAnggota
        // utk memastikan vektor daftarAnggota hanya berisi data dalam file
        daftarAnggota.clear();

        // mproses membaca data dr file
        while (file >> id_anggota)
        {
            getline(file >> ws, nama);
            getline(file >> ws, email);
            getline(file >> ws, tanggalDaftar);

            // menyimpan data dlm objek
            info.id_anggota = id_anggota;
            info.nama = nama;
            info.email = email;
            info.tanggalDaftar = tanggalDaftar;

            // menambahkan data anggota dari 'info' ke dalam vektor daftarAnggota
            daftarAnggota.push_back(info);
        }

        file.close(); // menutup file
        return daftarAnggota;
    }

    // fungsi utk mengambil data anggota dngn id anggota
    Anggota getAnggotaById(int idAngota)
    {
        Anggota returnAnggota;
        int x;
        for (x = 0; x < getDaftarAnggota().size(); x++)
        {
            if (getDaftarAnggota()[x].id_anggota == idAngota)
            {
                returnAnggota = getDaftarAnggota()[x];
            };
        }

        return returnAnggota;
    }

    // fungsi utk mengubah data anggota
    void ubahanggota()
    {
        system("cls");

        tampilkanDaftarAnggota();

        // jika tdk ada data anggota
        if (daftarAnggota.empty())
        {
            system("cls");
            cout << "Tidak ada anggota dalam daftar!" << endl;
            return;
        }

        cout << "Masukkan ID anggota yang ingin diedit: ";
        int id;
        cin >> id;
        cin.ignore();

        // inisialisasi anggotaKetemu dgn false
        bool anggotaKetemu = false;

        // proses mencari data anggota berdasarkan id
        for (Anggota &info : daftarAnggota)
        {
            // jika id ada
            if (info.id_anggota == id)
            {
                anggotaKetemu = true; // ubah anggotaKetemu mjd true
                int opsiEdit;
                bool selesai = false;

                do
                {
                    system("cls");
                    // tampilkan info anggota
                    cout << "==== Informasi anggota ====\n"
                         << endl;
                    cout << "ID anggota\t: " << info.id_anggota << endl;
                    cout << "Nama\t\t: " << info.nama << endl;
                    cout << "Email\t\t: " << info.email << endl;
                    cout << "Tanggal Daftar\t: " << info.tanggalDaftar << endl;
                   // cout << "Lama Keanggotaan: " << info.lamaKeanggotaan << endl;

                    cout << "\nApa yang ingin diedit?\n";
                    cout << "1. Nama\n";
                    cout << "2. Email\n";
                    cout << "3. Tanggal Daftar\n";
                    cout << "4. Semua data\n";
                    cout << "0. Kembali\n";
                    cout << "Pilihan: ";
                    cin >> opsiEdit;
                    cin.ignore();

                    switch (opsiEdit)
                    {
                    case 1:
                        cout << "Masukkan nama baru: ";
                        getline(cin, info.nama);
                        cout << "Nama anggota berhasil diedit!" << endl;
                        break;
                    case 2:
                        cout << "Masukkan email baru: ";
                        getline(cin, info.email);
                        cout << "Email anggota berhasil diedit!" << endl;
                        break;
                    case 3:
                        cout << "Masukkan tanggal daftar baru: ";
                        getline(cin, info.tanggalDaftar);
                        cout << "Tanggal daftar berhasil diedit!" << endl;
                        break;
                    case 4:
                        cout << "\nSilakan masukkan data baru" << endl;
                        cout << "Nama\t: " ; getline(cin, info.nama);
                        cout << "Email\t: " ; getline(cin, info.email);
                        cout << "Tanggal Daftar (DD-MM-YYYY) : " ; getline(cin, info.tanggalDaftar);
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
                cout << "Data anggota berhasil diedit!\n"
                     << endl;
                // simpan hasil edit
                simpanKeFile();
                break;
            }
        }

        // jika id anggota tdk ketemu
        if (!anggotaKetemu)
        {
            system("cls");
            cout << "Anggota dengan ID tersebut tidak ditemukan!" << endl;
        }
    }

    // fungsi utk menghapus data anggota
    void hapusanggota()
    {
        system("cls");
        tampilkanDaftarAnggota();

        // jk tdk ada data anggota
        if (daftarAnggota.empty())
        {
            system("cls");
            cout << "Tidak ada data anggota dalam daftar!" << endl;
            return;
        }

        cout << "Masukkan ID anggota yang ingin dihapus: ";
        int id;
        cin >> id;
        cin.ignore();

        // inisialisasi anggotaKetemu dgn false
        bool anggotaKetemu = false;

        // inisialisasi index dgn -1
        int index = -1;

        // proses cari data anggota berdasarkan id
        for (int i = 0; i < daftarAnggota.size(); i++)
        {
            // jika id sada
            if (daftarAnggota[i].id_anggota == id)
            {
                anggotaKetemu = true; // anggota ketemu ubah jd true
                index = i;            // simpan idx anggota ke var index
                break;
            }
        }

        // jika anggota ditemukan
        if (anggotaKetemu)
        {
            // proses penghapusan anggota
            daftarAnggota.erase(daftarAnggota.begin() + index);
            system("cls");
            cout << "Anggota berhasil dihapus!" << endl;
            simpanKeFile(); // simpan data anggota terbaru (yg sudah terhapus) ke file
        }
        else
        { // jika anggota tdk ditemukan
            system("cls");
            cout << "Anggota dengan ID tersebut tidak ditemukan!" << endl;
        }
    }

    // Fungsi untuk mengubah string menjadi lowercase
    void lowercase(string& target) {
        for (char& c : target) {
            c = tolower(c);
        }
    }

   // Fungsi cari anggota berdasarkan nama
    void cariAnggotaByNama() {
        bacaDariFile();
        // Tampung inputan nama yang akan dicari
        string nama;

        system("cls");
        // Meminta user menginputkan nama anggota yang akan dicari
        cout << "Masukkan nama anggota yang akan dicari: ";

        // Mengirim hasil inputan ke variabel 'nama'
        getline(cin, nama);
        lowercase(nama);

        // Nilai awal status ditemukan
        bool ditemukan = false;

        system("cls");

        for (Anggota& anggota : daftarAnggota) {
            // Digunakan untuk menerima objek Anggota dari vektor daftarAnggota ketika melakukan iterasi melalui elemen vektor dalam loop
            string lowercaseNama = anggota.nama;
            lowercase(lowercaseNama);

            // Tampilkan data jika nama yang dicari ditemukan
            if (lowercaseNama == nama) {

                anggota.tampilkanAnggota();
                // Ubah nilai variabel ditemukan menjadi true
                ditemukan = true;
            }
        }

        // Jika nama tidak ditemukan
        if (!ditemukan) {
            cout << "Anggota dengan nama \"" << nama << "\" tidak ditemukan." << endl;
        }
    }

    // Fungsi cari anggota besadarkan id
    void cariAnggotaById()
    {
        // baca data dari file
        bacaDariFile();

        // tampung inputan nama yang akan diacari
        int id;

        // meminta user menginputkan nama angooota yang akan dicri
        cout << "Masukkan ID anggota yang akan dicari : ";

        // mengirim hasil inputan ke variabel 'nama'
        cin >> id;

        // nilai awal status ditemukan
        bool ditemukan = false;

        system("cls");

        for (Anggota &anggota : daftarAnggota)
        { // digunakan utk menerima objek Anggota dari vektor daftarAnggota ketiak melkukan iterasi melalui elemen vektor dalam loop
            // tampilakan data jika nama yang dicari ditemukan
            if (anggota.id_anggota == id)
            {
                
                anggota.tampilkanAnggota();
                cout << endl;
                // ubah nilai variabel ditemukan menjadi true
                ditemukan = true;
            }
        }

        // jika nama tidakditemukan
        if (!ditemukan)
        {
            cout << "Anggota dengan nama \"" << id << "\" tidak ditemukan." << endl;
        }
    }
};
