#include <iostream>
#include <string>

#include "WordSearch.h"
#include <unistd.h>
//Global Variable Definition
char ans = 'n';

using namespace std;
int main() {
    //WordSearch Initialization
    cout << "Hello there, lets create your own word search!" << endl;

    while(true){
        //Create a Word Search (initailizes the creation of a wordsearch object)
        wordSearch mySearch;
        mySearch.createSearch();

        //Prompt for creating another word search
        cout << "You're all set, would you like to create another wordsearch? (y/n): " << endl;
        cin >> ans;
        if(ans == 'y' || ans == 'Y'){
            cout << "Ok! Let's make another one." << endl;
        }else{
            break;
        }
    }
    return 0;
}
