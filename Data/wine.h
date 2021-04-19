#pragma once
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
class Wine {
    string country, description, province, winery, variety, title;
    unsigned int num, points, price;
public:
    Wine(unsigned int num, string country, string description, unsigned int points, unsigned int price, string province, string title, string variety, string winery) {
        this->num = num;
        this->country = country;
        this->description = description;
        this->points = points;
        this->price = price;
        this->province = province;
        this->title = title;
        this->variety = variety;
        this->winery = winery;
    }
    unsigned int getNum() const {return num;}
    string getCountry() const {return country;}
    string getDescription() const {return description;}
    unsigned int getPoints() const {return points;}
    unsigned int getPrice() const {return price;}
    string getProvince() const {return province;}
    string getTitle() const {return title;}
    string getVariety() const {return variety;}
    string getWinery() const {return winery;}

    // Display the wine in the console
    void display() {
        cout << title << endl;
        cout << "Country: " << country << endl;
        cout << "Description: " << description << endl;
        cout << "Points: " << points << endl;
        cout << "Price: " << price << endl;
        cout << "Province: " << province << endl;
        cout << "Variety: " << variety << endl;
        cout << "Winery: " << winery << endl << endl;
    }
};