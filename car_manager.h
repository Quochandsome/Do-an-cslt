#ifndef CAR_MANAGER_H
#define CAR_MANAGER_H

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

void addCar(Car carList[], int &count);
void editCar(Car carList[], int count);
void deleteCar(Car carList[], int &count);
void viewCars(Car carList[], int count);
void searchCar(Car carList[], int count);
void saveToFile(Car carList[], int count, const char* filename);
void loadFromFile(Car carList[], int &count, const char* filename);

#endif