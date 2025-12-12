#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using std::cout, std::cin, std::string, std::getline, std::ifstream, std::ofstream, std::setw, std::left, std::right;

struct Customer {
    string id;
    string name;
    string phoneNum;
    string personalId;
    string address;
    string gender;
};

const int MAX_CUSTOMERS = 100;
Customer cusList[MAX_CUSTOMERS];
int customerQuantity = 0;

void readFile() {
    ifstream fileIn("data_khach.txt");
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
    ofstream fileOut("data_khach.txt");
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
    Customer cus;
    cout << "Nhập ID : "; getline(cin, cus.id);
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
    cout << "\n--- DANH SÁCH KHÁCH HÀNG ---\n";
    cout << "|ID       |Họ Tên             |SĐT            |CCCD           |Địa Chỉ           |Giới Tính|\n";
    cout << "---------------------------------------------------------------------------------------------\n";
    for(int i = 0; i < customerQuantity; ++i) {
        cout << "|"
             << setw(9)  << left << cusList[i].id << "|"
             << setw(19) << left << cusList[i].name << "|"
             << setw(15) << left << cusList[i].phoneNum << "|"
             << setw(15) << left << cusList[i].personalId << "|"
             << setw(18) << left << cusList[i].address << "|"
             << setw(10) << left << cusList[i].gender << "|\n";
    }
    cout << "---------------------------------------------------------------------------------------------\n";
}

void findCustomer(string id) {
    for (int i = 0; i < customerQuantity; ++i) {
        if (cusList[i].id == id) {
            cout << "\n--- THÔNG TIN KHÁCH HÀNG ---\n";
            cout << "|ID       |Họ Tên             |SĐT            |CCCD           |Địa Chỉ           |Giới Tính|\n";
            cout << "---------------------------------------------------------------------------------------------\n";
            cout << "|"
                 << setw(9)  << left << cusList[i].id << "|"
                 << setw(19) << left << cusList[i].name << "|"
                 << setw(15) << left << cusList[i].phoneNum << "|"
                 << setw(15) << left << cusList[i].personalId << "|"
                 << setw(18) << left << cusList[i].address << "|"
                 << setw(10) << left << cusList[i].gender << "|\n";
            cout << "---------------------------------------------------------------------------------------------\n";
            return;
        }
    }
    cout << "\n>>> Không tìm thấy khách hàng với ID này!\n";
}

void fixCustomer(string id) {
    for (int i = 0; i < customerQuantity; ++i) {
        if (cusList[i].id == id) {
            cout << "\n>>> Nhập thông tin mới cho khách hàng:\n";
            cout << "Họ và tên: "; getline(cin, cusList[i].name);
            cout << "SĐT: "; getline(cin, cusList[i].phoneNum);
            cout << "CCCD: "; getline(cin, cusList[i].personalId);
            cout << "Địa chỉ: "; getline(cin, cusList[i].address);
            cout << "Giới tính: "; getline(cin, cusList[i].gender);
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
            for (int j = i; j < customerQuantity - 1; j++) {
                cusList[j] = cusList[j + 1];
            }
            --customerQuantity;
            writeFile();
            cout << "\n>>> Xóa khách hàng thành công!\n";
            return;
        }
    }
    cout << "\n>>> Không tìm thấy khách hàng để xóa!\n";
}

int main() {
    string buffer;
    int choose;
    do {
        cout << "\n========================================\n";
        cout << "        QUẢN LÝ KHÁCH HÀNG\n";
        cout << "========================================\n";
        cout << " [1] Thêm khách hàng\n";
        cout << " [2] Xem danh sách khách hàng\n";
        cout << " [3] Tìm khách hàng theo ID\n";
        cout << " [4] Sửa thông tin khách hàng\n";
