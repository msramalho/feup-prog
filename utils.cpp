#include "utils.h"

void cin_test(bool &success) {
	if (cin.fail()) {
		cin.clear();
	} else {
		success = true;
	}
	cin.ignore(1000, '\n');
}

template<typename T1>
void cin_value(T1 &result, string message) {
	bool success = false;
	while (!success) {
		cout << message << endl;
		cin >> result;
		cin_test(success);
	}
}

void cin_value_str(string &result, string message) {
	result = "";
	while (result == "") {
		cout << message << endl;
		char cstr_result[1000];
		cin.getline(cstr_result, 1000, '\n');
		result = string(cstr_result);
		if (cin.fail()) {
			cin.clear();
		}
	}
}

//template<typename T1>
//void cin_value(T1 &result, string message) {
	/*cout << "(is_same<string, T1>::value)" << (is_same<string, T1>::value) << endl;
	cout << "(is_same<int, T1>::value)" << (is_same<int, T1>::value) << endl;
	cout << "typeid(result) == typeid(string)" << (typeid(result) == typeid(string)) << endl;
	cout << "result = " << result;*/
	/*if (is_same<string, T1>::value) {
		cin_value_str(result, message);
	} else {
		cin_value_any(result, message);
	}*/
	/*if (typeid(result) == typeid(string)) {
		cin_value_str(result, message);
	} else {
		cin_value_any(result, message);
	}*/
	//cin_value_any(result, message);
//}

void cin_value_between(usi &result, string message, usi min, usi max) {
	cin_value(result, message);
	while (min > result || result > max) {
		cout << "O valor deve estar compreendido entre " << min << " e " << max << ", tente novamente" << endl;
		cin_value(result, message);
	}
}

string to_lower(string original) {
	transform(original.begin(), original.end(), original.begin(), tolower);
	return original;
}

vector<string> split(string line, char delimiter) {
	unsigned int i = 0, last_pos = 0;
	vector<string> result;
	while (i < line.size()) {
		//if the current character matches the delimiter -> split the string there
		if (line.c_str()[i] == delimiter) {
			if (i > last_pos) {
				result.push_back(trim(line.substr(last_pos, i - last_pos)));
			}
			last_pos = i + 1;
		}
		i++;
	}
	if (line.size() > last_pos) {
		//add the remaining characters that came after the last split
		result.push_back(trim(line.substr(last_pos, line.size() - last_pos)));
	}
	return result;
}

string trim(string s, char char_trim) {
	stringstream double_trim;
	double_trim << char_trim << char_trim;
	string d_trim = double_trim.str();

	size_t pos = s.find(d_trim);
	while (pos != s.npos) {
		s.erase(pos, 1);
		pos = s.find(d_trim);
	}
	if (s[0] == char_trim) s.erase(0, 1);
	if (s[s.length() - 1] == char_trim) s.erase(s.length() - 1, 1);
	return s;
}

uint get_max(vector<uint> test) {
	if (test.size() > 0) {
		sort(test.begin(), test.end());
		return test[test.size()-1];
	}
	return 0;
}

void transpose(vector<vector<bool>> &matrix) {
	//for this function to be called there has to be at least one cell in the matrix, so the initialization fo result won't crash the program
	vector<vector<bool>> result(matrix[0].size(), vector<bool>(matrix.size()));
	for (size_t i = 0; i < matrix.size(); i++) {
		for (size_t j = 0; j < matrix[i].size(); j++) {
			result[j][i] = matrix[i][j];
		}
	}
	matrix = result;
}

template<typename T1>
bool in_vector(const vector<T1> &v, T1 value) {
	return find(v.begin(), v.end(), value) != v.end();
}

bool yes_no_question(string message) {
	string answer = "";
	cin_value(answer, message);
	answer = trim(to_lower(answer));
	while (answer != "s" && answer != "n") {
		cout << "A sua resposta deve ser 's' (sim) ou 'n' (nao)" << endl;
		cin_value(answer, message);
		answer = trim(to_lower(answer));
	}
	return answer == "s";
}

vector <string> read_file(string file_name) {
	ifstream f;
	string line;
	vector <string> result;

	f.open(file_name);

	if (f.is_open()) {
		while (getline(f, line)) {
			if (line != "") {//in case there are any additional empty lines in the file
				result.push_back(line);
			}
		}
	}
	f.close();
	return result;
}

bool file_exists(string file_name) {
	ifstream f;
	f.open(file_name);
	if (f.is_open()) {
		f.close();
		return true;
	} else {
		cerr << "Ficheiro " << file_name << " nao encontrado!" << endl;
		return false;
	}
}
