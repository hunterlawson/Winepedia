#include <string>
#include <iostream>
using namespace std;
class Wine {
    string country, description, province, winery, variety, title;
    unsigned int points, price;
public:
    Wine(string country, string description, unsigned int points, unsigned int price, string province, string title, string variety, string winery) {
        this->country = country;
        this->description = description;
        this->points = points;
        this->price = price;
        this->province = province;
        this->title = title;
        this->variety = variety;
        this->winery = winery;
    }
    string getCountry() const {return country;}
    string getDescription() const {return description;}
    unsigned int getPoints() const {return points;}
    unsigned int getPrice() const {return price;}
    string getProvince() const {return province;}
    string getTitle() const {return title;}
    string getVariety() const {return variety;}
    string getWinery() const {return winery;}
    
};