#include <iostream>

int main(int argc, char const *argv[])
{
    #ifdef __amd64__
        std::cout << "__amd64__ detected" << std::endl;
    #endif
    #ifdef __x86_64__
        std::cout << "__x86_64__ detected" << std::endl;
    #endif
    #ifdef __arm__
        std::cout << "__arm__ detected" << std::endl;
        // #ifdef __ARM_ARCH_'V'__
        // std::cout << "   Arm version is: " << __ARM_ARCH_'V'__ << std::endl;
        // #endif
    #endif
    #ifdef __aarch64__
        std::cout << "__aarch64__ detected" << std::endl;
    #endif
    #ifdef __SSE__
        std::cout << "__SSE__ detected" << std::endl;
    #endif
    #ifdef __SSE2__
        std::cout << "__SSE2__ detected" << std::endl;
    #endif
    #ifdef __SSE3__
        std::cout << "__SSE3__ detected" << std::endl;
    #endif
    #ifdef __AVX2__
        std::cout << "__AVX2__ detected" << std::endl;
    #endif
    #ifdef __AVX2__
        std::cout << "__AVX2__ detected" << std::endl;
    #endif
    #ifdef __ARM_NEON__
        std::cout << "__ARM_NEON__ detected" << std::endl;
    #endif
    #ifdef __SSE2__
        std::cout << "__SSE2__ detected" << std::endl;
    #endif

    return 0;
}
