#ifndef TEST_ENUM_H
#define TEST_ENUM_H

class TestEnum{
public:
    static bool test_setName();
    static bool test_setNameWithSpaces();
    static bool test_setNameBadChars();
    static bool test_addSingleValue();
    static bool test_addMultipleValues();

    //Generator tests
    static bool test_generate1();
};

#endif /* TEST_ENUM_H */
