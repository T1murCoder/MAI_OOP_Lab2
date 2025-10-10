#pragma once

#include <initializer_list>
#include <string>

class BitString {
public:
    BitString();
    BitString(const size_t& arraySize, unsigned char defaultValue = 0);
    BitString(const std::initializer_list<unsigned char>& initialValues);
    BitString(const std::string& sourceString);

    BitString(const BitString& other); // копирующий конструктор (правило пяти)
    BitString(BitString&& other); // перемещающий конструктор (правило пяти)
    virtual ~BitString() noexcept; // деструктор (правило пяти)
    // тут еще не хватает до правила пяти копирующего и перемащающего оператора присваивания

    BitString bitAnd(const BitString& other) const;
    BitString bitOr(const BitString& other) const;
    BitString bitXor(const BitString& other) const;
    BitString bitNot() const;

    bool equals(const BitString& other) const;
    // bool less(const BitString& other) const;
    // bool greater(const BitString& other) const;
    std::string toString() const;
private:
    size_t arraySize;
    unsigned char* bitArray;
};