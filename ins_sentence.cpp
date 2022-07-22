#include "ins_sentence.hpp"


#undef str
#include <sstream>
#include <iomanip>

std::string nmea::ins::INS_Sentence::timeToString(int hour, int minute, double second){
	char tmp[50];
	sprintf(tmp, "%02d%02d%06.3lf", hour, minute, second);
	std::stringstream ss;
	ss << tmp;
	return ss.str();
}

std::string nmea::ins::INS_Sentence::uInt2Hex(unsigned val, int width){
	std::stringstream ss;
	ss << std::uppercase <<std::hex << std::setw(width) << std::setfill('0') << val;
	return ss.str();
}
