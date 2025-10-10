#include "../include/bit_string.h"
#include <stdexcept>

BitString::BitString() : arraySize(0), bitArray(nullptr) {}

BitString::BitString(const size_t & arraySize, unsigned char defaultValue) {
    this -> arraySize = arraySize;
    this -> bitArray = new unsigned char[arraySize];

    for (size_t i = 0; i < arraySize; ++i) {
        this-> bitArray[i] = defaultValue;
    }
}

BitString::BitString(const std::initializer_list<unsigned char>& initialValues) {
    arraySize = initialValues.size();
    bitArray = new unsigned char[arraySize];

    size_t index = 0;
    for (const auto& value: initialValues) {
        bitArray[index++] = value;
    }
}

BitString::BitString(const std::string& sourceString) {
    arraySize = sourceString.size();
    bitArray = new unsigned char[arraySize];

    for (size_t i = 0; i < arraySize; ++i) {
        if (sourceString[i] != '0' && sourceString[i] != '1') {
            delete[] bitArray;
            throw std::invalid_argument("Строка должна состоять только из '0' или '1'");
        }
        bitArray[i] = static_cast<unsigned char>(sourceString[i]);
    }
}

BitString::BitString(const BitString& other) : arraySize(other.arraySize) {
    bitArray = new unsigned char[arraySize];
    for (size_t i = 0; i < arraySize; ++i) {
        bitArray[i] = other.bitArray[i];
    }
}

BitString::BitString(BitString&& other) : bitArray(other.bitArray), arraySize(other.arraySize) {
    other.bitArray = nullptr;
    other.arraySize = 0;
}

BitString::~BitString() noexcept {
    if (bitArray != nullptr) {
        delete[] bitArray;
        bitArray = nullptr;
    }

    arraySize = 0;
}

// Тут ввел ограничение с одинаковой длиной строк для упрощения 
BitString BitString::bitAnd(const BitString& other) const {
    if(arraySize != other.arraySize) {
        throw std::invalid_argument("Строки должны иметь одинаковую длину для побитовой операции");
    }

    BitString result(arraySize);
    for (size_t i = 0; i < arraySize; ++i) {
        result.bitArray[i] = (bitArray[i] & other.bitArray[i]);
    }
    return result;
}

BitString BitString::bitOr(const BitString& other) const {
    if(arraySize != other.arraySize) {
        throw std::invalid_argument("Строки должны иметь одинаковую длину для побитовой операции");
    }

    BitString result(arraySize);
    for (size_t i = 0; i < arraySize; ++i) {
        result.bitArray[i] = (bitArray[i] | other.bitArray[i]);
    }
    return result;
}

BitString BitString::bitXor(const BitString& other) const {
    if(arraySize != other.arraySize) {
        throw std::invalid_argument("Строки должны иметь одинаковую длину для побитовой операции");
    }

    BitString result(arraySize);
    for (size_t i = 0; i < arraySize; ++i) {
        result.bitArray[i] = (bitArray[i] ^ other.bitArray[i]);
    }
    return result;
}

BitString BitString::bitNot() const {
    BitString result(arraySize);
    for (size_t i = 0; i < arraySize; ++i) {
        result.bitArray[i] = (bitArray[i] == 0) ? 1 : 0;
    }
    return result;
}

bool BitString::equals(const BitString& other) const {
    if (arraySize != other.arraySize) {
        return false;
    }

    for (size_t i = 0; i < arraySize; ++i) {
        if (bitArray[i] != other.bitArray[i]) {
            return false;
        }
    }
    return true;
}

std::string BitString::toString() const {
    std::string result;
    for (size_t i = 0; i < arraySize; ++i) {
        result += (bitArray[i] == 1) ? '1' : '0';
    }
    return result;
}