#include"ser.hxx"
#include"../message.hxx"
#include<iostream>
#include<memory>
#include<assert.h>
using namespace std;

int main(void) {
    cout << __FILE_NAME__ << endl;

    {
        cout << "Test #1" << endl;

        serializator ser;
        unique_ptr<message> msg{new command(1001)};

        std::string ser_msg{ser.serialize(msg.get())};
        auto deser_msg{ser.deserialize(ser_msg)};

        assert(1001 == dynamic_cast<const command*>(deser_msg.get())->_value);
    }
}
