/*
    Tugas Kelompok ALPRO - A11.4205
    1. Taliya Meyswara - A11.2022.14163
    2. Mushafa Fadzan A - A11.2022.14171
    3. Indra Fadillah - A11.2022.14186
    4. Lukmanul Hakim - A11.2022.14197

    peminjaman.h

    Spesifikasi:
    1. terdapat fungsi utk meminjam buku dengan inputan ID Anggota sbg peminjam dan ID buku
    2. jika tidak ada data anggota/buku, peminjaman gagal
    3. peminjaman dibatasi 14 hari, yang menghasilkan tanggal batas peminjaman
    4. jika tgl pengembalian melebihi batas, maka akan terkena denda
    5. denda dapat dibayar dg fungsi bayarDenda
    6. fungsi bayarDenda tdk dapat digunakan jika tdk ada peminjaman dengan denda
    5. jika peminjaman selesai (tidak terlambat/denda terbayar), data peminjaman akan terhapus
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "buku.h"
#include "anggota.h"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
using namespace std;

class Peminjaman{
    private:
    int id;
    string tglpinjam;
    string tglDikembalikan;
    int lamaPinjam = 14; // maksimal pinjam 14 hari
    int dendaPerHari = 500; 

    int idAnggota;
    int idBuku;
    bool sudahKembali;
    bool sudahBayar;

    vector<Peminjaman> dataPeminjaman;

    public:
    string namaFile = "dataPeminjaman.txt";
    
    // fungsi utk meminjam buku
    void pinjamBuku(){
        // kamus lokal
        Peminjaman info;
        Anggota infopeminjam;
        Buku infobuku;
        
        system ("cls");
        cout << "==== Input Data Peminjaman ===="  << endl;
        cout << "Input tanggal (DD-MM-YYYY): " ; cin >> info.tglpinjam;
        infopeminjam.tampilkanDaftarAnggota(); // tampil data anggota
        if(!infopeminjam.getDaftarAnggota().empty()){
            cout << "Input ID Anggota: "; cin >> info.idAnggota;
            infopeminjam = infopeminjam.getAnggotaById(info.idAnggota);

            cin.ignore();
        
            infobuku.tampilkanDaftarBuku();
            cout << "Input ID buku: " ; cin >> info.idBuku;
            infobuku = infobuku.getBukuById(info.idBuku);

            cin.ignore();

            info.tglDikembalikan = "-";
            info.id = dataPeminjaman.size() + 1; // menyimpan id peminjaman dg index data peminjamn
            info.sudahKembali = false; // simpan data buku sbg buku yg blm dikembalikan


            // jika stok buku tdk ada
            if(!infobuku.kurangiStock(info.idBuku)){
                system("cls");
                cout << "Peminjaman gagal!" << endl;
                cout << "Stok Buku Tidak Ada " << endl;
                return;
            } else{ // jk stok buku ada
                system("cls");
                cout << "Peminjaman berhasil!" << endl;
                // cetak informasi peminjaman
                cout << "=== Informasi Peminjaman ===\n" << endl;
                cout << "ID Peminjaman\t\t: " << info.id << endl;
                cout << "Tanggal Peminjaman\t: " << info.tglpinjam << endl;
                cout << endl;
                infopeminjam.tampilkanAnggota(); // cetak data peminjam
                cout << "\n" << endl;
                infobuku.tampilkanBuku(); // cetak data buku yg dipinjam
                dataPeminjaman.push_back(info); // tambah data peminjaman dr info ke vektor dataPeminjaman
            }
        }else{
            cout << "Peminjaman gagal!" << endl;
        }
    
        simpanKeFile(); // simpan data peminjaman ke file
    }
    

     void tampilDetailPeminjaman(){
        cout << "\n------------------------------------" << endl;
        cout << "ID Peminjaman\t\t: " << id << endl;
        cout << "Tanggal Peminjaman\t: " << tglpinjam << endl;
        cout << "ID Peminjam\t\t: " << idAnggota << endl;
        cout << "ID Buku\t\t\t: " << idBuku << endl;
        cout << "Batas Pengembalian\t: " << getTanggalKembali() << endl;
        cout << "------------------------------------" << endl;
       
       if(sudahKembali==true){
        cout << "Tanggal Dikembalikan\t: " << tglDikembalikan << endl;
        cout << "------------------------------------" << endl;
       }

        if (isTerlambat()) {
            int terlambat = lamaTerlambat();

            cout << "Telambat Mengembalikan " << terlambat << " Hari" << endl;
            cout << "Total Denda (" << terlambat << "*" << dendaPerHari << ")\t: "
                        << "Rp" << totalDenda() << endl;
            if(sudahBayar==true){
            cout << "------- Denda Sudah Dibayar --------" << endl;
            }else if(sudahBayar == false){
            cout << "------- Denda Belum Dibayar --------" << endl;
            }else{
            cout << "------------------------------------" << endl;
            }
        }
    }
    
    //catatan blm ada detail denda
    // fungsi utk menyimpan data peminjaman buku yg belum dikembalikan
    vector<Peminjaman> daftarBelumDikembalikan(){
        bacaDariFile();
        // vector utk menyimpan data peminjaman yg blm dikembalikn
        vector<Peminjaman> listBelumDikembalikan; 

        for(int x = 0; x < dataPeminjaman.size(); x++){
            if(!dataPeminjaman[x].sudahKembali){ // cek apakh oeminjaman sdh dikembalian
            // memasukan data peminjaman yg blm dikembalikan ke vector listBelumDikembalikan
                listBelumDikembalikan.push_back(dataPeminjaman[x]); 
            }

        }

        // cetak
            // jika tdk ada data buku
            if (dataPeminjaman.empty()) {
                system("cls");
                cout << "Tidak ada peminjaman dalam daftar!" << endl;
            } else { // jk ada
                system("cls");
                cout << "==== Daftar Peminjaman ====\n" << endl;
                for (int i = 0; i < listBelumDikembalikan.size(); i++) {
            
                    cout << "------------------------------------" << endl;
                    cout << "ID Peminjaman\t\t: " << listBelumDikembalikan[i].id << endl;
                    cout << "Tanggal Peminjaman\t: " << listBelumDikembalikan[i].tglpinjam << endl;
                    cout << "ID Peminjam\t\t: " << listBelumDikembalikan[i].idAnggota << endl;
                    cout << "ID Buku\t\t\t: " << listBelumDikembalikan[i].idBuku << endl;
                    cout << "Batas Pengembalian\t: " << listBelumDikembalikan[i].getTanggalKembali() << endl;
                    cout << "------------------------------------" << endl;

                        if (dataPeminjaman[i].isTerlambat() && dataPeminjaman[i].sudahBayar == false) {
                            int terlambat = dataPeminjaman[i].lamaTerlambat();

                            cout << "Telambat Mengembalikan " << terlambat << " Hari" << endl;
                            cout << "Total Denda (" << terlambat << "*" << dendaPerHari << ")\t: "
                            << "Rp" << dataPeminjaman[i].totalDenda() << endl;
                        }
                        cout << endl;
    
                }
            }
        // return vektor yg berisi data peminjamn yg blm dikembalikan
        return listBelumDikembalikan;
    }


    // fungsi utk mengembalikan buku
   void kembaliBuku() {
    // baca data dari file
    bacaDariFile();
    system("cls");
    // panggil fungsi yang mencetak data peminjaman yang belum dikembalikan
    daftarBelumDikembalikan();

    // jika tidak ada data peminjaman
    if (dataPeminjaman.empty()) {
        system("cls");
        cout << "Tidak ada peminjaman dalam daftar!" << endl;
        return;
    }

    cout << "Masukkan ID peminjaman yang ingin dikembalikan: ";
    int id;
    cin >> id;
    cin.ignore();

    // inisialisasi peminjamanKetemu dengan false
    bool peminjamanKetemu = false;
    // inisialisasi index dengan -1
    int index = -1;

    for (int i = 0; i < dataPeminjaman.size(); i++) {
        if (dataPeminjaman[i].id == id) {
            peminjamanKetemu = true; // ubah peminjamanKetemu menjadi true
            dataPeminjaman[i].sudahKembali = true;
            index = i; // simpan indeks peminjaman ke variabel index

            cout << "Tanggal kembali (DD-MM-YYYY): ";
            cin >> dataPeminjaman[i].tglDikembalikan;
            Buku().tambahStock(dataPeminjaman[i].idBuku); // tambah stok buku karena sudah kembali

            simpanKeFile();
            system("cls");
            cout << "Peminjaman berhasil dikembalikan!\n" << endl;
            cout << "==== Detail Pengembalian ====" << endl;
            dataPeminjaman[i].tampilDetailPeminjaman();
            cout << endl;

           if(dataPeminjaman[i].sudahBayar == false && dataPeminjaman[i].isTerlambat()){
            cout << "Silahkan bayar denda" << endl;
           }else{
            dataPeminjaman.erase(dataPeminjaman.begin() + index);
            cout << "Peminjaman selesai, data peminjaman berhasil dihapus!" << endl;
           }
            simpanKeFile(); // simpan data peminjaman terbaru (yang sudah terhapus) ke file

            break;
        }
    }

    if (!peminjamanKetemu) {
        system("cls");
        cout << "Peminjaman dengan ID tersebut tidak ditemukan!" << endl;
    }
}
    

    // fungsi utk membayar denda
    void bayarDenda() {
    // membaca datapemimjaman dr file
    bacaDariFile();
        // jk tdk ada data peminjaman
        if (dataPeminjaman.empty()) {
            system("cls");
            cout << "Tidak ada peminjaman dalam daftar!" << endl;
            return;
        } else { // jk ada
                system("cls");
                // cetak data daftar denda 
                cout << "==== Daftar Denda Peminjaman ====" << endl;
                bool adaDataDenda = false; // inisialisasi dgn false
                // // jk ada data denda
                for (int i = 0; i < dataPeminjaman.size(); i++) {
                    if(dataPeminjaman[i].isTerlambat() && dataPeminjaman[i].sudahBayar == false ){
                        // ubah mjd true
                        adaDataDenda = true;

                        dataPeminjaman[i].tampilDetailPeminjaman();

                        if(dataPeminjaman[i].sudahKembali == false){
                            cout << "Kembalikan buku sebelum membayar denda!" << endl;
                        cout << "---------------------------------------" << endl;

                        }
                    }
                }
                 // jk tdk ada data denda 
                if (adaDataDenda == false) {
                    cout << "Tidak ada data denda" << endl;
                }
               
            }

        int idPeminjaman;

        // jk ada data denda, mk bayar denda bs diproses
        for (int i = 0; i < dataPeminjaman.size(); i++) {
        if(dataPeminjaman[i].isTerlambat() && dataPeminjaman[i].sudahBayar == false && dataPeminjaman[i].sudahKembali == true){
        cout << "\nMasukkan ID Peminjaman yang akan dibayar: ";
        cin >> idPeminjaman;

            bool found = false; // inisialisasi false, utk mncari data peminjamn brdsrkn id pinjam

            // jk id sesuai maka ketemu
            if (dataPeminjaman[i].id == idPeminjaman) {
                found = true; // ubah mjd true
                int index = i; 
                
                // tampil data id yg dipilih
                system("cls");
                dataPeminjaman[i].tampilDetailPeminjaman();

                // input pembayaran
                int bayar;
                cout << "\nInput jumlah bayar: ";
                cin >> bayar;
                cin.ignore();
                
                // jk juml bayar > totaldenda mk ada uang kembalian
                if (bayar > dataPeminjaman[i].totalDenda()) {

                    dataPeminjaman[i].sudahBayar = true; // ubah sudahBayar jd true

                    system("cls");
                    cout << "Pembayaran Denda Berhasil!" << endl;
                    cout << "Uang Kembalian: " << bayar-dataPeminjaman[i].totalDenda() << endl;

                    dataPeminjaman[i].tampilDetailPeminjaman();

                    dataPeminjaman.erase(dataPeminjaman.begin() + index);
                    cout << "\nPeminjaman selesai, data peminjaman berhasil dihapus!" << endl;
                    simpanKeFile(); // simpan data peminjaman terbaru (yang sudah terhapus) ke file


                } else if(bayar == dataPeminjaman[i].totalDenda()){ // jk jml baayr pas

                    dataPeminjaman[i].sudahBayar = true; // ubah sudahBayar jd true

                    system("cls");
                    cout << "Pembayaran Denda Berhasil!" << endl;

                    dataPeminjaman[i].tampilDetailPeminjaman();

                    dataPeminjaman.erase(dataPeminjaman.begin() + index);
                    cout << "\nPeminjaman selesai, data peminjaman berhasil dihapus!" << endl;
                    simpanKeFile(); // simpan data peminjaman terbaru (yang sudah terhapus) ke file

                }
                else { // jk jml bayar kurang
                    cout << "Jumlah pembayaran tidak mencukupi!" << endl;
                    cout << "Pembayaran Denda Gagal!" << endl;
                }

                break;
            } // jk id peminjaman tdk sesuai
            if (!found) {
                system("cls");
                cout << "ID Peminjaman tidak ditemukan!" << endl;
            }
            }
        }

        // menyimpan data ke file
        simpanKeFile();
    }


    // fungsi utk mendapatkan data tgl kembali
    string getTanggalKembali() {
        std::istringstream dateStream(tglpinjam);
        int day, month, year;
        char delimiter1, delimiter2;

        if (!(dateStream >> day >> delimiter1 >> month >> delimiter2 >> year)) {
            // Error parsing the input string
            return tglpinjam;
        }

        day += lamaPinjam;
        // Handle month and year adjustments if needed
        while (day > 31) {
            if (month == 12) {
                month = 1;
                year++;
            } else {
                month++;
            }
            day -= 31;
        }

        // Reconstruct the updated date string
        std::ostringstream updatedDate;
        updatedDate << std::setfill('0') << std::setw(2) << day << '-' << std::setw(2) << month << '-' << year;

        return updatedDate.str();
}


    // fungsi utk mengecek keterlambatan apakah pengembalian melebihi batas peminjaman
    bool isTerlambat() {

        string tanggal;
        if(sudahKembali){
        // jika sudah kembali maka menggunakan tanggal dikemablikannya sebagai patokan
            tanggal = tglDikembalikan;
        }else{
            // jika belum pakai tanggal hari ini sebagai patokan
            std::time_t currentTime = std::time(nullptr);
            std::tm* currentDate = std::localtime(&currentTime);

            char buffer[11];
            std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", currentDate);
            tanggal = buffer;
        }

        // Parse the first date string
        std::istringstream date1Stream(tanggal);
        int day1, month1, year1;
        char delimiter1;

        if (!(date1Stream >> day1 >> delimiter1 >> month1 >> delimiter1 >> year1)) {
            // Error parsing the first date string
            return false;
        }

        // Parse the second date string
        std::istringstream date2Stream(getTanggalKembali());
        int day2, month2, year2;
        char delimiter2;

        if (!(date2Stream >> day2 >> delimiter2 >> month2 >> delimiter2 >> year2)) {
            // Error parsing the second date string
            return false;
        }

        // Compare the dates
        if (year1 > year2)
            return true;
        else if (year1 == year2 && month1 > month2)
            return true;
        else if (year1 == year2 && month1 == month2 && day1 > day2)
            return true;

        return false;
    }


    // fungsi utk menghitung durasi keterlambatan (hari)
    int lamaTerlambat() {
        string tanggal;
        if(sudahKembali){
        // jika sudah kembali maka menggunakan tanggal dikemablikannya sebagai patokan
            tanggal = tglDikembalikan;
            // tanggal = "25-06-2023";     
        } else {
            // jika belum pakai tanggal hari ini sebagai patokan
            std::time_t currentTime = std::time(nullptr);
            std::tm* currentDate = std::localtime(&currentTime);

            char buffer[11];
            std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", currentDate);
            tanggal = buffer;
            // tanggal = "25-06-2023";
        }

            std::tm date1 = {};
            std::tm date2 = {};

            std::istringstream(tanggal.substr(0, 2)) >> date1.tm_mday;
            std::istringstream(tanggal.substr(3, 2)) >> date1.tm_mon;
            std::istringstream(tanggal.substr(6, 4)) >> date1.tm_year;
            date1.tm_mon -= 1;
            date1.tm_year -= 1900;

            std::istringstream(getTanggalKembali().substr(0, 2)) >> date2.tm_mday;
            std::istringstream(getTanggalKembali().substr(3, 2)) >> date2.tm_mon;
            std::istringstream(getTanggalKembali().substr(6, 4)) >> date2.tm_year;
            date2.tm_mon -= 1;
            date2.tm_year -= 1900;

            std::time_t time1 = std::mktime(&date1);
            std::time_t time2 = std::mktime(&date2);

            const auto tp1 = std::chrono::system_clock::from_time_t(time1);
            const auto tp2 = std::chrono::system_clock::from_time_t(time2);
            const auto duration = tp2 - tp1;
            const auto days = std::chrono::duration_cast<std::chrono::hours>(duration).count() / 24;

            return static_cast<int>(days) * -1;
    }


    // fungsi utk menghitung total denda
    int totalDenda() {
        return lamaTerlambat() * dendaPerHari;
    }
    

    // fungsi utk menampilkan data peminjaman
    void tampilkanDaftarPeminjaman() {
            bacaDariFile();
            if (dataPeminjaman.empty()) {
                system("cls");
                cout << "Tidak ada peminjaman dalam daftar!" << endl;
            } else {
                system("cls");
                cout << "==== Daftar Peminjaman ====" << endl;
                for (int i = 0; i < dataPeminjaman.size(); i++) {
                    if(dataPeminjaman[i].sudahKembali == false &&  dataPeminjaman[i].sudahBayar == false){
                   dataPeminjaman[i].tampilDetailPeminjaman();
                    }

                    
                    if (dataPeminjaman[i].sudahKembali && dataPeminjaman[i].isTerlambat() &&  dataPeminjaman[i].sudahBayar == false) {
                        dataPeminjaman[i].tampilDetailPeminjaman();
                        cout << endl;
                    }
                }
                
            }
        }


    // fungsi utk menyimpan data ke file
    void simpanKeFile(){
        // buka file
        ofstream file(namaFile);

        // jika file gagal dibuka
        if (!file){
            cout << "Gagal membuka file!" << endl;
            return;
        }

        // proses menyimpan data buku dari vektor 'dataPeminjaman' ke dalam file
        for (const Peminjaman &info : dataPeminjaman)
        {
            file << info.id << endl;
            file << info.idAnggota << endl;
            file << info.idBuku << endl;
            file << info.tglpinjam << endl;
            file << info.lamaPinjam << endl;
            file << info.tglDikembalikan << endl;
            file << info.sudahKembali << endl;
            file << info.sudahBayar << endl;
        }

        file.close(); // menutup file
    }


    // fungsi utk membaca data dari file
    void bacaDariFile(){
        // kamus lokal
        string tglPinjam,tglDikembalikan,lama,id_anggota,id_buku,sudahKembali,sudahBayar;
        int id_peminjaman;
        Peminjaman info; //'info' sbg objek peminjaman 

        // membuka file
        ifstream file(namaFile);

        // jika gagal membuka file
        if (!file){
            system("cls");
            cout << "Gagal membuka file!" << endl;
            return;
        }

        // hapus data buku dalam vektor daftarPeminjaman
        // utk memastikan vektor daftarPeminjaman hanya berisi data dalam file
        dataPeminjaman.clear();

        // mproses membaca data dr file
        while (file >> id_peminjaman){
            getline(file >> ws, id_anggota);
            getline(file >> ws, id_buku);
            getline(file >> ws, tglPinjam);
            getline(file >> ws, lama);
            getline(file >> ws, tglDikembalikan);
            getline(file >> ws, sudahKembali);
            getline(file >> ws, sudahBayar);



            
            info.id = id_peminjaman;
            info.idAnggota = stoi(id_anggota);
            info.idBuku = stoi(id_buku);
            info.tglpinjam = tglPinjam;
            info.lamaPinjam = stoi(lama);
            info.tglDikembalikan = tglDikembalikan;
            if(sudahKembali == "1"){
                info.sudahKembali = true;
            } else{
                info.sudahKembali = false;
            }

            if (sudahBayar == "1") {
            info.sudahBayar = true;
            } else {
                info.sudahBayar = false;
            }

        // menambahkan data peminjaman dari 'info' ke dalam vektor daftarPeminjaman
            dataPeminjaman.push_back(info);
        }

        file.close(); // menutup file
    }

};