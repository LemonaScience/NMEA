#ifndef NMEA_HPP
#define NMEA_HPP

#include "nmeaparser.hpp"
#include "gga_sentence.hpp"



namespace nmea{


enum Sentences{
    GGA = 0,
    __SENTENCES_MAX
};

class Nmea{
public:
    NmeaParser<Nmea> parser;

    typedef void (*Callback)(void*);

    Callback callbacks[__SENTENCES_MAX];

    Nmea() : parser(this, &Nmea::_onParse){
        memset(callbacks, 0x00, sizeof(callbacks));

        callbacks[GGA] = defaultGGAcallback;
    }

    void setCallback(Sentences sent, Callback callback){
        callbacks[sent] = callback;
    }

    void parse(std::string str){
        for(unsigned i = 0; i < str.length(); i++){
            parser.parse(str[i]);
        }
    }

    static void defaultGGAcallback(void *ptr){
        std::cout << "Default GGA Callback\n";
        auto g = ((gga::GGA_Sentence*)ptr);
        Time t = g->getTime();

        std::cout << "hour: " << t.hour << std::endl;
        std::cout << "minute: " << t.minute << std::endl;
        std::cout << "second: " << t.second << std::endl;

        std::cout << "getLatitude: " << g->getLatitude() << std::endl;
        std::cout << "getLongitude: " << g->getLongitude() << std::endl;

        std::cout << "getGpsQualityIndicator: " << g->getGpsQualityIndicator() << std::endl;
        std::cout << "getNumberOfSatellitesInUse: " << g->getNumberOfSatellitesInUse() << std::endl;
        std::cout << "getHorizontalDilution: " << g->getHorizontalDilution() << std::endl;
        std::cout << "getAntennaAltitude: " << g->getAntennaAltitude() << std::endl;
        std::cout << "getGeoidalSeparation: " << g->getGeoidalSeparation() << std::endl;
        std::cout << "getAgeOfDifferentialGpsData: " << g->getAgeOfDifferentialGpsData() << std::endl;
        std::cout << "getDifferentialReferenceStation: " << g->getDifferentialReferenceStation() << std::endl;

    }

    void _onParse(std::string s){
        auto sb = SentenceBase::parseSentence(s);
        if(sb){
            if(sb->sentenceID == "GGA" && callbacks[GGA]){
                callbacks[GGA](sb);
            }
        }
    }
};



}




#endif // NMEA_HPP
