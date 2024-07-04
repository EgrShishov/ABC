#include <iostream>
using namespace std;
// F[i]=A[i] * (B[i] + C[i]) - D[i] , i = 1...8.
int main()
{
    __int8 A[8] = {127,-128,127,-128,127,-128,127,-128};
    __int8 B[8] = {127,127,-128,-128,127,127,-128,-128};
    __int8 C[8] = {127,127,127,127,-128,-128,-128,-128};
    __int16 D[8] = {32767,32767,32767,32767,-32768,-32768,-32768,-32768};
    __int32 F[8]{};

 /*   std::cout << "Enter array of A!\n";
    for (int i = 0; i < 8; i++) {
        int tmp;
        cin >> tmp;
        A[i] = tmp;
    }

    std::cout << "Enter array of B!\n";
    for (int i = 0; i < 8; i++) {
        int tmp;
        cin >> tmp;
        B[i] = tmp;
    }

    std::cout << "Enter array of C!\n";
    for (int i = 0; i < 8; i++) {
        int tmp;
        cin >> tmp;
        C[i] = tmp;
    }

    std::cout << "Enter array of D!\n";
    for (int i = 0; i < 8; i++) {
        int tmp;
        cin >> tmp;
        D[i] = tmp;
    }*/

    __asm {
        ; B + C
        lea eax, B
        lea ebx, C

        movq mm0, [eax]
        movq mm1, [ebx]

        movq mm2, mm0
        movq mm3, mm1

        pxor mm4, mm4
        pxor mm5, mm5

        pcmpgtb mm4, mm2
        pcmpgtb mm5, mm3

        ; to 16 - bit
        ; low
        punpcklbw mm0, mm4
        ; high
        punpckhbw mm2, mm4
        ; low
        punpcklbw mm1, mm5
        ; high
        punpckhbw mm3, mm5


        paddw mm0, mm1
        paddw mm2, mm3
        ; result in mm0, mm2

        ; A* (B + C)
        pxor mm1, mm1
        pxor mm3, mm3
        pxor mm4, mm4
        pxor mm5, mm5
        pxor mm6, mm6

        movq mm1, mm0
        movq mm3, mm2

        ; converting to 32bit
        punpcklwd mm0, mm4; low low from result
        punpckhwd mm1, mm4; low high
        punpcklwd mm2, mm4; high low
        punpckhwd mm3, mm4; high high


        lea eax, A
        movq mm4, [eax]
        ; extending A(low)
        pcmpgtb mm6, mm4

        punpcklbw mm4, mm6
        movq mm5, mm4
        pxor mm6, mm6
        punpcklwd mm4, mm6
        punpckhwd mm5, mm6

        pmaddwd mm0, mm4
        pmaddwd mm1, mm5

        movq mm4, [eax]

        ; high
        pcmpgtb mm6, mm4

        punpckhbw mm4, mm6
        movq mm5, mm4
        pxor mm6, mm6
        punpcklwd mm4, mm6
        punpckhwd mm5, mm6

        pmaddwd mm2, mm4
        pmaddwd mm3, mm5

        ; result after multiplying stores in 0, 1, 2, 3


        ; A* (B + C) - D
        ; free registers
        pxor mm4, mm4
        pxor mm5, mm5
        pxor mm6, mm6
        pxor mm7, mm7

        lea edx, D
        movq mm4, [edx]
        movq mm5, mm4

        ; unpacking to 32bit
        pcmpgtw mm7, mm4
        punpcklwd mm4, mm7
        punpckhwd mm5, mm7

        psubd mm0, mm4
        psubd mm1, mm5

        pxor mm4, mm4
        pxor mm5, mm5

        ;second part
        movq mm6, [edx + 8]
        movq mm7, mm6
        pcmpgtw mm4, mm6
        punpcklwd mm6, mm4
        punpckhwd mm7, mm4

        psubd mm2, mm6
        psubd mm3, mm7

        ; result to F
        lea eax, F
        movq [eax], mm0
        movq [eax + 8], mm1
        movq [eax + 16], mm2
        movq [eax + 24], mm3
    }

    cout << "F: ";
    for (int i = 0; i < 8; i++) {
        cout << std::dec << F[i] << " ";
    }
    std::cout << "\n\n";
    for (int i = 0; i < 8; i++) {
        cout << std::dec << A[i]*(B[i]+C[i])-D[i] << " ";
    }

    return 0;
}
