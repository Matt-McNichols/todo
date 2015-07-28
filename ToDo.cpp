#include<iostream>
#include<string>
#include<sstream>
#include <algorithm>
#include<vector>
#include<string>
#include<fstream>
#include<ctime>
#include"ToDo.h"

using namespace std;


ToDo :: ToDo()
{
}

ToDo :: ~ToDo()
{
}

/*
  Function Prototype:
  void ToDo :: readIn()
  
  Function description:
  This method reads any todo list items that are saved in the
  ToDoList.txt file.  If there are items in the file, this method 
  re-enters the items into the todoList vector. This allows for the
  user to exit the program and start the program again without 
  losing their todo list items

  Example:
  ToDo T;
  T.readOut();

  Precondition:
  The ToDoList.txt file has only been written to by the program. 
  This method is called every time the user enters the program,
  if the user has an empty todo list the method will not do 
  anything.

  Post condition:
  The items that have been entered by the user while previously 
  running the program are entered into todoList vector. If no items
  have previously been entered, the vector remains empty.
 */
void ToDo :: readIn()
{
  ifstream inputFile;
  inputFile.open("ToDoList.txt"); //open file from the command line 
  if (inputFile.is_open())
    {
      string line;
      while(!inputFile.eof())
	{
	  //read in the date as a string
	  getline(inputFile,line,'\n');
	  if(inputFile.eof()){break;}
	  int eoDate=line.find('-');
	  string Fdate=line.substr(0,eoDate);

	  //read in the name as a string
	  int endOFname=line.find(":");
	  int nameLength=endOFname-(eoDate+2);
	  string Fname=line.substr((eoDate+2),nameLength);

	  //read in the priority as a string 
	  string Fpriority=line.substr(endOFname+1);

	  //call add item to add the file item into vector
	  addItem(Fname,atoi(Fpriority.c_str()),Fdate);
	  
	}
    }
}

/*
Function prototype:
void ToDo :: readOut()

Function description:
This method is called once the user has selected Quit from the 
menue.  The purpose of this method is to write all items from the 
todoList vector to the ToDoList.txt file.  

Example:
ToDo T;
T.readOut();

Precondition:
The Item vector is either empty or contains a objects of type item.
The user has entered valid inputs for the item components.

Post condition:
Each item from the todoList vector has been written to the 
ToDoList.txt file in the same odder they appear in the vector
 */
void ToDo :: readOut()
{
  ofstream fileOut;
  fileOut.open("ToDoList.txt");
  for(int i=0;i<todoList.size();i++)
  {
    fileOut<<todoList[i].monthDue<<"/"<<todoList[i].dayDue<<"/"<<todoList[i].yearDue<<"--"<<todoList[i].name<<":"<<todoList[i].priority<<endl;
  }
  fileOut.close();

}

/*
Function Prototype
void ToDo :: addItem(string name, int priority,string date)

Function Description:
This method adds an item to the todoList vector. The user is asked
to enter the items name, priority and due date. These values are 
passed to this method which breaks the date appart, creates a new 
item and pushes it into the todoList vector.

Example:
ToDo T;
T.addItem(example, 500, 04/25/2015)

Precondition:
The user must type valid inputs for name, priority and date. The 
date must be in the specified order and include the '/' in the 
correct locations.

Post condition:
The inputs given by the user are stored into a new item and the item
is pushed onto the todoList vector.
 */

