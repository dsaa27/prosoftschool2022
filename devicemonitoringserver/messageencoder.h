#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H
#define toInt(x) x-'0'
#define maxKeySize 10
#include <string>
#include <vector>

class MessageEncoder;

class BaseEncoderExecutor {
public:
    BaseEncoderExecutor(const std::string& name): m_name(name) {};
    virtual ~BaseEncoderExecutor() = default;

    virtual void encode(std::string& output, const std::string& input) = 0;
    virtual void decode(std::string& output, const std::string& input) = 0;

    std::string name() const {
        return m_name;
    };

private:
    std::string m_name;
};

class EncoderROT3 final: public BaseEncoderExecutor {
public:
    EncoderROT3(): BaseEncoderExecutor("ROT3") {};

    void encode(std::string& output, const std::string& input);
    void decode(std::string& output, const std::string& input);
};

class EncoderMirror final: public BaseEncoderExecutor {
public:
    EncoderMirror(): BaseEncoderExecutor("Mirror") {};

    void encode(std::string& output, const std::string& input);
    void decode(std::string& output, const std::string& input);
};


class EncoderMultiply41 final: public BaseEncoderExecutor {
public:
    EncoderMultiply41(): BaseEncoderExecutor("Multiply41") {};

    void encode(std::string& output, const std::string& input);
    void decode(std::string& output, const std::string& input);
};

class EncoderCustom final: public BaseEncoderExecutor {
public:
    EncoderCustom(): BaseEncoderExecutor("Custom") {};

    void encode (std::string& output, const std::string& input);
    void decode(std::string& output, const std::string& input);
    void setkey(const std::string& inputkey);

private:
    std::vector<char> key{'X', 'O', 'R'};
};

enum Methods{
    ROT3,
    Mirror,
    Multiply41,
    Custom
};

class MessageEncoder {
private:
    BaseEncoderExecutor *m_encoderexecutor = nullptr;

public:
    ~MessageEncoder() {
        if (m_encoderexecutor) delete m_encoderexecutor;
    };


    void proceedEncoding(std::string& output, const std::string& input);
    void proceedDecoding(std::string& output, const std::string& input);
    void selectMethod(Methods m_method);
    void deselect();
    void registerСustom(const std::string& inputkey);
    std::string getName() const;

};

#endif // MESSAGEENCODER_H
