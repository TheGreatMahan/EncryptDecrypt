/*!	/file		bce.cpp
    /author		Mahan Mehdipour
    /date		2020-03-21

    encoding a text from a text file
    and using a book from another text file
    and using book cipher method
    The purpose of this program is to read
    a file and write in another and encoding
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
    ifstream message(argv[2]);
    if (!message)
    {
        cout << "Could not oper the message file!\n";
        return EXIT_FAILURE;
    }
    ofstream code(argv[3]);
    if (!code)
    {
        cout << "Could not oper the code file!\n";
        return EXIT_FAILURE;
    }
    //Adding the letters of the book to the s string using x
    char x;
    string s;
    while (book.get(x))
        s += x;
    
    //Declaring varibale that play with indexes using size_t from stdio.h library
    size_t pInd, lInd, index, finCol;//Page Index, Line Index, Index of the letter, Column Index
    size_t pCounter, lCounter;//Page Counter, Line Counter


    //get every single character of the file and finding the code for all
    while (message.get(x))
    {
        //initializing the variables in every iteration
        pInd = 0;
        lInd = 0;
        index = 0;
        pCounter = 0;
        lCounter = 0;


        index = s.find(x);
        //if didn't find character, print out what character you can't find and exit the program
        if (s.find(x) == string::npos) {
            cout << "Character " << x << " Could not be found!";
            return EXIT_FAILURE;
        }
        //As long as there is a new page character that is less than the index needed you will count them 
        //if there is any
        if (index > s.find('\f'))
        {
            pInd = s.find('\f');
            pCounter++;
            while (s.find('\f', pInd + 1) < index) {
                pInd = s.find('\f', pInd + 1);
                pCounter++;
            }
            //As long as there is a new line character that is less than the index needed you will count them 
            //if there is any
            if (index > s.find('\n', pInd + 1))
            {
                lInd = s.find('\n', pInd + 1);
                lCounter++;
                while (s.find('\n', lInd + 1) < index) {
                    lInd = s.find('\n', lInd + 1);
                    lCounter++;
                }
                
                lInd -= pInd + 2;
            }


        }
        //As long as there is a new line character that is less than the index needed you will count them 
        //if there is any and there is no new page character
        else if (index > s.find('\n'))
        {

            do
            {
                lInd = s.find('\n', lInd + 1);
                lCounter++;

            } while (s.find('\n', lInd + 1) < index);

        }


        //some conditions to find the final answer
        int finLin = 0;
        if (lInd > 0 || pInd > 0)
            finLin = lInd + pInd + 1;
        finCol = index - finLin;

        //adding the results to the code file
        code << pCounter << "," << lCounter << "," << finCol << " ";
    }
    //Closing the files
    book.close();
    message.close();
    code.close();

    //Returning EXIT_SUCCESS if you have everything worked perfectly
    return EXIT_SUCCESS;

}

