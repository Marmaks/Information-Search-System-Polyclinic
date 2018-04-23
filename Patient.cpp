#include <iostream>
#include <string>
#include "Patient.h"

using namespace std;

	Patient::Patient() {

	}

	//Builder
	Patient::Patient(int id, string fn, string sn, string tn, int h, int w) {
		ID = id;
		firstName = fn;
		secondName = sn;
		thirdName = tn;
		height = h;
		weight = w;
	}

	//MainSetter
	void Patient::SetPatient(int id, string fn, string sn, string tn, int h, int w) {
		ID = id;
		firstName = fn;
		secondName = sn;
		thirdName = tn;
		height = h;
		weight = w;
	}

	//Getters
	int Patient::GetID() {
		return ID;
	}
	int Patient::GetHeight() {
		return height;
	}
	int Patient::GetWeight() {
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


