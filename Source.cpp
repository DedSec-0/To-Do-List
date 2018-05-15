#include <iostream>
#include <fstream>
using namespace std;

void Delete_CheckTask(int Check_Delete, bool &Found, char Name[], char Task[], int Day, int UserChoice);
void GetLength(char word[], int & WordLength);
void Search(bool &flag, char Task[], int TaskLength, char SearchTask[], int SearchTaskLength, int Day, int SearchDay);
void ConvertToLowerCase(char name[]);
void InsertExtension(char name[]);
int CheckUser(char name[]);

void Create(char Name[], int Day, int Choice, char Task[])
{
	int User = 2;
	bool Flag = false;
	char TempTask[10] = { '\0' };
	int TempDay = 0;
	int TempChoice = 0;

	User = CheckUser(Name);
	if (User == 0)
	{
		ofstream fout(Name, ios::out);
		fout << Task << ' ' << Day << ' ' << Choice << endl;
	}
	else if (User == 1)
	{
		if (Choice == 2)
		{
			ofstream fout(Name, ios::app);
			fout << Task << ' ' << Day << ' ' << Choice << endl;
		}
		else if (Choice == 1)
		{
			Delete_CheckTask(0, Flag, Name, Task, Day, Choice);
			if (Flag)
			{
				ifstream fin("temp.txt", ios::in);
				ofstream fout(Name, ios::out);
				while (1)
				{
					fin >> TempTask >> TempDay >> TempChoice;
					if (fin.eof())
						break;

					fout << TempTask << ' ' << TempDay << ' ' << TempChoice << endl;
				}
				fin.close();
				fout.close();
			}
			else
			{
				ofstream fout(Name, ios::app);
				fout << Task << ' ' << Day << ' ' << Choice << endl;
				fout.close();
			}
		}
	}
}

void Display(char name[], int UserDay)
{
	char Task[10] = { '\0' };
	int Day = 0;
	int Choice = 0;

	ifstream fin(name, ios::in);
	while (1)
	{
		fin >> Task >> Day >> Choice;
		if (fin.eof())
			break;

		if (Day == UserDay)
		{
			cout << endl << Task << " ";
			switch (UserDay)
			{
			case 1: cout << "Monday" << " "; break;
			case 2: cout << "Tuesday" << " "; break;
			case 3: cout << "Wednesday" << " "; break;
			case 4: cout << "Thursday" << " "; break;
			case 5: cout << "Friday" << " "; break;
			case 6: cout << "Saturday" << " "; break;
			case 7: cout << "Sunday" << " "; break;
			default:
				break;
			}
			if (Choice == 1)
				cout << "Done";
			else if (Choice == 2)
				cout << "Undone";
		}
	}

	cout << endl;
	system("pause");
}

void Delete(char Name[], char Task[], int Day)
{
	int None = 0;
	bool Flag = false;
	char TempTask[20] = { '\0' };
	int TempDay = 0;
	int TempChoice = 0;

	Delete_CheckTask(1, Flag, Name, Task, Day, None);
	if (Flag)
	{
		ifstream fin("temp.txt", ios::in);
		ofstream fout(Name, ios::out);
		while (1)
		{
			fin >> TempTask >> TempDay >> TempChoice;
			if (fin.eof())
				break;

			fout << TempTask << ' ' << TempDay << ' ' << TempChoice << endl;
		}
		fin.close();
		fout.close();
		cout << endl << "Inserting Done. . .";
	}
	else
	{
		cout << "Error !!!..." << Task << " is Not Present on " << Day << endl;
	}

	system("pause");
}

