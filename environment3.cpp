#include <iostream>
using namespace std;
#include <time.h>
#include <cmath>
#include <iomanip>
#include "environment2.h"

bool CheckNumber(string string1) // verifies user response is a number
{
    for(int i = 0; i < string1.length(); i++)
    {
        if(!isdigit(string1[i]))return false;
    }
    return true;
}

environment :: environment()
{
  head = NULL;
  tail = NULL;
  totalPrograms = 0;
  for(int i = 0; i < 20; i++)
  {
    total[i] = 0;
  }


}

void environment :: def()
{
  int id;
  for(int j = 0; j < 500; j++)
  {
    if(j < 50) id = 1;
    else if(j < 100) id = 2;
    else if(j < 150) id = 3;
    else if(j < 200) id = 4;
    else if(j < 250) id = 5;
    else if(j < 300) id = 6;
    else if(j < 350) id = 7;
    else if(j < 400) id = 8;
    else if(j < 450) id = 9;
    else if(j < 500) id = 10;
    Addnew(id, tail);
  }
  totalPrograms = 500;
}


bool environment :: addtype(int type)
{
  string user_response;
  getline(cin, user_response);
  if(CheckNumber(user_response))
  {
    //total[type] = stoi(user_response);
    for(int i = 0; i < stoi(user_response); i++)Addnew(type, tail);
    addtotal += stoi(user_response);
    return true;
  }
  else{
    cout << "invalid input" << endl;
    return false;
  }
}
bool environment :: custom()
{
  addtotal = 0;
  cout << "How many TitforTat (cooperative)?" << endl;
  if(!addtype(1)) return false;
  cout << "How many AlwaysCooperate(cooperative)?" << endl;
  if(!addtype(3)) return false;
  cout << "How many GenerousTitforTat(cooperative)?" << endl;
  if(!addtype(7)) return false;
  cout << "How many WeightedAverage (cooperative)?" << endl;
  if(!addtype(10)) return false;
  cout << "How many TakeAverage(neutral)?" << endl;
  if(!addtype(5)) return false;
  cout << "How many Random (neutral)?" << endl;
  if(!addtype(6)) return false;
  cout << "How many MeanTitforTat(uncooperative)?" << endl;
  if(!addtype(2)) return false;
  cout << "How many NeverCooperate(uncooperative)?" << endl;
  if(!addtype(4)) return false;
  cout << "How many UngenrousTitfotTat (uncooperative)?" << endl;
  if(!addtype(8)) return false;
  cout << "How many ReverseTitforTat (uncooperative)?" << endl;
  if(!addtype(9)) return false;
  totalPrograms = addtotal;
  return true;
}

bool environment :: round(program *pro)
{
  srand (time(NULL));
  int random = rand() % 2;
  int lastnum;
  double ave;
  double Ave;
  switch(pro -> identity){
    case 1:
      // tit for tat
      // cooperative
      if(pro -> number == 0) return true;
      return pro -> last;
    case 2:
    // mean tit for Tat
    // unccoperative
      if(pro -> number == 0) return false;
      return pro -> last;
    case 3:
    // always cooperate
    // cooperative
      return true;
    case 4:
    // never cooperate
    // uncooperative
      return false;
    case 5:
    // take take TakeAverage
    // neutral
    if(pro -> number == 0)
    {
      if(random == 0) return true;
      return false;
    }
    else
    {
      if(pro -> total / pro -> number < .5) return false;
      return true;
    }
    case 6:
    // random
    //neutral
    if(random == 0) return true;
    return false;
    case 7:
    // generous tit for Tat
    // cooperative
    if(pro -> last == true || pro -> number == 0) return true;
    else{
      if(random == 0) return true;
      return false;
    }
    case 8:
    // ungenerous tit for tat
    // uncooperative
    if(pro -> last == false || pro -> number == 0) return false;
    else{
      if(random == 0) return true;
      return false;
    }
    case 9:
    // reverse tit for Tat
    // unccoperative
    if(pro -> number == 0) return false;
    return !(pro -> last);
    case 10:
    // average of last and TakeAverage
    // cooperate
    if(pro -> number == 0) return true;
    ave = pro -> total / pro -> number;
    if(pro -> last == 0) lastnum = 0;
    else lastnum = 1;
    Ave = (ave + lastnum) / 2;
    if(Ave < .5) return false;
    return true;


    break;
  }


}


void environment :: update(bool other, program* pro)
{
  pro -> last = other;
  if(other) pro -> total = pro -> total + 1;
  pro -> number++;
}

void environment :: Addnew(int identity, program* previous)
{
  program* newprogram = new program;
  newprogram -> identity = identity;
  newprogram -> number = 0;
  newprogram -> total = 0;
  if(head == NULL)
  {
    newprogram -> place = 1;
    newprogram -> tplace = 1;
    head = newprogram;
    tail = newprogram;
    newprogram -> next = NULL;
    newprogram -> prev = NULL;
  }
  else if(previous == tail)
  {
    newprogram -> place = tail -> place + 1;
    newprogram -> tplace = tail -> tplace +1;
    newprogram -> next = NULL;
    tail -> next = newprogram;
    newprogram -> prev = tail;
    tail = newprogram;
  }
  else
  {
    newprogram -> prev = previous;
    newprogram -> next = previous -> next;
    previous -> next -> prev = newprogram;
    previous -> next = newprogram;
    reset();


  }
  total[identity]++;
}

