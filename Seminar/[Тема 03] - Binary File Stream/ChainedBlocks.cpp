#include <iostream>
#include <fstream>

constexpr int blockSize = 32;
constexpr int endOfChainIndex = -1;

int getMessageLength(std::ifstream& binaryReader)
{
	int binaryReaderInitialPosition = binaryReader.tellg();
	binaryReader.seekg(0);

	int16_t nextBlockIndex = 0;
	uint16_t currentMessageLength = 0;

	int totalMessageLength = 0;

	while (true)
	{
		binaryReader.seekg(nextBlockIndex * blockSize);

		binaryReader.read((char*)&nextBlockIndex, sizeof(int16_t));
		binaryReader.read((char*)&currentMessageLength, sizeof(int16_t));

		totalMessageLength += currentMessageLength;

		if (nextBlockIndex == endOfChainIndex)
		{
			break;
		}
	}

	binaryReader.seekg(binaryReaderInitialPosition);

	return totalMessageLength;
}

const char* readMessage(int totalMessageLength, std::ifstream& binaryReader)
{
	char* message = new char[totalMessageLength + 1]; // +1 because of '\0'
	char* messageIterator = message;

	int16_t nextBlockIndex = 0;
	uint16_t currentMessageLength = 0;

	while (true)
	{
		binaryReader.seekg(nextBlockIndex * blockSize);

		binaryReader.read((char*)&nextBlockIndex, sizeof(int16_t));
		binaryReader.read((char*)&currentMessageLength, sizeof(uint16_t));

		binaryReader.read(messageIterator, currentMessageLength);
		messageIterator += currentMessageLength;

		if (nextBlockIndex == endOfChainIndex)
		{
			break;
		}
	}

	message[totalMessageLength] = '\0';
	return message;
}

int main()
{
	std::ifstream binaryReader("blocks.dat", std::ios::binary);

	if (!binaryReader.good())
	{
		std::cout << "err";
		return -1;
	}

	int totalMessageLength = getMessageLength(binaryReader);

	const char* message = readMessage(totalMessageLength, binaryReader);

	std::cout << message;

	delete[] message;
}