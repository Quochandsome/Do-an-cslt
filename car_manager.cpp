#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <string>
#include <cctype>
#include <iomanip>
#include "car_manager.h"

using namespace std;

bool idExists(Car carList[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (carList[i].id == id) {
            return true;
        }
    }
    return false;
}

void toUpperString(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

void loadFromFile(Car carList[], int &count, const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Chưa có file dữ liệu. Bắt đầu với danh sách trống.\n";
        count = 0;
        return;
    }
    
    count = 0;
    string line;
    
    while (getline(file, line) && count < MAX_CARS) {
        if (line.empty()) {
            continue;
        }
        
        stringstream ss(line);
        string token;
        Car car;
        
        if (getline(ss, token, ',')) {
            car.id = stoi(token);
        }
        
        if (getline(ss, token, ',')) {
            strcpy(car.brand, token.c_str());
        }
        
        if (getline(ss, token, ',')) {
            strcpy(car.model, token.c_str());
        }
        
        if (getline(ss, token, ',')) {
            strcpy(car.fuel, token.c_str());
        }
        
        if (getline(ss, token, ',')) {
            car.horsepower = stoi(token);
        }
        
        if (getline(ss, token, ',')) {
            car.price = stod(token);
        }
        
        if (getline(ss, token, ',')) {
            strcpy(car.status, token.c_str());
        }
        
        carList[count] = car;
        count++;
    }
    
    file.close();
    cout << "Đã tải " << count << " xe từ file dữ liệu.\n";
}

