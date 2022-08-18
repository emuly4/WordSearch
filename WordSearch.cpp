//
// Created by Emil Muly on 8/15/2022.
//

#include "WordSearch.h"

wordSearch::wordSearch() {
    string input;
    char tmp[256];
    getcwd(tmp, 256);
    cwd = (string) tmp;
    //Check if user wants to create their own list
    cout << "Would you like to create your own word list? (y/n): " << endl;
    cin >> createFile;
    if(createFile == 'Y' || createFile == 'y'){
        createfile();
    }
    //Get filename and check if filename is valid
    while(!fileValid){
        cout << "Please enter the name of the text file you would like to used to generate your words (Ex. \"example.txt\"): " << endl;
        cin >> filename;
        ifstream wordList;
        wordList.open(cwd+WordListpath+filename);
        string tmp;
        if(wordList.is_open()){
            while(!wordList.eof()){
                getline(wordList, tmp);
                wordVec.push_back(tmp);
                if(tmp.size() > length){length = tmp.size();}
            }
            fileValid = true;
        }else{
            cout << "Error - File not found." << endl;
        }
    }
    cout << "Please enter a name for your word search (Ex. \"Emil's WordSearch\"): " << endl;
    cin.ignore();
    getline(cin, name);
    cout << R"(Please enter a word density level for your word search ("Low", "Medium", "High"): )" << endl;
    cin >> input;
    if(input == "Low"){
        density = 1;
    }else if(input == "Medium"){
        density = 2;
    }else if(input == "High"){
        density = 3;
    }else{
        //Default to Low Density
        density = 1;
    }
    cout << R"(Please enter a complexity level for your word search ("Low", "Medium", "High"): )" << endl;
    cin >> input;
    if(input == "Low"){
        complexity = 1;
    }else if(input == "Medium"){
        complexity = 2;
    }else if(input == "High"){
        complexity = 3;
    }else{
        //Default to Low Complexity
        complexity = 1;
    }
}

void wordSearch::createSearch() {
    int r;
    initializeGrid();
    srand(time(0)); // Randomizes Seed
    switch (complexity) {
        case 1:
            //Easy: Horizontal, Vertical Words Only
            for(int i {0}; i < wordVec.size(); i++){
                currentWord = wordVec[i];
                //Randomize the Choice
                r = rand() % 2;
                if(r == 0){
                    if(checkHorizontial()){
                        horizontial();
                    }else{
                        wordVec.erase(wordVec.begin()+i);
                    }
                }else{
                    if(checkVertical()){
                        vertical();
                    }else{
                        wordVec.erase(wordVec.begin()+i);
                    }
                }
            }
            break;
        case 2:
            //Medium: Horizontal Vertical, and Diagonal Words (only Horizontal and Vertical can be written backwards)
            for(int i {0}; i < wordVec.size(); i++){
                currentWord = wordVec[i];
                //Randomize the Choice
                r = rand() % 3;
                if(r == 0){
                    if(checkHorizontial()){
                        if(rand() % 2 == 0){
                            horizontial();
                        }else{
                            backwards();
                            horizontial();
                        }
                    }else{
                        wordVec.erase(wordVec.begin()+i);
                    }
                }else if(r == 1){
                    if(checkVertical()){
                        if(rand() % 2 == 0){
                            vertical();
                        }else{
                            backwards();
                            vertical();
                        }
                    }else{
                        wordVec.erase(wordVec.begin()+i);
                    }
                }else{
                    if(checkDiagonal()){
                        diagonal();
                    }else{
                        wordVec.erase(wordVec.begin()+i);
                    }
                }
            }
            break;
        case 3:
            //Hard: Horizontal, Vertical, Diagonal Words all could be written backwards
            for(int i {0}; i < wordVec.size(); i++){
                currentWord = wordVec[i];
                //Randomize the Choice
                r = rand() % 3;
                if(r == 0){
                    if(checkHorizontial()){
                        if(rand() % 2 == 0){
                            horizontial();
                        }else{
                            backwards();
                            horizontial();
                        }
                    }else{
                        wordVec.erase(wordVec.begin()+i);
                    }
                }else if(r == 1){
                    if(checkVertical()){
                        if(rand() % 2 == 0){
                            vertical();
                        }else{
                            backwards();
                            vertical();
                        }
                    }else{
                        wordVec.erase(wordVec.begin()+i);
                    }
                }else{
                    if(checkDiagonal()){
                        if(rand() % 2 == 0){
                            diagonal();
                        }else{
                            backwards();
                            diagonal();
                        }
                    }else{
                        wordVec.erase(wordVec.begin()+i);
                    }
                }
            }
            break;
    }
    createOutput();
}

