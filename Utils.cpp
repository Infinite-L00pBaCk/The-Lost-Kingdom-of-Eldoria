#include "Utils.h"
#include <iostream>
#include <chrono>
#include <random>
#include <limits>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif

// ─── Console Color ──────────────────────────────────────────────────────────

void setColor(Color textColor) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>(textColor));
#endif
}

void resetColor() {
    setColor(Color::WHITE);
}

void colorPrint(const std::string& text, Color color) {
    setColor(color);
    std::cout << text;
    resetColor();
}

void colorPrintLn(const std::string& text, Color color) {
    setColor(color);
    std::cout << text << "\n";
    resetColor();
}

// ─── Typewriter Effect ──────────────────────────────────────────────────────

void typewriter(const std::string& text, int delayMs) {
    for (char c : text) {
        std::cout << c << std::flush;
        Sleep(delayMs);
    }
    std::cout << "\n";
}

void typewriterColor(const std::string& text, Color color, int delayMs) {
    setColor(color);
    for (char c : text) {
        std::cout << c << std::flush;
        Sleep(delayMs);
    }
    std::cout << "\n";
    resetColor();
}

// ─── Screen Utilities ───────────────────────────────────────────────────────

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printSeparator(char ch, int length, Color color) {
    setColor(color);
    for (int i = 0; i < length; i++) {
        std::cout << ch;
    }
    std::cout << "\n";
    resetColor();
}

void printBoxedTitle(const std::string& title, Color color) {
    int len = static_cast<int>(title.length());
    int boxWidth = len + 6;

    setColor(color);
    // Top border
    std::cout << "+";
    for (int i = 0; i < boxWidth - 2; i++) std::cout << "-";
    std::cout << "+\n";

    // Title line
    std::cout << "|  " << title << "  |\n";

    // Bottom border
    std::cout << "+";
    for (int i = 0; i < boxWidth - 2; i++) std::cout << "-";
    std::cout << "+\n";
    resetColor();
}

void printBanner() {
    setColor(Color::YELLOW);
    std::cout << "\n";
    std::cout << "  +================================================+\n";
    std::cout << "  |                                                |\n";
    std::cout << "  |        THE LOST KINGDOM OF ELDORIA             |\n";
    std::cout << "  |                                                |\n";
    std::cout << "  +================================================+\n";
    std::cout << "\n";

    setColor(Color::DARK_CYAN);
    std::cout << "      _____ _            _              _   \n";
    std::cout << "     |_   _| |__   ___  | |    ___  ___| |_ \n";
    std::cout << "       | | | '_ \\ / _ \\ | |   / _ \\/ __| __|\n";
    std::cout << "       | | | | | |  __/ | |__| (_) \\__ \\ |_ \n";
    std::cout << "       |_| |_| |_|\\___| |_____\\___/|___/\\__|\n";
    std::cout << "\n";

    setColor(Color::YELLOW);
    std::cout << "      _  ___                 _                \n";
    std::cout << "     | |/ (_)_ __   __ _  __| | ___  _ __ ___\n";
    std::cout << "     | ' /| | '_ \\ / _` |/ _` |/ _ \\| '_ ` _ \\\n";
    std::cout << "     | . \\| | | | | (_| | (_| | (_) | | | | | |\n";
    std::cout << "     |_|\\_\\_|_| |_|\\__, |\\__,_|\\___/|_| |_| |_|\n";
    std::cout << "                   |___/                      \n";
    std::cout << "\n";

    setColor(Color::GREEN);
    std::cout << "           ___   __   _____ _     _            _       \n";
    std::cout << "          / _ \\ / _| | ____| | __| | ___  _ __(_) __ _ \n";
    std::cout << "         | | | | |_  |  _| | |/ _` |/ _ \\| '__| |/ _` |\n";
    std::cout << "         | |_| |  _| | |___| | (_| | (_) | |  | | (_| |\n";
    std::cout << "          \\___/|_|   |_____|_|\\__,_|\\___/|_|  |_|\\__,_|\n";
    std::cout << "\n";
    resetColor();

    setColor(Color::CYAN);
    std::cout << "        A Text-Based Adventure Game in C++\n";
    std::cout << "      Developed for Pinnacle Labs Internship\n\n";
    resetColor();
}

// ─── Input Utilities ────────────────────────────────────────────────────────

void pressEnterToContinue() {
    setColor(Color::DARK_GRAY);
    std::cout << "\n  [Press Enter to continue...]";
    resetColor();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getValidInput(int min, int max) {
    int choice;
    while (true) {
        colorPrint("\n  >> ", Color::GREEN);
        if (std::cin >> choice && choice >= min && choice <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        colorPrintLn("  Invalid input! Please enter a number between "
                      + std::to_string(min) + " and " + std::to_string(max) + ".", Color::RED);
    }
}

std::string getStringInput(const std::string& prompt) {
    std::string input;
    while (true) {
        colorPrint("  " + prompt, Color::CYAN);
        colorPrint(": ", Color::WHITE);
        std::getline(std::cin, input);
        if (!input.empty()) {
            return input;
        }
        colorPrintLn("  Input cannot be empty. Please try again.", Color::RED);
    }
}

bool getYesNo(const std::string& prompt) {
    while (true) {
        colorPrint("  " + prompt + " (y/n): ", Color::CYAN);
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()) {
            char c = tolower(input[0]);
            if (c == 'y') return true;
            if (c == 'n') return false;
        }
        colorPrintLn("  Please enter 'y' or 'n'.", Color::RED);
    }
}

int displayMenu(const std::string& title, const std::vector<std::string>& options) {
    std::cout << "\n";
    printBoxedTitle(title, Color::YELLOW);
    std::cout << "\n";

    for (size_t i = 0; i < options.size(); i++) {
        colorPrint("    [", Color::DARK_GRAY);
        colorPrint(std::to_string(i + 1), Color::GREEN);
        colorPrint("] ", Color::DARK_GRAY);
        colorPrintLn(options[i], Color::WHITE);
    }

    return getValidInput(1, static_cast<int>(options.size()));
}

// ─── Random Number Generator ────────────────────────────────────────────────

int randomInt(int min, int max) {
    static std::mt19937 rng(static_cast<unsigned>(
        std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

// ─── Sleep ──────────────────────────────────────────────────────────────────

void sleepMs(int ms) {
    Sleep(ms);
}
