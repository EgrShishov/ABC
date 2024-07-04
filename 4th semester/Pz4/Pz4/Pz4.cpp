#include <iostream>

using namespace std;
// F[i]=A[i] * (B[i] + C[i]) - D[i] , i = 1...8.
int main()
{
    float A[] = { 2323.676788778, 4., 6., 8., 43., 213.534, 0.2342, 543.53454};
    float B[] = { 1., 2., 3., 4., 9.54, 20032.3544, 32.34, 121233.34};
    float C[] = { 10., 12., 14., 16., 0.98584, 1.00003443, 9723.34, 15.435};
    double D[] = { 127.342, 432.432, 100.001, 54.3534, 43.5435346, 10000.4, 13.54, 1234.5453};
    double F[8]{};

    /*   std::cout << "Enter array of A!\n";
       for (int i = 0; i < 8; i++) {
           float tmp;
           cin >> tmp;
           A[i] = tmp;
       }

       std::cout << "Enter array of B!\n";
       for (int i = 0; i < 8; i++) {
           float tmp;
           cin >> tmp;
           B[i] = tmp;
       }

       std::cout << "Enter array of C!\n";
       for (int i = 0; i < 8; i++) {
           float tmp;
           cin >> tmp;
           C[i] = tmp;
       }

       std::cout << "Enter array of D!\n";
       for (int i = 0; i < 8; i++) {
           double tmp;
           cin >> tmp;
           D[i] = tmp;
       }*/

    __asm {
        lea eax, A
        lea ebx, B
        lea ecx, C
        lea edx, D

        ; B + C
        cvtps2pd xmm0, [ebx]
        cvtps2pd xmm1, [ebx + 8]
        cvtps2pd xmm2, [ebx + 16]
        cvtps2pd xmm3, [ebx + 24]

        cvtps2pd xmm4, [ecx]
        cvtps2pd xmm5, [ecx + 8]
        cvtps2pd xmm6, [ecx + 16]
        cvtps2pd xmm7, [ecx + 24]

        xor ebx, ebx
        xor ecx, ecx

        addpd xmm0, xmm4
        addpd xmm1, xmm5
        addpd xmm2, xmm6
        addpd xmm3, xmm7
        ; result in xmm0, xmm1, xmm2, xmm3

        xorpd xmm4, xmm4
        xorpd xmm5, xmm5
        xorpd xmm6, xmm6
        xorpd xmm7, xmm7

        cvtps2pd xmm4, [eax]
        cvtps2pd xmm5, [eax + 8]
        cvtps2pd xmm6, [eax + 16]
        cvtps2pd xmm7, [eax + 24]

        ; A* (B + C)
        mulpd xmm0, xmm4
        mulpd xmm1, xmm5
        mulpd xmm2, xmm6
        mulpd xmm3, xmm7
        ; result in xmm0, xmm1, xmm2, xmm3

        xorpd xmm4, xmm4
        xorpd xmm5, xmm5
        xorpd xmm6, xmm6
        xorpd xmm7, xmm7

        movupd xmm4, [edx]
        movupd xmm5, [edx + 16]
        movupd xmm6, [edx + 32]
        movupd xmm7, [edx + 48]

        ; A* (B + C) - D
        subpd xmm0, xmm4
        subpd xmm1, xmm5
        subpd xmm2, xmm6
        subpd xmm3, xmm7

        ; result in xmm0, xmm1, xmm2, xmm3
        lea ebx, F

        movupd[ebx], xmm0
        movupd[ebx + 16], xmm1
        movupd[ebx + 32], xmm2
        movupd[ebx + 48], xmm3
    };

    cout << "F: ";
    for (int i = 0; i < 8; i++) {
        cout << std::dec << F[i] << " ";
    }
    std::cout << "\n";
    std::cout << "Right answer: ";
    for (int i = 0; i < 8; i++) {
        cout << std::dec << A[i] * (B[i] + C[i]) - D[i] << " ";
    }

    return 0;
}