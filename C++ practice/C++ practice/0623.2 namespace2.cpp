#include "stdafx.h"
#include "namesp.h"

void other(void);
void another(void);

int main()
{
	using debts::Debt;
	using debts::showDebt;
	Debt golf = { {"Benny", "Goatsniff"}, 120.0 };
	showDebt(golf);
	other();
	another();

	return 0;
}

void other(void)
{
	using namespace debts;
	Person dg = { "Doodles", "Glister" };
	showPerson(dg);
	cout << endl;

	Debt zippy[3];
	int i;
	for (i = 0; i < 3; i++)
		getDebt(zippy[i]);
	for (i = 0; i < 3; i++)
		showDebt(zippy[i]);

	cout << "��ä �Ѿ�: $" << sumDebts(zippy, 3) << endl;
	return;
}

void another(void)
{
	using pers::Person;
	Person collector = { "Milo", "Rightshift" };
	pers::showPerson(collector);
	cout << endl;
}