#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <boards.h>
#include <Arduino.h>
#include <font_prazo_9.h>

GxIO_Class io(SPI, EPD_CS, EPD_DC, EPD_RSET);
GxEPD_Class display(io, EPD_RSET, EPD_BUSY);

void setupDisplay() {
    SPI.begin(EPD_SCLK, EPD_MISO, EPD_MOSI);
    display.init();
}

void clearScreen(bool refreshScreen) {
    display.fillScreen(GxEPD_WHITE);
    if(refreshScreen) {
        display.update();
    }
    
}
void displayText(String text)
{  
    Serial.println("displayText");
    display.setRotation(1);
    display.setTextColor(GxEPD_BLACK);
    display.setFont(&prazo_Regular_29pt7b);
    display.setCursor(2, 80);
    display.println(text);
    display.update();
    Serial.println("displayText done");
}