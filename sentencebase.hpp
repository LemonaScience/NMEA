#ifndef SENTENCEBASE_HPP
#define SENTENCEBASE_HPP


#include <string>
#include <vector>
#include <utility>


#define NORTH 'N'
#define SOUTH 'S'
#define EAST 'E'
#define WEST 'W'

typedef std::vector<std::string> Fields_t;

namespace nmea {

struct Time {
    int hour;
    int minute;
    double second;
};

class SentenceBase
{
public:
    SentenceBase();
    std::string talkerID;
    std::string sentenceID;
    Fields_t fields;

    std::string toStringInt(int i, int len);

    //minimum is 1
    int intLen(int x);

    std::string toStringFloat(double val, int precision);


    std::string join(const std::vector<std::string> & v, const std::string delimiter = ",");


    std::string timeTo_hhmmss(int hour, int minute, double second);

    Time hhmmssToTime(std::string hhmmss);

    std::pair<std::string, char> latDegreeTo_ddmm(double degree);

    double ddmmToLatDegree(std::pair<std::string, char> in);

    std::pair<std::string, char> longDegreeTo_ddmm(double degree);

    double ddmmToLongDegree(std::pair<std::string, char> in);

    std::string generateSentence(bool addChecksum = true);



    //https://stackoverflow.com/a/14266139
    static Fields_t split(std::string sentence, std::string delimiter = ",");

    //https://stackoverflow.com/a/14266139
    static SentenceBase* parseSentence(std::string sentence);
};


}
#endif // SENTENCEBASE_HPP
