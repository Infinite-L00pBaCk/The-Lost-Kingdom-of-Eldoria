#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

// Console color codes for Windows
enum class Color {
    BLACK = 0,
    DARK_BLUE = 1,
    DARK_GREEN = 2,
    DARK_CYAN = 3,
    DARK_RED = 4,
    DARK_MAGENTA = 5,
    DARK_YELLOW = 6,
    GRAY = 7,
    DARK_GRAY = 8,
    BLUE = 9,
    GREEN = 10,
    CYAN = 11,
    RED = 12,
    MAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

// Set console text color
void setColor(Color textColor);

// Reset console color to default (white on black)
void resetColor();

// Print text with a specific color
void colorPrint(const std::string& text, Color color);

// Print text with a specific color followed by newline
void colorPrintLn(const std::string& text, Color color);

// Typewriter effect — prints text character by character
void typewriter(const std::string& text, int delayMs = 25);

// Typewriter effect with color
void typewriterColor(const std::string& text, Color color, int delayMs = 25);

// Clear the console screen
void clearScreen();

// Print a decorative separator line
void printSeparator(char ch = '=', int length = 60, Color color = Color::DARK_CYAN);

// Print a boxed title
void printBoxedTitle(const std::string& title, Color color = Color::YELLOW);

// Print the game's ASCII art banner
void printBanner();

// Wait for the user to press Enter
void pressEnterToContinue();

// Get a validated integer input within a range [min, max]
int getValidInput(int min, int max);

// Get a string input (non-empty)
std::string getStringInput(const std::string& prompt);

// Get a yes/no input, returns true for yes
bool getYesNo(const std::string& prompt);

// Display a numbered menu and return the user's choice (1-indexed)
int displayMenu(const std::string& title, const std::vector<std::string>& options);

// Generate a random integer in range [min, max]
int randomInt(int min, int max);

// Pause for a given number of milliseconds
void sleepMs(int ms);

#endif // UTILS_H
