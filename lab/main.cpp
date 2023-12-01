#include <iostream>
#include<string>
#include<fstream>
using namespace std;

/*
teacher.txt / student.txt
name email obj id
*/

/*
date_sheet
class obj d m y xx:xx xx:xx
*/

/*
ans
id ans
*/

/*
paper
question marks ans
*/

/*
result
obj id marks
*/

/*
BBoard
name id marks
*/

//判断是否加换行
bool addteacher = 0;
bool addstudent = 0;
bool addsheet = 0;

bool addres = 0;

bool addans1 = 0;
bool addans2 = 0;
bool addans3 = 0;
bool addans4 = 0;
bool addans5 = 0;

bool addpaper1 = 0;
bool addpaper2 = 0;
bool addpaper3 = 0;
bool addpaper4 = 0;
bool addpaper5 = 0;


void menu();

struct Borad{
	string name;
	int score;
};

void quick_sort(Borad* a[], int l, int r)
{
    if (l < r)
    {
        int i,j,x;

        i = l;
        j = r;
        x = a[i]->score;
		string name = a[i]->name;
        while (i < j)
        {
            while(i < j && a[j]->score > x)
                j--; 
            if(i < j){
				a[i]->name = a[j]->name;
				a[i]->score = a[j]->score;
				i++;
			}
            while(i < j && a[i]->score < x)
                i++; 
            if(i < j){
				a[j]->name = a[i]->name;
				a[j]->score = a[j]->score;
				j--;
			}
        }
        a[i]->score = x;
		a[i]->name = name;
        quick_sort(a, l, i-1); 
        quick_sort(a, i+1, r); 
    }
}


//const Global Variables
#include"include/constant.h"
//Classes
//Abstract Class
class first {
	public:
	//pure virtual Function
	virtual void log()=0;	
};

class auth{
protected:
	string username;
	string pass;
	int user,passw;


public:
	void log(){
		cout << "Enter Username  : ";
		cin >> username;
		cout << "Enter Password : ";
		cin >> pass;
	}

	void log1(){
		cout << "Enter Username  : ";
		cin >> user;
		cout << "Enter Password : ";
		cin >> passw;
	}
};



class check {
private:
	string student_name;
	string student_email;
	string student_class;
	int student_rollNO;

	string teacher_name;
	string teacher_email;
	string teacher_obj;
	int teacher_rollNO;

	bool isfound=0;

	string obj;
	int id;
	int mark;
	Borad* bb[100];
	int nums;

	int minimum_score;
	int average_score;
	int maximum_score;

public:
	Borad* get_mini(string obj){
		fstream fp;
		fp.open("result.txt");
		Borad *bmi[100];
		for(int i = 0; i < 100; i++){
			bmi[i] = new Borad;
			bmi[i]->score = 0;
		}
		nums = 0;
		while(!fp.eof()){
			fp >> obj >> id >> mark;
			string name = get_name(id);
			bmi[nums]->name = name;
			bmi[nums]->score = mark;
			nums++;
		}
		quick_sort(bmi, 0, nums - 1);
		return bmi[0];
	}

	Borad* get_max(string getobj){
		fstream fp;
		fp.open("result.txt");
		Borad *bma[100];
		for(int i = 0; i < 100; i++){
			bma[i] = new Borad;
			bma[i]->score = 0;
		}
		nums = 0;
		while(!fp.eof()){
			fp >> obj >> id >> mark;
			if(getobj == obj){
				string name = get_name(id);
				bma[nums]->name = name;
				bma[nums]->score = mark;
				nums++;
			}
		}
		quick_sort(bma, 0, nums - 1);
		return bma[nums-1];
	}

	int get_avr(string getobj){
		fstream fp;
		fp.open("result.txt");
		nums = 0;
		int ans = 0;
		int people = 0;
		while(!fp.eof()){
			fp >> obj >> id >> mark;
			if(getobj == obj){
				ans += mark;
				people++;
			}
		}
		return (ans/people);
	}

