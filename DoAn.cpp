#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include<algorithm>
#include <vector>   
#include <map>      
#include <climits>
using namespace std;
#define MAX_CARS 100
#define CYAN    "\033[36m"      
#define BOLD    "\033[1m"      
void xoaManHinh() {
    #ifdef _WIN32
        system("cls");  
    #else
        system("clear");
    #endif
}
struct Car {
    int id;
    char brand[50];
    char model[50];
    char fuel[20];
    int horsepower;
    double price;
    char status[20];  
};



void toUpperString(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}


int nhapSoNguyen(const string& message) {
    int number;
    cout << message;
    while (!(cin >> number) || number <= 0) {
        cout << ">> Lỗi: Vui lòng nhập lại số nguyên dương: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return number;
}


double nhapSoThuc(const string& message) {
    double number;
    cout << message;
    while (!(cin >> number) || number <= 0) {
        cout << ">> Lỗi: Vui lòng nhập lại số dương: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return number;
}

void nhapChuoi(const string& message, char* str, int size) {
    cout << message;
    if (cin.peek() == '\n') cin.ignore(); 
    cin.getline(str, size);
}

int timViTriTheoID(Car carList[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (carList[i].id == id) {
            return i;
        }
    }
    return -1;
}



void inTieuDeBang() {
    cout << string(95, '-') << endl;
    cout << "| " << left << setw(5) << "ID" 
         << "| " << setw(14) << "Hãng xe" 
         << "| " << setw(14) << "Model" 
         << "| " << setw(12) << "Nhiên liệu"
         << "| " << setw(10) << "Mã lực"
         << "| " << setw(14) << "Giá (VND)" 
         << "| " << setw(12) << "Trạng Thái" << "|\n";
    cout << string(95, '-') << endl;
}

void inThongTinXe(Car c) {
    cout << "| " << left << setw(5) << c.id 
         << "| " << setw(14) << c.brand
         << "| " << setw(14) << c.model
         << "| " << setw(12) << c.fuel
         << "| " << setw(10) << c.horsepower
         << "| " << setw(14) << fixed << setprecision(0) << c.price
         << "| " << setw(12) << c.status << "|\n";
}

void luuFile(Car carList[], int count, const char* filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Không thể mở file để lưu dữ liệu!\n";
        return;
    }
    
    for (int i = 0; i < count; i++) {
        file << carList[i].id << ","
             << carList[i].brand << ","
             << carList[i].model << ","
             << carList[i].fuel << ","
             << carList[i].horsepower << ","
             << fixed << setprecision(0) << carList[i].price << ","
             << carList[i].status << "\n";
    }
    file.close(); 
}

void docFile(Car carList[], int &count, const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        count = 0; return;
    }
    
    count = 0;
    string line;
    while (getline(file, line) && count < MAX_CARS) {
        if (line.empty()) continue;
        stringstream ss(line);
        string token;
        Car car;
        if(getline(ss, token, ',')) car.id = stoi(token);
        if(getline(ss, token, ',')) strcpy(car.brand, token.c_str());
        if(getline(ss, token, ',')) strcpy(car.model, token.c_str());
        if(getline(ss, token, ',')) strcpy(car.fuel, token.c_str());
        if(getline(ss, token, ',')) car.horsepower = stoi(token);
        if(getline(ss, token, ',')) car.price = stod(token);
        if(getline(ss, token, ',')) strcpy(car.status, token.c_str());
        
        carList[count++] = car;
    }
    file.close();
    cout << ">> Đã tải " << count << " xe từ file.\n";
}



void themXe(Car carList[], int &count) {
    if (count >= MAX_CARS) {
        cout << ">> Danh sách đã đầy!\n";
        return;
    }
    
    cout << "\n--- THÊM XE MỚI ---\n";
    Car newCar;

   
    do {
        newCar.id = nhapSoNguyen("Hãy nhập ID (số nguyên duy nhất): ");
        if (timViTriTheoID(carList, count, newCar.id) != -1) {
            cout << ">> ID đã tồn tại, hãy nhập ID khác.\n";
        } else {
            break;
        }
    } while (true);
    
    nhapChuoi("Hãng xe: ", newCar.brand, 50);
    nhapChuoi("Model: ", newCar.model, 50);
    nhapChuoi("Nhiên liệu (Xăng/Dầu/Điện): ", newCar.fuel, 20);
    newCar.horsepower = nhapSoNguyen("Mã lực (HP): ");
    newCar.price = nhapSoThuc("Giá (VND): ");
    nhapChuoi("Trạng thái (Còn hàng/Đã bán): ", newCar.status, 20);

    carList[count++] = newCar;
    luuFile(carList, count, "data_xe.txt");
    cout << ">> Đã thêm xe thành công!\n";
}

void xemDanhSach(Car carList[], int count) {
    cout << "\n--- DANH SÁCH XE ---\n";
    if (count == 0) {
        cout << "Danh sách trống!\n";
        return;
    }
    
    inTieuDeBang();
    for (int i = 0; i < count; i++) {
        inThongTinXe(carList[i]);
    }
    cout << string(95, '-') << endl;
    cout << "Trong kho hiện đang có " << count << " xe\n";
}

void suaXe(Car carList[], int count) {
    if (count == 0) { cout << "Danh sách trống!\n"; return; }

    int id = nhapSoNguyen("\nNhập ID xe cần sửa: ");
    int index = timViTriTheoID(carList, count, id);
    
    if (index == -1) {
        cout << ">> Không tìm thấy xe ID " << id << endl;
        return;
    }
    
   
    cout << "\nTHONG TIN HIEN TAI:\n";
    cout << "1. Hãng xe: " << carList[index].brand << endl;
    cout << "2. Model: " << carList[index].model << endl;
    cout << "3. Nhiên liệu: " << carList[index].fuel << endl;
    cout << "4. Mã lực: " << carList[index].horsepower << " HP" << endl;
    cout << "5. Giá (VND): " << (long long)carList[index].price << " VND" << endl;
    cout << "6. Trạng thái: " << carList[index].status << endl;
    
    
    int choice;
    cout << "\nChọn mục muốn sửa (chọn 1 đến 6 để sửa, 0 để hủy): ";
    if (!(cin >> choice)) choice = 0;
    
    if (choice == 0) { cout << "Đã hủy thao tác.\n"; return; }

    switch (choice) {
        case 1: nhapChuoi("Nhập hãng xe mới: ", carList[index].brand, 50); break;
        case 2: nhapChuoi("Nhập model mới: ", carList[index].model, 50); break;
        case 3: nhapChuoi("Nhap nhiên liệu mới: ", carList[index].fuel, 20); break;
        case 4: carList[index].horsepower = nhapSoNguyen("Nhập mã lực mới: "); break;
        case 5: carList[index].price = nhapSoThuc("Nhập giá mới: "); break;
        case 6: nhapChuoi("Nhập trạng thái mới: ", carList[index].status, 20); break;
        default: cout << "Lựa chọn không hợp lệ!\n"; return;
    }
    
    luuFile(carList, count, "data_xe.txt");
    cout << ">> Cập nhật thành công!\n";
}

