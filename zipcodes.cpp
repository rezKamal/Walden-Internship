#include "zipcodes.h"

ZipCode::ZipCode(int code, map<int,string> makeupGroups, vector<pair<int,int>> makeupDays,
                vector<pair<int,vector<int>>> deliveryDays) {
    this->code = code;
    this->findMakeupGroup(makeupGroups);
    this->findMakeupDays(makeupDays);
    this->findDeliveryDays(deliveryDays);
}

ZipCode::~ZipCode() {
    delete this;
}

void ZipCode::findMakeupGroup(map<int,string> makeupGroups) {
    this->group = makeupGroups[this->code];
}

/*
    Inputs  :  list of makeup days and their delivery routines
    Returns :  (void) assigns list of eligible makeup days for zip code   
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
    Inputs  :  list of delivery days and the zip codes they deliver to
    Returns :  (void) assigns list of eligible delivery days for zip code
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
    Inputs  :  date of last delivery (as a service day no.)
    Returns :  date of next delivery based on algorithm
*/
int ZipCode::algorithm(int date) {
  /*
      The code in this function has been REDACTED because it contains sensitive
      information pertaining to Walden's delivery algorithm.
  */
    throw runtime_error("Unexpected outcome");
}

/*
  Inputs: date of last delivery (date), current date (initial), and
          date after which algorithm will stop looking for the next
          eligible date (cutoff)
  Returns: date of next REGULAR delivery OR cutoff date, whichever
          comes sooner.
*/
int ZipCode::algorithm2(int date, int initial, int cutoff) {
    /*
       The code in this function has been REDACTED because it contains sensitive
       information pertaining to Walden's delivery algorithm.
    */
    throw runtime_error("Unexpected outcome");
}

/*
    Tweaked version of algorithm()
*/
int ZipCode::modifiedAlgo(int date) {
/*
   The code in this function has been REDACTED because it contains sensitive
   information pertaining to Walden's delivery algorithm.
*/
    throw runtime_error("Unexpected outcome");
}

float ZipCode::convergence(int algo) {
    int date, count = 0;
    float acc = 0;
    int size = this->makeupDays.size();
    for (int i=0; i < size; i++) {
        date = this->makeupDays[i];
        if (date > 700 && date < 935) {
            if (algo == 0) {
                acc += (this->algorithm2(date, date, 180)-date);
            } else if (algo == 1) {
                acc += (this->modifiedAlgo2(date, date, 180)-date);
            }
            count++;
        }
    }
    return acc/count;
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

vector<ZipCode*> getAllShares(map<int,string> makeupGroups, vector<pair<int,int>> makeupDays,
                vector<pair<int,vector<int>>> deliveryDays) {
    ifstream file1("code.txt");
    vector<ZipCode*> shares;
    string data = "";
    while (getline(file1, data, '\n')) {
        ZipCode* zip = new ZipCode(stoi(data), makeupGroups, makeupDays, deliveryDays);
        shares.push_back(zip);
    }
    file1.close();
    return shares;
}

float successRate(vector<pair<int,int>> makeupDays, vector<ZipCode*> shares, int date, int algo) {
    int r, convDate = 0;
    float count = 0;
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
        if (algo == 0) {
            convDate = codes[i]->algorithm2(date, date, 60);
        } else if (algo == 1) {
            convDate = codes[i]->modifiedAlgo2(date, date, 60);
        }
        if (convDate-date < 60) {
            count++;
        }
    }
    return count/codes.size();
}
