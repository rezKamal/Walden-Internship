#include "zipcodes.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        throw runtime_error("Invalid command line arguments");
    }
    int algo = stoi(argv[1]);
    if (algo != 0 && algo != 1) {
        throw runtime_error("Invalid command line arguments"); 
    }
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
/*    file1.open("success.txt");
    file2.open("convergence.txt"); */

/*    
    for (int i=0; i < shares.size(); i++) {
        file2 << shares[i]->modifiedConvergence() << '\n';
        file3 << shares[i]->code                  << '\n';
    } */
//    for (int i=18; i < shares[50]->makeupDays.size()-10; i++) {
  //      cout << shares[50]->modifiedAlgo2(shares[50]->makeupDays[i],shares[50]->makeupDays[i])-shares[50]->makeupDays[i] << '\n';

    //}

/*    cout << shares[50]->modifiedAlgo2(708,708) << endl;
    cout << shares[50]->modifiedConvergence() << endl;
    cout << shares[50]->convergence() << endl; */
/*    for (int i=18; i < makeupDays.size()-15; i++) {
        float success = modifiedSuccess(makeupDays, shares, makeupDays[i].first);
        cout << "Success rate for " << makeupDays[i].first << " = " << success << '\n';
 //       file1 << success << '\n';
    } */
/*    for (int i=0; i < shares.size(); i++) {
        shares[i]->findMakeupGroup(makeupGroups);
        shares[i]->findMakeupDays(makeupDays);
        shares[i]->findDeliveryDays(deliveryDays);
        file2 << shares[i]->convergence() << '\n';
        file3 << shares[i]->code          << '\n';
    } */
    file1.close();
    file2.close();
    file3.close();
    return 0;
}