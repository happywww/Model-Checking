#include <vector>
#include <set>
#include <boost/functional/hash.hpp>

std::vector<std::vector<int>> SignalValues;
std::vector<std::vector<unsigned int>> NextStates;
std::vector<std::set<unsigned int>> StateLabel;



unsigned int ProduceUniqueFormulaID(std::string seed) {
	boost::hash<std::string> string_hash;

	std::size_t h = string_hash(seed);

	return h;

}

bool IsLabeled(unsigned int FormulaID, unsigned int s) {

	/*	for (auto it = StateLabel[s].begin(); it != StateLabel[s].end(); ++it) {
	if (FormulaID == *it) {
	return true;
	}
	}
	*/
	if (StateLabel.at(s).find(FormulaID) != StateLabel.at(s).end()) {
		return true;
	}
	return false;
}

void AddLabel(unsigned int FormulaID, unsigned int s) {
	StateLabel[s].insert(FormulaID);
}

//FALSE

//TRUE

//ATOMIC

//NOT
unsigned int NOT(unsigned int f) {
	std::string seed = "NOT" + std::to_string(f);
	unsigned int FormulaID = ProduceUniqueFormulaID(seed);

	// std::set<unsigned>::iterator f_position;

	for (int i = 0; i != StateLabel.size(); ++i) {
		if (IsLabeled(f, i) == false) {
			StateLabel.at(i).insert(FormulaID);
		}
	}

	return FormulaID;
}

//AND
unsigned AND(unsigned f1, unsigned f2) {
	std::string seed = "AND" + std::to_string(f1) + std::to_string(f2);
	unsigned int FormulaID = ProduceUniqueFormulaID(seed);

	// std::set<unsigned>::iterator f_position;

	for (int i = 0; i != StateLabel.size(); ++i) {
		if (IsLabeled(f1, i) && IsLabeled(f2, i)) {
			StateLabel.at(i).insert(FormulaID);
		}
	}

	return FormulaID;
}

//AX
unsigned AX(unsigned f) {
	std::string seed = "AX" + std::to_string(f);
	unsigned int FormulaID = ProduceUniqueFormulaID(seed);

	for (int i = 0; i != NextStates.size(); ++i) {
		bool ax_satisfied = 1;
		for (int j = 0; j != NextStates[i].size(); ++j) {
			if (IsLabeled(f, NextStates[i].at(j)) == false) {
				ax_satisfied = 0;
				break;
			}
		}
		if (ax_satisfied) {
			StateLabel.at(i).insert(FormulaID);
		}
	}

	return FormulaID;
}

//EX
unsigned EX(unsigned f) {
	std::string seed = "EX" + std::to_string(f);
	unsigned int FormulaID = ProduceUniqueFormulaID(seed);

	for (int i = 0; i != NextStates.size(); ++i) {
		bool ax_satisfied = 0;
		for (int j = 0; j != NextStates[i].size(); ++j) {
			if (IsLabeled(f, NextStates[i].at(j))) {
				ax_satisfied = 1;
				break;
			}
		}
		if (ax_satisfied) {
			StateLabel.at(i).insert(FormulaID);
		}
	}

	return FormulaID;
}


//AU
unsigned int AU_S(unsigned int f1, unsigned int f2, unsigned int s, std::vector<int> Marked, unsigned int FormulaID) {
	if (1 == Marked.at(s)) {
		if (1 == IsLabeled(FormulaID, s)) {
			return 1;
		}
		else {
			return 0;
		}
	}

	Marked.at(s) = 1;

	if (1 == IsLabeled(f2, s)) {
		AddLabel(FormulaID, s);
		return 1;
	}

	// If neither f2 nor f1 hold in the state, then f is FALSE.Return 0.
	if (0 == IsLabeled(f1, s)) {
		return 0;
	}

	// If f2 is FALSE and f1 is TRUE in s, then, call AU_S for each of its successors, sm.f is TRUE in s iff it is TRUE in all its successors.
	for (unsigned int m = 0; m < NextStates[s].size(); ++m) {
		if (AU_S(f1, f2, NextStates[s][m], Marked, FormulaID) == 0){
			return 0;
		}
	}
	AddLabel(FormulaID, s);
	return 1;
}


unsigned int AU(unsigned int f1, unsigned int f2) {
	std::string seed = "AU" + std::to_string(f1) + std::to_string(f2);
	unsigned int FormulaID = ProduceUniqueFormulaID(seed);

	std::vector<int> Marked(NextStates.size(), 0);

	for (unsigned int n = 0; n < NextStates.size(); ++n) {
		if (0 == Marked.at(n)) {
			AU_S(f1, f2, n, Marked, FormulaID);
		}
	}

	return FormulaID;
}



//EU