void xoaXe(Car carList[], int &count) {
    if (count == 0) { cout << "Danh sách trống!\n"; return; }

    int id = nhapSoNguyen("\nNhập ID xe cần xóa: ");
    int index = timViTriTheoID(carList, count, id);
    
    if (index == -1) {
        cout << ">> Không tìm thấy ID xe " << id << endl;
        return;
    }
    
    cout << "Bạn chắc chắn muốn xóa xe [" << carList[index].brand << " " << carList[index].model << "]? (y/n): ";
    char confirm; cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        for (int i = index; i < count - 1; i++) {
            carList[i] = carList[i + 1];
        }
        count--;
        luuFile(carList, count, "data_xe.txt");
        cout << ">> Đã xóa xe!\n";
    } else {
        cout << ">> Đã hủy xóa.\n";
    }
}

void timKiemXe(Car carList[], int count) {
    if (count == 0) { cout << "Danh sách trống!\n"; return; }
    
    cout << "\n--- TÌM KIẾM XE ---\n";
    cout << "1. Tìm theo ID\n";
    cout << "2. Tìm theo hãng xe\n";
    cout << "3. Tìm theo khoảng giá\n";
    cout << "4. Tìm theo trạng thái\n";
    int choice = nhapSoNguyen("Chọn phương thức (1-4): ");
    
    bool found = false;
    int foundCount = 0;
    
  
    
    switch (choice) {
        case 1: { 
            int id = nhapSoNguyen("Nhập ID xe cần tìm: ");
            int idx = timViTriTheoID(carList, count, id);
            if (idx != -1) {
                inTieuDeBang();
                inThongTinXe(carList[idx]);
                found = true; foundCount++;
            }
            break;
        }
        case 2: { 
            char keyword[50];
            nhapChuoi("Nhập tên hãng xe: ", keyword, 50);
            toUpperString(keyword); 
            
            inTieuDeBang();
            for (int i = 0; i < count; i++) {
                char tempBrand[50];
                strcpy(tempBrand, carList[i].brand);
                toUpperString(tempBrand); 
                
                if (strstr(tempBrand, keyword) != NULL) {
                    inThongTinXe(carList[i]);
                    found = true; foundCount++;
                }
            }
            break;
        }
        case 3: { 
            double minP = nhapSoThuc("Giá thấp nhất: ");
            double maxP = nhapSoThuc("Giá cao nhất: ");
            if (minP > maxP) swap(minP, maxP);
            
            inTieuDeBang();
            for (int i = 0; i < count; i++) {
                if (carList[i].price >= minP && carList[i].price <= maxP) {
                    inThongTinXe(carList[i]);
                    found = true; foundCount++;
                }
            }
            break;
        }
        case 4: { 
            char keyword[20];
            nhapChuoi("Nhập trạng thái: ", keyword, 20);
            toUpperString(keyword);
            
            inTieuDeBang();
            for (int i = 0; i < count; i++) {
                char tempStatus[20];
                strcpy(tempStatus, carList[i].status);
                toUpperString(tempStatus);
                
                if (strstr(tempStatus, keyword) != NULL) { 
                    inThongTinXe(carList[i]);
                    found = true; foundCount++;
                }
            }
            break;
        }
        default:
            cout << "Lựa chọn không hợp lệ!\n";
            return;
    }
    
    if (found) cout << ">> Tìm thấy " << foundCount << " xe phù hợp.\n";
    else cout << ">> Không tìm thấy xe nào.\n";
}


void quanlyXe() {
    Car carList[MAX_CARS];
    int count = 0; 
    docFile(carList, count, "data_xe.txt");
    int choice;
    do {
        cout << "\n========================================\n";
        cout << "        QUẢN LÝ XE\n";
        cout << "========================================\n";
        cout << "[1]. Thêm xe mới\n";
        cout << "[2]. Xem danh sách xe\n";
        cout << "[3]. Sửa thông tin xe\n";
        cout << "[4]. Xóa xe\n";
        cout << "[5]. Tìm kiếm xe\n";
        cout << "[6]. Lưu dữ liệu\n";
        cout << "[0]. Quay lại console\n";
        cout << "Nhập lựa chọn: ";
        
       
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(1000, '\n');
            choice = -1;
        }
        
        switch (choice) {
            case 1: themXe(carList, count); break;
            case 2: xemDanhSach(carList, count); break;
            case 3: suaXe(carList, count); break;
            case 4: xoaXe(carList, count); break;
            case 5: timKiemXe(carList, count); break;
            case 6: 
                luuFile(carList, count, "data_xe.txt");
                cout << ">> Đã lưu dữ liệu!\n";
                break;
            case 0: 
                luuFile(carList, count, "data_xe.txt");
                cout << ">> Đã lưu dữ liệu. Hẹn gặp lại!\n";
                return;
            default: cout << ">> Lựa chọn không hợp lệ!\n";
        }   
    } while (choice != 0);
}
const string FILE_NAME = "data_nv.txt";
const int MAX_NHAN_VIEN = 100;


struct NhanVien {
    int ID;
    string HoTen;
    string ChucVu;
    string GioiTinh;
};

NhanVien danhSach[MAX_NHAN_VIEN];
int soLuongHienTai = 0; 

