# Задачи

**Задача 1:** Да се разпише клас SelfCounting, който сам брои колко живи инстанции има в даден момент.

**Задача 2:** Да се напише клас MyString, който играе роля на wrapper class на char* (подобно на std::string). 
Класът трябва да има следните неща:
 - Конструктор по подразбиране, който създава празен стринг ("")
 - Конструктор с const char*, който създава обект с подаденото C-style съдържание
 - Копиращ конструктор
 - Оператор =
 - Деструктор

Основни методи:
 - size_t getSize() const – връща дължината на стринга (без нул терминатора).

 - size_t getCapacity() const – връща капацитета на заделената памет.

 - const char* c_str() const – връща C-style представяне на стринга.

 - MyString substr(unsigned startIndex, unsigned len) const - връща подстринг на нашия.

Оператори:
 - char& operator[](size_t index) и const char& operator[](size_t index) const – достъп до символ по индекс (с/без модификация).

 - MyString& operator+=(const MyString& other) – конкатенация на друг низ към текущия.

 - friend std::ostream& operator<<(std::ostream& os, const MyString& obj) – извеждане в поток.

 - friend std::istream& operator>>(std::istream& is, MyString& ref) – въвеждане от поток.

 - MyString operator+(const MyString& lhs, const MyString& rhs) – връща нов обект, който е резултат от слепване на два низа.

 - Оператори за сравнение


 
