#pragma once

// #if defined(LILYGO_T5_V213)

#ifndef EPD_MOSI
#define EPD_MOSI                (23)
#define EPD_MISO                (-1)
#define EPD_SCLK                (18)
#define EPD_CS                  (5)

#define EPD_BUSY                (4)
#define EPD_RSET                (16)
#define EPD_DC                  (17)

#define SDCARD_CS               (13)
#define SDCARD_MOSI             (15)
#define SDCARD_MISO             (2)
#define SDCARD_SCLK             (14)

#define BUTTON_1                (39)
#define BUTTONS                 {39}

#define BUTTON_COUNT            (1)

#define LED_PIN                 (19)
#define LED_ON                  (LOW)

#define BATTERY_ADC_PIN         (35)

#define SCREEN_WIDTH            (250)
#define SCREEN_HEIGHT           (120)
#define UNUSABLE_TOP_HEIGHT     (8)

#define GPS_RX_PIN              (15)
#define GPS_TX_PIN              (14)

#define DEBUG_MODE              false

#define _HAS_ADC_DETECTED_
#define _HAS_LED_
#define _HAS_SDCARD_
#endif
// #else
// #error "Please select model !!!"
// #endif