#ifndef HDT_SENTENCE_H
#define HDT_SENTENCE_H

#include "sentencebase.hpp"


namespace nmea{
namespace hdt {

enum FieldsEnum{
	HEADING_DEGREES,
	T_Field,
    __FieldsEnum__MAX
};

class HDT_Sentence : public SentenceBase
{
public:
	HDT_Sentence(std::string talkerID)
    {
        this->fields = Fields_t(__FieldsEnum__MAX);
        this->talkerID = talkerID;
        this->sentenceID = "HDT";
    }

    void setHeading(double heading){
    	fields[HEADING_DEGREES] = toStringFloat(heading, 3);
        fields[T_Field] = "T";
    }

};



}
}


#endif // GLL_SENTENCE_H
