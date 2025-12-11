#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>

using namespace std;
#define MAX_CARS 100

struct Car {
    int id;
    char brand[50];
    char model[50];
    char fuel[20];
    int horsepower;
    double price;
    char status[20];  
};



void xoaManHinh() {
    #ifdef _WIN32
        system("cls");  
    #else
        system("clear");
    #endif
}

void dungManHinh() {
    cout << "\nNhan Enter de tiep tuc...";
    cin.ignore();
    cin.get();
}

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


int main() {
    Car carList[MAX_CARS];
    int count = 0;
    
    
    docFile(carList, count, "data_xe.txt");
    
    int choice;
    do {
        xoaManHinh();
        cout << "\n=== HE THONG QUAN LY XE ===\n";
        cout << "1. Them xe moi\n";
        cout << "2. Xem danh sach xe\n";
        cout << "3. Sua thong tin xe\n";
        cout << "4. Xoa xe\n";
        cout << "5. Tim kiem xe\n";
        cout << "6. Luu du lieu\n";
        cout << "0. Thoat\n";
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
                break;
            default: cout << ">> Lua chon khong hop le!\n";
        }
        
        if (choice != 0) dungManHinh();
        
    } while (choice != 0);
    
    return 0;
}
