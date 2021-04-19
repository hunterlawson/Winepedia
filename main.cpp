/*
    Annalina Becker
    Kabir Khara
    Hunter Lawson

    Winepedia - wine search engine
    To compile: 
        g++ main.cpp Data/sqlite3.o -o Winepedia.exe
*/

#include <string>
#include <vector>
#include "Data/sqlite3.h"
#include "Data/wine.h"
#include "Algorithms/sort.h"
using namespace std;

// Selects Wines from the database where attribute # 'columnNum' matches 'term'
// Returns the result into the passed-in pointer to a vector of wines
void selectData(const char* dir, int column, string match, vector<Wine>* container);
// Adopted from the SQLite documentation
// Retrieves data from the call in selectData() and passes the wines into the container
int callback(void* container, int argc, char** argv, char** azColName);

int main() {
    const char* dataDir = "Data/wineData.db";
    vector<Wine> searchResults;
    searchResults.clear();
    
   
    cout<< "--------Winepedia--------" << endl;
    cout<< "1. Search by country" << endl;
    cout<< "2. Search by province" << endl;
    cout<< "3. Search by title" << endl;
    cout<< "4. Search by variety" << endl;
    cout<< "5. Search by winery" << endl;
    
    int colNum;
    cout<< "Menu Choice: ";
    getline(cin,colNum);
    
    string searchItem;
    
   if (colNum == 1)
       cout<< "Enter country: ";
    else if (colNum == 2)
        cout<< "Enter province: ";
    else if (colNum == 3)
        cout<< "Enter title: ";
    else if (colNum == 4)
        cout<< "Enter variety: ";
    else if (colNum == 5)
        cout<< "Enter winery: ";
    
    getline(cin,searchItem);        
      
   
    selectData(dataDir, colNum, searchItem, &searchResults);
    for(Wine w : searchResults) {
        w.display();
    }
    return 0;
}

void selectData(const char* dir, int columnNum, string term, vector<Wine>* container) {
    sqlite3* database;
    sqlite3_open(dir, &database); // Open the database

    // Choose the correct name for the column depending on the choice for columnNum
    string columnName;
    switch(columnNum) {
        case 1: columnName = "Country"; break;
        case 2: columnName = "Province"; break;
        case 3: columnName = "Title"; break;
        case 4: columnName = "Variety"; break;
        case 5: columnName = "Winery"; break;
    }
    string query = "SELECT * FROM Wines WHERE " + columnName + " = \'" + term + "\';";
    sqlite3_exec(database, query.c_str(), callback, (void*) container, nullptr);
    sqlite3_close(database); // Close the database
}

int callback(void* container, int argc, char** arg, char** azColName) {
    vector<Wine>* tempWines = (vector<Wine>*) container;

    string checkNull = arg[4];
    if(checkNull.size() == 0) return 0; // Return 0 if the price is null

    int num = stoi(arg[0]);
    string country = arg[1];
    string description = arg[2];
    int points = stoi(arg[3]);
    int price = stoi(arg[4]);
    string province = arg[5];
    string title = arg[6];
    string variety = arg[7];
    string winery = arg[8];

    Wine tempWine(num, country, description, points, price, province, title, variety, winery);
    tempWines->push_back(tempWine);
    return 0;
}