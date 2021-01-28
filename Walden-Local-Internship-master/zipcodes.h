#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <sstream>

using namespace std;

class ZipCode {
    public:
        int code;
        string group;
        vector<int> makeupDays;
        vector<int> deliveryDays;
        ZipCode(int code);
        ~ZipCode();
        void findMakeupGroup(map<int,string> makeupGroups);
        void findMakeupDays(vector<pair<int,int>> makeupDays);
        void findDeliveryDays(vector<pair<int,vector<int>>> deliveryDays);
        int algorithm(int date);
        int algorithm2(int date, vector<int> dates);
        float convergence();
};

vector<pair<int,int>> getMakeupDays();
vector<pair<int,vector<int>>> getDeliveryDays();
vector<ZipCode*> getAllShares();
map<int,string> getMakeupGroups();
float successRate(vector<pair<int,int>> makeupDays, vector<ZipCode*> shares, int date);

