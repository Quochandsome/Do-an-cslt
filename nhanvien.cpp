#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
using namespace std;
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


int main() {
    
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
        cout << "0. Thoát\n";
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

    return 0;
}
