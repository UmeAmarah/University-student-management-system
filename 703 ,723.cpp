#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>
#include<stdlib.h>
using namespace std;

class date;
class Course;
class Department;
class Faculty;
class Club;
class Assignment;
class Enrollment;
class FCAllocation;
class Grade;
class LResource;
class Attendance;
class Event;
class Project;
class Feedback;
void Menu();
void Admin();
void User();
void Faculties();
void AdminMenu();
void StudentDetail();
void AddStudent();
void NewUser();
void OldUser();
void UserView(int s_id);
int SearchCourseEnroll(int c_id, int s_id);
int searchStudent(int id);
void oldFacuilty();
void FacuiltyOp();
void newfacuilty();
void AddFacuilty();
const int MAX_SIZE = 100;
static int enro = 0;
//              Student calss

class Student {
	int	student_id;
	string name;
	string email;
	string phone_number;


	Course* enrolled_courses;
	Assignment* submitted_assignments;
	Club* joined_clubs;

public:
	friend istream& operator>>(istream& i, Student& s);
	friend ostream& operator<<(ostream& o,const Student& s);
	
	void Details() {
		ifstream read;
		int id;
		int f=searchStudent(student_id);
		id = student_id;
		if (f == 1) {
			read.open("Students info.txt", ios::in);
			if (!(read.is_open())) {
				cout << "\n\t\t\tError in opening file.\n";
			}
			while (!read.eof()) {
				read >> student_id;
				read.ignore();
				getline(read, name);
				read.ignore();
				getline(read, email);
				read.ignore();
				getline(read, phone_number);
				if (student_id == id) {
					system("cls");
					cout << "\n\n\n\t\t\tStudent_id: " << student_id;
					cout << "\n\t\t\tStudent name: " << name;
					cout << "\n\t\t\tStudent email: " << email;
					cout << "\n\t\t\tStudent phone_no: " << phone_number<<endl;
				}
			}
		}
	}
	void submit_assignment(Assignment& a) {

	}
	void join_club(Club& c) {

	}
	// Default construct of Student
	Student():student_id(0), name("Null"), email("Null"), phone_number("Null") {

	} 
	// para construct of Student
	Student(int s_id,string n, string e_mail, string p_no): student_id(s_id), name(n), email(e_mail), phone_number(p_no) {
		
	}
	// Copy construct of Student
	Student(const Student& s) :student_id(s.student_id), name(s.name), email(s.email), phone_number(s.phone_number) {
	}
	int getstudent_id() {
		return student_id;
	}
	string getname() {
		return name;
	}
	string getemail() {
		return email;
	}
	string getphone_no() {
		return phone_number;
	}
	void setstudent_id(int id) {
		student_id=id;
	}
	~Student() {
		delete enrolled_courses;

	}
};

ostream& operator<<(ostream& o,const Student& s) {
	o<<"Enter Student_id\nStudent name\nStudent email\nStudent phone no\nrespectively.\n";
	return o;
}
istream& operator>>(istream& i, Student& s) {
	i >> s.student_id >> s.name >> s.email >> s.phone_number;
	return i;
}


//            Course calss


class Course {
	int	course_id;
	string name;
	int credits;
	string instructor;

	Student* enrolled_students[MAX_SIZE];
	Assignment* assignments[20];

public:
	friend istream& operator>>(istream& i, Course& s);
	friend ostream& operator<<(ostream& o, const Course& s);
	//in file course id and student id only
	int AvaiableCor(int c_id) {
		ifstream  readCor;
		int flag = 0;
		readCor.open("Available Courses.txt", ios::in);
		while((!readCor.eof())&&flag==0){
			readCor >> course_id;
			readCor.ignore();
			getline(readCor, name);
			readCor >> credits;
			readCor.ignore();
			getline(readCor, instructor);
			if (c_id == course_id) {
				flag= 1;
			}
		}
		if (flag == 1) {
			return 1;
		}
		else
			return 0;
	}
	void add_student(Student& s) {
		ofstream write;
		write.open("Student Enroll in Course.txt", ios::app);
		write << endl << course_id<<endl<<s.getstudent_id()<<endl;
	}
	void add_assignment(Assignment& a) {

	}

	Course() :course_id(0), name("Null"), credits(0), instructor("Null") {


	}
	Course(int c_id, string n, int cre, string inst) :course_id(c_id), name(n), credits(cre), instructor(inst) {
	

	}
	Course(const Course& c) :course_id(c.course_id), name(c.name), credits(c.credits), instructor(c.instructor) {


	}
	int getcourse_id() {
		return course_id;
	}
	string getname() {
		return name;
	}
	int getcredits() {
		return credits;
	}
	string getinstructor() {
		return instructor;
	}
	void setcourse_id(int id) {
		course_id = id;
	}
	~Course() {


	}
};
ostream& operator<<(ostream& o, const Course& s) {
	o << "Enter Course_id\nCourse name\nCredits Hours\nInstructor Name\nrespectively.\n";
	return o;
}
istream& operator>>(istream& i, Course& c) {
	i >> c.course_id >> c.name >> c.credits >> c.instructor;
	return i;
}


