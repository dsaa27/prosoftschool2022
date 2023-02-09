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

        const serializator ser{};
        const unique_ptr<const message> msg{new command(1001)};

        const std::string ser_msg{ser.serialize(msg.get())};
        const auto deser_msg = ser.deserialize(ser_msg);

        assert(deser_msg);
        assert(MSG_TYPE::COMMAND == deser_msg->type());
        assert(1001 ==
               dynamic_cast<const command* const>(deser_msg.get())->_value);
    }

    {
        cout << "Test #2" << endl;
        const std::uint64_t timestamp{1234567890u}, value{987654321u};

        const serializator ser{};
        const unique_ptr<const message> msg{new meterage(timestamp, value)};

        const auto ser_msg = ser.serialize(msg.get());
        const auto deser_msg = ser.deserialize(ser_msg);

        assert(deser_msg);
        assert(MSG_TYPE::METERAGE == deser_msg.get()->type());

        assert(
            timestamp ==
            dynamic_cast<const meterage* const>(deser_msg.get())->_timestamp);

        assert(value ==
               dynamic_cast<const meterage* const>(deser_msg.get())->_value);
    }

    {
        cout << "Test #3" << endl;
        const ERR_TYPE err{ERR_TYPE::NOSCHEDULE};

        const serializator ser{};
        const unique_ptr<const message> msg{new error(err)};

        const std::string ser_msg{ser.serialize(msg.get())};
        const auto deser_msg = ser.deserialize(ser_msg);

        assert(deser_msg);
        assert(MSG_TYPE::ERROR == deser_msg->type());
        assert(err == dynamic_cast<const error* const>(deser_msg.get())->_err);
    }
}
