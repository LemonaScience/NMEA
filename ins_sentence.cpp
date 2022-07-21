#include "ins_sentence.hpp"


#undef str
#include <sstream>

std::string nmea::ins::INS_Sentence::timeToString(int hour, int minute, double second){
	char tmp[50];
	sprintf(tmp, "%02d%02d%06.3lf", hour, minute, second);
	std::stringstream ss;
	ss << tmp;
	return ss.str();
}
