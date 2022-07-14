#ifndef VBW_SENTENCE_H
#define VBW_SENTENCE_H

#include "sentencebase.hpp"


namespace nmea::vbw {

enum FieldsEnum{
    LONGITUDINAL_WATER_SPEED = 0,
    TRANSVERSE_WATER_SPEED,
    STATUS_WATER_SPEED,
    LONGITUDINAL_GROUND_SPEED,
    TRANSVERSE_GROUND_SPEED,
    STATUS_GROUND_SPEED,
#ifdef NMEA_ABOVE_3
    STERN_TRANSVERSE_WATER_SPEED,
    STATUS_STERN_TRANSVERSE_WATER_SPEED,
    STERN_TRANSVERSE_GROUND_SPEED,
    STATUS_STERN_TRANSVERSE_GROUND_SPEED,
#endif
    __FieldsEnum__MAX
};

enum Validity {
    VALID = 'A',
    INVALID = 'V',
};

class VBW_Sentence : public SentenceBase
{
public:
    VBW_Sentence(std::string talkerID)
    {
        this->fields = Fields_t(__FieldsEnum__MAX);
        this->talkerID = talkerID;
        this->sentenceID = "VBW";
    }

    void setWaterSpeed(double longitudinal, double transverse, Validity validity = VALID, int precision = 3){
        fields[LONGITUDINAL_WATER_SPEED] = toStringFloat(longitudinal, precision);
        fields[TRANSVERSE_WATER_SPEED] = toStringFloat(transverse, precision);
        fields[STATUS_WATER_SPEED] = validity;
    }

    void setGroundSpeed(double longitudinal, double transverse, Validity validity = VALID, int precision = 3){
        fields[LONGITUDINAL_GROUND_SPEED] = toStringFloat(longitudinal, precision);
        fields[TRANSVERSE_GROUND_SPEED] = toStringFloat(transverse, precision);
        fields[STATUS_GROUND_SPEED] = validity;
    }
};



}



#endif // VBW_SENTENCE_H
