#include "NetWork.h"

NetWork::NetWork(const int layers, int* size, const int threadsNum, const std::string& FILE)
{
	if (FILE.empty())
	{
		HaveData = false;
		this->layers = layers;
		neurons = new neuron * [this->layers]; // Установка слоя
		this->threadsNum = threadsNum;
		weight = new double** [this->layers - 1];
		this->size = new int[this->layers];

		for (int i = 0; i < this->layers; i++)
		{
			this->size[i] = size[i];
			neurons[i] = new neuron[size[i]]; // выделяется область памяти под NeuroNum[i] количество нейронов в слое i 
			if (i < this->layers - 1)
			{
				weight[i] = new double* [this->size[i]];
				for (int j = 0; j < this->size[i]; j++)
				{
					weight[i][j] = new double[size[i + 1]];
					for (int k = 0; k < size[i + 1]; k++)
						weight[i][j][k] = getRandom();
				}
			}
		}
		activationFunction = &sigm;
		std::cout << "\nВсе начальные настройки установлены, но Вам нужно произвести обучение (Educate).\n";
	}
	else
	{
		this->threadsNum = threadsNum;
		HaveData = true;
		this->layers = layers;
		this->size = new int[this->layers];
		neurons = new neuron * [layers];
		for (int i = 0; i < this->layers; i++)
		{
			this->size[i] = size[i];
			neurons[i] = new neuron[size[i]];
		}
		ReadFromFile(FILE);
		activationFunction = &sigm;
	}
}

NetWork::NetWork(std::initializer_list<int> iL, const int threadsNum, const std::string& FILE)
{
	if (FILE.empty())
	{
		HaveData = false;
		this->layers = iL.size();
		this->threadsNum = threadsNum;

		neurons = new neuron * [this->layers]; // Установка слоя
		weight = new double** [this->layers - 1];
		this->size = new int[this->layers];

		auto it = iL.begin();
		for (int i = 0; i < this->layers; i++, it++)
		{
			this->size[i] = *it;
			neurons[i] = new neuron[this->size[i]]; // выделяется область памяти под NeuroNum[i] количество нейронов в слое i 

			if (i < this->layers - 1)
			{
				weight[i] = new double* [this->size[i]];
				auto nextIt = std::next(it);
				for (int j = 0; j < this->size[i]; j++)
				{
					weight[i][j] = new double[*nextIt];
					for (int k = 0; k < *nextIt; k++)
						weight[i][j][k] = getRandom();
				}
			}
		}
		activationFunction = &sigm;
		std::cout << "\nВсе начальные настройки установлены, но Вам нужно произвести обучение (Educate).\n";
	}
	else
	{
		this->threadsNum = threadsNum;
		HaveData = true;
		this->layers = iL.size();
		this->size = new int[this->layers];
		neurons = new neuron * [this->layers];
		auto it = iL.begin();
		for (int i = 0; i < this->layers; i++, it++)
		{
			this->size[i] = *it;
			neurons[i] = new neuron[size[i]];
		}
		ReadFromFile(FILE);
		activationFunction = &sigm;
	}
}

NetWork::NetWork(std::vector<int>& vica, const int threadsNum, const std::string& FILE)
{
	if (FILE.empty())
	{
		HaveData = false;
		this->layers = vica.size();
		neurons = new neuron * [this->layers]; // Установка слоя
		this->threadsNum = threadsNum;
		weight = new double** [this->layers - 1];
		this->size = new int[this->layers];

		for (int i = 0; i < this->layers; i++)
		{
			this->size[i] = vica[i];
			neurons[i] = new neuron[size[i]]; // выделяется область памяти под NeuroNum[i] количество нейронов в слое i 
			if (i < this->layers - 1)
			{
				weight[i] = new double* [this->size[i]];
				for (int j = 0; j < this->size[i]; j++)
				{
					weight[i][j] = new double[vica[i + 1]];
					for (int k = 0; k < vica[i + 1]; k++)
						weight[i][j][k] = getRandom();
				}
			}
		}
		activationFunction = &sigm;
		std::cout << "\nВсе начальные настройки установлены, но Вам нужно произвести обучение (Educate).\n";
	}
	else
	{
		this->threadsNum = threadsNum;
		HaveData = true;
		this->layers = vica.size();
		this->size = new int[this->layers];
		neurons = new neuron * [this->layers];

		for (int i = 0; i < this->layers; i++)
		{
			this->size[i] = vica[i];
			neurons[i] = new neuron[size[i]];
		}
		activationFunction = &sigm;
		ReadFromFile(FILE);
	}
}

