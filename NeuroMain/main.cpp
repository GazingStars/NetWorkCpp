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

void doSave(const NetWork& neuro)
{
	std::string safeFile;
	do
	{
		std::cout << "Желаете ли вы согранить архитектуру нейросети в отдельном файле? (Y/N) ";
		cin >> safeFile;

		if (safeFile == "Y")
			neuro.silentShowToFile();

	} while (!(safeFile == "Y" || safeFile == "N"));
}

void doFA(NetWork& neuro)
{
	int activationFunction;
	do
	{
		std::cout << "Укажите желаемую функцию активации:\n1. Sigmoid\n2. ReLU\n3. Tangent\n:";
		cin >> activationFunction;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Ошибка ввода. Пожалуйста, введите число.\n";
		}
		else if (!(activationFunction == 1 || activationFunction == 2 || activationFunction == 3))
			std::cout << "Неверное значение. Пожалуйста, введите 1, 2 или 4.\n";

	} while (!(activationFunction == 1 || activationFunction == 2 || activationFunction == 3));

	if (activationFunction == 1)
		neuro.setActivationFunction(new SigmoidActivation());
	else if (activationFunction == 2)
		neuro.setActivationFunction(new ReLUActivation());
	else if (activationFunction == 3)
		neuro.setActivationFunction(new Tangent());
	else
		std::cout << "\nВозникла ошибка, по умолчанию функцией активации будет сигмоида. ";
}

int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	std::ios_base::sync_with_stdio(false);

	std::string to_start_education;
	int threadNum;
	int activationFunction;
	const int layer = 4;
	const int imputLayer = 4096;
	std::vector<int> size = { imputLayer , 64, 32, 26 };

	do
	{
		std::cout << "Желаете ли вы провести обучение? (Y/N) ";
		std::cin >> to_start_education;

	} while (!(to_start_education == "Y" || to_start_education == "N"));

	do
	{
		threadNum = 0;
		std::cout << "Укажите желаемое число потоков (1/2/4):  ";
		std::cin >> threadNum;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Ошибка ввода. Пожалуйста, введите число.\n";
		}
		else if (!(threadNum == 1 || threadNum == 2 || threadNum == 4))
			std::cout << "Неверное значение. Пожалуйста, введите 1, 2 или 3.\n";

	} while (!(threadNum == 1 || threadNum == 2 || threadNum == 4));

	if (to_start_education == "Y")
	{
		NetWork neuro(size, threadNum);

		doFA(neuro);

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
		std::cout << "Укажите название Вашего файла с весами (Например: weights_Final):  \n";
		cin >> weightsName;

		NetWork neuro(size, threadNum, weightsName);

		doFA(neuro);
		doTest(neuro);
		doSave(neuro);
	}

	return 0;
}
