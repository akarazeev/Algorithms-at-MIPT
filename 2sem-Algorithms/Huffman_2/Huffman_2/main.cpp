#include <queue>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "bitChar.h"

const std::string magicNum="7771234777";
const int asciiSize = 256;
int lCount[asciiSize];
std::string str_code[asciiSize];

struct node{
    char ch;
    int count;
    node* left;
    node* right;
};

class cmp{
public:
    bool operator()(const node* lhs, const node* rhs) const
    {
        return lhs->count > rhs->count;
    }
};

node* makeNode(char ch, int count)
{
    node* tmp = new node;
    tmp->ch = ch;
    tmp->count = count;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
};

typedef std::priority_queue<node*, std::vector<node*>, cmp> mypq;

void trie(mypq& _X)
{
    while(_X.size() > 1)
    {
        node* holder = new node;
        holder->left = _X.top(); _X.pop();
        holder->right = _X.top(); _X.pop();
        holder->count = holder->left->count + holder->right->count;
        holder->ch = -1;
        _X.push(holder);
    }
}

//Create bit codes by recursively traversing the trie, adding a 0 for left and 1 for right, the key is to remove the end char when the recursion breaks and you have to go up a level
void code(node* _X)
{
    static std::string bits = "";
    if (_X->right != NULL)
    {
        bits += "1";
        code(_X->right);
        bits = bits.substr(0, bits.size() - 1);
    }
    if (_X->left != NULL)
    {
        bits += "0";
        code(_X->left);
        bits = bits.substr(0, bits.size() - 1);
    }
    if(!_X->left && !_X->right)
    {
        str_code[_X->ch] = bits;
    }
}

void count(std::string file, int& _X){
    char letter;
    std::ifstream inf(file.c_str());
    
    inf >> std::noskipws;
    
    //Clears array
    for(int i = 0;i < asciiSize; ++i)
        lCount[i] = 0;
    
    //Goes through text and counts
    while(inf >> letter){
        if(letter >= 0 && letter < asciiSize)
        {
            ++lCount[letter];
            ++_X;
        }
    }
    inf.close();
}

//Generates a string of the bit codes in the order they appear in the file
//Used during encoding
std::string BITSstring(std::string inFile)
{
    char input;
    std::string BITS = "";
    
    //Open input stream and create BITS string of entire file
    std::ifstream inf(inFile.c_str());
    inf >> std::noskipws;
    
    while(inf >> input)
    {
        BITS += str_code[input];
    }
    
    inf.close();
    
    //Append ascii 3 EOT character to signify end of text
    BITS += str_code[3];
    
    return BITS;
}

int main(int argc, char** argv)
{
    int rc;
    char choice;
    unsigned char inChar;
    std::string inFile = "", outFile = "", BITS = "", BITSsub = "", mn = "";
    std::ofstream outf;
    std::ifstream inf;
    mypq pq;
    bitChar bchar;
    int origSize = 0;
    
    std::cout << "Menu..." << std::endl << "e) Encode file" << std::endl << "d) Decode file" << std::endl;
    std::cin >> choice;
    
    switch(choice)
    {
        case 'e':
            //Get input filename and set output filename
            std::cout<<"Enter File Name to Encode: "<<std::endl;
            std::cin>>inFile;
            
            outFile = inFile + ".mpc";
            
            std::cout << std::left << std::setw(17);
            std::cout << "Input filename: " << inFile << std::endl;
            std::cout << std::left << std::setw(17);
            std::cout << "Output filename:" << outFile << std::endl;
            std::cout << std::endl;
            
            //Open output streams
            outf.open(outFile.c_str());
            
            //count and populate array of letter occurrences (lCount) and add one EOT char
            count(inFile, origSize);
            if(lCount[3] == 0)
                lCount[3] = 1;
            
            //Output compressed file header
            outf<<magicNum<<std::endl;
            outf<<inFile<<std::endl;
            for(int i = 0; i < asciiSize; ++i)
            {
                outf << lCount[i] << " ";
            }
            outf << std::endl;
            
            //Create nodes based on the available ascii characters and push them into the priority queue
            for(int i = 0; i < asciiSize; ++i)
            {
                if(lCount[i] > 0)
                {
                    node* tmp = makeNode(i, lCount[i]);
                    pq.push(tmp);
                }
            }
            
            //Create trie and bit codes
            trie(pq);
            code(pq.top());
            
            //Create string of bitcodes for actual huffman encoding and do it
            BITS = BITSstring(inFile);
            outf << '#';
            bchar.setBITS(BITS);
            outf << std::noskipws;
            rc = bchar.insertBits(outf);
            
            if(rc == BITS.length())
            {
                std::cout << "Encoding succsessful! :)" << std::endl;
                std::cout << "The compression ration is: " << (float)rc / ((float)origSize * 8.0) * 100.0 << "%" << std::endl;
            }
            else
            {
                std::cout << "There was an error writing the bits! :(" << std::endl;
                std::cout << "Expected: " << BITS.length() * 8 << " but got: " << rc << std::endl;
            }
            
            break;
        case 'd':
            //Get input filename and set output filename
            std::cout<<"Enter File Name to Decode: "<<std::endl;
            std::cin>>inFile;
            
            inf.open(inFile.c_str());
            inf >> mn;
            if(mn != magicNum)
            {
                std::cout << "Magic number does not match, this is not a valid file..." << std::endl;
                return 1;
            }
            
            inf >> outFile;
            if(outFile != inFile.substr(0, inFile.length() - 4))
            {
                std::cout << outFile << " " << inFile.substr(0, inFile.length() - 4) << std::endl;
                std::cout << "File names do not match but will attempt to decode anyway..." << std::endl;
            }
            outf.open(outFile.c_str());
            
            //Read in the letter count and add valid one to the priority queue
            for(int i = 0; i < asciiSize; ++i)
            {
                inf >> lCount[i];
                if(lCount[i] > 0)
                {
                    node* tmp = makeNode(i, lCount[i]);
                    pq.push(tmp);
                }
            }
            
            //Create trie and bit codes
            trie(pq);
            code(pq.top());
            
            while(inChar != '#')
            {
                inf >> inChar;
            }
            
            inf >> std::noskipws;
            //Read in encoded chars and create BITS
            while(inf >> inChar)
            {
                BITS += bchar.getBits(inChar);
            }
            
            inf.close();
            
            for(int i = 0; i < BITS.length(); ++i)
            {
                BITSsub += BITS[i];
                for(int j = 0; j < asciiSize; ++j)
                {
                    if(BITSsub == str_code[j])
                    {
                        //End of text has been hit and file is over, write newline and exit
                        if(j == 3)
                        {
                            outf << "\n";
                            i = BITS.length();
                            break;
                        }
                        outf << (char)j;
                        BITSsub = "";
                        break;
                    }
                }
            }
            
            break;
        default:
            std::cout << "Invalid choice...." << std::endl;
            break;
    }
    
    outf.close();
    
    return 0;
}