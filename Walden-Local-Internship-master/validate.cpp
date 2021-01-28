#include "zipcodes.h"

int main(int argc, char** argv) {
    ofstream file1;
    file1.open("success.txt");
    vector<pair<int,int>> makeupDays = getMakeupDays();
    
    map<int,string> makeupGroups = getMakeupGroups();
    vector<pair<int,vector<int>>> deliveryDays = getDeliveryDays();
    vector<ZipCode*> shares = getAllShares();
    for (int i=0; i < shares.size(); i++) {
        shares[i]->findMakeupGroup(makeupGroups);
        shares[i]->findMakeupDays(makeupDays);
        shares[i]->findDeliveryDays(deliveryDays);
    }
    for (int i=18; i < makeupDays.size()-17; i++) {
        float success = successRate(makeupDays, shares, makeupDays[i].first);
        cout << "Success rate for " << makeupDays[i].first << " = " << success << '\n';
        file1 << success << "\n";
    }
    ZipCode* zippy = new ZipCode(2420);
    cout << shares[50]->convergence() << endl;
    file1.close();
    return 0;
}