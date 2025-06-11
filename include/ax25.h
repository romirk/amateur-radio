//
// Created by Romir Kulshrestha on 11/06/2025.
//

#ifndef AX25_H
#define AX25_H

#include "types.h"

// Sentry flag
#define AX25_FLAG               0b01111110u

// S frame control fields

// Receive ready
#define AX25_RR                 0b00u
// Receive not ready (TNC buffer full)
#define AX25_RNR                0b00u
// Reject (out of sequence/duplicate)
#define AX25_REJ                0b10u
// Selective reject (request retran_smission)
#define AX25_SREJ               0b11u

// U frame control fields

// Set Asynchronous Balanced Mode Extended
#define AX25_SABME              0b01111u
// Set Asynchronous Balanced Mode
#define AX25_SABM               0b00111u
// Disconnect
#define AX25_DISC               0b01000u
// Disconnect mode
#define AX25_DM                 0b00011u
// Unnumbered Acknowledge
#define AX25_UA                 0b01100u
// Frame Reject
#define AX25_FRMR               0b10001u
// Unnumbered Information
#define AX25_UI                 0b00000u
// Exchange Identification
#define AX25_XID                0b10111u
// Test
#define AX25_TEST               0b11100u

typedef struct ax25_state {
    // state vars
    u16 v_s;
    u16 v_a;
    u16 v_r;

    // config

    bool half_duplex: 1;
    bool modulo8: 1;
    u8 reject_mode: 2;
    u16 max_field_length_tx;
    u16 max_field_length_rx;
    u8 window_size_tx;
    u8 window_size_rx;
    u16 timeout;
    u8 max_retries;
} ax25_state;


typedef struct ax25_address {
    u8 destination[6];
    u8 ssid_dst;
    u8 source[6];
    u8 ssid_src;
} ax25_address;

typedef union ax25_control_8 {
    // physical representation in memory
    u8 raw;

    // frame type
    // 0 = information, 1 = supervisory/unnumbered
    bool meta: 1;

    struct {
        bool meta: 1;
        u8 n_s: 3;
        bool PF: 1;
        u8 n_r: 3;
    } information;

    // supervisory/unnumbered
    struct {
        bool meta: 1;
        bool type: 1;
        u8 lo: 2;
        bool PF: 1;
        u8 hi: 3;
    } su;
} ax25_control_8;

typedef union ax25_control {
    // physical representation in memory
    u16 raw;

    // frame type
    // 1 = supervisory, 0 = information
    bool meta: 1;

    // 8-bit version
    ax25_control_8 _8;

    struct {
        bool meta: 1;
        bool : 1;
        u8 s: 2;
        u8 : 4;
        bool PF: 1;
        u8 n_r: 7;
    } supervisory;

    struct {
        bool meta: 1;
        u8 n_s: 7;
        bool PF: 1;
        u8 n_r: 7;
    } information;
} ax25_control;

typedef union ax25_header {
    u8 raw[16];

    struct {
        ax25_address address;
        ax25_control control;
    } fields;
} ax25_header;

typedef struct ax25_footer {
    u16 fcs;
} ax25_footer;

typedef struct ax25_packet {
    ax25_header header;
    u8 *data;
    ax25_footer footer;
} ax25_packet;


ax25_state ax25_init();
ax25_packet ax25_encode(ax25_state *state, u8 *data);
ax25_packet ax25_decode(ax25_state *state, u8 *packet);

#endif //AX25_H
