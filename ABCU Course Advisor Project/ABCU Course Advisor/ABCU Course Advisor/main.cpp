//
//  main.cpp
//  ABCU Course Advisor
//
//  Created by Russell Pallas III on 6/9/21.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//================================================================================================================================
//--------------------------------------------------------------------------------------------------------------------------------
//================================================================================================================================
struct Course {
   string courseObjID;  //ID of each course loaded into courseVector vector (i.e. "CSCI100")
   string courseObjName;  //name of each course loaded into courseVector (i.e. "Introduction to Programming")
   string courseObjPR1;  //First pre-requisite of each course loaded into courseVector (displayed as ID) (IF APPLICABLE)
   string courseObjPR2;  //Second pre-requisite of each course loaded into courseVector (displayed as ID) (IF APPLICABLE)
};

void ClearScreen() {
   cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int menuInput;  //user menu selection
void Menu() {
   cout << "ABCU Course Planner" << endl << endl;  //menu display
   
   cout << "1. Load Data Structure" << endl;
   cout << "2. Print Course List" << endl;
   cout << "3. Print Course" << endl;
   cout << "9. Exit" << endl << endl;
   cout << "Please make a selection from the list above here -->";
   cin >> menuInput; //user selection
   
   if (menuInput != 1 && menuInput != 2 && menuInput != 3 && menuInput != 9) { //input validation
      ClearScreen();
      cout << "Invalid selection. Please try again." << endl <<endl;
      Menu();  //recursive menu call if invalid menu selection
   }
}

vector<Course> courseVector;   //VECTOR TO HOLD COURSE OBJECTS*********
vector<string> tempCourseVector;  //temporary courseVector vector used for sorting (will only be courseID's)
string fileName;  //file name to be entered by user
bool fileLoaded = false;  //used to confirm if file loaded properly
void LoadDataStructure() {
   
   cout << "Please enter file name here -->"; //file name entry prompt
   
   string fileName;       //file name to be entered by user
   cin >> fileName;       //file name assignment
   
   ifstream file;         //create file object
   file.open(fileName);   //opening of file with user specified file name
   
   if (!file.is_open()) {
      cout << "File failed to open" << endl; //file opening verification
   }
   
   string courseID, courseName, PR1, PR2;    //course attributes
   string line;
   while (getline(file, line)) {
      stringstream ss(line);
      
      getline(ss, courseID, ',');            //main course ID, read until comma
      getline(ss, courseName, ',');          //main course name, read until comma
      getline(ss, PR1, ',');                 //first pre-requisite (IF APPLICABLE), read until comma
      getline(ss, PR2, ',');                //second pre-requisite (IF APPLICABLE), read until newline
      
      Course course;                         //course object to be modified/put into courseVector
      course.courseObjID = courseID;         //course object ID
      course.courseObjName = courseName;     //course object name
      course.courseObjPR1 = PR1;             //course object PR1 (I/A)
      course.courseObjPR1 = PR2;             //course object PR2 (I/A)
      courseVector.push_back(course);        //adds course object to course vector
      
      fileLoaded = true; //used for printing courses to determine if file was loaded
   }                     //will default to false should Menu() have to be recalled for some failed process
   file.close();  //close file
   
   for (int i = 0; i < courseVector.size(); i++) {               //sort courseVector alphanumerically
      string tempCourseString = courseVector.at(i).courseObjID;  //string of courseObjID used to compare to courseVector.at().courseObjID
      tempCourseVector.push_back(tempCourseString);
   }
   sort(tempCourseVector.begin(), tempCourseVector.end());  //actual built-in sorting function
}

/*
 To then print the list in order, rather than ordering the courseVector vector, the courseVector is loaded as-is. The tempCourseVector vector is loaded with the courseID (as a string) of each course. The tempCourseVector is then sorted so all of the courseID's are sorted alphanumerically. We will later use this when printing all of the courses. The PrintAllCourses() function will use this sorted list to iterate through the courseVector and print the object's information for that iteration.
 */

void PrintCourseList() {  //prints an alphanumerically ordered list of all of the course objects
   ClearScreen();
   for (int i = 0; i < tempCourseVector.size(); i++) {
      for (int j = 0; j < courseVector.size(); j++) {
         if (tempCourseVector.at(i) == courseVector.at(j).courseObjID) {
            if (i != 0 && i != 1 && i != 2) {
            cout << tempCourseVector.at(i) << ": " << courseVector.at(j).courseObjName << endl;
            cout << "PR1: " << courseVector.at(j).courseObjPR1 << endl;
            cout << "PR2: " << courseVector.at(j).courseObjPR2 << endl << endl;
            }
         }
      }
   }
}

void PrintCourse() {  //prints a course specified by the user
   ClearScreen();
   
   string courseSelection;  //user specified course
   if (fileLoaded == false) {  //file loaded check
      cout << "Must load data structure before printing courses. Please select \"1. Load Data Structure\" first." << endl << endl;
      Menu();  //recursive menu display if load failed
   }
   else {
      for (int i = 0; i < courseVector.size(); i++) {
         if (i == 8 || i == 9 || i == 10) {
            break;
         }
         cout << courseVector.at(i).courseObjID << ": " << courseVector.at(i).courseObjName << endl << endl;
      }
      cout << "Please select a course from the list above. Enter Course ID here -->";   //course selection prompt
      cin >> courseSelection;
      
      for (int i = 0; i <= courseVector.size(); i++) {
         if (courseSelection == courseVector.at(i).courseObjID) {   //loop through courseVector until course ID matches user specified ID
            cout << courseVector.at(i).courseObjID << endl;
            cout << courseVector.at(i).courseObjName << endl;
            cout << courseVector.at(i).courseObjPR1 << endl;
            cout << courseVector.at(i).courseObjPR2 << endl;
         }
         else if (i == courseVector.size()) {     //if user enters a course that does not exist, they are notified and menu is recalled
            cout << "Course does not exist" << endl;
            Menu();
         }
      }
   }
}

void Exit() {  //confirmation of program termination
   ClearScreen();
   cout << "\n\n\n\nExiting Program \n\n\n\n";
}
//=================================================================================================================================
//---------------------------------------------MAIN STARTS HERE--------------------------------------------------------------------
//=================================================================================================================================

int main() {   //tried to keep main as clean as possible
   
   char continueToMenu; //after process completed, user will be asked whether they would like to do something else (y/n)
   bool quitInput = false;   //bool will be true when user specifies that they wish to leave program and while loop will terminate
   while (quitInput != true) {
      
      Menu();  //intial menu display
      
      switch (menuInput) {  //menuInput received from Menu()
         case 1:
            LoadDataStructure();  //loading the user specified file into the data structure
            ClearScreen();
            cout << "Would you like to make another selection? Enter y/n here -->";
            cin >> continueToMenu;
            
            if (continueToMenu == 'y') {
               quitInput = false;  //loop continuation
               ClearScreen();
            }
            else if (continueToMenu == 'n') {
               quitInput = true;  //loop temrination
               Exit();
            }
            break;
         case 2:
            LoadDataStructure(); //user doesn't need to use option 1(load structure) first becasue we also call loadstructure in all options
            PrintCourseList();
            
            cout << "Would you like to make another selection? Enter y/n here -->";
            cin >> continueToMenu;

            if (continueToMenu == 'y') {
               quitInput = false;
               ClearScreen();
            }
            else if (continueToMenu == 'n') {
               quitInput = true;
               Exit();
            }
            break;
         case 3:
            LoadDataStructure();
            PrintCourse();
            cout << "Would you like to make another selection? Enter y/n here -->";
            cin >> continueToMenu;
            
            if (continueToMenu == 'y') {
               quitInput = false;
               ClearScreen();
            }
            else if (continueToMenu == 'n') {
               quitInput = true;
               Exit();
            }
         case 9:
            Exit();
            quitInput = true;
      }
   }
}
