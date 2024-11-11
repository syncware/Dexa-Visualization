#include <napi.h>
#include <unordered_map>
#include <iostream>
#include <string>
#include "src/cpp/Forecast/ProductionForecast/DateCreation.h"
#include "src/cpp/Forecast/utilities/runForecastAsyncWorkerModifiedT.h"
#include "src/cpp/Forecast/utilities/runForecastAsyncWorker.h"
#include "src/cpp/Forecast/utilities/AllWellsYearlyResultNewAsyncT.h"
#include "src/cpp/Forecast/utilities/PlotChartAsyncWorker.h"
#include "src/cpp/learnings/Circle.h"
#include "src/cpp/learnings/Rectangle.h"
#include "src/cpp/learnings/Shape.h"
#include "src/cpp/learnings/Singleton.h"
#include "src/cpp/learnings/LinkedList.h"
#include "src/cpp/learnings/BinarySearchTree.h"
#include "src/cpp/learnings/HashTable.h"
#include "src/cpp/learnings/Stack.h"
#include "src/cpp/learnings/HackRankTest.h"

using namespace std;


void getDays();
json ReadJsonFile(string jsonFileName);
void runForecast();
void export_to_file(const json& j, const string& filename);
void plotChat();
void plotChat2();
void testInheritance(); // The same with abstraction
void testPolymorphism();
void testEncapsulation();
void testSetSingletonValue();
void testGetSingletonValue();
void testLinkedList();
void testBinaryTreeSearch();
void testHashTable();
void testStackList();
int lengthOfLongestSubstring(string s);
void testHackRankTest();
pair<int, string> lengthOfLongestSubstring2(string s);

DateCreation dateCreation;

//Initialize static member

int main(){
    //getDays();
    // runForecast();
    plotChat2();
    //testInheritance();
    //testPolymorphism();
    //testEncapsulation();
    //testSetSingletonValue();
    //testGetSingletonValue();
    //testBinaryTreeSearch();
    //testLinkedList();
    //testHashTable();
    //testStackList();

    // string s = "bbbbb";
    // int a = lengthOfLongestSubstring(s);

    // auto result = lengthOfLongestSubstring2(s);
    // cout << "Length of the longest substring without repeating characters: " << result.first << endl;
    // cout << "Longest substring: " << result.second << endl;

    //testHackRankTest();
    return 0;
}

void testHackRankTest() {
    HackRankTest hackRankTest;
    // string ss = "Gabriel";
    // string ans = hackRankTest.isPalindrome(ss);
    // bool isAscending = false;
    // vector<int> vec = {2, 7, 4, 6, 1, 3, 5};
    // hackRankTest.sortIntegers(vec, isAscending);
    int n = 6;
    hackRankTest.fibonacci(n);
    int a = 0;
}

int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> charIndexMap; // To store the latest index of each character
    int maxLength = 0; // To store the result
    int start = 0;     // Left pointer of the window

    for (int end = 0; end < s.length(); end++) {
        char currentChar = s[end];

        // If the character is found in the map and is in the current window, move the start pointer
        if (charIndexMap.find(currentChar) != charIndexMap.end() && charIndexMap[currentChar] >= start) {
            start = charIndexMap[currentChar] + 1;
        }

        // Update the character's latest index
        charIndexMap[currentChar] = end;

        // Calculate the maximum length of substring
        maxLength = max(maxLength, end - start + 1);
    }

    return maxLength;
}

pair<int, string> lengthOfLongestSubstring2(string s) {
    unordered_map<char, int> charIndexMap; // To store the latest index of each character
    int maxLength = 0;     // To store the maximum length
    int start = 0;         // Left pointer of the window
    int maxStart = 0;      // Start index of the longest substring

    for (int end = 0; end < s.length(); end++) {
        char currentChar = s[end];

        // If the character is found in the map and is in the current window, move the start pointer
        if (charIndexMap.find(currentChar) != charIndexMap.end() && charIndexMap[currentChar] >= start) {
            start = charIndexMap[currentChar] + 1;
        }

        // Update the character's latest index
        charIndexMap[currentChar] = end;

        // Calculate the maximum length and update the starting index of the longest substring
        if (end - start + 1 > maxLength) {
            maxLength = end - start + 1;
            maxStart = start;
        }
    }

    // Extract the longest substring
    string longestSubstring = s.substr(maxStart, maxLength);

    return {maxLength, longestSubstring}; // Return both the length and the longest substring
}

void testStackList() {

     StackDouble stack(4);

    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.display();  // Output: 10 20 30

    stack.pop();
    stack.display();  // Output: 10 20

    std::cout << "Top element: " << stack.peek() << std::endl;  // Output: 20
}

