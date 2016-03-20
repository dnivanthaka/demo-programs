// Three simple random number generators
#include <iostream>
using namespace std;
// three different custom random number generators
int rand1(int lim);
int rand2(int lim);
int rand3(int lim);
int main(void) {
// select the strategy
int strategy = 0;
do {
cout << "Choose your strategy (1, 2, or 3): ";
cin >> strategy;
}while (strategy < 1 && strategy > 3);
// output ten random numbers using the strategy
cout << "Ten random numbers between 1 and 100:" << endl;
    for (int k = 0; k < 10; k++) {
    int randomNumber;
        switch (strategy) {
        case 1: cout << rand1(100); break;
        case 2: cout << rand2(100); break;
        case 3: cout << rand3(100); break;
        }
    }

return 0;
};
// returns random integer from 1 to lim
int rand1(int lim) {
    long a = 100001;
    a = (a * 125) % 2796203;
    return ((a % lim) + 1);
}
// returns random integer from 1 to lim (Gerhard's generator)
int rand2(int lim) {
    long a = 1;
    a = (a * 32719 + 3) % 32749;
    return ((a % lim) + 1);
}
// returns random integer from 1 to lim (Bill's generator)
int rand3(int lim) {
    long a = 3;
    a = (((a * 214013L + 2531011L) >> 16) & 32767);
    return ((a % lim) + 1);
}

