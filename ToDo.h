///////////////////////////////////////////////////////////////////////////////
//
// FILENAME: ToDo.h
// PROJECT : 
// KEYWORDS:
// LANGUAGE: 
// INTELLIPROP AUTHOR  : mattm
// CREATED : 7/14/2015
//
// DESCRIPTION:
//
// TESTS USED/CREATED:
//
// REVISION HISTORY: Rev1.0
// Date     Person      Description
// -------- ----------- -------------------------------------------------------
//
// CURRENT ISSUES: none.
//
// REMAINING WORK:
//
//
// This media contains an authorized copy or copies of material owned by
// IntelliProp Inc.  This ownership notice and any other notices included in
// machine readable copies must be reproduced on all authorized copies.
//
// This is confidential and unpublished property of IntelliProp Inc.
//
// All rights reserved.
// Copyright [2015] [IntelliProp Inc.]
//
// Licensed under the IntelliProp Software Products License,
// Version 1.0 (the "License");
//
// You may not use this file except in compliance with the IntelliProp
// Software Products License Agreement.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef TODO_H
#define TODO_H
#include<vector>
//#include<iostream>

struct item{
  std::string name;
  int priority;
  int dayDue;
  int monthDue;
  int yearDue;
};

struct subItem{
  std::string name;
  int priority;
};

class ToDo
{
  public:
    ToDo();
    ~ToDo();

    void readIn();
    void readOut();
    void addItem(std::string name, int priority, std::string date);
    void displayALL();
    void PrintPriority();
    void EditbyName(std :: string IncomingName);
    void PrintDate();
    void taskComplete(std::string task);
    void PrintDueToday();
    void PrintDueMonth();
    void clearAll();

  protected:
  private:
    std::vector<item> todoList;
};

class scratch
{
  public:
    scratch();
    ~scratch();

    void readIn();
    void readOut();
    void addItem(std::string name);
    void printPriority();
    void subItemComplete(int listNum);
    void changePriority();
    void clearAll();

  protected:
  private:
    std::vector<subItem> scratchList;
};

#endif // GRAPH_H