void testHashTable() {
    HashTable ht(7);
    ht.insert(10);
    ht.insert(20);
    ht.insert(5);
    ht.insert(25);

    ht.display();  // Output example: 25 Empty 5 10 20 Empty Empty

    std::cout << "Search 20: " << (ht.search(20) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 15: " << (ht.search(15) ? "Found" : "Not Found") << std::endl;
}

void testBinaryTreeSearch() {
     BinarySearchTree bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    bst.inorder();  // Output: 20 30 40 50 60 70 80

    std::cout << "Search 40: " << (bst.search(40) ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 25: " << (bst.search(25) ? "Found" : "Not Found") << std::endl;
}

void testLinkedList() {
    LinkedList list;
    list.insert(10);
    list.insert(20);
    list.insert(30);
    list.display();  // Output: 30 -> 20 -> 10 -> NULL

    list.remove(20);
    list.display();  // Output: 30 -> 10 -> NULL
}

void testSetSingletonValue() {
    Singleton* s1 = Singleton::getInstance();
    s1->setValue(100);
}

void testGetSingletonValue() {
    Singleton* s2 = Singleton::getInstance();
    std::cout << "Value in singleton: " << s2->getValue() << std::endl;
}

void testEncapsulation(){
    Rectangle rectangle("Rectangle", 4.0, 5.0);

    std::cout << rectangle.getName() << "Rectangle Area: "
    << rectangle.area() << std::endl;

    // Access and modify using setter methods
    rectangle.setLength(10.0);
    rectangle.setWidth(4.0);

    std::cout << rectangle.getName() << "Updated Rectangle Area: "
    << rectangle.area() << std::endl;

}

void testPolymorphism() {
    // Creating instance of derived classes
    Circle circle("Circle", 5.0);
    Rectangle rectangle("Rectangle", 4.0, 6.0);

   // Vector of Shape pointers (polymorphism)
   std::vector<Shape*> shapes = {
    &circle,
    &rectangle
   };

    for(Shape* shape: shapes){
        std::cout << shape->getName() << "Area: " <<
        shape->area() << std::endl;
    }
}

void testInheritance() {
    Circle circle("Circle", 5.0);
    Rectangle rectangle("Rectangle", 4.0, 6.0);

    std::cout << circle.getName() << " Area: "
    << circle.area() << std::endl;

    std::cout << rectangle.getName() << "Area: "
    << rectangle.area() << std::endl;
}

void getDays(){
    int month = 3;
    int days = dateCreation.DaysInMonth(month);
    int cc = 0;
}

json ReadJsonFile(string jsonFileName) {
    std::ifstream file(jsonFileName);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open JSON file");
    }

    json jsonData;
    file >> jsonData;
    file.close();

    return jsonData;
}

void runForecast() {
    json jsonData = ReadJsonFile("C:/Users/Gabriel/Documents/Softwares/Syncware/Pet_App/pet_app/files/forecast_input_data_updated.json");
    RunForecastAsyncWorkerModifiedTest runForecastAsyncWorkerModifiedTest;
    json responseJsonData = runForecastAsyncWorkerModifiedTest.RunForecast(jsonData);
    export_to_file(responseJsonData, 
    "C:/Users/Gabriel/Documents/Softwares/Syncware/Pet_App/pet_app/files/forecast_output_data.json");
}

void plotChat() {
    json jsonData = ReadJsonFile("C:/Users/Gabriel/Documents/Softwares/Syncware/Pet_App/pet_app/forecast_chat_data_input.json");
    AllWellsYearlyResultNewAsyncT allWellsYearlyResultNewAsyncT;
    json responseJsonData = allWellsYearlyResultNewAsyncT.Plot(jsonData);
    export_to_file(responseJsonData, 
    "C:/Users/Gabriel/Documents/Softwares/Syncware/Pet_App/pet_app/forecast_chat_data_output.json");
}

void plotChat2() {
    json forecastResultsJsonData = ReadJsonFile("C:/Users/Gabriel/Documents/Softwares/Syncware/Pet_App/pet_app/files/apex_forecast_db.forecast_forecastresultsbymodules.json");
    AllWellsYearlyResultNewAsyncT allWellsYearlyResultNewAsyncT;
    json chatInputJsonData = ReadJsonFile("C:/Users/Gabriel/Documents/Softwares/Syncware/Pet_App/pet_app/files/forecast_chat_data_input.json");
    json responseJsonData = 
    allWellsYearlyResultNewAsyncT.PlotChart(forecastResultsJsonData, chatInputJsonData);
    export_to_file(responseJsonData, 
    "C:/Users/Gabriel/Documents/Softwares/Syncware/Pet_App/pet_app/files/forecast_chat_data_output.json");
}



void export_to_file(const json& j, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4); // Pretty print with 4 spaces
        file.close();
        cout << "JSON saved to " << filename << endl;
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}


Napi::Value runForecastAsync(const Napi::CallbackInfo& info) {
     Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    Napi::Object wrappedInstance = info[0].As<Napi::Object>();
    Napi::Function callback = info[1].As<Napi::Function>();

    RunForecastAsyncWorker* asyncWorker = new RunForecastAsyncWorker(wrappedInstance, callback);
    asyncWorker->Queue();

    string msg = "runForecastAsync running...";

    return Napi::String::New(info.Env(), msg.c_str());

}

Napi::Value plotChartAsync(const Napi::CallbackInfo& info) {
     Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    Napi::Object wrappedInstance = info[0].As<Napi::Object>();
    Napi::Function callback = info[1].As<Napi::Function>();

    PlotChartAsyncWorker* asyncWorker = new PlotChartAsyncWorker(wrappedInstance, callback);
    asyncWorker->Queue();

    string msg = "plotChartAsync running...";

    return Napi::String::New(info.Env(), msg.c_str());

}


Napi::Object Init(Napi::Env env, Napi::Object exports){

    exports.Set(
		Napi::String::New(env, "runForecastAsync"), // property name => "runForecastAsync"
		Napi::Function::New(env, runForecastAsync)  //property value => 'runForecastAsync' function
	);

    exports.Set(
		Napi::String::New(env, "plotChartAsync"), // property name => "runForecastAsync"
		Napi::Function::New(env, plotChartAsync)  //property value => 'runForecastAsync' function
	);

	//return 'exports' object (always)
	return exports;
}

NODE_API_MODULE(volumeforecast, Init)