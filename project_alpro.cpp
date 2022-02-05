#include <iostream>
#include <stdlib.h>
#include <iomanip>
using namespace std;

//! BACA ITEM BARANG
void baca_item_barang()
{
    struct DetailBarang
    {
        char kode_barang[5];
        char nama_barang[20];
        int harga_barang;
    };

    FILE *file_item_barang;
    file_item_barang = fopen("data_item_barang.txt", "r");

    DetailBarang brg_baca;

    system("cls");
    cout << right << setw(28) << "\04\04\04\04\04\04\04\04-Data Item Barang-\04\04\04\04\04\04\04\04\n";
    cout << left << setw(4) << "No";
    cout << setw(8) << "Kode";
    cout << setw(15) << "Nama";
    cout << " " << "Harga" << endl;

    int no_baris = 1;

    while (fread(&brg_baca, sizeof(brg_baca), 1, file_item_barang))
    {
        cout << left << setw(4) << no_baris;
        cout << setw(8) << brg_baca.kode_barang;
        cout << setw(15) << brg_baca.nama_barang;
        cout << " " << brg_baca.harga_barang << endl;

        no_baris++;
    }
    cout << endl;
    fclose(file_item_barang);
}

//! PROSES ITEM BARANG
void proses_item_barang()
{
    int opsi_1;

ulang_menu_item_barang:
    cout << "\04\04~MANAJEMEN ITEM BARANG~\04\04\n";
    cout << "\04 " << "1.Menambah Barang       \04\n";
    cout << "\04 " << "2.Mengubah Barang       \04\n";
    cout << "\04 " << "3.Menghapus Barang      \04\n";
    cout << "\04 " << "4.Melihat Barang        \04\n";
    cout << "\04 " << "5.Kembali               \04\n";
    cout << "Input angka opsi >> ";
    cin >> opsi_1;

    system("cls");

    FILE *file_item_barang;

    struct DetailBarang
    {
        char kode_barang[5];
        char nama_barang[20];
        int harga_barang;
    };

    //? digunakan case 1
    int jumlah_barang_masuk;

    // ? digunakan case 2
    int baris_diubah, banyak_perubahan, banyak_penghapusan, baris_dihapus;

    //? digunakan case 3
    char kode_barang[5], nama_barang[20];
    double harga_barang;

    switch (opsi_1)
    {
    //? menambah barang
    case 1:

        baca_item_barang();

        file_item_barang = fopen("data_item_barang.txt", "a+");

        cout << "\nJumlah barang yang masuk >> ";
        cin >> jumlah_barang_masuk;

        if (file_item_barang == NULL)
        {
            cout << "data_item_barang.txt gagal terbentuk\n";
        }
        else
        {
            //* loop detail barang masuk selama jmlah barangnya
            for (int idx = 0; idx < jumlah_barang_masuk; idx++)
            {
                DetailBarang brg;

                cout << "\nBarang ke-" << idx + 1 << endl;
                cout << "Kode Barang  : ";
                cin >> brg.kode_barang;
                cin.ignore();
                cout << "Nama Barang  : ";
                cin.get(brg.nama_barang, 20);
                cout << "Harga Barang : ";
                cin >> brg.harga_barang;

                fwrite(&brg, sizeof(brg), 1, file_item_barang);
                cout << "~~~Barang sukses ditambahkan~~~\n";
            }

            fclose(file_item_barang);
        }
        baca_item_barang();
        goto ulang_menu_item_barang;

    //? mengubah barang
    case 2:
        baca_item_barang();

        cout << "\nBerapa kali perubahan >> ";
        cin >> banyak_perubahan;

        for (int idx = 0; idx < banyak_perubahan; idx++)
        {
            // todo update and read mode
            file_item_barang = fopen("data_item_barang.txt", "r+");

            DetailBarang brg_baru;

            cout << "\nPerubahan ke-" << idx + 1 << endl;

            cout << "Nomor baris yang diubah >> ";
            cin >> baris_diubah;
            baris_diubah = baris_diubah - 1;

            cout << "\nKode Barang  : ";
            cin >> brg_baru.kode_barang;
            cin.ignore();
            cout << "Nama Barang  : ";
            cin.get(brg_baru.nama_barang, 20);
            cout << "Harga Barang : ";
            cin >> brg_baru.harga_barang;

            DetailBarang brg_buffer;

            fseek(file_item_barang, baris_diubah * sizeof(brg_buffer), SEEK_SET);
            fwrite(&brg_baru, sizeof(brg_baru), 1, file_item_barang);

            system("cls");
            fclose(file_item_barang);
            baca_item_barang();

            cout << "\n~~Update item barang berhasil~~\n";
        }

        baca_item_barang();
        goto ulang_menu_item_barang;

    //? menghapus barang
    case 3:
        baca_item_barang();

        cout << "\nBerapa kali penghapusan >> ";
        cin >> banyak_penghapusan;

        //*proses update data kosong
        for (int idx = 0; idx < banyak_penghapusan; idx++)
        {
            file_item_barang = fopen("data_item_barang.txt", "r+");

            cout << "Penghapusan ke-" << idx + 1 << endl;

            cout << "\nNomor baris yang dihapus >> ";
            cin >> baris_dihapus;
            baris_dihapus = baris_dihapus - 1;

            DetailBarang brg_buffer;
            DetailBarang brg_kosong = {"", "", 0};

            fseek(file_item_barang, baris_dihapus * sizeof(brg_buffer), SEEK_SET);
            fwrite(&brg_kosong, sizeof(brg_kosong), 1, file_item_barang);

            system("cls");
            fclose(file_item_barang);

            cout << "\n~~Hapus item barang berhasil~~\n";
            baca_item_barang();
        }

        goto ulang_menu_item_barang;

    //? lihat barang
    case 4:
        baca_item_barang();
        goto ulang_menu_item_barang;

    // ?kembali ke menu utama
    case 5:
        break;

    default:
        cout << "\n!!!INPUT ANGKA OPSI YANG ADA!!!\n";
        goto ulang_menu_item_barang;
    }
}