string convert_to_line(const NhanVien& nv) {
    return to_string(nv.ID) + "|" + nv.HoTen + "|" + nv.ChucVu + "|" + nv.GioiTinh;
}

NhanVien convert_to_struct(const string& line) {
    NhanVien nv;
    stringstream ss(line);
    string segment;

    getline(ss, segment, '|');
    if (!segment.empty()) {
        nv.ID = stoi(segment);
    } else {
        nv.ID = -1;
    }

    getline(ss, nv.HoTen, '|');
    getline(ss, nv.ChucVu, '|');
    getline(ss, nv.GioiTinh, '|');

    return nv;
}

void doc_file() {
    soLuongHienTai = 0;

    ifstream file(FILE_NAME);
    if (file.is_open()) {
        string line;
        while (getline(file, line) && soLuongHienTai < MAX_NHAN_VIEN) {
            if (!line.empty()) {
                danhSach[soLuongHienTai] = convert_to_struct(line);
                soLuongHienTai++;
            }
        }
        file.close();
        cout << "\n>>> Đã đọc " << soLuongHienTai << " nhân viên từ file " << FILE_NAME << ".\n";
    } else {
        cout << "\n>>> Không tìm thấy file " << FILE_NAME << ". Dữ liệu sẽ được lưu khi thêm mới.\n";
    }
}

void ghi_file() {
    ofstream file(FILE_NAME);
    if (file.is_open()) {
        for (int i = 0; i < soLuongHienTai; ++i) {
            file << convert_to_line(danhSach[i]) << "\n";
        }
        file.close();
        cout << "\n>>> Đã ghi thành công dữ liệu vào file " << FILE_NAME << ".\n";
    } else {
        cerr << "\n>>> Lỗi: Không thể mở file để ghi.\n";
    }
}

int tim_vi_tri_theo_id(int id) {
    for (int i = 0; i < soLuongHienTai; ++i) {
        if (danhSach[i].ID == id) {
            return i;
        }
    }
    return -1;
}

void them_nhan_vien() {
    if (soLuongHienTai >= MAX_NHAN_VIEN) {
        cout << "\n>>> Lỗi: Danh sách đầy, không thể thêm nữa!\n";
        return;
    }

    NhanVien nv;
    cout << "\n--- THÊM NHÂN VIÊN ---\n";

    int maxID = 0;
    for (int i = 0; i < soLuongHienTai; ++i) {
        if (danhSach[i].ID > maxID) {
            maxID = danhSach[i].ID;
        }
    }
    nv.ID = maxID + 1;
    cout << "ID mới (Tự động): " << nv.ID << "\n";

    cout << "Nhập Họ Tên: ";
    cin.ignore(); 
    getline(cin, nv.HoTen);

    cout << "Nhập Chức Vụ: ";
    getline(cin, nv.ChucVu);

    cout << "Nhập Giới Tính: ";
    getline(cin, nv.GioiTinh);

    danhSach[soLuongHienTai] = nv;
    soLuongHienTai++;
    
    cout << "\n*** Thêm nhân viên thành công! ***\n";
    ghi_file();
}

void xem_danh_sach() {
    cout << "\n--- Danh Sách Nhân Viên ---\n";
    if (soLuongHienTai == 0) {
        cout << "Danh sách trống.\n";
        return;
    }

    cout << setfill('-') << setw(55) << "-" << setfill(' ') << endl;
    cout << "|" << setw(5) << left << "ID"
         << "|" << setw(20) << left << "Họ Tên"
         << "|" << setw(15) << left << "Chức Vụ"
         << "|" << setw(10) << left << "Giới Tính"
         << "|\n";
    cout << setfill('-') << setw(55) << "-" << setfill(' ') << endl;

    for (int i = 0; i < soLuongHienTai; ++i) {
        const NhanVien& nv = danhSach[i];
        cout << "|" << setw(5) << left << nv.ID
             << "|" << setw(20) << left << nv.HoTen
             << "|" << setw(15) << left << nv.ChucVu
             << "|" << setw(10) << left << nv.GioiTinh
             << "|\n";
    }
    cout << setfill('-') << setw(55) << "-" << setfill(' ') << endl;
}

void sua_nhan_vien() {
    int idSua;
    cout << "\n--- SỬA THÔNG TIN NHÂN VIÊN ---\n";
    cout << "Nhập ID nhân viên cần sửa: ";
    if (!(cin >> idSua)) {
        cout << "\n>>> Lỗi nhập liệu ID.\n";
        cin.clear(); cin.ignore(10000, '\n'); return;
    }
    
    int viTri = tim_vi_tri_theo_id(idSua);

    if (viTri != -1) {
        NhanVien& nv = danhSach[viTri];
        cout << "Tìm thấy nhân viên: " << nv.HoTen << ". Bắt đầu sửa:\n";
        cin.ignore(); 

        cout << "Nhập Họ Tên mới (Enter để giữ nguyên [" << nv.HoTen << "]): ";
        string hoTenMoi;
        getline(cin, hoTenMoi);
        if (!hoTenMoi.empty()) nv.HoTen = hoTenMoi;

        cout << "Nhập Chức Vụ mới (Enter để giữ nguyên [" << nv.ChucVu << "]): ";
        string chucVuMoi;
        getline(cin, chucVuMoi);
        if (!chucVuMoi.empty()) nv.ChucVu = chucVuMoi;

        cout << "Nhập Giới Tính mới (Enter để giữ nguyên [" << nv.GioiTinh << "]): ";
        string gioiTinhMoi;
        getline(cin, gioiTinhMoi);
        if (!gioiTinhMoi.empty()) nv.GioiTinh = gioiTinhMoi;

        cout << "\n*** Sửa thông tin nhân viên ID " << idSua << " thành công! ***\n";
        ghi_file();
    } else {
        cout << "\n>>> Không tìm thấy nhân viên có ID " << idSua << ".\n";
    }
}

