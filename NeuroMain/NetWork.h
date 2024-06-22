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

		// ���������� �������� ������������� ������� //numeric ����������
		void act()
		{
			value = (1.0 / (1.0 + std::exp(-value)));
		}

	};

	ifstream fin;//������ � �����
	ofstream fout;//������ � �����
	int layers;		// ��������� ���������� ����� 
	neuron** neurons;
	double*** weight;
	bool HaveData;
	int* size;		// ��������� ���������� ��������, ��� size[i] ���������� �������� �� i-� ���� 
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



	// ����������� ������������� �������
	double sigm_pro(double x);


	double predict(double x);


	void setLayer(int LayerNum, int* NeuroNum); // LayerNum - ammount of layers you wish, NeuroNum - ammount of neurons you wish


	// ������� ��������� ������� ������ � �������� �� �� ������ ������� ��� ����������� �������
	void set_input(double* input);


	void show();

	void silentShowToFile();

	void LayersCleaner(int LayerNumber, int start, int stop); // LayerNumber - the layer that we want to clean, start/stop - the neurons we want to clean;


	void ForwardFeeder(int LayersNumber, int start, int stop); // LayerNumber - the layer that we want to chande value, start/stop - the neurons we want to change value


	double ForwardFeed(); // ������������ LayersCleaner � ForwardFeeder �� ������� (� ����������� �� �� ����������)


	void ErrorCounter(int LayerNumber, int start, int stop, double prediction, double rresult); // TO DO


	void WeightUpdater(int start, int stop, int LayerNum, double lr);


	void BackPropogation(double prediction, double rresult, double Ir);


	bool SafeWeights(const std::string& SafeFaleName);
};