	bool check_class(string abc) {
		fstream file;
		file.open("bin/student.txt", ios:: in );
		if (!file) {
			cout << "Something went wrong Try again...";
		}
		while (!file.eof()) {
			file >> student_name >> student_email >> student_class >> student_rollNO;
				if (abc == student_class) {
					isfound=1;
					break;
				}
		}
		return isfound;
	}

	bool check_student(int roll,int pass){
		fstream file;
		file.open("bin/student.txt", ios:: in );
		if (!file) {
			cout << "Something went wrong Try again...";
		}
		while (!file.eof()) {
			file >> student_name >> student_email >> student_class >> student_rollNO;
			if (roll == student_rollNO && pass ==student_rollNO) {
				isfound = 1;
				break;
			}
		}
		return isfound;
	}

	bool check_teacher(int roll,int pass){
		fstream file;
		file.open("bin/teacher.txt", ios:: in );
		if (!file) {
			cout << "Something went wrong Try again...";
		}
		while (!file.eof()) {
			file >> teacher_name >> teacher_email >> teacher_obj >> teacher_rollNO;
				if (roll == teacher_rollNO && pass == teacher_rollNO) {
					isfound = 1;
					break;
				}
		}
		return isfound;
	}

	string check_subject(int code){
		string sub;
		fstream file;
		file.open("bin/teacher.txt", ios:: in );
		if (!file) {
			cout << "Something went wrong Try again...";
		}
		while (!file.eof()) {
			file >> teacher_name >> teacher_email >> teacher_obj >> teacher_rollNO;
			if (code == teacher_rollNO ) {
				sub = teacher_obj;
				break;
			}
		}
		return sub;
	}

	string get_name(int str){
		fstream file;
		file.open("bin/student.txt", ios:: in );
		if (!file) {
			cout << "Something went wrong Try again...";
		}
		while (!file.eof()) {
			file >> student_name >> student_email >> student_class >> student_rollNO;
			if (str == student_rollNO) {
				return student_name;
			}
		}
		return "";
	}

	int check_name(string name){
		for(int i = 0; i< nums; i++){
			if(bb[i]->name == name)
				return i;
		}
		return -1;
	}

	void get_Board(){
		ofstream bo;
		fstream res;
		res.open("result.txt");
		for(int i = 0; i < 100; i++){
			bb[i] = new Borad;
			bb[i]->score = 0;
		}
		nums = 0;
		while(!res.eof()){
			res >> obj >> id >> mark;
			string name = get_name(id);
			int index = check_name(name);
			if(index == -1){
				bb[nums]->name = name;
				bb[nums]->score = mark;
				nums += 1;
			}
			else{
				bb[index] += mark;
			}
		}
		quick_sort(bb, 0, nums-1);
		for(int i = 0; i < nums; i++){
			bo << bb[i]->name<< " "<< bb[i]->score <<endl;;  
		}
		res.close();
		bo.close();
	}
};


