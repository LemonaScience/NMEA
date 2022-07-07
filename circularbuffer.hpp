#ifndef CIRCULARBUFFER_HPP
#define CIRCULARBUFFER_HPP

#include <atomic>

template<typename T, unsigned len> // len would be 0x..ff, all ones
class CircularBuffer{
public:
    CircularBuffer(){
        writePtr = 0;
        readPtr = 0;
        elemCount.store(0);
    }
    T buffer[len];
    unsigned writePtr;
    unsigned readPtr;
    std::atomic<unsigned> elemCount;
    bool add(T val){
        if(elemCount.load() < len){
            buffer[writePtr++] = val;
            writePtr %= len;
            elemCount.fetch_add(1);
            return true;
        } else {
            return false;
        }
    }
    bool remove(T &val){
        if(elemCount.load() > 0){
            val = buffer[readPtr++];
            readPtr %= len;
            elemCount.fetch_sub(1);
            return true;
        } else {
            return false;
        }
    }
};


#endif // CIRCULARBUFFER_HPP
