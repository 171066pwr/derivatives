#include<stdlib.h>
#include<stdio.h>
#include<iostream>

using namespace std;

bool swapIfLesser(long &a, long &b) {
    if(a>b) {
        long c = b;
        b = a;
        a = c;
        return true;
    }
    return false;
}

int main () {
    long a, b, c, d;
    cin >> a >> b >> c >> d;
    bool swapped;
    do {
        swapped = false;
        swapped = swapIfLesser(a, b) ? true : swapped;
        swapped = swapIfLesser(b, c) ? true : swapped;
        swapped = swapIfLesser(c, d) ? true : swapped;
    } while (swapped);

    printf("Środkowe wartości: %ld, %ld", b, c);

    return 0;
}