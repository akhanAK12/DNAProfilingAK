// Project 1 Starter Code - DNA Profiling

//  File name: main.cpp Author: Arij Khan
//  NetId: akhan342  System: Replit


/*
Creative Componenet: Largest DNA Occurences 
My creative component was finding the dna that occurs the most within the dna sequence. I check if a data base has been added in and if dna is added in as well in order for my component to work. 

*/

#include "ourvector.h"

#include <sstream>

#include <fstream>

#include <vector>

using namespace std;

struct setVec
{

    ourvector<char> hold;
};

struct dataBaseData
{

    string name; // holds the name

    ourvector<int> values; // holds the numbers
};

void displayDataBase(ourvector<setVec> dataBaseDNA, ourvector<dataBaseData> dataBase);

void displayDNA(ourvector<char> dnaStrand);

void displayProcessed(ourvector<setVec> dataBaseDNA, ourvector<int> processed, int counter);

void parseFileName(string &fileName, string &file)
{

    int till = fileName.find(" ");

    file = fileName.substr(till + 1);

    fileName = fileName.substr(0, till);
}

void countDNA(ourvector<setVec> &dataBaseDNA, int &counter)
{

    ourvector<char> holder;

    for (int i = 0; i < dataBaseDNA.size(); i++)
    {

        for (int j = 0; j < dataBaseDNA[i].hold.size(); j++)

            holder.push_back(dataBaseDNA[i].hold[j]);

        counter++;
    }

    counter -= 1;
}

void readFileDB(string fileName, ourvector<dataBaseData> &dataBase, ourvector<setVec> &dataBaseDNA, int &counter)
{
    dataBase.clear();
    dataBaseDNA.clear();
    counter = 0;
    fstream infile;

    string line = "";

    string tempString;

    infile.open(fileName);

    if (!infile.is_open())
    {

        cout << "Error: Unable to open '" << fileName << "'" << endl;

        return;
    }

    getline(infile, line); // gets the first line

    stringstream s(line);

    setVec newData; // declare an instance of setVec

    // pushes in the dna sequences

    while (getline(s, tempString, ','))
    {

        for (int i = 0; i < tempString.size(); i++)
        {

            newData.hold.push_back(tempString[i]);
        }

        dataBaseDNA.push_back(newData);

        newData.hold.clear();
    }

    countDNA(dataBaseDNA, counter); // counts the number of dna strands in dataBase

    dataBaseData person; // declare an instance of dataBaseData

    while (!infile.eof())
    {

        getline(infile, line); // gets the next line

        dataBaseData person;

        stringstream s(line);

        getline(s, tempString, ',');

        person.name = tempString; // will store in the first name from the file

        while (getline(s, tempString, ','))
        {

            person.values.push_back(stoi(tempString));
        }

        dataBase.push_back(person); // store that line data into

        person.values.clear();
    }
}

void readFileDNA(string fileName, ourvector<char> &dnaStrand)
{

    fstream infile;

    string line = "";

    string tempString;

    infile.open(fileName);

    if (!infile.is_open())
    {

        cout << "Error: Unable to open '" << fileName << "'" << endl;

        return;
    }

    while (!infile.eof()) {

        getline(infile, line); // gets the first line

        for (int i = 0; i < line.length(); i++)
        {

            dnaStrand.push_back(line[i]);
        }

        line.clear();
    }
}

void display(ourvector<setVec> dataBaseDNA, ourvector<dataBaseData> dataBase, ourvector<char> dnaStrand, ourvector<int> processed, int counter)
{

    if (dataBase.size() == 0 && dataBaseDNA.size() == 0)
    {

        cout << "No database loaded.";
    }

    else
    {

        cout << "Database loaded: " << endl;

        displayDataBase(dataBaseDNA, dataBase);
    }

    if (dnaStrand.size() == 0)
    {

        cout << endl;

        cout << "No DNA loaded." << endl;

        cout << endl;
    }

    else
    {

        cout << endl;

        cout << "DNA loaded: " << endl;

        displayDNA(dnaStrand);
    }

    if (processed.size() == 0)
    {

        cout << "No DNA has been processed." << endl;
    }

    else
    {

        cout << "DNA processed, STR counts: " << endl;

        displayProcessed(dataBaseDNA, processed, counter);
    }
}

