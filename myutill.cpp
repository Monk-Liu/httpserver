#include "myutill.h"

vector<string> split(const string & str, const string &sen){
    vector<string> res;
    size_t start=0, end=0;
    while((end=str.find(sen, start))!=string::npos){
        res.push_back(str.substr(start, end-start));
        start = end + sen.size();
    }

    if(end!=start && start < end){
        res.push_back(str.substr(start, end-start));
    }
    return res;

}
//template??
void pv(vector<string> & v){
    for(int i=0; i< v.size(); i++){
       cout<<i<<v[i]<<endl;
    }
}