void xoa_nhan_vien() {
    int idXoa;
    cout << "\n--- XÓA NHÂN VIÊN ---\n";
    cout << "Nhập ID nhân viên cần xóa: ";
    if (!(cin >> idXoa)) {
        cout << "\n>>> Lỗi nhập liệu ID.\n";
        cin.clear(); cin.ignore(10000, '\n'); return;
    }

    int viTri = tim_vi_tri_theo_id(idXoa);

    if (viTri != -1) {
        cout << "Xác nhận xóa nhân viên: " << danhSach[viTri].HoTen << " (Y/N)? ";
        char confirm;
        cin >> confirm;
        
        if (confirm == 'Y' || confirm == 'y') {
            for (int i = viTri; i < soLuongHienTai - 1; ++i) {
                danhSach[i] = danhSach[i + 1];
            }
            soLuongHienTai--;

            cout << "\n*** Xóa nhân viên ID " << idXoa << " thành công! ***\n";
            ghi_file();
        } else {
            cout << "Hủy thao tác xóa.\n";
        }
    } else {
        cout << "\n>>> Không tìm thấy nhân viên có ID " << idXoa << ".\n";
    }
}

void tim_nhan_vien() {
    string tuKhoa;
    cout << "\n--- TÌM KIẾM NHÂN VIÊN ---\n";
    cout << "Nhập từ khóa tìm kiếm (ID hoặc Họ Tên): ";
    cin.ignore();
    getline(cin, tuKhoa);

    bool timThay = false;

    cout << "\n*** Kết Quả Tìm Kiếm: ***\n";
    
    cout << setfill('-') << setw(55) << "-" << setfill(' ') << endl;
    cout << "|" << setw(5) << left << "ID"
         << "|" << setw(20) << left << "Họ Tên"
         << "|" << setw(15) << left << "Chức Vụ"
         << "|" << setw(10) << left << "Giới Tính"
         << "|\n";
    cout << setfill('-') << setw(55) << "-" << setfill(' ') << endl;


    bool laID = true;
    for (char c : tuKhoa) {
        if (!isdigit(c)) {
            laID = false;
            break;
        }
    }

    if (laID) {
        try {
            int idTim = stoi(tuKhoa);
            int viTri = tim_vi_tri_theo_id(idTim);
            if (viTri != -1) {
                const NhanVien& nv = danhSach[viTri];
                cout << "|" << setw(5) << left << nv.ID
                     << "|" << setw(20) << left << nv.HoTen
                     << "|" << setw(15) << left << nv.ChucVu
                     << "|" << setw(10) << left << nv.GioiTinh
                     << "|\n";
                timThay = true;
            }
        } catch (...) {
            laID = false;
        }
    }

    if (!laID) {
        for (int i = 0; i < soLuongHienTai; ++i) {
            const NhanVien& nv = danhSach[i];

            string hoTenLower = nv.HoTen;
            string tuKhoaLower = tuKhoa;
            transform(hoTenLower.begin(), hoTenLower.end(), hoTenLower.begin(), ::tolower);
            transform(tuKhoaLower.begin(), tuKhoaLower.end(), tuKhoaLower.begin(), ::tolower);

            if (hoTenLower.find(tuKhoaLower) != string::npos) {
                cout << "|" << setw(5) << left << nv.ID
                     << "|" << setw(20) << left << nv.HoTen
                     << "|" << setw(15) << left << nv.ChucVu
                     << "|" << setw(10) << left << nv.GioiTinh
                     << "|\n";
                timThay = true;
            }
        }
    }
    cout << setfill('-') << setw(55) << "-" << setfill(' ') << endl;


    if (!timThay) {
        cout << "\n>>> Không tìm thấy nhân viên nào với từ khóa: " << tuKhoa << ".\n";
    }
}
void quanlyNhanVien(){
    doc_file();

    int luaChon;
    do {
        cout << "\n====================================\n";
        cout << "          QUẢN LÝ NHÂN VIÊN         \n";
        cout << "====================================\n";
        cout << "[1]. Thêm Nhân Viên\n";
        cout << "[2]. Xem Danh Sách Nhân Viên\n";
        cout << "[3]. Sửa Thông Tin Nhân Viên\n";
        cout << "[4]. Xóa Nhân Viên\n";
        cout << "[5]. Tìm Kiếm Nhân Viên\n";
        cout << "[0]. quay lại console \n";
        cout << "------------------------------------\n";
        cout << "Nhập lựa chọn của bạn: ";
        
        if (!(cin >> luaChon)) {
            cout << "\n>>> Lỗi nhập liệu. Vui lòng nhập số.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            luaChon = -1;
            continue;
        }

        switch (luaChon) {
            case 1:
                them_nhan_vien();
                break;
            case 2:
                xem_danh_sach();
                break;
            case 3:
                sua_nhan_vien();
                break;
            case 4:
                xoa_nhan_vien();
                break;
            case 5:
                tim_nhan_vien();
                break;
            case 0:
                cout << "\nĐã chọn Thoát. Dữ liệu đã được tự động lưu sau mỗi thao tác thêm/sửa/xóa.\n";
                break;
            default:
                cout << "\n>>> Lựa chọn không hợp lệ. Vui lòng chọn lại.\n";
                break;
        }
    } while (luaChon != 0);
}

const int MAX_CUSTOMERS = 100;


struct Customer {
    string id;
    string name;
    string phoneNum;
    string personalId;
    string address;
    string gender;
};

Customer cusList[MAX_CUSTOMERS]; 
int customerQuantity = 0;

const string FILE_NAME1 = "data_khach.txt";

void readFile() {
    ifstream fileIn(FILE_NAME1); 
    if (!fileIn.is_open()) return; 

    customerQuantity = 0;
    while(fileIn >> cusList[customerQuantity].id) {
        fileIn.ignore(); 
        getline(fileIn, cusList[customerQuantity].name);
        getline(fileIn, cusList[customerQuantity].phoneNum);
        getline(fileIn, cusList[customerQuantity].personalId);
        getline(fileIn, cusList[customerQuantity].address);
        getline(fileIn, cusList[customerQuantity].gender);
        customerQuantity++;
    }
    fileIn.close();
}

void writeFile() {
    ofstream fileOut(FILE_NAME1); 
    for(int i = 0; i < customerQuantity; ++i) {
        fileOut << cusList[i].id << "\n"
                << cusList[i].name << "\n"
                << cusList[i].phoneNum << "\n"
                << cusList[i].personalId << "\n"
                << cusList[i].address << "\n"
                << cusList[i].gender << "\n";
    }
    fileOut.close();
}

