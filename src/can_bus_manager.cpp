#include <can_bus_manager.h>

CanBusManager::CanBusManager(CAN_device_t &can)  {
    p_CAN_cfg = &can;
}

CanBusManager::~CanBusManager() {
    delete p_CAN_cfg;
    p_CAN_cfg = nullptr;
}

void CanBusManager::init(CAN_speed_t can_speed, gpio_num_t tx, gpio_num_t rx) {
    p_CAN_cfg->speed = can_speed;
    p_CAN_cfg->tx_pin_id = tx;
    p_CAN_cfg->rx_pin_id = rx;
    p_CAN_cfg->rx_queue = xQueueCreate(10, sizeof(CAN_frame_t));

    ESP32Can.CANInit();
}

/**
 * @brief Set CAN Filter
    See in the SJA1000 Datasheet chapter "6.4.15 Acceptance filter"
    ACR0 + ACR1 are building the filter starting with ACR0
    4 least significant bits [0-3] of ACR1 and ACR3 are not used.
    bit 4 of ACR1 = RCT = 0
 * @example CAN_ID = 1551 -> 0b_0110_0000_1111 -> 0b_110_0000_1111 -> 0b_1100_0001_111 -> ACR0: 0b1100_0001  ACR1: 0b_111
 * @param filter_id value between 0-2031 to filter for a single incoming can_id
 * 
**/
void CanBusManager::activate_filter(uint16_t filter_id, bool ignore_last_2_bits) {
    CAN_filter_t p_filter;
    p_filter.FM = Single_Mode;

    uint16_t acr0_acr1 = 0b0000000000001111;
    acr0_acr1 |= ((filter_id & 0x7FF) << 5);

    p_filter.FM = Single_Mode;

    p_filter.ACR0 = acr0_acr1 >> 8;
    p_filter.ACR1 = (acr0_acr1 & 0xFF);
    p_filter.ACR2 = 0;
    p_filter.ACR3 = 0;

    // set bits in AMR to decide which bits of ACR are relevant. AMR1 and AMR0 correspond to ACR1 and ACR0.
    // [0-3] of AMR1 and AMR3 are not used
    // 0 = relevant
    // 1 = do not care
    p_filter.AMR0 = 0x00;
    if (ignore_last_2_bits) {
        p_filter.AMR1 = 0x7f; //ignore the last 3 bits of ACR (e.g.: also allows 1441-1443 if the id is 1440)
    } else {
        p_filter.AMR1 = 0x0f;
    }
    p_filter.AMR2 = 0xff;
    p_filter.AMR3 = 0xff;

    log_i("ACR0, ACR1: %x  %x", p_filter.ACR0, p_filter.ACR1);

    ESP32Can.CANConfigFilter(&p_filter);
}

bool CanBusManager::is_msg_available(CAN_frame_t &rx_frame) {
    // receive next CAN frame from queue
    return xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) == pdTRUE;
}

void CanBusManager::send_can_msg(CAN_frame_t can_frame) {
    ESP32Can.CANWriteFrame(&can_frame);
}

void CanBusManager::send_can_msg(const uint8_t *data, const uint8_t nr_of_bytes, const uint32_t can_id) {
    CAN_frame_t tx_frame;
    tx_frame.FIR.B.FF = CAN_frame_std;
    tx_frame.MsgID = can_id;
    tx_frame.FIR.B.DLC = nr_of_bytes;
    tx_frame.FIR.B.RTR = CAN_no_RTR;
    for (uint8_t i = 0; i < nr_of_bytes; i++) {
        tx_frame.data.u8[i] = data[i];
    }
    ESP32Can.CANWriteFrame(&tx_frame);
}

void CanBusManager::print_can_msg(CAN_frame_t &rx_frame) {
    log_i("ID: [%d]  (Std/Ext: [%c]  Rtr: [%c]) ->  [%c]   [%c]   [%c]   [%c]   [%c]   [%c]   [%c]   [%c]",
    rx_frame.MsgID,
    (rx_frame.FIR.B.FF == CAN_frame_std) ? 'S' : 'E',
    (rx_frame.FIR.B.RTR == CAN_frame_std) ? 'R' : ' ',
    (char)rx_frame.data.u8[0], (char)rx_frame.data.u8[1], (char)rx_frame.data.u8[2], (char)rx_frame.data.u8[3],
    (char)rx_frame.data.u8[4], (char)rx_frame.data.u8[5], (char)rx_frame.data.u8[6], (char)rx_frame.data.u8[7]);

    // if (rx_frame.FIR.B.FF == CAN_frame_std) {
    // log_i("Received standard can frame");
    // } else {
    //     log_i("Received extended can frame");
    // }
    // if (rx_frame.FIR.B.RTR == CAN_RTR) {
    //     printf(" RTR from 0x%08x, DLC %d\r\n", rx_frame.MsgID, rx_frame.FIR.B.DLC);
    // } else {
    //     printf(" from 0x%08x, DLC %d\n", rx_frame.MsgID, rx_frame.FIR.B.DLC);
    // }
}