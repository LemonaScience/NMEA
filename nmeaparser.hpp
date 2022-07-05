#ifndef NMEAPARSER_HPP
#define NMEAPARSER_HPP

#include <queue>

#define START_DELIMITER '$'

#define TO_STR(x) #x

namespace nmea {

enum ParserState{
    STATE_StartDelimiter,
    STATE_Fields,
    STATE_Checksum_0,
    STATE_Checksum_1,
    STATE_Terminator_CR,
    STATE_Terminator_LF,
};

template<class C>
class NmeaParser
{
public:

    typedef void (C::*Callback) (std::queue<char>);

    Callback callback;
    C *owner;
    std::queue<char> waitQueue;
    std::queue<char> currentBuffer;
    ParserState currentState = STATE_StartDelimiter;
    char currentChecksum = 0;
    char expectedCheksum = 0;

    int getNum(char ch)
    {
        int num = 0;
        if (ch >= '0' && ch <= '9') {
            num = ch - 0x30;
        }
        else {
            switch (ch) {
            case 'A':
            case 'a':
                num = 10;
                break;
            case 'B':
            case 'b':
                num = 11;
                break;
            case 'C':
            case 'c':
                num = 12;
                break;
            case 'D':
            case 'd':
                num = 13;
                break;
            case 'E':
            case 'e':
                num = 14;
                break;
            case 'F':
            case 'f':
                num = 15;
                break;
            default:
                num = 0;
            }
        }
        return num;
    }

    NmeaParser(C* o, Callback c) :
        owner(o),
        callback(c)
    {

    }

    void parse(char c)
    {
        waitQueue.push(c);

        if(c == START_DELIMITER){
            currentState = STATE_StartDelimiter;
        }


        switch (currentState) {
        case STATE_StartDelimiter:
        {
            if(c == START_DELIMITER){
                currentBuffer = std::queue<char>();
                currentBuffer.push(c);
                currentChecksum = 0;
                currentState = STATE_Fields;
            } else {
                //fail
                return;
            }
        }
            break;
        case nmea::STATE_Fields:
        {
            if(!isprint(c)) {
                //fail
                return;
            } else {
                if(c == '*'){
                    currentBuffer.push(c);
                    currentState = STATE_Checksum_0;
                    return;
                } else {
                    putDataChar2Buffer(c);
                    return;
                }
            }
        }
            break;
        case nmea::STATE_Checksum_0:
        {
            if(!isxdigit(c)) {
                //fail
                return;
            } else {
                currentBuffer.push(c);
                currentState = STATE_Checksum_1;
                expectedCheksum = getNum(c);
                return;
            }
        }
            break;
        case nmea::STATE_Checksum_1:
        {
            if(!isxdigit(c)) {
                //fail
                return;
            } else {
                currentBuffer.push(c);
                expectedCheksum <<= 4;
                expectedCheksum |= getNum(c);

                if( expectedCheksum ^ currentChecksum){
                    //fail
                    return;
                } else {
                    currentState = STATE_Terminator_CR;
                    return;
                }

                return;
            }
        }
            break;
        case nmea::STATE_Terminator_CR:
        {
            if(c == '\r'){
                currentBuffer.push(c);
                currentState = STATE_Terminator_LF;
            } else {
                //fail
                return;
            }
        }
            break;
        case nmea::STATE_Terminator_LF:
        {
            if(c == '\n'){
                currentBuffer.push(c);
                currentState = STATE_StartDelimiter;

                foundValidNmea();



            } else {
                //fail
                return;
            }
        }
            break;
        default:
            break;
        }
    }

    void putDataChar2Buffer(char c)
    {
        currentBuffer.push(c);
        currentChecksum ^= c;
    }

    void foundValidNmea()
    {
        (owner->*callback)(currentBuffer);
    }
};

}



#endif // NMEAPARSER_HPP
