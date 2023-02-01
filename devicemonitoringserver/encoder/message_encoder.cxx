#include "message_encoder.hxx"
#include "base_encoder.hxx"

message_encoder::message_encoder(base_encoder* encoder)
    : main_encoder{nullptr} {
    register_encoder(encoder);
    choose_encoder(encoder->name());
}

void message_encoder::register_encoder(base_encoder* encoder) {
    encoder_table[encoder->name()]= encoder;
}

void message_encoder::choose_encoder(const std::string& name) {
    main_encoder = encoder_table[name];
}

std::string message_encoder::encode(const std::string& message) const {
    return main_encoder->encode(message);
}

std::string message_encoder::decode(const std::string& message) const {
    return main_encoder->decode(message);
}

std::string message_encoder::curr_encoder_name(void) const {
    return main_encoder->name();
}
