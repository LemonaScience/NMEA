#include "sentencebase.hpp"
#include "gga_sentence.hpp"

#undef str
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace nmea;

SentenceBase::SentenceBase(){

}

std::string SentenceBase::toStringInt(int i, int len){
    std::stringstream ss;
    if(i < 0){
        ss << '-';
        i = -i;
    }
    ss << std::setw(len) << std::setfill('0') << i;
    return ss.str();
}

int SentenceBase::intLen(int x){
    int a = 0;
    do
    {
        a++;
        x/=10;
    }while(x);
    return a;
}

std::string SentenceBase::toStringFloat(double val, int precision){
    std::stringstream ss;
    int width = intLen(val) + precision + 1;
    if(val < 0){
        ss << '-';
        val = -val;
    }

    ss << std::fixed << std::setw(width) << std::setfill('0') << std::setprecision(precision) << val;
    return ss.str();
}

std::string SentenceBase::join(const std::vector<std::string> &v, const std::string &delimiter) {
    std::string out;
    auto i = v.begin(), e = v.end();
    if ( i != e) {
        out += *i++;
        for (; i != e; ++i) out.append(delimiter).append(*i);
    }
    return out;
}

std::string SentenceBase::timeTo_hhmmss(int hour, int minute, double second){
    char tmp[50];
    sprintf(tmp, "%02d%02d%05.2lf", hour, minute, second);
    std::stringstream ss;
    ss << tmp;
    return ss.str();
}

Time SentenceBase::hhmmssToTime(std::string hhmmss){
    Time res;
    sscanf(hhmmss.c_str(), "%02d%02d%lf", &res.hour, &res.minute, &res.second);
    return res;
}

std::pair<std::string, char> SentenceBase::latDegreeTo_ddmm(double degree){
    int dd = degree;
    degree -= dd;
    char res = NORTH;
    if(dd < 0){
        dd = -dd;
        res = SOUTH;
    }
    double minute = degree * 60;
    char tmp[50];
    sprintf(tmp, "%02d%08.5lf", dd, minute);
    std::stringstream ss;
    ss << tmp;
    return std::make_pair(ss.str(), res);
}

double SentenceBase::ddmmToLatDegree(std::pair<std::string, char> in){
    double degree;
    int dd;
    double minute;
    sscanf(in.first.c_str(), "%02d%lf", &dd, &minute);
    degree = dd + minute / 60;
    return (in.second == NORTH ? 1 : -1) * degree;
}

std::pair<std::string, char> SentenceBase::longDegreeTo_ddmm(double degree){
    int dd = degree;
    degree -= dd;
    char res = EAST;
    if(dd < 0){
        dd = -dd;
        res = WEST;
    }
    double minute = degree * 60;
    char tmp[50];
    sprintf(tmp, "%03d%08.5lf", dd, minute);
    std::stringstream ss;
    ss << tmp;
    return std::make_pair(ss.str(), res);
}

double SentenceBase::ddmmToLongDegree(std::pair<std::string, char> in){
    double degree;
    int dd;
    double minute;
    sscanf(in.first.c_str(), "%03d%lf", &dd, &minute);
    degree = dd + minute / 60;
    return (in.second == EAST ? 1 : -1) * degree;
}

std::string SentenceBase::generateSentence(){
    std::stringstream res;
    res << "$";
    std::stringstream checksumIncluded;
    checksumIncluded << this->talkerID;
    checksumIncluded << this->sentenceID;
    checksumIncluded << "," << join(fields);
    unsigned checksum = 0;
    for(auto &c: checksumIncluded.str()){
        checksum ^= c;
    }
    res << checksumIncluded.str() << "*" << std::uppercase << std::hex << std::setfill('0') << std::setw(2) << checksum;
    res << "\r\n";
    return res.str();
}

Fields_t SentenceBase::split(std::string sentence, std::string delimiter){
    Fields_t res;

    size_t pos = 0;
    std::string token;
    while ((pos = sentence.find(delimiter)) != std::string::npos) {
        token = sentence.substr(0, pos);
        res.push_back(token);
        sentence.erase(0, pos + delimiter.length());
    }
    res.push_back(sentence);

    return res;
}

SentenceBase *SentenceBase::parseSentence(std::string sentence){

//	printf("before split\r\n");
    auto res = split(sentence);
//    printf("after split\r\n");

    std::string talkerID_tmp = res[0].substr(0, 2);
//    printf("talkerID_tmp: %s\r\n", talkerID_tmp.c_str());
    std::string sentenceID_tmp = res[0].substr(2, 3);
    printf("sentenceID_tmp: %s\r\n", sentenceID_tmp.c_str());

    SentenceBase *retVal = nullptr;

    if(sentenceID_tmp == "GGA"){
        //TODO, can cause memory leak, dont forget to delete
        retVal = new gga::GGA_Sentence(talkerID_tmp);
    }



    //.
    //.
    //.

    if(retVal && retVal->fields.size() + 1 == res.size()){
        for(unsigned i = 0; i < retVal->fields.size(); i++){
            retVal->fields[i] = res[i + 1];
        }
    } else if(retVal) {
    	delete retVal;
    	retVal = nullptr;
    }

    return retVal;
}