//            Department calss

class Department{
	int	department_id;
	string name;
	string head_of_department;


	Course* courses_offered;
	Faculty* faculty_members;
public:
	void add_course() {
		char o = '1';
		int size=1;
		int c = 0;
		 // Dynamic Array of courses
		cout << "\n\n\n\t\t\tEnter Courses No that you want to add.\n\t\t\t";
		cin >> size;
		courses_offered = new Course[size];
		while((o == '1') && (c < size)) {
			cout << courses_offered[c];
			cin >> courses_offered[c];
			cout << "\n\t\t\tEnter Department Id: \n\t\t\t";
			cin >> department_id;
			int f = DepartCourseCheck(department_id, courses_offered[c].getcourse_id());
			if (f == 1) {
				system("cls");
				cout << "\n\n\t\t\tThis course is alredy added int that department.\n";
			}
			else if(f==0){
				system("cls");
				cout << "\n\n\n\t\t\tCourse is added successful.\n";
				ofstream write;
				write.open("Depar ID and course Id.txt", ios::app);
				write << endl<< department_id << endl << courses_offered[c].getcourse_id()<<endl;
				write.close();
				write.open("Available Courses.txt", ios::app);
				write <<endl<< courses_offered[c].getcourse_id() << endl << courses_offered[c].getname() << endl << courses_offered[c].getcredits() << endl << courses_offered[c].getinstructor()<<endl;
				write.close();
			}
			c++;
			cout << "\n\t\t\tEnter 1 to continue adding and enter any key to terminate it.\n\t\t\t";
			cin >> o;
		}
	}
	void add_faculty(Faculty& f) {

	}

	Department() :department_id(0), name("Null"), head_of_department("Null") {
 

	}
	Department(int d_id, string n,string hod) :department_id(d_id), name(n), head_of_department(hod) {


	}
	Department(const Department& d) :department_id(d.department_id), name(d.name), head_of_department(d.head_of_department) {


	}
	int DepartCourseCheck(int d_id, int c_id) {
		ifstream read;
		int course_id,flag=0;
		read.open("Depar ID and course Id.txt", ios::in);
		if (!(read.is_open())) {
			cout << "\n\n\t\t\tError in opening file.\n";
		}
		while (read >> department_id>> course_id) {

			cout << department_id<<endl;
			cout << course_id<<endl;
			if ((department_id == d_id)&&(course_id == c_id)) {
				flag = 1;
				break;
			}
		}
		if (flag == 1) {
			return 1;
		}
		else {
			return 0;
		}
	}
	int getdepartment_id() {
		return department_id;
	}
	void setdepartment_id(int id) {
		department_id = id;
	}
	~Department() {

		delete[] courses_offered;

	}
};


//            Faculty calss

class Faculty {
	int	faculty_id;
	string name;
	string email;
	string phone_number;


	Course* courses_taught;
	Student* supervised_students;
public:
	friend istream& operator>>(istream& i, Faculty& s);
	friend ostream& operator<<(ostream& o, const Faculty& s);

	void teach_course(const Course& c) {

	}
	void supervise_project(const Student& s) {

	}
	Faculty() :faculty_id(0), name("Null"), email("Null"), phone_number("Null") {


	}
	Faculty(int f_id, string n, string e_mail, string p_no) :faculty_id(f_id), name(n), email(e_mail), phone_number(p_no) {


	}
	Faculty(const Faculty& f) :faculty_id(f.faculty_id), name(f.name), email(f.email), phone_number(f.phone_number) {


	}
	int SearchFacuilty(int id) {
		int flag = 0;
		ifstream read;
		read.open("Facuilty.txt", ios::in);
		if (!(read.is_open())) {
			cout << "\n\n\t\t\tError in opening file.\n";
		}
		while (!read.eof())
		{
			read >> faculty_id;
			read.ignore();
			getline(read,name);
			read.ignore();
			getline(read, email);
			read.ignore();
			getline(read, phone_number);

			cout << faculty_id << endl;
			if (faculty_id == id)
			{
				flag = 1;
			}
		}
		read.close();
		if (flag == 1)
		{
			return 1;
			system("cls");
			FacuiltyOp();
		}
		else
		{
			return 0;
			
		}
	}
	int getfaculty_id() {
		return faculty_id;
	}
	string getname() {
		return name;
	}
	string getemail() {
		return email;
	}

	string getphone_no() {
		return phone_number;
	}
	void setfaculty_id(int id) {
		faculty_id = id;
	}
	~Faculty() {


	}
};
ostream& operator<<(ostream& o, const Faculty& f) {
	o << "Enter Faculty_id\nFaculty name\nFaculty email\nFaculty phone no\nrespectively.\n";
	return o;
}
istream& operator>>(istream& i, Faculty& f) {
	i >> f.faculty_id >> f.name >> f.email >> f.phone_number;
	return i;
}



