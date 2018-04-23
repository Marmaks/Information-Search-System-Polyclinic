#include <iostream>
#include <string>

using namespace std;

class Patient
{
private:
	int ID;
	int height;
	int weight;
	string firstName;
	string secondName;
	string thirdName;

public:
	Patient();

	//Builder
	Patient(int, string, string, string, int, int);

	//MainSetter
	void SetPatient(int, string, string, string, int, int);

	//Getters
	int GetID();
	int GetHeight();
	int GetWeight();
	string GetFirstName();
	string GetSecondName();
	string GetThirdName ();
};