void addCustomer() {
    if (customerQuantity >= MAX_CUSTOMERS) {
        cout << "Danh sách đã đầy!\n";
        return;
    }
    Customer cus;
    cout << "--- NHẬP THÔNG TIN KHÁCH ---\n";
    cout << "Nhập ID: "; getline(cin, cus.id);
    
    for(int i=0; i<customerQuantity; i++) {
        if(cusList[i].id == cus.id) {
            cout << "Lỗi: ID đã tồn tại!\n"; return;
        }
    }

    cout << "Nhập Họ và tên: "; getline(cin, cus.name);
    cout << "Nhập SĐT: "; getline(cin, cus.phoneNum);
    cout << "Nhập mã CCCD: "; getline(cin, cus.personalId);
    cout << "Nhập địa chỉ: "; getline(cin, cus.address);
    cout << "Nhập giới tính: "; getline(cin, cus.gender);
    
    cusList[customerQuantity++] = cus;
    writeFile();
    cout << "\n>>> Thêm khách hàng thành công!\n";
}

void showList() {
    cout << "\n--- DANH SÁCH KHÁCH HÀNG (" << customerQuantity << ") ---\n";
    cout << left << setw(10) << "ID" << setw(20) << "Ho Ten" << setw(15) << "SDT" 
         << setw(15) << "CCCD" << setw(20) << "Dia Chi" << setw(10) << "Gioi Tinh" << endl;
    cout << string(90, '-') << endl;

    for(int i = 0; i < customerQuantity; ++i) {
        cout << left 
             << setw(10) << cusList[i].id 
             << setw(20) << cusList[i].name 
             << setw(15) << cusList[i].phoneNum 
             << setw(15) << cusList[i].personalId 
             << setw(20) << cusList[i].address 
             << setw(10) << cusList[i].gender << endl;
    }
    cout << string(90, '-') << endl;
}

void findCustomer(string id) {
    bool found = false;
    cout << string(90, '-') << endl;
    for (int i = 0; i < customerQuantity; ++i) {
        if (cusList[i].id == id) {
            cout << "| " << setw(8) << cusList[i].id 
                 << "| " << setw(18) << cusList[i].name 
                 << "| " << setw(13) << cusList[i].phoneNum 
                 << "| " << setw(13) << cusList[i].personalId 
                 << "| " << setw(18) << cusList[i].address 
                 << "| " << setw(9) << cusList[i].gender << "|\n";
            found = true;
        }
    }
    if (!found) cout << "\n>>> Không tìm thấy khách hàng với ID này!\n";
    cout << string(90, '-') << endl;
}

void fixCustomer(string id) {
    for (int i = 0; i < customerQuantity; ++i) {
        if (cusList[i].id == id) {
            cout << "\n>>> Nhập thông tin mới cho ID " << id << " (Enter để giữ nguyên):\n";
            
            string temp;
            cout << "Họ và tên (" << cusList[i].name << "): "; 
            getline(cin, temp); if(!temp.empty()) cusList[i].name = temp;

            cout << "SĐT (" << cusList[i].phoneNum << "): "; 
            getline(cin, temp); if(!temp.empty()) cusList[i].phoneNum = temp;

            cout << "CCCD (" << cusList[i].personalId << "): "; 
            getline(cin, temp); if(!temp.empty()) cusList[i].personalId = temp;

            cout << "Địa chỉ (" << cusList[i].address << "): "; 
            getline(cin, temp); if(!temp.empty()) cusList[i].address = temp;

            cout << "Giới tính (" << cusList[i].gender << "): "; 
            getline(cin, temp); if(!temp.empty()) cusList[i].gender = temp;

            writeFile();
            cout << "\n>>> Sửa thông tin thành công!\n";
            return;
        }
    }
    cout << "\n>>> Không tìm thấy khách hàng để sửa!\n";
}

void deleteCustomer(string id) {
    for (int i = 0; i < customerQuantity; ++i) {
        if (cusList[i].id == id) {
            cout << "Bạn có chắc muốn xóa khách hàng " << cusList[i].name << "? (y/n): ";
            char confirm; cin >> confirm; cin.ignore(); 
            
            if (confirm == 'y' || confirm == 'Y') {
                for (int j = i; j < customerQuantity - 1; j++) {
                    cusList[j] = cusList[j + 1];
                }
                --customerQuantity;
                writeFile();
                cout << "\n>>> Xóa khách hàng thành công!\n";
            } else {
                cout << "\n>>> Đã hủy xóa.\n";
            }
            return;
        }
    }
    cout << "\n>>> Không tìm thấy khách hàng để xóa!\n";
}


void quanlyKhachHang() { 
    readFile(); 
    int choose;
    do {
        cout << "\n========================================\n";
        cout << "        QUẢN LÝ KHÁCH HÀNG\n";
        cout << "========================================\n";
        cout << " [1] Thêm khách hàng\n";
        cout << " [2] Xem danh sách khách hàng\n";
        cout << " [3] Tìm khách hàng theo ID\n";
        cout << " [4] Sửa thông tin khách hàng\n";
        cout << " [5] Xoá khách hàng\n";
        cout << " [0] Quay lại Menu chính\n";
        cout << "Nhập lựa chọn: ";
        cin >> choose; 
        
       
        cin.ignore();
        
        switch (choose) {
            case 1: addCustomer(); break;
            case 2: showList(); break;
            case 3: {
                string id; cout << "Nhập ID cần tìm: "; getline(cin, id);
                findCustomer(id); break;
            }
            case 4: {
                string id; cout << "Nhập ID cần sửa: "; getline(cin, id);
                fixCustomer(id); break;
            }
            case 5: {
                string id; cout << "Nhập ID cần xóa: "; getline(cin, id);
                deleteCustomer(id); break;
            }
            case 0: cout << "Đang quay lại...\n"; return;
            default: cout << "Lựa chọn không hợp lệ!\n";
        }
    } while (choose != 0);
}


