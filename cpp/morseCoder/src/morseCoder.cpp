#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <map>
#include <conio.h>
#include <regex>
////////////////////////////////////////////////////////////////////////////////
using std::cin;
using std::cout;
using std::endl;
using std::string;
////////////////////////////////////////////////////////////////////////////////
#define UPPER 0xDF
const char DOT = '0';
const char DASH = '1';
const char UNKNOWN = '?';
const int MGM_LENGTH = 36;
const char *MGM_LIST = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const char* FILE_NAME = "morse_index.txt";
const std::regex MORSE_PATTERN(string("[0-1+]|[ ]"));
////////////////////////////////////////////////////////////////////////////////
struct MorseTree
{
    char value = UNKNOWN;
    MorseTree *left = nullptr;
    MorseTree *right = nullptr;
};
////////////////////////////////////////////////////////////////////////////////
void editNode(MorseTree *root, string MorseCode, char MorseValue)
{
    MorseTree *p = root;
    for (auto i = MorseCode.begin(); i != MorseCode.end(); ++i)
    {
        if (*i == DOT)
        {
            if (p->left == nullptr)
                p->left = new MorseTree;
            p = p->left;
        }
        if (*i == DASH)
        {
            if (p->right == nullptr)
                p->right = new MorseTree;
            p = p->right;
        }
    }
    p->value = MorseValue;
}
char searchMorse(MorseTree *root, string MorseCode)
{
    MorseTree *p = root;
    for (auto i = MorseCode.begin(); i != MorseCode.end(); ++i)
    {
        if (p == nullptr)
            return UNKNOWN;
        if (*i == DOT)
            p = p->left;
        if (*i == DASH)
            p = p->right;
    }
    return p->value;
}
////////////////////////////////////////////////////////////////////////////////
std::map<char, string> MGM_ENCODE = {
    {'A', "01"},
    {'B', "1000"},
    {'C', "1010"},
    {'D', "100"},
    {'E', "0"},
    {'F', "0010"},
    {'G', "110"},
    {'H', "0000"},
    {'I', "00"},
    {'J', "0111"},
    {'K', "101"},
    {'L', "0100"},
    {'M', "11"},
    {'N', "10"},
    {'O', "111"},
    {'P', "0110"},
    {'Q', "1101"},
    {'R', "010"},
    {'S', "000"},
    {'T', "1"},
    {'U', "001"},
    {'V', "0001"},
    {'W', "011"},
    {'X', "1001"},
    {'Y', "1011"},
    {'Z', "1100"},
    {'0', "11111"},
    {'1', "01111"},
    {'2', "00111"},
    {'3', "00011"},
    {'4', "00001"},
    {'5', "00000"},
    {'6', "10000"},
    {'7', "11000"},
    {'8', "11100"},
    {'9', "11110"}};

MorseTree *root = new MorseTree;
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    char directory[128] = {0};
    int i;
    for (i = strlen(argv[0]) - 1; i >= 0; --i)
        if (argv[0][i] == '\\')
            break;
    strncpy(directory, argv[0], i + 1);
    strncat(directory,FILE_NAME,15);

    for (int i = 0; i < MGM_LENGTH; ++i)
        editNode(root, MGM_ENCODE[MGM_LIST[i]], MGM_LIST[i]);
    std::ifstream index_file;
    index_file.open(directory, std::ifstream::in);
    if (index_file) // Open file succeed
    {
        int length = 0;
        char value;
        string morse_code;
        index_file >> length;
        for (int i = 0; i < length; ++i)
        {
            index_file >> value >> morse_code;
            editNode(root, morse_code, value);
        }
        index_file.close();
    }
    else
    {
        index_file.close();
        std::ofstream index_file;
        index_file.open(directory, std::ofstream::out);
        index_file << MGM_LENGTH << endl;
        for (int i = 0; i < MGM_LENGTH; ++i)
            index_file << MGM_LIST[i] << ' ' << MGM_ENCODE[MGM_LIST[i]] << endl;
        index_file.close();
    }

    cout << "Morse Coder" << endl;
    char key;
    string str;
    while (true)
    {
        cout << "Decode or Encode(D/e)?";
        key = _getch();
        switch (key)
        {
        case 27: // ESC
            exit(0);
        case 69:  // E
        case 101: // e
            cout << endl;
            getline(cin, str);
            for (auto i = str.begin(); i != str.end(); ++i)
            {
                if (i == str.begin())
                    cout << MGM_ENCODE[*i & UPPER];
                else
                {
                    if (*i == ' ')
                        cout << "   ";
                    else if (*i == '\n')
                        break;
                    else
                    {
                        if (*i >= 'a' && *i <= 'z')
                            *i &= UPPER;
                        cout << ' ' << MGM_ENCODE[*i];
                    }
                }
            }
            cout << endl;
            break;
        case 68:  // D
        case 100: // d
        default:
            cout << endl;
            string code;
        _input:
            str.clear();
            getline(cin, str);
            if (!std::regex_search(str, MORSE_PATTERN))
            {
                cout << "Invalid Input!\nPlease try again." << endl;
                goto _input;
            }
            std::istringstream line(str);
            while (line >> code)
                cout << searchMorse(root, code);
            cout << endl;
            break;
        }
    }
    return 0;
}