//            Club calss

class Club {
	int	club_id;
	string name;
	string description;


	Student members[MAX_SIZE];
	Event* events_organized[30];

public:
	void add_member(Student& s) {

	}
	void organize_event(Event& e) {

	}


	Club() :club_id(0), name("Null"), description("Null") {


	}
	Club(int c_id, string n,string des) :club_id(c_id), name(n), description(des) {


	}
	Club(const Club& c) :club_id(c.club_id), name(c.name), description(c.description) {


	}
	int getclub_id() {
		return club_id;
	}
	void setclub_id(int id) {
		club_id = id;
	}
	~Club() {


	}
};


//            DATE calss



class date {
private:
	int month, day, year;
public:
	date():month(1),year(1900),day(1) {
		

	}
	date(int m, int d, int y) :month(m), year(y), day(d) {

		
	}
	date(const date& d) :month(d.month), year(d.year), day(d.day) {


	}
	int getmonth() {
		return month;
	}
	int getday() {
		return day;
	}
	int getyear() {
		return year;
	}
	void setdate(date& d) {
		while (!(d.month>=1 && d.month <= 12) )
		{
			cout << "enter correct month\n";
			cin >> month;
		}
		month = d.month;
		year = d.year;
		while (!(d.day>=1 && d.day <= 31)) {
			cout << "Enter correct day\n";
			cin >> d.day;
		}
		day = d.day;
	}
	void setyear(int y) {
		year = y;
	}
	void setday(date& d) {
		day = d.day;
	}
	friend ostream& operator<<(ostream& o, const date& d);
	friend istream& operator>>(istream& i, date& d);
	void display() {
		cout <<month<< "/" << day << "/" << year << endl;
	}
	~date() {

	}
};

ostream& operator<<(ostream& o, const date& d) {
	o <<"Enter date in this format  mm/dd/yyyy" << endl;
	return o;
}
istream& operator>>(istream& i, date& d) {
	i >> d.month >> d.day >> d.year;
	return i;
}

//            Assignment calss

class Assignment {
	int	assignment_id;
	int	course_id;
	date due_date;
	string description;

	Course course;
public:
	Assignment() :assignment_id(0), course_id(0),due_date(0,0,0), description("Null"){


	}
	Assignment(int a_id, int c_id,date& d, string des) :assignment_id(a_id), course_id(c_id),due_date(d), description(des) {
	

	}
	Assignment(const Assignment& a) :assignment_id(a.assignment_id), course_id(a.course_id),due_date(a.due_date), description(a.description) {
		

	}
	int getassignment_id() {
		return assignment_id;
	}
	void setassignment_id(int id) {
		assignment_id = id;
	}
	int getcourse_id() {
		return course_id;
	}
	void setcourse_id(int id) {
		course_id = id;
	}
	date& getDue_Date() {
		return due_date;
	}
	void setdue_date(date& d_date) {
		due_date = d_date;
	}


	~Assignment() {
	


	}
};


//            Enrollment calss

class Enrollment {
	int	enrollment_id;
	int student_id;
	int	course_id;
	date enrollment_date;

	Student student;
	Course course;
public:

