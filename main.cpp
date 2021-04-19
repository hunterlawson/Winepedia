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
    
   //Menu display
    cout<< "--------Winepedia--------" << endl;
    cout<< "1. Search by country" << endl;
    cout<< "2. Search by province" << endl;
    cout<< "3. Search by title" << endl;
    cout<< "4. Search by variety" << endl;
    cout<< "5. Search by winery" << endl;
    
    string colNumStr;
    cout<< "\nMenu Choice: ";
    getline(cin,colNumStr);
    int colNum = stoi(colNumStr);
    
    string searchItem;
    
   if (colNum == 1)
       cout<< "\nEnter country: ";
    else if (colNum == 2)
        cout<< "\nEnter province: ";
    else if (colNum == 3)
        cout<< "\nEnter title: ";
    else if (colNum == 4)
        cout<< "\nEnter variety: ";
    else if (colNum == 5)
        cout<< "\nEnter winery: ";   
  
    getline(cin,searchItem);  
    
    //Search by data structure
    string algoStr;
    
    cout<< "\nSorting Algorithm Options: " << endl;
    cout<< "1. Bubble Sort"<< endl;
    cout<< "2. Merge Sort" << endl;
    cout<< "3. Quick Sort" << endl;
    cout<< "\nEnter menu option number: ";
    getline(cin,algoStr);
    int algo = stoi(algoStr);
      
    cout<< "\nSearch by: "<< endl;
    cout<< "1. Points"<< endl;
    cout<< "2. Price" << endl;
    cout<< "\nEnter menu option number: ";
    string selectionStr;
    getline(cin,selectionStr);
    int selection = stoi(selectionStr);
    
    selectData(dataDir, colNum, searchItem, &searchResults);

     //Call sorting functions
    auto start = chrono::steady_clock::now();
    if (algo == 1)  { //bubble
        if (selection == 1) //points
            bubbleSortPoint(searchResults);            
        else if (selection == 2)   //price          
            bubbleSortPrice(searchResults);
    }
    else if (algo == 2) { //merge
         if (selection == 1) //points
            mergeSortPoints(searchResults,0,searchResults.size()-1);   
        else if (selection == 2)   //price        
            mergeSortPrice(searchResults,0,searchResults.size()-1);
    }
    else if (algo == 3) { //quick
          if (selection == 1) //points
            quickSortPoints(searchResults,0,searchResults.size()-1);
        else if (selection == 2)   //price      
            quickSortPrice(searchResults,0,searchResults.size()-1);
    }
    auto end = chrono::steady_clock::now();
    auto diff = end - start;

    for(Wine w : searchResults) {
        w.display();
    }

    cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
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
