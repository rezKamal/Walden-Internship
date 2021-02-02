/*
    Author: Rezhwan A Kamal
    Date:   Jan 19 2021
    For:    Walden Local Meat Co.
*/

#include "zipcodes.h"

ZipCode::ZipCode(int code) {
    this->code = code;
}

ZipCode::~ZipCode() {
    delete this;
}

/*
    @param   :  mapping of codes to makeup groups
    @returns :  (void) assigns makeup group to zip code 
*/
void ZipCode::findMakeupGroup(map<int,string> makeupGroups) {
    this->group = makeupGroups[this->code];
}

/*
    @param   :  list of makeup days and their delivery routines
    @returns :  (void) assigns list of eligible makeup days for zip code   
*/
void ZipCode::findMakeupDays(vector<pair<int,int>> makeupDays) {
    vector<int> elg_MakeupDays;
    int r = 0;
    for (int i=0; i < makeupDays.size(); i++) {
        r = makeupDays[i].second;
        if (this->group == "North North" && (r == 10 || r == 2 || r == 6)) {
            elg_MakeupDays.push_back(makeupDays[i].first);
        } else if (this->group == "North South" && (r == 5 || r == 1)) {
            elg_MakeupDays.push_back(makeupDays[i].first);
        } else if (this->group == "South East" && (r == 5 || r == 4 || r == 6)) {
            elg_MakeupDays.push_back(makeupDays[i].first);
        } else if (this->group == "South West" && (r == 10 || r == 8)) {
            elg_MakeupDays.push_back(makeupDays[i].first);
        }
    }
    this->makeupDays = elg_MakeupDays;
}

/*
    @param   :  list of delivery days and the zip codes they deliver to
    @returns :  (void) assigns list of eligible delivery days for zip code
*/
void ZipCode::findDeliveryDays(vector<pair<int,vector<int>>> deliveryDays) {
    vector<int> elg_DeliveryDays;
    for (int i=0; i < deliveryDays.size(); i++) {
        for (int j=0; j < deliveryDays[i].second.size(); j++) {
            if (deliveryDays[i].second[j] == this->code) {
                elg_DeliveryDays.push_back(deliveryDays[i].first);
            }
        }
    }
    this->deliveryDays = elg_DeliveryDays;
}

/*
    @param   :  date of last delivery (as a service day no.)
    @returns :  date of next delivery based on algorithm
*/
int ZipCode::algorithm(int date) {
    // Identify date of last delivery (either using historical data, or by choosing a makeup day from the previous month)
    // Look up next projected delivery day based off of zip group
    // If date is within 15-35 days of last delivery: use that day
    // Else continue
    // Get a list of eligible makeup days (15-42 days away)
    // If no days remain, pick the next normal service day > 14 days away
    // Calculate difference in days from each makeup day to the last delivery 
    // Pick the makeup day closest to 30 days away
    int diff, x = 0;
    int small = 3000;
    vector<int> elg_MakeupDays;
    vector<int> offsets;
    for (int i=0; i < this->deliveryDays.size(); i++) {
        if (this->deliveryDays[i] > date) {
            diff = this->deliveryDays[i] - date;
            if (diff >= 15 && diff <= 35) {
                return this->deliveryDays[i];
            }
            x = i;
        }
    }
    for (int i=0; i < this->makeupDays.size(); i++) {
        diff = this->makeupDays[i] - date;
        if (diff >= 15 && diff <= 42) {
            elg_MakeupDays.push_back(this->makeupDays[i]);
        }
    }
    if (elg_MakeupDays.size() == 0) {
        return this->deliveryDays[x];
    } else {
        for (int i=0; i < elg_MakeupDays.size(); i++) {
            if (elg_MakeupDays[i] <= date) {
                offsets.push_back(date - elg_MakeupDays[i]);
            } else {
                offsets.push_back(elg_MakeupDays[i] - date);
            }
        }
        for (int i=0; i < offsets.size(); i++) {
            if (offsets[i] < small) {
                small = offsets[i];
                x = i;
            }
        }
        return elg_MakeupDays[x];
    }
    return 1;
}