void displayDataBase(ourvector<setVec> dataBaseDNA, ourvector<dataBaseData> dataBase)
{

    for (int i = 0; i < dataBase.size(); i++)
    {

        cout << dataBase[i].name;

        for (int j = 0; j < dataBase[i].values.size(); j++)
        {

            cout << " " << dataBase[i].values[j];
        }

        cout << endl;
    }
}

void displayDNA(ourvector<char> dnaStrand)
{

    for (int i = 0; i < dnaStrand.size(); i++)
    {

        cout << dnaStrand.at(i);
    }

    cout << endl;

    cout << endl;
}

void displayProcessed(ourvector<setVec> dataBaseDNA, ourvector<int> processed, int counter)
{
int position;
    for (int i = 1; i < counter + 2; i++)
    {

        for (int j = 0; j < dataBaseDNA[i].hold.size(); j++)
        {

            cout << dataBaseDNA[i].hold[j];
        }

        cout << ": ";

        cout << processed.at(position);
        if(position == counter - 1){
            cout << endl;
            return;
        }
        cout << endl;
        position++;
    }

    cout << endl;
}

  


void process(ourvector<setVec> dataBaseDNA, ourvector<char> dnaStrand, ourvector<int> &processed, int counter)
{

    for (int i = 1; i < dataBaseDNA.size(); i++)
    {

        int size = dataBaseDNA[i].hold.size(); // gets the size of the dna strand

        int DNAindex = 0; // keeps track of where we are in the vector

        int max = 0; // hold the max streak

        int currStreak = 0;

        while (true)
        {

            int fakeindex = DNAindex;

            for (int index = 0; index < size; index++)

            {
                // if characters match
                if (dataBaseDNA[i].hold[index] == dnaStrand.at(fakeindex))

                {

                    // if the DNA string in dataBase matches with a DNA strand in dnaStrand then increment streak
                    if (index == size - 1)

                    {

                        currStreak++;

                        DNAindex += size; // setting the DNAindex by the size of the string we are comparing with(AATAC - 5, so dnaIndex would be at 5)
                    }
                }

                else
                {

                    if (currStreak > max) // current streak is greater then set it as max

                    {

                        max = currStreak;
                    }

                    DNAindex++; // move to the next nucleotide char by 1

                    currStreak = 0;

                    break;
                }

                fakeindex++;
            }

            // if we get to the end of the dna sequence
            if (DNAindex == dnaStrand.size())

            {

                break;
            }
            // checks if we are reading less than size characters
            if (dnaStrand.size() - DNAindex < size)

            {

                break;
            }
            // if we get to the end of the sequence
            if (fakeindex >= dnaStrand.size())
            {

                break;
            }
        }

        processed.push_back(max); // push back max streak
    }
}

void search(ourvector<dataBaseData> &dataBase, ourvector<int> &processed, int counter, string file)
{

    int counterResults = 0; // index for processed vector

    int counterCorrect = 0; // counter for the number of correct comparasions

    string name;

    for (int i = 0; i < dataBase.size(); i++)
    {
        // loops through each dna strand within the vector
        for (int j = 0; j < dataBase[i].values.size(); j++)
        {

            if (processed.at(counterResults) == dataBase[i].values[j])
            {

                ++counterResults;

                ++counterCorrect; // increment counter by 1 if numbers match

                if (counterCorrect == processed.size())
                {

                    name = dataBase[i].name;

                    cout << "Found in database!  "
                         << "DNA matches: ";
                    cout << name << endl;
                    return;
                }
            }

            else
            {

                counterResults = 0;
                counterCorrect = 0;
            }
        }
    }
    if (counterResults != processed.size())
    {
        cout << "Not found in database." << endl;
    }
}

