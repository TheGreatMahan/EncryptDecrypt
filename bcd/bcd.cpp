/*!	/file		bcd.cpp
    /author		Mahan Mehdipour
    /date		2020-03-21

    decoding a code from a text file
    and using a book from another text file
    and using book cipher method
    The purpose of this program is to read 
    a file and write in another and decoding 
    using algorithms.
    
*/

//importing libraries for functions needed and using namespace std
#include <stdio.h>
#include <iostream>
#include <string>
#include <locale>	
#include <iomanip>	
#include <sstream>	
#include <fstream>
#include <cstdlib>
using namespace std;

//The main function has argc and argv as its parameters to 
//be able to use console arguments
int main(int argc, char* argv[])
{
    //validating the number of arguments
    if (argc < 4)
    {
        cout << "Too few arguments!" << endl;
        return EXIT_FAILURE;
    }
    if (argc > 4)
    {
        cout << "Too many arguments!" << endl;
        return EXIT_FAILURE;
    }
    //Streaming files in order to be able to manipulate data
    //and importing data from them or be able to add data to them
    ifstream book(argv[1]);
    if (!book)
    {
        cout << "Could not open the book file!\n";
        return EXIT_FAILURE;
    }
    ifstream code(argv[2]);
    if (!code)
    {
        cout << "Could not oper the code file!\n";
        return EXIT_FAILURE;
    }
    ofstream message(argv[3]);
    if (!message)
    {
        cout << "Could not oper the message file!\n";
        return EXIT_FAILURE;
    }

    //Adding the letters of the book to the str string using ch
    char ch;
    string str;
    while (book.get(ch))
        str += ch;
    //Declaring varibale that play with indexes using size_t from stdio.h library
    //and a char variable in order to get rid of commas while getting input from a file
    size_t pNum, pInd;//page numbers and page Index
    size_t lNum, lInd;//Line number and line Index
    size_t colNum;//column number
    size_t iBeforeCol;//Index that was chosen before Column
    size_t finalInd;//Final Index 
    char comma;

    //Getting input from the code file in order to be able to find the index of each letter
    while (code >> pNum >> comma >> lNum >> comma >> colNum)
    {
        iBeforeCol = 0;
        //if page number is more than 0 we will find the index of it
        //if afterwards line number is greater than 0 we will find the index of that and final index or else 
        //we will calculate the index without considering the line number
        if (pNum > 0)
        {
            pInd = str.find('\f');
            pNum--;
            while (pNum > 0) {
                pInd = str.find('\f', pInd + 1);
                pNum--;
            }
            if (lNum > 0)
            {
                lInd = str.find('\n', pInd + 1);
                lNum--;
                while (lNum > 0)
                {
                    lInd = str.find('\n', lInd + 1);
                    lNum--;
                }
                iBeforeCol = lInd;
            }
            else
            {
                iBeforeCol = pInd;
            }
            finalInd = colNum + iBeforeCol + 1;
        }
        //We will consider the this condition if page number is 0 and line number is greater than 0
        //In this condtion we will find the index of the last line and based on the number of the Lines
        //and will find the final Index based on that
        else if (lNum > 0)
        {
            lInd = str.find('\n');
            lNum--;
            while (lNum > 0)
            {
                lInd = str.find('\n', lInd + 1);
                lNum--;
            }
            iBeforeCol = lInd;
            finalInd = colNum + iBeforeCol + 1;
        }
        //We will consider the final index as the column number when there is no pages or lines
        else
            finalInd = colNum;

        message << str[finalInd];
    }

    //Closing the files
    book.close();
    message.close();
    code.close();

    //Returning EXIT_SUCCESS if you have everything worked perfectly
    return EXIT_SUCCESS;

}


