/*

VCC CMPT 1010 - Assignment 4

12/08/15

Junho Sohn, Justin Sze, Kai Lin

Ubbi Dubbi Translator
An Ubbi Dubbi translator which translates a single word or read, encode, and write to a file.

*/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

const int MAX_SIZE=100;
const string ub = "ub";
const string Ub = "Ub";

void intro_message();
void menu_option();
int get_input(int,int);

bool replay_check(int);

void encode_word();
string read_file_check(string&);
void read_file();

int check_letter(string);
string encode_file(string[],int,int);

string output_file_check(string&);
void READCHECK (int);

int main()
{
    ifstream in_stream;
    ofstream out_stream;
    string file, filearray[MAX_SIZE], FINAL_ARRAY[MAX_SIZE];
    int ubcount = 0, selection = 0, i=0, overwrite_check=0;

    intro_message();

    do
    {
        menu_option();
        selection = get_input(0,4);

        switch (selection)
        {
//***************************************************
        case 0:
            cout << "\nThanks for using our translator.\nGoodbye!" << endl;
            break;

//***************************************************
        case 1:
            do
            {
                system("cls");
                cout << "Please enter one word to be translated into Ubi Dubbi." << endl;
                cout << "Note that any other words than the first will be ignored." << endl << endl;
                encode_word();
            }
            while(replay_check(selection));
            system("cls");

            break;

//***************************************************
        case 2:
        {
            system("cls");
            read_file_check(file);
            in_stream.open(file.c_str()); //opens the file with inputted name

            if(overwrite_check>0)
            {
                cout << "You already read a file!\nReturning to main menu." << endl << endl;
                cin.clear(); cin.ignore();
                break;
            }

            while(in_stream.fail())
            {
                cout << "Input file error!" << endl;
                if(replay_check(selection))
                {
                    cout << endl;
                    read_file_check(file);
                    in_stream.open(file.c_str());
                }
                else
                {
                    cout << endl << "Returning to main menu." << endl;
                    break;
                }
            }

            while(!in_stream.eof() && !in_stream.fail() && i<MAX_SIZE)
            {
                in_stream >> filearray[i]; //all words stored in 'filearray[]'
                i++; //i = # of words
            }

            if(i==MAX_SIZE)
            {
                cout << "Your file contains more than 100 words.\nReturning to main menu." << endl << endl;
                i=0;
            }

            else if(i<MAX_SIZE)
            {
                overwrite_check++;
                cout << "File read successfully!" << endl << endl;
            }

            in_stream.clear();
            in_stream.close();
            cin.clear(); cin.ignore();
        }
        break;

//***************************************************
        case 3:
        {
            system("cls");
            READCHECK(i);
            if(i==0)
                break;

            for(int z=0; z<i; z++)
            {
                int wordsize = filearray[z].length();
                FINAL_ARRAY[z] = encode_file(filearray,z,wordsize);
            }

            cout << "Encoding complete!" << endl << endl;
        }
        break;

//***************************************************
        case 4:
        {
            system("cls");
            READCHECK(i);

            if(i==0)
                break;

            output_file_check(file);
            out_stream.open(file.c_str()); //sets inputted name as output file

            if(out_stream.fail())
            {
                cout << "Output file error!";
                exit(1);
            }

            for(int a=0; a<i; a++)
                out_stream << FINAL_ARRAY[a] << " ";

            out_stream.close();

            cout << "Writing complete!" << endl << endl;
            cin.clear();
            cin.ignore();
        }
        break;

        }
    }
    while(selection!=0);

    return 0;
}


///*************///
///* FUNCTIONS *///
///*************///

//Intro message
//PRE: None
//POST: Displays message
void intro_message()
{
    cout << "******************************************" << endl;
    cout << "*                                        *" << endl;
    cout << "*  Welcome to the Ubi Dubbi translator!  *" << endl;
    cout << "*                                        *" << endl;
    cout << "******************************************" << endl << endl;
}

//Menu Options
//PRE: None
//POST: Displays message
void menu_option()
{
    cout << "****************************" << endl;
    cout << "*                          *" << endl;
    cout << "*   0 - Quit the program   *" << endl;
    cout << "*   1 - Encode word        *" << endl;
    cout << "*   2 - Read file          *" << endl;
    cout << "*   3 - Encode file        *" << endl;
    cout << "*   4 - Write to a file    *" << endl;
    cout << "*                          *" << endl;
    cout << "****************************" << endl << endl;
    cout << "Make your selection: ";
}

