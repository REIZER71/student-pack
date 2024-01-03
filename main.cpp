#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct subject
{
	string SubjectName;
	vector <int> grade;
	subject(string name)
	{
		SubjectName = name;
	}
	subject()
	{
		SubjectName = "Sample text";
	}
	
};
class student
{
private:
	vector <subject*> SubInfo;
	string name;
	bool sex;
public:
	bool SubjectCheck(string SName)//check subject existence in list
	{
		for (int i = 0; i < SubInfo.size(); i++)
		{
			if (SubInfo[i]->SubjectName == SName)
			{
				return 1;
			}
		}
		return 0;
	}
	bool SubjectCheck(string SName, int number)//works like prev. but also return position
	{
		for (int i = 0; i < SubInfo.size(); i++)
		{
			if (SubInfo[i]->SubjectName == SName)
			{
				number = i;
				return 1;
			}
		}
		return 0;
	}
	void NewSubject(string SName)// add new subject in sybject list
	{
		if (SubjectCheck(SName) == 1)
		{
			cout << "Subject list already have that subject!" << endl;
			return;
		}
		subject lesson(SName);
		SubInfo.push_back(new subject(SName));
		cout << SName << " added in subject list!" << endl;

	}
	void addGrade(string SName)// add random grade
	{
		int grade = (rand() % 4) + 2;
		string input;
		int current = 0;
		SubjectCheck(SName, current);
		if (SubjectCheck(SName) == false)
		{
			bool checker;
			cout << "This subject doesn't exist. Add new one?" << endl<<"0 - No     1 - Yes"<< endl;
			cin >> checker;
			if (checker == 1)
				NewSubject(SName);
			SubInfo[SubInfo.size()-1]->grade.push_back(grade);
		}
		else 
		{
			SubInfo[current]->grade.push_back(grade);
		}
	}
	bool IsHonorsStudent(string SName) //check is that student is honors student (single subject)
	{
		int current = 0;
		if (SubjectCheck(SName) == 0)
		{
			cout << "No data!" << endl;
			return 0;
		}
		else
		{
			int sum = 0;
			SubjectCheck(SName, current);
			for (int II = 0; II < SubInfo[current]->grade.size(); II++)
				sum += SubInfo[current]->grade[II];
			sum = sum / SubInfo[current]->grade.size();
			if (sum == 5)
				return 1;
			else 
				return 0;
		}
	}
	bool IsHonorsStudent()// check is that student is honors student (all subjects)
	{
		int sum = 0;
		for (int i = 0; i < SubInfo.size(); i++)
			sum += IsHonorsStudent(SubInfo[i]->SubjectName);
		
		if (sum == SubInfo.size())
			return 1;
		else 
			return 0;
	}
	student(string Name, bool b) //constructor
	{
		name = Name;
		sex = b;
		cout << "student " << name << " (";
		if (sex == 0)
			cout << "girl";
		else 
			cout << "boy";
		cout << ')' << " joined!" << endl;
	}
	void getSubInfo(unsigned int I)// print grade
	{
		cout << SubInfo[I]->SubjectName << ": ";
		if (I < SubInfo.size())
		{
			for (int II = 0; II < SubInfo[I]->grade.size(); II++)
				cout << SubInfo[I]->grade[II] << ' ';
			cout << endl;
			return;
		}
		else
			cout << "No data!" << endl;
	}
};
int main() 
{
	srand((unsigned)time(NULL));
	student student1 ("Jane", 0);
	student student2 ("John", 1);
	student1.NewSubject("Geometry");
	student2.NewSubject("Geometry");
	for (int i = 0; i < 1; i++)
		student1.addGrade("Geometry");
	student1.getSubInfo(0);
	cout << student1.IsHonorsStudent();
	return 0;
}