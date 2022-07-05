#ifndef GGA_SENTENCE_H
#define GGA_SENTENCE_H

#include "sentencebase.hpp"

namespace gga {

enum FieldsEnum{
    UTC = 0,
    LATITUDE,
    N_or_S,
    LONGITUDE,
    E_or_W,
    GPS_QUALITY_INDICATOR,
    NUMBER_OF_SATALLITES_IN_USE,
    HORIZONTAL_DILUTION,
    ANTENNA_ALTITUDE,
    UNITS_OF_ANTENNA_ALTITUDE,
    GEOIDAL_SEPARATION,
    UNITS_OF_GEOIDAL_SEPARATION,
    AGE_OF_DIFFERENTIAL_GPS_DATA,
    DIFFERENTIAL_REFERENCE_STATION,
    __FieldsEnum__MAX
};

enum GpsQualityIndicator {
    FIX_NOT_AVAILABLE = 0,
    GPS_FIX,
    DIFFERENTIAL_GPS_FIX,
    PPS_FIX,
    REAL_TIME_KINEMATIC,
    FLOAT_RTK,
    ESTIMATED,
    MANUAL_INPUT_MODE,
    SIMULATION_MODE,
};


class GGA_Sentence : public SentenceBase
{
public:
    GGA_Sentence(std::string talkerID)
    {
        this->fields = Fields_t(__FieldsEnum__MAX);
        this->talkerID = talkerID;
        this->sentenceID = "GGA";
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

    void setGpsQualityIndicator(GpsQualityIndicator gqi){
        fields[GPS_QUALITY_INDICATOR] = toStringInt(gqi, 1);
    }

    void setNumberOfSatellitesInUse(int val){
        fields[NUMBER_OF_SATALLITES_IN_USE] = toStringInt(val, 2);
    }

    void setHorizontalDilution(double val){
        fields[HORIZONTAL_DILUTION] = toStringFloat(val, 2);
    }

    void setAntennaAltitude(double val){
        fields[ANTENNA_ALTITUDE] = toStringFloat(val, 2);
        setUnitsOfAntennaAltitude();
    }

    void setUnitsOfAntennaAltitude(){
        fields[UNITS_OF_ANTENNA_ALTITUDE] = "M";
    }

    void setGeoidalSeparation(double val){
        fields[GEOIDAL_SEPARATION] = toStringFloat(val, 2);
        setUnitsOfGeoidalSeparation();
    }

    void setUnitsOfGeoidalSeparation(){
        fields[UNITS_OF_GEOIDAL_SEPARATION] = "M";
    }

    void setAgeOfDifferentialGpsData(double sec){
        fields[AGE_OF_DIFFERENTIAL_GPS_DATA] = std::to_string(sec);
    }

    void setDifferentialReferenceStation(int val){
        fields[DIFFERENTIAL_REFERENCE_STATION] = toStringInt(val, 4);
    }
};



}



#endif // GGA_SENTENCE_H
