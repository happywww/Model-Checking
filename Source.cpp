#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <boost/functional/hash.hpp>
#include "CTL_formulas.h"

void MiniCheck(unsigned formula_id) {
	bool all_satisfied = true;
	std::vector<int> not_satisfied_states;
	for (int i = 0; i != StateLabel.size(); ++i)
	{
		if (!IsLabeled(formula_id, i)) {
			not_satisfied_states.push_back(i);
			all_satisfied = false;
		}
	}
	if (all_satisfied) {
		std::cout << "the given formula is TRUE in all the staets." << '\n';
	}
	else {
		std::cout << "the given formula is FALSE in the following state(s):" << '\n';
		for (auto it = not_satisfied_states.begin(); it != not_satisfied_states.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << "\n";
	}
}

void CheckNOT(unsigned f) {
	unsigned not_formula_id = NOT(f);
	MiniCheck(not_formula_id);
	std::cout << "NOT(" << f << ")�Ĺ�ʽIDΪ�� " << not_formula_id;
}

void CheckAND(unsigned f1, unsigned f2) {
	unsigned and_formula_id = AND(f1, f2);
	MiniCheck(and_formula_id);
	std::cout << "AND(" << f1 << ", " << f2 << ")�Ĺ�ʽIDΪ�� " << and_formula_id;
}

void CheckAX(unsigned f) {
	unsigned ax_formula_id = AX(f);
	MiniCheck(ax_formula_id);
	std::cout << "AX(" << f << ")�Ĺ�ʽIDΪ�� " << ax_formula_id;
}

void CheckEX(unsigned f) {
	unsigned ex_formula_id = EX(f);
	MiniCheck(ex_formula_id);
	std::cout << "EX(" << f << ")�Ĺ�ʽIDΪ�� " << ex_formula_id;
}

void CheckAU(unsigned f1, unsigned f2) {
	unsigned au_formula_id = AU(f1, f2);
	MiniCheck(au_formula_id);
	std::cout << "AU(" << f1 << ", " << f2 << ")�Ĺ�ʽIDΪ�� " << au_formula_id;
}

void CheckEU(unsigned f1, unsigned f2) {
	unsigned eu_formula_id = EU(f1, f2);
	MiniCheck(eu_formula_id);
	std::cout << "EU(" << f1 << ", " << f2 << ")�Ĺ�ʽIDΪ�� " << eu_formula_id;
}

void CheckAF(unsigned f) {
	unsigned af_formula_id = AF(f);
	MiniCheck(af_formula_id);
	std::cout << "AF(" << f << ")�Ĺ�ʽIDΪ�� " << af_formula_id;
}

void CheckEF(unsigned f) {
	unsigned ef_formula_id = EF(f);
	MiniCheck(ef_formula_id);
	std::cout << "EF(" << f << ")�Ĺ�ʽIDΪ�� " << ef_formula_id;
}

void CheckEG(unsigned f) {
	unsigned eg_formula_id = EG(f);
	MiniCheck(eg_formula_id);
	std::cout << "EG(" << f << ")�Ĺ�ʽIDΪ�� " << eg_formula_id;
}

void CheckAG(unsigned f) {
	unsigned ag_formula_id = AG(f);
	MiniCheck(ag_formula_id);
	std::cout << "AG(" << f << ")�Ĺ�ʽIDΪ�� " << ag_formula_id;
}

void CheckOR(unsigned f1, unsigned f2) {
	unsigned or_formula_id = OR(f1, f2);
	MiniCheck(or_formula_id);
	std::cout << "OR(" << f1 << ", " << f2 << ")�Ĺ�ʽIDΪ�� " << or_formula_id;
}
void CheckIMP(unsigned f1, unsigned f2) {
	unsigned imp_formula_id = AND(f1, f2);
	MiniCheck(imp_formula_id);
	std::cout << "IMP(" << f1 << ", " << f2 << ")�Ĺ�ʽIDΪ�� " << imp_formula_id;
}

void input_f() {
	std::cout << "�����빫ʽID f��" << '\n';
}

void input_f1_f2() {
	std::cout << "�����빫ʽID f1 f2��" << '\n';
}

int main() {

	//����state variable
	int state_variables_length;
	std::cout << "����״̬�����ĸ�����" << '\n';
	std::cin >> state_variables_length;

	std::vector<std::string> state_variables;

	std::string *temp_state_variable;
	temp_state_variable = new std::string;
	for (int i = 0; i != state_variables_length; ++i) {
		std::cout << "�������" << i + 1 << "��state variable�����ƣ�" << '\n';
		std::cin >> *temp_state_variable;
		state_variables.push_back(*temp_state_variable);
	}
	delete temp_state_variable;

	//����states�ĸ���
	std::cout << "������״̬������" << '\n';
	int states_length;
	std::cin >> states_length;

	//��ʼ��SignalValues
	SignalValues.resize(states_length);
	for (auto it = SignalValues.begin(); it != SignalValues.end(); ++it) {
		(*it).resize(state_variables_length);
	}
	
	//��ʼ��NextStates
	NextStates.resize(states_length);

	//����߼���ֵ
	std::cout << "������ߣ�������0->1 aw +������\"0 0 0\"������" << '\n';
	for (int i = 0; i != states_length; ++i) {
		std::cout << i << "->";
		int j;
		std::string edge_value;
		std::string edge_value_op;
		while (std::cin >> j >> edge_value >> edge_value_op) {
			if (j == 0 && edge_value == "0" && edge_value_op == "0") {
				break;
			}

			//����NextStates��
			bool j_not_exise = true;
			for (auto it = NextStates[i].begin(); it != NextStates[i].end(); ++it) {
				if (*it == j) {
					j_not_exise = false;
					break;
				}
			}
			if (j_not_exise) {
				NextStates[i].push_back(j);
			}
			
			//����SignalValues��
			SignalValues[j] = SignalValues[i];
			for (int k = 0; k != state_variables_length; ++k) {
				if (edge_value == state_variables.at(k)) {
					if (edge_value_op == "+") {
						SignalValues[j].at(k) = 1;
					}
					else if (edge_value_op == "-") {
						SignalValues[j].at(k) = 0;
					}
					break;
				}
			}
			
		}
	}

	//��ʼ��StateLabel��
	StateLabel.resize(states_length);
	for (int i = 0; i != states_length; ++i) {
		StateLabel.at(i).insert(1);
		for (int j = 0; j != state_variables_length; ++j) {
			if (SignalValues[i].at(j) == 1) {
				StateLabel[i].insert(j + 2);
			}
		}
	}

	//��ӡ��(�����ã� ����signalvalues�д�
//	SignalValues[0].at(0) = 1;//////////////////////////////test
	for (auto it = state_variables.begin(); it != state_variables.end(); ++it) {		
		std::cout << *it << '\t';
		
	}
	std::cout << '\n';
	for (auto it = SignalValues.begin(); it != SignalValues.end(); ++it) {
		for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
			std::cout << *it2 << '\t';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
	for (auto it = NextStates.begin(); it != NextStates.end(); ++it) {
		for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
			std::cout << *it2 << '\t';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
	for (auto it = StateLabel.begin(); it != StateLabel.end(); ++it) {
		for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
			std::cout << *it2 << '\t';
		}
		std::cout << '\n';
	}

	//check����
	std::cout << "FALSE�Ĺ�ʽID��0" << '\n' << "TRUE�Ĺ�ʽID��1" << '\n';
	for (int i = 0; i != state_variables_length; ++i) {
		std::cout << state_variables.at(i) << "�Ĺ�ʽID��" << i + 2 << '\n' << '\n';
	}
	while (true) {
		std::cout << "��ѡ���ܣ�" << '\n'
			<< "1. check ATOMIC" << '\n'
			<< "2. check NOT(f)" << '\n'
			<< "3. check AND(f1, f2)" << '\n'
			<< "4. check AX(f)" << '\n'
			<< "5. check EX(f)" << '\n'
			<< "6. check AU(f1, f2)" << '\n'
			<< "7. check EU(f1, f2)" << '\n'
			<< "8. check AF(f)" << '\n'
			<< "9. check EF(f)" << '\n'
			<< "10. check EG(f)" << '\n'
			<< "11. check AG(f)" << '\n'
			<< "12. check OR(f1, f2)" << '\n'
			<< "13. check IMP(f1, f2)" << '\n';
		int function_select, f1, f2;
		std::cin >> function_select;
		switch (function_select)
		{
		case 1: {
					input_f();
					std::cin >> f1;
					MiniCheck(f1);
					break;
		}
		case 2: {
					input_f();
					std::cin >> f1;
					CheckNOT(f1);
					break;
		}
		case 3: {
					input_f1_f2();
					std::cin >> f1 >> f2;
					CheckAND(f1, f2);
					break;
		}
		case 4: {
					input_f();
					std::cin >> f1;
					CheckAX(f1);
					break;
		}
		case 5: {
					input_f();
					std::cin >> f1;
					CheckEX(f1);
					break;
		}
		case 6: {
					input_f1_f2();
					std::cin >> f1 >> f2;
					CheckAU(f1, f2);
					break;
		}
		case 7: {
					input_f1_f2();
					std::cin >> f1 >> f2;
					CheckEU(f1, f2);
					break;
		}
		case 8: {
					input_f();
					std::cin >> f1;
					CheckAF(f1);
					break;
		}
		case 9: {
					input_f();
					std::cin >> f1;
					CheckEF(f1);
					break;
		}
		case 10: {
					 input_f();
					 std::cin >> f1;
					 CheckEG(f1);
					 break;
		}
		case 11: {
					 input_f();
					 std::cin >> f1;
					 CheckAG(f1);
					 break;
		}
		case 12: {
					 input_f1_f2();
					 std::cin >> f1 >> f2;
					 CheckOR(f1, f2);
					 break;
		}
		case 13: {
					 input_f1_f2();
					 std::cin >> f1 >> f2;
					 CheckIMP(f1, f2);
					 break;
		}
		default:
			break;
		}
	}
	return 0;
}