#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;


enum Spec { KN, INF, ME, FI, TN };
string specStr[] = { "KN", "INF", "ME", "FI", "TN" };


struct Student
{
	string prizv;
	int course;
	Spec spec;
	int physic;
	int math;

	union
	{
		int prog;
		int chysmet;
		int pedah;
	};
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
double average(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const double ave, const int prog);


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "������ ������� ��������: "; cin >> N;

	Student* p = new Student[N];

	string prizv;
	double ave;
	int prog;
	int found;

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << "  [1] - �������� ����� � ���������" << endl;
		cout << "  [2] - ���� �� �����" << endl;
		cout << "  [3] - ������� �������������" << endl;
		cout << "  [4] - �������� ������������� �� ���� �����" << endl;
		cout << "  [5] - ������� ����� �������� �� ��������," << endl;
		cout << "        ������� ����� �� ������ � �����������" << endl << endl;
		cout << "  [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
		cout << endl << endl << endl;


		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			break;
		case 4:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 5:
			cout << "������ ����� ������:" << endl;
			cout << "������� ���:";
			cin >> ave;
			cin.get();
			cin.sync();
			cout << " �������: "; getline(cin, prizv);
			cout << "  ������ � �������� ��������:  "; cin >> prog;
			if ((found = BinSearch(p, N, prizv, ave, prog)) != -1)
				cout << "�������� ���������� � ������� " << found + 1 << endl;
			else
				cout << "�������� ���������� �� ��������" << endl;
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);

	
	
	return 0;
}
void Create(Student* p, const int N)
{
	int spec;
	int course;
	for (int i = 0; i < N; i++)
	{
		cout << "������� �  " << i + 1 << ":" << endl;

		cin.get();
		cin.sync();

		cout << "   �������: "; getline(cin, p[i].prizv);
		cout << "   ����:   "; cin >> p[i].course;
		cout << "  ������������(0-KN, 1 - INF, 2 - ME, 3-FI, 4-TN): ";
		cin >> spec;
		cout << "  ������ � ������:  "; cin >> p[i].physic;
		cout << "  ������ � ����������:  "; cin >> p[i].math;

		p[i].spec = (Spec)spec;

		switch (p[i].spec)
		{
		case KN:
			cout << "  ������ � �������������:  "; cin >> p[i].prog;
			break;
		case INF:
			cout << "  ������ � ��������� ������:  "; cin >> p[i].chysmet;
			break;
		case ME:
		case FI:
		case TN:
			cout << "  ������ � ���������:  "; cin >> p[i].pedah;
			break;
		}
		cout << endl;
	}
}

void Print(Student* p, const int N)
{
	cout << "================================================================================================================"
		<< endl;
	cout << "|  �  |  �������  | ���� | ������������ | Գ���� | ���������� | ������������� | ������� ������ | ��������� |"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------"
		<< endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(11) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].course << " "
			<< "| " << setw(14) << left << specStr[p[i].spec]
			<< "| " << setw(6) << right << p[i].physic << " "
			<< "| " << setw(10) << right << p[i].math << " ";

		switch (p[i].spec)
		{
		case KN:
			cout << "| " << setw(13) << right << p[i].prog
				<< " |" << setw(19) << right << " | " << setw(12) << right << "|" << endl;
			break;
		case INF:
			cout << "| " << setw(15) << right << " |" << setw(16) << right
				<< p[i].chysmet << " | " << setw(12) << right << "|" << endl;
			break;
		case ME:
		case FI:
		case TN:
			cout << "| " << setw(15) << right << " |" << setw(19) << right
				<< " | " << setw(11) << right << p[i].pedah << "|";
			break;
		}
		cout << endl;
	}
	cout << "================================================================================================================"
		<< endl;
	cout << endl;

}

double average(Student* p, const int i)
{
	double ave = 0;

	ave = (p[i].physic + p[i].math + p[i].prog) / 3.;

	return ave;
}

void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++)
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((average(p, i1) > average(p, i1 + 1))
				||
				(average(p, i1) == average(p, i1 + 1) &&
					p[i1].prog > p[i1 + 1].prog)
				||
				(average(p, i1) == average(p, i1 + 1) &&
					p[i1].prog == p[i1 + 1].prog &&
					p[i1].prizv < p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}

int* IndexSort(Student* p, const int N)
{
	int* I = new int[N];
	for (int i = 0; i < N; i++)
		I[i] = i;

	int i, j, value;
	for (int i = 0; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((average(p, I[j]) > average(p, value)) ||
				(average(p, I[j]) == average(p, value) &&
					p[I[j]].prog > p[value].prog) ||
				(average(p, I[j]) == average(p, value) &&
					p[I[j]].prog == p[value].prog &&
					p[I[j]].prizv < p[value].prizv));
			j--)

		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "================================================================================================================"
		<< endl;
	cout << "|  �  |  �������  | ���� | ������������ | Գ���� | ���������� | ������������� | ������� ������ | ��������� |"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------"
		<< endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " ";
		cout << "| " << setw(11) << left << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].course << " "
			<< "| " << setw(14) << left << specStr[p[I[i]].spec]
			<< "| " << setw(6) << right << p[I[i]].physic << " "
			<< "| " << setw(10) << right << p[I[i]].math << " ";

		switch (p[i].spec)
		{
		case KN:
			cout << "| " << setw(13) << right << p [I[i]].prog
					<< " |" << setw(19) << right << " | " << setw(12) << right << "|" << endl;
				break;
			case INF:
				cout << "| " << setw(15) << right << " |" << setw(16) << right
					<< p[I[i]].chysmet << " | " << setw(12) << right << "|" << endl;
				break;
			case ME:
			case FI:
			case TN:
				cout << "| " << setw(15) << right << " |" << setw(19) << right
					<< " | " << setw(11) << right << p[I[i]].pedah << "|";
				break;
			}
		cout << endl;
	}
	cout << "================================================================================================================"
		<< endl;
	cout << endl;
}

int BinSearch(Student* p, const int N, const string prizv, const double ave, const int prog)
{ // ������� ������ ���������� �������� ��� -1, ���� ������� ������� �������
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && average(p, m) == ave && p[m].prog == prog)
			return m;
		if ((average(p, m) < ave)
			||
			(average(p, m) == ave &&
				p[m].prog < prog)
			||
			(average(p, m) == ave &&
				p[m].prog == prog &&
				p[m].prizv < prizv))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
