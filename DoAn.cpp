#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include<algorithm>
using namespace std;
#define MAX_CARS 100
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
        cout << ">> Loi: Vui long nhap so nguyen duong: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return number;
}


double nhapSoThuc(const string& message) {
    double number;
    cout << message;
    while (!(cin >> number) || number <= 0) {
        cout << ">> Loi: Vui long nhap so duong: ";
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
         << "| " << setw(14) << "Hang xe" 
         << "| " << setw(14) << "Model" 
         << "| " << setw(12) << "N.Lieu"
         << "| " << setw(10) << "Ma Luc"
         << "| " << setw(14) << "Gia (VND)" 
         << "| " << setw(12) << "Trang thai" << "|\n";
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
        cout << "Khong the mo file de luu du lieu!\n";
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
    cout << ">> Da tai " << count << " xe tu file.\n";
}



void themXe(Car carList[], int &count) {
    if (count >= MAX_CARS) {
        cout << ">> Danh sach da day!\n";
        return;
    }
    
    cout << "\n--- THEM XE MOI ---\n";
    Car newCar;

   
    do {
        newCar.id = nhapSoNguyen("ID (so nguyen duy nhat): ");
        if (timViTriTheoID(carList, count, newCar.id) != -1) {
            cout << ">> ID da ton tai, hay nhap ID khac\n";
        } else {
            break;
        }
    } while (true);
    
    nhapChuoi("Hang xe: ", newCar.brand, 50);
    nhapChuoi("Model: ", newCar.model, 50);
    nhapChuoi("Nhien lieu (Xang/Dau/Dien): ", newCar.fuel, 20);
    newCar.horsepower = nhapSoNguyen("Ma luc (HP): ");
    newCar.price = nhapSoThuc("Gia (VND): ");
    nhapChuoi("Trang thai (Con hang/Da ban): ", newCar.status, 20);

    carList[count++] = newCar;
    luuFile(carList, count, "data_xe.txt");
    cout << ">> DA THEM XE THANH CONG!\n";
}

void xemDanhSach(Car carList[], int count) {
    cout << "\n--- DANH SACH XE ---\n";
    if (count == 0) {
        cout << "Danh sach trong!\n";
        return;
    }
    
    inTieuDeBang();
    for (int i = 0; i < count; i++) {
        inThongTinXe(carList[i]);
    }
    cout << string(95, '-') << endl;
    cout << "Tong so: " << count << " xe\n";
}

void suaXe(Car carList[], int count) {
    if (count == 0) { cout << "Danh sach trong!\n"; return; }

    int id = nhapSoNguyen("\nNhap ID xe can sua: ");
    int index = timViTriTheoID(carList, count, id);
    
    if (index == -1) {
        cout << ">> Khong tim thay xe ID " << id << endl;
        return;
    }
    
   
    cout << "\nTHONG TIN HIEN TAI:\n";
    cout << "1. Hang xe:   " << carList[index].brand << endl;
    cout << "2. Model:     " << carList[index].model << endl;
    cout << "3. Nhien lieu:" << carList[index].fuel << endl;
    cout << "4. Ma luc:    " << carList[index].horsepower << " HP" << endl;
    cout << "5. Gia:       " << (long long)carList[index].price << " VND" << endl;
    cout << "6. Trang thai:" << carList[index].status << endl;
    
    
    int choice;
    cout << "\nChon muc muon sua (1-6, 0 de Huy): ";
    if (!(cin >> choice)) choice = 0;
    
    if (choice == 0) { cout << "Da huy thao tac.\n"; return; }

    switch (choice) {
        case 1: nhapChuoi("Nhap hang xe moi: ", carList[index].brand, 50); break;
        case 2: nhapChuoi("Nhap model moi: ", carList[index].model, 50); break;
        case 3: nhapChuoi("Nhap nhien lieu moi: ", carList[index].fuel, 20); break;
        case 4: carList[index].horsepower = nhapSoNguyen("Nhap ma luc moi: "); break;
        case 5: carList[index].price = nhapSoThuc("Nhap gia moi: "); break;
        case 6: nhapChuoi("Nhap trang thai moi: ", carList[index].status, 20); break;
        default: cout << "Lua chon khong hop le!\n"; return;
    }
    
    luuFile(carList, count, "data_xe.txt");
    cout << ">> CAP NHAT THANH CONG!\n";
}

void xoaXe(Car carList[], int &count) {
    if (count == 0) { cout << "Danh sach trong!\n"; return; }

    int id = nhapSoNguyen("\nNhap ID xe can xoa: ");
    int index = timViTriTheoID(carList, count, id);
    
    if (index == -1) {
        cout << ">> Khong tim thay xe ID " << id << endl;
        return;
    }
    
    cout << "Ban chac chan muon xoa xe [" << carList[index].brand << " " << carList[index].model << "]? (y/n): ";
    char confirm; cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        for (int i = index; i < count - 1; i++) {
            carList[i] = carList[i + 1];
        }
        count--;
        luuFile(carList, count, "data_xe.txt");
        cout << ">> DA XOA XE!\n";
    } else {
        cout << ">> DA HUY XOA.\n";
    }
}