//Gets valid input (0<=input<=4)
//PRE: Asks for menu selection
//POST: Returns input that is 0<=input<=4
int get_input(int min, int max)
{
    int num;
    cin.unsetf(ios::skipws);
    while ( !(cin >> num) || ( cin.get() != '\n') ||  (num > max) || (num < min) )
    {
        cout << "Invalid. Re-enter from " << min << "-" << max << ": ";
        cin.clear(); // unset failbit
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.setf(ios::skipws);
    return num;
}

//Do again? Yes or no
//PRE: Yes/No question
//POST: Returns true if Y/y, false if N/n
bool replay_check(int checknum)
{
    char ch;

    do
    {
        if(checknum==1)
            cout << endl << "Again? (Y/N) ";
        else if(checknum==2)
            cout << endl << "Do you want to enter again? (Y/N) ";

        cin >> ch;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    while (!(ch=='y' || ch=='n' || ch=='Y' || ch=='N'));

    if(ch=='y' || ch=='Y')
        return true;
    else
        return false;
}

//Translates one word into Ubbi Dubbi
//PRE: Takes in a word (or multiple)
//POST: Returns printed translation and ignores any words after the first
void encode_word()
{
    char word_input;
    cin.get(word_input);
    cout << endl;

    while(word_input!='\n')
    {
        if(word_input=='a' || word_input=='e' || word_input=='i' ||
                word_input=='o' || word_input=='u')
            cout << ub;
        else if(word_input=='A' || word_input=='E' || word_input=='I' ||
                word_input=='O' || word_input=='U')
        {
            word_input +=32; //change to lowercase
            cout << Ub;
        }

        cout << word_input;
        cin.get(word_input);

        if(word_input== ' ') //Ignores all words after the first
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
            return;
        }
    }

    cout << endl;
}

//Reads input name of file
//PRE: None
//POST: Returns input
string read_file_check(string& filename)
{
    cin.clear();
    cout << "Input the name of the file: ";
    cin >> filename;

    filename = filename + ".txt"; //converting to .txt format

    cout << endl << "Reading from file " << filename << endl;
    cout << "---------------------------------" << endl;

    return filename;
}

//Reads output name of file
//PRE: None
//POST: Returns input
string output_file_check(string& filename_output)
{
    cin.clear();
    cout << "Input the name of the output file: ";
    cin >> filename_output;

    filename_output = filename_output + ".txt"; //converting to .txt format

    cout << endl << "Outputting to file " << filename_output << endl;
    cout << "---------------------------------" << endl;

    return filename_output;
}

//Checks each letter and returns value accordingly
//PRE: 'lettercheck' is actually a string
//POST: Returns 0, 1, or 2 depending on if it is an UPPERCASE/lowercase vowel
int check_letter(string lettercheck)
{
    if (lettercheck=="a" || lettercheck=="e" || lettercheck=="i" || lettercheck=="o" || lettercheck=="u")
        return 2;
    else if (lettercheck=="A" || lettercheck=="E" || lettercheck=="I" || lettercheck=="O" || lettercheck=="U")
        return 1;
    else if(!(lettercheck=="A" || lettercheck=="E" || lettercheck=="I" || lettercheck=="O" || lettercheck=="U") &&
            !(lettercheck=="a" || lettercheck=="e" || lettercheck=="i" || lettercheck=="i" || lettercheck=="u"))
        return 0;
}

//Encodes strings from the array and returns translation
//PRE: Array is sent from main along with length of the word and what 'place' the word is in
//POST: Returns translated word, with proper capitalization
string encode_file(string arr[], int s, int wordlength)
{
    string letter;
    string newword = "";

    for(int j=0; j<wordlength; j++)
    {
        letter = arr[s].at(j);

        if(check_letter(letter) == 1) //if first letter is uppercase...
        {
            letter = tolower(arr[s].at(j)); //change to lowercase
            newword = newword + Ub + letter;
        }

        else if(check_letter(letter) == 2)
            newword = newword + ub + letter;

        else if(check_letter(letter) == 0)
            newword = newword + letter;
    }
    return newword;
}

//Displays an error message if a file hasn't been read
//PRE: No files have been read
//POST: Display message
void READCHECK (int iii)
{
    if(iii==0)
    {
        cout << "**********************************" << endl;
        cout << "*                                *" << endl;
        cout << "*  You haven't read a file yet!  *" << endl;
        cout << "*    Returning to main menu.     *" << endl;
        cout << "*                                *" << endl;
        cout << "**********************************" << endl;
    }
}
