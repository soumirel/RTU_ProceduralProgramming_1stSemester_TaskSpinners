#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <fstream>
#include <iomanip> 
#include <string>
#define NOMINMAX
#include <windows.h>

using namespace std;


void uncorrectValueMessage_cinClear() {
	cout << "Некорректный ввод. Введите значение заново: ";
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


//Functions for error cheking with input:
int initializeInteger(string limits = "", int left = 0, int right = 0) {

	string var;
	bool isVarCorrect = true;
	bool isNumber;
	int intValue;
	bool isPositive, isNegative, isNotPositive, isNotNegative, isAllExeptZero;
	bool isInBorders;

	while (true) {
		cin >> var;
		isVarCorrect = true;
		for (size_t i = 0; i < var.length(); i++) { // Проверка на то, является ли введенная строка числом в принципе.
			if (i == 0 and var[i] == '-') {
				if (var.length() < 2) {
					isVarCorrect = false;
					break;
				}
			} else {
				isNumber = (var[i] >= '0' && var[i] <= '9');
				if (!isNumber) {
					isVarCorrect = false;
					break;
				}
			}
		}
		if (isVarCorrect) {
			intValue = stoi(var);
			if (left == 0 and right == 0) { //Ввод числа без заданного диапазона допустимых значений.
				isPositive = intValue > 0;
				isNegative = intValue < 0;
				isNotPositive = intValue <= 0;
				isNotNegative = intValue >= 0;
				isAllExeptZero = intValue != 0;
				if ((limits == "POSITIVE" && !isPositive) ||
					(limits == "NEGATIVE" && !isNegative) ||
					(limits == "NOTPOSITIVE" && !isNotPositive) ||
					(limits == "NOTNEGATIVE" && !isNotNegative) ||
					(limits == "NOTZERO" && !isAllExeptZero)) {
					isVarCorrect = false;
				}
				else {
					return intValue;
				}
			} else {  //Ввод числа с заданным диапазоном допустимых значений.
				isInBorders = (intValue >= left && intValue <= right);
				if (isInBorders)
					return intValue;
				else {
					isVarCorrect = false;
				}
			}
		}
		if (!isVarCorrect){
			uncorrectValueMessage_cinClear();
		}
	}
}


void spinners(){
	int baseCost, bladeCost, maxCost = 0;
	cout << "\nВведите стоимость осования спиннера: ";
	baseCost = initializeInteger("POSITIVE");
	cout << "Введите стоимость лопасти: ";
	bladeCost = initializeInteger("POSITIVE");
	cout << "Сколько денег готов отдать покупатель? - ";
	while (maxCost < baseCost) {
		maxCost = initializeInteger("POSITIVE");
		if (maxCost < baseCost) {
			cout << "Слишком низкая цена, давай еще поторгуемся: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	int numberOfBlades = (maxCost - baseCost) / bladeCost;
	if (numberOfBlades > 0) {
		cout << "Максимальное число лопастей = " << numberOfBlades << endl;
	}
	else {
		cout << "Похоже, спиннер придется сделать без лопастей\n\n";
	}
}


void spinnersAgain() {
	int totalNumberOfBlades;
	cout << "Введите число лопастей: ";
	totalNumberOfBlades = initializeInteger("POSITIVE");

	int numberOfThreeBlades = 0, numberOfFourBlades = 0;
	bool isResolve = false;
	if (totalNumberOfBlades % 4 == 0) {
		numberOfFourBlades = totalNumberOfBlades / 4;
		numberOfThreeBlades = 0;
		isResolve = true;
	}
	else if (totalNumberOfBlades % 3 == 0) {
		numberOfThreeBlades = totalNumberOfBlades / 3;
		numberOfFourBlades = 0;
		isResolve = true;
	}
	else {
		while (totalNumberOfBlades > 4 && !isResolve) {
			totalNumberOfBlades -= 4;
			numberOfFourBlades++;
			if (totalNumberOfBlades % 3 == 0) {
				numberOfThreeBlades = totalNumberOfBlades / 3;
				isResolve = true;
			}
		}
		if (isResolve) {
			cout << "Количество трёхлопастных спиннеров - " << numberOfThreeBlades << endl;
			cout << "Количество четырёхлопастных спиннеров - " << numberOfFourBlades << endl;
		}
		else {
			cout << "Количество трёхлопастных спиннеров - 0\n";
			cout << "Количество четырёхлопастных спиннеров - 0\n";
		}
	}
}


void notAboutSpinners() {
	int length, width, combinations;
	cout << "Введите длинну листа: ";
	length = initializeInteger("POSITIVE");
	cout << "Введите ширину листа: ";
	width = initializeInteger("POSITIVE");
	combinations = (length * (length + 1) / 2 * width * (width + 1) / 2);
	cout << "Кол-во прямоугольников, что можно вырезать из даного листа = " << combinations << endl << endl;
}


int compartment(int seat) {
	if (seat < 37)
		return (seat - 1) / 4;
	else
		return 8 - (seat - 37) / 2;
}


void wagon() {
	int seatsNumber, currentSeat;
	int freeСompartment[9] = { 0 };
	int answer = 0, currentAnswer = 0;
	cout << "Введите число свободных мест в вагоне : ";
	seatsNumber = initializeInteger("ALL", 1, 54);
	cout << "Введите номера свободных мест: ";
	for (int i = 0; i < seatsNumber; i++){
		currentSeat = initializeInteger("ALL", 1, 54);
		freeСompartment[compartment(currentSeat)]++;
	}
	for (int i = 0; i < 9; i++){
		if (freeСompartment[i] == 6)
			currentAnswer++;
		else {
			answer = max(answer, currentAnswer);
			currentAnswer = 0;
		}
	}
	cout << "Максимальное число подряд идущих свободных купе = " << answer << "\n\n";
}


void movieTheatre() {
	int freeSpace, students;
	cout << "Введите количество свободных мест в ряду: ";
	freeSpace = initializeInteger("ALL", 1, numeric_limits<int>::max()) + 2;
	cout << "Сколько школьников зашло в зал: ";
	students = initializeInteger("ALL", 1, freeSpace);

	int* row = new int[freeSpace]{ 0 } ;
	row[0] = 1;
	row[freeSpace - 1] = 1;

	int answerOnLeft, answerOnRight;
	int left, right, center;
	int currLeft, currRight;
	int maxLength, currLength;

	for (int i = 1; i <= students; i++) {
		left = right = currLeft = currRight = currLength = maxLength = 0;
		for (int j = 0; j < freeSpace; j++) {
			if (row[j] == 0) {
				if (currLength == 0) {
					currLeft = j;
				}
				currRight = j;
				currLength++;
			}
			else {
				if (currLength > maxLength) {
					maxLength = currLength;
					left = currLeft;
					right = currRight;
				}
				currLength = 0;
			}
		}
		cout << endl;
		center = (left + right) / 2;
		row[center] = 1;
		if (i == students) {
			answerOnLeft = center - left;
			answerOnRight = right - center;
		}
	}
	cout << "Кол-во свободных мест слева от последнего школьника = " << answerOnLeft << endl;
	cout << "Кол-во свободных мест справа от последнего школьника = " << answerOnRight << endl << endl;
}


int main() {
	setlocale(LC_ALL, "Rus");
	int neededTask;
	bool isСontinues = true;
	while (isСontinues) {
		cout << "Введите номер задания, которое хотите проверить." << endl;
		cout << "Если вы хотите закончить проверку - введите 0" << endl;
		cin >> neededTask;
		switch (neededTask) {
		case(0):
			isСontinues = false;
			break;
		case(1):
			spinners();
			break;
		case(2):
			spinnersAgain();
			break;
		case(3):
			notAboutSpinners();
			break;
		case(4):
			wagon();
			break;
		case(5):
			movieTheatre();
			break;
		default:
			cout << "Я не понимаю вас." << endl;
			break;
		}

	}
}