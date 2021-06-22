#include "zipcodes.h"

int main() {
    ofstream file1;
    ofstream file2;
    ofstream file3;
    file1.open("shares.txt");
    file2.open("convergence.txt");
    file3.open("success.txt");
    vector<pair<int,int>> makeupDays = getMakeupDays();
    map<int,string> makeupGroups = getMakeupGroups();
    vector<pair<int,vector<int>>> deliveryDays = getDeliveryDays();
    vector<ZipCode*> shares = getAllShares(makeupGroups, makeupDays, deliveryDays);
    for (int i=0; i < shares.size(); i++) {
        file1 << shares[i]->code << '\n';
    }
    for (int i=0; i < shares.size(); i++) {
        file2 << shares[i]->convergence(algo) << '\n';
    }
    for (int i=18; i < makeupDays.size()-15; i++) {
            float success = successRate(makeupDays, shares, makeupDays[i].first, algo);
            file3 << success << '\n';
        }
    file1.close();
    file2.close();
    file3.close();
    return 0;
}