//! TRANSAKSI BARANG
void transaksi_barang()
{
    int opsi, no_baris;

    struct DataPengadaan
    {
        char id_pengadaan[5];
        char kode_barang[5];
        char nama_barang[20];
        int jumlah_barang;
    };

    struct DetailBarang
    {
        char kode_barang[5];
        char nama_barang[20];
        int harga_barang;
    };

    struct DataPembelian
    {
        char id_pembelian[5];
        char nama_barang[20];
        int jumlah_barang;
    };

    //? variabel yang dipakai di case 1
    string daftar_nama_brg[100];
    int index;
    bool ada_di_item_brg;
    int banyak_pengadaan;

ulang_menu_transaksi:
    cout << "\04\04\04\04\04\04\04\04\04\04~TRANSAKSI BARANG~\04\04\04\04\04\04\04\04\04\04\n";
    cout << "\04 " << "1.Pengadaan Barang                 \04\n";
    cout << "\04 " << "2.Pembelian Barang                 \04\n";
    cout << "\04 " << "3.Tampilkan Data Pengadaan Barang  \04\n";
    cout << "\04 " << "4.Tampilkan Data Pembelian Barang  \04\n";
    cout << "\04 " << "5.Kembali                          \04\n";

    cout << "Input Angka Opsi >> ";
    cin >> opsi;

    switch (opsi)
    {
    //? pengadaan barang
    case 1:
        FILE *file_item_barang;
        file_item_barang = fopen("data_item_barang.txt", "r");

        FILE *file_pengadaan;
        file_pengadaan = fopen("pengadaan.txt", "a+");

        DetailBarang brg;
        index = 0;

        while (fread(&brg, sizeof(brg), 1, file_item_barang))
        {
            daftar_nama_brg[index] = brg.nama_barang;
            index++;
        }

        system("cls");
        cout << "berapa banyak barang yang ingin diadakan : ";
        cin >> banyak_pengadaan;

        DataPengadaan brg_baru;

        cout << "ID Pengadaan         : ";
        cin >> brg_baru.id_pengadaan;

        for (int barang = 0; barang < banyak_pengadaan; barang++)
        {
            ada_di_item_brg = false;
            cin.ignore();
            cout << "\nBarang ke-" << barang + 1 << endl;
            cout << "Masukkan nama barang : ";
            cin.get(brg_baru.nama_barang, 20);

            for (int idx = 0; idx < index; idx++)
            {
                if (brg_baru.nama_barang == daftar_nama_brg[idx])
                {
                    cout << "Kode Barang          : ";
                    cin >> brg_baru.kode_barang;
                    cout << "Jumlah Barang        : ";
                    cin >> brg_baru.jumlah_barang;

                    ada_di_item_brg = true;

                    fwrite(&brg_baru, sizeof(brg_baru), 1, file_pengadaan);
                    system("cls");
                }
            }

            if (not ada_di_item_brg)
            {
                cout << "\n!!!Tidak bisa diadakan karena tidak ada di item barang!!!" << endl;
            }
        }

        fclose(file_item_barang);
        fclose(file_pengadaan);
        goto ulang_menu_transaksi;

    //? pembelian barang
    case 2:
        int banyak_pembelian;

        FILE *file_pembelian;
        file_pembelian = fopen("data_pembelian.txt", "a+");

        system("cls");
        cout << "Banyak Pembelian >> ";
        cin >> banyak_pembelian;

        if (file_pembelian == NULL){
            cout << "\nfile data_pembelian.txt gagal terbentuk";
        }
        else
        {
            DataPembelian brg_dibeli;

            cout << "\nID Pembelian : ";
            cin >> brg_dibeli.id_pembelian;

            no_baris = 1;

            // *write data pembelian ke file selama banyak pembelian
            for (int idx = 0; idx < banyak_pembelian; idx++)
            {
                cout << "\nBarang ke-" << no_baris << endl;
                cin.ignore();
                cout << "Nama Barang   : ";
                cin.get(brg_dibeli.nama_barang, 20);
                cout << "Jumlah Barang : ";
                cin >> brg_dibeli.jumlah_barang;

                fwrite(&brg_dibeli, sizeof(brg_dibeli), 1, file_pembelian);
                no_baris++;

                system("cls");
            }
            fclose(file_pembelian);
        }
        goto ulang_menu_transaksi;

    // ? Menampilkan Data Pengadaan
    case 3:
        FILE *file_lihat_pengadaan;
        file_lihat_pengadaan = fopen("pengadaan.txt", "r");

        DataPengadaan baca_data;

        system("cls");
        cout << "==================Data Pengadaan Barang=================\n";
        cout << left << setw(4) << "No";
        cout << setw(15) << "Id_pengadaan";
        cout << setw(15) << "Kode_barang";
        cout << setw(15) << "Nama_barang";
        cout << " " << "Jumlah" << endl;

        no_baris = 1;

        while(fread(&baca_data, sizeof(baca_data), 1, file_lihat_pengadaan))
        {
            cout << left << setw(4) << no_baris;
            cout << setw(15) << baca_data.id_pengadaan;
            cout << setw(15) << baca_data.kode_barang;
            cout << setw(15) << baca_data.nama_barang;
            cout << " " << baca_data.jumlah_barang << endl;

            no_baris++;
        }
        fclose(file_lihat_pengadaan);
        cout << endl;
        goto ulang_menu_transaksi;

    // ?menampilkan data pembelian
    case 4:
        FILE *file_lihat_pembelian;
        file_lihat_pembelian = fopen("data_pembelian.txt", "r");

        DataPembelian lihat_data;

        system("cls");
        cout << "==========Data Pembelian Barang==========\n";
        cout << left << setw(4) << "No";
        cout << setw(15) << "ID Pembelian";
        cout << setw(15) << "Nama Barang";
        cout << " " << "Jumlah" << endl;

        no_baris = 1;

        while (fread(&lihat_data, sizeof(lihat_data), 1, file_lihat_pembelian))
        {
            cout << left << setw(4) << no_baris;
            cout << setw(15) << lihat_data.id_pembelian;
            cout << setw(15) << lihat_data.nama_barang;
            cout << " " << lihat_data.jumlah_barang << endl;

            no_baris++;
        }
        fclose(file_lihat_pembelian);
        cout << endl;
        goto ulang_menu_transaksi;

    case 5:
        system("cls");
        break;

    default:
        system("cls");
        cout << "\n!!!INPUT ANGKA OPSI YANG ADA!!!\n";
        goto ulang_menu_transaksi;
    }
}



