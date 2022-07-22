#ifndef INS_SENTENCE_H
#define INS_SENTENCE_H

#include "sentencebase.hpp"
#include "attitudeMessage.hpp"
#include "b_c_Message.hpp"
#include "gga_sentence.hpp"
#include <iostream>

namespace nmea{

namespace ins {
    
enum FieldsEnum {
	MESSAGE_IDENTIFIER = 0,
    UTC,
    ROLL_ANGLE,
	PITCH_ANGLE,
	HEADING,
    VELOCITY_NORTH,
	VELOCITY_EAST,
    VALIDITIES,
    __FieldsEnum__MAX
};

enum E_VALIDITIES {
	vROLL = 1,
	vPITCH = 1 << 1,
	vHEADING = 1 << 2,
	vVELOCITY = 1 << 3,
};


class INS_Sentence : public SentenceBase
{
public:
    INS_Sentence(std::string talkerID, nmea::gga::GGA_Sentence *gga, NS_PL41::Attitude::AttitudeModel *atm, NS_PL41::B_C_Message::BMessageModel *bmm)
    {
        this->fields = Fields_t(__FieldsEnum__MAX);
        this->talkerID = talkerID;
        this->sentenceID = "INS";

        uint16_t validities = 0;

        fields[MESSAGE_IDENTIFIER] = "001";

        if(gga){
        	auto time = gga->getTime();
        	fields[UTC] = timeToString(time.hour, time.minute, time.second);
        } else {
        	fields[UTC] = timeToString(0, 0, 0);
        }

        if(atm){
        	auto roll = atm->getOwnShipsRoll();
        	roll = limitter(roll, 100); //TODO
        	fields[ROLL_ANGLE] = toStringFloatSigned(roll, 2, 5);

        	validities |= vROLL;

        	auto pitch = atm->getOwnShipsPitch();
        	pitch = limitter(pitch, 100); //TODO
        	fields[PITCH_ANGLE] = toStringFloatSigned(pitch, 2, 5);

        	validities |= vPITCH;

        	auto heading = atm->getOwnShipsHeading();
        	fields[HEADING] = toStringFloat(heading, 3, 5);

        	validities |= vHEADING;


        } else {
        	fields[ROLL_ANGLE] = toStringFloatSigned(0, 2, 5);

        	fields[PITCH_ANGLE] = toStringFloatSigned(0, 2, 5);

        	fields[HEADING] = toStringFloat(0, 3, 5);
        }


        if(bmm){
        	auto nv = bmm->getNorthVelocity();
        	nv = limitter(nv, 100); //TODO
        	fields[VELOCITY_NORTH] = toStringFloatSigned(nv, 2, 5);

        	auto ev = bmm->getEastVelocity();
        	ev = limitter(ev, 100); //TODO
        	fields[VELOCITY_EAST] = toStringFloatSigned(ev, 2, 5);

        	validities |= vVELOCITY;
        } else {
        	fields[VELOCITY_NORTH] = toStringFloatSigned(0, 2, 5);

        	fields[VELOCITY_EAST] = toStringFloatSigned(0, 2, 5);
        }


        fields[VALIDITIES] = uInt2Hex(validities, 4);
    }
private:
    std::string timeToString(int hour, int minute, double second);
    std::string uInt2Hex(unsigned val, int width);

    double limitter(double val, double lim){
    	int sign = 1;
    	if(val < 0){
    		sign = -1;
    		val = -val;
    	}

    	if(val > lim){
    		val = lim - 0.001;
    	}
    	return val * sign;
    }
};



}

}


#endif // INS_SENTENCE_H