class paper {
private: 
	int each_marks;
	int total_marks=0;
	int total_qes;
	char question[555];
	int time_allowed;
	char ans[999];

public: 
	void make_paper() {
		cout << "Make Paper \n";
		cout << "Select Subject : "<<endl;
		for(int i = 0; i <= 4; i++){
				cout<<"Press "<< i+1 <<" For "<< subject[i] <<endl;
		}
		cout<<"==> ";
		int ch;
		cin>>ch;

		
		if (ch>0 && ch<7){
			cout << "Enter total number of Questions : ";
			cin >> total_qes;
			cout << "Total Time Allowed(in minutes) : ";
			cin >> time_allowed;
			cout << "Enter Question : \n";
			
			ofstream paper;
			paper.open(file_of_papers[ch-1]);
			if (!paper) {
				cout << "Something went wrong Try again...";
			}
			// paper << subject[ch-1] << " " << time_allowed << " " << endl;

			for (int i = 0; i < total_qes; i++) {
				cout << "Q" << i+1 << " : ";
				cin.ignore();
				cin.getline(question, 256);
				cout<<"Enter marks for this Question : ";
				cin >> each_marks;
				cout << "Enter answer for this Question: ";
				cin.ignore();
				cin.getline(ans, 256);
				if(ch == 1){
					if(addpaper1 == 0){
						paper << question << endl;
						paper << each_marks<< endl;
						paper << ans;
						addpaper1 = 1;
					}
					else{
						paper << endl << question << endl;
						paper << each_marks<< endl;
						paper << ans;
					}
				}
				else if(ch == 2){
					if(addpaper2 == 0){
						paper << question << endl;
						paper << each_marks<< endl;
						paper << ans;
						addpaper2 = 1;
					}
					else{
						paper << endl << question << endl;
						paper << each_marks<< endl;
						paper << ans;
					}
				}
				else if(ch == 3){
					if(addpaper3 == 0){
						paper << question << endl;
						paper << each_marks<< endl;
						paper << ans;
						addpaper3 = 1;
					}
					else{
						paper << endl << question << endl;
						paper << each_marks<< endl;
						paper << ans;
					}
				}
				else if(ch == 4){
					if(addpaper4 == 0){
						paper << question << endl;
						paper << each_marks<< endl;
						paper << ans;
						addpaper4 = 1;
					}
					else{
						paper << endl << question << endl;
						paper << each_marks<< endl;
						paper << ans;
					}
				}
				else if(ch == 5){
					if(addpaper5 == 0){
						paper << question << endl;
						paper << each_marks<< endl;
						paper << ans;
						addpaper5 = 1;
					}
					else{
						paper << endl << question << endl;
						paper << each_marks<< endl;
						paper << ans;
					}
				}
				
				total_marks=total_marks + each_marks;
			}
			cout<<"Total marks : "<< total_marks;
			paper.close();
		}
		else{
			cout<<"class Not found";
		}
	}
};


class date_sheet {
	protected:
		string classx;
		string s;
		int d,
		m,
		y;
		int starting_time, ending_time;
	public:
	//For Date_sheet
		void view_datesheet() {
			ifstream file;			
			file.open("bin/date_sheet.txt");

			if (!file) {
				cout << "File Not Found ";
			}
			cout<<"\n\t\t\t\t------DateSheet-----\n\n";
			while (!file.eof()) {
				file >> classx>> s >> d >> m >> y >> starting_time >> ending_time;
				cout<<"class: "<< classx
					<<"Subject : "<< s
					<<"\tDate : "<< d
					<<"-"<< m
					<<"-"<< y
					<<"\t\tStarting Time : "<< starting_time
					<<" \t\tEnding Time : "<< ending_time <<endl;
			}
			file.close();
		}
};


class admin: public first, public check, public auth, public date_sheet {
private: 
	//admin credentials: 
	const string admin_username="admin";
	const string admin_password="123";

	//student
	string student_name;
	string student_email;
	string student_class;
	int student_rollNO;


	//teacher
	string teacher_name;
	string teacher_email;
	int teach_Code;

	int choice;
	bool isFound = 0;
	string Class;
	int ret=0;

public: 
		
	void make_datesheet() {	
		do{
			system("cls");
			cout << "\t\t\t----------Welcome admin----------- \n\n";
			cout<<"\t\tMake Date sheet \n";
			cout << "Enter the class Name :(classx)";
			cin >> Class;
			ofstream date_sheet;
			date_sheet.open("bin/date_sheet.txt");
			if (!date_sheet) {
				cout << "File Not Found or permission denied.";
			}
			for (int i = 0; i < 5; i++) {
				cout << "For " << subject[i] << " : " << endl;
				cout << "Enter Date (DD-MM-YYYY) :\n";
				cout << "Enter Date : ";
				cin >> d;
				cout << "Enter Month: ";
				cin >> m;
				cout << "Enter Year: ";
				cin >> y;
				cout << "Enter Time\n";
				cout << "Enter Starting time : ";
				cin >> starting_time;
				cout << "Enter Ending Time : ";
				cin >> ending_time;

				if(!addsheet){
					date_sheet << Class << " "
						   	   << subject[i] << " " 
						       << d << " " 
						       << m << " " 
						       << y << " " 
						       << starting_time << " " 
						       << ending_time<<" ";
					addsheet = 1;
				}
				else{
					date_sheet << endl
							   << Class << " "
						   	   << subject[i] << " " 
						       << d << " " 
						       << m << " " 
						       << y << " " 
						       << starting_time << " " 
						       << ending_time<<" ";
				}
			}
			cout << "Enter 1 to add another date_sheet else back";
			cin>>ret;
		}while(ret == 1);
	}

		
	void add_student() {
		do{	
			cout<<"\t\tAdd Students \n";
			cout << "Enter Student Name: ";
			cin >> student_name;
			cout << "Enter student email: ";
			cin >> student_email;
			cout << "Enter student class: ";
			cin >> student_class;
			cout << "Enter student Roll No.: ";
			cin >> student_rollNO;

			ofstream Add_student;
			Add_student.open("bin/student.txt", ios::app);
			if (!Add_student) {
				cout << "File Not Found or permission denied.";
			} 
			else {
				if(!addstudent){
					Add_student << student_name << " " 
								<< student_email << " " 
								<< student_class << " " 
								<< student_rollNO << " ";
								addstudent = 1;
				}
				else
					Add_student << endl
								<< student_name << " " 
								<< student_email << " " 
								<< student_class << " " 
								<< student_rollNO << " ";
			}

			Add_student.close();

			cout << "Enter 1 to add another student else back";
			cin >> ret;
		}while(ret == 1);
	}

