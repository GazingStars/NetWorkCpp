#include "NetWork.h"
#include <string>

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	std::ios_base::sync_with_stdio(false);

	std::string to_start_education;
	std::string to_start_test;
	const int layer = 4;
	const int imputLayer = 4096;
	std::vector<int> size = { imputLayer , 64, 32, 26 };

	do
	{
		std::cout << "������� �� �� �������� ��������? (Y/N) ";
		cin >> to_start_education;

	} while (!(to_start_education == "Y" || to_start_education == "N"));



	if (to_start_education == "Y")
	{
		NetWork neuro(size, 1);

		std::cout << "������� �������� ��� ����� � ������:  \n";
		std::string safeFileName;
		cin >> safeFileName;

		const int n = 52; // Ammount of peactures
		neuro.Educate(n, "lib.txt", safeFileName);

		do
		{
			std::cout << "������� �� �� �������� ������������? (Y/N) \n";
			cin >> to_start_test;

		} while (!(to_start_test == "Y" || to_start_test == "N"));

		if (to_start_test == "Y")
		{
			std::string safeFileName;
			std::cout << "������� �������� ������������ ����� (��������: test3.txt): \n";
			cin >> safeFileName;

			neuro.Test(safeFileName);
		}
	}
	else
	{
		std::string weightsName;
		std::cout << "������� �������� ������ ����� � ������(��������: weights_Final):  \n";
		cin >> weightsName;


		NetWork neuro(size, 1, weightsName);


		do
		{

			do
			{
				std::cout << "������� �� �� �������� ������������? (Y/N) \n";
				cin >> to_start_test;

			} while (!(to_start_test == "Y" || to_start_test == "N"));

			if (to_start_test == "Y")
			{

				std::string safeFileName;
				std::cout << "������� �������� ������������ ����� (��������: test3.txt): \n";
				cin >> safeFileName;

				neuro.Test(safeFileName);

			}

		} while (to_start_test == "Y");



	}

	return 0;
}
