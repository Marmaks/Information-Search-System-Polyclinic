#include <iostream>
#include <string>

using namespace std;

class Patient
{
private:
	int ID;
	float height;
	float weight;
	string firstName;
	string secondName;
	string thirdName;

public:
	Patient();

	//Builder
	Patient(int, string, string, string, float, float);

	//MainSetter
	void SetPatient(int, string, string, string, float, float);

	//Getters
	int GetID();
	float GetHeight();
	float GetWeight();
	string GetFirstName();
	string GetSecondName();
	string GetThirdName ();
};