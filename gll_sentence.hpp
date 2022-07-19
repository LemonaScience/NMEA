#ifndef GLL_SENTENCE_H
#define GLL_SENTENCE_H

#include "sentencebase.hpp"


namespace nmea{
namespace gll {

enum FieldsEnum{
	LATITUDE,
	N_or_S,
	LONGITUDE,
	E_or_W,
	UTC,
	STATUS,
    __FieldsEnum__MAX
};

enum Validity {
    VALID = 'A',
    INVALID = 'V',
};

class GLL_Sentence : public SentenceBase
{
public:
	GLL_Sentence(std::string talkerID)
    {
        this->fields = Fields_t(__FieldsEnum__MAX);
        this->talkerID = talkerID;
        this->sentenceID = "GLL";
    }

    void setTime(int hour, int minute, double second){
        fields[UTC] = timeTo_hhmmss(hour, minute, second);
    }

    void setLatitude(double lat){
        auto tmp = latDegreeTo_ddmm(lat);
        fields[LATITUDE] = tmp.first;
        fields[N_or_S] = tmp.second;
    }

    void setLongitude(double lon){
        auto tmp = longDegreeTo_ddmm(lon);
        fields[LONGITUDE] = tmp.first;
        fields[E_or_W] = tmp.second;
    }

    void setStatus(bool valid){
    	if(valid){
    		fields[STATUS] = VALID;
    	} else {
    		fields[STATUS] = INVALID;
    	}
    }
};



}
}


#endif // GLL_SENTENCE_H