NetWork::~NetWork()
{
	if (weight)
	{
		for (int i = 0; i < layers - 1; i++)
		{
			for (int j = 0; j < size[i]; j++)
				delete[] weight[i][j];
			delete[] weight[i];
		}
		delete[] weight;
	}

	if (neurons)
	{
		for (int i = 0; i < layers; i++)
			delete[] neurons[i];
		delete[] neurons;
	}

	if (size)
		delete[] this->size;

}

double NetWork::getRandom() const
{
	std::random_device rd; // SetTheSeed
	std::mt19937 gen(rd());  // Mersenne Twister by Matsumoto and Nishimura
	std::uniform_real_distribution<> dis(-1.0, 1.0); //values distributed across a range

	return dis(gen);
}

void NetWork::ReadFromFile(const std::string& filename)
{
	ifstream fin;
	fin.open(filename);
	if (!filename.empty() && fin.good())
	{
		weight = new double** [layers - 1];
		for (int i = 0; i < layers; i++)
		{
			if (i < layers - 1)
			{
				weight[i] = new double* [size[i]];
				for (int j = 0; j < size[i]; j++)
				{
					weight[i][j] = new double[size[i + 1]];
					for (int k = 0; k < size[i + 1]; k++)
						fin >> weight[i][j][k];
				}
			}
		}
		cout << "\nОшибок не обнаружено, все веса установлены корректно.\n";
	}
	else
		std::cout << "\nОшибка открытия файла.\n";

}

void NetWork::Educate(const int DataAmmount, const std::string& FileEducateData, const std::string& SafeFaleName, const int activationFunction)
{
	ifstream fin;
	ofstream fout;

	double ra = 0; // Right ansvers
	char rresult;  // Right results
	double time = 0;
	double result;

	if (!haveData())
	{
		for (int e = 0; ra / DataAmmount * 100 < 100; e++)
		{
			fout << "Epoch No: " << e << endl;
			double epoch_start = clock();
			ra = 0;

			fin.open(FileEducateData);

			if (fin.good())
			{
				for (int i = 0; i < DataAmmount; i++)
				{
					double start = clock();

					for (int j = 0; j < size[0]; j++)
						fin >> neurons[0][j].value;

					fin >> rresult;
					double stop = clock();
					time += stop - start;

					rresult -= 65;
					result = ForwardFeed();

					if (char(result) == rresult)
					{
						cout << "Угадал " << char(rresult + 65) << "\t\t\t****" << endl;
						ra++;
					}
					else if (activationFunction == 1)
						BackPropogation(result, rresult, 0.3);
					else if (activationFunction == 2)
						BackPropogation(result, rresult, 0.00001);
					else if (activationFunction == 3)
						BackPropogation(result, rresult, 0.001);
				}
				fin.close();
			}
			else
				std::cout << "Ошибка в открытии  файла с обучающими данными.";

			double epoch_stop = clock();
			double maxraepoch = e;

			cout << "Richt answers: " << ra / DataAmmount * 100 << "%\t Max RA: " << "(epoch " << maxraepoch << ')' << endl;
			cout << "Time needed to fin: " << time / 1000 << "s\t\t\tEpoch time: " << epoch_stop - epoch_start << endl;
		}
		if (SafeWeights(SafeFaleName))
			cout << "All saves is done.";
	}
	fin.close();
}

void NetWork::Test(const std::string& FileTestData)
{
	ifstream fin;
	double result;
	fin.open(FileTestData);
	if (fin.is_open())
	{
		for (int i = 0; i < size[0]; i++)
			fin >> neurons[0][i].value;

		result = ForwardFeed();
		cout << "I thing it's letter: " << char(result + 65) << "\n\n";
		fin.close();
	}
	else
		cout << "Mistake with file.";
}

double NetWork::sigm_pro(double x) const
{
	if ((fabs(x - 1) < 1e-9) || (fabs(x) < 1e-9)) // Проверка и отсечение случаев очень близкого значения к 1 или 0, (Значения, очень близкие к 0 или 1, могут из-за ошибок округления вести себя непредсказуемо)
		return 0.0;

	double res = x * (1.0 - x);

	return res;
}

double NetWork::predict(double x) const
{
	if (x >= 0.8)
		return 1;
	return 0;
}

