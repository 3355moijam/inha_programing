#include "stdafx.h"
#include "class\TableTennisPlayer.h"

int main()
{
	TableTennisPlayer player1("Tara", "Boomdea", false);
	RatedPlayer rplayer1(1140, "Mallory", "Duck", true);
	rplayer1.Name();
	if (rplayer1.HasTable())
		cout << ": Ź���밡 �ִ�." << endl;
	else
		cout << ": Ź���밡 ����." << endl;

	cout << "�̸�: ";
	rplayer1.Name();
	cout << "; ��ŷ: " << rplayer1.Rating() << endl;

	RatedPlayer rplayer2(1212, player1);
	cout << "�̸�: ";
	rplayer2.Name();
	cout << "; ��ŷ: " << rplayer2.Rating() << endl;

	return 0;
}
