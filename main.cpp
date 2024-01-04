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
	int s;// for correct work
public:
	vector <subject*> GetSubInfo() { return SubInfo; }
	string GetName() { return name; }
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
		if (SubjectCheck(SName,s) == 1)
		{
			cout << "Subject list already have that subject!" << endl;
			return;
		}
		subject lesson(SName);
		SubInfo.push_back(new subject(SName));
		cout << SName << " added in subject list! (student)" << endl;

	}
	bool IsHonorsStudent(string SName) //check is that student is honors student (single subject)
	{
		int current = 0;
		if (SubjectCheck(SName, current) == 0 or SubInfo[current]->grade.size() == 0)
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
	void printGrade(string name)
	{	
		int I = 0;
		cout << endl;
		cout << this->GetName() << ": " << endl;
		cout << name << ": ";
		if (SubjectCheck(name, I) == true)
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
class teacher
{
private:
	string name;
	bool sex;
	int s;
	vector <string> SubjectList;//subject vector (teacher can grade students on subjects from that vector )
	bool IsUniversal;// if teacher is universal => can grade student ignoring student subject list
public:
	bool SubjectCheck(string SName, int number)//works like prev. but also return position
	{
		for (int i = 0; i < SubjectList.size(); i++)
		{
			if (SubjectList[i] == SName)
			{
				number = i;
				return 1;
			}
		}
		return 0;
	}
	void AddSubject(string SName)// add new subject in sybject list
	{
		if (SubjectCheck(SName,s) == 1)
		{
			cout << "Subject list already have that subject!" << endl;
			return;
		}
		SubjectList.push_back(SName);
		cout << SName << " added in subject list! (teacher)" << endl;

	}
	void addGrade(string SName, student pupil)// it works when teacher has input subject in subject list (or teacher is universal) and student has input subject in subject list
	{
		int grade = (rand() % 4) + 2;
		int current = 0;
		if ((IsUniversal == false) and (SubjectCheck(SName, current) == false))
		{
			cout << "This teacher has no permition to do that!" << endl;
			return;
		}

		pupil.SubjectCheck(SName, current);// ?
		if (pupil.SubjectCheck(SName, current) == false)
		{
			cout << "This teacher doesn't teach that student" << endl;
			return;
		}
		else
		{
			pupil.GetSubInfo()[current]->grade.push_back(grade);
		}
	}
	void setUniversal(bool T) { IsUniversal = T; }
	teacher(string n, bool s)
	{
		name = n;
		sex = s;
		cout << "Teacher " << name << " (";
		if (sex == 0)
			cout << "woman";
		else
			cout << "man";
		cout << ')' << " joined!" << endl;
		int r = (rand() % 10)+1;
		if (r <= 2)
		{
			IsUniversal = true;
			cout << "This teacher is universal! (u don't need to add subject for this teacher) " << endl;
		}
		else 
		{
			IsUniversal = false;
			cout << "This teacher is common teacher" << endl;
		}
	}
};
int main() 
{
	srand((unsigned)time(NULL));
	student student1 ("Jane", 0);
	student student2 ("John", 1);
	teacher Teacher1("Nick", 1);
	teacher Teacher2("Margaret", 0);
	Teacher2.setUniversal(1);
	Teacher1.AddSubject("Geometry");
	student1.NewSubject("Geometry");
	student2.NewSubject("Geometry");
	Teacher1.addGrade("Geometry", student2);
	Teacher1.addGrade("Geometry", student1);
	student1.printGrade("Geometry");
	cout << student1.GetName() <<" is honour: " << student1.IsHonorsStudent();
	student2.printGrade("Geometry");
	cout << student2.GetName() << " is honour: " << student2.IsHonorsStudent();
	return 0;
}