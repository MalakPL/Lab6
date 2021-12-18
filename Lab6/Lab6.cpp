#include <iostream>
#include <iomanip>
#include <algorithm>
#include <io.h>
#include <fcntl.h>
#include <vector>
#include <array>
#include <string>
#include <sstream>

using std::cin;
using std::wcin;
using std::wcout;
using std::cout;
using std::cerr;
using std::endl;
using std::exception;
using std::max_element;
using std::setw;
using std::vector;
using std::array;
using std::wstring;
using std::string;
using std::wstringstream;

const char* IntCastExceptionMessage = "Podana wartosc nie mogla zostac zrzutowana do typu int.";
const char* FloatCastExceptionMessage = "Podana wartosc nie mogla zostac zrzutowana do typu float.";


auto Zadanie1() -> void
{
	wcout << "[Zadanie 1]" << endl;

	int N;
	wcout << "Podaj N: "; cin >> N;

	if (cin.fail()) { throw exception{ IntCastExceptionMessage }; }

	if (N <= 0)
	{
		throw exception{ "Liczba N musi byc wiekszy od 0" };
	}

	int Count = 0;

	/* Rozwiązanie naiwne */
	for (int i = 1; i < N; i++)
	{
		if (i % 5 == 0 && i % 3 != 0)
		{
			Count++;
		}
	}

	/* Szybsze rozwiązanie */
	Count = (N / 3) - (N / 5);

	wcout << L"Ilość liczb naturalnych podzielnych przez 5 i nie podzielnych przez 3 z przedzialu <1," << N << ") wynosi: " << Count << endl << endl;
}


/* Wspólna struktura dla zadania 2 oraz 3 */
struct Studnet
{
	wstring Name;
	wstring LastName;
	unsigned int Index;

	float Ocena[4];
};

vector<wstring> Przedmioty = { L"Informatyka", L"Matematyka", L"Chemia", L"Język polski" };

auto Zadanie2() -> void
{
	const int StudnetCount = 2;

	wcout << "[Zadanie 2]" << endl;

	vector<Studnet> Vec;

	for (int i = 0; i < StudnetCount; ++i)
	{
		Studnet CurStudent;

		wcout << L"Podaj imie ucznia nr " << (i + 1) << L": ";
		wcin >> CurStudent.Name;

		for (int p = 0; p < Przedmioty.size(); ++p)
		{
			wcout << L"Podaj ocene z " << Przedmioty[p] << L": ";
			wcin >> CurStudent.Ocena[p];

			if (cin.fail()) { throw exception{ FloatCastExceptionMessage }; }
		}

		Vec.push_back(CurStudent);

		wcout << endl;
	}

	int N;
	wcout << L"Podaj liczbe zapytań: "; cin >> N;

	for (int i = 0; i < N; ++i)
	{
		int IDX;
		wcout << L"Podaj nr ucznia [1..." << StudnetCount << L"] "; cin >> IDX;

		if (cin.fail()) { throw exception{ IntCastExceptionMessage }; }

		if (IDX < 1 || IDX > StudnetCount)
		{
			throw exception{ "Podany nr ucznia jest niepoprawny" };
		}

		int PIDX;
		wcout << L"Podaj nr przedmiotu [0..." << Przedmioty.size() - 1 << L"] "; cin >> PIDX;

		if (cin.fail()) { throw exception{ IntCastExceptionMessage }; }

		if (PIDX < 0 || PIDX > Przedmioty.size() - 1)
		{
			throw exception{ "Podany nr przedmiotu jest niepoprawny" };
		}

		wcout << L"Uczeń: " << Vec[IDX - 1].Name << L", ocena z " << Przedmioty[PIDX] << L": " << Vec[IDX - 1].Ocena[PIDX] << endl;
	}
}







bool SortByIndex(Studnet i, Studnet j) { return (i.Index < j.Index); }

void PrintVector(vector<Studnet>& Vec)
{
	for (auto const& Element : Vec)
	{
		wcout << Element.Index << L"\t" << Element.Name << L"\t" << Element.LastName << endl;
	}
	wcout << endl;
}

auto Zadanie3() -> void
{
	wcout << "[Zadanie 3*]" << endl;

	vector<Studnet> Vec = {
		{L"Karol",L"Szmajda",5},
		{L"Cezary",L"Walenciuk",25},
		{L"Elon",L"Mózg",1},
		{L"Doge",L"Coin",3},
		{L"Shiba",L"Inu",7},
		{L"Mana",L"Sandbox",4}
	};

	wcout << "Wektor przed sortowaniem: " << endl << endl;
	PrintVector(Vec);

	/* Szkoda, że nie ma tu LINQ ;_; */
	std::sort(Vec.begin(), Vec.end(), SortByIndex);

	wcout << "Wektor po sortowaniu: " << endl << endl;
	PrintVector(Vec);
}


auto Zadanie4() -> void
{
	constexpr auto MAX_GETLINE_SIZE = 80;
	wchar_t Text[MAX_GETLINE_SIZE];
	int N;

	wcout << L"[Zadanie 4]" << endl;

	wcout << L"Wprowadz tekst: ";
	wcin.getline(Text, MAX_GETLINE_SIZE);

	wcout << L"Podaj N: ";
	cin >> N;

	wstringstream NewText;
	for (int i = 0; i < N; ++i)
	{
		NewText << Text;
	}

	wcout << L"Wynik koncowy: " << NewText.str() << endl;
}

auto main() -> int
{
	/* Obsługa wyjątków */
	try
	{
		if (_setmode(_fileno(stdout), _O_U8TEXT) == -1)
		{
			throw exception{ "Nie mozna ustawic kodowania UTF-8" };
		}
		Zadanie1();
		Zadanie2();
		Zadanie3();
		Zadanie4();
	}
	catch (exception ex)
	{
		cerr << "Wyjatek: " << ex.what() << endl;

		return 1; /* Zwracamy błąd */
	}

	return 0;
}