	Enrollment() :enrollment_id(0),student_id(0), course_id(0), enrollment_date(0,0,0){
	

	}
	Enrollment(int e_id, int s_id, int c_id) :enrollment_id(e_id),student_id(s_id), course_id(c_id){
		cout << "para construct of Enrollment\n";
	}
	Enrollment(const Enrollment& e) :enrollment_id(e.enrollment_id), student_id(e.student_id), course_id(e.course_id), enrollment_date(e.enrollment_date) {
		

	}
	int getenrollment_id() {
		return enrollment_id;
	}
	void setenrollment_id(int id) {
		enrollment_id=id;
	}
	int getstudent_id() {
		return student_id;
	}
	void setstudent_id(int id) {
		student_id = id;
	}
	int getcourse_id() {
		return course_id;
	}
	void setcourse_id(int id) {
		course_id = id;
	}
	date& getenrollment_date() {
		return enrollment_date;
	}
	void setenrollment_date(date& e_date) {
		enrollment_date = e_date;
	}
	void Enroll(int s_id) {
		char o = '1';
		Course c;
		int availCor;
		int c_id=1;
		while (o == '1') {
			cout << "\nEnter Course id: ";
			cin >> c_id;
			availCor = c.AvaiableCor(c_id);
			int flag=SearchCourseEnroll(c_id,s_id);
			if (availCor == 1) {
				if (flag == 1) {
					system("cls");
					cout << "\n\t\t\tYou already enrolled in that course.\n";

				}
				else if (flag == 0) {
					student_id = s_id;
					ofstream write;
					write.open("Enrollment.txt", ios::app);
					if (!(write.is_open())) {
						cout << "\n\t\t\tError in opening file.\n";
					}
					else {
						setenrollment_id(++enro);
						write << endl << enrollment_id << endl << student_id << endl << c_id << endl << __DATE__;
						system("cls");
						cout << "\n\n\n\t\t\tENROLLMENT IN COURSE IS SUCCESSFUL.\n";
					}
				}
			}
			else {
				system("cls");
				cout << "\n\n\n\t\t\tCourse is not available yet.reEnter course\n\t\t\t";
				cin >> c_id;
			}
			cout<<"\n\t\t\tClick 1 to continue enrollment. And click any key to stop it\n\t\t\t";
			cin >> o;
		}

		
	}
	~Enrollment() {

	}
};
int SearchCourseEnroll(int c_id, int s_id) {
	Course c;
	c.setcourse_id(c_id);
	fstream readE;
	string t;
	int e_id,cor_id,std_id,flag=0;
	
	readE.open("Enrollment.txt",ios::in);
	readE.ignore();
	if (!(readE.is_open())) {
		cout << "\n\t\t\tError in opening file.\n";
	}
	while ((!readE.eof()) && flag == 0)
	{
		readE >> e_id;
		readE.ignore();
		readE >> std_id;
		readE.ignore();
		readE >> cor_id;
		readE.ignore();
		getline(readE , t);
		if (cor_id == c_id && std_id == s_id) {
			flag= 1;
		}
	}
	readE.close();
	if (flag == 1) {
		return 1;
	}
	else
		return 0;

}


//            FacultyCourseAllocation calss

class FCAllocation {
	int	allocation_id;
	int faculty_id;
	int	course_id;
	string semester;

	Faculty faculty;
	Course course;
public:
	FCAllocation() :allocation_id(0), faculty_id(0), course_id(0), semester("NULL") {


	}
	FCAllocation(int a_id, int f_id, int c_id,string s) :allocation_id(a_id), faculty_id(f_id), course_id(c_id), semester(s){


	}
	FCAllocation(const FCAllocation& a) :allocation_id(a.allocation_id), faculty_id(a.faculty_id), course_id(a.course_id), semester(a.semester) {


	}
	int getallocation_id() {
		return allocation_id;
	}
	void setallocation_id(int id) {
		allocation_id = id;
	}
	int getfaculty_id() {
		return faculty_id;
	}
	void setfaculty_id(int id) {
		faculty_id = id;
	}
	int getcourse_id() {
		return course_id;
	}
	void setcourse_id(int id) {
		course_id = id;
	}
	~FCAllocation() {


	}
};


//            Grade calss

class Grade {
	int	grade_id;
	int student_id;
	int	course_id;
	string grade;


	Student student;
	Course course;
public:
	Grade() :grade_id(0), student_id(0), course_id(0), grade("NULL") {


	}
	Grade(int g_id, int s_id, int c_id, string g) :grade_id(g_id), student_id(s_id), course_id(c_id), grade(g) {


	}
	Grade(const Grade& g) :grade_id(g.grade_id), student_id(g.student_id), course_id(g.course_id), grade(g.grade) {


	}
	int getgrade_id() {
		return grade_id;
	}
	void setgrade_id(int id) {
		grade_id = id;
	}
	int getstudent_id() {
		return student_id;
	}
	void setstudent_id(int id) {
		student_id = id;
	}
	int getcourse_id() {
		return course_id;
	}
	void setcourse_id(int id) {
		course_id = id;
	}
	~Grade() {


	}
};


//            LibraryResource calss

class LResource {
	int	resource_id;
	string title;
	string author;
	bool availability;
public:
	LResource() :resource_id(0), title("Null"), author("NULL"), availability(false){


	}
	LResource(int l_id, string t, string auth, bool avail) :resource_id(l_id), title(t), author(auth), availability(avail) {


	}
	LResource(const LResource& l) :resource_id(l.resource_id), title(l.title), author(l.author), availability(l.availability) {


	}
	int getresource_id() {
		return resource_id;
	}
	void setresource_id(int id) {
		resource_id = id;
	}
	string gettitle() {
		return title;
	}
	void settitle(string t) {
		title = t;
	}
	~LResource() {

	}
};


//            Attendance calss

class Attendance {
	int	attendance_id;
	int student_id;
	int	session_id;
	string attendance_status;


	Student student;
public:
	Attendance() :attendance_id(0), student_id(0), session_id(0), attendance_status("NULL") {


	}
	Attendance(int a_id, int s_id, int sess_id, string attend) :attendance_id(a_id), student_id(s_id), session_id(sess_id), attendance_status(attend) {


	}
	Attendance(const Attendance& a) :attendance_id(a.attendance_id), student_id(a.student_id), session_id(a.session_id), attendance_status(a.attendance_status) {

	}
	int getattendance_id() {
		return attendance_id;
	}
	void setattendance_id(int id) {
		attendance_id = id;
	}
	int getstudent_id() {
		return student_id;
	}
	void setstudent_id(int id) {
		student_id = id;
	}
	int getsession_id() {
		return session_id;
	}
	void setsession_id(int id) {
		session_id = id;
	}
	~Attendance() {


	}
};