void ToDo :: EditbyName(string IncomingName )
{
  bool foundItem=0;
  int scroll;

  for( scroll =0; scroll<todoList.size(); scroll++)
  {
    if( todoList[scroll].name==IncomingName)
    {
      cout<<"you found a match!!"<<endl;
      foundItem=1;
      break;
    }//incoming name was not found 
    cout<<"no match was found"<<endl;
  }

  if(foundItem)
  {
    //Now you Know Incoming main item is located at index[scroll]
    //
    string New_name_string="empty";
    int priority=-1;
    string New_date_string="empty";

    //*************************************************************
    while(1)
    {
      //Get replacement name info
      cout<<"\nDo you want a new Name?  (y/n)"<<endl;
      string userResponse;
      cin>>userResponse;
      if(userResponse=="y")
      {
        cout<<"The item's new name will be..."<<endl;
        string newName;
        cin>>newName;
        New_name_string=newName;

        //NewName is a string that has the items new name 
        //todoList[scroll].name=newName;
        break;

      }

      else if(userResponse=="n")
      {
        New_name_string=todoList[scroll].name;
        break;
      }
      else cout<<"oops not an option"<<endl;
    }//end name info loop

    //get priority info

//*************************************************************
    while(1)
    {
      //Get replacement priority info
      cout<<"Set a different priority?  (y/n)"<<endl;
      string userResponse;
      cin>>userResponse;
      if(userResponse=="y")
      {
        cout<<"The item's new priority will be..."<<endl;
        string newPriority;
        cin>>newPriority;

        //NewName is a string that has the items new name 
        priority=atoi(newPriority.c_str());
        break;
      }

      else if(userResponse=="n")
      {
        priority=todoList[scroll].priority;
        break;
      }
      else cout<<"oops not an option"<<endl;
    }//end name info loop 
    //*************************************************************
    while(1)
    {
      //Get replacement day due info
      cout<<"Set a different due date?  (y/n)"<<endl;
      string userResponse;
      cin>>userResponse;
      if(userResponse=="y")
      {
        cout<<"The item's new due date will be (MM/DD/YYYY):"<<endl;
        string newDueDate;
        cin>>newDueDate;
        New_date_string=newDueDate;
        //NewName is a string that has the items new name 
        // todoList[scroll].dayDue=newDueDate;
        break;
      }

      else if(userResponse=="n")
      {
        //*****need to deal with the issue of having a string for the date and integers in todoList
        stringstream day;
        day << todoList[scroll].dayDue;
        string oldDay = day.str();

        stringstream month;
        month << todoList[scroll].monthDue;
        string oldMonth = month.str();

        stringstream year;
        year << todoList[scroll].yearDue;
        string oldYear = year.str();

        New_date_string = oldDay+"/"+oldMonth+"/"+oldYear;
        break;
      }
      else cout<<"oops not an option"<<endl;
    }//end name info loop 


    //if no edits were made dont do anything otherwise rm the orriginal
    //item and add a new item
    if(New_name_string=="empty" && priority==-1 && New_date_string=="empty")return;
    else 
    {
      taskComplete(IncomingName);
      addItem(New_name_string, priority, New_date_string);
    }


  }//end of found item while loop
  else cout<<"Item was not found"<<endl;
  return;

}

/*
Function Prototype
void ToDo :: addItem(string name, int priority,string date)

Function Description:
This method adds an item to the todoList vector. The user is asked
to enter the items name, priority and due date. These values are 
passed to this method which breaks the date appart, creates a new 
item and pushes it into the todoList vector.

Example:
ToDo T;
T.addItem(example, 500, 04/25/2015)

Precondition:
The user must type valid inputs for name, priority and date. The 
date must be in the specified order and include the '/' in the 
correct locations.

Post condition:
The inputs given by the user are stored into a new item and the item
is pushed onto the todoList vector.
 */

void ToDo :: addItem(string name, int priority,string date)
{
      //break up the date string into seperate parts
      //month
      int monthLength=date.find('/');
      string month=date.substr(0,monthLength);
      
      //day
      int dayPosition=date.find('/',monthLength+1);
      int dayLength=dayPosition-monthLength;
      string day=date.substr(monthLength+1,dayLength-1);
      
      //year
      string year=date.substr(dayPosition+1);
      
      //add the item to vector
      item v;
      v.name=name;
      v.priority=priority;
      v.dayDue=atoi(day.c_str());
      v.monthDue=atoi(month.c_str());
      v.yearDue=atoi(year.c_str());
      todoList.push_back(v);
}


/*
Function Prototype:
void ToDo :: displayALL()

Funcion Description:
This method is used to display all items that are in the todoList 
vector. The method uses a vector iterator to scroll through all
each item in order and displays all the information about the item.

Example:
ToDo T;
T.displayAll();

Precondition:
This method assumes there are items in the vector. If there are no 
items in the vector, this method simply returns and does not output 
anything.

Post conditions:
This method will output the items in the vector in the order the 
items appear in the vector. It will output all the information for
each item. The output is of the same format as the output used when
writing to the ToDoList.txt file. 
 */

