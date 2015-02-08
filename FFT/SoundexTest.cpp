#include "gmock/gmock.h"    //<label id="code.include"/>
#include "Soundex.h"

using namespace testing;

class SoundexEncoding: public testing::Test {
    public:
        Soundex soundex;
};

TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord) {
    auto encoded = soundex.encode("A");
    ASSERT_THAT(encoded, Eq("A000"));
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits) {
    auto encoded = soundex.encode("I");
    ASSERT_THAT(encoded, Eq("I000"));
}

TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits) {
    ASSERT_THAT(soundex.encode("Ax"), Eq("A200"));
}

TEST_F(SoundexEncoding, IgnoresNonAlphabetics) {
    ASSERT_THAT(soundex.encode("A#"), Eq("A000"));
}