int ZipCode::algorithm2(int date, vector<int> dates) {
    int diff, x = 0;
    int small = 3000;
    vector<int> elg_MakeupDays;
    vector<int> offsets;
    for (int i=0; i < this->deliveryDays.size(); i++) {
        if (this->deliveryDays[i] > date) {
            diff = this->deliveryDays[i] - date;
            if (diff >= 15 && diff <= 35) {
                return this->deliveryDays[i];
            }
            x = i;
        }
    }
    for (int i=0; i < this->makeupDays.size(); i++) {
        diff = this->makeupDays[i] - date;
        if (diff >= 15 && diff <= 42) {
            elg_MakeupDays.push_back(this->makeupDays[i]);
        }
    }
    if (elg_MakeupDays.size() == 0) {
        return this->deliveryDays[x];
    } else {
        for (int i=0; i < elg_MakeupDays.size(); i++) {
            if (elg_MakeupDays[i] <= date) {
                offsets.push_back(date - elg_MakeupDays[i]);
            } else {
                offsets.push_back(elg_MakeupDays[i] - date);
            }
        }
        for (int i=0; i < offsets.size(); i++) {
            if (offsets[i] < small) {
                small = offsets[i];
                x = i;
            }
        }
        dates.push_back(elg_MakeupDays[x]);
        if (elg_MakeupDays[x]-dates[0] >= 80) {
            return dates[0]+80;
        } else {
            return algorithm2(elg_MakeupDays[x], dates);
        }
    }
    throw runtime_error("Unexpected outcome");
}

float ZipCode::convergence() {
    float acc = 0;
    int conv, date = 0;
    int size = this->makeupDays.size()-9;
    vector<int> dummy;
    for (int i=0; i < size; i++) {
        date = this->makeupDays[i];
        acc += this->algorithm2(date, dummy)-date;
    }
    return acc/size;
}

/*
    @param   :  (nothing)
    @returns :  list of makeup day delivery dates paired with their routines
*/
vector<pair<int,int>> getMakeupDays() {
    ifstream file1("service_day.txt");
    ifstream file2("region_lock.txt");
    vector<pair<int, int>> makeupDays;
    vector<int> Service_day;
    vector<int> region_lock;
    string data = "";
    while(getline(file1, data, '\n')) {
        Service_day.push_back(stoi(data));
    }
    while(getline(file2, data, '\n')) {
        region_lock.push_back(stoi(data));
    }
    file1.close();
    file2.close();
    for (int i=0; i < region_lock.size(); i++) {
        makeupDays.push_back(pair<int,int>(Service_day[i],region_lock[i]));
    }
    return makeupDays;
}

/*
    @param   :  (nothing)
    @returns :  list of delivery dates paired with eligible zip codes
*/
vector<pair<int,vector<int>>> getDeliveryDays() {
    ifstream file3("delivery_days.txt");
    ifstream file4("deliveries.txt");
    vector<pair<int,vector<int>>> deliveryDays;
    vector<int> days;
    string data = "";
    vector<vector<int>> deliveries;
    while(getline(file3,data,'\n')) {
        days.push_back(stoi(data));
    }
    while (getline(file4,data,'\n')) {
        vector<int> zips;
        stringstream ss(data);
        while (ss.good()) {   
            string zip;
            getline(ss,zip,',');
            zips.push_back(stoi(zip));
        }
        deliveries.push_back(zips);
    }
    for (int i=0; i < days.size(); i++) {
        deliveryDays.push_back(pair<int,vector<int>>(days[i],deliveries[i]));
    }
    file3.close();
    file4.close();
    return deliveryDays;
}

/*
    @param   :  (nothing)
    @returns :  mapping of zip codes to four makeup groups
*/
map<int,string> getMakeupGroups() {
    ifstream file1("code.txt");
    ifstream file2("makeup_group.txt");
    map<int,string> makeupGroups;
    vector<int> codes;
    vector<string> groups;
    string data = "";
    while (getline(file1, data, '\n')) {
        codes.push_back(stoi(data));
    }
    while (getline(file2, data, '\n')) {
        groups.push_back(data);
    }
    for (int i=0; i < codes.size(); i++) {
        makeupGroups[codes[i]] = groups[i];
    }
    file1.close();
    file2.close();
    return makeupGroups;
}

vector<ZipCode*> getAllShares() {
    ifstream file1("code.txt");
    vector<ZipCode*> shares;
    string data = "";
    while (getline(file1, data, '\n')) {
        ZipCode* zip = new ZipCode(stoi(data));
        shares.push_back(zip);
    }
    file1.close();
    return shares;
}

float successRate(vector<pair<int,int>> makeupDays, vector<ZipCode*> shares, int date) {
    int r, convDate = 0;
    float count = 0;
    vector<int> dummy;
    vector<ZipCode*> codes;
    for (int i=0; i < makeupDays.size(); i++) {
        if (makeupDays[i].first == date) {
            r = makeupDays[i].second;
        }
    }
    for (int i=0; i < shares.size(); i++) {
        if ((shares[i]->group == "North North" && (r == 10 || r == 6 || r == 2))
          || (shares[i]->group == "North South" && (r == 5 || r == 1))
          || (shares[i]->group == "South East" && (r == 5 || r == 4 || r == 6))
          || (shares[i]->group == "South West" && (r == 10 || r == 8))) {
            codes.push_back(shares[i]);
        }
    }
    for (int i=0; i < codes.size(); i++) {
        convDate = codes[i]->algorithm2(date, dummy);
        if (convDate-date < 60) {
            count++;
        }
    }
    return count/codes.size();
}