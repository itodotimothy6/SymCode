#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Function declaration
string convertTextToBits(string);
vector<int> convertBitsToIndex(string, int);
string convertIndexToSymcode(vector<int>);
string convertToSymcode(string);
void trim(string& s);


// Main function
int main(int argc, const char * argv[]) {
    
    string line;
    ifstream in;
    ofstream out;
    
    in.open("symcode-in.txt"); // File to read from
    out.open("symcode-out.txt"); // File to write into
    while (!in.eof()) {
        getline(in, line); // Get string in a line in the input file
        trim(line); // Remove preceding white spaces
        out << convertToSymcode(line) << endl; // Convert to Symcode and write into 1 file
    }
    // Close files
    in.close();
    out.close();
    
    return 0;
}

string convertTextToBits(string text){
    // This function converts each character in a text to 8-bit binary and concatenates them
    /* For output strings with size that are not divisible by 3, the functions
     pads it by adding "00000000" until the size of the ouptut is 3*/
    
    string bits = "";
    for(int i = 0; i < text.size(); i++ ){
        bits += bitset<8>(text[i]).to_string();
    }
    //padding
    while(bits.size() % 3){
        bits += "00000000";
    }
    return bits;
}

vector<int> convertBitsToIndex(string bits, int textLength){
    // This function converts each group of 3 bits to an integer and stores it in a vector
    // For the last 0s, the function pushes 8 to the vector
    vector <int> indexList;
    int i = 0;
    while (i < textLength * 8){
        int a = (bits[i]-'0') * 4 + (bits[i+1]-'0') * 2 + (bits[i+2]-'0') * 1;
        indexList.push_back(a);
        i = i+3;
    }
    while (i < bits.size()){
        indexList.push_back(8);
        i = i+3;
    }
    return indexList;
}

string convertIndexToSymcode(vector<int> indexList){
    // This function replaces the index in indexList with its corresponding value in the string "symantec$"
    string s = "symantec$";
    string symcode = "";
    
    for(int i = 0; i < indexList.size(); i++){
        symcode += s[indexList[i]];
    }
    return symcode;
}

string convertToSymcode(string input){
    // This function converts a string to its symcode string
    string bits = convertTextToBits(input);
    vector<int> index = convertBitsToIndex(bits, input.length());
    return convertIndexToSymcode(index);
}

void trim(string& s){
    // This function removes preceding whitespaces
    size_t a = s.find_first_not_of(" \t");
    s.erase(0, a);
}