void timKiemXe(Car carList[], int count) {
    if (count == 0) { cout << "Danh sach trong!\n"; return; }
    
    cout << "\n--- TIM KIEM XE ---\n";
    cout << "1. Tim theo ID\n";
    cout << "2. Tim theo Hang xe\n";
    cout << "3. Tim theo Khoang gia\n";
    cout << "4. Tim theo Trang thai\n";
    int choice = nhapSoNguyen("Chon phuong thuc (1-4): ");
    
    bool found = false;
    int foundCount = 0;
    
  
    
    switch (choice) {
        case 1: { 
            int id = nhapSoNguyen("Nhap ID can tim: ");
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
            nhapChuoi("Nhap ten hang xe: ", keyword, 50);
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
            double minP = nhapSoThuc("Gia thap nhat: ");
            double maxP = nhapSoThuc("Gia cao nhat: ");
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
            nhapChuoi("Nhap trang thai: ", keyword, 20);
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
            cout << "Lua chon khong hop le!\n";
            return;
    }
    
    if (found) cout << ">> Tim thay " << foundCount << " xe phu hop.\n";
    else cout << ">> Khong tim thay xe nao.\n";
}


void ql1() {
    Car carList[MAX_CARS];
    int count = 0; 
    docFile(carList, count, "data_xe.txt");
    int choice;
    do {
        cout << "\n=== HE THONG QUAN LY XE ===\n";
        cout << "1. Them xe moi\n";
        cout << "2. Xem danh sach xe\n";
        cout << "3. Sua thong tin xe\n";
        cout << "4. Xoa xe\n";
        cout << "5. Tim kiem xe\n";
        cout << "6. Luu du lieu\n";
        cout << "0. Quay lại console\n";
        cout << "Nhap lua chon: ";
        
       
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
                cout << ">> DA LUU DU LIEU!\n";
                break;
            case 0: 
                luuFile(carList, count, "data_xe.txt");
                cout << ">> Da luu du lieu. Hen gap lai!\n";
                return;
            default: cout << ">> Lua chon khong hop le!\n";
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
    cout << "\n--- Thêm Nhân Viên ---\n";

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
    cout << "\n--- Sửa Thông Tin Nhân Viên ---\n";
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
    cout << "\n--- Xóa Nhân Viên ---\n";
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
    cout << "\n--- Tìm Kiếm Nhân Viên ---\n";
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
void ql3(){
    doc_file();

    int luaChon;
    do {
        cout << "\n====================================\n";
        cout << "          QUẢN LÝ NHÂN VIÊN         \n";
        cout << "       (Tối đa " << MAX_NHAN_VIEN << " nhân viên)      \n";
        cout << "====================================\n";
        cout << "1. Thêm Nhân Viên\n";
        cout << "2. Xem Danh Sách Nhân Viên\n";
        cout << "3. Sửa Thông Tin Nhân Viên\n";
        cout << "4. Xóa Nhân Viên\n";
        cout << "5. Tìm Kiếm Nhân Viên\n";
        cout << "0. quay lại cosole \n";
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


void ql2() { 
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
void ql4() {
    Car dsXeTam[MAX_CARS];
    int slXeTam = 0;
    
    
    docFile(dsXeTam, slXeTam, "data_xe.txt"); 
    readFile(); 

    cout << "\n----------------------------------------\n";
    cout << "           TAO HOA DON BAN XE           \n";
    cout << "----------------------------------------\n";

    
    string idKhach;
    cout << "Nhap ID Khach hang: ";
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
        cout << ">> LOI: Khong tim thay khach hang ID [" << idKhach << "]!\n";
        cout << ">> Vui long them khach hang o chuc nang so 2 truoc.\n";
        cout << "Nhan Enter de quay lai...";
        cin.ignore(); cin.get();
        return;
    }
    cout << ">> Da chon khach hang: " << tenKhach << endl;

    int idXe;
    cout << "Nhap ID Xe muon mua: ";
    if (!(cin >> idXe)) {
        cout << ">> LOI: ID xe phai la so nguyen!\n";
        cin.clear(); cin.ignore(1000, '\n');
        return;
    }

    int viTri = timViTriTheoID(dsXeTam, slXeTam, idXe);
    if (viTri == -1) {
        cout << ">> LOI: Khong tim thay xe ID [" << idXe << "] trong kho!\n";
        cout << "Nhan Enter de quay lai...";
        cin.ignore(); cin.get();
        return;
    }

   
    char statusCheck[20];
    strcpy(statusCheck, dsXeTam[viTri].status);
    toUpperString(statusCheck); 

    if (strstr(statusCheck, "DA BAN") != NULL) {
        cout << ">> LOI: Xe nay DA BAN roi, khong the tao hoa don!\n";
        cout << "Nhan Enter de quay lai...";
        cin.ignore(); cin.get();
        return;
    }

  
    string ngayLap;
    cout << "Nhap ngay lap hoa don (dd/mm/yyyy): ";
    cin.ignore(); 
    getline(cin, ngayLap);

  
    cout << "----------------------------------------\n";
    cout << "THONG TIN GIAO DICH:\n";
    cout << "- Ngay bán: " << ngayLap << endl;
    cout << "- Khach hang: " << tenKhach << endl;
    cout << "- Xe: " << dsXeTam[viTri].brand << " " << dsXeTam[viTri].model << endl;
    cout << "- Gia ban: " << (long long)dsXeTam[viTri].price << " VND\n";
    cout << "----------------------------------------\n";
    cout << "Xac nhan ban xe nay? (y/n): ";
    char xacNhan;
    cin >> xacNhan;

    if (xacNhan == 'y' || xacNhan == 'Y') {

        strcpy(dsXeTam[viTri].status, "Da ban");

   
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
            cout << "\n>> GIAO DICH THANH CONG! Hoa don da duoc luu.\n";
        } else {
            cout << "\n>> LOI: Khong the mo file hoadon.txt de luu!\n";
        }
    } else {
        cout << "\n>> Da huy giao dich.\n";
    }
    
    cout << "Nhan Enter de tiep tuc...";
    cin.ignore(); cin.get();
}
int main(){
    int choice;
    do{
        xoaManHinh();
        cout << "\n-----CHÀO MỪNG BẠN ĐẾN VỚI CONSOLE QUẢN LÝ SHOWROOM Ô TÔ-----" << endl;
        cout << "1. Quản lý Ô TÔ. " << endl;
        cout << "2. Quản lý khách hàng. "<< endl;
        cout << "3. Quản lý nhân viên. " << endl;
        cout << "4, Tạo hoá đơn bán xe" << endl;
        cout << "0. để thoát chương trình. " << endl;
        cout << "nhập vào lựa chọn của bạn : " ;
        cin >> choice;
        switch(choice){
        case 1 :
            ql1();
            break;
        case 2:
            ql2();
            break;
        case 3:
            ql3();
            break;
        case 4:
            ql4(); 
            break;
        case 0 : 
            cout << "chương trình đang thoát nhấn enter để kết thúc. ";
            cin.ignore();
            cin.get();
            break;
        default :
            cout << "lựa chọn của bạn không hợp lệ vui lòng chọn lại nhé!! " ;
            break;
    }
    }while( choice != 0 );
    return 0;
}
