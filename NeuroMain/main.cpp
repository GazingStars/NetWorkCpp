#include "NetWork.h"


int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	std::ios_base::sync_with_stdio(false);

	const int layer = 4;
	const int imputLayer = 4096;

	//int size[layer] = { imputLayer , 64, 32, 26 }; // Array 

	std::vector<int> size = { imputLayer , 64, 32, 26 };

	//NetWork neuro(layer, size, 1);
	
	NetWork neuro(size, 1, "weights5.txt");

	//NetWork nn2(,);

	//NetWork neuro({ imputLayer , 64, 32, 26 }, 1, "weights.txt");

	const int n = 52; // Ammount of peactures

	neuro.Educate(n, "lib.txt", "weights_Final");


	cout << "Заупстить тестирование: ";
	bool to_start_test;
	cin >> to_start_test;


	if (to_start_test)
	{
		neuro.Test("test3.txt");
	}

	cout << endl;

	//neuro.silentShowToFile();

	

	return 0;
}