//            Event calss

class Event {
	int	event_id;
	string title;
    string description;
	date Date;
	string venue;
public:
	Event() :event_id(0), title("NULL"), description("NULL"),Date(0,0,0), venue("NULL") {

	}
	Event(int e_id, string t, string des,date& d, string ven) :event_id(e_id), title(t), description(des),Date(d), venue(ven) {

	}
	Event(const Event& e) :event_id(e.event_id), title(e.title), description(e.description), venue(e.venue), Date(e.Date){

	}
	int getevent_id() {
		return event_id;
	}
	void setevent_id(int id) {
		event_id = id;
	}

	string gettitle() {
		return title;
	}
	void settitle(string t) {
		title = t;
	}

	string getvenue() {
		return venue;
	}
	void setvenue(string v) {
		venue = v;
	}
	~Event() {


	}
};


//            Project calss

class Project {
	int	project_id;
	string title;
	string description;


	Student students[MAX_SIZE];
	Faculty faculty_supervisor;
public:
	Project() :project_id(0), title("NULL"), description("NULL"){

	}
	Project(int p_id, string t, string des) :project_id(p_id), title(t), description(des){

	}
	Project(const Project& p) :project_id(p.project_id), title(p.title), description(p.description){

	}
	int getproject_id() {
		return project_id;
	}
	void setproject_id(int id) {
		project_id = id;
	}

	string gettitle() {
		return title;
	}
	void settitle(string t) {
		title = t;
	}
	~Project() {


	}
};


//            Feedback calss

class Feedback {
	int	feedback_id;
	string content;
	int rating;


	Student student;
	Course course;
public:
	Feedback() :feedback_id(0), content("NULL"), rating(0) {

	}
	Feedback(int f_id, string con, int ra) :feedback_id(f_id), content(con), rating(ra) {

	}
	Feedback(const Feedback& f) :feedback_id(f.feedback_id), content(f.content), rating(f.rating) {

	}
	void savefeedback() {
		setfeedback_id();
		cout << "\n\t\t\tEnter your feedback.\n\t\t\t";
		cin.ignore();
		getline(cin, content);
		ofstream write;
		write.open("Feedback.txt", ios::app);

		if (!write.is_open())
		{
			cout << "Error in opening file.";
		}
		write << endl << feedback_id << endl << content<<endl<<4;

		write.close();
	}
	int getfeedback_id() {
		return feedback_id;
	}
	void setfeedback_id() {
		cout << "\n\n\t\t\tEnter feedback id.\n\t\t\t";
		cin >> feedback_id;
	}

	string getcontent() {
		return content;
	}
	void setcontent(string c) {
		content = c;
	}
	~Feedback() {


	}
};

//            InterFace

void Menu() {
	char o;
	cout << "\n\n\n\t\t\t*********************************************************\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t1. Admin\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t2. Faculty\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t3. User\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t*********************************************************\n";
	cout << "\n\t\t\t\t*****************************************\n";
	cout << "\t\t\t\t|\t\tEnter Option: "; cin >> o;
	cout << "\t\t\t\t|\t\t\t\t\t|";
	cout << "\n\t\t\t\t*****************************************\n\n\n";
	while (o != '1' && o != '2'&& o!='3')
	{
		cout << "\t\t\t\tEnter correct option from above: "; cin >> o;
	}
	if (o == '1') {
		system("cls");
		Admin();
	}
	else if(o=='2'){
		system("cls");
		Faculties();
	}
	else {
		system("cls");
		User();
	}
}

//            ADMIN INTERFACE

void Admin() {
	string password, pass;
	string userId, U_id;
	int flag = 0;
	cout << "\n\n\n\t\t\t Enter Your Correct UserName and Password with out space \n";
	cout << "\n\t\t\t\t*****************************************\n";
	cout << "\t\t\t\t|\t\t\t\t\t|\n";
	cout << "\t\t\t\t|\tUserName: "; cin >> U_id;
	cout << "\t\t\t\t|\tPassword: "; cin >> pass;
	cout << "\t\t\t\t|\t\t\t\t\t|";
	cout << "\n\t\t\t\t*****************************************\n\n";

	ifstream read;
	read.open("Admin id.txt", ios::in);
	while (read >> userId >> password)
	{
		if (userId == U_id && password == pass)
		{
			flag = 1;
		}
	}
	read.close();
	if (flag == 1)
	{
		system("cls");
		AdminMenu();
	}
	else
	{
		char o;
		cout << endl << "\t\tYour provided UserName or Password is incorrect renter your UserName and Password.";
		cout << endl << "\t\t\t1. BACK\n";
		cout << "\t\t\tOR\n\t\t\tClick any key from keyboard to ignore this\n";
		cout << "\t\t\t";
		cin >> o;
		if (o != '1') {
			system("cls");
			Admin();
		}
		else {
			system("cls");
			Menu();
		}
	}
}


