#include <ncurses.h>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

class BaseWindow {
protected:
    WINDOW* win;
    int height;
    int width;
    int startY;
    int startX;

public:
    BaseWindow(int h, int w, int y, int x)
            : win(0), height(h), width(w), startY(y), startX(x) {
        win = newwin(height, width, startY, startX);
        keypad(win, TRUE);
    }

    virtual ~BaseWindow() {
        if (win) {
            delwin(win);
        }
    }

    virtual void drawBorder() {
        box(win, 0, 0);
    }

    virtual void refreshWin() {
        wrefresh(win);
    }
};

class RoomList : public BaseWindow {
    vector<string> rooms;
    int selected;

public:
    RoomList(int h, int w, int y, int x, const vector<string>& roomNames)
            : BaseWindow(h, w, y, x), rooms(roomNames), selected(0) {}

    void handleInput(int ch) {
        if (ch == KEY_UP && selected > 0) {
            selected--;
        } else if (ch == KEY_DOWN && selected < (int)rooms.size() - 1) {
            selected++;
        }
    }

    void draw() {
        werase(win);
        drawBorder();
        wattron(win, COLOR_PAIR(3) | A_BOLD);
        mvwprintw(win, 0, 2, " Rooms ");
        wattroff(win, COLOR_PAIR(3) | A_BOLD);
        for (size_t i = 0; i < rooms.size(); ++i) {
            if ((int)i == selected) {
                wattron(win, COLOR_PAIR(4) | A_BOLD);
            } else {
                wattron(win, COLOR_PAIR(3));
            }
            mvwprintw(win, (int)i + 1, 1, "%-*s", width - 2, rooms[i].c_str());
            if ((int)i == selected) {
                wattroff(win, COLOR_PAIR(4) | A_BOLD);
            } else {
                wattroff(win, COLOR_PAIR(3));
            }
        }
        refreshWin();
    }
};

class MessageArea : public BaseWindow {
    vector<string> messages;
    int scrollOffset;

public:
    MessageArea(int h, int w, int y, int x)
            : BaseWindow(h, w, y, x), scrollOffset(0) {}

    void setSampleMessages() {
        messages.push_back("Welcome to the chat!");
        messages.push_back("This is a sample message.");
        messages.push_back("Use Up/Down to move in the rooms list.");
        messages.push_back("PageUp/PageDown scroll this area.");
        messages.push_back("Later this will show real chat messages.");
        messages.push_back("Line 6");
        messages.push_back("Line 7");
        messages.push_back("Line 8");
        messages.push_back("Line 9");
        messages.push_back("Line 10");
    }

    void handleScroll(int ch) {
        int visibleLines = height - 2;
        int maxOffset = 0;
        if ((int)messages.size() > visibleLines) {
            maxOffset = (int)messages.size() - visibleLines;
        }
        if (ch == KEY_PPAGE) {
            scrollOffset -= visibleLines;
            if (scrollOffset < 0) scrollOffset = 0;
        } else if (ch == KEY_NPAGE) {
            scrollOffset += visibleLines;
            if (scrollOffset > maxOffset) scrollOffset = maxOffset;
        }
    }

    void draw() {
        werase(win);
        drawBorder();
        wattron(win, COLOR_PAIR(2) | A_BOLD);
        mvwprintw(win, 0, 2, " Messages ");
        wattroff(win, COLOR_PAIR(2) | A_BOLD);
        int visibleLines = height - 2;
        for (int i = 0; i < visibleLines; ++i) {
            int index = scrollOffset + i;
            if (index >= (int)messages.size()) break;
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, i + 1, 1, "%-*s", width - 2, messages[index].c_str());
            wattroff(win, COLOR_PAIR(2));
        }
        refreshWin();
    }
};

class InputArea : public BaseWindow {
    string buffer;

public:
    InputArea(int h, int w, int y, int x)
            : BaseWindow(h, w, y, x) {}

    bool handleInput(int ch) {
        if (ch == '\n') {
            return true;
        } else if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
            if (!buffer.empty()) buffer.pop_back();
        } else if (isprint(ch)) {
            buffer.push_back((char)ch);
        }
        return false;
    }

    void clearBuffer() {
        buffer.clear();
    }

    void draw() {
        werase(win);
        drawBorder();
        wattron(win, COLOR_PAIR(5) | A_BOLD);
        mvwprintw(win, 0, 2, " Input ");
        wattroff(win, COLOR_PAIR(5) | A_BOLD);
        mvwprintw(win, 1, 1, "%-*s", width - 2, buffer.c_str());
        wmove(win, 1, 1 + (int)buffer.size());
        refreshWin();
    }
};

class ChatClientUI {
    RoomList* roomList;
    MessageArea* messageArea;
    InputArea* inputArea;
    bool running;

public:
    ChatClientUI() : roomList(0), messageArea(0), inputArea(0), running(true) {}

    ~ChatClientUI() {
        delete roomList;
        delete messageArea;
        delete inputArea;
    }

    void init() {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(1);
        if (has_colors()) {
            start_color();
            init_pair(1, COLOR_CYAN, COLOR_BLACK);
            init_pair(2, COLOR_YELLOW, COLOR_BLACK);
            init_pair(3, COLOR_CYAN, COLOR_BLACK);
            init_pair(4, COLOR_WHITE, COLOR_BLUE);
            init_pair(5, COLOR_GREEN, COLOR_BLACK);
        }
        int h, w;
        getmaxyx(stdscr, h, w);
        int headerHeight = 3;
        int inputHeight = 3;
        int roomsWidth = w / 4;
        roomList = new RoomList(h - headerHeight - inputHeight, roomsWidth,
                                headerHeight, w - roomsWidth,
                                vector<string>{"General", "Sports", "Programming", "Music", "Random"});
        messageArea = new MessageArea(h - headerHeight - inputHeight, w - roomsWidth,
                                      headerHeight, 0);
        messageArea->setSampleMessages();
        inputArea = new InputArea(inputHeight, w, h - inputHeight, 0);
    }

    void drawHeader() {
        int h, w;
        getmaxyx(stdscr, h, w);
        werase(stdscr);
        if (has_colors()) {
            attron(COLOR_PAIR(1) | A_BOLD);
        } else {
            attron(A_BOLD);
        }
        mvprintw(1, 2, "Advanced C++ Chat Client");
        attroff(A_BOLD);
        if (has_colors()) {
            attroff(COLOR_PAIR(1));
        }
        refresh();
    }

    void run() {
        while (running) {
            drawHeader();
            roomList->draw();
            messageArea->draw();
            inputArea->draw();
            int ch = getch();
            if (ch == 'q' || ch == 'Q') {
                running = false;
                break;
            }
            if (ch == KEY_UP || ch == KEY_DOWN) {
                roomList->handleInput(ch);
            } else if (ch == KEY_PPAGE || ch == KEY_NPAGE) {
                messageArea->handleScroll(ch);
            } else {
                bool submitted = inputArea->handleInput(ch);
                if (submitted) {
                    inputArea->clearBuffer();
                }
            }
        }
    }

    void shutdown() {
        endwin();
    }
};

int main() {
    ChatClientUI ui;
    ui.init();
    ui.run();
    ui.shutdown();
    return 0;
}
