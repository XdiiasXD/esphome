#pragma once

// Font table for 4-tube display (legacy support)
static const uint16_t alphafonttable[] PROGMEM = {
    0x0000,                 // space
    0x0080,                 // 'upper .'
    0x2000,                 // 'lower .'
    0x4478,                 // '0'
    0x0060,                 // '1'
    0x0758,                 // '2'
    0x0770,                 // '3'
    0x4360,                 // '4'
    0x4730,                 // '5'
    0x4738,                 // '6'
    0x0070,                 // '7'
    0x4778,                 // '8'
    0x4770,                 // '9'
    0x4378,                 // 'A'
    0x2d70,                 // 'B'
    0x4418,                 // 'C'
    0x2c70,                 // 'D'
    0x4718,                 // 'E'
    0x4318,                 // 'F'
    0x4538,                 // 'G'
    0x4368,                 // 'H'
    0x2c10,                 // 'I'
    0x0478,                 // 'J'
    0x2806,                 // 'K'
    0x4408,                 // 'L'
    0x40ea,                 // 'M'
    0x40ec,                 // 'N'
    0x4478,                 // 'O'
    0x4358,                 // 'P'
    0x447c,                 // 'Q'
    0x435c,                 // 'R'
    0x0494,                 // 'S'
    0x2810,                 // 'T'
    0x4468,                 // 'U'
    0x500a,                 // 'V'
    0x506c,                 // 'W'
    0x1086,                 // 'X'
    0x0882,                 // 'Y'
    0x1412,                 // 'Z'
};

// Font table for 2-tube display (Seeed's mapping)
static const uint16_t g_display_font2[] PROGMEM = {
    0x4000,                 // '.'
    0x0000,                 // '/'   display nothing.
    0xa145,                 // '0'
    0x8001,                 // '1'
    0x3107,                 // '2'
    0xb007,                 // '3'
    0x9043,                 // '4'
    0xb046,                 // '5'
    0xb146,                 // '6'
    0x8005,                 // '7'
    0xb147,                 // '8'
    0xb047,                 // '9'
    0x9147,                 // 'A'
    0xb415,                 // 'B'
    0x2144,                 // 'C'
    0xa415,                 // 'D'
    0x3146,                 // 'E'
    0x1146,                 // 'F'
    0xb144,                 // 'G'
    0x9143,                 // 'H'
    0x2414,                 // 'I'
    0xA101,                 // 'J'
    0x0c18,                 // 'K'
    0x2140,                 // 'L'
    0x8169,                 // 'M'
    0x8961,                 // 'N'
    0xa145,                 // 'O'
    0x1147,                 // 'P'
    0xa945,                 // 'Q'
    0x1947,                 // 'R'
    0x2824,                 // 'S'
    0x0414,                 // 'T'
    0xa141,                 // 'U'
    0x8821,                 // 'V'
    0x8b41,                 // 'W'
    0x0a28,                 // 'X'
    0x0428,                 // 'Y'
    0x220c,                 // 'Z'
    0x0000,                 // illegal char
};

// Segment mapping for 2-tube display
static const uint16_t segments2Tubes[] = {
    0x4,    // A
    0x40,   // B
    0x20,   // C
    0x1,    // D
    0x8,    // E
    0x10,   // F
    0x2,    // G1
    0x1000, // G2
    0x2000, // H
    0x100,  // I
    0x200,  // J
    0x8000, // K
    0x800,  // L
    0x400   // M
};