	void add_teacher(){
		do{	
			system("cls");
			cout << "Enter Teacher Name: ";
			cin >> teacher_name;
			cout << "Enter Teacher email: ";
			cin >> teacher_email;
			cout << "Enter Teacher Subect: \n";
			
			for(int i = 0; i < 5; i++){
				cout<< "Press " << i <<" For " << subject[i] <<endl;
			}

			int ch;
			cin >> ch;
						
			cout << "Enter Teacher Code : ";
			cin >> teach_Code;
			
			ofstream teacher;
			teacher.open("bin/teacher.txt", ios::app);
			if (!teacher) {
				cout << "File Not Found Something went wrong Try again.";
			} 
			else {
				if(!addteacher){
					teacher << teacher_name << " " 
							<< teacher_email << " " 
							<< subject[ch] << " " 
							<< teach_Code << " ";
					addteacher = 1;
				}
				else{
					teacher << endl
							<< teacher_name << " " 
							<< teacher_email << " " 
							<< subject[ch] << " " 
							<< teach_Code << " ";
				}
			}

			teacher.close();
			
			cout << "Enter 1 to add another teacher else back\n";
			cin >> ret;
		}while(ret == 1);
	}

		
	void log(){
		auth::log();
		login(username,pass);
	}


	void login(string user,string pass){
			int ret;

			do{
				system("cls");
				if(user == admin_username && pass == admin_password){	
					cout<<"Press\n1.For Add Student \n";
					cout<<"2.For Add Teacher \n";
					cout<<"3.To Make Date_Sheet \n";
					cout<<"4.to Back to main menu\n";
					cin>>choice;
					switch (choice)
					{
						case 1:
							add_student();
							break;
						case 2:
							add_teacher();
							break;
						case 3:
							make_datesheet();
							break;
						case 4:
							menu();
						default:
							cout<<"Invalid Choice Press 0 to Try Again else Exit..";
							cin>>ret;
							break;
					}
				}
			}while(ret == 0);		
		}
};


class teacher:public auth,public check,public paper,public first,public date_sheet {
private:
	int choice;
	int usr;
	int check_roll;
	int ret = 0;
	int obtained_marks;
	
public:
	void log(){
		auth::log1();
		login(user,passw);
	}

	void login(int user,int pasw){
		usr=user;

		if (check::check_teacher(user, pasw) == 1){
			teach_menu:
				//system("cls");
				cout<<"WELCOME TEACHERS....."<<endl;
				cout<<"Press\n1.To Make paper \n";
				cout<<"2.To Check paper \n";
				cout<<"3.To  View DateSheet\n4.To back to main Menu \n";
				cin>>choice;
				switch (choice)
				{
					case 1:
						system("cls");
						paper::make_paper();
						break;
					case 2:
						system("cls");
						check_paper();
						break;
					case 3:
						system("cls");
						date_sheet::view_datesheet();	
						char r; 
						cout<<"\nPress Any key to Go back : ";
						cin>>r;
						goto teach_menu;
						break;
					case 4:
						menu();
						break;
					default:
						cout<<"INVALID CHOICE";
						break;
				}
			}
			else{
				cout<<"Emp No. Not found Ask Admin to register You Or try again.\nThanks...";
			}
	}
		
