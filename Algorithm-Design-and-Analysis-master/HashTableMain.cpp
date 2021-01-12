#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <chrono> // C++11
#include <ctime>
#include <list>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <cctype>
#include <cstring>
#include <string>
#include "HT_Chaining.h"
#include "HT_LinearProbing.h"

void displayData(string, vector<string>, double, double, double, double);

int main()
{
   fstream myfile1;
   vector<string> vectEmail;
   vector<string> vectEmailFound;
   vector<string> vectEmailNotFound;
   string line;

  /********** ********** **********
   * user input
   ********** ********** **********/

   int fileChoice;
   string fileName;
   string emailFound;
   string emailNotFound;
   cout
   << "Choose email file\n"
   << "1. email_100.txt\n"
   << "2. email_100000\n"
   << "3. email_500000\n";
   cin >> fileChoice;
   cout << endl;

   if (fileChoice == 1){
    fileName = "email_100.txt";
    emailFound = "Email Found_100.txt";
    emailNotFound= "Email Not Found_100.txt";
   } else
   if (fileChoice == 2){
    fileName = "email_100000.txt";
    emailFound = "Email Found_100000.txt";
    emailNotFound= "Email Not Found_100000.txt";
   }else
   if (fileChoice == 3){
    fileName = "email_500000.txt";
    emailFound = "Email Found_500000.txt";
    emailNotFound= "Email Not Found_500000.txt";
   }else{
    cout << "error";
    return 0;
   }

  /********** ********** **********
   * io file
   ********** ********** **********/

   /*
    * Email Generator File
    */

   myfile1.open(fileName); //opening the file.
   if (myfile1.is_open())         //if the file is open
   {
      while (!myfile1.eof()) //while the end of file is NOT reached
      {
         getline(myfile1, line);    //get one line from the file
         vectEmail.push_back(line); //output loop statement
      }
      myfile1.close(); //closing the file
   }
   else
   {
       cout << "Unable to open file";
       return 0;
   }
   vectEmail.pop_back();

   /*
    * Email Found File
    */

   myfile1.open(emailFound);
   if (myfile1.is_open()) //if the file is open
   {
      while (!myfile1.eof()) //while the end of file is NOT reached
      {
         getline(myfile1, line);         //get one line from the file
         vectEmailFound.push_back(line); //output loop statement
      }
      myfile1.close(); //closing the file
   }
   else
      cout << "Unable to open file found";

   vectEmailFound.pop_back();

   /*
    * Email Not Found File
    */

   myfile1.open(emailNotFound);
   if (myfile1.is_open()) //if the file is open
   {
      while (!myfile1.eof()) //while the end of file is NOT reached
      {
         getline(myfile1, line);         //get one line from the file
         vectEmailNotFound.push_back(line); //output loop statement
      }
      myfile1.close(); //closing the file
   }
   else
      cout << "Unable to open file found";

   vectEmailNotFound.pop_back();



  /********** ********** **********
   * construct hash table
   ********** ********** **********/

   const float HTCDATASIZE = 0.9;
   const float HTLBDATASIZE = 1.5;

   // Declaration
   HT_Chaining htc(vectEmail.size() * HTCDATASIZE);
   HT_LinearProbing htlp(vectEmail.size() * HTLBDATASIZE);


   // Construct gash table using chaining method and record the time
   int sum_ascii;
   auto insetStart = chrono::system_clock::now();
   for (int i = 0; i < vectEmail.size(); i++)
   {
      for (char c : vectEmail[i])
      {
         sum_ascii += c;
      };
      htc.insertItem(sum_ascii, vectEmail[i]);
      sum_ascii = 0; //clear the sum_ascii
   }
   auto insetEnd = chrono::system_clock::now();
   double nanotime_htcInsertTaken = chrono::duration_cast<chrono::nanoseconds>(insetEnd - insetStart).count();
   double millitime_htcInsertTaken = chrono::duration_cast<chrono::milliseconds>(insetEnd - insetStart).count();

   // Construct gash table using linear probing method and record the time
   sum_ascii;
   insetStart = chrono::system_clock::now();
   for (int i = 0; i < vectEmail.size(); i++)
   {
      for (char c : vectEmail[i])
      {
         sum_ascii += c;
      };
      htlp.insertItem(sum_ascii, vectEmail[i]);
      sum_ascii = 0; //clear the sum_ascii
   }
   insetEnd = chrono::system_clock::now();
   double nanotime_htlpInsertTaken = chrono::duration_cast<chrono::nanoseconds>(insetEnd - insetStart).count();
   double millitime_htlpInsertTaken = chrono::duration_cast<chrono::milliseconds>(insetEnd - insetStart).count();

   //Display fileChoice that is email_100.txt
   /* */
   if(fileChoice == 1){
      cout << "HashTable Chaining Method\n\n";
      cout << htc << endl << endl;
      cout << "HashTable Linear Probing Method\n\n";
      htlp.displayAll();
      cout << endl << endl;
   }/* */


  /********** ********** **********
   * calculate hash table searching
   * && retrieval time
   ********** ********** **********/

   cout << "VECT FOUND SIZE: " << vectEmailFound.size() << endl;

   sum_ascii = 0;
   auto searchStart = chrono::system_clock::now();
   for (int i = 0; i < vectEmailFound.size(); i++){
      for (char c : vectEmailFound[i]){
         sum_ascii += c;
      };
      cout << "ITEM " << htlp.retrieve(sum_ascii) << " At Key => " << htlp.hashfunction(sum_ascii) << "\n";
      sum_ascii = 0;
   }
   auto searchEnd = chrono::system_clock::now();
   double nanotime_htlpSearchTaken = chrono::duration_cast<chrono::nanoseconds>(searchEnd - searchStart).count();
   double millitime_htlpSearchTaken = chrono::duration_cast<chrono::milliseconds>(searchEnd - searchStart).count();

   displayData("Linear Probing", vectEmail,
               nanotime_htlpInsertTaken, millitime_htlpInsertTaken,
               nanotime_htlpSearchTaken, millitime_htlpSearchTaken);


   sum_ascii = 0;
   searchStart = chrono::system_clock::now();
   bool htcFound = false;
   for (int i = 0; i < vectEmailFound.size(); i++)
   {
      for (char c : vectEmailFound[i])
      {
         sum_ascii += c;
      };
      if (htcFound = htc.retrieve(sum_ascii, vectEmailFound[i]))
        cout << "ITEM " << vectEmailFound[i] << " At Key => " << htc.hashfunction(sum_ascii) << endl;
      sum_ascii = 0;
   }
   searchEnd = chrono::system_clock::now();
   double nanotime_htcSearchTaken = chrono::duration_cast<chrono::nanoseconds>(searchEnd - searchStart).count();
   double millitime_htcSearchTaken = chrono::duration_cast<chrono::milliseconds>(searchEnd - searchStart).count();

   displayData("Chaining Method", vectEmail,
               nanotime_htcInsertTaken, millitime_htcInsertTaken,
               nanotime_htcSearchTaken, millitime_htcSearchTaken);

}

