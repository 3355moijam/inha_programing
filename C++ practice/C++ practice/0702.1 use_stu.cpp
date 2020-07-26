#include "stdafx.h"
#include "class\Student.h"

void set(Student & sa, int n);

const int pupils = 3;
const int quizzes = 5;

int main()
{
	Student ada[pupils] = { Student(quizzes), Student(quizzes), Student(quizzes) };

	int i;
	for (i = 0; i < pupils; i++)
		set(ada[i], quizzes);

	cout << "\n학생 리스트:\n";
	for (i = 0; i < pupils; i++)
		cout << ada[i].Name() << endl;
	cout << "\n시험 결과:\n";
	for (i = 0; i < pupils; i++)
	{
		cout << endl << ada[i];
		cout << "평균: " << ada[i].Average() << endl;
	}
	cout << "프로그램을 종료합니다. \n";
}

void set(Student & sa, int n)
{
	cout << "학생의 이름을 입력하십시오: ";
	getline(cin, sa);
	cout << n << "회에 걸친 시험 점수를 모두 입력하십시오: \n";
	for (size_t i = 0; i < n; i++)
	{
		cin >> sa[i];
	}
	while (cin.get() != '\n')
	{
		continue;
	}
}
