#include "../message/message.hxx"
#include "ser.hxx"
#include <assert.h>
#include <iostream>
#include <memory>

#include "../encoder/message_encoder.hxx"

using namespace std;

int
main(void) {
    cout << __FILE_NAME__ << endl;

    {
        cout << "Command, value[-100; 100]" << endl;
        const serializator ser{};

        for (std::int8_t value{-100}; value <= 100; value++) {
            const unique_ptr<const dms::message::message> msg{
                new const dms::message::command(value)};

            const std::string ser_msg{ser.serialize(msg.get())};
            const auto deser_msg = ser.deserialize(ser_msg);

            assert(deser_msg);
            assert(dms::message::MSG_TYPE::COMMAND == deser_msg->type());

            assert(value == dynamic_cast<const dms::message::command* const>(
                                deser_msg.get())
                                ->value());
        }
    }

    {
        cout << "Meterage, timestamp[0; 10000], value[0; 100]" << endl;
        const serializator ser{};

        for (std::int8_t value{0u}; value <= 100; value++) {
            for (std::uint64_t timestamp{0u}; timestamp <= 10000u;
                 timestamp++) {

                const unique_ptr<const dms::message::message> msg{
                    new const dms::message::meterage(timestamp, value)};

                const std::string ser_msg{ser.serialize(msg.get())};

                const std::unique_ptr<const dms::message::message> deser_msg{
                    ser.deserialize(ser_msg)};

                assert(deser_msg);
                assert(dms::message::MSG_TYPE::METERAGE ==
                       deser_msg.get()->type());

                assert(timestamp ==
                       dynamic_cast<const dms::message::meterage* const>(
                           deser_msg.get())
                           ->timestamp());

                assert(value ==
                       dynamic_cast<const dms::message::meterage* const>(
                           deser_msg.get())
                           ->value());
            }
        }
    }

    {
        cout << "Error: NOTIMESTAMP, NOSCHEDULE, OBSOLETE" << endl;

        {
            const dms::message::ERR_TYPE err{
                dms::message::ERR_TYPE::NOSCHEDULE};

            const serializator ser{};

            const unique_ptr<const dms::message::message> msg{
                new const dms::message::error(err)};

            const std::string ser_msg{ser.serialize(msg.get())};

            const std::unique_ptr<const dms::message::message> deser_msg{
                ser.deserialize(ser_msg)};

            assert(deser_msg);
            assert(dms::message::MSG_TYPE::ERROR == deser_msg->type());
            assert(err == dynamic_cast<const dms::message::error* const>(
                              deser_msg.get())
                              ->err());
        }

        {
            const dms::message::ERR_TYPE err{
                dms::message::ERR_TYPE::NOTIMESTAMP};

            const serializator ser{};
            const unique_ptr<const dms::message::message> msg{
                new const dms::message::error(err)};

            const string ser_msg{ser.serialize(msg.get())};

            const unique_ptr<const dms::message::message> deser_msg{
                ser.deserialize(ser_msg)};

            assert(deser_msg);
            assert(dms::message::MSG_TYPE::ERROR == deser_msg->type());
            assert(err == dynamic_cast<const dms::message::error* const>(
                              deser_msg.get())
                              ->err());
        }

        {
            const dms::message::ERR_TYPE err{dms::message::ERR_TYPE::OBSOLETE};

            const serializator ser{};
            const unique_ptr<const dms::message::message> msg{
                new const dms::message::error(err)};

            const std::string ser_msg{ser.serialize(msg.get())};
            const auto deser_msg = ser.deserialize(ser_msg);

            assert(deser_msg);
            assert(dms::message::MSG_TYPE::ERROR == deser_msg->type());

            assert(err == dynamic_cast<const dms::message::error* const>(
                              deser_msg.get())
                              ->err());
        }
    }

    {
        cout << "Command, mirror, value[-100; 100]" << endl;

        const serializator ser{};
        const message_encoder menc{ENC_TYPE::MIRR};

        for (std::int8_t corr_val{-100}; corr_val <= 100; corr_val++) {

            const std::unique_ptr<const dms::message::message> msg{
                new const dms::message::command(corr_val)};

            const std::string ser_msg{ser.serialize(msg.get())};

            // сообщение шифруется
            const std::string enc_ser_msg{menc.encode(ser_msg)};

            // сообщение расшифровывается
            const std::string denc_ser_msg{menc.decode(enc_ser_msg)};

            // f(f^-1(x)) =?= x
            assert(denc_ser_msg == ser_msg);

            const std::unique_ptr<const dms::message::message> deser_msg{
                ser.deserialize(denc_ser_msg)};

            assert(deser_msg);
            assert(dms::message::MSG_TYPE::COMMAND == deser_msg->type());

            assert(corr_val ==
                   dynamic_cast<const dms::message::command*>(deser_msg.get())
                       ->value());
        }
    }

    {
        cout << "Command, mul41, value[-100; 100]" << endl;

        const serializator ser{};
        const message_encoder menc{ENC_TYPE::MUL41};

        for (std::int8_t corr_val{-100}; corr_val <= 100; corr_val++) {

            const std::unique_ptr<const dms::message::message> msg{
                new const dms::message::command(corr_val)};

            const std::string ser_msg{ser.serialize(msg.get())};

            // сообщение шифруется
            const std::string enc_ser_msg{menc.encode(ser_msg)};

            // сообщение расшифровывается
            const std::string denc_ser_msg{menc.decode(enc_ser_msg)};

            // f(f^-1(x)) =?= x
            assert(denc_ser_msg == ser_msg);

            const std::unique_ptr<const dms::message::message> deser_msg{
                ser.deserialize(denc_ser_msg)};

            assert(deser_msg);
            assert(dms::message::MSG_TYPE::COMMAND == deser_msg->type());

            assert(corr_val ==
                   dynamic_cast<const dms::message::command*>(deser_msg.get())
                       ->value());
        }
    }

    // команда под шифром rot3
    {
        cout << "Command, rot3, value[-100, 100]" << endl;

        const serializator ser{};
        const message_encoder menc{ENC_TYPE::ROT3};

        for (std::int8_t corr_val{-100}; corr_val <= 100; corr_val++) {

            const std::unique_ptr<const dms::message::message> msg{
                new const dms::message::command(corr_val)};

            const std::string ser_msg{ser.serialize(msg.get())};

            // сообщение шифруется
            const std::string enc_ser_msg{menc.encode(ser_msg)};

            // сообщение расшифровывается
            const std::string denc_ser_msg{menc.decode(enc_ser_msg)};

            // f(f^-1(x)) =?= x
            assert(denc_ser_msg == ser_msg);

            const std::unique_ptr<const dms::message::message> deser_msg{
                ser.deserialize(denc_ser_msg)};

            assert(deser_msg);
            assert(dms::message::MSG_TYPE::COMMAND == deser_msg->type());

            assert(corr_val ==
                   dynamic_cast<const dms::message::command*>(deser_msg.get())
                       ->value());
        }
    }
}
