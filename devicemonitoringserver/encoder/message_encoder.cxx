#include "message_encoder.hxx"
#include "base_encoder.hxx"
#include "mirr/mirr.hxx"
#include "mul41/mul41.hxx"
#include "rot3/rot3.hxx"
#include <memory>

message_encoder::message_encoder(void)
    : _encoder_table{{dms::encoder::ENC_TYPE::MIRR,
                      std::make_shared<const dms::encoder::mirr>()},

                     {dms::encoder::ENC_TYPE::MUL41,
                      std::make_shared<const dms::encoder::mul41>()},

                     {dms::encoder::ENC_TYPE::ROT3,
                      std::make_shared<const dms::encoder::rot3>()}},

      _curr{_encoder_table[dms::encoder::ENC_TYPE::MIRR]} {
}

message_encoder::message_encoder(dms::encoder::ENC_TYPE et)
    : _encoder_table{{dms::encoder::ENC_TYPE::MIRR,
                      std::make_shared<const dms::encoder::mirr>()},

                     {dms::encoder::ENC_TYPE::MUL41,
                      std::make_shared<const dms::encoder::mul41>()},

                     {dms::encoder::ENC_TYPE::ROT3,
                      std::make_shared<const dms::encoder::rot3>()}},

      _curr{_encoder_table[et]} {
}

void
message_encoder::set_encoder(const dms::encoder::ENC_TYPE et) {
    _curr = _encoder_table[et];
}

std::string
message_encoder::encode(const std::string& data) const {
    return _curr->encode(data);
}

std::string
message_encoder::decode(const std::string& data) const {
    return _curr->decode(data);
}

// временно
dms::encoder::ENC_TYPE
message_encoder::curr_encoder(void) const {
    return _curr->name();
}