void wordSearch::initializeGrid() {
    //Define RC using generation density
    if(density == 1){
        RC = 30;
    }else if(density == 2){
        RC = 20;
    }else if(density == 3){
        RC = 15;
    }
    srand(time(0)); // Randomizes Seed
    for(int i {0}; i < RC; i++){
        for(int j {0}; j < RC; j++){
            grid[i][j] = char(rand() % 26 + 65);
            gridFilled[{i, j}] = true;
        }
    }
}

void wordSearch::createOutput() {
    //Open Template
    ifstream searchTemp;
    searchTemp.open(cwd+WordSearchpath+"template.htm");
    //Initailize New HTM File
    ofstream wordSearch;
    int n = filename.length();
    char char_array[n + 1];
    strcpy(char_array, filename.c_str());
    string htmfile = strtok(char_array, ".");
    htmfile+=".htm";
    wordSearch.open(cwd+WordSearchpath+htmfile);
    string str;
    while(!searchTemp.eof()){
        //All Lines in Template
        getline(searchTemp, str);
        if(str == "<h1>WordSearch Title</h1>"){
            //Title Comes Up -> insert Name
            wordSearch << "<h1>" << name << "</h1>" << endl;
        }else if(str == R"(<table style="width:20%", class="center">)"){//Array Comes Up -> insert table/array
            wordSearch << R"(<table style="width:20%", class="center">)" << endl;
            string addRowValue;
            for(int i {0}; i < RC; i++){
                wordSearch << "    <tr>" << endl;
                for(int j {0}; j < RC; j++){
                    addRowValue = "        <td style=\"text-align:center\">";
                    addRowValue += grid[i][j]; //Value to Add
                    addRowValue += "</td>";
                    wordSearch << addRowValue << endl;
                }
                wordSearch << "    </tr>" << endl;
            }
        }else if(str == "<h3>Word List</h3>"){
            //Word List Comes up -> insert word list
            wordSearch << "<h3>Word List</h3>" << endl;
            int size = wordVec.size() / 3;
            string addColValue;
            wordSearch << "    <div class=\"column\">" << endl;
            for(int i {0}; i < size; i++){
                addColValue = "        <p>";
                addColValue += string(wordVec[i]);
                addColValue += "</p>";
                wordSearch << addColValue << endl;
            }
            wordSearch << "    </div>" << endl;
            wordSearch << "    <div class=\"column\">" << endl;
            for(int i {size}; i < (size*2); i++){
                addColValue = "        <p>";
                addColValue += string(wordVec[i]);
                addColValue += "</p>";
                wordSearch << addColValue << endl;
            }
            wordSearch << "    </div>" << endl;
            wordSearch << "    <div class=\"column\">" << endl;
            for(int i {size*2}; i < wordVec.size(); i++){
                addColValue = "        <p>";
                addColValue += string(wordVec[i]);
                addColValue += "</p>";
                wordSearch << addColValue << endl;
            }
            wordSearch << "    </div>" << endl;
        }else{
            //Add template lines to new file
            wordSearch << str << endl;
        }
    }
    searchTemp.close();
    wordSearch.close();
}

