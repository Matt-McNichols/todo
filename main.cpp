#include <algorithm>
#include<iostream>
#include<istream>
#include<vector>
#include<string>
#include"ToDo.h"
#include<fstream>

using namespace std;

void MainMenu()
{
  cout<<"======Main Menu====="<<endl;
  cout<<"1. Quit"<<endl;//main
  cout<<"2. Edit List"<<endl;
  cout<<"3. Print Options"<<endl;
  cout<<"4. Edit scratchpad"<<endl;
  cout<<"=========================="<<endl;
  return;
}

void EditList()
{
  cout<<"======Edit List====="<<endl;
  cout<<"1. Back To Main"<<endl;
  cout<<"2. Add Item"<<endl;//edit list
  cout<<"3. Completed Task"<<endl;//edit list
  cout<<"4. Edit by Name"<<endl;//edit list
  cout<<"5. Clear All"<<endl;//edit list
  cout<<"=========================="<<endl;
}

void PrintOptions()
{
  cout<<"======Print Options====="<<endl;
  cout<<"1. Back To Main"<<endl;
  cout<<"2. Print By priority"<<endl;//pritn options
  cout<<"3. Print By Date"<<endl;//print options
  cout<<"4. Print What is Due Today"<<endl;//print options
  cout<<"5. Print What is Due This Month"<<endl;//print options
  cout<<"=========================="<<endl;
}

void editScratch()
{
  cout<<"====== Scratch Options ====="<<endl;  
  cout<<"1. Back to Main"<<endl;       
  cout<<"2. Add Scratch Item"<<endl;      
  cout<<"3. Print Scratch Items"<<endl; 
  cout<<"4. Erase Item"<<endl;       
  cout<<"5. Erase All"<<endl;        
  cout<<"============================"<<endl;
}
//setup the main function with three print menues instead of just 1



int main()
{
  int input;
  // Flag used for exiting menu
  bool quitMain = false;
  ToDo T;
  scratch S;
  //input existing items from todoList.txt back into T 
  T.readIn();
  //input file will not be found the first time through 
  //as soon as the user exits the program all info will be written to
  //a newly created file  
  while(quitMain != true)
  {
    MainMenu();
    cin >> input;

    //clear out cin
    cin.clear();
    cin.ignore(10000,'\n');
    //T.getTime();
    switch (input)
    {



      // edit list
      case 2:
        {
          bool quitEdit=false;
          while(quitEdit==false)
          {

            EditList();
            int EditInput;
            cin>>EditInput;
            cin.clear();
            cin.ignore(1000,'\n');
            //edit menu (2nd level)
            switch(EditInput)
            {
              //add item
              case 2:
                {//add item case
                  string name;
                  string Spriority;
                  string date;
                  int priority=0;
                  cout << "Enter Item Name:" << endl;
                  getline(cin,name);
                  cout << "Enter Priority:" << endl;
                  getline(cin,Spriority);
                  priority=atoi(Spriority.c_str());
                  cout << "Enter Due Date(MM/DD/YYYY):" << endl;
                  getline(cin,date);
                  T.addItem(name,priority,date);
                }//end add item case
                break;
                //completed task
              case 3:
                {//completed task
                  string name;
                  cout << "Enter Item Name:" << endl;
                  getline(cin,name);
                  T.taskComplete(name);

                }//end completed task
                break;
              case 4:
                {//edit by name
                  cout << "Enter the name of an item: " << endl;
                  string EditName;
                  getline(cin,EditName);
                  T.EditbyName(EditName);
                }//end edit by name
                break;
              case 5:
                {//clear all
                  T.clearAll();
                }//end clear all
                break;
              case 1:
                { //back to main
                  quitEdit=true;
                }//end back to main
                break;
              default:
                {
                  cout << "Invalid Input" << endl;
                  cin.clear();
                  cin.ignore(10000,'\n');
                }
            }//end edit item switch
          }//end edit item while
        }//end of case 1
        break;
      case 3:
        {//print properties
          bool quitPrint=false;
          while(quitPrint==false)
          {//open while
            PrintOptions();
            int PrintInput;
            cin>>PrintInput;
            cin.clear();
            cin.ignore(1000,'\n');
            switch(PrintInput)
            {
              //print all items
             /* case 1:
                {
                  T.displayALL();
                }
                break;*/
                //print by priority
              case 2:
                {
                  T.PrintPriority();
                }
                break;
                //print by date
              case 3:
                {
                  T.PrintDate();
                }
                break;
                //print what is due today
              case 4:
                {
                  T.PrintDueToday();
                }
                break;
                //print what is due this month
              case 5:
                {
                  T.PrintDueMonth();
                }
                break;
              case 1:
                {
                  quitPrint=true;
                }
                break;
            }//close switch
          }//close while
        }//close case
        break;  
        //edit scratch pad  
      case 4:
        {
          S.readIn();
          bool endScratch=false; 
          while(endScratch==false)
          {
            editScratch();
            int selectScratch;
            cin>>selectScratch; 
            cin.clear();
            cin.ignore(1000,'\n');

            switch(selectScratch)
            {
              case 2:
                {
                  //add item case
                  string name;
                  string Spriority;
                  int priority=0;
                  cout << "Enter Item Name:" << endl;
                  getline(cin,name);
                  //cout << "Enter Priority:" << endl;
                  //getline(cin,Spriority);
                  //priority=atoi(Spriority.c_str());
                  S.addItem(name);
                }//end add item case
                break;
              case 4:
                {//erase scratch
                  string name;
                  S.printPriority();
                  cout << "Enter Item List Number:" << endl;
                  getline(cin,name);
                  S.subItemComplete(atoi(name.c_str()));

                }
                break;
              case 3:
                {//print scratch
                  S.printPriority();
                }
                break;
              case 5:
                {
                  S.clearAll();
                }
                break;
              case 1:
                {//back to main
                  endScratch=true;
                  S.readOut();
                  S.clearAll();
                }
                break;

            }
          }
        }
        break;
        //quit
      case 1:   
        { 
          cout << "Goodbye!" << endl;
          quitMain = true;
          T.readOut();
        }
        break;


        // invalid input
      default:
        {
          cout << "Invalid Input" << endl;
          cin.clear();
          cin.ignore(10000,'\n');
        }
        break;
    }//close switch
  }//close while
  return 0;
}//close main