void displayData(string hashtableMethod, vector<string> vectEmail,
                 double nanotime_insertTaken, double millitime_insertTaken,
                 double nanotime_searchTaken, double millitime_searchTaken){

   cout << "\n" << hashtableMethod << "\n\n";
   cout << "Total Nanoseconds for Inserting " << vectEmail.size() << " Emails: " << nanotime_insertTaken << " nanoseconds";
   cout << "\n";
   cout << "Average Nanoseconds for Inserting " << vectEmail.size() << " Email: " << nanotime_insertTaken / vectEmail.size() << " nanoseconds";
   cout << "\n";
   cout << "Total Milliseconds for Inserting " << vectEmail.size() << " Email: " << millitime_insertTaken << " milliseconds";
   cout << "\n";
   cout << "Average Milliseconds for Inserting " << vectEmail.size() << " Email: " << millitime_insertTaken / vectEmail.size() << " milliseconds";
   cout << "\n";

   cout << "\n";
   cout << "Total Nanoseconds for Searching " << vectEmail.size() << " Emails: " << nanotime_searchTaken << " nanoseconds";
   cout << "\n";
   cout << "Average Nanoseconds for Searching " << vectEmail.size() << " Email: " << nanotime_searchTaken / vectEmail.size() << " nanoseconds";
   cout << "\n";
   cout << "Total Milliseconds for Searching " << vectEmail.size() << " Email: " << millitime_searchTaken << " milliseconds";
   cout << "\n";
   cout << "Average Milliseconds for Searching " << vectEmail.size() << " Email: " << millitime_searchTaken / vectEmail.size() << " milliseconds";
   cout << "\n\n\n";
}