void NetWork::setLayer(int LayerNum, int* NeuroNum)
{
	// Перемещено в конструктор

	// Уточняющий компонент: 
	// В weight[i][j][k]: 
	// weight[i] - количество слоев связей, 
	// weight[i][j] - количество нейронов в текущем слое связей 
	// weight[i][j][k] - количество связей у текущего нейрона
	// Соответственно weight[i][j][k] выделяет конкретную связь у конкретную нейрона в конкретном слое связей
	// 
	// NeuroNum[i] это количество нейронов в i-м слое, size[i] то же самое, но в рамках класса

	layers = LayerNum;
	neurons = new neuron * [LayerNum]; // Установка слоя
	weight = new double** [LayerNum - 1];
	size = new int[LayerNum];
	for (int i = 0; i < LayerNum; i++)
	{
		size[i] = NeuroNum[i];
		neurons[i] = new neuron[NeuroNum[i]]; // выделяется область памяти под NeuroNum[i] количество нейронов в слое i 
		if (i < LayerNum - 1)
		{
			weight[i] = new double* [NeuroNum[i]];
			for (int j = 0; j < NeuroNum[i]; j++)
			{
				weight[i][j] = new double[NeuroNum[i + 1]];
				for (int k = 0; k < NeuroNum[i + 1]; k++)
					weight[i][j][k] = getRandom();
			}
		}
	}
}

void NetWork::set_input(double* input)
{
	for (int i = 0; i < size[0]; i++)
		neurons[0][i].value = input[i];

}

void NetWork::show() const
{
	cout << "Ядер процессора: " << thread::hardware_concurrency() << endl;
	cout << "Нейронная сеть имеет архитектуру: ";
	for (int i = 0; i < layers; i++)
	{
		cout << size[i];
		if (i < layers - 1)
			cout << " - ";

	}cout << endl;
	for (int i = 0; i < layers; i++)
	{
		cout << "\n#Слой " << i + 1 << "\n\n";
		for (int j = 0; j < size[i]; j++)
		{
			cout << "Нейрон №" << j + 1 << ": \n";
			cout << "Значение: " << neurons[i][j].value << endl;

			if (i < layers - 1) // Ограничение выхода за пределы последнего слоя весов
			{
				cout << "Веса: \n";
				for (int k = 0; k < size[i + 1]; k++)
				{
					cout << "#" << k + 1 << ":";
					cout << weight[i][j][k] << endl;
				}
			}
		}
	}
}

void NetWork::silentShowToFile() const
{
	ofstream fout;
	fout.open("silentShowToFile.txt");

	if (fout.good())
	{
		fout << "Ядер процессора: " << thread::hardware_concurrency() << endl;
		fout << "Нейронная сеть имеет архитектуру: ";

		for (int i = 0; i < layers; i++)
		{
			fout << size[i];
			if (i < layers - 1)
				fout << " - ";
		}fout << endl;
		for (int i = 0; i < layers; i++)
		{
			fout << "\n#Слой " << i + 1 << "\n\n";
			for (int j = 0; j < size[i]; j++)
			{
				fout << "Нейрон №" << j + 1 << ": \n";
				fout << "Значение: " << neurons[i][j].value << endl;

				if (i < layers - 1) // Ограничение выхода за пределы последнего слоя весов
				{
					fout << "Веса: \n";
					for (int k = 0; k < size[i + 1]; k++)
					{
						fout << "#" << k + 1 << ":";
						fout << weight[i][j][k] << endl;
					}
				}
			}
		}
		fout.close();
	}
}

void NetWork::LayersCleaner(int LayerNumber, int start, int stop)
{
	for (int i = start; i < stop; i++)
		neurons[LayerNumber][i].value = 0.1;
}

void NetWork::ForwardFeeder(int LayersNumber, int start, int stop)
{
	for (int i = start; i < stop; i++) // Идет по нейронам текущего слоя
	{
		for (int j = 0; j < size[LayersNumber - 1]; j++) // Идет по нейронам предыдущего слоя
			neurons[LayersNumber][i].value += neurons[LayersNumber - 1][j].value * weight[LayersNumber - 1][j][i];
		neurons[LayersNumber][i].act(activationFunction);
	}
}