void quanlyHoaDon() {
    Car dsXeTam[MAX_CARS];
    int slXeTam = 0;
    
    
    docFile(dsXeTam, slXeTam, "data_xe.txt"); 
    readFile(); 

    cout << "\n----------------------------------------\n";
    cout << "           TẠO HÓA ĐƠN BÁN XE           \n";
    cout << "----------------------------------------\n";

    
    string idKhach;
    cout << "Nhập ID khách hàng: ";
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, idKhach);

    bool timThayKhach = false;
    string tenKhach = "";
    
    for (int i = 0; i < customerQuantity; i++) {
        if (cusList[i].id == idKhach) {
            timThayKhach = true;
            tenKhach = cusList[i].name;
            break;
        }
    }

    if (!timThayKhach) {
        cout << ">> Lỗi: Không tìm thấy khách hàng có ID [" << idKhach << "]!\n";
        cout << ">> Vui lòng thêm khách hàng ở chức năng số 2 trước.\n";
        cout << "Nhấn Enter để quay lại...";
        cin.ignore(); cin.get();
        return;
    }
    cout << ">> Đã chọn khách hàng: " << tenKhach << endl;

    int idXe;
    cout << "Nhập ID xe khách mua: ";
    if (!(cin >> idXe)) {
        cout << ">> Lỗi: ID xe phải là số nguyên!\n";
        cin.clear(); cin.ignore(1000, '\n');
        return;
    }

    int viTri = timViTriTheoID(dsXeTam, slXeTam, idXe);
    if (viTri == -1) {
        cout << ">> Lỗi: không tìm thấy xe có ID [" << idXe << "] trong kho!\n";
        cout << "Nhấn Enter để quay lại...";
        cin.ignore(); cin.get();
        return;
    }

   
    char statusCheck[20];
    strcpy(statusCheck, dsXeTam[viTri].status);
    toUpperString(statusCheck); 

    if (strstr(statusCheck, "ĐÃ BÁN") != NULL) {
        cout << ">> Lỗi: xe này ĐÃ BÁN rồi, không thể tạo hóa đơn!\n";
        cout << "Nhấn Enter để quay lại...";
        cin.ignore(); cin.get();
        return;
    }

  
    string ngayLap;
    cout << "Nhập ngày tạo hóa đơn (dd/mm/yyyy): ";
    cin.ignore(); 
    getline(cin, ngayLap);

  
    cout << "----------------------------------------\n";
    cout << "THÔNG TIN GIAO DỊCH:\n";
    cout << "- Ngày bán: " << ngayLap << endl;
    cout << "- Khách hàng: " << tenKhach << endl;
    cout << "- Xe: " << dsXeTam[viTri].brand << " " << dsXeTam[viTri].model << endl;
    cout << "- Giá bán: " << (long long)dsXeTam[viTri].price << " VND\n";
    cout << "----------------------------------------\n";
    cout << "Xác nhận bán xe này? (y/n): ";
    char xacNhan;
    cin >> xacNhan;

    if (xacNhan == 'y' || xacNhan == 'Y') {

        strcpy(dsXeTam[viTri].status, "ĐÃ BÁN");

   
        luuFile(dsXeTam, slXeTam, "data_xe.txt");

     
        ofstream fileHD("hoadon.txt", ios::app); 
        if (fileHD.is_open()) {
            fileHD << idKhach << "|" 
                   << tenKhach << "|" 
                   << idXe << "|" 
                   << dsXeTam[viTri].brand << "-" << dsXeTam[viTri].model << "|"
                   << fixed << setprecision(0) << dsXeTam[viTri].price << "|"
                   << ngayLap << "\n"; 
            fileHD.close();
            cout << "\n>> GIAO DỊCH THÀNH CÔNG! Hóa đơn đã được lưu.\n";
        } else {
            cout << "\n>> Lỗi: Không thể mở file hoadon.txt để lưu!\n";
        }
    } else {
        cout << "\n>> Đã hủy giao dịch.\n";
    }
    
    cout << "Nhấn Enter để tiếp tục...";
    cin.ignore(); cin.get();
}
struct HoaDonFull {
    string idKhach, tenKhach, idXe, brand, model, ngay;
    double gia;
};


void ghiTieuDeChung(int thang, int nam) {
    ofstream fileOut("Baocao&Thongke.txt", ios::out); 
    if (fileOut.is_open()) {
        fileOut << "********************************************************\n";
        fileOut << "       BÁO CÁO VÀ THỐNG KÊ DOANH THU THÁNG " << thang << "/" << nam << "\n";
        fileOut << "       Thời gian xuất: " << __DATE__ << " " << __TIME__ << "\n";
        fileOut << "********************************************************\n\n";
        fileOut.close();
    }
}


