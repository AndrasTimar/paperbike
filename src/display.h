#ifndef DISPLAY_H
#define DISPLAY_H

void setupDisplay();
void displayText(String text, int x = 2, int y = 40, bool refreshScreen = true);
void clearScreen(bool refreshScreen = true);
#endif