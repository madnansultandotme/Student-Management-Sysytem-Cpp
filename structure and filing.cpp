
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
#include<stdio.h>
#include<cstdlib>



using namespace std;
//////////////////////////////////////
//////function prototypes/////////////
//////////////////////////////////////
void gotoxy(short, short); // 
void display();	// for record displaying
void add();//adding records
int Search(struct student Std[], int n, int);
void sort(struct student Std[], int n, int);
void del();
int modify(struct student Stu[], int n, int sn);//modify the record
void Update();//To Update the REcords Added by the user
int d_check = 0;//variable to check if data already esist or not;

struct student
{
	char name[40];
	int id;
	double gpa;
	int semester;

};

struct student Std[50];
int n = 0;
int sn;
//////////////////////////////////////
///////////////////main///////////////
/////////////////////////////////////
int main()
{
	fstream file; file.open("data.dat", ios::app);
	if (!file)
	{
		cout << "Error occured in opening a file" << endl;
	}
	char ch1;
	while (1)
	{

		cout << "-------------" << endl

		 << "| MAIN MENU |" << endl

		 << "-------------" << endl << endl

			<< "Please choose one of the options below: "

			<< endl

			<< "--------------------------------------------------------------"

		<< endl



		<< "( A ) add record" << endl << endl

		<< "( O ) sort all records" << endl << endl

		<< "( S ) search for a record" << endl << endl

		 << "( D ) display a record" << endl << endl

		 << "( T ) delete / undelete" << endl << endl

		<< "( M ) update record" << endl << endl

		<< "( Q ) Quit" << endl << endl
		 << "Enter Option      [ ]" << endl << endl;
	
cin>>ch1;




	
	   switch(ch1)
		{
		case 'a':
		case 'A':add(); break;

		case 'd':
		case 'D': display(); break;

		case 'S':
		case 's':
			cout << "Enter the Id you want to Search++++" << endl;
			cin >> sn;
			Search(Std, n, sn);
			if (d_check == 0)

			{
				cout << "========================\n";
				cout << "\n\t\tRecord not found in Given data enter another id\n";
				cout << "========================\n";

			}
			break;
		case 't':
		case 'T':del(); break;

		case 'O':
		case 'o':
			int choice;
			cout << "Enter the following choice" << endl;
			cout << "Press 1 to Sort by Name" << endl;
			cout << "Press 2 to Sort by Id" << endl;
			cin >> choice;
			sort(Std, n, choice);

			break;

		case 'm':
		case 'M':
			Update();
			break;


		case 'q':
		case 'Q':exit(0); break;
		default:
			cout<<"\n enter only from selection listed"<<endl;
		} //end switch
	}//end while

}//end mainst

//////////////////////////////////////
///////////////////Display///////////////
/////////////////////////////////////

void display(void)
{
	fstream file;
	file.open("data.dat", ios::in | ios::out);

	if (!file)
	{
		cout << "file not opened sucessfully" << endl;
	}
	else
	{

		system("cls");
		if (file.fail())               //if reading fails, file is empty

		{
			cout << "empty file";
			cout << "No  Student Record Entered \a" << endl;
			cout << "Press enter to goto main manu.....";
			
		}
		else
		{

			cout << "++++Records in Data are+++++\n";
			cout << " Name:" << "Id:" <<  "Semester" << "Gpa" << endl;
			cout <<  "-------" << "----" << "-------" <<  "----" << endl;
			int i = 0;
			while (file.read((char*)&Std[i], sizeof(Std[i])))
			{
				cout << setw(10) << Std[i].name << setw(20) << Std[i].id << setw(30) << Std[i].semester << setw(40) << Std[i].gpa << endl;
				i++;
			}

			cout << "Press enter to goto main manu.....";
			
		}

	}

}


//////////////////////////////////////
///////////////////Add///////////////
/////////////////////////////////////
void add(void)
{
	char ch;//char id1[6];
	do
	{
		system("cls");
		cout << endl;
		cout << " ADD the Record \n";
		cout << "Enter ID:";
		cin >> Std[n].id;
		//Loop to validate duplicate record  by id
		while (1)
		{
			Search(Std, n, Std[n].id);
			while (d_check == 1)
			{
				cout << "Sorry you cannot Enter Record. The Record already exists with this Id \a" << endl;
				cout << "Try another one" << endl;
				cin >> Std[n].id;
				break;

			}

			if (d_check == 0) {
				break;
			}
		}

		cin.ignore();
		cout << "Enter name:";
		cin.get(Std[n].name, 40);
		cout << "Enter Gpa " << endl;
		cin >> Std[n].gpa;
		while (Std[n].gpa < 0 || Std[n].gpa>4)
		{
			cout << "Gpa must be Between 0 and 4\a" << endl;
			cout << "Enter Gpa you Got again>>>" << endl;
			cin >> Std[n].gpa;

		}

		cout << "In which Semester you Study" << endl;
		cin >> Std[n].semester;
		while (Std[n].semester < 0 || Std[n].semester>8)
		{
			cout << "Semester must be Between 1 and 8\a" << endl;
			cout << "Enter Semester you study again>>>" << endl;
			cin >> Std[n].semester;

		}
		fstream file;
		file.open("data.dat", ios::app);

		file.write((char*)&Std[n], sizeof(Std[n]));

		cin.ignore();
		n++;
		file.close();
		cout << "do you want to add more recors [y/n]";
		cin>>ch;
	} while (ch != 'n'&& ch != 'N');
}

