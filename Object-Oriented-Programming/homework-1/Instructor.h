#include <iostream>
#include <string.h>
using namespace std;


class instructor{
    //members
    string title;
    string firstName;
    string lastName;
    string telNumber;
    string roomNumber;
    string userName;
    string email;
    string *courses;
    string tempCourses;
    int courseNum;

    public:
        instructor(); // constructors
        instructor(const string&,const string&, const string&, const string&,const string&,const string&,const string&,const string&);

        void print() const;
        // getters and setter methods
        string gettelNumber() const;
        void settelNumber(const string&);
        string getroomNumber() const;
        void setroomNumber(const string&);

        string getTitle() const;
        void setTitle(const string&);

        string getfirstName() const;
        void setfirstName(const string&);


        string getlastName() const;
        void setlastName(const string&);

        string getuserName()const;
        void setuserName(const string&);


        string getemail() const;
        void setemail(const string&);


        //string getcourses() const;
        void setcourses( string);

        string * get_courses();
        int getCourseNum();

};
    instructor::instructor(){

}
// constructor with parameters
instructor::instructor(const string& tit,const string& f, const string& l, const string&t,const string &r,const string& u,const string& e,const string& c){

    title = tit;
    firstName = f;
    lastName = l;
    telNumber = t;
    roomNumber = r;
    userName = u;
    email = e;
    tempCourses = c;
}
void instructor::print() const{

cout << "instruction information" << endl;
cout<< "\t title: " << title << endl;
cout<< "\t first name: " << firstName<< endl;
cout<< "\t last name: " << lastName<< endl;
cout<< "\t tel number: " << telNumber << endl;
cout<< "\t room number: " << roomNumber << endl;

cout<< "\t user name: " << userName << endl;
cout<< "\t email: " << email << endl;
cout<< "\t courses: " << courses << endl;
}

string instructor::getTitle() const{
return title;
}
void instructor::setTitle(const string& title_in) {title = title_in;}


string instructor::getfirstName() const{
 return firstName;
 }

string instructor::getlastName() const{
return lastName;
}


string instructor::gettelNumber() const{
return telNumber;
}


string instructor::getroomNumber() const{
return roomNumber;
}

string instructor::getuserName()const{
return userName;
}


string instructor::getemail() const{
return email;
}



//string instructor::getcourses() const{
//return courses;}

void instructor::setcourses(string a){

	char *newArray = new char[a.length() + 1];
	int i;

	for (i = 0; i < a.length(); i++){
		newArray[i] = a[i];
	}
	newArray[i] = '\0';

	char *temporary = new char[strlen(newArray) + 1];
	temporary = strtok(newArray, " ");

	i = 0; // for course_num
	courseNum = 0;
	courses = new string[10];

	while (temporary){

		courses[i++]=temporary;
		courseNum++;
		temporary = strtok(NULL, " ");

	}


}

string * instructor::get_courses() {


        return courses;
        }

int instructor::getCourseNum(){
    return courseNum; }