void selectionSortAscending(int array[], int len)
{
    int idx_max, wadah;

    for (int batas_kiri = 0; batas_kiri < len - 1; batas_kiri++)
    {
        idx_max = batas_kiri;

        for (int idx_content_compare = batas_kiri + 1; idx_content_compare < len; idx_content_compare++)
        {
            if (array[idx_content_compare] < array[idx_max])
                {
                    idx_max = idx_content_compare;
                }
        }
        if (idx_max != batas_kiri)
        {
            wadah = array[batas_kiri];

            array[batas_kiri] = array[idx_max];

            array[idx_max] = wadah;
        }
    }
}


void selectionSortDescending(int array[], int len)
{
    int idx_max, wadah;

    for (int batas_kiri = 0; batas_kiri < len - 1; batas_kiri++)
    {
        idx_max = batas_kiri;

        for (int idx_content_compare = batas_kiri + 1; idx_content_compare < len; idx_content_compare++)
        {
            if (array[idx_content_compare] > array[idx_max])
            {
                idx_max = idx_content_compare;
            }
        }
        if (idx_max != batas_kiri)
        {
            wadah = array[batas_kiri];

            array[batas_kiri] = array[idx_max];

            array[idx_max] = wadah;
        }
    }
}



//! FITUR LAINNYA
void fitur_lainnya()
{
    int opsi;

    //? case 1
    int banyak_brg_before_sort[100] = {};
    int banyak_brg_after_sort[100] = {};
    int index_baris[100] = {};
    int index = 0;
    int no_baris;

    // ?case 2
    string key;
    bool ditemukan;

    FILE *file_pembelian;

    struct DataPembelian
    {
        char id_pembelian[5];
        char nama_barang[20];
        int jumlah_barang;
    };

ulang_fitur_lainya:
    cout << "\04\04\04\04\04\04\04\04\04\04\04\04\04\04\04\04\04\04\04~FITUR LAINNYA~\04\04\04\04\04\04\04\04\04\04\04\04\04\04\04\04\04\04\04\04\04" << endl;
    cout << "\04 " << "1.Tampilkan Data Pembelian Sort by Jumlah Belanja   \04\n";
    cout << "\04 " << "2.Mencari Data Pembelian Barang dengan ID Pembelian \04\n";
    cout << "\04 " << "3.Kembali                                           \04\n";
    cout << "Masukkan Angka opsi >> ";
    cin >> opsi;

    switch (opsi)
    {
    case 1:
        int opsi_sort;

ulang_menu_sort:
        system("cls");
        cout << "  Sort by ?\n";
        cout << "1.Ascending\n";
        cout << "2.Descending\n";
        cout << "Masukkan Angka Opsi >> ";
        cin >> opsi_sort;

        file_pembelian = fopen("data_pembelian.txt", "r");

        DataPembelian brg;

        //? menyimpan banyak barang di 2 array
        while (fread(&brg, sizeof(brg), 1, file_pembelian))
        {
            banyak_brg_before_sort[index] = brg.jumlah_barang;
            banyak_brg_after_sort[index] = brg.jumlah_barang;
            index++;
        }

        if (opsi_sort == 1)
        {
            selectionSortAscending(banyak_brg_after_sort, index);
        }
        else if(opsi_sort == 2)
        {
            selectionSortDescending(banyak_brg_after_sort, index);
        }
        else{
            system("cls");
            goto ulang_menu_sort;
        }

        //? suatu angka banyak barang ada di baris keberapa si tadinya
        // ?for pertama meloping index dari index array banyak_brg_after_sort
        for (int idx_after = 0; idx_after < index; idx_after++)
        {
            // ?for pertama meloping index dari index array banyak_brg_before_sort
            for (int idx_before = 0; idx_before < index; idx_before++)
            {
                //?mencari nomor index baris yang sesuai dengan array banyak_brg_after_sort
                if (banyak_brg_after_sort[idx_after] == banyak_brg_before_sort[idx_before])
                {
                    index_baris[idx_after] = idx_before;
                }
            }
        }

        DataPembelian brg_buffer;

        system("cls");
        cout << "==========Data Pembelian Barang==========\n";
        cout << left << setw(4) << "No";
        cout << setw(15) << "ID Pembelian";
        cout << setw(15) << "Nama Barang";
        cout << " " << "Jumlah" << endl;

        no_baris = 1;

        for (int idx = 0; idx < index; idx++)
        {
            fseek(file_pembelian, index_baris[idx] * sizeof(brg_buffer), SEEK_SET);
            fread(&brg, sizeof(brg), 1, file_pembelian);
            cout << left << setw(4) << no_baris;
            cout << setw(15) << brg.id_pembelian;
            cout << setw(15) << brg.nama_barang;
            cout << " " << brg.jumlah_barang << endl;

            no_baris++;
        }
        fclose(file_pembelian);
        cout << endl;
        cin.ignore();
        break;

    case 2:
        file_pembelian = fopen("data_pembelian.txt", "r");

        DataPembelian barang;

        //* tujuannya untuk tahu berapa baris indexnya
        while (fread(&barang, sizeof(barang), 1, file_pembelian))
        {
            index++;
        }

        system("cls");
        cout << "Input ID Pembelian : ";
        cin >> key;
        system("cls");

        cout << "==========Data Pembelian Barang==========\n";
        cout << left << setw(4) << "No";
        cout << setw(15) << "ID Pembelian";
        cout << setw(15) << "Nama Barang";
        cout << " " << "Jumlah" << endl;

        no_baris = 1;

        for (int idx = 0; idx < index; idx++)
        {
            fseek(file_pembelian, idx * sizeof(barang), SEEK_SET);
            fread(&barang, sizeof(barang), 1, file_pembelian);

            if(key == barang.id_pembelian)
            {
                cout << left << setw(4) << no_baris;
                cout << setw(15) << barang.id_pembelian;
                cout << setw(15) << barang.nama_barang;
                cout << " " << barang.jumlah_barang << endl;

                no_baris++;
                ditemukan = true;
            }

        }
        if (not ditemukan)
        {
            system("cls");
            cout << "!!!Barang dengan ID tersebut tidak ditemukan!!!";
        }

        fclose(file_pembelian);
        cout << endl;
        break;

    case 3:
        system("cls");
        break;

    default:
        system("cls");
        cout << "\n!!!INPUT ANGKA OPSI YANG ADA!!!\n";
        goto ulang_fitur_lainya;
    }
}