void largestDNA(ourvector<int> processed, ourvector<setVec> dataBaseDNA, int counter){
  
  int mostdnaOccur = 0;   
  int index = 1;
  
  for(int i = 0; i < processed.size(); i++){
    
    if(processed.at(i) > mostdnaOccur){
      mostdnaOccur = processed.at(i);
      ++index;
      
    }

  }
  
  cout << "Most apperaed DNA strand that occured the most within the DNA sequence was: "; 
  for(int j = 0; j < dataBaseDNA.size(); j++){
    
    cout << dataBaseDNA[index].hold.at(j); 
  }

  cout << endl; 

}


void handleUserInput(string &command, ourvector<char> &dnaStrand, ourvector<dataBaseData> &dataBase, ourvector<setVec> &dataBaseDNA, int &counter, ourvector<int> &processed)
{

    string file;

    parseFileName(command, file);

    if (command == "load_db")

    {

        cout << "Loading database..." << endl;

        // function will read in the file(int/names) into the dataBase vector and dna into dataBaseDna vector

        readFileDB(file, dataBase, dataBaseDNA, counter);
    }

    if (command == "load_dna")

    {

        cout << "Loading DNA..." << endl;

        readFileDNA(file, dnaStrand);
    }

    if (command == "display")

    {

        display(dataBaseDNA, dataBase, dnaStrand, processed, counter);
    }

    if (command == "process")

    {

        if (dataBase.size() == 0 && dataBaseDNA.size() == 0)

        {

            cout << "No database loaded." << endl;
        }

        else if (dnaStrand.size() == 0)

        {

            cout << "No DNA loaded." << endl;
        }

        else

        {

            cout << "Processing DNA..." << endl;

            // Function will process the DNA and count the most consective strs which were repeated

            process(dataBaseDNA, dnaStrand, processed, counter);
        }
    }

    if (command == "search")

    {

        if (dataBase.size() == 0)
        {

            cout << "No database loaded." << endl;
        }
        else if (dnaStrand.size() == 0)

        {

            cout << "No DNA loaded." << endl;
        }

        else if (processed.size() == 0)

        {

            cout << "No DNA processed." << endl;
        }

        else
        {

            cout << "Searching database..." << endl;

            // Function will find if someone matches the same strs that were repeated in DNA database

            search(dataBase, processed, counter, file);
        }
    }
    // creative component
    if (command == "LargestDNA")
    {

        if (dataBase.size() == 0)
        {

            cout << "No database loaded." << endl;
        }

        else if (dnaStrand.size() == 0)

        {

            cout << "No DNA loaded." << endl;
        }

        else if (processed.size() == 0)

        {

            cout << "No DNA processed." << endl;
        }

        else
        {

            cout << "Looking for the DNA strand that occurs the most..." << endl << endl; 
           largestDNA(processed, dataBaseDNA, counter);
        }
    }
}

string menuOption(bool &exit)
{

    string userInput;

    cout << "Enter command or # to exit: ";

    getline(cin, userInput);

    if (userInput == "#")
    {

        exit = false;
    }

    return userInput;
}

int main()
{

    // TODO:  Write your code here.  You should have LOTS of function decomposition.

    bool quit = true;

    string command; // what user enters

    ourvector<char> dnaStrand; // stores the dna strands

    ourvector<dataBaseData> dataBase; // stores the frequncy and names

    ourvector<setVec> dataBaseDNA; // stoes in the dna strands from the data base files

    ourvector<int> processed; // stores the max streak of dna strands that occured

    int counter; // counts the number of dna strands from the data base files

    cout << "Welcome to the DNA Profiling Application." << endl;

    while (true)
    {

        command = menuOption(quit);

        if (quit == false) // if user enters in "#" then quit the program
        {

            break;
        }
        // handles users input
        handleUserInput(command, dnaStrand, dataBase, dataBaseDNA, counter, processed);
    }

    return 0;
}
