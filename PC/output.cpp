#include <iostream>
#include <string>
using namespace std;
 int main () {
    int answer = rand() % 100 + 0;

    int I = 0;
    while(I<5){
        cout << "Guess a number 0 to 100" << endl;
        int guess;
        cin >> guess;

        if (guess==answer){
            cout << "you guessed it" << endl;
            cout << answer;
            break;
        }


        if (guess>answer){
            cout << "the number is lower" << endl;
        }


        if (guess<answer){
            cout << "the number is higher" << endl;
        }

        I++;
    }

    return 0;
}
