#ifndef CAN_BUS_MANAGER_H
#define CAN_BUS_MANAGER_H

#include <Arduino.h>

#include <CAN_config.h>
#include <ESP32CAN.h>

class CanBusManager {
public:
    CanBusManager(CAN_device_t &can);
    ~CanBusManager();

    void init(CAN_speed_t can_speed, gpio_num_t tx, gpio_num_t rx);
    void activate_filter(uint16_t filter_id, bool ignore_last_2_bits);

    bool is_msg_available(CAN_frame_t &rx_frame);

    void print_can_msg(CAN_frame_t &rx_frame);

    void send_can_msg(CAN_frame_t can_frame);
    void send_can_msg(const uint8_t *data, const uint8_t nr_of_bytes, const uint32_t can_id);

private:
    CAN_device_t *p_CAN_cfg;
    CAN_filter_t p_filter;

};

#endif // CAN_BUS_MANAGER_H