void bc1() {
    ifstream file("hoadon.txt");
    if (!file.is_open()) {
        cout << ">> Loi: Khong mo duoc file hoadon.txt\n";
        return;
    }

    vector<HoaDonFull> listHD;
    string line;
    
    
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string segment;
        vector<string> parts;
        while(getline(ss, segment, '|')) parts.push_back(segment);

        if(parts.size() >= 6) {
            HoaDonFull hd;
            hd.idKhach = parts[0];
            hd.tenKhach = parts[1];
            hd.idXe = parts[2];
            
            
            string hangModel = parts[3];
            size_t dash = hangModel.find('-');
            if (dash != string::npos) {
                hd.brand = hangModel.substr(0, dash);
                hd.model = hangModel.substr(dash + 1);
            } else {
                hd.brand = hangModel;
                hd.model = "Unknown";
            }
            
            hd.gia = stod(parts[4]);
            hd.ngay = parts[5];
            listHD.push_back(hd);
        }
    }
    file.close();

    if (listHD.empty()) {
        cout << ">> Không có hóa đơn nào!\n";
        return;
    }

    
    int thang, nam;
    cout << "\n--- [BC1] THỐNG KÊ DOANH THU CHI TIẾT ---\n";
    cout << "Nhập tháng cần thống kê (1-12): "; cin >> thang;
    cout << "Nhập năm cần thống kê: "; cin >> nam;

    
    ghiTieuDeChung(thang, nam);

    
    vector<HoaDonFull> listLoc;
    vector<string> listBrandUnique; 
    
    for(const auto& hd : listHD) {
        if (hd.ngay.length() >= 10) {
            int t = stoi(hd.ngay.substr(3, 2));
            int n = stoi(hd.ngay.substr(6, 4));
            if (t == thang && n == nam) {
                listLoc.push_back(hd);
                
                
                bool exists = false;
                for(const string& b : listBrandUnique) if(b == hd.brand) exists = true;
                if(!exists) listBrandUnique.push_back(hd.brand);
            }
        }
    }

    ofstream fileOut("Baocao&Thongke.txt", ios::app); 
    if (!fileOut.is_open()) return;

    fileOut << "=== [BC1] CHI TIẾT DOANH THU THEO HÀNG VÀ DÒNG XE ===\n";
    
    if (listLoc.empty()) {
        fileOut << "Không có xe nào được bán trong thời gian này.\n";
        cout << ">> Không có dữ liệu!\n";
    } else {
        double tongDoanhThuThang = 0;

    
        for (const string& brand : listBrandUnique) {
            fileOut << "----------------------------------------\n";
            fileOut << "HÃNG: " << brand << "\n";
            
            double tongGiaHang = 0;
            int tongSLHang = 0;
            
            
            vector<string> listModelUnique;
            for(const auto& hd : listLoc) {
                if(hd.brand == brand) {
                    bool exists = false;
                    for(const string& m : listModelUnique) if(m == hd.model) exists = true;
                    if(!exists) listModelUnique.push_back(hd.model);
                }
            }

          
            for(const string& model : listModelUnique) {
                int slModel = 0;
                double giaModel = 0; 
                
                for(const auto& hd : listLoc) {
                    if(hd.brand == brand && hd.model == model) {
                        slModel++;
                        giaModel = hd.gia; 
                    }
                }
                
              
                fileOut << "   + Xe: " << left << setw(15) << model 
                        << " | SL: " << setw(3) << slModel 
                        << " | Gia: " << fixed << setprecision(0) << giaModel << " Tr VND\n";
                
                tongSLHang += slModel;
                tongGiaHang += (slModel * giaModel);
            }

            fileOut << "\n   -> Tổng số xe của hãng: " << tongSLHang << " xe\n";
            fileOut << "   -> Tổng doanh thu của hãng: " << fixed << setprecision(0) << tongGiaHang << " Tr VND\n";
            
            tongDoanhThuThang += tongGiaHang;
        }
        
        fileOut << "========================================\n";
        fileOut << ">>> TỔNG DOANH THU CẢ THÁNG: " << fixed << setprecision(0) << tongDoanhThuThang << " Tr VND\n";
        fileOut << "========================================\n\n";
        
        cout << ">> Đã xuất báo cáo 1 (Chi tiết) vào file 'Baocao&Thongke.txt'.\n";
    }
    fileOut << "\n########################################################\n\n";
    fileOut.close();
}


