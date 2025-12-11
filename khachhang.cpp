#include <iostream>
#include <fstream>
#include <string>
using std::cout, std::cin, std::string;

struct Customer {
    string id;
    string name;
    string phoneNum;
    string personalId;
    string address;
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
        customerQuantity++;
    }
    fileIn.close();
}

void writeFile() {
    ofstream fileOut("data_khach.txt");
    for(int i = 0; i <= customerQuantity - 1; ++i) {
        fileOut << cusList[i].id << endl;
        fileOut << cusList[i].name << endl;
        fileOut << cusList[i].phoneNum << endl;
        fileOut << cusList[i].personalId << endl;
        fileOut << cusList[i].address << endl;

    }
    fileOut.close();
}

// hàm thêm khách hàng
void addCustomer() {
    Customer cus;
    cout << "Nhập ID : "; 
    getline(cin, cus.id);
    cout << "Nhập Họ và tên: ";
    getline(cin, cus.name);
    cout << "Nhập SĐT: ";
    getline(cin, cus.phoneNum);
    cout << "Nhập mã CCCD: ";
    getline(cin, cus.personalId);
    cout << "Nhập địa chỉ: ";
    getline(cin, cus.address);
    cusList[customerQuantity++] = cus;
    writeFile();
    cout << "Thêm khách hàng thành công!\n";
}

// hàm xem danh sách khách hàng
void showList() {
    for(int i = 0; i <= customerQuantity - 1; ++i) {
        cout << "ID Khách hàng: " << cusList[i].id << endl;
        cout << "Họ và tên: " << cusList[i].name << endl;
        cout << "SĐT: " << cusList[i].phoneNum << endl;
        cout << "Mã CCCD: " << cusList[i].personalId << endl;
        cout << "Địa chỉ: " << cusList[i].address << endl;
        cout << "--------------------------\n";

    }
}

// hàm tìm khách hàng
void findCustomer(string id) {
    for (int i = 0; i <= customerQuantity - 1; ++i) {
        if (cusList[i].id == id) {
            cout << "Khách hàng bạn muốn tìm là:\n";
            cout << "Họ và tên: " << cusList[i].name << endl;
            cout << "SĐT: " << cusList[i].phoneNum << endl;
            cout << "Mã CCCD: " << cusList[i].personalId << endl;
            cout << "Địa chỉ: " << cusList[i].address << endl;
            return;
        }
    }
}

// hàm sửa thông tin khách hàng
void fixCustomer(string id) {
    for (int i = 0; i < customerQuantity; ++i) {
        if (cusList[i].id == id) {
            cout << "Nhập thông tin mới:\n";
            cout << "Nhập Họ và tên: "; getline(cin, cusList[i].name);
            cout << "Nhập SĐT: "; getline(cin, cusList[i].phoneNum);
            cout << "Nhập Mã CCCD: "; getline(cin, cusList[i].personalId);
            cout << "Nhập Địa chỉ: "; getline(cin, cusList[i].address);
            writeFile();
            cout << "Sửa thông tin thành công!\n";
            return;
        }
    }
}

// hàm xóa thong tin khách hàng
void deleteCustomer(string id) {
    for (int i = 0; i <= customerQuantity - 1; ++i) {
        if (cusList[i].id == id) {
            for (int j = i; j < customerQuantity - 1; j++) {
                cusList[j] = cusList[j + 1];
            }
            --customerQuantity;
            writeFile();
            cout << "Xóa khách hàng thành công!\n";
            return;
        }
    }
}

int main() {
    string buffer;
    int choose;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Thêm khách hàng\n";
        cout << "2. Xem danh sách\n";
        cout << "3. Tìm khách hàng\n";
        cout << "4. Sửa khách hàng\n";
        cout << "5. Xóa khách hàng\n";
        cout << "0. Thoát\n";
        cout << "Chọn số theo nhu cầu của bạn "; 
        getline(cin, buffer);
        choose = stoi(buffer);

        switch (choose) {
            case 1: {
                addCustomer();
                break;
            } 
            case 2: {
                showList(); 
                break;
            }
            case 3: {
                int id; 
                cout << "Hãy nhập ID khách hàng cần tìm: "; cin >> id;
                findCustomer(id);
                break;
            }
            case 4: {
                int id; 
                cout << "Hãy nhập ID khách hàng cần sửa: "; cin >> id;
                fixCustomer(id);
                break;
            }
            case 5: {
                int id; 
                cout << "Nhap ID can xoa: "; cin >> id;
                deleteCustomer(id);
                break;
            }
            case 0: {
                cout << "Thoát chương trình.\n"; 
                break;
            }
        }
    } while (choose != 0);

    return 0;
}
