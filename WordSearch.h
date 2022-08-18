//
// Created by Emil Muly on 8/15/2022.
//

#ifndef WORDSEARCH_WORDSEARCH_H
#define WORDSEARCH_WORDSEARCH_H
#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <unistd.h>
#include <time.h>
#include <vector>
#include <map>
//#include <set>

using namespace std;
class wordSearch {
public:
    //Variables
    bool fileValid = false;
    char createFile = 'n';
    vector<string> wordVec;
    string cwd;
    string WordListpath = "\\LibraryFiles\\";
    string WordSearchpath = "\\WordSearch Outputs\\";
    //Functions
    wordSearch();
    void createfile();
    void createSearch();
    void initializeGrid();
    void createOutput();
    void horizontial();
    bool checkHorizontial();
    void vertical();
    bool checkVertical();
    void diagonal();
    bool checkDiagonal();
    void makeUpper();
    void backwards();

private:
    //Variables
    int length = 0;
    int complexity;
    int density;
    string name;
    string filename;
    string currentWord;
    int RC;
    char grid[30][30];
    int currPosX = 0;
    int currPosY = 0;
    map<pair<int, int>, bool> gridFilled;


};
#endif //WORDSEARCH_WORDSEARCH_H
