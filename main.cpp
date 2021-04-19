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
using namespace std;

// Selects Wines from the database where attribute # 'columnNum' matches 'term'
// Returns the result into the passed-in vector of wines
void selectData(const char* dir, int column, string match, vector<Wine>* result);
// Adopted from the SQLite documentation
// Retrieves data from the call in selectData() and passes the wines into the container
int callback(void* notused, int argc, char** argv, char** azColName);

int main() {
    const char* dataDir = "Data/wineData.db";
    vector<Wine> searchResults;
    searchResults.clear();
    selectData(dataDir, 1, "South Africa", &searchResults);
    for(Wine w : searchResults) {
        w.display();
    }
    return 0;
}

void selectData(const char* dir, int columnNum, string term, vector<Wine>* result) {
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
    sqlite3_exec(database, query.c_str(), callback, (void*) result, nullptr);
    sqlite3_close(database);
}

int callback(void* container, int argc, char** arg, char** azColName) {
    vector<Wine>* tempWines = (vector<Wine>*) container;

    string checkNull = arg[4];
    if(checkNull.size() == 0) return 0; // Return if the price is null

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