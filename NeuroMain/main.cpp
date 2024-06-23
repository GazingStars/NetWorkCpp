#include "NetWork.h"
#include <string>


void doTest(NetWork& neuro)
{
	std::string to_start_test;

	do
	{
		do
		{
			std::cout << "Желаете ли вы провести тестирование? (Y/N) \n";
			cin >> to_start_test;
		} while (!(to_start_test == "Y" || to_start_test == "N"));

		if (to_start_test == "Y")
		{
			std::string safeFileName;
			std::cout << "Укажите название тестируемого файла (Например: test3.txt): \n";
			cin >> safeFileName;

			neuro.Test(safeFileName);
		}
	} while (to_start_test == "Y");
}

void doSave(NetWork& neuro)
{
	std::string safeFile;

	do
	{
		std::cout << "Желаете ли вы согранить архитектуру нейросети в отдельном файле? (Y/N) ";
		cin >> safeFile;

		if (safeFile == "Y")
		{
			neuro.silentShowToFile();
		}

	} while (!(safeFile == "Y" || safeFile == "N"));
}


int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	std::ios_base::sync_with_stdio(false);

	std::string to_start_education;
	const int layer = 4;
	const int imputLayer = 4096;
	std::vector<int> size = { imputLayer , 64, 32, 26 };

	do
	{
		std::cout << "Желаете ли вы провести обучение? (Y/N) ";
		cin >> to_start_education;

	} while (!(to_start_education == "Y" || to_start_education == "N"));



	if (to_start_education == "Y")
	{
		NetWork neuro(size, 1);

		std::cout << "Укажите желаемое имя файла с весами:  \n";
		std::string safeFileName;
		cin >> safeFileName;

		const int n = 52; // Ammount of peactures
		neuro.Educate(n, "lib.txt", safeFileName);

		doTest(neuro);
		doSave(neuro);
	}
	else
	{
		std::string weightsName;
		std::cout << "Укажите название Вашего файла с весами(Например: weights_Final):  \n";
		cin >> weightsName;

		NetWork neuro(size, 1, weightsName);

		doTest(neuro);
		doSave(neuro);
	}

	

	return 0;
}
