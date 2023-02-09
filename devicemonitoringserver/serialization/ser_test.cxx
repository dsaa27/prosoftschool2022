#include "../message.hxx"
#include "ser.hxx"
#include <assert.h>
#include <iostream>
#include <memory>
using namespace std;

int main(void) {
    cout << __FILE_NAME__ << endl;

    {
        cout << "Test #1" << endl;

        serializator ser;
        unique_ptr<message> msg{new command(1001)};

        std::string ser_msg{ser.serialize(msg.get())};
        auto deser_msg{ser.deserialize(ser_msg)};

        assert(MSG_TYPE::COMMAND == deser_msg.get()->type());
        assert(1001 ==
               dynamic_cast<const command* const>(deser_msg.get())->_value);
    }

    {
        cout << "Test #2" << endl;

        const std::uint64_t timestamp{1234567890}, value{987654321};

        serializator ser;
        unique_ptr<message> msg{new meterage(timestamp, value)};

        std::string ser_msg{ser.serialize(msg.get())};

        auto deser_msg{ser.deserialize(ser_msg)};

        assert(MSG_TYPE::METERAGE == deser_msg.get()->type());
        assert(
            timestamp ==
            dynamic_cast<const meterage* const>(deser_msg.get())->_timestamp);
        assert(value ==
               dynamic_cast<const meterage* const>(deser_msg.get())->_value);
    }
}