void environment :: switchSides(program* pro)
{
  pro -> tplace = pro -> place * -1;
  program* current = pro -> next;
  while(current != nullptr)
  {
    current -> tplace--;
    current = current -> next;
  }

}

void environment :: rules()
{
  cout << "The prisoner's dilemma involves pinning teamwork against indivual gain" << endl;
  cout << "In this version various strategies are able to reproduce more or less based on their choices" << endl;
  cout << "This is to help simulate the evolution of moral strategies" << endl;
  cout << "The rules in this simulation used are: " <<endl;
  cout << "   1. If program A chooses to cooperate and program B does not B turns A into B and makes one additional copy" << endl;
  cout << "   2. If both programs cooperative they each make one additional copy" << endl;
  cout << "   3. If neither cooperates neither makes a copy"<< endl;
}
void environment :: listPrograms()
{
  cout << "The 10 strategies employed are: " << endl;
  cout << "   1. TitforTat: initially cooperate, then do whatever was done to you last" << endl;
  cout << "   2. AlwaysCooperate: always cooperate" << endl;
  cout << "   3. GenerousTitforTat: like TitforTat, but with a 50% chance of cooperating when your last interaction was uncooperative" << endl;
  cout << "   4. WeightedAverage: initially cooperate, then respond with the average of what was done to you last and what was done so far" << endl;
  cout << "   5. TakeAverage: initially respond randomly, then respond with the average of what was done to you so far" << endl;
  cout << "   6. Random: respond randomly" << endl;
  cout << "   7. MeanTitforTat: initially don't cooperate, then do whatever was done to you last" << endl;
  cout << "   8. NeverCooperate: never cooperate" << endl;
  cout << "   9. UngenrousTitfotTat: like MeanTitforTat, but with a 50% chance of not cooperating when your last interaction was cooperative" << endl;
  cout << "   10. ReverseTitforTat: initially don't cooperate, then do the opposite of whatever was done to you last" << endl;

}

void environment :: reset()
{
  program* current = head;
  head -> place = 1;
  while(current != nullptr)
  {
    if(current != head)current -> place = current -> prev -> place +1;
    current -> tplace = current -> place;
    current = current -> next;
  }
}

void environment :: Display()
{
  // program *current = head;
  // while(current != NULL)
  // {
  //   cout << current -> identity << " -> ";
  //   current = current -> next;
  // }
  // cout << "NULL" << endl;
  double totalp;
  int c = 0, n = 0, u = 0;
  double t = totalPrograms;
  for(int i = 1; i < 11; i++)
  {
    //cout << i << ": " << total[i] <<": "<< fixed << setprecision(2)<< total[i]/t * 100 <<"%"<< endl;
    totalp += (total[i]/t * 100);
    if(i == 1 || i == 3 || i == 7 || i == 10) c +=(total[i]);
    else if(i == 5 || i == 6) n += (total[i]);
    else u += (total[i]);
  }
  cout << "1.TitforTat(cooperative) : " << total[1]  << "             " << fixed << setprecision(2)<< total[1]/t * 100 <<"%"<< endl;
  cout << "2.AlwaysCooperate(cooperative) : " << total [3] << "       " << fixed << setprecision(2)<< total[3]/t * 100 <<"%"<< endl;
  cout << "3.GenerousTitforTat(cooperative) : " << total[7] << "     "<< fixed << setprecision(2)<< total[7]/t * 100 <<"%"<< endl;
  cout << "4.WeightedAverage (cooperative) : "<< total[10]  << "      "<< fixed << setprecision(2)<< total[10]/t * 100 <<"%"<< endl;
  cout << "5.TakeAverage(neutral) : " << total[5] << "               " << fixed << setprecision(2)<< total[5]/t * 100 <<"%"<< endl;
  cout << "6.Random (neutral) : " << total[6] << "                   " <<fixed << setprecision(2)<< total[6]/t * 100 <<"%"<< endl;
  cout << "7.MeanTitforTat(uncooperative) : " << total[2] << "       " <<fixed << setprecision(2)<< total[2]/t * 100 <<"%"<< endl;
  cout << "8.NeverCooperate(uncooperative) : " << total[4] << "      " << fixed << setprecision(2)<< total[4]/t * 100 <<"%"<< endl;;
  cout << "9.UngenrousTitfotTat (uncooperative) : " << total[8] << " " << fixed << setprecision(2)<< total[8]/t * 100 <<"%"<< endl;
  cout << "10.ReverseTitforTat (uncooperative) : " << total[9] << "  " << fixed << setprecision(2)<< total[9]/t * 100 <<"%"<< endl << endl;
  cout << "Cooperative total: " << c << "     " << (c / t) * 100 << "%" << endl;
  cout << "neutral total: " << n << "         " << (n / t) * 100 << "%" << endl;
  cout << "Uncooperative total: " << u << "   " << (u / t) * 100 << "%" << endl;
  cout << "Total : " << totalPrograms << "                " << totalp << "%" << endl << endl;
}