void ToDo :: displayALL()
{
  vector<item>::iterator myIntVectorIterator;
for(myIntVectorIterator = todoList.begin(); myIntVectorIterator != todoList.end();myIntVectorIterator++)
  {
    cout<<(*myIntVectorIterator).monthDue<<"/"<<(*myIntVectorIterator).dayDue<<"/"<<(*myIntVectorIterator).yearDue<<"--"<<(*myIntVectorIterator).name<<":"<<(*myIntVectorIterator).priority<<endl;   
  }
}
/*
Function Prototype:
void ToDo :: PrintPriority()

Function Description:
This method re-arranges the items in the todoList vector based on
priority. The method arranges from highest priority value to lowest.
The method then prints the items. This method only prints the item
priority value and name.

Example:
ToDo T;
T.PrintPriority();

Precondition:
This method assumes there are Items in the todoList vector. Also 
the method assumes the user entered a valid input for the priority
value of each item.

Post condition:
The todoList vector order has been changed. The highest priority 
item is first in the vector and lowest is last. The method prints 
the items in the new order.
 */
void ToDo :: PrintPriority()
{
  int i,j;
  cout<<"\n**************** List By Priority ****************"<<endl; 
  for(i= (todoList.size()-1); i>0; --i)
    {
      for(j=0; j<i; j++)
	{
	  if(todoList[j].priority<todoList[j+1].priority)
	    {
	      item temp=todoList[j];
	      todoList[j]=todoList[j+1];
	      todoList[j+1]=temp;
	    }
	}
    }
  
vector<item>::iterator myIntVectorIterator;
for(myIntVectorIterator = todoList.begin(); myIntVectorIterator != todoList.end();myIntVectorIterator++)
  {
    cout<<'\n'<<(*myIntVectorIterator).priority<<":"<<(*myIntVectorIterator).name<<endl;   
    
  }
  cout<<"\n**************************************************\n"<<endl; 
}
/*
Function Prototype:
void ToDo :: PrintDate()

Function Description:
This method re-arranges the items in the todoList vector based on
date. The method arranges items from the earliest date to the latest
The method then prints the items. This method only prints the item
date value and name.

Example:
ToDo T;
T.PrintDate();

Precondition:
This method assumes there are Items in the todoList vector. Also 
the method assumes the user entered a valid input for the date
value of each item.  There is a prototype date value printed when 
the program asks the user to enter the date.

Post condition:
The todoList vector order has been changed. The earliest due
date item is now first in the vector while the latest due date
item is last. The method prints the items in the new order.
 */
void ToDo :: PrintDate()
{
  cout<<"\n**************** List By Date ****************"<<endl; 
  int i,j;
  //sort by year
for(i=(todoList.size()-1); i>0; --i)
    {
      for(j=0; j<i; j++)
	{
	  if(todoList[j].yearDue>todoList[j+1].yearDue)
	    {
	      item temp=todoList[j];
	      todoList[j]=todoList[j+1];
	      todoList[j+1]=temp;
	    }
	}
    }

  //sort by month
  for(i=(todoList.size()-1); i>0; --i)
    {
      for(j=0; j<i; j++)
	{
	  if((todoList[j].yearDue==todoList[j+1].yearDue)&&(todoList[j].monthDue>todoList[j+1].monthDue))
	    {
	      item temp=todoList[j];
	      todoList[j]=todoList[j+1];
	      todoList[j+1]=temp;
	    }
	}
    }

  //sort by date within each month
  for(i= (todoList.size()-1); i>0; --i)
   {
      for(j=0; j<i; j++)
	{
	  if((todoList[j].monthDue==todoList[j+1].monthDue)&&(todoList[j].dayDue>todoList[j+1].dayDue))
	    {
	      item temp=todoList[j];
	      todoList[j]=todoList[j+1];
	      todoList[j+1]=temp;
	    }
	}
    }

vector<item>::iterator myIntVectorIterator;
for(myIntVectorIterator = todoList.begin(); myIntVectorIterator != todoList.end();myIntVectorIterator++)
  {
    cout<<'\n'<<(*myIntVectorIterator).monthDue<<"/"<<(*myIntVectorIterator).dayDue<<"/"<<(*myIntVectorIterator).yearDue<<"--"<<(*myIntVectorIterator).name<<endl;   
    
  }
  cout<<"\n**********************************************\n"<<endl; 
}
/*
Function Prototype:
void ToDo :: taskComplete(string task)

Function description:
This method allows the user to remove an item from the todoList 
vector.  The user is asked to enter the item name which is passed to
this method as a string. The method then finds the item with the 
same name and deletes the item.

Example:
ToDo T;
T.taskComplete("homework") 

Precondition:
The method searches the vector and if the string matches an item
name the item is erased from the vector. If the string does not
match any item names the the function tells the user the item was
not found and returns.
 
Post condition:
If an item is found,the vector is re-sized and all other items are 
shifted appropriately.
 */
