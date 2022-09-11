#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

class ListVect {
	list<vector<int>> data;
	struct iterator {
		list<vector<int>>::iterator begin;
		iterator(list<vector<int>>::iterator begin){
			this->begin=begin;
		}
		int& operator[](int index) {
			auto it=this->begin;
			while((*it).size()>=index){
				index-=(*it).size();
				it++;
			}
			return (*it)[index];
		}
	};
	iterator begin(){
		return iterator(this->data.begin());
	}
};

class Car {
	int speed, price;
	string type;
public:
	Car(int speed = 0, int price = 0, string type = "") {
		this->speed = speed;
		this->price = price;
		this->type = type;
	}

	int getSpeed() {
		return this->speed;
	}
	int getPrice() {
		return this->price;
	}
	string getType() {
		return this->type;
	}
	void setSpeed(int speed) {
		this->speed = speed;
	}
	void setPrice(int price) {
		this->price = price;
	}
	void setType(string type) {
		this->type = type;
	}
	void show() {
		cout << this->type << endl << "Max. speed " << this->speed << endl
				<< "Price " << this->price << "$" << endl;
	}
	friend bool compareBySpeed(Car*, Car*);
	friend bool compareByPrice(Car*, Car*);
	friend bool compareByType(Car*, Car*);
};

bool compareBySpeed(Car *first, Car *second) {
	return first->speed < second->speed;
}
bool compareByPrice(Car *first, Car *second) {
	return first->price < second->price;
}
bool compareByType(Car *first, Car *second) {
	return first->type < second->type;
}

typedef int (Car::*getIntCar)();
typedef bool (*carComparator)(Car*, Car*);

int main() {
	list<Car*> cars;
	cars.push_back(new Car(100, 50000, "Zaporozhets"));
	cars.push_back(new Car(150, 100000, "Lada Kalina"));
	cars.push_back(new Car(175, 150000, "Renault Lohan"));
	cars.push_back(new Car(165, 140000, "Ford Focus"));
	for (auto car : cars) {
		car->show();
	}

	list<carComparator> comparators;
	comparators.push_back(&compareByPrice);
	comparators.push_back(&compareBySpeed);
	comparators.push_back(&compareByType);

	for (auto comp : comparators) {
		cars.sort(*comp);
		for (auto car : cars)
			car->show();
		cout << endl << "----" << endl;
	}

//	carComparator comp1=&compareByPrice;
//	carComparator comp2=&compareBySpeed;
//	carComparator comp3=&compareByType;
//
//	cars.sort(*comp1);

	for (auto car : cars) {
		car->show();
	}

	getIntCar f1 = &Car::getPrice;
	getIntCar f2 = &Car::getSpeed;

	cout << cars.front()->getPrice() << endl;
	cout << (cars.front()->*f1)() << endl;
	cout << count_if(cars.begin(), cars.end(), [f1](Car *car) {
		return (car->*f1)() > 100000;
	}) << endl;

	return 0;
}
