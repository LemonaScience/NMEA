#include "sentencebase.hpp"
#include "gga_sentence.hpp"

using namespace nmea;

SentenceBase *SentenceBase::parseSentence(std::string sentence){
    auto res = split(sentence);

    std::string talkerID_tmp = res[0].substr(0, 2);
    std::string sentenceID_tmp = res[0].substr(2, 3);

    SentenceBase *retVal = nullptr;

    if(sentenceID_tmp == "GGA"){
        //TODO, can cause memory leak, dont forget to delete
        retVal = new gga::GGA_Sentence(talkerID_tmp);
    }



    //.
    //.
    //.

    if(retVal){
        for(int i = 0; i < res.size(); i++){
            retVal->fields[i] = res[i + 1];
        }
    }

    return retVal;
}