void wordSearch::createfile() {
    string word;
    while(!fileValid){
        cout << "Please enter a name for your word list (Ex. \"MyWordList.txt\"): " << endl;
        cin >> filename;
        if(filename.substr(filename.find_last_of(".") + 1) == "txt"){
            fileValid = true;
        }else{
            cout << "Error - File not found." << endl;
        }
    }
    ofstream wordList;

    wordList.open(cwd + WordListpath + filename);
    while(1){
        cout << "Please enter a word to add to the list, if you are done adding words please enter \"Done\": " << endl;
        cin >> word;
        if(word == "Done"){
            break;
        }else{
            wordList << word << endl;
            wordVec.push_back(word);
            if(word.size() > length){length = word.size();}
        }
    }
    wordList.close();
}

bool wordSearch::checkHorizontial() {
    bool viability = true;
    int count = 1;
    currPosX = 0;
    currPosY = 0;
    while(count <= (RC*(RC-currentWord.size()))){
        for(int i {0}; i < currentWord.size(); i++){
            viability = gridFilled[{currPosX+i, currPosY}];
            if(!viability){
                break;
            }
        }
        if(viability){
            break;
        }else{
            if(currPosY == RC-1){
                currPosY = 0;
                currPosX++;
            }else{
                currPosY++;
            }
            count++;
        }
    }
    return viability;
}

void wordSearch::horizontial() {
    int size = currentWord.size();
    //Make Sure Characters are UpperCase
    makeUpper();
    for(int i {0}; i < size; i++){
        grid[currPosX][currPosY] = currentWord[i];
        gridFilled[{currPosX,currPosY}] = false;
        currPosX++;
    }


}

void wordSearch::vertical() {
    int size = currentWord.size();
    //Make Sure Characters are UpperCase
    makeUpper();
    for(int i {0}; i < size; i++){
        grid[currPosX][currPosY] = currentWord[i];
        gridFilled[{currPosX,currPosY}] = false;
        currPosY++;
    }

}

bool wordSearch::checkVertical() {
    bool viability = true;
    int count = 1;
    currPosX = 0;
    currPosY = 0;
    while(count <= (RC*(RC-currentWord.size()))){
        for(int i {0}; i < currentWord.size(); i++){
            viability = gridFilled[{currPosX, currPosY+i}];
            if(!viability){
                break;
            }
        }
        if(viability){
            break;
        }else{
            if(currPosX == RC-1){
                currPosX = 0;
                currPosY++;
            }else{
                currPosX++;
            }
            count++;
        }
    }
    return viability;
}

void wordSearch::diagonal() {
    int size = currentWord.size();
    //Make Sure Characters are UpperCase
    makeUpper();
    for(int i {0}; i < size; i++){
        grid[currPosX][currPosY] = currentWord[i];
        gridFilled[{currPosX,currPosY}] = false;
        currPosX++;
        currPosY++;
    }

}

bool wordSearch::checkDiagonal() {
    bool viability = true;
    int count = 1;
    currPosX = 0;
    currPosY = 0;
    while(count <= (RC*(RC-currentWord.size()))){
        for(int i {0}; i < currentWord.size(); i++){
            viability = gridFilled[{currPosX+i, currPosY+i}];
            if(!viability){
                break;
            }
        }
        if(viability){
            break;
        }else{
            if(currPosX == RC-1){
                currPosX = 0;
                currPosY++;
            }else{
                currPosX++;
            }
            count++;
        }
    }
    return viability;
}

void wordSearch::backwards() {
    stack<char> str;
    for(int i {0}; i < currentWord.size(); i++){
        str.push(currentWord[i]);
    }
    string tmp;
    while(!str.empty()){
        tmp.push_back(str.top());
        str.pop();
    }
    currentWord = tmp;
}

void wordSearch::makeUpper() {
    //Make Sure Characters are UpperCase
    for(int i {0}; i<currentWord.size(); i++){
        if(!isupper(currentWord[i])){
            currentWord[i] = toupper(currentWord[i]);
        }
    }
}