void AdminMenu() {
	char o;
	cout << "\n\n\n\t\t\t*********************************************************\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\tWELLCOME TO ADMIN INTERFACE\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t*********************************************************\n";
	cout << "\n\t\t\t*********************************************************\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t1. Available Courses\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t2. Department\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t3. Add Courses in Department\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t4. Student Enrollment\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t5. Faculty Course Allocation\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t6. See Feedback\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t7. Menu\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t*********************************************************\n";
	cout << "\n\t\t\t\t*****************************************\n";
	cout << "\t\t\t\t|\t\tEnter Option: "; cin >> o;
	cout << "\t\t\t\t|\t\t\t\t\t|";
	cout << "\n\t\t\t\t*****************************************\n\n\n";
	while (o != '1' && o != '2' && o != '3'&& o!='4' && o != '5' && o != '6' && o != '7')
	{
		cout << "\t\t\t\tEnter correct option in digit from above: "; cin >> o;
	}
	ifstream read;
	char c;
	switch (o) {
	 case '1': {
		 system("cls");
		read.open("Available Courses.txt", ios::in);
		if (!read.is_open())
		{
			cout << "Error in opening file.";
		}
		while (read.get(c))
		{
			cout << read.rdbuf();
		}
		read.close();
		break;
	 }
	 case '2': {
		 system("cls");
		read.open("Department.txt", ios::in);
		if (!read.is_open())
		{
			cout << "Error in opening file.";
		}
		while (read.get(c))
		{
			cout << read.rdbuf();
		}
		read.close();
		break;
	 }
	 case '3': {
		 system("cls");
		 Department d;
		 d.add_course();
		 break;
	 }
	 case '4': {
		 system("cls");
		read.open("Student Enrollment.txt", ios::in);
		if (!read.is_open())
		{
			cout << "Error in opening file.";
		}
		while (read.get(c))
		{
			cout << read.rdbuf();
		}
		read.close();
		break;
	 }
	 case '5': {
		 system("cls");
		read.open("Faculty Course Allocation.txt");
		if (!read.is_open())
		{
			cout << "Error in opening file.";
		}
		while (read.get(c))
		{
			cout << read.rdbuf();
		}
		read.close();
		break;
	 }
	 case '6': {
		 system("cls");
		 read.open("Feedback.txt");
		 if (!read.is_open())
		 {
			 cout << "Error in opening file.";
		 }
		 while (read.get(c))
		 {
			 cout << read.rdbuf();
		 }
		 read.close();
		 break;
	 }
	 case '7': {
		 system("cls");
		 Menu();
		 break;
	 }
	}
	cout << "\n\n\n\t\t\tClick 1.Back\n";
	cout << "\n\t\t\tClick any key to bo to Menu\n\n\t\t\t";
	cin >> o;
	if (o != '1') {
		system("cls");
		Menu();
	}
	else {
		system("cls");
		AdminMenu();
	}
}

//           USER INTERFACE

void User() {
	char o;
	cout << "\n\n\t\t\t*********************************************************\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t1. New student\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t2. Old student\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t3. Menu\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t*********************************************************\n";
	cout << "\n\t\t\t\t*****************************************\n";
	cout << "\t\t\t\t|\tEnter Option: "; cin >> o;
	cout << "\t\t\t\t|\t\t\t\t\t|";
	cout << "\n\t\t\t\t*****************************************\n\n\n";
	while (o != '1' && o != '2'&&o != '3') {
		cout << "\t\t\t\tEnter correct option from above: "; cin >> o;
	}
	if (o == '1') {
		system("cls");
		NewUser();
	}
	else if(o == '2'){
		system("cls");
		OldUser();
	}
	else {
		system("cls");
		Menu();
	}
}
void NewUser() {
	char o; 
	cout << "\n\n\n\t\t\t*************************************************************************\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t\t\t |\t|\n";
	cout << "\t\t\t|\t|First Register yourself and go back select old Students|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t\t\t |\t|\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t*************************************************************************\n\n";
	AddStudent();
	system("cls");
	User();
}

