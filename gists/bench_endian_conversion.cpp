// simple swapping without data types
#include <assert.h>

#include <chrono>
#include <cstring>
#include <iostream>
#include <ratio>
#include <vector>
#include "helper.hpp"

#define SIZE_CAN_FLOAT 4

namespace chrono = std::chrono;

inline void reverse4(void* to, const void* from) {
    unsigned int x, xsw;
    memcpy(&x, from, 4);
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)
    xsw = __builtin_bswap32(x);
#else
    xsw = ((x & 0xffu) << 24u) | ((x & 0xff00u) << 8u) | ((x & 0xff0000u) >> 8u) | (x >> 24u);
#endif
    memcpy(to, &xsw, 4);
}

inline size_t toLocal(float& to, const void* from) {
    // #if defined(AIPS_LITTLE_ENDIAN)
    reverse4(((char*)&to) + sizeof(float) - 4, from);
    // #else
    // move4 (&to, from);
    // #endif
    return SIZE_CAN_FLOAT;
}

size_t TOLOCAL(int CONVERT, void* to, const void* from, size_t nr) {
    int SIZE = sizeof(float);

    /* Use memcpy if no conversion is needed. */
    if (CONVERT == 0) {
        assert(sizeof(float) == SIZE);
        memcpy(to, from, nr * SIZE);
    } else {
        const char* data = (const char*)from;
        float* dest      = (float*)to;
        float* last      = dest + nr;
        while (dest < last) {
            toLocal(*dest++, data);
            data += SIZE;
        }
    }
    return nr * SIZE;
}

int main() {
    // #if (defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__))
    // #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    // printf("__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ \n\n");
    // #endif
    // #endif

    // #if defined(__APPLE__)
    // printf("__APPLE__ is defined by default");
    // #endif

    size_t SIZE = 1<<20;
    size_t bytesOperated;
    Timer<std::chrono::microseconds> t;

    std::vector<float> inVec;

    inVec = generateRandomData(SIZE, -50.0f, 50.0f, 245);

    std::vector<float> outVecNormal(SIZE);
    t.start_timer();
    bytesOperated = TOLOCAL(0, outVecNormal.data(), inVec.data(), SIZE);
    t.stop_timer();
    std::cout << "bytesOperated : " << bytesOperated << std::endl;
    std::cout << "Time elapsed normal : " << t.time_elapsed() << std::endl;

    inVec = generateRandomData(SIZE, -50.0f, 50.0f, 245);

    std::vector<float> outVecReversed(SIZE);
    t.start_timer();
    bytesOperated = TOLOCAL(1, outVecReversed.data(), inVec.data(), SIZE);
    t.stop_timer();
    std::cout << "bytesOperated : " << bytesOperated << std::endl;
    std::cout << "Time elapsed reversed : " << t.time_elapsed() << std::endl;
}
