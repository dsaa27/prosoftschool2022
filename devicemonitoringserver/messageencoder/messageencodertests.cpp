#include "messageencodertests.h"
#include "messageencoder.h"
#include "test_runner.h"
#include <algorithm>
#include "common.h"

void assertStrVectors(std::vector<std::string> fstVector, std::vector<std::string> sndVector)
{
    int fstVectorLen = fstVector.size();
    ASSERT_EQUAL(fstVectorLen, sndVector.size());
    sort(fstVector.begin(), fstVector.end());
    sort(sndVector.begin(), sndVector.end());
    for(int i = 0; i < fstVectorLen; ++i)
        ASSERT_EQUAL(fstVector[i], sndVector[i]);
}

void messageEncoderTest()
{
    class TestExecutor final : public BaseEncoderExecutor
    {
    public:
        std::string encode(const std::string& message) const final
        {
            UNUSED(message);
            return "encode";
        }

        std::string decode(const std::string& message) const final
        {
            UNUSED(message);
            return "decode";
        }

        std::string getName() const final
        {
            return "test";
        }
    };

    MessageEncoder encoder;
    std::vector<std::string> executorsName {"Mirror", "Multiply41", "ROT3"};
    std::string str_out;

    ASSERT(!encoder.encode("abc", str_out));
    ASSERT(!encoder.decode("abc", str_out));
    ASSERT(!encoder.getAlgName(str_out));
    assertStrVectors(encoder.getAllAlgNames(), executorsName);

    ASSERT(encoder.addAlgorithm(new TestExecutor()));
    TestExecutor* testExec = new TestExecutor();
    ASSERT(!encoder.addAlgorithm(testExec));
    delete testExec;
    ASSERT(!encoder.encode("abc", str_out));
    ASSERT(!encoder.decode("abc", str_out));
    ASSERT(!encoder.getAlgName(str_out));
    executorsName.push_back("test");
    assertStrVectors(encoder.getAllAlgNames(), executorsName);

    ASSERT(encoder.setAlgorithm("test"));
    ASSERT(encoder.getAlgName(str_out));
    ASSERT_EQUAL(str_out, "test");
    ASSERT(encoder.encode("abc", str_out));
    ASSERT_EQUAL(str_out, "encode");
    ASSERT(encoder.decode("abc", str_out));
    ASSERT_EQUAL(str_out, "decode");
    assertStrVectors(encoder.getAllAlgNames(),executorsName);
}
