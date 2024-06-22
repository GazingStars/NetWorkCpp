#pragma once
#include <iostream>
#include <time.h>
#include <random>
#include <thread>
#include <fstream>
#include <initializer_list>
#include <vector>

using std::cout;
using std::thread;
using std::ofstream;
using std::ifstream;
using std::endl;
using std::cin;
using std::vector;

//TODO
// 1. Random [done!]
// 2. Menu
// 3. Numeric sigm
// 4. Strategy 
// 5. Bridge Logger
// 6. Clean code

class NetWork
{
private:

	struct neuron
	{
		double value;
		double error;

		// возвращает значение сигмоидальной функции //numeric посмотреть
		void act()
		{
			value = (1.0 / (1.0 + std::exp(-value)));
		}

	};

	ifstream fin;//убрать в метод
	ofstream fout;//убрать в метод
	int layers;		// Хранилище количества слоев 
	neuron** neurons;
	double*** weight;
	bool HaveData;
	int* size;		// Хранилище количества нейронов, где size[i] количество нейронов на i-м слое 
	int threadsNum;

public:
	NetWork(const int layers, int* size, const int threadsNum, const std::string& FILE = "");

	NetWork(std::initializer_list<int> iL, const int threadsNum, const std::string& FILE = "");

	NetWork(std::vector<int>& vica, const int threadsNum, const std::string& FILE = "");

	NetWork(NetWork& another) = delete;

	~NetWork();
	
	double getRandom() const;
	

	NetWork& operator=(const NetWork& another) = delete;

	bool haveData() const { return HaveData; }

	void ReadFromFile(const std::string& filename);


	void Educate(const int DataAmmount,const std::string& FileEducateData,const std::string& SafeFaleName);


	void Test(const std::string& FileTestData);



	// Производная сигмоидальной функции
	double sigm_pro(double x);


	double predict(double x);


	void setLayer(int LayerNum, int* NeuroNum); // LayerNum - ammount of layers you wish, NeuroNum - ammount of neurons you wish


	// Функция принимает входные данные и передает их на первые нейроны для дальнейшего анализа
	void set_input(double* input);


	void show();

	void silentShowToFile();

	void LayersCleaner(int LayerNumber, int start, int stop); // LayerNumber - the layer that we want to clean, start/stop - the neurons we want to clean;


	void ForwardFeeder(int LayersNumber, int start, int stop); // LayerNumber - the layer that we want to chande value, start/stop - the neurons we want to change value


	double ForwardFeed(); // Распределяет LayersCleaner и ForwardFeeder по потокам (в зависимости от их количества)


	void ErrorCounter(int LayerNumber, int start, int stop, double prediction, double rresult); // TO DO


	void WeightUpdater(int start, int stop, int LayerNum, double lr);


	void BackPropogation(double prediction, double rresult, double Ir);


	bool SafeWeights(const std::string& SafeFaleName);
};