//////////Search////////////////////
int Search(student Std[], int n, int sn)
{
	fstream file;
	file.open("data.dat", ios::in);
	int flag = 0, loc;
	int i = 0;
	while (file.read((char*)&Std[i], sizeof(Std[i])))
	{
		if (Std[i].id == sn)
		{
			loc = i;
			flag = 1;
			break;
		}
	}
	if (flag == 1)
	{
		cout << "\t\t========================\n";
		cout << "\t\tRecord found\n";
		cout << "\t\t========================\n";

		cout << "\t\tName\t student no\t Gpa \t\tSemester \n";
		cout << "\t\t========================\n";
		cout << "\t\t" << Std[loc].name << "\t" << Std[loc].id << "\t" << Std[loc].gpa << "\t\t" << Std[loc].semester << endl; // Prints student name// Prints student number// Prints GPA

		d_check = flag;
		return flag;

	}
	else
	{
		return	d_check = 0;

	}



	
}

//////////sort///////////////////////
void sort(student Std[], int n, int choice)
{
	fstream file;
	file.open("data.dat", ios::binary | ios::in);
	file.read((char*)&Std, sizeof(Std));
	n = (sizeof(Std)) / 52;
	file.close();
	//cout<< "in SORT function\n";
	if (choice == 1)
	{
		student temp;	// Local variable used to swap records

		for (int j = 0; j < n; j++)
		{
			for (int i = 0; i < n - 1; i++)
			{
				// If s[i].student_number is greater than s[i+1].student_number, swap the records
				if (strcmp(Std[i].name, Std[i + 1].name) > 0)
				{
					temp = Std[i];
					Std[i] = Std[i + 1];
					Std[i + 1] = temp;
				}
			}

		}
		cout << "Sorting By name sucessful" << endl << "Press enter to go back" << endl;
	}
	else if (choice == 2)
	{
		student temp;	// Local variable used to swap records

		for (int j = 0; j < n; j++)
		{
			for (int i = 0; i < n - 1; i++)
			{
				if (Std[i].id > Std[i + 1].id)
				{
					temp = Std[i];
					Std[i] = Std[i + 1];
					Std[i + 1] = temp;
				}
			}
		}


		cout << "Sorting Done" << endl << "Press enter to go back" << endl;


	}
	else
	{
		cout << "Invalid Try Again" << endl;

		
		
		cout << "Press enter to go Back" << endl;
	}
}
	///////////////////Update////////////////////////
	void Update()
{
		int index = 0;
		cout << "Enter the Id of record you want to modify" << endl;
		cin >> sn;

		index = modify(Std, n, sn);
		if (index == -1)
		{
			cout << "There is no record against this Id" << endl;
			cout << "Press Enter to go back to Menu and Add Record" << endl;
		}
		else
		{

			
				cout << "Enter the new[Id] " << endl;
				cin >> Std[index].id;
				cin.ignore();
				cout << "Enter the new [ Name ]  " << endl;
				cin.get(Std[index].name, 40);
				cout << "Enter the new  [Semester]" << endl;
				cin >> Std[index].semester;
				cout << "Enter the new [ Gpa ]" << endl;
				cin >> Std[index].gpa;
				//cin.ignore();
			

			}
			cout << "Record Updated Successfully" << endl;
		
	
	}


	////////////Delete//////////////////////
	void del(void)
	{
		int d_index;
		//	cout<< "in DELETE function\n";
		cout << "Enter the Id of record you want to Delete" << endl;
		cin >> sn;
		d_index = modify(Std, n, sn);
		if (d_index == -1)
		{
			cout << "There is no record against this Id" << endl;
			cout << "Press Enter to go back to Menu " << endl;
		}
		else
		{
			for (int i = d_index; i < n - 1; i++)
			{
				Std[i] = Std[i + 1];
			}
			n--;
			system("cls");
			cout << setw(40) << "Record Deleted Sucessfully.............." << endl;x
		}
	}

	///////////Modify//////////////////////
	int modify(student Stu[], int n, int sn)
	{
		fstream file;
		file.open("data.dat", ios::in);
		int flag = 0, loc;
		int i = 0;
		while (file.read((char*)&Std[i], sizeof(Std[i])))
		{
			if (Std[i].id == sn)
			{
				loc = i;
				flag = 1;
				break;
			}
		}
		if (flag == 1)
		{
			cout << "\t\t========================\n";
			cout << "\t\tRecord at Id is\n";
			cout << "\t\t======================================================================\n";
			cout << "\t\tName\t student no\t \t\tGpa \t\t\tSemester \n";
			cout << "\t\t=======================================================================\n";
			cout << "\t\t" << Std[loc].name << "\t" << Std[loc].id << "\t" << Std[loc].gpa << "\t\t" << Std[loc].semester << endl; // Prints student name// Prints student number// Prints GPA


			return loc;

		}
		else
		{
			return -1;

		}




	}