unsigned int EU_S(unsigned int f1, unsigned int f2, unsigned int s, std::vector<int> Marked, unsigned int FormulaID) {
	if (1 == Marked.at(s)) {
		if (1 == IsLabeled(FormulaID, s)) {
			return 1;
		}
		else {
			return 0;
		}
	}

	Marked.at(s) = 1;

	if (1 == IsLabeled(f2, s)) {
		AddLabel(FormulaID, s);
		return 1;
	}

	// If neither f2 nor f1 hold in the state, then f is FALSE.Return 0.
	if (0 == IsLabeled(f1, s)) {
		return 0;
	}

	// If f2 is FALSE and f1 is TRUE in s, then, call AU_S for each of its successors, sm.f is TRUE in s iff it is TRUE in all its successors.
	for (unsigned int m = 0; m < NextStates[s].size(); ++m) {
		if (EU_S(f1, f2, NextStates[s][m], Marked, FormulaID) == 1){
			AddLabel(FormulaID, s);
			return 1;
		}
	}
	return 0;
}

unsigned int EU(unsigned int f1, unsigned int f2) {
	std::string seed = "EU" + std::to_string(f1) + std::to_string(f2);
	unsigned int FormulaID = ProduceUniqueFormulaID(seed);

	std::vector<int> Marked(NextStates.size(), 0);

	for (unsigned int n = 0; n < NextStates.size(); ++n) {
		if (0 == Marked.at(n)) {
			EU_S(f1, f2, n, Marked, FormulaID);
		}
	}

	return FormulaID;
}



//AF

//EF

//EG

//AG

//OR

//IMP



//AF
unsigned AF(unsigned f) {
	return AU(1, f);
}
/*
unsigned int AF(unsigned int f) {
std::string seed = "AU" + std::to_string(1) + std::to_string(f);
unsigned int FormulaID = ProduceUniqueFormulaID(seed);

std::vector<int> Marked(NextStates.size(), 0);

for (unsigned int n = 0; n < NextStates.size(); ++n) {
if (0 == Marked.at(n)) {
AU_S(f, n, Marked, FormulaID);
}
}

return FormulaID;
}

unsigned int AF_S(unsigned int f, unsigned int s, std::vector<int> Marked, unsigned int FormulaID) {
if (1 == Marked.at(s)) {
if (1 == IsLabeled(FormulaID, s)) {
return 1;
}
else {
return 0;
}
}

Marked.at(s) = 1;

if (1 == IsLabeled(f, s)) {
AddLabel(FormulaID, s);
return 1;
}

//If neither f2 nor f1 hold in the state, then f is FALSE.Return 0.
//if (0 == IsLabeled(f1, s)) {
//return 0;
//}

// If f2 is FALSE and f1 is TRUE in s, then, call AU_S for each of its successors, sm.f is TRUE in s iff it is TRUE in all its successors.
for (unsigned int m = 0; m < NextStates[s].size(); ++m) {
if (AF_S(f, NextStates[s][m], Marked, FormulaID) == 0){
return 0;
}
}
AddLabel(FormulaID, s);
return 1;
}

*/


//EF
unsigned EF(unsigned f) {
	return EU(1, f);
}
/*
unsigned int EF(unsigned int f) {
std::string seed = "EU" + std::to_string(1) + std::to_string(f);
unsigned int FormulaID = ProduceUniqueFormulaID(seed);

std::vector<int> Marked(NextStates.size(), 0);

for (unsigned int n = 0; n < NextStates.size(); ++n) {
if (0 == Marked.at(n)) {
EF_S(f, n, Marked, FormulaID);
}
}

return FormulaID;
}

unsigned int EF_S(unsigned int f, unsigned int s, std::vector<int> Marked, unsigned int FormulaID) {
if (1 == Marked.at(s)) {
if (1 == IsLabeled(FormulaID, s)) {
return 1;
}
else {
return 0;
}
}

Marked.at(s) = 1;

if (1 == IsLabeled(f, s)) {
AddLabel(FormulaID, s);
return 1;
}

//	 If neither f2 nor f1 hold in the state, then f is FALSE.Return 0.
//	if (0 == IsLabeled(f1, s)) {
//	return 0;
//	}

// If f2 is FALSE and f1 is TRUE in s, then, call AU_S for each of its successors, sm.f is TRUE in s iff it is TRUE in all its successors.
for (unsigned int m = 0; m < NextStates[s].size(); ++m) {
if (EF_S(f, NextStates[s][m], Marked, FormulaID) == 1){
AddLabel(FormulaID, s);
return 1;
}
}
return 0;
}
*/


//EG
unsigned int EG(unsigned int f) {
	return NOT(AF(NOT(f)));
}

//AG
unsigned int AG(unsigned int f) {
	return NOT(EF(NOT(f)));
}


//OR
unsigned OR(unsigned f1, unsigned f2) {
	std::string seed = "OR" + std::to_string(f1) + std::to_string(f2);
	unsigned int FormulaID = ProduceUniqueFormulaID(seed);

	//std::set<unsigned>::iterator f_position;

	for (int i = 0; i != StateLabel.size(); ++i) {
		if (IsLabeled(f1, i) || IsLabeled(f2, i)) {
			StateLabel.at(i).insert(FormulaID);
		}
	}

	return FormulaID;
}

//IMP
unsigned IMP(unsigned f1, unsigned f2) {
	return OR(NOT(f1), f2);
}

