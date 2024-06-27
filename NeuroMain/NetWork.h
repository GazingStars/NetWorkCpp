#pragma once
#include "ActivationFunction.h"
#include "SigmoidActivation.h"
#include "ReLUActivation.h"
#include "Tangent.h"
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

class NetWork
{
protected:

	struct neuron
	{
		double value;
		double error;
		ActivationFunctions* activationFunction;
		// Функция активации 
		void act(ActivationFunctions* activationFunction) { value = activationFunction->activate(value); }
	};

	int layers;		// Хранилище количества слоев 
	neuron** neurons; // Двумерный массив нейронов, где neurons[i] представляет массив нейронов в i-м слое.
	double*** weight;
	bool HaveData;
	int* size;		// Хранилище количества нейронов, где size[i] количество нейронов на i-м слое 
	int threadsNum;
	ActivationFunctions* activationFunction;
	SigmoidActivation sigm;

public:
	NetWork(const int layers, int* size, const int threadsNum, const std::string& FILE = "");

	NetWork(std::initializer_list<int> iL, const int threadsNum, const std::string& FILE = "");

	NetWork(std::vector<int>& vica, const int threadsNum, const std::string& FILE = "");

	NetWork(NetWork& another) = delete;

	~NetWork();

	void setActivationFunction(ActivationFunctions* func) { activationFunction = func; }

	double getRandom() const;

	NetWork& operator=(const NetWork& another) = delete;

	bool haveData() const { return HaveData; }

	void ReadFromFile(const std::string& filename);

	void Educate(const int DataAmmount, const std::string& FileEducateData, const std::string& SafeFaleName, const int activationFunction);

	void Test(const std::string& FileTestData);

	// Производная сигмоидальной функции
	double sigm_pro(double x) const;

	double predict(double x) const;

	void setLayer(int LayerNum, int* NeuroNum); // LayerNum - ammount of layers you wish, NeuroNum - ammount of neurons you wish

	// Функция принимает входные данные и передает их на первые нейроны для дальнейшего анализа
	void set_input(double* input);

	void show() const;

	void silentShowToFile() const;

	void LayersCleaner(int LayerNumber, int start, int stop); // LayerNumber - the layer that we want to clean, start/stop - the neurons we want to clean;

	void ForwardFeeder(int LayersNumber, int start, int stop); // LayerNumber - the layer that we want to chande value, start/stop - the neurons we want to change value

	double ForwardFeed(); // Распределяет LayersCleaner и ForwardFeeder по потокам (в зависимости от их количества)

	void ErrorCounter(int LayerNumber, int start, int stop, double rresult);

	void WeightUpdater(int start, int stop, int LayerNum, double lr);

	void BackPropogation(double prediction, double rresult, double Ir);

	bool SafeWeights(const std::string& SafeFaleName);
};

