#include "../test_runner.h"
#include "unittest.h"
#include "../clientservercomponents/messageencoder.h"

#include <vector>

void unitTest::codeAlgorithm::ROT3Code()
{
    MessageEncoder messageEncoder;
    ASSERT(messageEncoder.chooseCodingAlgorithm("ROT3"));

    std::vector<std::string> origin = {"Longdog6", "Timer", "EasyLimon"};
    std::vector<std::string> expectedEncoded = {"Orqjgrj9", "Wlphu", "Hdv|Olprq"};
    std::vector<std::string> expectedDecoded = origin;
    std::vector<std::string> encoded;
    std::vector<std::string> decoded;

    for (const auto &now : origin)
        encoded.push_back(messageEncoder.encode(now));

    ASSERT_EQUAL(encoded, expectedEncoded);

    for (const auto &now : encoded)
        decoded.push_back(messageEncoder.decode(now));

    ASSERT_EQUAL(decoded, expectedDecoded);
}

void unitTest::codeAlgorithm::MirrorCode()
{
    MessageEncoder messageEncoder;
    ASSERT(messageEncoder.chooseCodingAlgorithm("Mirror"));

    std::string origin = {(char)100,
                          (char)86,
                          (char)87,
                          (char)101,
                          (char)125,
                          (char)44,
                          (char)9,
                          (char)111,
                          (char)10};
    std::string expectedEncoded = "001 68 78 101 521 44 9 111 01";
    std::string expectedDecoded = origin;
    std::string encoded;
    std::string decoded;

    encoded = messageEncoder.encode(origin);

    ASSERT_EQUAL(encoded, expectedEncoded);

    decoded = messageEncoder.decode(encoded);

    ASSERT_EQUAL(decoded, expectedDecoded);
}

void unitTest::codeAlgorithm::Multiply41Code()
{
    MessageEncoder messageEncoder;
    ASSERT(messageEncoder.chooseCodingAlgorithm("Multiply41"));

    std::string origin = {(char)100,
                          (char)86,
                          (char)87,
                          (char)101,
                          (char)125,
                          (char)44,
                          (char)9,
                          (char)111,
                          (char)10};
    std::string expectedEncoded = "4100 3526 3567 4141 5125 1804 369 4551 410";
    std::string expectedDecoded = origin;
    std::string encoded;
    std::string decoded;

    encoded = messageEncoder.encode(origin);

    ASSERT_EQUAL(encoded, expectedEncoded);

    decoded = messageEncoder.decode(encoded);

    ASSERT_EQUAL(decoded, expectedDecoded);

}

void unitTest::codeAlgorithm::MixedCodeAlgorithms()
{
    MessageEncoder messageEncoder;

    std::string origin = "Mary might have been waiting outside for you...";
    std::string decoded;
    std::string encoded;
    std::string expectedDecoded = origin;

    messageEncoder.chooseCodingAlgorithm("ROT3");
    encoded = messageEncoder.encode(origin);
    decoded = messageEncoder.decode(encoded);
    ASSERT_EQUAL(decoded, expectedDecoded);

    messageEncoder.chooseCodingAlgorithm("Mirror");
    encoded = messageEncoder.encode(origin);
    decoded = messageEncoder.decode(encoded);
    ASSERT_EQUAL(decoded, expectedDecoded);

    messageEncoder.chooseCodingAlgorithm("Multiply41");
    encoded = messageEncoder.encode(origin);
    decoded = messageEncoder.decode(encoded);
    ASSERT_EQUAL(decoded, expectedDecoded);
}

void unitTest::codeAlgorithm::inductiveEncoding()
{
    MessageEncoder messageEncoder;

    std::string origin = "380asdjklfj2mu2j f8sdufpoiwjoiq38fu98asj aosiudf oiasdmfp oiausdf8j2l3kr mj";
    std::string decoded;
    std::string transitive;

    messageEncoder.chooseCodingAlgorithm("ROT3");
    transitive = messageEncoder.encode(origin); // (
    messageEncoder.chooseCodingAlgorithm("Mirror");
    transitive = messageEncoder.encode(transitive); // ({
    transitive = messageEncoder.encode(transitive); // ({{
    transitive = messageEncoder.decode(transitive); // ({{}
    messageEncoder.chooseCodingAlgorithm("ROT3");
    transitive = messageEncoder.encode(transitive); // ({{}(
    messageEncoder.chooseCodingAlgorithm("Multiply41");
    transitive = messageEncoder.encode(transitive); // ({{}([
    transitive = messageEncoder.decode(transitive); // ({{}([]
    messageEncoder.chooseCodingAlgorithm("Mirror");
    transitive = messageEncoder.encode(transitive); // ({{}([]{
    transitive = messageEncoder.decode(transitive); // ({{}([]{}
    messageEncoder.chooseCodingAlgorithm("ROT3");
    transitive = messageEncoder.decode(transitive); // ({{}([]{})
    messageEncoder.chooseCodingAlgorithm("Mirror");
    transitive = messageEncoder.decode(transitive); // ({{}([]{})}
    messageEncoder.chooseCodingAlgorithm("ROT3");
    decoded = messageEncoder.decode(transitive); // ({{}([]{}))
    ASSERT_EQUAL(decoded, origin);
}
