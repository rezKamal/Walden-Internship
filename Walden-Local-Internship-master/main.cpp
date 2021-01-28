#include "zipcodes.h"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Try again \n";
    }
    else {
        ZipCode* zip = new ZipCode(atoi(argv[1]));
        vector<pair<int,int>> makeupDays = getMakeupDays();
        map<int,string> makeupGroups = getMakeupGroups();
        vector<pair<int,vector<int>>> deliveryDays = getDeliveryDays();
        zip->findMakeupGroup(makeupGroups);
        zip->findMakeupDays(makeupDays);
        zip->findDeliveryDays(deliveryDays);
        cout << "Zip Code No.:  " << zip->code << '\n';
        cout << "Makeup Group:  " << zip->group << '\n';
        cout << "Next Delivery: " << zip->algorithm(stoi(argv[2])) << '\n';
        }
    return 0;
}