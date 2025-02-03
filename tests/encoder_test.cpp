#include "encoder.h"
#include <gtest/gtest.h>

class EncoderTest : public ::testing::Test {
protected:
    Encoder encoder;
};

TEST(EncoderTest, EncodeEmptyString) {
    Encoder encoder;
    std::wstring src = L"";
    std::wstring key = L"key";
    std::wstring dest;
    EXPECT_EQ(encoder.encodeStringByKey(src, key, dest), STATUS_SUCCESS);
    EXPECT_TRUE(dest.empty());
}

TEST(EncoderTest, EncodeWithEmptyKey) {
    Encoder encoder;
    std::wstring src = L"hello";
    std::wstring key = L"";
    std::wstring dest;
    EXPECT_EQ(encoder.encodeStringByKey(src, key, dest), STATUS_SUCCESS);
    EXPECT_EQ(dest, src);
}

TEST(EncoderTest, EncodeBasicString) {
    Encoder encoder;
    std::wstring src = L"test";
    std::wstring key = L"key";
    std::wstring dest;
    EXPECT_EQ(encoder.encodeStringByKey(src, key, dest), STATUS_SUCCESS);
    
    std::wstring decoded;
    EXPECT_EQ(encoder.decodeStringByKey(dest, key, decoded), STATUS_SUCCESS);
    EXPECT_EQ(decoded, src);
}

TEST(EncoderTest, DecodeEmptyString) {
    Encoder encoder;
    std::wstring src = L"";
    std::wstring key = L"key";
    std::wstring dest;
    EXPECT_EQ(encoder.decodeStringByKey(src, key, dest), STATUS_SUCCESS);
    EXPECT_TRUE(dest.empty());
}

TEST(EncoderTest, DecodeWithEmptyKey) {
    Encoder encoder;
    std::wstring src = L"hello";
    std::wstring key = L"";
    std::wstring dest;
    EXPECT_EQ(encoder.decodeStringByKey(src, key, dest), STATUS_SUCCESS);
    EXPECT_EQ(dest, src);
}

TEST(EncoderTest, EncodeLongStringShortKey) {
    Encoder encoder;
    std::wstring src = L"this is a long string";
    std::wstring key = L"key";
    std::wstring dest;
    EXPECT_EQ(encoder.encodeStringByKey(src, key, dest), STATUS_SUCCESS);
    
    std::wstring decoded;
    EXPECT_EQ(encoder.decodeStringByKey(dest, key, decoded), STATUS_SUCCESS);
    EXPECT_EQ(decoded, src);
}