void ToDo :: taskComplete(string task)
{
  bool found=false;
  for(int i=0; i<todoList.size(); i++)
    {
      if(todoList[i].name==task)
	{
	  
	  todoList.erase(todoList.begin()+i);
	  found=true;
	  break;
	}
    }
  if(found==false)cout<<"completed item not found"<<endl;
  return;
}
/*
Function prototype:
void ToDo :: PrintDueToday()

Function description:
This method uses ctime library to compare the due date of each item
in the vector with the current date. If an item has a due date 
that matches the current date the method prints the item.

Example:
ToDo T;
T.PrintDueToday();

Precondition:
This method assumes the vector is not empty and that items contain
valid inputs. 

Postcodition:
The function prints the items that are due today but makes no change
the the todoList vector
 */
void ToDo :: PrintDueToday()
{
  cout<<"\n**************** List Due Today ****************"<<endl; 
 time_t t = time(0);   // get time now
 struct tm * now = localtime( & t );
 
 vector<item>::iterator myIntVectorIterator;
for(myIntVectorIterator = todoList.begin(); myIntVectorIterator != todoList.end();myIntVectorIterator++)
  {
    if(now->tm_mday==(*myIntVectorIterator).dayDue && (now->tm_mon+1)==(*myIntVectorIterator).monthDue && (now->tm_year+1900)==(*myIntVectorIterator).yearDue)
      {
	cout<<'\n'<<(*myIntVectorIterator).monthDue<<"/"<<(*myIntVectorIterator).dayDue<<"/"<<(*myIntVectorIterator).yearDue<<"--"<<(*myIntVectorIterator).name<<":"<<(*myIntVectorIterator).priority<<endl;   
      }
  }

  cout<<"\n************************************************\n"<<endl; 
}
/*
Function prototype:
void ToDo :: PrintDueToday()

Function description:
This method uses ctime library to compare the due date of each item
in the vector with the current date. If an item has a due date 
whos month matches the current month the method prints the item.

Example:
ToDo T;
T.PrintDueMonth();

Precondition:
This method assumes the vector is not empty and that items contain
valid inputs. 

Postcodition:
The function prints the items that are due this month but makes no
change the the todoList vector.
 */
void ToDo :: PrintDueMonth()
{
  cout<<"\n**************** List Due This Month ****************"<<endl; 
  time_t t = time(0);   // get time now
  struct tm * now = localtime( & t );
  
  vector<item>::iterator myIntVectorIterator;
  for(myIntVectorIterator = todoList.begin(); myIntVectorIterator != todoList.end();myIntVectorIterator++)
    {
      if((now->tm_mon+1)==(*myIntVectorIterator).monthDue && (1900+now->tm_year)==(*myIntVectorIterator).yearDue)
	{
	  cout<<'\n'<<(*myIntVectorIterator).monthDue<<"/"<<(*myIntVectorIterator).dayDue<<"/"<<(*myIntVectorIterator).yearDue<<"--"<<(*myIntVectorIterator).name<<":"<<(*myIntVectorIterator).priority<<endl;   
	}
    }

  cout<<"\n*****************************************************\n"<<endl; 
}
/*
Function Prototype:
void ToDo :: clearAll()

Function description:
This method allows the user to clear everything out of todoList 
vector. 

Example:
ToDo T;
T.clearAll();

Precondition:
This Function assumes there are items in the vector although if the
vector is empty, calling this method will not change the vector.

Post condition:
The vector is completely empty. All items have been freed. If the 
user ends the program after this method, the ToDoList.txt file will
be empty.
*/

void ToDo :: clearAll()
{
  todoList.clear();
}

