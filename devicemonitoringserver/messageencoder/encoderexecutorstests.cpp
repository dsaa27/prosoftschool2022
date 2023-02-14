#include "encoderexecutorstests.h"
#include "baseencoderexecutor.h"
#include "mirror.h"
#include "multiply41.h"
#include "rot3.h"
#include "test_runner.h"

#include <limits.h>

void runTestCase(const BaseEncoderExecutor* executor, const std::string& original, const std::string& encoded)
{
    std::string encodedActual = executor->encode(original);
    ASSERT_EQUAL(encodedActual, encoded);
    std::string decodedActual = executor->decode(encoded);
    ASSERT_EQUAL(decodedActual, original);
}

void mirrorEncoderExecutorTest()
{
    Mirror mirrorExec;
    ASSERT_EQUAL(mirrorExec.getName(), "Mirror");
    runTestCase(&mirrorExec, "abcd", "dcba");
    runTestCase(&mirrorExec, "", "");
    runTestCase(&mirrorExec, "1 2 3", "3 2 1");
    runTestCase(&mirrorExec, "a12 3b", "b3 21a");

}

void multiply41EncoderExecutorTest()
{
    Multiply41 multiply41Exec;
    ASSERT_EQUAL(multiply41Exec.getName(), "Multiply41");

    std::string msg = std::string({97, 49});
    std::string encoded = std::string({31, 9, 15, 89});    // 97 * 41 = 31 * 128 + 9
    runTestCase(&multiply41Exec, msg, encoded);            // 49 * 41 = 15 * 128 + 89

    msg = std::string({-65, 57});
    encoded = std::string({-20, -105, 18, 33});            // -65 * 41 = -20 * 128 + -105
    runTestCase(&multiply41Exec, msg, encoded);            //  57 * 41 =  18 * 128 + 33

}

void ROT3EncoderExecutorTest()
{
    ROT3 rot3Exec;
    ASSERT_EQUAL(rot3Exec.getName(), "ROT3");
    runTestCase(&rot3Exec, "0", "3");
    runTestCase(&rot3Exec, "abcd", "defg");
    runTestCase(&rot3Exec, "1 -2", "4#05");

    std::string msg = std::string({CHAR_MAX, CHAR_MIN});
    std::string encoded = std::string({CHAR_MIN + 2, CHAR_MIN + 3});
    runTestCase(&rot3Exec, msg, encoded);

}