void environment :: compete()
{
  cout << "competing . . ." << endl;
  int numleft = totalPrograms;
  for(numleft; numleft > 1 ; numleft = numleft -2 )
  {
    srand (time(NULL));
    int num1 = rand() % numleft + 1;
    int num2;
    if(num1 != numleft)num2 = num1 + 1;
    else num2 = num1 -1;

    program* pro1 = head;
    while(pro1 -> tplace != num1)
    {
      pro1 = pro1 -> next;
    }
    program *pro2 = head;
    while(pro2 -> tplace != num2)
    {
      pro2 = pro2 -> next;
    }
    bool response1 = round(pro1);
    bool response2 = round(pro2);
    update(response1, pro2);
    update(response2, pro1);
    if(response1)
    {
      if(response2)
      {
        Addnew(pro1 -> identity, pro1);
        // total[pro1 -> identity]++;
        Addnew(pro2 -> identity, pro2);
        // total[pro2 -> identity]++;
        totalPrograms +=2;
      }
      else
      {
        convertProgram(pro2 -> identity, pro1);
        Addnew(pro2 -> identity, pro2);
        totalPrograms++;
      }
    }
    else
    {
      if(response2)
      {
        convertProgram(pro1 -> identity, pro2);
        Addnew(pro1 -> identity, pro1);
        totalPrograms++;
      }
    }
    switchSides(pro1);
    switchSides(pro2);


  }
  reset();
  while(totalPrograms > 5000) deleteEveryOther();


}

void environment ::  convertProgram(int id, program *pro)
{
  total[pro -> identity]--;
  pro -> identity = id;
  pro -> number = 0;
  pro -> total = 0;
  total[id]++;
}
void environment :: setProgram()
{
  string user_response;
  cout << "How many of each program would you like to run?" << endl;
  cout << "1. Fifty each" << endl;
  cout << "2. custom" << endl;
  cout << "3. Rules" << endl;
  cout << "4. Programs" << endl;
  getline(cin, user_response);
  if(user_response == "1" || user_response =="one") def();
  else if(user_response == "2" || user_response == "two"){
    if(!custom()) {
      deleteAll();
      rerun();
    }
  }
  else if(user_response == "3" || user_response == "three")
  {
    rules();
    rerun();
    return;
  }
  else if(user_response == "4" || user_response == "four")
  {
    listPrograms();
    rerun();
    return;
  }
  else{
    cout << "invalid input" << endl;
    rerun();
    return;
  }
}

void environment :: run()
{
  if(!cont) return;
  string user_response;
  if(head == NULL) setProgram();
  if( head != NULL){
  if(!cont) return;
  cout << "How many rounds would you like to run the program for?"<< endl;
  getline(cin, user_response);
  if (CheckNumber(user_response))
  {
    for(int i = 0 ; i < stoi(user_response); i++) compete();
    Display();
  }
  else cout << "invalid input"<< endl;

  rerun();
}


}

void environment :: rerun()
{
  string user_response;
  cout << "Would you like to run the program for longer(y/n)" << endl;
  getline(cin, user_response);
  if(user_response[0] == 'n' || user_response[0] == 'N') cont = false;
  if(user_response[0] == 'y' ||user_response[0] == 'Y') run();
}

void environment :: deleteNode(program* pro)
{
  program* P = pro -> prev;
  program* N = pro -> next;
  if(head == pro)
  {
    N -> prev = NULL;
    N -> place = 1;
    head = N;
  }
  else if(pro == tail)
  {
    P -> next = NULL;
    tail = P;
  }
  else{
    P -> next = N;
    N -> prev = P;
  }
  total[pro -> identity]--;
  delete pro;
  pro = nullptr;
  totalPrograms--;
}

void environment :: deleteEveryOther()
{
  program* current = head;
  while(current != NULL)
  {
    if(current -> place % 2 == 0)
    {
      deleteNode(current -> prev);
    }
    current = current -> next;
  }
  reset();
}

void environment :: deleteAll()
{
  program *current = head;
  while(current != NULL)
  {
    current = current -> next;
    if(current!= NULL) deleteNode(current -> prev);
    cout << 6;

  }
  cout << 7;
  head = NULL;
}

int main()
{
  cout << "run" << endl;
  environment one;
  // one.convertProgram(9, one.returnHed());
  // one.Display();
  // for(int i = 0; i < 8; i++) one.compete();
  //
  // // one.deleteEveryOther();
  // // one.deleteEveryOther();
  // one.Display();
  // program* head = new program;
  // head = one.returnHed();
  // //one.deleteNode(head -> next);
  // //one.deleteNode(head);
  // program* tail = new program;
  // tail = one.returnTail();
  // //one.deleteNode(tail);
  // //one.deleteNode(tail -> prev);
  // one.deleteEveryOther();
  // one.Display();
  one.run();
}
