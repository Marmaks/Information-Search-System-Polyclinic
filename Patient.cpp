#include <iostream>
#include <string>
#include "Patient.h"

using namespace std;

	Patient::Patient(int id, string fn, string sn, string tn, float h, float w) {
		ID = id;
		firstName = fn;
		secondName = sn;
		thirdName = tn;
		height = h;
		weight = w;
	}

	void Patient::SetPatient(int id, string fn, string sn, string tn, float h, float w) {
		ID = id;
		firstName = fn;
		secondName = sn;
		thirdName = tn;
		height = h;
		weight = w;
	}

	int Patient::GetID() {
		return ID;
	}
	float Patient::GetHeight() {
		return height;
	}
	float Patient::GetWeight() {
		return weight;
	}
	string Patient::GetFirstName() {
		return firstName;
	}
	string Patient::GetSecondName() {
		return secondName;
	}
	string Patient::GetThirdName() {
		return thirdName;
	}


