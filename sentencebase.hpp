#ifndef SENTENCEBASE_HPP
#define SENTENCEBASE_HPP

#include <string>
#include <vector>
#include <utility>
#include <iomanip>
#include <sstream>

#define NORTH 'N'
#define SOUTH 'S'
#define EAST 'E'
#define WEST 'W'

typedef std::vector<std::string> Fields_t;

class SentenceBase
{
public:
    SentenceBase();
    std::string talkerID;
    std::string sentenceID;
    Fields_t fields;

    std::string toStringInt(int i, int len){
        std::stringstream ss;
        if(i < 0){
            ss << '-';
            i = -i;
        }
        ss << std::setw(len) << std::setfill('0') << i;
        return ss.str();
    }

    //minimum is 1
    inline int intLen(int x){
        int a = 0;
        do
        {
            a++;
            x/=10;
        }while(x);
        return a;
    }

    std::string toStringFloat(double val, int precision){
        std::stringstream ss;
        int width = intLen(val) + precision + 1;
        if(val < 0){
            ss << '-';
            val = -val;
        }

        ss << std::fixed << std::setw(width) << std::setfill('0') << std::setprecision(precision) << val;
        return ss.str();
    }


    //https://stackoverflow.com/a/40497964
    std::string join(const std::vector<std::string> & v, const std::string & delimiter = ",") {
        std::string out;
        if (auto i = v.begin(), e = v.end(); i != e) {
            out += *i++;
            for (; i != e; ++i) out.append(delimiter).append(*i);
        }
        return out;
    }


    std::string timeTo_hhmmss(int hour, int minute, double second){
        char tmp[50];
        sprintf(tmp, "%02d%02d%05.2f", hour, minute, second);
        std::stringstream ss;
        ss << tmp;
        return ss.str();
    }

    std::pair<std::string, char> latDegreeTo_ddmm(double degree){
        int dd = degree;
        degree -= dd;
        char res = NORTH;
        if(dd < 0){
            dd = -dd;
            res = SOUTH;
        }
        double minute = degree * 60;
        char tmp[50];
        sprintf(tmp, "%02d%08.5f", dd, minute);
        std::stringstream ss;
        ss << tmp;
        return std::make_pair(ss.str(), res);
    }

    std::pair<std::string, char> longDegreeTo_ddmm(double degree){
        int dd = degree;
        degree -= dd;
        char res = EAST;
        if(dd < 0){
            dd = -dd;
            res = WEST;
        }
        double minute = degree * 60;
        char tmp[50];
        sprintf(tmp, "%03d%08.5f", dd, minute);
        std::stringstream ss;
        ss << tmp;
        return std::make_pair(ss.str(), res);
    }

    std::string generateSentence(){
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
};

#endif // SENTENCEBASE_HPP