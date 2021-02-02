#include "zipcodes.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Try again \n";
    }
    else {
        vector<pair<int,int>> makeupDays = getMakeupDays();
        map<int,string> makeupGroups = getMakeupGroups();
        vector<pair<int,vector<int>>> deliveryDays = getDeliveryDays();
        ZipCode* zip = new ZipCode(atoi(argv[1]), makeupGroups, makeupDays, deliveryDays);
        cout << "Zip Code     :  " << zip->code << '\n';
        cout << "Makeup Group :  " << zip->group << '\n';
        cout << "Next Delivery:  " << zip->algorithm(stoi(argv[2])) << '\n';
        cout << "New Algorithm:  " << zip->modifiedAlgo(stoi(argv[2])) << '\n';
        }
    return 0;
}