int main()
{
	int option = 0;
	int Day = 0;
	int Choice = 0;
	char Name[10] = { '\0' };
	char Task[20] = { '\0' };

	system("color 4E");
	cout << "************************* Welcome to To-do List ********************************" << endl << endl;
	cout << "Enter Your Name to proceed Further: ";
	cin >> Name;
	InsertExtension(Name);

	while (option != 4)
	{
		cout << endl <<  "Select an option option from below: " << endl;
		cout << "1 : Insert a new task: " << endl;
		cout << "2 : Display the tasks: " << endl;
		cout << "3 : Delete a task " << endl;
		cout << "4 : Quit: ";
		cin >> option;

		system("cls");
		switch (option)
		{
		case 1:
			cout << "Select the day of which you want to enter a task " << endl;
			cout << "1. Monday" << endl << "2. Tuesday" << endl << "3. Wednesday" << endl << "4. Thursday" << endl << "5. Friday" << endl << "6. Saturday" << endl << "7. Sunday: ";
			cin >> Day;
			cout << "Enter the phrase of the task: ";
			cin >> Task;
			cout << "Enter 1 if it is a done task and 2 if its undone: ";
			cin >> Choice;

			ConvertToLowerCase(Task);
			Create(Name, Day, Choice, Task);
			cout << endl << "Inserting Done. . .";
			system("pause");
			system("cls");
			break;

		case 2:
			cout << "Select the day of which you want to display the tasks " << endl;
			cout << "1. Monday" << endl << "2. Tuesday" << endl << "3. Wednesday" << endl << "4. Thursday" << endl << "5. Friday" << endl << "6. Saturday" << endl << "7. Sunday: ";
			cin >> Day;

			Display(Name, Day);
			system("cls");
			break;

		case 3:
			cout << "Enter the phrase of the task you want to delete: ";
			cin >> Task;
			cout << "Select the day of the task of which you want to delete " << endl;
			cout << "1. Monday" << endl << "2. Tuesday" << endl << "3. Wednesday" << endl << "4. Thursday" << endl << "5. Friday" << endl << "6. Saturday" << endl << "7. Sunday: ";
			cin >> Day;

			Delete(Name, Task, Day);
			system("cls");
			break;

		case 4:
			cout << "Quitting . . ." << endl;
			break;

		default:
			cout << "Wrong Input !!!!.... Try Again. . ." << endl;
			break;
		}
	}

	system("pause");
}

void GetLength(char word[], int & WordLength)
{
	WordLength = 0;

	for (int i = 0; word[i] != '\0'; i++)
	{
		WordLength++;
	}
}

void InsertExtension(char name[])
{
	const char Extension[5] = { ".txt" };
	int Length = 0;

	GetLength(name, Length);

	for (int i = 0; i < 5; i++)
	{
		name[i + Length] = Extension[i];
	}
}

void ConvertToLowerCase(char name[])
{
	for (int x = 0; name[x] != '\0'; x++)
	{
		if (name[x] >= 65 && name[x] <= 90)
		{
			name[x] = name[x] + 32;
		}
	}
}

int CheckUser(char name[])
{
	ifstream fin(name, ios::in);
	if (fin.is_open())
		return 1;
	else
		return 0;
}

void Search(bool &flag, char Task[], int TaskLength, char SearchTask[], int SearchTaskLength, int Day, int SearchDay)
{
	flag = true;

	if (TaskLength == SearchTaskLength && Day == SearchDay)
	{
		for (int i = 0; Task[i] != '\0'; i++)
		{
			if (Task[i] != SearchTask[i])
			{
				flag = false;
				break;
			}
		}
	}
	else
	{
		flag = false;
	}
}

void Delete_CheckTask(int Check_Delete, bool &Found, char Name[], char Task[], int Day, int UserChoice)
{
	int SearchDay = 0;
	int Choice = 0;
	int TaskLength = 0;
	int SearchTaskLength = 0;
	char SearchTask[10] = { '\0' };
	bool Flag;

	ofstream fout("temp.txt", ios::out);
	ifstream fin(Name, ios::in);
	while (1)
	{
		fin >> SearchTask >> SearchDay >> Choice;
		if (fin.eof())
			break;

		GetLength(Task, TaskLength);
		GetLength(SearchTask, SearchTaskLength);
		Search(Flag, Task, TaskLength, SearchTask, SearchTaskLength, Day, SearchDay);
		if (Check_Delete == 0)
		{
			if (Flag)
			{
				Choice = UserChoice;
				fout << SearchTask << ' ' << SearchDay << ' ' << Choice << endl;
				Found = true;
			}
			else
			{
				fout << SearchTask << ' ' << SearchDay << ' ' << Choice << endl;
			}
		}
		else if (Check_Delete == 1)
		{
			if (!Flag)
			{
				fout << SearchTask << ' ' << SearchDay << ' ' << Choice << endl;
			}
			else
			{
				Found = true;
			}
		}
	}
}