double NetWork::ForwardFeed()
{
	for (int i = 1; i < layers; i++)
	{
		if (threadsNum == 1)
		{

			thread th1([&]() {
				LayersCleaner(i, 0, size[i]);
				});
			th1.join();

		}
		if (threadsNum == 2)
		{
			//Выполняю очистку двумя
			thread th1([&]() {
				LayersCleaner(i, 0, int(floor(size[i] / 2)));
				});

			thread th2([&]() {
				LayersCleaner(i, int(floor(size[i]) / 2), size[i]);
				});
			th1.join();
			th2.join();
		}

		if (threadsNum == 4)
		{
			if (size[i] == 1)
			{
				thread th1([&]() {
					LayersCleaner(i, 0, size[i]);
					});
				th1.join();
			}

			if (size[i] == 2 || size[i] == 3)
			{
				thread th1([&]() {
					LayersCleaner(i, 0, int(floor(size[i] / 2)));
					});

				thread th2([&]() {
					LayersCleaner(i, int(floor(size[i]) / 2), size[i]);
					});
				th1.join();
				th2.join();
			}

			if (size[i] >= 4)
			{
				int start1 = 0; int stop1 = int(size[i] / 4);
				int start2 = int(size[i] / 4); int stop2 = int(size[i] / 2);
				int start3 = int(size[i] / 2); int stop3 = int(size[i] - floor(size[i] / 4));
				int start4 = int(size[i] - floor(size[i] / 4)); int stop4 = size[i];

				thread th1([&]() {LayersCleaner(i, start1, stop1); });
				thread th2([&]() {LayersCleaner(i, start2, stop2); });
				thread th3([&]() {LayersCleaner(i, start3, stop3); });
				thread th4([&]() {LayersCleaner(i, start4, stop4); });
				th1.join();
				th2.join();
				th3.join();
				th4.join();
			}
		}

		if (threadsNum == 1)
		{
			thread th1([&]() {
				ForwardFeeder(i, 0, size[i]);
				});
			th1.join();
		}

		if (threadsNum == 2)
		{
			thread th1([&]() {
				ForwardFeeder(i, 0, int(floor(size[i] / 2)));
				});

			thread th2([&]() {
				ForwardFeeder(i, int(floor(size[i]) / 2), size[i]);
				});
			th1.join();
			th2.join();
		}

		if (threadsNum == 4)
		{
			if (size[i] == 1)
			{
				thread th1([&]() {
					ForwardFeeder(i, 0, size[i]);
					});
				th1.join();
			}

			if (size[i] == 2 || size[i] == 3)
			{
				thread th1([&]() {
					ForwardFeeder(i, 0, int(floor(size[i] / 2)));
					});

				thread th2([&]() {
					ForwardFeeder(i, int(floor(size[i]) / 2), size[i]);
					});
				th1.join();
				th2.join();
			}

			if (size[i] >= 4)
			{
				int start1 = 0; int stop1 = int(size[i] / 4);
				int start2 = int(size[i] / 4); int stop2 = int(size[i] / 2);
				int start3 = int(size[i] / 2); int stop3 = int(size[i] - floor(size[i] / 4));
				int start4 = int(size[i] - floor(size[i] / 4)); int stop4 = size[i];

				thread th1([&]() {ForwardFeeder(i, start1, stop1); });
				thread th2([&]() {ForwardFeeder(i, start2, stop2); });
				thread th3([&]() {ForwardFeeder(i, start3, stop3); });
				thread th4([&]() {ForwardFeeder(i, start4, stop4); });
				th1.join();
				th2.join();
				th3.join();
				th4.join();
			}
		}
	}

	double max = 0;
	double predicton = 0;
	for (int i = 0; i < size[layers - 1]; i++)
	{
		if (neurons[layers - 1][i].value > max)
		{
			max = neurons[layers - 1][i].value;
			predicton = i;
		}
	}
	return predicton;
}

void NetWork::ErrorCounter(int LayerNumber, int start, int stop, double rresult)
{

	if (LayerNumber == layers - 1)
	{
		for (int j = start; j < stop; j++)
		{
			if (j != int(rresult))
				neurons[LayerNumber][j].error = -(neurons[LayerNumber][j].value);
			else
				neurons[LayerNumber][j].error = 1.0 - neurons[LayerNumber][j].value;
		}
	}
	else
	{
		for (int j = start; j < stop; j++)
		{
			double error = 0.0;
			for (int k = 0; k < size[LayerNumber + 1]; k++)
				error += neurons[LayerNumber + 1][k].error * weight[LayerNumber][j][k];

			neurons[LayerNumber][j].error = error;
		}
	}
}

