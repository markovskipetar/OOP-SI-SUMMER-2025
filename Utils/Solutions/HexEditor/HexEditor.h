#pragma once
class HexEditor
{
	unsigned char* buffer;
	size_t size;
	size_t capacity;
	char* fileName;

	void copyFrom(const HexEditor& other);
	void free();
	void resize();

	void saveToFile(const char* fileName) const;
	void printByteAsHex(unsigned char byte) const;
	bool isValidSymbol(unsigned char byte) const;

public:
	HexEditor();
	HexEditor(const HexEditor& other);
	HexEditor& operator=(const HexEditor& other);
	~HexEditor();

	void loadFile(const char* fileName);
	void print() const;
	void editByte(unsigned index, unsigned char byte);
	void removeByte();
	void addByte(unsigned char byte);
	void save() const;
	void saveAs(const char* fileName) const;

};

