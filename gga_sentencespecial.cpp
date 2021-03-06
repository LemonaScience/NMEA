#include "gga_sentencespecial.hpp"

#undef str
#include <sstream>
#include <iostream>
#include <iomanip>

namespace nmea{

namespace ggaifu {
    
	std::string GGA_Sentence::timeTo_hhmmss(int hour, int minute, double second){
	    char tmp[50];
	    sprintf(tmp, "%02d%02d%04.1lf", hour, minute, second);
	    //eger dokumna dogru ise
	    //sprintf(tmp, "%02d%02d%05.2lf", hour, minute, second);
	    std::stringstream ss;
	    ss << tmp;
	    return ss.str();
	}

	std::pair<std::string, char> GGA_Sentence::latDegreeTo_ddmm(double degree){
	    int dd = degree;
	    degree -= dd;
	    char res = NORTH;
	    if((dd+degree) < 0){
	        dd = -dd;
	        degree = -degree;
	        res = SOUTH;
	    }
	    double minute = degree * 60;
	    char tmp[50];
	    sprintf(tmp, "%02d%05.2lf", dd, minute);
	    std::stringstream ss;
	    ss << tmp;
	    return std::make_pair(ss.str(), res);
	}


	std::pair<std::string, char> GGA_Sentence::longDegreeTo_ddmm(double degree){
	    int dd = degree;
	    degree -= dd;
	    char res = EAST;
	    if((dd+degree) < 0){
	        dd = -dd;
	        degree = -degree;
	        res = WEST;
	    }
	    double minute = degree * 60;
	    char tmp[50];
	    sprintf(tmp, "%03d%05.2lf", dd, minute);
	    std::stringstream ss;
	    ss << tmp;
	    return std::make_pair(ss.str(), res);
	}

}

}

