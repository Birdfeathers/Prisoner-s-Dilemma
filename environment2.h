#include <iostream>
using namespace std;
#include <time.h>
#include <cmath>


/*
Prisoner's Delimma
if A cooperates and B doesn't A leaves zero descendents and B leaves 3
if A and B both cooperate they each leave two descendents
if neither A or B cooperate they each leave one descendent

cooperate = true, don't cooperate = false

srand (time(NULL));
int random = rand() % 100;
*/

struct program
{
  bool last;
  int number; // number of rounds played so far
  int identity;
  double total;
  int place;
  int tplace;
  program* next;
  program* prev;;

};


class environment
{
private:
  program* head; // first node
  program* tail; // last node
  //string orientation = "pos";
  int totalPrograms;
  int total[20];
  int addtotal;
  bool cont = true;
public:
  bool round(program *pro);
  void update(bool other, program* pro);
  environment();
  void def();
  bool custom();
  void rules();
  void listPrograms();
  bool addtype(int type);
  void Addnew(int identity, program* previous);
  void switchSides(program* pro);
  void reset();
  void Display();
  void convertProgram(int id, program *pro);
  void compete();
  program* returnHed(){return head;}
  program* returnTail(){return tail;}
  void run();
  void rerun();
  void setProgram();
  void deleteNode(program* pro);
  void deleteEveryOther();
  void deleteAll();

};
