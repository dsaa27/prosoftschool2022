#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H
#include <string>
#include <vector>
#include <unordered_map>
constexpr uint8_t maxKeySize = 10;

class MessageEncoder;

class BaseEncoderExecutor {
public:
    BaseEncoderExecutor(const std::string& name): m_name(name) {};
    virtual ~BaseEncoderExecutor() = default;

    virtual std::string encode(const std::string& input) = 0;
    virtual std::string decode(const std::string& input) = 0;

    std::string name() const {
        return m_name;
    };

protected:
    int toInt(const char& charToInt);

private:
    std::string m_name;
};

class EncoderROT3 final: public BaseEncoderExecutor {
public:
    EncoderROT3(): BaseEncoderExecutor("ROT3") {};

    std::string encode(const std::string& input);
    std::string decode(const std::string& input);
};

class EncoderMirror final: public BaseEncoderExecutor {
public:
    EncoderMirror(): BaseEncoderExecutor("Mirror") {};

    std::string encode(const std::string& input);
    std::string decode(const std::string& input);
};


class EncoderMultiply41 final: public BaseEncoderExecutor {
public:
    EncoderMultiply41(): BaseEncoderExecutor("Multiply41") {};

    std::string encode(const std::string& input);
    std::string decode(const std::string& input);
};

class EncoderCustom final: public BaseEncoderExecutor {
public:
    EncoderCustom(const std::string& name): BaseEncoderExecutor(name) {};

    std::string encode (const std::string& input);
    std::string decode(const std::string& input);
    void setkey(const std::string& inputkey);

private:
    std::vector<char> key{'X', 'O', 'R'};
};

class MessageEncoder {

public:
    ~MessageEncoder();

    std::string proceedEncoding(const std::string& input);
    std::string proceedDecoding(const std::string& input);
    void selectMethod(const std::string& name);
    void registerСustom(const std::string& name, const std::string& key);
    std::string getName() const;

private:
    void deselect();

private:
    BaseEncoderExecutor *m_encoderexecutor = nullptr;
    std::unordered_map<std::string, BaseEncoderExecutor*> m_encoderExecutors;

};

#endif // MESSAGEENCODER_H