void addCar(Car carList[], int &count) {
    if (count >= MAX_CARS) {
        cout << "DANH SÁCH ĐÃ ĐẦY. KHÔNG THỂ THÊM XE MỚI\n";
        return;
    }
    
    Car newCar;
    cout << "\nTHÊM XE MỚI\n";

    do {
        cout << "ID (số nguyên duy nhất): ";
        cin >> newCar.id;
        
        if (idExists(carList, count, newCar.id)) {
            cout << "ID đã tồn tại, hãy nhập ID khác\n";
        } else if (newCar.id <= 0) {
            cout << "ID phải là số nguyên dương!\n";
        } else {
            break;
        }
    } while (true);
    
    cin.ignore();
    
    cout << "Hãng xe: ";
    cin.getline(newCar.brand, 50);
    
    cout << "Model: ";
    cin.getline(newCar.model, 50);
    
    cout << "Nhiên liệu (Xăng/Dầu/Điện): ";
    cin.getline(newCar.fuel, 20);
    
    cout << "Mã lực (HP): ";
    while (!(cin >> newCar.horsepower) || newCar.horsepower <= 0) {
        cout << "Mã lực phải là số dương: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    
    cout << "Giá (VND): ";
    while (!(cin >> newCar.price) || newCar.price <= 0) {
        cout << "Giá phải là số dương: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    
    cin.ignore();
    cout << "Trạng thái (Còn hàng/Đã bán/Bảo trì): ";
    cin.getline(newCar.status, 20);

    carList[count] = newCar;
    count++;

    saveToFile(carList, count, "data_xe.txt");
    cout << "\nĐÃ THÊM XE THÀNH CÔNG\n";
    cout << "Thông tin: " << newCar.brand << " " << newCar.model 
         << " - Giá: " << newCar.price << " VND\n";
}

void viewCars(Car carList[], int count) {
    cout << "\nDANH SÁCH XE\n";
    
    if (count == 0) {
        cout << "Danh sách xe trống!\n";
        return;
    }
    
    cout << "                                       \n";
    cout << "| ID  | Hãng xe        | Model         | Giá (VND)     | Trạng thái |\n";
    cout << "                                       \n";
    
    for (int i = 0; i < count; i++) {
        printf("| %-3d | %-14s | %-13s | %-13.0f | %-11s |\n",
               carList[i].id,
               carList[i].brand,
               carList[i].model,
               carList[i].price,
               carList[i].status);
    }
    
    cout << "                                       \n";
    cout << "Tổng số: " << count << " xe\n";
}

void saveToFile(Car carList[], int count, const char* filename) {
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
             << carList[i].price << ","
             << carList[i].status << "\n";
    }
    
    file.close();
    cout << "Đã lưu " << count << " xe vào file.\n";
}

void editCar(Car carList[], int count) {
    if (count == 0) {
        cout << "Danh sách hiện không có xe nào để sửa!\n";
        return;
    }
    
    int id;
    cout << "\nSỬA THÔNG TIN XE\n";
    cout << "Nhập ID xe cần sửa: ";
    cin >> id;
    
    int index = -1;
    for (int i = 0; i < count; i++) {
        if (carList[i].id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        cout << "Không tìm thấy xe với ID " << id << endl;
        return;
    }
    
    cout << "\nTHÔNG TIN HIỆN TẠI CỦA XE " << id << ":\n";
    cout << "1. Hãng xe: " << carList[index].brand << endl;
    cout << "2. Model: " << carList[index].model << endl;
    cout << "3. Nhiên liệu: " << carList[index].fuel << endl;
    cout << "4. Mã lực: " << carList[index].horsepower << " HP" << endl;
    cout << "5. Giá: " << carList[index].price << " VND" << endl;
    cout << "6. Trạng thái: " << carList[index].status << endl;
    
    int choice;
    cout << "\nChọn phần muốn sửa (1-6, 0: Hủy): ";
    cin >> choice;
    
    if (choice == 0) {
        cout << "Đã hủy thao tác sửa!\n";
        return;
    }
    
    cin.ignore();
    
    switch (choice) {
        case 1:
            cout << "Nhập hãng xe mới: ";
            cin.getline(carList[index].brand, 50);
            break;
        case 2:
            cout << "Nhập model mới: ";
            cin.getline(carList[index].model, 50);
            break;
        case 3:
            cout << "Nhập nhiên liệu mới: ";
            cin.getline(carList[index].fuel, 20);
            break;
        case 4:
            cout << "Nhập mã lực mới: ";
            while (!(cin >> carList[index].horsepower) || carList[index].horsepower <= 0) {
                cout << "Mã lực phải là số dương: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore();
            break;
        case 5:
            cout << "Nhập giá mới: ";
            while (!(cin >> carList[index].price) || carList[index].price <= 0) {
                cout << "Giá phải là số dương: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore();
            break;
        case 6:
            cout << "Nhập trạng thái mới (Còn hàng/Đã bán/Bảo trì): ";
            cin.getline(carList[index].status, 20);
            break;
        default:
            cout << "Lựa chọn không hợp lệ!\n";
            return;
    }
    
    saveToFile(carList, count, "data_xe.txt");
    cout << "ĐÃ CẬP NHẬT THÔNG TIN XE THÀNH CÔNG!\n";
}

void deleteCar(Car carList[], int &count) {
    if (count == 0) {
        cout << "Danh sách xe hiện trống, không có gì để xóa.\n";
        return;
    }
    
    int id;
    cout << "\nXÓA XE\n";
    cout << "Nhập ID xe cần xóa: ";
    cin >> id;
    
    int index = -1;
    for (int i = 0; i < count; i++) {
        if (carList[i].id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        cout << "Không tìm thấy xe với ID: " << id << endl;
        return;
    }
    
    cout << "\nTHÔNG TIN XE SẼ XÓA:\n";
    cout << "ID: " << carList[index].id << endl;
    cout << "Hãng: " << carList[index].brand << endl;
    cout << "Model: " << carList[index].model << endl;
    cout << "Giá: " << carList[index].price << " VND" << endl;
    
    char confirm;
    cout << "\nBạn có chắc chắn muốn xóa xe này? (y/n): ";
    cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        for (int i = index; i < count - 1; i++) {
            carList[i] = carList[i + 1];
        }
        count--;
        
        saveToFile(carList, count, "data_xe.txt");
        cout << "ĐÃ XÓA XE THÀNH CÔNG\n";
    } else {
        cout << "ĐÃ HỦY VIỆC XÓA\n";
    }
}

void searchCar(Car carList[], int count) {
    if (count == 0) {
        cout << "Danh sách xe hiện trống, không có gì để tìm\n";
        return;
    }
    
    int choice;
    cout << "\nTÌM KIẾM XE\n";
    cout << "1. Tìm theo ID xe\n";
    cout << "2. Tìm theo hãng xe\n";
    cout << "3. Tìm theo khoảng giá\n";
    cout << "4. Tìm theo trạng thái\n";
    cout << "Lựa chọn: ";
    cin >> choice;
    
    bool found = false;
    int foundCount = 0;
    
    switch (choice) {
        case 1: { 
            int id;
            cout << "Nhập ID cần tìm: ";
            cin >> id;
            
            for (int i = 0; i < count; i++) {
                if (carList[i].id == id) {
                    cout << "\nTÌM THẤY XE:\n";
                    cout << "ID: " << carList[i].id << endl;
                    cout << "Hãng: " << carList[i].brand << endl;
                    cout << "Model: " << carList[i].model << endl;
                    cout << "Nhiên liệu: " << carList[i].fuel << endl;
                    cout << "Mã lực: " << carList[i].horsepower << " HP" << endl;
                    cout << "Giá: " << carList[i].price << " VND" << endl;
                    cout << "Trạng thái: " << carList[i].status << endl;
                    found = true;
                    foundCount++;
                    break;
                }
            }
            break;
        }
        
        case 2: { 
            char brand[50];
            cout << "Nhập tên hãng xe: ";
            cin.ignore();
            cin.getline(brand, 50);
            
            cout << "\nKẾT QUẢ TÌM KIẾM:\n";
            for (int i = 0; i < count; i++) {
                char tempBrand[50];
                strcpy(tempBrand, carList[i].brand);
                toUpperString(tempBrand);
                char searchBrand[50];
                strcpy(searchBrand, brand);
                toUpperString(searchBrand);
                
                if (strstr(tempBrand, searchBrand) != NULL) {
                    cout << "ID: " << carList[i].id << " | "
                         << carList[i].brand << " " << carList[i].model
                         << " | Giá: " << carList[i].price << " VND"
                         << " | TT: " << carList[i].status << endl;
                    found = true;
                    foundCount++;
                }
            }
            break;
        }
        
        case 3: {
            double minPrice, maxPrice;
            cout << "Nhập giá thấp nhất: ";
            cin >> minPrice;
            cout << "Nhập giá cao nhất: ";
            cin >> maxPrice;
            
            if (minPrice > maxPrice) {
                double temp = minPrice;
                minPrice = maxPrice;
                maxPrice = temp;
            }
            
            cout << "\nKẾT QUẢ TÌM KIẾM (" << minPrice << " - " << maxPrice << " VND):\n";
            for (int i = 0; i < count; i++) {
                if (carList[i].price >= minPrice && carList[i].price <= maxPrice) {
                    cout << "ID: " << carList[i].id << " | "
                         << carList[i].brand << " " << carList[i].model
                         << " | Giá: " << carList[i].price << " VND"
                         << " | TT: " << carList[i].status << endl;
                    found = true;
                    foundCount++;
                }
            }
            break;
        }
        
        case 4: {
            char status[20];
            cout << "Nhập trạng thái (Còn hàng/Đã bán/Bảo trì): ";
            cin.ignore();
            cin.getline(status, 20);
            
            cout << "\nKẾT QUẢ TÌM KIẾM:\n";
            for (int i = 0; i < count; i++) {
                char tempStatus[20];
                strcpy(tempStatus, carList[i].status);
                toUpperString(tempStatus);
                char searchStatus[20];
                strcpy(searchStatus, status);
                toUpperString(searchStatus);
                
                if (strcmp(tempStatus, searchStatus) == 0) {
                    cout << "ID: " << carList[i].id << " | "
                         << carList[i].brand << " " << carList[i].model
                         << " | Giá: " << carList[i].price << " VND"
                         << " | TT: " << carList[i].status << endl;
                    found = true;
                    foundCount++;
                }
            }
            break;
        }
        
        default:
            cout << "Lựa chọn không hợp lệ!\n";
            return;
    }
    
    if (found) {
        cout << "\nTìm thấy " << foundCount << " xe.\n";
    } else {
        cout << "\nKhông tìm thấy xe nào phù hợp.\n";
    }
}