	void check_paper() {
		string n,e,s; int r;
		ifstream ans_sht,file,ques;
		ofstream res;
		string a, b;
		string temp_subject;
		file.open("bin/student.txt" );
		res.open("result.txt",ios::app);
		if (!file) {
			cout << "Something went wrong Try again...";
		}
		string p=check::check_subject(usr);
		cout<<"Check Paper of " << p << endl;
		cout<<"Select Student To Check his/her Paper : "<<endl;
		string lastname = "";
		while (!file.eof()) {
			file >> n >> e >> s >> r;
			if(n!=lastname){
				cout<<"Name : "<<n<<";  Roll Number : "<< r <<endl;
				lastname = n;
			}
			else{
				break;
			}
		}
		cout<<"Enter Roll Number to Check : ";
		cin>>check_roll;

		if(check::check_student(check_roll,check_roll) == 1){
			for(int i=0;i<=5;i++){
				if(p == subject[i]){
					temp_subject=subject[i];
					ans_sht.open(Ans_sheet[i]);

					if(!ans_sht ){
						cout << "Something went wrong Try again...";
					}
					int j=0;
					while(!ans_sht.eof()){
						getline(ans_sht, a);
						getline(ans_sht, b);
						if(stoi(a) == check_roll){
							j++;
							cout << "Q" << j << "  answer: " << b << endl; 
						}
						//cout<<"Answer of "<<j<<" Question : "<<endl<<b<<endl;
					}
					
					cout<<"Enter The Total marks for this student : ";
					cin>>obtained_marks;
					if(addres == 0){
						res << temp_subject<<" "<<check_roll<<" "<<obtained_marks;
						addres = 1;
					}
					else
						res << endl << temp_subject<<" "<<check_roll<<" "<<obtained_marks;
					cout<<endl<<"press 1 for another check else back to main menu: ";
					int pr;
					cin>>pr;
					if(pr == 1)
						check_paper();
					else{
						menu();
					}
				}
			}
		}
		else{
			cout<<"please enter correct roll no. Press 1 to go back";
			char r;
			cin>>r;
			menu();
		}
	}
};


class student:public auth,public check,public date_sheet,public paper,public first{
private:
	int valid;
	int choice;
	char answer[256];
	int ret;

public:
	void log(){
		auth::log1();
		login(user,passw);
	}

	void view_bboard(){
		string stname;
		int marks;
		system("cls");
		get_Board();
		ifstream bboard;
		bboard.open("bboard.txt");
		while(!bboard.eof()){
			bboard >> stname >> marks;
			cout << stname << marks; 
		}
		char r;
		cout<<"Press Any key to go back : ";
		cin >> r;
		menu();	
	}

	void give_paper(){
		cout<<"Welcome Gave Your Paper "<<endl;
		cout << "Select Subject : "<<endl;
		for(int i = 0; i <= 4; i++){
			cout<<"Press "<< i+1 <<" For "<<subject[i] <<endl;
		}
		int ch;
		cin>>ch;
		
		if (ch > 0 && ch < 7){
			ifstream file;
			ofstream ans;
			file.open(file_of_papers[ch-1]);
			ans.open(Ans_sheet[ch-1],ios::app);
			string str;
			if (!file || !ans) {
				cout << "Something went wrong Try again...";
			}
			else{
				string q;
				string m;
				string an;
				cin.ignore();
				while (!file.eof())
				{
					getline(file, q);
					if(q == "\n")
						return;
					getline(file, m);
					getline(file, an);
					cout<<"Q : "<< q << "\t\t\t Marks : " << m << endl;
					cout<<"Ans : ";
					cin.getline(answer, 256);
					cout << answer << endl;
					if(ch == 1){
						if(addans1 == 0){
							ans << valid <<endl;;	
							ans << answer;
							addans1 = 1;
						}
						else{
							ans << endl << valid<<endl;	
							ans << answer;
						}
					}
					else if(ch == 2){
						if(addans2 == 0){
							ans << valid<< endl;	
							ans << answer;
							addans2 = 1;
						}
						else{
							ans << endl << valid<< endl;	
							ans << answer;
						}
					}
					else if(ch == 3){
						if(addans3 == 0){
							ans << valid<< endl;	
							ans << answer;
							addans3 = 1;
						}
						else{
							ans << endl << valid<< endl;	
							ans << answer;
						}
					}
					else if(ch == 4){
						if(addans4 == 0){
							ans << valid<< endl;	
							ans << answer;
							addans4 = 1;
						}
						else{
							ans << endl << valid<< endl;;	
							ans << answer;
						}
					}
					else if(ch == 5){
						if(addans5 == 0){
							ans << valid<< endl;	
							ans << answer;
							addans5 = 1;
						}
						else{
							ans << endl << valid<< endl;
							ans << answer;
						}
					}
				}
				file.close();
			}
		}
	}

