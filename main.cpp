#include <iostream>
#include <cstdlib>
#include "car_manager.h"

using namespace std;

void Menu();

void Menu() {
    #ifdef _WIN32
        system("cls");  
    #else
        system("clear");
    #endif
    
    cout << "\nHỆ THỐNG QUẢN LÝ XE\n";
    cout << "1. Thêm xe mới\n";
    cout << "2. Xem danh sách xe\n";
    cout << "3. Sửa thông tin xe\n";
    cout << "4. Xóa xe\n";
    cout << "5. Tìm kiếm xe\n";
    cout << "6. Lưu dữ liệu\n";
    cout << "0. Thoát\n";
    cout << "Nhập lựa chọn: ";
}

int main() {
    Car carList[MAX_CARS];
    int count = 0;
    
    loadFromFile(carList, count, "data_xe.txt");
    
    int choice;
    do {
        Menu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                addCar(carList, count);
                break;
            case 2:
                viewCars(carList, count);
                break;
            case 3:
                editCar(carList, count);
                break;
            case 4:
                deleteCar(carList, count);
                break;
            case 5:
                searchCar(carList, count);
                break;
            case 6:
                saveToFile(carList, count, "data_xe.txt");
                cout << "\n✓ ĐÃ LƯU DỮ LIỆU THÀNH CÔNG!\n";
                break;
            case 0:
                saveToFile(carList, count, "data_xe.txt");
                cout << "\n ĐÃ LƯU DỮ LIỆU\n";
                cout << "   HẸN GẶP LẠI! \n";
                break;
            default:
                cout << "\n LỰA CHỌN KHÔNG HỢP LỆ. VUI LÒNG CHỌN LẠI!\n";
        }
        
        if (choice != 0) {
            cout << "\nNhấn Enter để tiếp tục...";
            cin.ignore();  
            cin.get();   
        }
        
    } while (choice != 0);
    
    return 0;
}