int searchStudent(int id) {
	bool flag=0;
	int s_id;
	ifstream read;
	read.open("Students ids.txt", ios::in);
	if (!read.is_open()) {
		cout << "Error in opening file\n";
	}
	else {
		while (read >> s_id)
		{
			if (s_id == id)
			{
				return 1;
			}
		}
		read.close();
	}

	return 0;

}
void OldUser() {
	int std_id, s_id;
	char o;
	cout << "\n\n\n\t\t\t\tEnter Your Student_id without space \n";
	cout << "\n\t\t\t\t*****************************************\n";
	cout << "\t\t\t\t|\t\t\t\t\t|\n";
	cout << "\t\t\t\t|\tStudent_id: "; cin >> s_id;
	cout << "\t\t\t\t|\t\t\t\t\t|";
	cout << "\n\t\t\t\t*****************************************\n\n";
	cout << "\n\t\t\t1 .back\n\t\t\t";
	cout << "\n\t\t\tClick any key to skip this option\n\t\t\t";
	cin >> o;
	if (o != '1') {
		std_id = searchStudent(s_id);
		if (std_id == 1) {
			system("cls");
			UserView(s_id);
		}
		else {
			system("cls");
			cout << "\n\n\n\t\t\t\t\tEnter Correct Student_id\n\n";
			OldUser();
		}
	}
	else {
		system("cls");
		User();
	}
}
void UserView(int s_id) {
	char o;
	cout << "\n\n\n\t\t\t*********************************************************\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\tWELLCOME TO USER INTERFACE\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t*********************************************************\n";
	cout << "\n\t\t\t*********************************************************\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t1. Student details\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t2. Enroll_in_course\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t3. Submitt Assignment\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t4. Join Club\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t5. See Library Resource\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t6. Project/Research\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t7. Give Feedback\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t8. Menu\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t*********************************************************\n";
	cout << "\n\t\t\t\t*****************************************\n";
	cout << "\t\t\t\t|\t\tEnter Option: "; cin >> o;
	cout << "\t\t\t\t|\t\t\t\t\t|";
	cout << "\n\t\t\t\t*****************************************\n\n\n";
	while (o != '1' && o != '2' && o != '3' && o != '4'&&o != '5' && o != '6' && o != '7' && o != '8' && o != '9')
	{
		cout << "\t\t\t\tEnter correct option in digit from above: "; cin >> o;
	}
	fstream read;
	char c;
	switch (o) {
	case '1': {
		system("cls");
		int id;
		Student s;
		s.setstudent_id(s_id);
		s.Details();
		StudentDetail();
		break;
	}
	case '2': {
		system("cls");
		ifstream read;
		char c;
		cout << "\n\n\t\t\tAvailable Courses:\n";
		read.open("Available Courses.txt");
		if (!(read.is_open())) {
			cout << "Error in opening file\n";
		}
		while (read.get(c)) {
			cout << read.rdbuf();
		}
		read.close();

		Enrollment e;
		e.Enroll(s_id);
		
		break;
	}
	case '3': {
		system("cls");
		Assignment a;
		//a.submitt();
		read.open("Student Enrollment.txt", ios::in);
		if (!read.is_open())
		{
			cout << "Error in opening file.";
		}
		while (read.get(c))
		{
			cout << read.rdbuf();
		}
		read.close();
	}
	case '4': {
		system("cls");
		read.open("Faculty Course Allocation.txt");
		if (!read.is_open())
		{
			cout << "Error in opening file.";
		}
		while (read.get(c))
		{
			cout << read.rdbuf();
		}
		read.close();
	}
	
	case '5': {
		system("cls");
		read.open("Faculty Course Allocation.txt");
		if (!read.is_open())
		{
			cout << "Error in opening file.";
		}
		while (read.get(c))
		{
			cout << read.rdbuf();
		}
		read.close();
	}
	case '6': {
		system("cls");
		read.open("Faculty Course Allocation.txt");
		if (!read.is_open())
		{
			cout << "Error in opening file.";
		}
		while (read.get(c))
		{
			cout << read.rdbuf();
		}
		read.close();
		break;
	}
	case '7': {
		system("cls");
		Feedback f;
		f.savefeedback();
		cout << "\n\n\t\t\tYour feedback is save successfuly.\n";
		break;
	}
	case '8': {
		system("cls");
		Menu();
		break;
	}
	}
	cout << "\n\n\n\t\t\tClick any key to go to menu and 0 to terminate progrm.";
	cin >> o;
	if (o != '0') {
		system("cls");
		Menu();
	}
}

void StudentDetail() {
	
}

//      Facuilty interface

void Faculties(){
	char o;
	cout << "\n\n\t\t\t*********************************************************\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t1. New Facuilty\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t2. Old Facuilty\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t3. Menu\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t*********************************************************\n";
	cout << "\n\t\t\t\t*****************************************\n";
	cout << "\t\t\t\t|\tEnter Option: "; cin >> o;
	cout << "\t\t\t\t|\t\t\t\t\t|";
	cout << "\n\t\t\t\t*****************************************\n\n\n";
	while (o != '1' && o != '2' && o != '3') {
		cout << "\t\t\t\tEnter correct option from above: "; cin >> o;
	}
	if (o == '1') {
		system("cls");
		newfacuilty();
	}
	else if (o == '2') {
		system("cls");
		oldFacuilty();
	}
	else {
		system("cls");
		Menu();
	}
}
void newfacuilty() {
	char o;
	cout << "\n\n\n\t\t\t*************************************************************************\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t\t\t |\t|\n";
	cout << "\t\t\t|\t|First Register yourself and go back select old Faculty|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t\t\t |\t|\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t*************************************************************************\n\n";
	AddFacuilty();
	system("cls");
	Faculties();
}