	void login(int user, int pasw){
		valid = user;	
		if (check::check_student(user, pasw) == 1){
			st_menu:
			do{
				system("cls");
				cout << "WELCOME " << user << endl;
				cout << "Press\n1. To View Date_sheet \n";
				cout << "2. To Give Paper \n";
				cout << "3. To  View BBoard\n";
				cout << "4. To view Result\n";
				cout << "5. Back to menu\n";
				cin >> choice;
				switch (choice)
				{
					case 1:
						date_sheet::view_datesheet();
						char r; 
						cout << "\nPress Any key to Go back :- ";
						cin >> r;
						goto st_menu;
						break;
					case 2:
						give_paper();
						break;
					case 4:
						result();
						break;
					case 3:
						view_bboard();
						break;
					case 5:
						menu();
						break;
					default:
						cout<<"INVALID CHOICE";
						cout<<"press 1 to try again";
						cin>>ret;
						break;
				}
			}while(ret==1);
		}

		else{
			cout<<"Roll No. Not found Ask Admin to register You Or try again.\nPress any Key to go back : ";
			char r;
			cin >> r;
			menu();
		}
	
	}

	void result(){
		bool isf = 0;
		int choice;
		string sab;
		int rs,om;
		system("cls");
		cout<<"Select Subject to View your result : "<<endl;
		for(int i = 0; i <= 4; i++){
			cout<<"Press "<<i+1<<" to "<< subject[i]<<endl;
		}
		cin >> choice;
		choice = choice - 1;
		if(choice >= 0 && choice < 5){
			ifstream res;
			res.open("result.txt");
			while(!res.eof()){
				res >> sab >> rs >> om;
				if(valid == rs && sab == subject[choice]){
					cout<<"Your Total MArks are : "<< om ;
					isf = 1;
					char r;
					cout<<"Press Any key to go back : ";
					cin >> r;
					menu();	
					break;
				}
			}
			if(!isf){
				cout<<"\nPaper is not check Yet. \n";
				char r;
				cout<<"Press Any key to go back : ";
				cin >> r;
				menu();	
			}
		}
	}

};


void menu(){
	first *obj;
	int choice;
	int ret;
mnu:
	do{
		system("cls");
		cout<<"==========\t\t\t\tEXAM PORTAL\t\t\t\t=========\nPress\n";
	
		cout<<"1. For Admin"<<endl;
		cout<<"2. For Student"<<endl;
		cout<<"3. For Teacher"<<endl;
		cout<<"4. To Exit"<<endl;
		cout<<"Select : ";cin>>choice;
		switch (choice)
		{
			case 1:
				obj=new admin;
				obj->log();
				break;
			case 2:
				obj=new student;
				obj->log();
				break;
			case 3:
				obj=new teacher;
				obj->log();
				break;
			case 4:
				cout<<"\n\tThanks for Using//\n";
				exit(1);
			default:
				cout<<"Invalid Choice Press 0 to Try Again else Exit..";
				cin>>ret;
				break;
		}
	}while (ret==0);
}
	
int main() {
	menu();
}