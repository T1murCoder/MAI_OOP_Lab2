#include <gtest/gtest.h>
#include "../include/bit_string.h"
#include <stdexcept>

// Тесты для конструкторов
TEST(BitStringConstructorTest, DefaultConstructor) {
    BitString bs;
    EXPECT_EQ(bs.getSize(), 0);
    EXPECT_EQ(bs.toString(), "");
}

TEST(BitStringConstructorTest, SizeConstructor) {
    BitString bs(5, 0);
    EXPECT_EQ(bs.getSize(), 5);
    EXPECT_EQ(bs.toString(), "00000");

    BitString bs2(3, 1);
    EXPECT_EQ(bs2.getSize(), 3);
    EXPECT_EQ(bs2.toString(), "111");
}

TEST(BitStringConstructorTest, InitializerListConstructor) {
    BitString bs({0, 1, 0, 1});
    EXPECT_EQ(bs.getSize(), 4);
    EXPECT_EQ(bs.toString(), "0101");
}

TEST(BitStringConstructorTest, StringConstructor) {
    BitString bs("10110");
    EXPECT_EQ(bs.getSize(), 5);
    EXPECT_EQ(bs.toString(), "10110");
}

TEST(BitStringConstructorTest, CopyConstructor) {
    BitString original({1, 0, 1});
    BitString copy(original);
    
    EXPECT_EQ(copy.getSize(), original.getSize());
    EXPECT_EQ(copy.toString(), original.toString());
    
    // Проверяем, что это действительно копия (изменения оригинала не влияют на копию)
    BitString modified = original.add(BitString({1}));
    EXPECT_NE(modified.toString(), copy.toString());
}

TEST(BitStringConstructorTest, MoveConstructor) {
    BitString original({1, 0, 1});
    std::string originalStr = original.toString();
    size_t originalSize = original.getSize();
    
    BitString moved(std::move(original));
    
    EXPECT_EQ(moved.getSize(), originalSize);
    EXPECT_EQ(moved.toString(), originalStr);
}

// Тесты для арифметических операций
TEST(BitStringOperationsTest, Add) {
    BitString bs1({1, 0, 1});
    BitString bs2({0, 1});
    
    BitString result = bs1.add(bs2);
    EXPECT_EQ(result.getSize(), bs1.getSize() + bs2.getSize());
    EXPECT_EQ(result.toString(), "10101");
}

TEST(BitStringOperationsTest, Subtract) {
    BitString bs1({1, 0, 1, 1, 0});
    BitString bs2({0, 1});
    
    BitString result = bs1.subtract(bs2);
    EXPECT_EQ(result.getSize(), bs1.getSize() - bs2.getSize());
    EXPECT_EQ(result.toString(), "101");
    
    // Проверка на ошибку при вычитании большего из меньшего
    BitString bs3({1});
    BitString bs4({1, 0});
    
    EXPECT_THROW(bs3.subtract(bs4), std::logic_error);
}

// Тесты для битовых операций
TEST(BitStringBitwiseTest, BitAnd) {
    BitString bs1({1, 0, 1, 1});
    BitString bs2({1, 1, 0, 0});
    
    BitString result = bs1.bitAnd(bs2);
    EXPECT_EQ(result.toString(), "1000");
    
    // Проверка на исключение при разных длинах
    BitString bs3({1, 0, 1});
    BitString bs4({1, 1});
    
    EXPECT_THROW(bs3.bitAnd(bs4), std::invalid_argument);
}

TEST(BitStringBitwiseTest, BitOr) {
    BitString bs1({1, 0, 1, 1});
    BitString bs2({1, 1, 0, 0});
    
    BitString result = bs1.bitOr(bs2);
    EXPECT_EQ(result.toString(), "1111");
    
    // Проверка на исключение при разных длинах
    BitString bs3({1, 0, 1});
    BitString bs4({1, 1});
    
    EXPECT_THROW(bs3.bitOr(bs4), std::invalid_argument);
}

TEST(BitStringBitwiseTest, BitXor) {
    BitString bs1({1, 0, 1, 1});
    BitString bs2({1, 1, 0, 0});
    
    BitString result = bs1.bitXor(bs2);
    EXPECT_EQ(result.toString(), "0111");
    
    // Проверка на исключение при разных длинах
    BitString bs3({1, 0, 1});
    BitString bs4({1, 1});
    
    EXPECT_THROW(bs3.bitXor(bs4), std::invalid_argument);
}

TEST(BitStringBitwiseTest, BitNot) {
    BitString bs({1, 0, 1, 1});
    
    BitString result = bs.bitNot();
    EXPECT_EQ(result.toString(), "0100");
}

// Тесты для операций сравнения
TEST(BitStringComparisonTest, Equals) {
    BitString bs1({1, 0, 1, 1});
    BitString bs2({1, 0, 1, 1});
    BitString bs3({1, 0, 1, 0});
    
    EXPECT_TRUE(bs1.equals(bs2));
    EXPECT_FALSE(bs1.equals(bs3));
    
    // Разные длины
    BitString bs4({1, 0, 1});
    EXPECT_FALSE(bs1.equals(bs4));
}

TEST(BitStringComparisonTest, Less) {
    BitString bs1({0, 1, 1});
    BitString bs2({1, 0, 0});
    BitString bs3({0, 1, 1, 0});
    
    EXPECT_TRUE(bs1.less(bs2));
    EXPECT_FALSE(bs2.less(bs1));
    
    // Равные строки
    BitString bs4({0, 1, 1});
    EXPECT_FALSE(bs1.less(bs4));
    
    // Разные длины
    EXPECT_TRUE(bs1.less(bs3));
}

TEST(BitStringComparisonTest, Greater) {
    BitString bs1({1, 0, 1});
    BitString bs2({0, 1, 1});
    BitString bs3({1, 0, 1, 0});
    
    EXPECT_TRUE(bs1.greater(bs2));
    EXPECT_FALSE(bs2.greater(bs1));
    
    // Равные строки
    BitString bs4({1, 0, 1});
    EXPECT_FALSE(bs1.greater(bs4));
    
    // Разные длины
    EXPECT_FALSE(bs1.greater(bs3));
    EXPECT_TRUE(bs3.greater(bs1));
}

// Тесты для утилитарных методов
TEST(BitStringUtilityTest, ToString) {
    BitString bs1({1, 0, 1, 1, 0});
    EXPECT_EQ(bs1.toString(), "10110");
    
    BitString bs2;
    EXPECT_EQ(bs2.toString(), "");
}

TEST(BitStringUtilityTest, GetSize) {
    BitString bs1({1, 0, 1, 1, 0});
    EXPECT_EQ(bs1.getSize(), 5);
    
    BitString bs2;
    EXPECT_EQ(bs2.getSize(), 0);
    
    BitString bs3(10, 1);
    EXPECT_EQ(bs3.getSize(), 10);
}

// Тест на комбинирование операций
TEST(BitStringCombinationTest, CombinedOperations) {
    BitString bs1({1, 0, 1, 1});
    BitString bs2({1, 1, 0, 0});
    
    BitString andResult = bs1.bitAnd(bs2);
    BitString orResult = bs1.bitOr(bs2);
    BitString result = andResult.add(orResult);
    
    EXPECT_EQ(result.toString(), "10001111");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}