void oldFacuilty(){
	Faculty f;
	int f_id;
	cout << "\n\n\n\t\t\t Enter Your Correct Facuilty_id\n";
	cout << "\n\t\t\t\t*****************************************\n";
	cout << "\t\t\t\t|\t\t\t\t\t|\n";
	cout << "\t\t\t\t|\tFacuilty_id: "; cin >> f_id;
	cout << "\t\t\t\t|\t\t\t\t\t|";
	cout << "\n\t\t\t\t*****************************************\n\n";
	int flag=f.SearchFacuilty(f_id);
	if (flag == 1) {
		system("cls");
		FacuiltyOp();
	}
	else {
		char o;
		cout << endl << "\t\tYour provided id is incorrect plese enter correct id.\n\t\t\t";
		cout << endl << "\t\t\t1. BACK\n";
		cout << "\t\t\tOR\n\t\t\tClick any key from keyboard to ignore this\n\t\t\t";
		cin >> o;
		if (o != '1') {
			system("cls");
			oldFacuilty();
		}
		else {
			system("cls");
			Menu();
		}
	}
}
void FacuiltyOp(){
	char o;
	cout << "\n\n\n\t\t\t*********************************************************\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\tWELLCOME TO Facuilty INTERFACE\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t*********************************************************\n";
	cout << "\n\t\t\t*********************************************************\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t1. See Allocated courses\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t2. See Submitted Assignments\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t3. Project/Research\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t4. See Feedback\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t5. Menu\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t|\t\t\t\t\t|\t|\n";
	cout << "\t\t\t|\t-\t-\t-\t-\t-\t-\t|\n";
	cout << "\t\t\t*********************************************************\n";
	cout << "\n\t\t\t\t*****************************************\n";
	cout << "\t\t\t\t|\t\tEnter Option: "; cin >> o;
	cout << "\t\t\t\t|\t\t\t\t\t|";
	cout << "\n\t\t\t\t*****************************************\n\n\n";
	while (o != '1' && o != '2' && o != '3' && o != '4' && o != '5')
	{
		cout << "\t\t\t\tEnter correct option in digit from above: "; cin >> o;
	}
	
}

void AddFacuilty() {
	int o = 1;
	int size;
	int c = 0;
	Faculty* f;   // Dynamic Array of Student
	cout << "\n\n\n\t\t\tEnter Facuilty No.\n\t\t\t";
	cin >> size;
	f = new Faculty[size];
	while (o == 1 && c < size) {
		cout << f[c];
		cin >> f[c];
		int r= f[c].SearchFacuilty(f[c].getfaculty_id());
		cout << "\n\n\n"<<r<<endl;
		if (r == 1) {
			system("cls");
			cout << "\n\n\t\t\tYou are already resistered.\n";
		}
		else {
			system("cls");
			cout << "\n\n\n\t\t\tRegistration is successful.\n";
			ofstream write;
			write.open("Facuilty.txt", ios::app);
			write << endl << f[c].getfaculty_id() << endl << f[c].getname() << endl << f[c].getemail() << endl << f[c].getphone_no();
			write.close();
		}
		cout << "\n\t\t\t\Enter 0 to continue or click 1 to Add new faculty.\n\t\t\t";
		cin >> o;
		c++;
	}
}
void AddStudent() {
	int o=1;
	int size;
	int c = 0;
	Student* s;   // Dynamic Array of Student
	cout << "\n\n\n\t\t\tEnter student No.\n\t\t\t";
	cin >> size;
	s = new Student[size];
	while (o == 1 && c<size) {
		cout <<s[c];
		cin >> s[c];
		int r= searchStudent(s[c].getstudent_id());
		if (r == 1) {
			system("cls");
			cout << "\n\n\t\t\tYou are already resistered.\n";
		}
		else {
			system("cls");
			cout << "\n\n\n\t\t\tRegistration is successful.\n";
			ofstream write;
			write.open("Students info.txt",ios::app);
			write << endl<< s[c].getstudent_id()<<endl<< s[c].getname() << endl << s[c].getemail() << endl << s[c].getphone_no();
			write.close();
			write.open("Students ids.txt", ios::app);
			write << endl << s[c].getstudent_id();
			write.close();
		}
		cout << "\n\t\t\t\Enter 0 to continue or click 1 to Add new student.\n\t\t\t";
		cin >> o;
		c++;
	}
}

int main(){

	Menu();
	
	return 0;

}
