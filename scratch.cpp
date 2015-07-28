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

scratch::scratch()
{ 
}



scratch::~scratch()
{
}

void scratch::readIn()
{
 // cout<<"enter read in"<<endl;
  ifstream inputFile;
  inputFile.open("Scratch.txt"); //open file from the command line 
  if (inputFile.is_open())
  {
    string line;
    while(!inputFile.eof())
    {
      //read in the date as a string
      getline(inputFile,line,'\n');
      if(inputFile.eof()){break;}
      /* int eoDate=line.find('-');
         string Fdate=line.substr(0,eoDate);
       */
      //read in the name as a string
      int endOFname=line.find('\n');
      // int nameLength=endOFname-(eoDate+2);
      string Fname=line.substr(0,endOFname);

      //read in the priority as a string 
      //string Fpriority=line.substr(endOFname+1);

      //call add item to add the file item into vector
 //     cout<<"item added"<<endl;
      addItem(Fname);

    }
  }
}



void scratch::readOut()
{
 // cout<<"readout called"<<endl;
  ofstream fileOut;
  fileOut.open("Scratch.txt");
  for(int i=scratchList.size()-1;i>=0;i--)
  {
   // cout<<"inside file out"<<endl;
    fileOut<<scratchList[i].name<<endl;
  }
  fileOut.close();

}

void scratch::addItem(string name)
{
  //add the item to vector
  subItem v;
  v.name=name;
  int priority=scratchList.size();
  v.priority=priority;
  scratchList.push_back(v);

}

void scratch::printPriority()
{
  cout<<"\n**************** Print Scratch List ****************"<<endl; 
  int i,j;

  for(i= (scratchList.size()-1); i>0; --i)
  {
    for(j=0; j<i; j++)
    {
      if(scratchList[j].priority<scratchList[j+1].priority)
      {
        subItem temp=scratchList[j];
        scratchList[j]=scratchList[j+1];
        scratchList[j+1]=temp;
      }
    }
  }

  vector<subItem>::iterator myIntVectorIterator;
  for(myIntVectorIterator = scratchList.begin(); myIntVectorIterator != scratchList.end();myIntVectorIterator++)
  {
    cout<<'\n'<<(*myIntVectorIterator).priority<<"---"<<(*myIntVectorIterator).name<<endl;   

  }

  cout<<"\n****************************************************\n"<<endl; 
}


void scratch::subItemComplete(int listNum)
{
  bool found=false;
  for(int i=0; i<scratchList.size(); i++)
  {
    if(scratchList[i].priority==listNum)
    {

      scratchList.erase(scratchList.begin()+i);
      found=true;
      break;
    }
  }
  if(found==false)cout<<"completed item not found"<<endl;
  return;

}

void scratch::changePriority()
{
}

void scratch::clearAll()
{
  scratchList.clear();
}