void bc2() {
    int thang, nam;
    cout << "\n--- [BC2] XE BÁN CHẠY / BÁN CHẬM ---\n";
    cout << "Nhập tháng cần thống kê (1-12): "; cin >> thang;
    cout << "Nhập năm cần thống kê: "; cin >> nam;
    
    ifstream fileIn("hoadon.txt");
    if (!fileIn.is_open()) return;

    map<string, int> demSoLuong;
    string line;
    int tongBan = 0;

    while (getline(fileIn, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string segment;
        vector<string> parts;
        while(getline(ss, segment, '|')) parts.push_back(segment);

        if (parts.size() >= 6) {
            string ngay = parts[5];
            if (ngay.length() >= 10) {
                int t = stoi(ngay.substr(3, 2));
                int n = stoi(ngay.substr(6, 4));
                
                if (t == thang && n == nam) {
                    string carInfo = parts[3];
                    string brand = carInfo.substr(0, carInfo.find('-'));
                    demSoLuong[brand]++;
                    tongBan++;
                }
            }
        }
    }
    fileIn.close();

    ofstream fileOut("Baocao&Thongke.txt", ios::app); 
    if (fileOut.is_open()) {
        fileOut << "=== [BC2] XẾP HẠNG BÁN CHẠY / BÁN CHẬM ===\n";
        
        if (tongBan == 0) {
            fileOut << "Không có dữ liệu để xếp hạng.\n";
            cout << ">> Không có dữ liệu bán hàng trong tháng này.\n";
        } else {
            string hangBanChay = "", hangBanE = "";
            int maxBan = INT_MIN;
            int minBan = INT_MAX;

            for (const auto& pair : demSoLuong) {
                if (pair.second > maxBan) { maxBan = pair.second; hangBanChay = pair.first; }
                if (pair.second < minBan) { minBan = pair.second; hangBanE = pair.first; }
            }

            fileOut << "[1] HÃNG XE BÁN CHẠY NHẤT:\n";
            fileOut << "    -> " << hangBanChay << ": " << maxBan << " xe\n\n";

            fileOut << "[2] HÃNG XE BÁN CHẬM NHẤT:\n";
            fileOut << "    -> " << hangBanE << ": " << minBan << " xe\n\n";

            fileOut << "[3] TỔNG HỢP SỐ LƯỢNG:\n";
            for (const auto& pair : demSoLuong) {
                fileOut << "    - " << left << setw(15) << pair.first << ": " << pair.second << " xe\n";
            }
            cout << ">> Đã xuất báo cáo 2 vào file 'Baocao&Thongke.txt'.\n";
        }
        fileOut << "\n########################################################\n\n";
        fileOut.close();
    }
}
void bc3() {
    
    Car listXe[MAX_CARS];
    int soLuongXe = 0;
    docFile(listXe, soLuongXe, "data_xe.txt");

    if (soLuongXe == 0) {
        cout << ">> Danh sách xe trống, không thể tạo báo cáo.\n";
        return;
    }

    
    ofstream fileOut("Baocao&Thongke.txt", ios::app);
    if (!fileOut.is_open()) {
        cout << ">> Lỗi: Không mở được file báo cáo!\n";
        return;
    }

    fileOut << "\n=== [BC3] TÌNH TRẠNG KHO XE (CÒN HÀNG / ĐÃ BÁN) ===\n";
    
    int conHang = 0;
    int daBan = 0;

   
    fileOut << "\n--- I. DANH SÁCH XE CÒN HÀNG ---\n";
    fileOut << string(95, '-') << endl;
    fileOut << "| " << left << setw(5) << "ID" 
            << "| " << setw(14) << "Hãng xe" 
            << "| " << setw(14) << "Model" 
            << "| " << setw(12) << "Nhiên liệu"
            << "| " << setw(10) << "Mã lực"
            << "| " << setw(14) << "Giá (VND)" 
            << "| " << setw(12) << "Trạng thái" << "|\n";
    fileOut << string(95, '-') << endl;

    for (int i = 0; i < soLuongXe; ++i) {
        char status[50];
        strcpy(status, listXe[i].status);
        toUpperString(status); 
        
     
        if (strstr(status, "ĐÃ BÁN") == NULL) {
            fileOut << "| " << left << setw(5) << listXe[i].id 
                    << "| " << setw(14) << listXe[i].brand
                    << "| " << setw(14) << listXe[i].model
                    << "| " << setw(12) << listXe[i].fuel
                    << "| " << setw(10) << listXe[i].horsepower
                    << "| " << setw(14) << fixed << setprecision(0) << listXe[i].price
                    << "| " << setw(12) << listXe[i].status << "|\n";
            conHang++;
        }
    }
    fileOut << string(95, '-') << "\n";

    fileOut << "\n--- II. DANH SÁCH XE ĐÃ BÁN ---\n";
    fileOut << string(95, '-') << endl;
    fileOut << "| " << left << setw(5) << "ID" 
            << "| " << setw(14) << "Hãng xe" 
            << "| " << setw(14) << "Model" 
            << "| " << setw(12) << "Nhiên liệu"
            << "| " << setw(10) << "Mã lực"
            << "| " << setw(14) << "Giá (VND)" 
            << "| " << setw(12) << "Trạng thái" << "|\n";
    fileOut << string(95, '-') << endl;

    for (int i = 0; i < soLuongXe; ++i) {
        char status[50];
        strcpy(status, listXe[i].status);
        toUpperString(status);
        
        if (strstr(status, "DA BAN") != NULL) {
            fileOut << "| " << left << setw(5) << listXe[i].id 
                    << "| " << setw(14) << listXe[i].brand
                    << "| " << setw(14) << listXe[i].model
                    << "| " << setw(12) << listXe[i].fuel
                    << "| " << setw(10) << listXe[i].horsepower
                    << "| " << setw(14) << fixed << setprecision(0) << listXe[i].price
                    << "| " << setw(12) << listXe[i].status << "|\n";
            daBan++;
        }
    }
    fileOut << string(95, '-') << "\n";
    fileOut << ">>> TỔNG KẾT:\n"; 
    fileOut << "    Số lượng xe còn trong kho: " << conHang << "\n"; 
    fileOut << "    Số lượng xe đã bán       : " << daBan << "\n";
    fileOut << "    Tổng số lượng xe         : " << soLuongXe << "\n";
    fileOut << "########################################################\n\n";

    fileOut.close();
    cout << "\n>> Đã xuất báo cáo 3 (Tồn kho) vào file 'Baocao&Thongke.txt'.\n";
    cout << "   - Còn hàng: " << conHang << " xe\n";
    cout << "   - Đã bán  : " << daBan << " xe\n";
}
void quanlyBaoCaoVaThongKe() {
    int subChoice;
    do {
        xoaManHinh();
        cout << "\n========================================\n";
        cout << "       BÁO CÁO VÀ THỐNG KÊ\n";
        cout << "========================================\n";
        cout << "[1]. BC1: Số lượng và doanh thu (Tháng/Năm)\n";
        cout << "[2]. BC2: Hãng xe bán chạy nhất và chậm nhất (Tháng/Năm)\n";
        cout << "[3]. BC3: Các xe còn hàng và đã bán\n";
        cout << "[0]. Quay lại menu chính\n";
        cout << "Nhập lựa chọn: ";
        
        if (!(cin >> subChoice)) {
            cin.clear(); cin.ignore(1000, '\n');
            subChoice = -1;
        }

        switch (subChoice) {
            case 1: 
                bc1();
                cout << "\nNhấn Enter để tiếp tục..."; cin.ignore(); cin.get();
                break;
            case 2: 
                bc2(); 
                cout << "\nNhấn Enter để tiếp tục..."; cin.ignore(); cin.get();
                break;
            case 3: 
                bc3();
                cout << "\nNhấn Enter để tiếp tục..."; cin.ignore(); cin.get();
                break;
            case 0: return;
            default: 
                cout << "Lựa chọn không hợp lệ!\n"; 
                cout << "\nNhấn Enter để tiếp tục..."; cin.ignore(); cin.get();
                break;
        }
    } while (subChoice != 0);
}
int main(){
    int choice;
    do{
        xoaManHinh();
        cout << BOLD << CYAN << R"(
   ___  __  __ _____ ____  
  / _ \/ / / //_  _// __ \ 
 / // / /_/ /  / / / /_/ / 
/____/\____/  /_/  \____/  SHOWROOM MANAGER v2.0
)" << endl;
        cout << "-------------------------------" << endl;
        cout << "[1]. Quản lý ô tô. " << endl;
        cout << "[2]. Quản lý khách hàng. "<< endl;
        cout << "[3]. Quản lý nhân viên. " << endl;
        cout << "[4]. Tạo hoá đơn bán xe" << endl;
        cout << "[5]. Báo cáo và thống kê" << endl;
        cout << "[0]. để thoát chương trình. " << endl;
        cout << "-------------------------------" << endl;
        cout << ">> nhập vào lựa chọn của bạn : " ;
        cin >> choice;
        switch(choice) {
            case 1:
                quanlyXe();
                break;
            case 2:
                quanlyKhachHang();
                break;
            case 3:
                quanlyNhanVien();
                break;
            case 4:
                quanlyHoaDon(); 
                break;
            case 5:
                quanlyBaoCaoVaThongKe();
                break;
            case 0: 
                cout << "chương trình đang thoát nhấn Enter để kết thúc. ";
                cin.ignore();
                cin.get();
                break;
            default:
                cout << "lựa chọn của bạn không hợp lệ vui lòng chọn lại nhé!! " ;
                break;
        }
    } while( choice != 0 );
    return 0;
}