//! FLOW UTAMA
int main()
{
    system("cls");

    //? opsi menu utama
    int opsi;

ulang_menu:
    cout << "\04\04~SISTEM INVENTORI BARANG~\04\04\n";
    cout << "\04 " << "1.Item Barang             \04" << endl;
    cout << "\04 " << "2.Transaksi Barang        \04" << endl;
    cout << "\04 " << "3.Fitur Lainnya           \04" << endl;
    cout << "\04 " << "4.Info Developer          \04" << endl;
    cout << "\04 " << "5.Exit                    \04" << endl;
    cout << "Input angka opsi >> ";
    cin >> opsi;

    system("cls");

    switch (opsi)
    {
    case 1:
        proses_item_barang();
        goto ulang_menu;

    case 2:
        transaksi_barang();
        goto ulang_menu;

    case 3:
        fitur_lainnya();
        goto ulang_menu;

    case 4:
        cout << "~~~~~~~~~~~~~Developer~~~~~~~~~~~~" << endl;
        cout << "1.The member of team | *******" << endl;
        cout << "2.The member of team | *******" << endl;
        cout << "3.The member of team | *******" << endl;
        cout << "4.The member of team | *******" << endl;
        cout << "5.The member of team | *******" << endl << endl;
        goto ulang_menu;

    case 5:
        // ? /06 kode unicode diamond
        cout << setw(30) << "\06\06\06\06Program Berhenti\06\06\06\06";
        break;

    default:
        cout << "\n!!!INPUT ANGKA OPSI YANG ADA!!!\n";
        goto ulang_menu;
    }

    return 0;
}