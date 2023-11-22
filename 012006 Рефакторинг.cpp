#include <iostream>
#include <limits>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#elif __linux
#include <termios.h>
#endif
using namespace std;

#ifdef __linux
struct termios Old, New;

void inputLinux(string& text, const string& charset) {
    cout << "Для закінчення введення даних натисніть клавішу esc\n";
    tcgetattr(0, &Old);
    New = Old;
    New.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &New);

    char qt;
    while ((qt = getchar()) != 27) {
        for (int i = 0; i < charset.length(); i++) {
            if (qt == charset[i]) {
                qt = ' ';
                break;
            }
        }
        text += qt;
        cout << qt;
    }
    tcsetattr(0, TCSANOW, &Old);
    cout << endl << "Ви ввели текст:\n" << text << endl;
}

#elif _WIN32
void inputWindows(string& text, const string& charset) {
    cout << "Для закінчення введення даних натисніть клавішу esc\n";
    char qt;
    bool run = true;

    while (run) {
        if (_kbhit()) {
            qt = _getch();
            for (int i = 0; i < charset.length(); i++) {
                if (qt == charset[i]) {
                    qt = ' ';
                }
                else if (qt == 13) {
                    qt = '\n';
                }
                else if (qt == 27) {
                    run = false;
                    qt = ' ';
                    break;
                }
            }
            text += qt;
            cout << qt;
        }
    }
    cout << endl << "Ви ввели текст:\n" << text << endl;
}
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
#elif __linux
#endif

    string Ukr = "йцукенгшщзхждлорпавфячсмитьбюЙЦУКЕНГШЩЗХЖДЛОРПАВФЯЧСМИТЬБЮґҐІіЄєЇї";
    string Eng = "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM";
    string Num = "0123456789";
    string Symb = "`~!@#$%^&*()_+}{|\":<>?/.,\\';][=-№";

    bool menu_run = true;
    int choice = 0;
    string text;

    while (menu_run) {
        cout << "Натисніть 1 для заміни цифр пробілами\n";
        cout << "Натисніть 2 для заміни розділових знаків пробілами\n";
        cout << "Натисніть 3 для заміни англійських букв пробілами\n";
        cout << "Натисніть 4 для заміни українських букв пробілами\n";
        cin >> choice;

#ifdef __linux
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
        case 1:
            system("clear");
            inputLinux(text, Num);
            break;
        case 2:
            system("clear");
            inputLinux(text, Symb);
            break;
        case 3:
            system("clear");
            inputLinux(text, Eng);
            break;
        case 4:
            system("clear");
            inputLinux(text, Ukr);
            break;
        default:
            menu_run = false;
            break;
        }

#elif _WIN32
        switch (choice) {
        case 1:
            system("CLS");
            inputWindows(text, Num);
            break;
        case 2:
            system("CLS");
            inputWindows(text, Symb);
            break;
        case 3:
            system("CLS");
            inputWindows(text, Eng);
            break;
        case 4:
            system("CLS");
            inputWindows(text, Ukr);
            break;
        default:
            menu_run = false;
            break;
        }
#endif
    }
    return 0;
}