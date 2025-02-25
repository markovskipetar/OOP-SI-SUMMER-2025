# Теоретични задачи:


**Задача 1:** Определете големината на структурите:

```c++

struct Empty {

};

struct A {
	char a;
	int32_t b;
};

struct B {	//optimize it
	char a;
	int32_t b;
	char c;
};

struct C {
	int* ptr;
	A a;
	float f;
	int32_t b;
};

struct D {
	B* ptr;
	double d;
};

struct E {
	A arr[3];
	char c;
};

struct F {
	double d;
	int32_t a;
	char c;
	char arr[];
};

struct G {
	char c;
	short a;
	int** ptr;
	C obj;
};
```

**Задача 2:** Какво ще отпечата кода, ако във input.txt има:
```
123 abv pract
```

Кода:
```c++
int main() {
	std::ifstream ifs("input.txt");

	int a;
	char buffer[1024];

	ifs.seekg(1, std::ios::cur);
	ifs >> a;
	std::cout << a << std::endl;
	std::cout << ifs.tellg() << std::endl;

	ifs.getline(buffer, 1024, 'b');
	std::cout << buffer << std::endl;
	std::cout << ifs.tellg() << std::endl;
	std::cout << (char)ifs.get() << std::endl;

	ifs.get(buffer, 1024, 'c');
	std::cout << buffer << std::endl;
	std::cout << ifs.tellg() << std::endl;
}
```

**Задача 3:** Да се напише функция, която намира големината на файл.

**Задача 4:** Да се напише програма, която отпечатва сорс кода си.


# Задачи за практикум:

**Задача 1:**  Да се напише функция, която проверява колко пъти се среща даден символ във файл.

**Задача 2:** От стандартния вход се прочитат три числа. Запишете във файл "result.txt" сумата и произведението им. Направете функция, която извежда на стандартния изход разликата на сумата и произведението, прочетени от файла "result.txt".

**Задача 3:** Напишете програма, която чете масив от файл, като заделя точно толкова памет, колкото е нужна. След това да се сортира възходящо и низходящо, като двата резултата да се запишат в два отделни резултатни файла. ВНИМАНИЕ! Файлът може да е празен.

```
“input.txt”
5
1 6 2 3 9

“ascending.txt”
5
1 2 3 6 9

“descending.txt”
5
9 6 3 2 1
```

**Задача 4:** Напишете структура FMIStudent, която в себе си има име с големина най-много 50, години, масив от оценки с големина най-много 100 и специалност. Специалностите могат да са SE, CS, IS, I. Вашата задача е да напишете функциите saveStudentToFile(const Student& s, std::ofstream& ofs), readStudentFromFile(Student& s, std::ifstream& ifs). Също така напишете и функциите writeStudentArrayToFile(const char* filename, const Student* students, size_t size) и readStudentArrayFromFile(const char* filename, size_t& size).

**Задача 5:** За тази задача използвайте структурите, които написахме предния път - Point, Triangle. Напишете програма, която чете масив от точки от стандартния вход, след което го записва във файл. След като точките са записани във файла, трябва да прочетете същия файл, интерпретиран като масив от триъгълници. Ако броят точки не се дели точно на 3, прочетете толкова триъгълници за колкото стигат точките.

```
Стандартен вход:
4
1 1
1 2
2 3
4 5

Триъгълници:	//само един
(1,1), (1,2), (2,3)
```