void NetWork::WeightUpdater(int start, int stop, int LayerNum, double lr)
{
	int i = LayerNum;

	for (int j = start; j < stop; j++)
		for (int k = 0; k < size[i + 1]; k++)
			weight[i][j][k] += lr * neurons[i + 1][k].error * activationFunction->derivative(neurons[i + 1][k].value) * neurons[i][j].value;
}

void NetWork::BackPropogation(double prediction, double rresult, double Ir)
{
	for (int i = layers - 1; i > 0; i--)
	{
		if (threadsNum == 1)
		{
			thread th1([&]() {
				ErrorCounter(i, 0, size[i], rresult);
				});
			th1.join();
		}
		if (threadsNum == 2)
		{
			thread th1([&]() {
				ErrorCounter(i, 0, int(size[i] / 2), rresult);
				});

			thread th2([&]() {
				ErrorCounter(i, int(size[i] / 2), size[i], rresult);
				});
			th1.join();
			th2.join();
		}

		if (threadsNum == 4)
		{
			if (size[i] < 4)
			{
				if (i == layers - 1)
				{
					for (int j = 0; j < size[i]; j++)
					{
						if (j != int(rresult))
							neurons[i][j].error = -(neurons[i][j].value);
						else
							neurons[i][j].error = 1.0 - neurons[i][j].value;
					}
				}
				else
				{
					for (int j = 0; j < size[i]; j++)
					{
						double error = 0.0;
						for (int k = 0; k < size[i + 1]; k++)
							error += neurons[i + 1][k].error * weight[i][j][k];
						neurons[i][j].error = error;
					}
				}
			}
			if (size[i] >= 4)
			{
				int start1 = 0; int stop1 = int(size[i] / 4);
				int start2 = int(size[i] / 4); int stop2 = int(size[i] / 2);
				int start3 = int(size[i] / 2); int stop3 = int(size[i] - floor(size[i] / 4));
				int start4 = int(size[i] - floor(size[i] / 4)); int stop4 = size[i];

				thread th1([&]() {
					ErrorCounter(i, start1, stop1, rresult);
					});
				thread th2([&]() {
					ErrorCounter(i, start2, stop2, rresult);
					});
				thread th3([&]() {
					ErrorCounter(i, start3, stop3, rresult);
					});
				thread th4([&]() {
					ErrorCounter(i, start4, stop4, rresult);
					});

				th1.join();
				th2.join();
				th3.join();
				th4.join();
			}
		}
	}
	for (int i = 0; i < layers - 1; i++)
	{
		if (threadsNum == 1)
		{
			thread th1([&]() {
				WeightUpdater(0, int(size[i]), i, Ir);
				});

			th1.join();
		}
		if (threadsNum == 2)
		{
			thread th1([&]() {
				WeightUpdater(0, int(size[i] / 2), i, Ir);
				});

			thread th2([&]() {
				WeightUpdater(int(size[i] / 2), size[i], i, Ir);
				});

			th1.join();
			th2.join();
		}
		if (threadsNum == 4)
		{
			int start1 = 0; int stop1 = int(size[i] / 4);
			int start2 = int(size[i] / 4); int stop2 = int(size[i] / 2);
			int start3 = int(size[i] / 2); int stop3 = int(size[i] - floor(size[i] / 4));
			int start4 = int(size[i] - floor(size[i] / 4)); int stop4 = size[i];

			thread th1([&]() {
				WeightUpdater(start1, stop1, i, Ir);
				});
			thread th2([&]() {
				WeightUpdater(start2, stop2, i, Ir);
				});
			thread th3([&]() {
				WeightUpdater(start3, stop3, i, Ir);
				});
			thread th4([&]() {
				WeightUpdater(start4, stop4, i, Ir);
				});

			th1.join();
			th2.join();
			th3.join();
			th4.join();
		}
	}
}

bool NetWork::SafeWeights(const std::string& SafeFaleName)
{
	ofstream fout;
	fout.open(SafeFaleName);
	if (fout.is_open())
	{
		for (int i = 0; i < layers; i++)
			if (i < layers - 1)
				for (int j = 0; j < size[i]; j++)
					for (int k = 0; k < size[i + 1]; k++)
						fout << weight[i][j][k] << " ";
		fout.close();
		return 1;
	}
	return 0;
}