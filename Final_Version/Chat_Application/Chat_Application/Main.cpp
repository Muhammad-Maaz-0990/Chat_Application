#include<iostream>
#include <WinSock2.h> 
#include <WS2tcpip.h> 
#include<iomanip>
#include<sstream>
#include<ctime>
#include<conio.h>
#include<string>
#include<cstdlib>
#include<cmath>
#include<fstream>
#include<windows.h>
#include <tchar.h>
#include <thread>
#include <chrono>
#include<atomic>
#include<vector>
#include<array>


using namespace std;


#pragma comment(lib,"ws2_32.lib") 


string static_username;
string static_email;
string static_tier;


class Design {
private:
	static int theme;
	static string color;

public:
	int getTerminalWidth()
	{
#ifdef _WIN32
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		return w.ws_col;
#endif
	}

	int getTerminalHeight()
	{
#ifdef _WIN32
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		return w.ws_row;
#endif
	}
	int getCurrentLinePosition()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		if (GetConsoleScreenBufferInfo(hConsole, &csbi))
		{
			return csbi.dwCursorPosition.Y;
		}
		else
		{
			return -1;
		}
	}
	void setTerminalZoom(float zoomFactor)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		// Get the current console font info
		CONSOLE_FONT_INFOEX fontInfo = { sizeof(CONSOLE_FONT_INFOEX) };
		if (!GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo)) {
			std::cerr << "Error: Unable to retrieve console font info." << std::endl;
			return;
		}

		// Modify the font size
		fontInfo.dwFontSize.X = static_cast<SHORT>(fontInfo.dwFontSize.X * zoomFactor);
		fontInfo.dwFontSize.Y = static_cast<SHORT>(fontInfo.dwFontSize.Y * zoomFactor);

		// Apply the new font size
		if (!SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo)) {
			std::cerr << "Error: Unable to set console font info." << std::endl;
		}
	}
	void gotoxy(int x, int y)
	{

		COORD coord;

		coord.X = x;

		coord.Y = y;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	}
	void GotoXY(int x, int y)
	{
		HANDLE a;
		COORD b;
		fflush(stdout);
		b.X = x;
		b.Y = y;
		a = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(a, b);
	}


	void fullscreen()
	{
		HWND consoleWindow = GetConsoleWindow();
		ShowWindow(consoleWindow, SW_MAXIMIZE);

	}
	static void set_theme(int i)
	{

		theme = i;
	}
	static int get_theme()
	{
		return theme;
	}

	static void set_color(string i)
	{
		color = i;
	}
	static string get_color()
	{
		return color;
	}

	void set_color(int color) {
		// Set the console text attribute based on the theme
		if (theme == 0) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color | 0 << 4);
		}
		else if (theme == -1) {
			// Light Theme
			if (color == 4) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | 4);
			}
			else if (color == 10) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | 2);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | 0);
			}
		}
		else if (theme == 5)
		{
			if (color == 4) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 << 4 | 4);
			}
			else if (color == 10) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 << 4 | 2);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			}
		}
		else if (theme == 3)
		{
			if (color == 4) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 << 4 | 4);
			}
			else if (color == 10) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 << 4 | 2);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
			}
		}
		else if (theme == 4) {
			if (color == 4) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 << 4 | 4);
			}
			else if (color == 10) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 << 4 | 2);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
			}
		}
		else if (theme == 2) {
			if (color == 4) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 << 4 | 4);
			}
			else if (color == 10) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0 << 4 | 2);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			}
		}
		else if (theme == 1) {
			if (color == 4) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 << 4 | 15);
			}
			else if (color == 10) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2 << 4 | 15);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}

	}

	void red_color() {
		set_color(4); // Red
	}

	void pink_color() {
		set_color(12); // Light Red (Pink)
	}

	void green_color() {
		set_color(10); // Light Green
	}

	void blue_color() {
		set_color(9); // Light Blue
	}

	void yellow_color() {
		set_color(6); // Yellow
	}

	void white_color() {
		set_color(15); // White
	}

	void grey_color() {
		set_color(8); // Gray
	}

	void cyan_color() {
		set_color(11); // Light Cyan
	}

	void skin_color() {
		set_color(14); // Light Yellow (Skin)
	}
	void new_color()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	}
	void display_line_slash()
	{
		grey_color();
		cout << endl;
		cout << "//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////" << endl;
		cout << endl;
		white_color();
	}
	void display_box_line()
	{
		red_color();
		cout << endl;
		cout << " |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_| |_|" << endl;
		cout << endl;
		white_color();
	}
	void display_line()
	{
		grey_color();
		cout << "_____________________________________________________________________________";
		//		blue_color();
		cout << "________________________________________________________________________________" << endl;
		cout << endl;
		white_color();
	}
	void display_line_p()
	{
		green_color();
		cout << "__________________________________________________________________________________________________________________________________________________________" << endl;
		white_color();
	}


	void banner()
	{
		cout << R"(               
		                 ______________________________________________________________________________________________________                      
    _______                 ___ |        ___     ___    ____       ___    ____   ___    _     ____  ____   ____    _   _   _  ____     |      ..      ..                                 
   | [] [] |               /    |       /   \   / _ \  |  _ \     |   \  |  __| / _ \  | |   |  __||  _ \ / __/   / / \ \ | ||  _ \    |      \_/    \_/             
   |       |     __ _     /     |      /  /\_\ / /_\ \ | |/ |     | |\ \ | |_  / /_\ \ | |   | |_  | |/ | \ \__   | |_| | | || |/ /    |                       ___             
   | [] [] |   _/m m \_  /      |      | |  __ |  _  | |    /     | || | |  _| |  _  | | |   |  _| |    /  \__ \  |  _  | | ||  _/     |        Q__   O       /   /_                     
   |_______| /'_@____@_\/       |      \  \/ / | | | | | |\ \     | |/ / | |__ | | | | | |__ | |__ | |\ \   __\ \ | | | | | || |       |       /|  "_/|\     / $ / /                       
                                |       \___/  |_| |_| |_| \_\    |___/  |____||_| |_| |____||____||_| \_\ /____| \_\ /_/ |_||_|       |       / \   / \    /___/ /                 
                                |______________________________________________________________________________________________________|                     /___/                
	  )" << endl;

	}

	void border()
	{

		system("cls"); // Clear the screen

		skin_color();
		int width = getTerminalWidth();
		int height = getTerminalHeight() - 1; // Set height for border; adjust based on preference


		string title = ">>>>   ZAMS CHAT   <<<<";


		int titleLength = title.length();
		int startX = (width - titleLength) / 2;

		// Draw the top border
		for (int i = 0; i < width; i++) {
			GotoXY(i, 0); // Top border line at y = 0
			cout << "=";
		}


		for (int i = 0; i < titleLength; i++) {
			GotoXY(startX + i, 0); // Move to the appropriate position for the title
			cout << title[i];
		}

		// Draw the sides
		for (int i = 1; i < height; i++) {
			GotoXY(0, i);        // Left border
			cout << "||";
			GotoXY(width - 2, i); // Right border
			cout << "||";
		}

		// Draw the bottom border
		for (int i = 0; i < width; i++) {
			GotoXY(i, height); // Bottom border line
			cout << "=";
		}
		white_color();
	}


	void drawBox(int x, int y, int width, int height)
	{
		// Draw top border
		yellow_color();
		gotoxy(x, y);
		cout << "/";
		for (int i = 0; i < width - 2; ++i)
			cout << "_";
		cout << "\\";

		// Draw sides
		for (int i = 1; i < height - 1; ++i) {
			gotoxy(x, y + i);
			cout << "|";
			gotoxy(x + width - 1, y + i);
			cout << "|";
		}

		// Draw bottom border
		gotoxy(x, y + height - 1);
		cout << "\\";
		for (int i = 0; i < width - 2; ++i)
			cout << "_";
		cout << "/";
		white_color();
	}

	void printBorderedText(const string& text)
	{
		// Calculate the length of the text
		int length = text.length();

		cout << ' ';
		// Print the top border
		cout << "    " << string(length + 2, '_') << endl; // +4 for the borders and spaces

		// Print the text with side borders
		cout << "    / " << string(length, ' ') << " \\" << endl;
		cout << "    | " << text << " |" << endl;
		cout << "    \\" << string(length + 2, '_') << "/" << endl << endl;
	}

	void printLeftAligned(const string& text, bool bordered) {
		if (bordered)
		{
			// Call the border function if bordered is true
			printBorderedText(text);
		}
		else
		{
			cout << "     " << text << endl; // Print the left-aligned text normally
		}
	}

	void printRightAligned(const string& text, bool bordered)
	{
		int width = getTerminalWidth(); // Get the current terminal width
		int len = text.length();

		// Calculate the number of spaces needed for right alignment
		int spaces = width - len - 3;
		spaces = spaces - 2;

		// Print the spaces for right alignment
		if (spaces > 0)
		{
			if (bordered)
			{
				spaces = spaces - 3;
				cout << string(spaces, ' ');
			}
			else
			{
				cout << string(spaces, ' ');
			}

		}

		// Print the right-aligned text
		if (bordered)
		{
			int length = text.length();
			// Print the top border
			cout << ' ';
			cout << string(length + 2, '_') << endl; // +4 for the borders and spaces
			// Print the text with side borders
			cout << string(spaces, ' ') << "/ " << string(length, ' ') << " \\" << endl;
			cout << string(spaces, ' ') << "| " << text << " |" << endl;
			cout << string(spaces, ' ') << "\\" << string(length + 2, '_') << "/" << endl << endl;
		}
		else
		{
			cout << text << endl;
		}
	}


	int displayMenu(vector<string> menuItems)
	{
		border();
		int longestItemLength = 0;
		for (const string& item : menuItems)
		{
			if (item.length() > longestItemLength)
				longestItemLength = item.length();
		}
		int extraSpacing = 3; // Space before and after the menu
		int boxWidth = max(longestItemLength, 10) + getTerminalWidth() / 3; // Add padding
		int boxHeight = menuItems.size() * 3 + extraSpacing * 2 + 1; // Include spacing for lines and borders

		int terminalWidth = getTerminalWidth();
		int terminalHeight = getTerminalHeight();

		// Center the box
		int startX = (terminalWidth - boxWidth) / 2;
		int startY = (terminalHeight - boxHeight) / 2;

		// Draw the box
		drawBox(startX, startY, boxWidth, boxHeight);

		// Display menu items with the new format
		int currentY = startY + extraSpacing; // Start after the top spacing
		for (size_t i = 0; i < menuItems.size(); ++i)
		{
			// Center and display the item number
			int numberStartX = startX + (boxWidth - 1) / 2;
			gotoxy(numberStartX - 15, currentY);
			
			//Sleep(200);

			skin_color();
			cout << "<--------------";
			cout << i + 1;
			cout << "-------------->";

			white_color();
			// Display the item text on the next centered line
			int textStartX = startX + (boxWidth - menuItems[i].length()) / 2;
			gotoxy(textStartX, currentY + 1);
			cout << menuItems[i];

			currentY += 3; // Move down for the next item (number + text + spacing)
		}
		return currentY + 5;

	}

	int accountInfo(vector<string> menuItems)
	{
		border();
		vector <string> items = { "Username","Email","Password","Tier","Joined Date" };
		int longestItemLength = 0;
		for (const string& item : menuItems)
		{
			if (item.length() > longestItemLength)
				longestItemLength = item.length();
		}
		int extraSpacing = 2; // Space before and after the menu
		int boxWidth = max(longestItemLength, 10) + getTerminalWidth() / 3; // Add padding
		int boxHeight = menuItems.size() * 3 + extraSpacing; // Include spacing for lines and borders

		int terminalWidth = getTerminalWidth();
		int terminalHeight = getTerminalHeight();

		// Center the box
		int startX = (terminalWidth - boxWidth) / 2;
		int startY = (terminalHeight - boxHeight) / 2;

		// Draw the box
		drawBox(startX, startY, boxWidth, boxHeight);

		// Display menu items with the new format
		int currentY = startY + extraSpacing; // Start after the top spacing
		for (size_t i = 0; i < menuItems.size(); ++i)
		{
			// Center and display the item number
			int numberStartX = startX + (boxWidth - 1) / 5;
			gotoxy(numberStartX, currentY);

			skin_color();
			cout << ">>";
			cout << items[i] << " :";


			white_color();
			// Display the item text on the next centered line
			int textStartX = startX + (boxWidth) / 2.5;
			gotoxy(textStartX, currentY);
			cout << menuItems[i];

			currentY += 3; // Move down for the next item (number + text + spacing)
		}
		return currentY + 5;

	}

	int getPremium(vector<string> menuItems)
	{
		border();
		vector <string> items = { "Change Theme:","Get Backup:","Multiple Device Login:","Show Deleted Messages" };
		int longestItemLength = 0;
		for (const string& item : menuItems)
		{
			if (item.length() > longestItemLength)
				longestItemLength = item.length();
		}
		int extraSpacing = 2; // Space before and after the menu
		int boxWidth = max(longestItemLength, 10) + getTerminalWidth() / 3; // Add padding
		int boxHeight = menuItems.size() * 3 + extraSpacing; // Include spacing for lines and borders

		int terminalWidth = getTerminalWidth();
		int terminalHeight = getTerminalHeight();

		// Center the box
		int startX = (terminalWidth - boxWidth) / 2;
		int startY = (terminalHeight - boxHeight) / 2;

		// Draw the box
		drawBox(startX, startY, boxWidth, boxHeight);

		// Display menu items with the new format
		int currentY = startY + extraSpacing; // Start after the top spacing
		for (size_t i = 0; i < menuItems.size(); ++i)
		{
			// Center and display the item number
			int numberStartX = startX + (boxWidth - 1) / 5;
			gotoxy(numberStartX - 5, currentY);

			skin_color();
			cout << ">>";
			cout << items[i] << " :";


			white_color();
			// Display the item text on the next centered line
			int textStartX = startX + (boxWidth) / 2.5;
			gotoxy(textStartX, currentY);
			cout << menuItems[i];

			currentY += 3; // Move down for the next item (number + text + spacing)
		}
		return currentY + 5;

	}


	int displayList(vector<string> listItems)
	{
		border();
		int longestItemLength = 0;
		for (const string& item : listItems)
		{
			if (item.length() > longestItemLength)
				longestItemLength = item.length();
		}

		int extraSpacing = 1; // Space before and after the list
		int boxWidth = max(longestItemLength, 10) + getTerminalWidth() / 3; // Wider box
		int boxHeight = listItems.size() * 2 + extraSpacing * 2; // Include spacing for lines and borders

		int terminalWidth = getTerminalWidth();
		int terminalHeight = getTerminalHeight();

		// Center the box
		int startX = (terminalWidth - boxWidth) / 2;
		int startY = (terminalHeight - boxHeight) / 2;

		// Draw the box
		drawBox(startX, startY, boxWidth, boxHeight);

		// Display list items with the new format
		int currentY = startY + extraSpacing; // Start after the top spacing
		for (const string& item : listItems)
		{
			// Display the item text centered
			int textStartX = startX + (boxWidth - item.length()) / 2;
			gotoxy(textStartX, currentY);
			cout << item;

			currentY += 1; // Line spacing between items
			gotoxy(startX + 1, currentY); // Draw separator line
			yellow_color();
			for (int i = 0; i < boxWidth - 2; ++i)
				cout << "+";
			white_color();
			currentY += 1; // Move down for the next item
		}

		// Display "Back" as the last item
		string backText = " Enter 'Back' to Return ";
		int backTextStartX = startX + (boxWidth - backText.length()) / 2;
		gotoxy(backTextStartX, currentY);
		yellow_color();
		cout << "/";
		white_color();
		cout << backText;
		yellow_color();
		cout << "\\";

		return currentY + 5;
	}



	void display_enter(string n, string m, int position)
	{
		skin_color();
		string arrows = "  >>>>>>>>>>  ";
		int horizontal = (getTerminalWidth() / 2) - n.length() - arrows.length() / 2;
		gotoxy(horizontal, position);
		cout << n;
		cout << arrows;
		cout << " [" << m << "]  ";
		white_color();
	}

	void display_enter(string n, int position)
	{

		skin_color();
		string arrows = "  >>>>>>>>>>  ";
		int horizontal = (getTerminalWidth() / 2) - n.length() - arrows.length() / 2;

		gotoxy(horizontal, position);
		cout << n;
		cout << arrows;
		white_color();
	}

	void display(string n, int position)
	{
		skin_color();
		string arrows = "  >>>>>>>>>>  ";
		int horizontal = (getTerminalWidth() / 2) - n.length() - arrows.length() / 2;
		gotoxy(horizontal, position);
		cout << n;
		cout << arrows;
		white_color();
	}
	void display_center(string n)
	{
		red_color();
		gotoxy(getTerminalWidth() / 2 - n.length() / 2, getTerminalHeight() / 2);
		cout << n;
		white_color();
	}
	void display_center_g(string n)
	{
		green_color();
		gotoxy(getTerminalWidth() / 2 - n.length() / 2, getTerminalHeight() / 2);
		cout << n;
		white_color();
	}
	void display(string n, string m, int position)
	{
		skin_color();
		gotoxy(getTerminalWidth() / 2.5, position);
		cout << n;
		cout << " >>>>>>>>>> ";
		cout << m;
		white_color();
	}

	void display_side(string n, int position)
	{
		skin_color();
		gotoxy((getTerminalWidth() / 3) * 2, position);
		cout << n;
		white_color();
	}

	void display_no_record()
	{
		cout << "\n" << setw(135);
		skin_color();
		cout << ">> ";

		cout << " NO RECORD FOUND :( ";
		skin_color();
		cout << " <<" << endl;
		white_color();
		_getch();
	}
	void display_no_record_p(int position)
	{
		skin_color();
		gotoxy((getTerminalWidth() / 3) * 2, position);
		cout << ">> ";
		cout << " NO RECORD FOUND :( ";
		skin_color();
		cout << " <<" << endl;
		white_color();
		_getch();
	}

	void display_invalid()
	{
		cout << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
		skin_color();
		cout << ">>";
		cout << " YOU ENTERED ";
		red_color();
		cout << "INVALID ";
		skin_color();
		cout << "CHOICE ! ";
		cout << "<<" << endl;
		white_color();
		_getch();
	}


	void display_file_p(int position)
	{
		skin_color();
		gotoxy((getTerminalWidth() / 3) * 2, position);
		cout << ">>";
		cout << " FILE ";
		red_color();
		cout << "DOES NOT ";
		skin_color();
		cout << "EXISTS !";
		cout << "<<" << endl;
		white_color();
		_getch();
	}

	void display_invalid(string n)
	{
		Beep(350, 400);
		cout << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
		skin_color();
		cout << ">> ";
		cout << "INVALID ";
		red_color();
		cout << n;
		skin_color();
		cout << " <<" << endl;
		white_color();
		_getch();
	}
	void display_sucessfully(string n)
	{
		cout << endl;
		cout << setw(120);
		skin_color();
		cout << ">> ";
		cout << n;
		green_color();
		cout << " SUCESSFULLY :)";
		skin_color();
		cout << " <<" << endl;
		white_color();
		_getch();
	}
	void display_sucessfully_p(string n, int position)
	{
		gotoxy((getTerminalWidth() / 3) * 2, position);
		skin_color();
		cout << ">> ";
		cout << n;
		green_color();
		cout << " SUCESSFULLY :)";
		skin_color();
		cout << " <<" << endl;
		white_color();
		_getch();
	}
	void display_invalid_p(string n, int position)
	{
		gotoxy((getTerminalWidth() / 3) * 2 - n.length(), position);
		skin_color();
		cout << ">> ";
		cout << "INVALID ";
		red_color();
		cout << n;
		skin_color();
		cout << " <<" << endl;
		white_color();
		_getch();
	}

	void display_not_found_p(string n, int position)
	{
		gotoxy((getTerminalWidth() / 3) * 2, position);
		red_color();
		cout << n;
		skin_color();
		cout << " NOT FOUND !";
		white_color();
		_getch();
	}

	void display_do_you_p(string n, string m, int position)
	{
		Beep(350, 400);
		gotoxy((getTerminalWidth() / 3) * 2 - n.length(), position);
		green_color();
		cout << " ";
		cout << "DO YOU ";
		pink_color();
		cout << n;
		green_color();
		cout << " >>>>>>>>>> ";
		cout << "[";
		pink_color();
		cout << m;
		green_color();
		cout << "]  ";
		white_color();
	}
	void display_do_you(string n, string m)
	{
		Beep(350, 400);
		setw((getTerminalWidth() / 3) * 2 - n.length());
		green_color();
		cout << " ";
		cout << "DO YOU ";
		pink_color();
		cout << n;
		green_color();
		cout << " >>>>>>>>>> ";
		cout << "[";
		pink_color();
		cout << m;
		green_color();
		cout << "]  ";
		white_color();
	}

	void display_already_contained_p(string n, int position)
	{
		Beep(350, 400);
		gotoxy((getTerminalWidth() / 3) * 2, position);
		skin_color();
		cout << ">> ";
		red_color();
		cout << n;
		skin_color();
		cout << " ALREADY CONTAINED ";
		cout << " <<" << endl;
		white_color();
		_getch();
	}

	void tab_login()
	{
		gotoxy(0, 1);
		yellow_color();
		cout << "\t\t   ===================== " << endl;
		cout << "\t\t /|      LOGIN PAGE    |" << endl;
		cout << "\t\t| |____________________|" << endl;
		cout << "\t\t|/____________________/ " << endl;
		white_color();
	}
	void tab_signup()
	{
		gotoxy(0, 1);
		yellow_color();
		cout << "\t\t   ===================== " << endl;
		cout << "\t\t /|     SIGNUP PAGE    |" << endl;
		cout << "\t\t| |____________________|" << endl;
		cout << "\t\t|/____________________/ " << endl;
		white_color();
	}
	void tab_forget()
	{
		gotoxy(0, 1);
		yellow_color();
		cout << "\t\t   ===================== " << endl;
		cout << "\t\t /|        FORGET      |" << endl;
		cout << "\t\t| |____________________|" << endl;
		cout << "\t\t|/____________________/ " << endl;
		white_color();
	}
	void tab_dashboard()
	{
		gotoxy(0, 1);
		yellow_color();
		cout << "\t\t   ===================== " << endl;
		cout << "\t\t /|      DASHBOARD     |" << endl;
		cout << "\t\t| |____________________|" << endl;
		cout << "\t\t|/____________________/ " << endl;
		white_color();
	}
	void tab_status_management()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		yellow_color();
		cout << "\t\t   ======================== " << endl;
		grey_color();


		cout << "\t\t |                     |";
		yellow_color();
		cout << "\t\t /|   STATUS MANAGEMENT   |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		yellow_color();
		cout << "\t\t| |_______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		yellow_color();
		cout << "\t\t|/_______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_friends()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		yellow_color();
		cout << "\t\t   ==================== " << endl;
		grey_color();


		cout << "\t\t |                     |";
		yellow_color();
		cout << "\t\t /|      FRIENDS      |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		yellow_color();
		cout << "\t\t| |___________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		yellow_color();
		cout << "\t\t|/___________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_groups()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		yellow_color();
		cout << "\t\t   ==================== " << endl;
		grey_color();


		cout << "\t\t |                     |";
		yellow_color();
		cout << "\t\t /|       GROUPS      |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		yellow_color();
		cout << "\t\t| |___________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		yellow_color();
		cout << "\t\t|/___________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_setting()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		yellow_color();
		cout << "\t\t   ==================== " << endl;
		grey_color();


		cout << "\t\t |                     |";
		yellow_color();
		cout << "\t\t /|      SETTING      |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		yellow_color();
		cout << "\t\t| |___________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		yellow_color();
		cout << "\t\t|/___________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_status_management_add()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t\t  _____________________ ";
		yellow_color();
		cout << "\t\t   ==================== " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t\t |                     |";
		yellow_color();
		cout << "\t\t /|        ADD        |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t\t |  STATUS MANAGEMENT  |";
		yellow_color();
		cout << "\t\t| |___________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t\t |_____________________| ";
		yellow_color();
		cout << "\t\t|/___________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_status_management_delete()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t\t  _____________________ ";
		yellow_color();
		cout << "\t\t   ==================== " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t\t |                     |";
		yellow_color();
		cout << "\t\t /|      DELETE       |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t\t |  STATUS MANAGEMENT  |";
		yellow_color();
		cout << "\t\t| |___________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t\t |_____________________| ";
		yellow_color();
		cout << "\t\t|/___________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_status_management_view()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t\t  _____________________ ";
		yellow_color();
		cout << "\t\t   ==================== " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t\t |                     |";
		yellow_color();
		cout << "\t\t /|        VIEW       |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t\t |  STATUS MANAGEMENT  |";
		yellow_color();
		cout << "\t\t| |___________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t\t |_____________________| ";
		yellow_color();
		cout << "\t\t|/___________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_friends_fm()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t\t  _____________________ ";
		yellow_color();
		cout << "\t\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t\t |                     |";
		yellow_color();
		cout << "\t\t /|   FRIENDS MANGEMENT  |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t\t |       FRIENDS       |";
		yellow_color();
		cout << "\t\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t\t |_____________________| ";
		yellow_color();
		cout << "\t\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_friends_fm_sr()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t  _____________________ ";
		cout << "\t  _____________________ ";
		yellow_color();
		cout << "\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t |                     |";
		cout << "\t |                     |";
		yellow_color();
		cout << "\t /|     SEND REQUEST     |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t |       FRIENDS       |";
		cout << "\t |  FRIENDS MANAGEMENT |";
		yellow_color();
		cout << "\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t |_____________________| ";
		cout << "\t |_____________________| ";
		yellow_color();
		cout << "\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_friends_fm_ra()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t  _____________________ ";
		cout << "\t  _____________________ ";
		yellow_color();
		cout << "\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t |                     |";
		cout << "\t |                     |";
		yellow_color();
		cout << "\t /|    REQUEST APPROVAL  |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t |       FRIENDS       |";
		cout << "\t |  FRIENDS MANAGEMENT |";
		yellow_color();
		cout << "\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t |_____________________| ";
		cout << "\t |_____________________| ";
		yellow_color();
		cout << "\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_friends_fm_ra_o()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t___________________ ";
		cout << "      ________________";
		cout << "      __________________________";
		cout << "      ______________________";
		yellow_color();
		cout << "        =======================" << endl;
		grey_color();


		cout << "\t|                 |";
		cout << "      |               |";
		cout << "      |                        |";
		cout << "      |                    |";
		yellow_color();
		cout << "       /|   OUTREACH REQUEST   |" << endl;
		grey_color();


		cout << "\t|    DASHBOARD    |";
		cout << "      |    FRIENDS    |";
		cout << "      |    FRIEND MANAGEMENT   |";
		cout << "      |  REQUEST APPROVAL  |";
		yellow_color();
		cout << "      | |______________________|" << endl;
		grey_color();


		cout << "\t|_________________|";
		cout << "      |_______________|";
		cout << "      |________________________|";
		cout << "      |____________________|";
		yellow_color();
		cout << "      |/______________________/" << endl;
		grey_color();

		white_color();
	}
	void tab_friends_fm_ra_i()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t___________________ ";
		cout << "      ________________";
		cout << "      __________________________";
		cout << "      ______________________";
		yellow_color();
		cout << "        =======================" << endl;
		grey_color();


		cout << "\t|                 |";
		cout << "      |               |";
		cout << "      |                        |";
		cout << "      |                    |";
		yellow_color();
		cout << "       /|   INCOMING REQUEST   |" << endl;
		grey_color();


		cout << "\t|    DASHBOARD    |";
		cout << "      |    FRIENDS    |";
		cout << "      |    FRIEND MANAGEMENT   |";
		cout << "      |  REQUEST APPROVAL  |";
		yellow_color();
		cout << "      | |______________________|" << endl;
		grey_color();


		cout << "\t|_________________|";
		cout << "      |_______________|";
		cout << "      |________________________|";
		cout << "      |____________________|";
		yellow_color();
		cout << "      |/______________________/" << endl;
		grey_color();

		white_color();
	}
	void tab_friends_fm_yf()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t  _____________________ ";
		cout << "\t  _____________________ ";
		yellow_color();
		cout << "\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t |                     |";
		cout << "\t |                     |";
		yellow_color();
		cout << "\t /|     YOUR FRIENDS     |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t |       FRIENDS       |";
		cout << "\t |  FRIENDS MANAGEMENT |";
		yellow_color();
		cout << "\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t |_____________________| ";
		cout << "\t |_____________________| ";
		yellow_color();
		cout << "\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_friends_fc()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t\t  _____________________ ";
		yellow_color();
		cout << "\t\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t\t |                     |";
		yellow_color();
		cout << "\t\t /|     FRIENDS CHAT     |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t\t |       FRIENDS       |";
		yellow_color();
		cout << "\t\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t\t |_____________________| ";
		yellow_color();
		cout << "\t\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_friends_fc_lc()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t  _____________________ ";
		cout << "\t  _______________________ ";
		yellow_color();
		cout << "\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t |                     |";
		cout << "\t |                        |";
		yellow_color();
		cout << "\t /|   LIVE CONERSATION   |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t |       FRIENDS       |";
		cout << "\t |  FRIENDS CONVERSATION  |";
		yellow_color();
		cout << "\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t |_____________________| ";
		cout << "\t |________________________| ";
		yellow_color();
		cout << "\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_friends_fc_vc()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t  _____________________ ";
		cout << "\t  _______________________ ";
		yellow_color();
		cout << "\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t |                     |";
		cout << "\t |                        |";
		yellow_color();
		cout << "\t /|      VIEW CHATS      |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t |       FRIENDS       |";
		cout << "\t |  FRIENDS CONVERSATION  |";
		yellow_color();
		cout << "\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t |_____________________| ";
		cout << "\t |________________________| ";
		yellow_color();
		cout << "\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_groups_gm()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t\t  _____________________ ";
		yellow_color();
		cout << "\t\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t\t |                     |";
		yellow_color();
		cout << "\t\t /|   GROUPS MAHAGEMENT  |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t\t |        GROUPS       |";
		yellow_color();
		cout << "\t\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t\t |_____________________| ";
		yellow_color();
		cout << "\t\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_groups_gm_ag()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t  _____________________ ";
		cout << "\t  _______________________ ";
		yellow_color();
		cout << "\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t |                     |";
		cout << "\t |                        |";
		yellow_color();
		cout << "\t /|       ADD GROUP      |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t |        GROUPS       |";
		cout << "\t |    GROUP MANAGEMENT    |";
		yellow_color();
		cout << "\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t |_____________________| ";
		cout << "\t |________________________| ";
		yellow_color();
		cout << "\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_groups_gm_ug()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t  _____________________ ";
		cout << "\t  _______________________ ";
		yellow_color();
		cout << "\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t |                     |";
		cout << "\t |                        |";
		yellow_color();
		cout << "\t /|     UPDATE GROUP     |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t |        GROUPS       |";
		cout << "\t |    GROUP MANAGEMENT    |";
		yellow_color();
		cout << "\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t |_____________________| ";
		cout << "\t |________________________| ";
		yellow_color();
		cout << "\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_groups_gm_dg()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t  _____________________ ";
		cout << "\t  _______________________ ";
		yellow_color();
		cout << "\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t |                     |";
		cout << "\t |                        |";
		yellow_color();
		cout << "\t /|     DELETE GROUP     |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t |        GROUPS       |";
		cout << "\t |    GROUP MANAGEMENT    |";
		yellow_color();
		cout << "\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t |_____________________| ";
		cout << "\t |________________________| ";
		yellow_color();
		cout << "\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_groups_gm_gm()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t  _____________________ ";
		cout << "\t  _______________________ ";
		yellow_color();
		cout << "\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t |                     |";
		cout << "\t |                        |";
		yellow_color();
		cout << "\t /|     GROUP MEMBERS    |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t |        GROUPS       |";
		cout << "\t |    GROUP MANAGEMENT    |";
		yellow_color();
		cout << "\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t |_____________________| ";
		cout << "\t |________________________| ";
		yellow_color();
		cout << "\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_groups_gm_gm_am()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t___________________ ";
		cout << "      ________________";
		cout << "      __________________________";
		cout << "      ______________________";
		yellow_color();
		cout << "        =======================" << endl;
		grey_color();


		cout << "\t|                 |";
		cout << "      |               |";
		cout << "      |                        |";
		cout << "      |                    |";
		yellow_color();
		cout << "       /|      ADD MEMBERS     |" << endl;
		grey_color();


		cout << "\t|    DASHBOARD    |";
		cout << "      |     GROUPS    |";
		cout << "      |    GROUP MANAGEMENT    |";
		cout << "      |    GROUP MEMBERS   |";
		yellow_color();
		cout << "      | |______________________|" << endl;
		grey_color();


		cout << "\t|_________________|";
		cout << "      |_______________|";
		cout << "      |________________________|";
		cout << "      |____________________|";
		yellow_color();
		cout << "      |/______________________/" << endl;
		grey_color();

		white_color();
	}
	void tab_groups_gm_gm_rm()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t___________________ ";
		cout << "      ________________";
		cout << "      __________________________";
		cout << "      ______________________";
		yellow_color();
		cout << "        =======================" << endl;
		grey_color();


		cout << "\t|                 |";
		cout << "      |               |";
		cout << "      |                        |";
		cout << "      |                    |";
		yellow_color();
		cout << "       /|     REMOVE MEMBERS   |" << endl;
		grey_color();


		cout << "\t|    DASHBOARD    |";
		cout << "      |     GROUPS    |";
		cout << "      |    GROUP MANAGEMENT    |";
		cout << "      |    GROUP MEMBERS   |";
		yellow_color();
		cout << "      | |______________________|" << endl;
		grey_color();


		cout << "\t|_________________|";
		cout << "      |_______________|";
		cout << "      |________________________|";
		cout << "      |____________________|";
		yellow_color();
		cout << "      |/______________________/" << endl;
		grey_color();

		white_color();
	}
	void tab_groups_gm_gm_lg()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t___________________ ";
		cout << "      ________________";
		cout << "      __________________________";
		cout << "      ______________________";
		yellow_color();
		cout << "        =======================" << endl;
		grey_color();


		cout << "\t|                 |";
		cout << "      |               |";
		cout << "      |                        |";
		cout << "      |                    |";
		yellow_color();
		cout << "       /|      LEAVE GROUP     |" << endl;
		grey_color();


		cout << "\t|    DASHBOARD    |";
		cout << "      |     GROUPS    |";
		cout << "      |    GROUP MANAGEMENT    |";
		cout << "      |    GROUP MEMBERS   |";
		yellow_color();
		cout << "      | |______________________|" << endl;
		grey_color();


		cout << "\t|_________________|";
		cout << "      |_______________|";
		cout << "      |________________________|";
		cout << "      |____________________|";
		yellow_color();
		cout << "      |/______________________/" << endl;
		grey_color();

		white_color();
	}
	void tab_groups_gc()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t\t  _____________________ ";
		yellow_color();
		cout << "\t\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t\t |                     |";
		yellow_color();
		cout << "\t\t /|     GROUPS  CHATS    |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t\t |        GROUPS       |";
		yellow_color();
		cout << "\t\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t\t |_____________________| ";
		yellow_color();
		cout << "\t\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_groups_gc_lc()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t  _____________________ ";
		cout << "\t  _______________________ ";
		yellow_color();
		cout << "\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t |                     |";
		cout << "\t |                        |";
		yellow_color();
		cout << "\t /|   LIVE CONERSATION   |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t |        GROUPS       |";
		cout << "\t |   GROUP  CONVERSATION  |";
		yellow_color();
		cout << "\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t |_____________________| ";
		cout << "\t |________________________| ";
		yellow_color();
		cout << "\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_groups_gc_vc()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t  _____________________ ";
		cout << "\t  _______________________ ";
		yellow_color();
		cout << "\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t |                     |";
		cout << "\t |                        |";
		yellow_color();
		cout << "\t /|      VIEW CHATS      |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t |        GROUPS       |";
		cout << "\t |   GROUP  CONVERSATION  |";
		yellow_color();
		cout << "\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t |_____________________| ";
		cout << "\t |________________________| ";
		yellow_color();
		cout << "\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_setting_cp()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t\t  _____________________ ";
		yellow_color();
		cout << "\t\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t\t |                     |";
		yellow_color();
		cout << "\t\t /|   CHANGE PASSWORD    |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t\t |      SETTINGS       |";
		yellow_color();
		cout << "\t\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t\t |_____________________| ";
		yellow_color();
		cout << "\t\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_setting_ct()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t\t  _____________________ ";
		yellow_color();
		cout << "\t\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t\t |                     |";
		yellow_color();
		cout << "\t\t /|     CHANGE  THEME    |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t\t |      SETTINGS       |";
		yellow_color();
		cout << "\t\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t\t |_____________________| ";
		yellow_color();
		cout << "\t\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_setting_gb()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t\t  _____________________ ";
		yellow_color();
		cout << "\t\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t\t |                     |";
		yellow_color();
		cout << "\t\t /|       GET  BACKUP    |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t\t |      SETTINGS       |";
		yellow_color();
		cout << "\t\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t\t |_____________________| ";
		yellow_color();
		cout << "\t\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_setting_gp()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t\t  _____________________ ";
		yellow_color();
		cout << "\t\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t\t |                     |";
		yellow_color();
		cout << "\t\t /|      GET  PREMIUM    |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t\t |       SETTINGS      |";
		yellow_color();
		cout << "\t\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t\t |_____________________| ";
		yellow_color();
		cout << "\t\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_setting_vp()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t\t  _____________________ ";
		yellow_color();
		cout << "\t\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t\t |                     |";
		yellow_color();
		cout << "\t\t /|     VIEW  PROFILE    |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t\t |       SETTINGS      |";
		yellow_color();
		cout << "\t\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t\t |_____________________| ";
		yellow_color();
		cout << "\t\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
	void tab_setting_da()
	{
		gotoxy(0, 1);
		grey_color();
		cout << "\t\t  _____________________ ";
		cout << "\t\t  _____________________ ";
		yellow_color();
		cout << "\t\t   ======================= " << endl;
		grey_color();


		cout << "\t\t |                     |";
		cout << "\t\t |                     |";
		yellow_color();
		cout << "\t\t /|    DELETE  ACCOUNT   |" << endl;
		grey_color();


		cout << "\t\t |      DASHBOARD      |";
		cout << "\t\t |       SETTINGS      |";
		yellow_color();
		cout << "\t\t| |______________________|" << endl;
		grey_color();


		cout << "\t\t |_____________________| ";
		cout << "\t\t |_____________________| ";
		yellow_color();
		cout << "\t\t|/______________________/ " << endl;
		grey_color();

		white_color();
	}
};

//string Design::color;

int Design::theme = 0;
string Design::color;
Design des;


// End Previous Here

class organization_files final {
public:
	static constexpr const char* user_credentials = "User_Credentials.txt";
	static constexpr const char* user_address = "User_address.txt";
	static constexpr const char* group = "Groups.txt";
	static constexpr const char* group_members = "Group_Members.txt";
	static constexpr const char* friends = "Friends.txt";
	static constexpr const char* friend_request = "Friend_Request.txt";
	static constexpr const char* status = "Status.txt";
	static constexpr const char* temp = "Temp.txt";
};

class Components
{
public:

	static int generate_id(string file_name)
	{
		int id = 0, file_id = 0;
		string line;
		ifstream output(file_name.c_str());
		if (output)
		{
			while (getline(output, line))
			{
				istringstream data(line);
				string temp;
				data >> temp;

				Components::get_decrypt_text(temp);
				file_id = get_stoi(temp);

				if (id < file_id)
				{
					id = file_id;
				}
			}
			output.close();
		}
		return ++id;
	}

	static string generate_OTP()
	{
		string file_name, file_password, file_OTP, line;
		// Generating OTP
		int n;
		char OTP[7];
		srand(static_cast<unsigned int>(time(0)));
		for (int i = 0;i < 6;i++)
		{
			n = rand() % 10;
			OTP[i] = static_cast<char>(n + '0');
		}
		OTP[6] = '\0';

		return OTP;
		// End Generating OTP

	}

	static void get_encrypt_text(string& text)
	{
		char ch[62] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
		for (int i = 0;i < text.length();i++)
		{
			if (text[i] != ' ')
			{
				for (int j = 0;j < 62;j++)
				{
					if (ch[j] == text[i])
					{
						int n = (j + text.length()) % 62;
						text[i] = ch[n];
						break;
					}
				}
			}
			else
			{
				text[i] = '_';
			}

		}
	}

	static void get_decrypt_text(string& text)
	{
		char ch[62] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
		for (int i = 0;i < text.length();i++)
		{
			if (text[i] != '_')
			{
				for (int j = 0;j < 62;j++)
				{
					if (ch[j] == text[i])
					{
						int n = (j - text.length() + 62) % 62;
						text[i] = ch[n];
						break;
					}
				}
			}
			else
			{
				text[i] = ' ';
			}

		}
	}

	// Input Values Functions

	static char input_color()
	{
		int i = 0;
		char pass;
		char a;
		while (1)
		{
			a = _getch();
			if ((a >= '1' && a <= '5') && i < 1)
			{
				pass = a;//stores a in pass
				++i;
				cout << a;
			}
			else if (a == '\b' && i >= 1)//if user typed backspace
			{
				cout << "\b \b";//rub the character behind the cursor.
				--i;
			}
			else if (a == '\r' && i > 0)//if enter is pressed
			{
				break;//break the loop
			}
		}
		return pass;
	}

	static string input_email()
	{
		int i = 0;
		char pass[64];
		char a;

		while (true)
		{
			a = _getch();

			if (a == '\b' && i > 0)
			{
				cout << "\b \b";
				--i;
			}
			else if (a == '\r' && i > 0)
			{
				pass[i] = '\0';
				break;
			}
			else if (i < 63 && isprint(a)) {
				pass[i] = a;
				++i;
				cout << a;
			}
		}
		return string(pass);
	}

	static string input_text_value()
	{
		int i = 0;
		char pass[20];
		char a;
		while (1)
		{
			a = _getch();
			if (((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9') || (a == ' ')) && i < 19)
			{
				pass[i] = a;//stores a in pass
				++i;
				cout << a;
			}
			else if (a == '\b' && i >= 1)//if user typed backspace
			{
				cout << "\b \b";//rub the character behind the cursor.
				--i;
			}
			else if (a == '\r' && i > 0)//if enter is pressed
			{
				pass[i] = '\0';//null means end of string.
				break;//break the loop
			}
		}
		return string(pass);
	}

	static string input_number_value()
	{
		int i = 0;
		char pass[20];
		char a;
		while (1)
		{
			a = _getch();
			if ((a >= '0' && a <= '9') && i < 19)
			{
				pass[i] = a;//stores a in pass
				++i;
				cout << a;
			}
			else if (a == '\b' && i >= 1)//if user typed backspace
			{
				cout << "\b \b";//rub the character behind the cursor.
				--i;
			}
			else if (a == '\r' && i > 0)//if enter is pressed
			{
				pass[i] = '\0';//null means end of string.
				break;//break the loop
			}
		}
		return string(pass);
	}

	static string input_date_value()
	{
		int i = 0;
		char pass[11];
		char a;
		while (1)
		{
			a = _getch();
			if (((a >= '0' && a <= '9') || a == '-') && i < 10)
			{
				pass[i] = a;//stores a in pass
				++i;
				cout << a;
			}
			else if (a == '\b' && i >= 1)//if user typed backspace
			{
				cout << "\b \b";//rub the character behind the cursor.
				--i;
			}
			else if (a == '\r' && i == 10)//if enter is pressed
			{
				pass[i] = '\0';//null means end of string.
				break;//break the loop
			}
		}
		return string(pass);
	}

	static string input_password()
	{
		int i = 0;
		char pass[20];
		char a;
		bool check = true;
		while (1)
		{
			a = _getch();
			if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9') && i < 19)
			{
				pass[i] = a;//stores a in pass
				++i;
				if (check)
				{
					cout << "*";
				}
				else
				{
					cout << a;
				}
				
			}
			else if (a == '\b' && i >= 1)//if user typed backspace
			{
				cout << "\b \b";//rub the character behind the cursor.
				--i;
			}
			else if (a == '\r' && i >= 8)//if enter is pressed
			{
				pass[i] = '\0';//null means end of string.
				break;//break the loop
			}
			else if (a == '\t')
			{
				if (check)
				{
					for (int j = 0;j < i;j++)
					{
						cout << "\b \b";
					}
					for (int j = 0;j < i;j++)
					{
						cout << pass[j];
					}
					check = false;
				}
				else
				{
					for (int j = 0;j < i;j++)
					{
						cout << "\b \b";
					}
					for (int j = 0;j < i;j++)
					{
						cout << "*";
					}
					check = true;
				}
			}
		}
		cout << endl;
		return string(pass);
	}

	static string input_OTP()
	{
		int i = 0;
		char pass[7];
		char a;
		while (1)
		{
			a = _getch();
			if (a >= '0' && a <= '9')
			{
				pass[i] = a;//stores a in pass
				++i;
				cout << a;
			}
			else if (a == '\b' && i >= 1)//if user typed backspace
			{
				cout << "\b \b";//rub the character behind the cursor.
				--i;
			}
			if (i == 6)
			{
				pass[i] = '\0';//null means end of string.
				break;//break the loop
			}
		}
		cout << endl;
		return string(pass);
	}

	static string input_account_no()
	{
		int i = 0;
		char pass[17];
		char a;
		while (1)
		{
			a = _getch();
			if ((a >= '0' && a <= '9') && i < 16)
			{
				pass[i] = a;//stores a in pass
				++i;
				cout << a;
			}
			else if (a == '\b' && i >= 1)//if user typed backspace
			{
				cout << "\b \b";//rub the character behind the cursor.
				--i;
			}
			else if (i == 16 && a == '\r')
			{
				pass[i] = '\0';//null means end of string.
				break;//break the loop
			}
		}
		cout << endl;
		return string(pass);
	}

	static string input_string_choice()
	{
		int i = 0;
		char pass[4];
		char a;
		while (1)
		{
			a = _getch();

			if (i == 0 && (a == 'Y' || a == 'N'))
			{
				pass[i++] = a;
				cout << a;
			}
			else if (i == 1 && a == 'o' && pass[0] == 'N')
			{
				pass[i++] = a;
				cout << a;
			}
			else if (i == 1 && a == 'e' && pass[0] == 'Y')
			{
				pass[i++] = a;
				cout << a;
			}
			else if (i == 2 && a == 's' && pass[0] == 'Y' && pass[1] == 'e')
			{
				pass[i++] = a;
				cout << a;
			}
			else if (a == '\b' && i >= 1)//if user typed backspace
			{
				cout << "\b \b";//rub the character behind the cursor.
				--i;
			}
			else if (((i == 2 && pass[0] == 'N' && pass[1] == 'o') || (i == 3 && pass[0] == 'Y' && pass[1] == 'e' && pass[2] == 's')) && a == '\r')
			{
				pass[i] = '\0';//null means end of string.
				break;//break the loop
			}
		}
		cout << endl;
		return string(pass);
	}

	static string input_approval()
	{
		int i = 0;
		char pass[7];
		char a;
		while (1)
		{
			a = _getch();
			if (((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')) && i < 6)
			{
				pass[i] = a;//stores a in pass
				++i;
				cout << a;
			}
			else if (a == '\b' && i >= 1)//if user typed backspace
			{
				cout << "\b \b";//rub the character behind the cursor.
				--i;
			}
			else if (a == '\r' && i == 6)//if enter is pressed
			{
				pass[i] = '\0';//null means end of string.
				if (string(pass) == "Accept" || string(pass) == "Reject")
				{
					break;
				}
				else
				{
					for (int i = 0;i < 6;i++)
					{
						cout << "\b \b";
					}
					i = 0;
				}

			}
		}
		cout << endl;
		return string(pass);
	}


	// End



	// Validation 

	static void check_date(string& date)
	{
		bool display = true;
		while (1)
		{
			if (date.length() == 10)
			{
				char d[3] = { date[0], date[1], '\0' };
				char m[3] = { date[3], date[4], '\0' };
				char y[5] = { date[6], date[7], date[8], date[9], '\0' };
				int f_d = atoi(d);
				int f_m = atoi(m);
				int f_y = atoi(y);

				if (date[2] == '-' && date[5] == '-')
				{
					if (f_m == 2)
					{
						if ((f_y % 4 == 0 && f_d > 0 && f_d <= 29) || (f_y % 4 != 0 && f_d > 0 && f_d <= 28))
						{
							break;
						}
					}
					else if (f_m == 1 || f_m == 3 || f_m == 5 || f_m == 7 || f_m == 8 || f_m == 10 || f_m == 12)
					{
						if (f_d > 0 && f_d <= 31)
						{
							break;
						}
					}
					else if (f_m == 4 || f_m == 6 || f_m == 9 || f_m == 11)
					{
						if (f_d > 0 && f_d <= 30)
						{
							break;
						}
					}
				}
			}

			if (display)
			{
				display = false;
				int p = 34;
				des.display_invalid_p("Date", p);
				des.display_enter("Enter Correct Date", "DD-MM-YYYY", p + 2);
				//				cout << "Enter Correct Date [DD-MM-YYYY] :";
			}
			else
			{
				for (int i = 0;i < date.length();i++)
				{
					cout << "\b \b";
				}
			}
			date = input_date_value();
		}
	}

	// End Validation

	static string get_current_date()
	{
		time_t tim = time(0);
		tm timeinfo;  // Use a struct to hold time information

		// Use localtime_s for safer local time retrieval
		localtime_s(&timeinfo, &tim);  // This is the safer alternative

		// Format the date as dd-mm-yyyy
		string date =
			to_string(timeinfo.tm_mday) + '-' +
			to_string(timeinfo.tm_mon + 1) + '-' +
			to_string(timeinfo.tm_year + 1900);

		return date;
	}

	static string get_current_time()
	{
		time_t tim = time(0);
		tm timeinfo;  // Use a struct to hold time information

		// Use localtime_s for safer local time retrieval
		localtime_s(&timeinfo, &tim);  // This is the safer alternative

		// Format the time as hh:mm:ss
		string time =
			to_string(timeinfo.tm_hour) + ':' +
			to_string(timeinfo.tm_min) + ':' +
			to_string(timeinfo.tm_sec);

		// Optional: Add leading zeros for single-digit values
		time = (timeinfo.tm_hour < 10 ? "0" : "") + to_string(timeinfo.tm_hour) + ':' +
			(timeinfo.tm_min < 10 ? "0" : "") + to_string(timeinfo.tm_min) + ':' +
			(timeinfo.tm_sec < 10 ? "0" : "") + to_string(timeinfo.tm_sec);

		return time;
	}

	static void convert_date(string& date)
	{
		char day[2] = { date[0],date[1] };
		int d = atoi(day);
		char month[2] = { date[3],date[4] };
		int m = atoi(month);
		char year[4] = { date[6],date[7],date[8],date[9] };
		int y = atoi(year);

		date = get_itos(d) + '-' + get_itos(m) + '-' + get_itos(y);

	}

	static int get_stoi(string value)
	{
		int var;
		stringstream temp(value);
		temp >> var;
		return var;
	}

	static string get_itos(int n)
	{
		string a;
		stringstream data;
		data << n;
		data >> a;
		return a;
	}

	static string getMACAddress()
	{
		array<char, 128> buffer;
		string result;
		string command = "getmac"; // Command to retrieve MAC address in Windows

		// Open a pipe to execute the command
		FILE* pipe = _popen(command.c_str(), "r");
		if (!pipe) return "Error: Unable to open pipe.";

		// Read the command output
		while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
			result += buffer.data();
		}

		_pclose(pipe);

		// Find the MAC address (first valid entry)
		istringstream stream(result);

		string line;

		while (getline(stream, line)) {
			if (line.find("-") != string::npos) {  //MAC address contains '-'
				return line.substr(0, 17);  //Return the first valid MAC address
			}
		}

		return "Error";
	}

};


// End Previous Here

class User_Credentials
{

	string username;
	string email;
	string password;
	string tier;
	string join_date;

	User_Credentials* next_node;

public:

	void set_next_node(User_Credentials* Node)
	{
		next_node = Node;
	}

	void set_username(string value)
	{
		username = value;
	}

	void set_email(string value)
	{
		email = value;
	}

	void set_password(string value)
	{
		password = value;
	}

	void set_tier(string value)
	{
		tier = value;
	}

	void set_join_date(string value)
	{
		join_date = value;
	}

	string get_username()
	{
		return username;
	}

	string get_email()
	{
		return email;
	}

	string get_password()
	{
		return password;
	}

	string get_tier()
	{
		return tier;
	}

	string get_join_date()
	{
		return join_date;
	}

	User_Credentials* get_next_node()
	{
		return next_node;
	}

};

class User_Credentials_List
{

	int size;
	User_Credentials* head_node;
	User_Credentials* last_current_node;
	User_Credentials* current_node;

public:

	User_Credentials_List()
	{
		size = 0;
		head_node = NULL;
		current_node = NULL;
	}

	void insert(string value, string value1, string value2, string value3, string value4)
	{
		if (current_node != NULL)
		{
			User_Credentials* new_node = new User_Credentials;

			new_node->set_username(value);
			new_node->set_email(value1);
			new_node->set_password(value2);
			new_node->set_tier(value3);
			new_node->set_join_date(value4);
			new_node->set_next_node(NULL);
			current_node->set_next_node(new_node);
			current_node = new_node;
		}
		else
		{
			head_node = new User_Credentials;
			head_node->set_username(value);
			head_node->set_email(value1);
			head_node->set_password(value2);
			head_node->set_tier(value3);
			head_node->set_join_date(value4);
			head_node->set_next_node(NULL);

			current_node = head_node;
		}
		size++;

	}

	void get_values()
	{
		ifstream output(organization_files::user_credentials);

		string username, email, password, tier, date;

		if (output)
		{
			string line;
			while (getline(output, line))
			{
				istringstream data(line);
				data >> username >> email >> password >> tier >> date;

				Components::get_decrypt_text(username);
				Components::get_decrypt_text(email);
				Components::get_decrypt_text(password);
				Components::get_decrypt_text(tier);
				Components::get_decrypt_text(date);

				insert(username, email, password, tier, date);
			}
			output.close();
		}

	}

	bool check_username(string name)
	{
		bool check = true;
		if (size > 0)
		{
			current_node = head_node;
			while (current_node != NULL)
			{
				if (current_node->get_username() == name)
				{
					check = false;
				}
				if (current_node->get_next_node() == NULL)
				{
					break;
				}
				current_node = current_node->get_next_node();
			}
		}
		return check;
	}

	bool check_email(string email)
	{
		bool check = false;
		if (size > 0)
		{
			current_node = head_node;
			while (current_node != NULL)
			{
				if (current_node->get_email() == email)
				{
					check = true;
				}
				if (current_node->get_next_node() == NULL)
				{
					break;
				}
				current_node = current_node->get_next_node();
			}
		}
		return check;
	}

	int check_login(string name, string password, string& tier)
	{
		int check = 0;
		if (size > 0)
		{
			current_node = head_node;
			while (current_node != NULL)
			{
				if (current_node->get_username() == name && current_node->get_password() == password)
				{
					check = 1;
					tier = current_node->get_tier();
					break;
				}
				if (current_node->get_next_node() == NULL)
				{
					break;
				}
				current_node = current_node->get_next_node();
			}
		}
		else
		{
			des.display_no_record_p(12);
			//			cout << "File OR Record Not Found " << endl;
			check = 2;
		}

		return check;
	}

	void display(string username, string pass)
	{
		if (size > 0)
		{
			bool check = false;
			current_node = head_node;
			while (1)
			{
				if (current_node->get_username() == username && current_node->get_password() == pass)
				{
					check = true;
					//					system("CLS");
					vector <string> accountInfo;
					accountInfo.push_back(current_node->get_username());
					accountInfo.push_back(current_node->get_email());
					accountInfo.push_back(current_node->get_password());
					accountInfo.push_back(current_node->get_tier());
					accountInfo.push_back(current_node->get_join_date());

					des.accountInfo(accountInfo);

				}
				if (current_node->get_next_node() == NULL)
				{
					break;
				}
				current_node = current_node->get_next_node();
			}
			if (!check)
			{
				//				cout << "\nIncorrect Password";
				int p = 12;
				des.display_invalid_p("Password", p);
			}
		}
		else
		{
			//			cout << "File OR Record Not Found";
			des.display_file_p(12);
		}

	}

	~User_Credentials_List()
	{
		User_Credentials* temp;
		while (head_node != NULL)
		{
			temp = head_node->get_next_node();
			delete head_node;
			head_node = temp;
		}
	}


};


// End Previous Here


class Client_Script
{
	string message;
	int i = 0;
	atomic<bool> running; // Flag to control the running state of threads

	string input_text_value()
	{
		i = 0;
		char pass[30];
		char a;
		while (1)
		{
			a = _getch();

			if (a == '\b' && i >= 1) // if user typed backspace
			{
				cout << "\b \b"; // rub the character behind the cursor.
				--i;
			}
			else if (a == '\r' && i > 0) // if enter is pressed
			{
				pass[i] = '\0'; // null means end of string.
				break; // break the loop
			}
			else if (i < 29)
			{
				pass[i] = a; // stores a in pass
				++i;
				cout << a;
			}
		}
		return string(pass);
	}

	bool Initialize_client()
	{
		WSADATA data;
		return WSAStartup(MAKEWORD(2, 2), &data) == 0;
	}

	void SendMsg(SOCKET s, string s_n, string r_n, string function, string filename)
	{
		string recieverName = r_n;
		string senderName = s_n;
		message = senderName + " " + recieverName + " " + function;

		int sendbyte = send(s, message.c_str(), message.length(), 0);
		if (sendbyte == SOCKET_ERROR)
		{
			cout << "Error Sending Message: " << WSAGetLastError() << endl;
			return;
		}

		while (running) // Check if the application is still running
		{
			message = input_text_value();

			if (message == "quit")
			{
				string msg = message;
				int bytesSent = send(s, msg.c_str(), msg.length(), 0);
				cout << "Stopping the application" << endl;
				running = false; // Set the running flag to false
				break;
			}
			else
			{
				string msg = message;

				// Components::get_encrypt_text(msg);

				msg = senderName + " " + msg;

				Components::get_encrypt_text(msg);

				int bytesSent = send(s, msg.c_str(), msg.length(), 0);

				if (bytesSent == SOCKET_ERROR)
				{
					cout << "Error Sending Message: " << WSAGetLastError() << endl;
					break;
				}
				else
				{
					string id = to_string(Components::generate_id(filename));
					string s_name = senderName;
					string date = Components::get_current_date();
					string time = Components::get_current_time();
					string status = "Yes";

					// displaying msg in format

					remove_entered_text();

					string dateTime = " ON : " + date + " AT : " + time;
					des.skin_color();
					cout << setw(des.getTerminalWidth() / 2 + dateTime.length() / 2) << right << dateTime << endl;
					des.white_color();

					des.printRightAligned("ID: " + id + "   @ " + s_name, false);
					des.skin_color();
					des.printRightAligned(message, true);
					des.white_color();

					des.display_line();

					Components::get_encrypt_text(id);
					Components::get_encrypt_text(s_name);
					Components::get_encrypt_text(message);
					Components::get_encrypt_text(date);
					Components::get_encrypt_text(time);
					Components::get_encrypt_text(status);

					ofstream inputfile(filename.c_str(), ios::app);
					inputfile << id << " " << s_name << " " << message << " " << date << " " << time << " " << status << endl;
					inputfile.close();
				}
			}
		}
	}

	void ReceiveMsg(SOCKET s, string filename)
	{
		char buffer[4096];
		int recvLength;

		while (running) // Check if the application is still running
		{
			recvLength = recv(s, buffer, sizeof(buffer), 0);

			if (recvLength <= 0)
			{
				cout << "Disconnected from the server: " << WSAGetLastError() << endl;
				running = false; // Set the running flag to false if disconnected
				break;
			}
			else
			{
				string msg = string(buffer, recvLength);

				Components::get_decrypt_text(msg);

				istringstream data(msg);
				string senderName;
				data >> senderName;

				string temp;
				msg = "";

				while (data >> temp)
				{
					msg += " " + temp;
				}
				if (msg == "quit")
				{
					break;
				}
				else
				{

					string id = to_string(Components::generate_id(filename));
					string date = Components::get_current_date();
					string time = Components::get_current_time();
					string status = "Yes";

					remove_entered_text();

					string dateTime = " ON : " + date + " AT : " + time;
					des.skin_color();
					cout << setw(des.getTerminalWidth() / 2 + dateTime.length() / 2) << right << dateTime << endl;
					des.white_color();

					des.printLeftAligned("ID: " + id + "   @ " + senderName, false);
					des.blue_color();
					des.printLeftAligned(msg, true);
					des.white_color();

					des.display_line();

					Components::get_encrypt_text(id);
					Components::get_encrypt_text(senderName);
					Components::get_encrypt_text(msg);
					Components::get_encrypt_text(date);
					Components::get_encrypt_text(time);
					Components::get_encrypt_text(status);

					ofstream inputfile(filename.c_str(), ios::app);
					inputfile << id << " " << senderName << " " << msg << " " << date << " " << time << " " << status << endl;
					inputfile.close();
				}
			}
		}
	}

	void remove_entered_text()
	{
		for (int j = 1; j <= i; j++)
		{
			cout << "\b \b";
		}
	}

public:
	Client_Script(string pass_sender, string pass_reciver, string pass_function, string pass_filename)
		: running(true) // Initialize the running flag to true
	{
		if (!Initialize_client())
		{
			cout << "\nWinsock initialization failed" << endl;
			return;
		}

		// Creating a new socket      
		SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

		if (s == INVALID_SOCKET)
		{
			cout << "\nSocket Creation Failed: " << WSAGetLastError() << endl;
			return;
		}

		// Server Local Address         
		string server_address = "127.0.0.1";

		// Create Address Structure     
		sockaddr_in serveraddr;
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_port = htons(1234);

		// Use inet_pton to convert IP address to binary format     
		if (inet_pton(AF_INET, server_address.c_str(), &serveraddr.sin_addr) <= 0)
		{
			cout << "\nInvalid address" << endl;
			closesocket(s);
			WSACleanup();
			return;
		}

		if (connect(s, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR)
		{
			cout << "\nNot able to connect to server: " << WSAGetLastError() << endl;
			closesocket(s);
			WSACleanup();
			return;
		}

		cout << "Successfully Connected to server" << endl;

		// Start threads for sending and receiving messages     
		thread senderThread(&Client_Script::SendMsg, this, s, pass_sender, pass_reciver, pass_function, pass_filename);
		thread receiverThread(&Client_Script::ReceiveMsg, this, s, pass_filename);

		senderThread.join();  // Wait for sender thread to finish     
		receiverThread.join(); // Wait for receiver thread to finish      

		closesocket(s);  // Close the socket after everything is done     
		WSACleanup();    // Clean up Winsock at the end of the program     
	}
};

// End Previous Here


class Node {
private:
	string msg_id;
	string sender_name;
	string message;
	string date;
	string time;
	string status;
	Node* left;
	Node* right;
	int height;

public:
	Node()
	{

	}

	Node(string id, string sender, string msg, string d, string t, string s)
		: msg_id(id), sender_name(sender), message(msg), date(d), time(t), status(s), left(nullptr), right(nullptr), height(1) {
	}

	void set_left(Node* pass) { left = pass; }
	void set_right(Node* pass) { right = pass; }
	void set_height(int h) { height = h; }
	string get_msg_id() { return msg_id; }
	string get_sender_name() { return sender_name; }
	string get_message() { return message; }
	string get_date() { return date; }
	string get_time() { return time; }
	string get_status() { return status; }
	Node* get_left() { return left; }
	Node* get_right() { return right; }
	int get_height() { return height; }
};

class Chat_AVL_Tree {
private:
	Node* root;

	// Helper functions
	int height(Node* node) {
		return node ? node->get_height() : 0;
	}

	int getBalance(Node* node) {
		return node ? height(node->get_left()) - height(node->get_right()) : 0;
	}

	Node* rightRotate(Node* y) {
		Node* x = y->get_left();
		Node* T2 = x->get_right();

		x->set_right(y);
		y->set_left(T2);

		y->set_height(max(height(y->get_left()), height(y->get_right())) + 1);
		x->set_height(max(height(x->get_left()), height(x->get_right())) + 1);

		return x;
	}

	Node* leftRotate(Node* x) {
		Node* y = x->get_right();
		Node* T2 = y->get_left();

		y->set_left(x);
		x->set_right(T2);

		x->set_height(max(height(x->get_left()), height(x->get_right())) + 1);
		y->set_height(max(height(y->get_left()), height(y->get_right())) + 1);

		return y;
	}

	Node* insert(Node* node, string id, string sender, string msg, string d, string t, string s) {
		if (!node) return new Node(id, sender, msg, d, t, s);
		if (id < node->get_msg_id())
			node->set_left(insert(node->get_left(), id, sender, msg, d, t, s));
		else if (id > node->get_msg_id())
			node->set_right(insert(node->get_right(), id, sender, msg, d, t, s));
		else // Duplicate keys are not allowed
			return node;

		node->set_height(1 + max(height(node->get_left()), height(node->get_right())));

		int balance = getBalance(node);

		// Left Left Case
		if (balance > 1 && id < node->get_left()->get_msg_id())
			return rightRotate(node);

		// Right Right Case
		if (balance < -1 && id > node->get_right()->get_msg_id())
			return leftRotate(node);

		// Left Right Case
		if (balance > 1 && id > node->get_left()->get_msg_id()) {
			node->set_left(leftRotate(node->get_left()));
			return rightRotate(node);
		}

		// Right Left Case
		if (balance < -1 && id < node->get_right()->get_msg_id()) {
			node->set_right(rightRotate(node->get_right()));
			return leftRotate(node);
		}

		return node;
	}

	void inorder(Node* root) {
		if (root) {

			inorder(root->get_left());
			if (root->get_status() == "Yes" || (root->get_status() == "No"))
			{
				if (root->get_status() == "No" && static_tier == "premium")
				{

					if (root->get_sender_name() == static_username)
					{
						string dateTime = " ON : " + root->get_date() + " AT : " + root->get_time();
						des.skin_color();
						cout << setw(des.getTerminalWidth() / 2 + dateTime.length() / 2) << right << dateTime << endl;
						des.white_color();
						des.printRightAligned("ID: " + root->get_msg_id() + "   @ " + root->get_sender_name(), false);
						des.red_color();
						des.printRightAligned(root->get_message(), true);
						des.white_color();

						des.display_line();
					}
					else
					{
						string dateTime = " ON : " + root->get_date() + " AT : " + root->get_time();
						des.skin_color();
						cout << setw(des.getTerminalWidth() / 2 + dateTime.length() / 2) << right << dateTime << endl;
						des.white_color();
						des.printLeftAligned("ID: " + root->get_msg_id() + "   @ " + root->get_sender_name(), false);
						des.red_color();
						des.printLeftAligned(root->get_message(), true);
						des.white_color();

						des.display_line();
					}

				}
				else if (root->get_status() == "No" && static_tier == "simple")
				{
					if (root->get_sender_name() == static_username)
					{
						string dateTime = " ON : " + root->get_date() + " AT : " + root->get_time();
						des.skin_color();
						cout << setw(des.getTerminalWidth() / 2 + dateTime.length() / 2) << right << dateTime << endl;
						des.white_color();

						des.printRightAligned("ID: " + root->get_msg_id() + "   @ " + root->get_sender_name(), false);
						des.red_color();
						des.printRightAligned("This message was deleted purchase premiuim to view this!", false);
						des.white_color();

						des.display_line();
					}
					else
					{
						string dateTime = " ON : " + root->get_date() + " AT : " + root->get_time();
						des.skin_color();
						cout << setw(des.getTerminalWidth() / 2 + dateTime.length() / 2) << right << dateTime << endl;
						des.white_color();

						des.printLeftAligned("ID: " + root->get_msg_id() + "   @ " + root->get_sender_name(), false);
						des.red_color();
						des.printLeftAligned("This message was deleted purchase premiuim to view this!", false);
						des.white_color();

						des.display_line();
					}

				}

				else if (root->get_sender_name() == static_username)
				{
					string dateTime = " ON : " + root->get_date() + " AT : " + root->get_time();
					des.skin_color();
					cout << setw(des.getTerminalWidth() / 2 + dateTime.length() / 2) << right << dateTime << endl;
					des.white_color();

					des.printRightAligned("ID: " + root->get_msg_id() + "   @ " + root->get_sender_name(), false);
					des.skin_color();
					des.printRightAligned(root->get_message(), true);
					des.white_color();

					des.display_line();
				}
				else
				{
					string dateTime = " ON : " + root->get_date() + " AT : " + root->get_time();
					des.skin_color();
					cout << setw(des.getTerminalWidth() / 2 + dateTime.length() / 2) << right << dateTime << endl;
					des.white_color();

					des.printLeftAligned("ID: " + root->get_msg_id() + "   @ " + root->get_sender_name(), false);
					des.blue_color();
					des.printLeftAligned(root->get_message(), true);
					des.white_color();

					des.display_line();
				}

			}
			inorder(root->get_right());

			des.white_color();
		}
	}



	Node* search(Node* root, const string& id) {
		if (root == nullptr || (root->get_msg_id() == id && root->get_sender_name() == static_username))
			return root;

		if (id < root->get_msg_id())
			return search(root->get_left(), id);
		else
			return search(root->get_right(), id);
	}

	bool load_chats_from_file(string file_name, string pass_data, string process)
	{
		bool record = false;
		ifstream chatFile(file_name.c_str());
		if (!chatFile)
		{
			des.display_file_p(35);
			return record;
		}

		string line;
		while (getline(chatFile, line))
		{
			istringstream data(line);
			string msg_id, sender, message, date, time, status;
			data >> msg_id >> sender >> message >> date >> time >> status;

			Components::get_decrypt_text(msg_id);
			Components::get_decrypt_text(sender);
			Components::get_decrypt_text(message);
			Components::get_decrypt_text(date);
			Components::get_decrypt_text(time);
			Components::get_decrypt_text(status);

			if (process == "Date")
			{
				if (pass_data == date)
				{
					record = true;
					root = insert(root, msg_id, sender, message, date, time, status);
				}
			}
			else if (process == "Text")
			{
				if (pass_data == message)		// Be like functions will be used there
				{
					record = true;
					root = insert(root, msg_id, sender, message, date, time, status);
				}

			}
		}
		chatFile.close();
		if (!record)
		{

			des.border();
			des.display_no_record_p(35);
		}
		return record;
	}

	void deleteAVLTree(Node* root) {
		if (root == nullptr) {
			return;
		}
		deleteAVLTree(root->get_left());
		deleteAVLTree(root->get_right());
		delete root;
	}

public:

	Chat_AVL_Tree(string file_name, string pass_data, string process)
	{
		system("CLS");
		int p = 10;
		while (1)
		{

			root = nullptr;
			if (load_chats_from_file(file_name, pass_data, process))
			{
				string value;
				displayInOrder();
				//				des.display_do_you_p("Do You Want to Delete Any Record","Yes/No",p);
				des.display_do_you("Do You Want to Delete Any Record", "Yes/No");
				value = Components::input_string_choice();
				p = des.getCurrentLinePosition();
				if (value == "Yes")
				{
					p += 2;
					des.display_enter("Enter Message ID", p);
					value = Components::input_number_value();

					Node* msg_values = searchById(value);

					if (msg_values)
					{
						ifstream output(file_name);
						if (output)
						{
							ofstream temp(organization_files::temp);
							string line;
							bool record = false;
							while (getline(output, line))
							{
								istringstream data(line);
								string msg_id, sender, message, date, time, status;
								data >> msg_id >> sender >> message >> date >> time >> status;

								Components::get_decrypt_text(msg_id);
								Components::get_decrypt_text(sender);
								Components::get_decrypt_text(message);
								Components::get_decrypt_text(date);
								Components::get_decrypt_text(time);
								Components::get_decrypt_text(status);

								if (msg_id == msg_values->get_msg_id() && sender == msg_values->get_sender_name() && status == "Yes")
								{
									record = true;

									status = "No";

									Components::get_encrypt_text(msg_id);
									Components::get_encrypt_text(sender);
									Components::get_encrypt_text(message);
									Components::get_encrypt_text(date);
									Components::get_encrypt_text(time);
									Components::get_encrypt_text(status);

									temp << msg_id << " " << sender << " " << message << " " << date << " " << time << " " << status << endl;
								}
								else
								{
									temp << line << endl;
								}

							}

							output.close();
							temp.close();

							const char* filePath = file_name.c_str();
							remove(filePath);
							rename(organization_files::temp, filePath);

							if (record)
							{
								//								cout << "Message Deleted Successfully" << endl;
								p += 2;
								des.display_sucessfully_p("Message Deleted", p);

							}
							else
							{
								cout << "Message Not Deleted" << endl;
							}

							cin.get();

						}
						else
						{
							p += 2;
							des.display_file_p(p);
						}

					}
					else
					{
						p += 2;
						des.display_invalid_p("Invalid ID OR Donot have access to delete this", p);
						cin.get();
					}

				}

				else if (value == "No")
				{
					break;
				}

				deleteAVLTree(root);

			}

			else
			{
				break;
			}
		}

	}

	void displayInOrder() {
		system("CLS");
		inorder(root);
	}

	Node* searchById(string& id) {
		return search(root, id);
	}


};

class chat_management
{

	string choice;
	string file_name;
	string value;
	string line;

	vector<string>* vector_names;
	vector<string>* vector_file_name;

public:

	chat_management(const string value)
	{
		string choice;
		while (true)
		{

			system("CLS");
			vector<string> menuItems = { "Live Conversation", "View Chats", "Back" };
			int position = des.displayMenu(menuItems);
			if (value == "Friend")
			{
				des.tab_friends_fc();
			}
			else
			{
				des.tab_groups_gc();
			}
			des.display_line_slash();

			des.display_enter("Select", "1-3", position);

			choice = Components::input_number_value();

			if (choice == "1")
			{
				// start live conversation here by checking the input
				if (value == "Friend")
				{
					while (1)
					{
						system("CLS");
						des.border();
						des.tab_friends_fc_vc();
						des.display_line_slash();
						vector_names = new vector<string>;
						vector_file_name = new vector<string>;
						get_friends();

						int p = display_friends();
						des.tab_friends_fc_vc();
						des.display_line_slash();
						if (p > 0)
						{
							p++;
							des.display_enter("Enter Friend Name", "Text Only", p);
							choice = Components::input_text_value();
							if (check_input_name(choice))
							{
								system("cls");
								Client_Script obj(static_username,choice,value,get_file_name(choice));
							}
							else if (choice == "Back")
							{
								break;
							}
							else
							{
								p += 2;
								des.display_invalid_p("Name", p);
							}
						}
						else
						{
							break;
						}
						delete vector_names;
						delete vector_file_name;
					}
				}
				else if (value == "Group")
				{
					while (1)
					{
						system("CLS");
						des.border();
						des.tab_groups_gc_vc();
						des.display_line_slash();

						vector_names = new vector<string>;
						get_groups();

						int p = display_groups();
						des.tab_groups_gc_vc();
						des.display_line_slash();
						if (p > 0)
						{
							p++;
							des.display_enter("Enter Group Name", "Text Only", p);
							choice = Components::input_text_value();
							if (check_input_name(choice))
							{
								system("cls");
								Client_Script obj(static_username, choice, value, choice + ".txt");
							}
							else if (choice == "Back")
							{
								break;
							}
							else
							{
								p += 2;
								des.display_invalid_p("Name", p);
							}
						}
						else
						{
							break;
						}
						delete vector_names;
						delete vector_file_name;
					}
				}
				cin.get();
			}
			else if (choice == "2")
			{
				if (value == "Friend")
				{
					while (1)
					{
						system("CLS");
						des.border();
						des.tab_friends_fc_vc();
						des.display_line_slash();
						vector_names = new vector<string>;
						vector_file_name = new vector<string>;
						get_friends();

						int p = display_friends();
						des.tab_friends_fc_vc();
						des.display_line_slash();
						if (p > 0)
						{
							p++;
							des.display_enter("Enter Friend Name", "Text Only", p);
							choice = Components::input_text_value();
							if (check_input_name(choice))
							{
								filtration_on_data(get_file_name(choice));
							}
							else if (choice == "Back")
							{
								break;
							}
							else
							{
								p += 2;
								des.display_invalid_p("Name", p);
							}
						}
						else
						{
							break;
						}
						delete vector_names;
						delete vector_file_name;
					}
				}
				else if (value == "Group")
				{
					while (1)
					{
						system("CLS");
						des.border();
						des.tab_groups_gc_vc();
						des.display_line_slash();

						vector_names = new vector<string>;
						get_groups();

						int p = display_groups();
						des.tab_groups_gc_vc();
						des.display_line_slash();
						if (p > 0)
						{
							p++;
							des.display_enter("Enter Group Name", "Text Only", p);
							choice = Components::input_text_value();
							if (check_input_name(choice))
							{
								filtration_on_data(choice + ".txt");
							}
							else if (choice == "Back")
							{
								break;
							}
							else
							{
								p += 2;
								des.display_invalid_p("Name", p);
							}
						}
						else
						{
							break;
						}
						delete vector_names;
						delete vector_file_name;
					}
				}
				cin.get();
			}
			else if (choice == "3")
			{
				break;
			}
			else
			{
				position += 2;
				des.display_invalid_p("Choice", position);
			}


		}

	}

	void filtration_on_data(string filename)
	{
		this->file_name = filename;
		while (true)
		{
			vector<string> menuItems = { "Latest", "Filter By Date", "Filter By Text", "Return" };
			int position = des.displayMenu(menuItems);
			des.display_enter("Select", "1-4", position);

			choice = Components::input_number_value();

			if (choice == "1")
			{
				value = Components::get_current_date();

				Chat_AVL_Tree chatTree(filename, value, "Date");

				cin.get();
			}
			else if (choice == "2")
			{
				position += 2;

				des.display_enter("Enter Date", "DD-MM-YYYY", position);
				value = Components::input_date_value();
				Components::check_date(value);
				Components::convert_date(value);

				Chat_AVL_Tree chatTree(filename, value, "Date");
				cin.get();
			}
			else if (choice == "3")
			{

				position += 2;
				des.display_enter("Enter Text to Search", position);

				value = Components::input_text_value();

				Chat_AVL_Tree chatTree(filename, value, "Text");
				cin.get();
			}
			else if (choice == "4")
			{
				break;
			}
			else
			{
				position += 2;
				des.display_invalid_p("Selection", position);
			}

		}
	}

	void get_friends()
	{
		ifstream output(organization_files::friends);
		if (output)
		{
			while (getline(output, line))
			{

				string id, user1, user2, file_name;
				istringstream data(line);
				data >> id >> user1 >> user2;

				Components::get_decrypt_text(id);
				Components::get_decrypt_text(user1);
				Components::get_decrypt_text(user2);

				file_name = user1 + user2 + ".txt";

				if (user1 == static_username)
				{
					vector_names->push_back(user2);
					vector_file_name->push_back(file_name);
				}
				else if (user2 == static_username)
				{
					vector_names->push_back(user1);
					vector_file_name->push_back(file_name);
				}
			}
			output.close();
		}
	}

	int display_friends()
	{
		if (vector_names->empty())
		{
			des.display_center("You have no Friends yet");
			cin.get();
			return false;
		}
		return des.displayList(*vector_names);
	}

	bool check_input_name(string name)
	{
		if (vector_names->empty())
		{
			return false;
		}
		for (const auto& friends : *vector_names)
		{
			if (friends == name)
			{
				return true;
			}
		}
		return false;
	}

	string get_file_name(string name)
	{
		if (vector_names->empty())
		{
			return NULL;
		}
		for (int i = 0;i < vector_names->size();i++)
		{
			if ((*vector_names)[i] == name)
			{
				return (*vector_file_name)[i];
			}
		}
		return NULL;
	}

	void get_groups()
	{
		ifstream output(organization_files::group);
		if (output)
		{
			while (getline(output, line))
			{

				string id, name, admin;
				istringstream data(line);
				data >> id >> name >> admin;

				Components::get_decrypt_text(id);
				Components::get_decrypt_text(name);
				Components::get_decrypt_text(admin);

				if (admin == static_username)
				{
					vector_names->push_back(name);
				}
				else
				{
					ifstream output2(organization_files::group_members);
					if (output2)
					{
						while (getline(output2, line))
						{
							string m_id;
							istringstream data2(line);
							data2 >> m_id;

							Components::get_decrypt_text(m_id);
							if (m_id == id)
							{
								string m_name;
								data2 >> m_name;

								Components::get_decrypt_text(m_name);

								if (m_name == static_username)
								{
									vector_names->push_back(name);
								}

							}

						}
						output2.close();
					}
				}
			}
			output.close();
		}
	}

	int display_groups()
	{
		if (vector_names->empty())
		{
			des.display_center("You have no groups yet");
			cin.get();
			return false;
		}

		return des.displayList(*vector_names);
	}

	~chat_management()
	{
		delete vector_names;
		delete vector_file_name;
	}



};



// End Previous Here

class Request_Node
{
	string id;
	string sender;
	string reciever;
	string date;
	Request_Node* next;

public:
	void set_id(string input)
	{
		id = input;
	}
	void set_sender(string input)
	{
		sender = input;
	}
	void set_reciever(string input)
	{
		reciever = input;
	}
	void set_date(string input)
	{
		date = input;
	}
	void set_next(Request_Node* input)
	{
		next = input;
	}

	string get_id()
	{
		return id;
	}
	string get_sender()
	{
		return sender;
	}
	string get_reciever()
	{
		return reciever;
	}
	string get_date()
	{
		return date;
	}
	Request_Node* get_next()
	{
		return next;
	}
};

class Friend_Request_list {
	int size;
	Request_Node* head_Request_Node;
	Request_Node* current_Request_Node;

public:
	Friend_Request_list()
	{
		size = 0;
		head_Request_Node = NULL;
		current_Request_Node = NULL;
	}

	void insert(string id, string sender, string receiver, string date)
	{
		Request_Node* new_Request_Node = new Request_Node();
		new_Request_Node->set_id(id);
		new_Request_Node->set_sender(sender);
		new_Request_Node->set_reciever(receiver);
		new_Request_Node->set_date(date);
		new_Request_Node->set_next(NULL);

		if (head_Request_Node == NULL)
		{
			head_Request_Node = new_Request_Node;
			current_Request_Node = new_Request_Node;
		}
		else
		{
			current_Request_Node->set_next(new_Request_Node);
			current_Request_Node = new_Request_Node;
		}
		size++;
	}

	bool get_values(bool pass)
	{
		ifstream input(organization_files::friend_request);
		string id, sender, receiver, date;

		if (input)
		{
			string line;
			while (getline(input, line))
			{
				istringstream data(line);
				data >> id >> sender >> receiver >> date;

				Components::get_decrypt_text(id);
				Components::get_decrypt_text(sender);
				Components::get_decrypt_text(receiver);
				Components::get_decrypt_text(date);

				if (static_username == sender && pass)
				{
					insert(id, sender, receiver, date);
				}
				else if (static_username == receiver && !pass)
				{
					insert(id, sender, receiver, date);
				}

			}
			input.close();
			return true;
		}
		else
		{

			des.display_no_record_p(10);
			return false;
		}
	}

	int display(bool pass)
	{
		int y = 0;
		if (size > 0)
		{
			Request_Node* temp = head_Request_Node;
			while (temp != NULL)
			{
				if (pass)
				{
					//					cout << "ID: " << temp->get_id() << endl;
					//					cout << "Receiver: " << temp->get_reciever() << endl;
					//					cout << "Date: " << temp->get_date() << endl;
					//					cout << "--------------------------" << endl;
					y = 10;
					des.gotoxy(2, y);
					cout << " ID : " << temp->get_id() << "\t " << "@ " << temp->get_reciever();
					y++;
					des.gotoxy(des.getTerminalWidth() / 3, y);
					cout << " DATE :" << temp->get_date();
					y++;
					des.gotoxy(2, y);
					des.display_line_p();
					y++;
				}
				else if (!pass)
				{
					//					cout << "ID: " << temp->get_id() << endl;
					//					cout << "Sender: " << temp->get_sender() << endl;
					//					cout << "Date: " << temp->get_date() << endl;
					//					cout << "--------------------------" << endl;
					y = 10;
					des.gotoxy(2, y);
					cout << " ID : " << temp->get_id() << "\t " << "@ " << temp->get_sender();
					y++;
					des.gotoxy(des.getTerminalWidth() - 15, y);
					cout << " DATE :" << temp->get_date();
					y++;
					des.gotoxy(2, y);
					des.display_line_p();
					y++;

				}
				temp = temp->get_next();
			}
			return y;
		}
		else
		{
			//			cout << "No records Found" << endl;

			des.display_no_record_p(y + 10);

			return y;
		}
	}

	Request_Node* search(const string& id)
	{
		Request_Node* temp = head_Request_Node;
		while (temp != nullptr)
		{
			if (temp->get_id() == id)
			{
				return temp;
			}
			temp = temp->get_next();
		}
		return NULL;
	}

	int get_size()
	{
		return size;
	}
	~Friend_Request_list()
	{
		Request_Node* temp;
		while (head_Request_Node != NULL)
		{
			temp = head_Request_Node->get_next();
			delete head_Request_Node;
			head_Request_Node = temp;
		}
	}

};

class Friends_Management
{

	vector<string> vector_friends;
	vector<string> vector_unfriends;

	string choice;
	string line;
	string value;

public:
	Friends_Management()
	{
		while (1)
		{
			system("CLS");
			system("CLS");
			vector<string> menuItems = { "Send Request", "Request Approval", "Your Friends", "Back" };
			int position = des.displayMenu(menuItems);
			des.tab_friends_fm_sr();
			des.display_line_slash();
			des.display_enter("Your Choice", "1-4", position);

			choice = Components::input_number_value();

			if (choice == "1")
			{
				send_request();
			}
			else if (choice == "2")
			{
				request_approval();
			}
			else if (choice == "3")
			{
				your_friends();
			}
			else if (choice == "4")
			{
				break;
			}
			else
			{
				cout << "Invalid Choice";
				cin.get();
			}
		}
	}

	void send_request()
	{
		while (1)
		{
			system("CLS");
			des.tab_friends_fm_sr();
			des.display_line_slash();

			vector_friends.clear();
			vector_unfriends.clear();
			get_friends(true);
			get_unfriends();

			int position = display_unfriends();
			if (position > 0)
			{
				des.tab_friends_fm_sr();
				des.display_line_slash();
				position++;
				des.display_enter("Choose", "using name", position);
				value = Components::input_text_value();

				if (check_unfriend(value))
				{
					string id = to_string(Components::generate_id(organization_files::friend_request));
					string sender = static_username;
					string date = Components::get_current_date();

					Components::get_encrypt_text(id);
					Components::get_encrypt_text(sender);
					Components::get_encrypt_text(value);
					Components::get_encrypt_text(date);

					ofstream output(organization_files::friend_request, ios::app);
					output << id << " " << sender << " " << value << " " << date << endl;
					output.close();

					position = position + 2;
					des.display_sucessfully_p("Request Sent", position);
					cin.get();

				}
				else if (value == "Back")
				{
					break;
				}
				else
				{
					position++;
					des.display_invalid_p("Choice", position);
				}

			}
			else
			{
				break;
			}
		}
	}

	void get_friends(bool check)
	{
		ifstream output(organization_files::friends);
		if (output)
		{
			while (getline(output, line))
			{

				string id, user1, user2;
				istringstream data(line);
				data >> id >> user1 >> user2;

				Components::get_decrypt_text(user1);
				Components::get_decrypt_text(user2);

				if (user1 == static_username)
				{
					vector_friends.push_back(user2);
				}
				else if (user2 == static_username)
				{
					vector_friends.push_back(user1);
				}
			}
			output.close();
		}

		if (check)
		{
			ifstream output1(organization_files::friend_request);
			if (output1)
			{
				while (getline(output1, line))
				{

					string id, user1, user2;
					istringstream data(line);
					data >> id >> user1 >> user2;

					Components::get_decrypt_text(user1);
					Components::get_decrypt_text(user2);

					if (user1 == static_username)
					{
						vector_friends.push_back(user2);
					}
					else if (user2 == static_username)
					{
						vector_friends.push_back(user1);
					}
				}
				output1.close();
			}

		}


	}

	void get_unfriends()
	{
		ifstream file(organization_files::user_credentials);
		if (file)
		{
			while (getline(file, line))
			{
				string name;
				istringstream data(line);
				data >> name;

				Components::get_decrypt_text(name);

				if (!check_friend(name) && name != static_username)
				{
					vector_unfriends.push_back(name);
				}

			}

			file.close();
		}

	}

	int display_friends()
	{
		if (vector_friends.empty())
		{
			int p = 10;
			des.display_side("You have no Friends yet", p);
			return false;
		}

		int i = 1;
		return des.displayList(vector_friends);
	}

	int display_unfriends()
	{
		if (vector_unfriends.empty())
		{
			int p = 10;
			des.display_side("You have no people to add Friends", p);
			cin.get();
			return false;
		}
		return des.displayList(vector_unfriends);
	}

	bool check_friend(string name)
	{
		if (vector_friends.empty())
		{
			return false;
		}
		for (const auto friends : vector_friends)
		{
			if (friends == name)
			{
				return true;
			}
		}
		return false;
	}

	bool check_unfriend(string name)
	{
		if (vector_unfriends.empty())
		{
			return false;
		}
		for (const auto value : vector_unfriends)
		{
			if (value == name)
			{
				return true;
			}
		}
		return false;
	}

	void your_friends()
	{
		while (true)
		{
			system("CLS");
			des.border();
			des.tab_friends_fm_yf();
			des.display_line_slash();

			vector_friends.clear();
			get_friends(false);

			int position = display_friends();
			if (position > 0)
			{
				des.tab_friends_fm_yf();
				des.display_line_slash();
				des.display_enter("Choose", "using name", position);
				value = Components::input_text_value();

				if (value == "Back")
				{
					break;
				}
				else if (check_friend(value))
				{
					position += 1;
					des.display_do_you_p("want to delete this friend", "Yes/No", position);
					choice = Components::input_string_choice();

					if (choice == "Yes")
					{
						ifstream output(organization_files::friends);
						if (output)
						{
							bool check = false;
							ofstream temp(organization_files::temp);
							while (getline(output, line))
							{
								string id, u1, u2;
								istringstream data(line);
								data >> id >> u1 >> u2;

								Components::get_decrypt_text(u1);
								Components::get_decrypt_text(u2);

								if ((u1 == static_username && u2 == value) || (u1 == value && u2 == static_username))
								{
									string temp_file = (u1 + u2 + ".txt");
									const char* filename = temp_file.c_str();
									remove(filename);
									check = true;
								}
								else
								{
									temp << line << endl;
								}
							}
							output.close();
							temp.close();
							remove(organization_files::friends);
							rename(organization_files::temp, organization_files::friends);
							if (check)
							{
								des.display_sucessfully_p("Friend Deleted", position++);
							}
							else
							{
								des.display_not_found_p("Friend", position++);
							}
							cin.get();
						}
						else
						{
							des.display_file_p(position++);
							cin.get();
						}

					}
					else
					{
						break;
					}

				}
				else
				{
					position++;
					des.display_invalid_p("Choice", position);

				}


			}
			else
			{
				break;
			}
		}

	}

	void request_approval()
	{
		while (true)
		{
			system("CLS");
			des.border();
			vector<string> menuItems = { "OutReach Requests", "Incoming Requests", "Back" };
			int position = des.displayMenu(menuItems);
			des.tab_friends_fm_ra();
			des.display_line_slash();
			des.display_enter("Select", "1-3", position);

			choice = Components::input_number_value();

			if (choice == "1")
			{
				while (true)
				{
					system("CLS");
					des.border();
					des.tab_friends_fm_ra_o();
					des.display_line_slash();

					Friend_Request_list list;


					if (list.get_values(true))
					{
						int p = list.display(true);
						if (p > 0)
						{
							p++;
							des.display_do_you_p("want to delete any request", "Yes/No", p);
							choice = Components::input_string_choice();

							if (choice == "Yes")
							{

								p = p + 2;
								des.display_enter("Enter Request ID", p);
								value = Components::input_number_value();

								Request_Node* found = list.search(value);
								if (found != NULL)
								{
									ifstream output(organization_files::friend_request);
									if (output)
									{
										bool check = false;
										ofstream temp(organization_files::temp);
										while (getline(output, line))
										{
											string id;
											istringstream data(line);
											data >> id;

											Components::get_decrypt_text(id);

											if (value != id)
											{
												temp << line << endl;
											}
											else
											{
												check = true;
											}
										}
										temp.close();
										output.close();
										remove(organization_files::friend_request);
										rename(organization_files::temp, organization_files::friend_request);
										if (check)
										{
											p = p + 2;
											des.display_sucessfully_p("Request deleted", p);
											//											cout << "Request Deleted Successfully";

										}
										else
										{
											//											cout << "No Record Found";
											p = 10;
											des.display_no_record_p(p);
											break;

										}
									}
									else
									{
										//										cout << "File Doesn't Found";
										p++;
										des.display_file_p(p);
									}
								}
								else
								{
									p++;
									des.display_invalid_p("ID", p);
									//									cout << "Invalid ID";

								}


							}
							else
							{
								break;
							}
						}
						else
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
			}
			else if (choice == "2")
			{
				while (true)
				{
					system("CLS");
					des.border();
					des.tab_friends_fm_ra_i();
					des.display_line_slash();

					Friend_Request_list list;
					if (list.get_values(false))
					{
						int p = list.display(false);
						if (p > 0)
						{
							p++;
							des.display_do_you_p("want to approve any request", "Yes/No", p);
							//						
							//							cout << "Do you want to approve any request [Yes/No] : ";
							choice = Components::input_string_choice();

							if (choice == "Yes")
							{
								//								cout << "Enter Request ID : ";
								p = p + 2;
								des.display_enter("Enter Request ID", p);
								value = Components::input_number_value();

								Request_Node* found = list.search(value);
								if (found != NULL)
								{
									string approval;
									p = p + 2;
									//									cout << "Select [Accept/Reject] : ";
									p = p + 2;
									des.display_enter("Select", "Accept/Reject", p);
									approval = Components::input_approval();

									ifstream output(organization_files::friend_request);
									if (output)
									{
										bool check = false;
										ofstream temp(organization_files::temp);
										while (getline(output, line))
										{
											string id;
											istringstream data(line);
											data >> id;

											Components::get_decrypt_text(id);

											if (value != id)
											{
												temp << line << endl;
											}
											else
											{
												check = true;
												if (approval == "Accept")
												{
													string sender, receiver;
													sender = found->get_sender();
													receiver = found->get_reciever();
													Components::get_encrypt_text(id);
													Components::get_encrypt_text(sender);
													Components::get_encrypt_text(receiver);
													ofstream file(organization_files::friends, ios::app);
													file << id << " " << sender << " " << receiver << endl;
													file.close();
												}
											}
										}
										temp.close();
										output.close();
										remove(organization_files::friend_request);
										rename(organization_files::temp, organization_files::friend_request);
										if (check)
										{
											if (approval == "Accept")
											{
												p = p + 2;
												des.display_sucessfully_p("Request Accepted", p);
												//												cout << "Request Accepted Successfully";
											}
											else
											{
												p = p + 2;
												des.display_sucessfully_p("Request Rejected", p);
												//												cout << "Request Rejected Successfully";
											}

											cin.get();
										}
										else
										{
											//											cout << "No Record Found";
											p = 10;
											des.display_no_record_p(p);
											break;
										}
									}
									else
									{
										//										cout << "File Doesn't Found";
										p++;
										des.display_file_p(p);
									}
								}
								else
								{
									//									cout << "Invalid ID";
									p++;
									des.display_invalid_p("ID", p);

								}


							}
							else
							{
								break;
							}
						}
						else
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
			}
			else if (choice == "3")
			{
				break;
			}
			else
			{
				position++;
				des.display_invalid_p("Choice", position);
			}
		}
	}


};


// End Previous Here


class Group
{
private:
	string group_id;
	string group_name;
	string group_admin;
	string description;
	string created_date;
	Group* nextNode;

public:
	// Setter and Getter for nextNode
	void set_nextNode(Group* nextNode)
	{
		this->nextNode = nextNode;
	}
	Group* get_nextNode()
	{
		return nextNode;
	}

	// Setter and Getter for group_id
	void set_group_id(string group_id)
	{
		this->group_id = group_id;
	}
	string get_group_id()
	{
		return group_id;
	}

	// Setter and Getter for group_name
	void set_group_name(string group_name)
	{
		this->group_name = group_name;
	}
	string get_group_name()
	{
		return group_name;
	}

	// Setter and Getter for group_admin
	void set_group_admin(string group_admin)
	{
		this->group_admin = group_admin;
	}
	string get_group_admin()
	{
		return group_admin;
	}

	// Setter and Getter for description
	void set_description(string description)
	{
		this->description = description;
	}
	string get_description()
	{
		return description;
	}

	// Setter and Getter for created_date
	void set_created_date(string created_date)
	{
		this->created_date = created_date;
	}
	string get_created_date()
	{
		return created_date;
	}
};

class Group_List
{
private:
	int size;
	Group* headNode;
	Group* currentNode;
	Group* lastCurrentNode;

public:
	// Default Constructor
	Group_List()
	{
		size = 0;
		headNode = NULL;
		currentNode = NULL;
		lastCurrentNode = NULL;
	}

	// Function for insertion
	void insert(string group_id, string group_name, string group_admin, string description, string created_date)
	{
		if (currentNode != NULL)
		{
			Group* newNode = new Group;
			newNode->set_group_id(group_id);
			newNode->set_group_name(group_name);
			newNode->set_group_admin(group_admin);
			newNode->set_description(description);
			newNode->set_created_date(created_date);
			newNode->set_nextNode(NULL);
			currentNode->set_nextNode(newNode);
			lastCurrentNode = currentNode;
			currentNode = newNode;
		}
		else
		{
			headNode = new Group;
			headNode->set_group_id(group_id);
			headNode->set_group_name(group_name);
			headNode->set_group_admin(group_admin);
			headNode->set_description(description);
			headNode->set_created_date(created_date);
			headNode->set_nextNode(NULL);
			lastCurrentNode = currentNode;
			currentNode = headNode;
		}
		size++;
	}

	// Function for displaying group_list
	int display()
	{
		int y = 10;
		lastCurrentNode = headNode;
		currentNode = headNode;
		if (currentNode != NULL)
		{
			do
			{
				//				cout << "-----------------------------------" << endl;
				//				cout << " Group Id    : " << currentNode->get_group_id() << endl;
				//				cout << " Group Name  : " << currentNode->get_group_name() << endl;
				//				cout << " Group Admin : " << currentNode->get_group_admin() << endl;
				//				cout << " Description : " << currentNode->get_description() << endl;
				//				cout << " CreatedDate : " << currentNode->get_created_date() << endl;


				des.gotoxy(2, y);
				cout << " GROUP  ID   : " << currentNode->get_group_id() << "    @ " << currentNode->get_group_name();
				y++;

				des.gotoxy(2, y);
				cout << " DESCRIPTION : " << currentNode->get_description();
				y++;

				des.gotoxy(2, y);
				cout << " CREATED BY  : @ " << currentNode->get_group_admin() << "\t   ON: " << currentNode->get_created_date();

				y++;
				des.gotoxy(2, y);
				des.display_line_p();
				y += 2;

				lastCurrentNode = currentNode;
				currentNode = currentNode->get_nextNode();
			} while (currentNode != NULL);
		}
		else
		{
			des.display_no_record_p(10);
			return 0;
		}
		return y;
	}

	string find(string id)
	{
		bool found = false;
		lastCurrentNode = headNode;
		currentNode = headNode;
		if (currentNode != NULL)
		{
			do
			{
				if (currentNode->get_group_id() == id)
				{
					found = true;
				}

				lastCurrentNode = currentNode;
				currentNode = currentNode->get_nextNode();
			} while (currentNode != NULL);
		}
		else
		{
			des.display_no_record();
		}
		if (found)
		{
			return id;
		}
		else
		{
			return "NULL";
		}
	}

	string find_group_name(string name)
	{
		bool found = false;
		lastCurrentNode = headNode;
		currentNode = headNode;
		if (currentNode != NULL)
		{
			do
			{
				if (currentNode->get_group_name() == name)
				{
					found = true;
				}

				lastCurrentNode = currentNode;
				currentNode = currentNode->get_nextNode();
			} while (currentNode != NULL);
			currentNode = lastCurrentNode;
		}

		if (!found)
		{
			return name;
		}
		else
		{
			return "NULL";
		}
	}

	void start()
	{
		currentNode = headNode;
		lastCurrentNode = headNode;
	}

	bool isEmpty()
	{
		return size == 0;
	}

	void get_data(string value)
	{
		vector<string> vec_groups_id;
		if (value == "leave")
		{
			get_group_ids(vec_groups_id);
		}

		ifstream outputfile(organization_files::group);
		if (outputfile)
		{
			string data;
			while (getline(outputfile, data))
			{
				string group_id;
				string group_name;
				string group_admin;
				string description;
				string created_date;
				istringstream line(data);
				line >> group_id >> group_name >> group_admin >> description >> created_date;
				Components::get_decrypt_text(group_id);
				Components::get_decrypt_text(group_name);
				Components::get_decrypt_text(group_admin);
				Components::get_decrypt_text(description);
				Components::get_decrypt_text(created_date);

				if (value == "add")
				{
					insert(group_id, group_name, group_admin, description, created_date);
				}
				else if (value == "update" && group_admin == static_username)
				{
					insert(group_id, group_name, group_admin, description, created_date);
				}
				else if (value == "leave")
				{
					if (check_group_id(group_id, vec_groups_id))
					{
						insert(group_id, group_name, group_admin, description, created_date);
					}
				}

			}
			outputfile.close();
		}
	}

	void get_group_ids(vector<string>& groups_id)
	{
		ifstream outputfile(organization_files::group_members);
		if (outputfile)
		{
			string data, g_id, f_u;
			while (getline(outputfile, data))
			{
				istringstream line(data);
				line >> g_id >> f_u;

				Components::get_decrypt_text(g_id);
				Components::get_decrypt_text(f_u);

				if (f_u == static_username)
				{
					groups_id.push_back(g_id);
				}
			}
			outputfile.close();
		}
	}

	bool check_group_id(string id, vector<string>& groups_id)
	{
		for (const auto& value : groups_id)
		{
			if (value == id)
			{
				return true;
			}
		}
		return false;
	}

	~Group_List()
	{
		Group* temp;
		while (headNode != NULL)
		{
			temp = headNode->get_nextNode();
			delete headNode;
			headNode = temp;
		}
	}
};

class Group_Management
{

private:
	// For Groups file
	string group_id;
	string group_name;
	string group_admin;
	string description;
	string created_date;
	// For Friends file
	string friend_id;
	string user1;
	string user2;
	string filename;

	// For Group_Members file
	string fusername;

public:
	// Default Constructor
	Group_Management()
	{
		while (true)
		{
			system("CLS");
			vector<string> menuItems = { "Add Group", "Update Group", "Delete Group","Group Members","Back" };
			int position = des.displayMenu(menuItems);
			des.tab_groups_gm();
			des.display_line_slash();
			des.display_enter("Select", "1-5", position);


			string choice;

			//			cout << " 1. Add_Group " << endl;
			//			cout << " 2. Update_Group " << endl;
			//			cout << " 3. Delete_Group " << endl;
			//			cout << " 4. Group_Members " << endl;
			//			cout << " 5. Return " << endl;
			//			cout << "    Enter Your Choice:: [1-5] ";
			choice = Components::input_number_value();
			if (choice == "1")
			{
				Add_Group();
			}
			else if (choice == "2")
			{
				Update_Group();
			}
			else if (choice == "3")
			{
				Delete_Group();
			}
			else if (choice == "4")
			{
				while (true)
				{
					system("CLS");
					vector<string> menuItems = { "Add Member", "Remove Member", "Leave Group","Back" };
					int position = des.displayMenu(menuItems);
					des.tab_groups_gm_gm();
					des.display_line_slash();
					des.display_enter("Select", "1-4", position);

					//					cout << " 1. Add_Member " << endl;
					//					cout << " 2. Remove_Member " << endl;
					//					cout << " 3. Leave_Group " << endl;
					//					cout << " 4. Return " << endl;
					//					cout << "    Enter Your Choice:: ";
					choice = Components::input_number_value();
					if (choice == "1")
					{
						Add_Member();
					}
					else if (choice == "2")
					{
						Remove_Member();
					}
					else if (choice == "3")
					{
						Leave_Group();
					}
					else if (choice == "4")
					{
						break;
					}
					else
					{
						des.display_invalid("Choice");
					}
				}
			}
			else if (choice == "5")
			{
				break;
			}
			else
			{
				des.display_invalid("Choice");
			}
		}
	}

	// Function to add new groups
	void Add_Group()
	{
		system("CLS");
		des.border();
		des.tab_groups_gm_ag();
		des.display_line_slash();

		int p = 10;
		Group_List group_list;
		group_list.get_data("add");

		string update_group_name;
		//		cout << "    Enter Group name: ";
		des.display_enter("Enter Group Name", p);
		group_name = Components::input_text_value();
		update_group_name = group_name;

		check_group_name(group_list, group_name);
		if (update_group_name != group_name)
		{
			p = p + 8;
		}
		p += 2;
		//		cout << "    Enter Group Description: ";
		des.display_enter("Enter Group Description", "limit < 20", p);
		description = Components::input_text_value();

		p += 2;
		des.display_do_you_p("want to add group", "Yes/No", p);
		//		cout << "Do you want to add group [Yes/No] : ";
		string choice = Components::input_string_choice();

		if (choice == "Yes")
		{
			group_id = (to_string(Components::generate_id(organization_files::group)));
			group_admin = static_username;
			created_date = Components::get_current_date();

			ofstream inputfile0(group_name + ".txt");
			inputfile0.close();

			ofstream inputfile(organization_files::group, ios::app);
			Components::get_encrypt_text(group_id);

			Components::get_encrypt_text(group_name);

			Components::get_encrypt_text(group_admin);

			Components::get_encrypt_text(description);

			Components::get_encrypt_text(created_date);

			inputfile << group_id << " " << group_name << " " << group_admin << " " << description << " " << created_date << endl;
			inputfile.close();

			p += 2;
			des.display_sucessfully_p("Group Added Successfully", p);
			inputfile.close();

		}
	}

	// Function to update existing groups
	void Update_Group()
	{
		system("CLS");
		des.border();
		des.tab_groups_gm_ug();
		des.display_line_slash();


		Group_List group_list;
		group_list.get_data("update");

		//		cout << "Yes" << endl;

		if (!(group_list.isEmpty()))
		{
			int p = group_list.display();
			p++;

			string id;
			string n_description;
			//			cout << "\n\n    Enter Group ID from above to update :";
			des.display_enter("Enter Group ID from above to update", p);
			id = Components::input_number_value();
			if (!(group_list.find(id) == "NULL"))
			{
				//				cout << " Enter new Description: ";
				p += 2;
				des.display_enter("Enter new Description", p);
				n_description = Components::input_text_value();

				//				cout << "Do you want to update description [Yes/No] : ";
				p += 2;
				des.display_do_you_p("want to update description", "Yes/No", p);
				string choice = Components::input_string_choice();

				if (choice == "Yes")
				{
					Components::get_encrypt_text(id);
					Components::get_encrypt_text(n_description);

					ifstream outputfile(organization_files::group);
					if (outputfile)
					{
						bool check = false;
						ofstream inputfile(organization_files::temp);
						string data;
						while (getline(outputfile, data))
						{
							istringstream line(data);
							line >> group_id >> group_name >> group_admin >> description >> created_date;

							if (group_id == id)
							{
								check = true;
								inputfile << group_id << " " << group_name << " " << group_admin << " " << n_description << " " << created_date << endl;
							}
							else
							{
								inputfile << data << endl;
							}
						}
						outputfile.close();
						inputfile.close();
						remove(organization_files::group);
						rename(organization_files::temp, organization_files::group);

						if (check)
						{
							p += 2;
							des.display_sucessfully_p("Group Updated", p);
						}
						else
						{
							p += 2;
							//							cout << "Record Not Found";
							des.display_no_record_p(p);
						}
					}
					else
					{
						//						cout << "File Doesn't Found";
						p += 2;
						des.display_file_p(p);
					}
				}
			}
			else
			{
				p += 2;
				des.display_invalid_p("ID", p);
				//				cout << "Invalid ID";

			}
		}
		else
		{

			des.display_no_record_p(10);
		}

	}

	// Function to update existing groups
	void Delete_Group()
	{
		while (1)
		{
			system("CLS");
			des.border();
			des.tab_groups_gm_dg();
			des.display_line_slash();

			Group_List group_list;
			group_list.get_data("update");

			if (!group_list.isEmpty())
			{

				int p = group_list.display();
				p++;
				string id;
				//				cout << "\n\n    Enter Group ID from above to delete :";
				des.display_enter("Enter Group ID from above to delete", p);
				id = Components::input_number_value();
				if (!(group_list.find(id) == "NULL"))
				{
					//					cout << "Do you want to delete group [Yes/No] : ";
					p += 2;
					des.display_do_you_p("want to delete group", "Yes/No", p);
					string choice = Components::input_string_choice();

					if (choice == "Yes")
					{
						ifstream outputfile(organization_files::group);
						if (outputfile)
						{
							bool check = false;
							ofstream inputfile(organization_files::temp);
							string temp_group_name = "_NULL";
							string data;
							while (getline(outputfile, data))
							{
								istringstream line(data);
								line >> group_id >> group_name >> group_admin >> description >> created_date;
								Components::get_decrypt_text(group_id);
								Components::get_decrypt_text(group_name);
								if (group_id != id)
								{
									Components::get_encrypt_text(group_id);
									Components::get_encrypt_text(group_name);
									inputfile << data << endl;
								}
								else if (group_id == id)
								{
									temp_group_name = group_name;
									temp_group_name += ".txt";
									check = true;
								}
							}
							outputfile.close();
							inputfile.close();
							remove(organization_files::group);
							rename(organization_files::temp, organization_files::group);

							if (check)
							{
								remove(temp_group_name.c_str());
								ifstream outputfile1(organization_files::group_members);
								if (outputfile1)
								{
									ofstream inputfile1(organization_files::temp);
									string data;
									while (getline(outputfile1, data))
									{
										istringstream line(data);
										line >> group_id >> fusername;
										Components::get_decrypt_text(group_id);
										if (group_id != id)
										{
											inputfile1 << data << endl;
										}
									}
									outputfile1.close();
									inputfile1.close();
									remove(organization_files::group_members);
									rename(organization_files::temp, organization_files::group_members);
								}
								p += 2;
								des.display_sucessfully_p("Group Deleted", p);
							}
							else
							{
								cout << "Record Not Found in File";
								cin.get();
							}

						}
						else
						{
							p += 2;
							//							cout << "File doesn't Found";
							des.display_file_p(p);
						}
					}
					else
					{
						break;
					}
				}
				else
				{

					p += 2;
					//					cout << "Invalid ID";
					des.display_invalid_p("ID", p);
					break;
				}
			}
			else
			{
				des.display_side("You have no groups yet", 10);
				//				cout << "You have no group yet";
				break;
			}

		}

	}

	// Function to add members
	void Add_Member()
	{
		system("CLS");
		des.border();
		des.tab_groups_gm_gm_am();
		des.display_line_slash();
		//		cout << " Add_Member() Function: - \n\n";
		Group_List group_list;
		group_list.get_data("update");

		if (!(group_list.isEmpty()))
		{
			int p = group_list.display();
			p++;

			string id;
			//			cout << "\n\n    Enter Group ID from above to add Members :";

			des.display_enter("Enter Group ID from above to add Members", p);
			id = Components::input_number_value();
			if (group_list.find(id) != "NULL")
			{
				while (true)
				{
					system("CLS");
					vector<string> already;
					vector<string> reLogin_variabliesing;

					get_members(id, already);
					get_friends(already, reLogin_variabliesing);

					int y = display_friends(reLogin_variabliesing);
					des.tab_groups_gm_gm_am();
					des.display_line_slash();

					if (y > 0)
					{
						string fname;
						y++;
						des.display_enter("Enter Name", "Text Only", y);

						//						cout << " Enter Name :";
						fname = Components::input_text_value();

						if (fname == "Back")
						{
							break;
						}
						else if (check_friend(fname, reLogin_variabliesing))
						{
							y += 2;
							des.display_do_you_p("want to add " + fname, "Yes/No", y);
							//							cout << "Do you want to add " << fname << " [Yes/No] : ";
							string choice = Components::input_string_choice();

							if (choice == "Yes")
							{
								string f_id = id, f_n = fname;
								ofstream inputfile(organization_files::group_members, ios::app);
								Components::get_encrypt_text(f_id);
								Components::get_encrypt_text(f_n);
								inputfile << f_id << " " << f_n << endl;
								inputfile.close();

								y += 2;
								des.display_sucessfully_p(fname + " added to Group", y);

							}

						}
						else
						{
							//							cout << "Invalid Name";
							y += 2;
							des.display_invalid_p("Name", y);
						}
					}
					else
					{
						p += 2;
						//						cout << "You have no friends to add in group";
						des.display_side("You have no friends to add in group", p);

						break;
					}

				}
			}
			else
			{
				p += 2;
				//				cout << "Invalid ID";
				des.display_invalid_p("ID", p);
			}
		}
		else
		{
			//			cout << "You have no group yet";
			//			des.display_side("You have no groups yet",10);
			des.display_center("You have no groups yet");
			cin.get();
		}

	}
	// Function to remove members
	void Remove_Member()
	{
		system("CLS");
		des.border();
		des.tab_groups_gm_gm_rm();
		des.display_line_slash();
		Group_List group_list;
		group_list.get_data("update");

		if (!(group_list.isEmpty()))
		{
			int p = group_list.display();
			p++;

			string id;
			des.display_enter("Enter Group ID from above to Remove Members", p);id = Components::input_number_value();
			if (group_list.find(id) != "NULL")
			{
				while (true)
				{
					system("CLS");
					vector<string> already;

					get_members(id, already);
					int y = display_members(already);
					des.tab_groups_gm_gm_rm();
					des.display_line_slash();

					if (y > 0)
					{
						string fname;
						y++;
						des.display_enter("Enter Name", "Text Only", y);

						fname = Components::input_text_value();

						if (fname == "Back")
						{
							break;
						}
						else if (check_member(fname, already))
						{
							//							cout << "Do you want to remove " << fname << " [Yes/No] : ";
							y += 2;
							des.display_do_you_p("want to remove " + fname, "Yes/No", y);
							string choice = Components::input_string_choice();

							if (choice == "Yes")
							{

								string f_id = id, f_n = fname;
								Components::get_encrypt_text(f_id);
								Components::get_encrypt_text(f_n);

								ifstream outputfile(organization_files::group_members);
								if (outputfile)
								{
									string line, t_id, t_n;
									bool found = false;
									ofstream temp(organization_files::temp);
									while (getline(outputfile, line))
									{
										istringstream data(line);
										data >> t_id >> t_n;
										if (t_id == f_id && t_n == f_n)
										{
											found = true;
										}
										else
										{
											temp << line << endl;
										}
									}
									outputfile.close();
									temp.close();
									remove(organization_files::group_members);
									rename(organization_files::temp, organization_files::group_members);

									if (found)
									{
										//										cout << fname << " Deleted From this Group";
										y += 2;
										des.display_sucessfully_p(fname + " removed from Group", y);

									}
									else
									{
										p += 2;
										des.display_no_record_p(p);
									}
									cin.get();
								}
								else
								{
									//									cout << "File Doesn't Found";
									p += 2;
									des.display_file_p(p);
									break;
								}
							}
						}
						else
						{
							//							cout << "Invalid Name";
							y += 2;
							des.display_invalid_p("Name", y);
						}
					}
					else
					{
						//						cout << "You have no friends to remove from this group";

						des.display_center("You have no members to remove in this group");
						cin.get();
						break;
					}

				}
			}
			else
			{
				//				cout << "Invalid ID";
				p += 2;
				des.display_invalid_p("ID", p);
			}
		}
		else
		{
			//			cout << "You have no group yet";
			des.display_center("You have no groups yet");
			cin.get();
		}

	}
	// Function to add members
	void Leave_Group()
	{
		system("CLS");
		des.border();
		des.tab_groups_gm_gm_lg();
		des.display_line_slash();

		Group_List group_list;
		group_list.get_data("leave");

		if (!(group_list.isEmpty()))
		{
			int p = group_list.display();
			p++;
			string id;
			//			cout << "\n\n    Enter Group ID To Leave :";
			des.display_enter("Enter Group ID from above to leave", p);
			id = Components::input_number_value();
			if (group_list.find(id) != "NULL")
			{
				p += 2;
				des.display_do_you_p("want to leave this group", "Yes/No", p);
				string choice = Components::input_string_choice();

				if (choice == "Yes")
				{
					ifstream outputfile1(organization_files::group_members);
					if (outputfile1)
					{
						ofstream inputfile1(organization_files::temp);
						if (inputfile1)
						{
							string data;
							while (getline(outputfile1, data))
							{
								istringstream line(data);
								line >> group_id >> fusername;

								Components::get_decrypt_text(group_id);
								Components::get_decrypt_text(fusername);

								if (fusername != static_username && group_id != id)
								{
									inputfile1 << data << endl;
								}

							}
							outputfile1.close();
							inputfile1.close();
							remove(organization_files::group_members);
							rename(organization_files::temp, organization_files::group_members);
							//							des.display_sucessfully("You left group Successfully");
							p += 2;
							des.display_sucessfully_p("You left this group", p);
						}
					}
					else
					{
						p += 2;
						//						cout << "File doesn't Found";
						des.display_file_p(p);
					}
				}
			}
			else
			{
				p += 2;
				//					cout << "Invalid ID";
				des.display_invalid_p("ID", p);
			}
		}
		else
		{
			des.display_center("You have no groups to leave");
			cin.get();
		}
	}

	void get_members(const string pass_id, vector<string>& already)
	{
		ifstream outputfile(organization_files::group_members);
		if (outputfile)
		{
			string data;
			while (getline(outputfile, data))
			{
				istringstream line(data);
				line >> group_id >> fusername;

				Components::get_decrypt_text(group_id);
				if (group_id == pass_id)
				{
					Components::get_decrypt_text(fusername);
					already.push_back(fusername);
				}
			}
			outputfile.close();
		}
	}

	void get_friends(vector<string>& already, vector<string>& reLogin_variabliesing)
	{
		// Checking filtred out friends
		ifstream outputfile1(organization_files::friends);
		if (outputfile1)
		{
			string data;
			while (getline(outputfile1, data))
			{
				istringstream line(data);
				line >> friend_id >> user1 >> user2;

				Components::get_decrypt_text(friend_id);
				Components::get_decrypt_text(user1);
				Components::get_decrypt_text(user2);

				if (user1 == static_username)
				{
					if (!(check_member(user2, already)))
					{
						reLogin_variabliesing.push_back(user2);
					}
				}
				else if (user2 == static_username)
				{
					if (!(check_member(user1, already)))
					{
						reLogin_variabliesing.push_back(user1);
					}
				}
			}
			outputfile1.close();
		}

	}

	bool check_member(const string& name, const vector<string>& already)
	{
		for (const auto& member : already)
		{
			if (name == member)
			{
				return true;
			}
		}
		return false;
	}

	bool check_friend(const string& name, const vector<string>& reLogin_variabliesing)
	{
		for (const auto& value : reLogin_variabliesing)
		{
			if (name == value)
			{
				return true;
			}
		}
		return false;
	}

	int display_friends(const vector<string>& reLogin_variabliesing)
	{
		//		bool check = false;
		//		int i = 1;
		//		for (const auto& value : reLogin_variabliesing)
		//		{
		//			cout << i++ << ". " << value << endl;
		//			check = true;
		//		}
		//
		//		if (check)
		//		{
		//			cout << i << ". Back" << endl;
		//		}
		if (reLogin_variabliesing.empty())
		{
			return false;
		}
		return des.displayList(reLogin_variabliesing);
		//		return check;
	}

	int display_members(const vector<string>& already)
	{
		//		bool check = false;
		//		int i = 1;
		//		for (const auto& value : already)
		//		{
		//			cout << i++ << ". " << value << endl;
		//			check = true;
		//		}
		//
		//		if (check)
		//		{
		//			cout << i << ". Back" << endl;
		//		}
		//
		//		return check;
		if (already.empty())
		{
			return false;
		}
		return des.displayList(already);
	}

	void check_group_name(Group_List& list, string& pass_name)
	{
		bool check = true;
		while (1)
		{
			if (list.find_group_name(pass_name) != "NULL")
			{
				break;
			}

			if (check)
			{
				check = false;
				//				cout << "\nThis username already contained" << endl;
				//				cout << "Suggested Username : { ";
				//				generate_group_name(list, pass_name);
				//				cout << " }" << endl;
				//				cout << "\nTry Different Username : ";

				des.display_already_contained_p("This Group Name", 12);
				des.display("Suggested Group Name", 14);
				generate_group_name(list, pass_name);
				des.display_side("Try Different Group Name", 15);
				des.display_enter("Enter Group Name", 16);
			}
			else
			{
				for (int i = 0;i < pass_name.length();i++)
				{
					cout << "\b \b";
				}
			}
			pass_name = Components::input_text_value();
		}
	}

	void generate_group_name(Group_List& list, string name)
	{
		string values = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
		string next_name[3];
		srand(static_cast<unsigned int>(time(0)));
		for (int i = 0;i < 3;)
		{
			next_name[i] = name;

			for (int j = 0;j < 3;j++)
			{
				int n = rand() % values.length();
				next_name[i] += values[n];
			}

			if (list.find_group_name(next_name[i]) != "NULL")
			{
				cout << next_name[i];

				if (i != 2)
				{
					cout << ", ";
				}
				i++;
			}
		}
	}


};

// End Previous Here


class Status_Node
{
	string status_id;
	string name;
	string status_message;
	string date;
	string time;
	Status_Node* next;

public:
	void set_status_id(string input)
	{
		status_id = input;
	}

	void set_name(string input)
	{
		name = input;
	}

	void set_status_message(string input)
	{
		status_message = input;
	}

	void set_date(string input)
	{
		date = input;
	}

	void set_time(string input)
	{
		time = input;
	}

	void set_next(Status_Node* input)
	{
		next = input;
	}

	string get_status_id()
	{
		return status_id;
	}

	string get_name() {
		return name;
	}

	string get_status_message()
	{
		return status_message;
	}

	string get_date()
	{
		return date;
	}

	string get_time()
	{
		return time;
	}

	Status_Node* get_next()
	{
		return next;
	}
};

class Status_list
{
	int size;
	Status_Node* head_Status_Node;
	Status_Node* current_Status_Node;
	vector<string> vector_names;

public:
	Status_list()
	{
		size = 0;
		head_Status_Node = NULL;
		current_Status_Node = NULL;
		vector_names.clear();
	}

	void insert(string status_id, string name, string status_message, string date, string time)
	{
		Status_Node* new_Status_Node = new Status_Node();
		new_Status_Node->set_status_id(status_id);
		new_Status_Node->set_name(name);
		new_Status_Node->set_status_message(status_message);
		new_Status_Node->set_date(date);
		new_Status_Node->set_time(time);
		new_Status_Node->set_next(NULL);

		if (head_Status_Node == NULL)
		{
			head_Status_Node = new_Status_Node;
			current_Status_Node = new_Status_Node;
		}
		else
		{
			current_Status_Node->set_next(new_Status_Node);
			current_Status_Node = new_Status_Node;
		}
		size++;
	}

	bool get_values(bool pass)
	{
		ifstream input(organization_files::status);
		string status_id, name, status_message, date, time;

		if (input)
		{
			string line;
			while (getline(input, line))
			{
				istringstream data(line);
				data >> status_id >> name >> status_message >> date >> time;

				Components::get_decrypt_text(status_id);
				Components::get_decrypt_text(name);
				Components::get_decrypt_text(status_message);
				Components::get_decrypt_text(date);
				Components::get_decrypt_text(time);

				if (pass && name == static_username)
				{
					insert(status_id, name, status_message, date, time);
				}
				else if (!pass)
				{
					if (static_username == name || check_friend(name))
					{
						insert(status_id, name, status_message, date, time);
					}
				}
			}
			input.close();
			return true;
		}
		else
		{
			//			cout << "You Have no Status yet";
			des.display_center("You Have no Status yet");
			cin.get();
			return false;
		}
	}

	bool display()
	{
		if (size > 0)
		{
			Status_Node* temp = head_Status_Node;
			int y = 8;
			while (temp != NULL)
			{

				//				cout << "Status ID: " << temp->get_status_id() << endl;
				//				cout << "Name: " << temp->get_name() << endl;
				//				cout << "Status Message: " << temp->get_status_message() << endl;
				//				cout << "Date: " << temp->get_date() << endl;
				//				cout << "Time: " << temp->get_time() << endl;
				//				cout << "--------------------------" << endl;

				des.gotoxy(2, y);
				cout << " " << temp->get_status_id() << "  @ " << temp->get_name() << ":-";

				y++;
				des.gotoxy(2, y);
				cout << string(temp->get_name().length() + 6, ' ');
				cout << "  " << temp->get_status_message();

				y++;
				des.gotoxy(2, y);

				cout << string(des.getTerminalWidth() / 2, ' ') << "\t DATE: " << temp->get_date() << "    TIME: " << temp->get_time();

				y++;
				des.gotoxy(2, y);
				des.display_line_p();
				y++;
				temp = temp->get_next();
			}
			return true;
		}
		else
		{
			//			cout << "You Have no Status yet" << endl;
			des.display_center("You Have no Status yet");
			cin.get();
			return false;
		}
	}

	Status_Node* search(const string& status_id)
	{
		Status_Node* temp = head_Status_Node;
		while (temp != NULL)
		{
			if (temp->get_status_id() == status_id)
			{
				return temp;
			}
			temp = temp->get_next();
		}
		return NULL;
	}

	void get_friends()
	{
		ifstream output(organization_files::friends);
		if (output)
		{
			string line;
			while (getline(output, line))
			{

				string id, user1, user2;
				istringstream data(line);
				data >> id >> user1 >> user2;

				Components::get_decrypt_text(id);
				Components::get_decrypt_text(user1);
				Components::get_decrypt_text(user2);

				if (user1 == static_username)
				{
					vector_names.push_back(user2);
				}
				else if (user2 == static_username)
				{
					vector_names.push_back(user1);
				}
			}
			output.close();
		}
	}

	bool check_friend(string name)
	{
		if (vector_names.empty())
		{
			return false;
		}
		for (const auto friends : vector_names)
		{
			if (friends == name)
			{
				return true;
			}
		}
		return false;
	}

	~Status_list()
	{
		Status_Node* temp;
		while (head_Status_Node != NULL)
		{
			temp = head_Status_Node->get_next();
			delete head_Status_Node;
			head_Status_Node = temp;
		}
	}
};

class Status
{
	string choice;
	string line;
	string value;

public:

	Status()
	{
		while (1)
		{
			system("CLS");
			vector<string> menuItems = { "Add", "Delete", "View", "Back" };
			int position = des.displayMenu(menuItems);
			des.tab_status_management();
			des.display_line_slash();
			des.display_enter("Select", "1-4", position);

			//			cout << "\n1. Add\n2. Delete\n3. View\n4. Back\n" << endl;
			//			cout << "Select [1-4] : ";

			choice = Components::input_number_value();

			if (choice == "1")
			{
				add_status();
			}
			else if (choice == "2")
			{
				delete_status();
			}
			else if (choice == "3")
			{
				system("CLS");
				des.border();
				des.tab_status_management_add();
				des.display_line_slash();

				view_status();
			}
			else if (choice == "4")
			{
				break;
			}
			else
			{
				cout << "Invalid Choice";
				cin.get();
			}
		}
	}

	void add_status()
	{
		system("CLS");
		des.border();
		des.tab_status_management_add();
		des.display_line_slash();

		des.display_enter("Enter Status Message", 10);
		//		cout << "Enter Status Message : ";
		value = Components::input_text_value();

		string id = to_string(Components::generate_id(organization_files::status));
		string name = static_username;
		string date = Components::get_current_date();
		string time = Components::get_current_time();

		Components::get_encrypt_text(id);
		Components::get_encrypt_text(name);
		Components::get_encrypt_text(value);
		Components::get_encrypt_text(date);
		Components::get_encrypt_text(time);

		if (static_tier == "simple")
		{
			bool check = false;
			ifstream output(organization_files::status);
			if (output)
			{
				ofstream temp(organization_files::temp);
				while (getline(output, line))
				{
					string f_name;
					istringstream data(line);
					data >> id >> f_name;

					Components::get_decrypt_text(f_name);

					if (f_name == static_username)
					{
						temp << id << " " << name << " " << value << " " << date << " " << time << endl;
						check = true;
					}
					else
					{
						temp << line << endl;
					}

				}
				output.close();
				temp.close();
				remove(organization_files::status);
				rename(organization_files::temp, organization_files::status);
			}
			if (!check)
			{
				ofstream output(organization_files::status, ios::app);
				output << id << " " << name << " " << value << " " << date << " " << time << endl;
				output.close();
				des.display_sucessfully_p("Status Added", 14);
				//				cout << "Status Added Successfully";
			}
			else
			{
				des.display_sucessfully_p("Status Updated", 14);
			}
		}
		else if (static_tier == "premium")
		{
			ofstream output(organization_files::status, ios::app);
			output << id << " " << name << " " << value << " " << date << " " << time << endl;
			output.close();
			des.display_sucessfully_p("New Status Added", 14);
		}
		else
		{
			cout << "Tier Error Occur";

		}
		cin.get();
	}

	void delete_status()
	{
		system("CLS");
		des.border();
		des.tab_status_management_delete();
		des.display_line_slash();
		des.border();
		des.tab_status_management_delete();
		des.display_line_slash();


		Status_list list;
		if (list.get_values(true))
		{
			if (list.display())
			{
				if (static_tier == "simple")
				{
					//					cout << "Do you want to delete your status [Yes/No] : ";
					des.display_do_you_p("want to delete your status ", "[Yes/No]", 14);
					choice = Components::input_string_choice();

					if (choice == "Yes")
					{
						bool check = false;
						ifstream output(organization_files::status);
						if (output)
						{
							ofstream temp("Temp.txt");
							while (getline(output, line))
							{
								string id, f_name;
								istringstream data(line);
								data >> id >> f_name;

								Components::get_decrypt_text(f_name);

								if (f_name == static_username)
								{
									check = true;
								}
								else
								{
									temp << line << endl;
								}

							}
							output.close();
							temp.close();
							remove(organization_files::status);
							rename("Temp.txt", organization_files::status);
						}
						if (!check)
						{
							//							cout << "Your Status not found";
							des.display_side("Your Status not found", 16);
						}
						else
						{
							des.display_sucessfully_p("Status Deleted", 16);
						}
						cin.get();
					}
				}
				else if (static_tier == "premium")
				{
					//					cout << "Do you want to delete your status [Yes/No] : ";
					des.display_do_you_p("want to delete your status ", "[Yes/No]", 16);

					choice = Components::input_string_choice();

					if (choice == "Yes")
					{
						des.display_enter("Enter Status ID", 18);
						//						cout << "Enter Status ID : ";
						value = Components::input_number_value();

						Status_Node* found = list.search(value);

						if (found != NULL)
						{
							bool check = false;
							ifstream output(organization_files::status);
							if (output)
							{
								ofstream temp(organization_files::temp);
								while (getline(output, line))
								{
									string id, f_name;
									istringstream data(line);
									data >> id >> f_name;

									Components::get_decrypt_text(id);
									Components::get_decrypt_text(f_name);

									if (f_name == static_username && value == id)
									{
										check = true;
									}
									else
									{
										temp << line << endl;
									}

								}
								output.close();
								temp.close();
								remove(organization_files::status);
								rename(organization_files::temp, organization_files::status);
							}
							if (!check)
							{
								//								cout << "Your Status not found";
								des.display_side("Your Status not found", 18);
							}
							else
							{
								//								cout << "Status Deleted Successfully";
								des.display_sucessfully_p("Status Deleted", 20);
							}
							cin.get();
						}
						else
						{
							des.display_invalid_p("Invalid ID", 20);
							cin.get();
						}
					}
				}
				else
				{
					cout << "User Tier Error Occur";
					cin.get();
				}
			}
		}
	}

	void view_status()
	{
		system("CLS");
		des.border();
		des.tab_status_management_view();
		des.display_line_slash();
		Status_list list;
		list.get_friends();
		if (list.get_values(false))
		{
			if (list.display())
			{
				//				cout << "Press any key to return";
				cin.get();
			}
		}
	}



};


// End Previous Here


class Setting
{
	string choice;
	string pass, line;

public:

	Setting()
	{
		while (1)
		{
			system("CLS");
			vector<string> menuItems = { "Change Password", "Change Theme", "Get Backup", "Get Premium","View Profile","Delete Account","Back" };
			int position = des.displayMenu(menuItems);
			des.tab_setting();
			des.display_line_slash();
			des.display_enter("Select", "1-7", position);

			//			cout << "1. Change Password\n2. Change Theme\n3. Get Backup\n4. Get Premium\n5. View Profile\n6. Delete Account\\n7. Back\n";
			//			cout << "Select [1-6] : ";

			choice = Components::input_number_value();

			if (choice == "1")
			{
				change_password();
			}
			else if (choice == "2")
			{
				if (static_tier == "simple")
				{
					system("cls");
					des.display_center("You Don't Have Access to this Feature Buy Premium To Use Pro Features");
					cin.get();
				}
				else
				{
					change_theme();
				}

			}
			else if (choice == "3")
			{
				if (static_tier == "simple")
				{
					system("cls");
					des.display_center("You Don't Have Access to this Feature Buy Premium To Use Pro Features");
					cin.get();
				}
				else
				{
					get_backup();
				}
			}
			else if (choice == "4")
			{
				if (static_tier == "premium")
				{
					system("cls");
					des.display_center_g("You are already a premium user");
					cin.get();
				}
				else
				{
					get_premium("as");
				}
				
			}
			else if (choice == "5")
			{
				view_profile();
				cin.get();
			}
			else if (choice == "6")
			{
				system("CLS");
				des.border();
				des.tab_setting_da();
				des.display_line_slash();
				int p = 10;
				des.display_do_you_p("Do you want to delete your Account", "Yes/No", p);

				choice = Components::input_string_choice();

				if (choice == "Yes")
				{
					if (delete_user())
					{
						p += 2;
						//						cout << "Your Account Deleted Successfully" << endl;
						des.display_sucessfully_p("Your Account Deleted", p);
						char currentExecutablePath[1024];
						GetModuleFileNameA(NULL, currentExecutablePath, sizeof(currentExecutablePath));

						// Relaunch the executable
						string command = "\"" + string(currentExecutablePath) + "\"";
						system(command.c_str());

						// Exit the current process
						exit(0);
					}
				}

			}
			else if (choice == "7")
			{
				break;
			}
			else
			{
				//				cout << "Invalid Input";
				position += 2;
				des.display_invalid_p("Input", position);
			}
		}
	}


	void change_password()
	{
		system("CLS");
		des.border();
		des.tab_setting_cp();
		des.display_line_slash();
		int p = 10;
		//		cout << "Enter Password : ";
		des.display_enter("Enter Your Password", p);
		pass = Components::input_password();		// Input Password in starik form


		User_Credentials_List* list = new User_Credentials_List();
		list->get_values();

		int value = list->check_login(static_username, pass, static_tier);

		if (value == 1)
		{
			string pass1;
			string pass2;

			p += 2;
			des.display_enter("Enter New Password", p);
			//			cout << "Enter New Password :";
			pass1 = Components::input_password();		// Input Password in starik form

			//			cout << "Confirm New Password :";
			p += 2;
			des.display_enter("Confirm New Password", p);

			pass2 = Components::input_password();		// Input Password in starik form

			while (1)
			{
				int check = 0;
				if (pass1 == pass2)
				{
					break;
				}
				if (check == 2)
				{
					break;
				}
				else
				{

					des.display_enter("Confirm New Password", p);
					des.gotoxy((des.getTerminalWidth() / 2) + 8 + pass.length(), p);
					for (int i = 0;i < pass2.length();i++)
					{
						cout << "\b \b";
					}

					pass2 = Components::input_password();		// Input Password in starik form
					check++;
				}

			}

			if (pass1 == pass2)
			{


				ifstream ob(organization_files::user_credentials);
				if (ob)
				{
					string file_name, file_email, file_password, file_tier, file_date, line;
					ofstream temp(organization_files::temp);		// Create a Temp file	
					while (getline(ob, line))
					{
						istringstream data(line);
						data >> file_name >> file_email >> file_password;

						Components::get_decrypt_text(file_name);
						Components::get_decrypt_text(file_password);

						if (file_name == static_username && pass == file_password)
						{
							data >> file_tier >> file_date;

							Components::get_encrypt_text(file_name);
							Components::get_encrypt_text(pass1);

							temp << file_name << " " << file_email << " " << pass1 << " " << file_tier << " " << file_date << endl;
						}
						else
						{
							temp << line << endl;
						}
					}
					ob.close();
					temp.close();
					remove(organization_files::user_credentials);
					rename(organization_files::temp, organization_files::user_credentials);
					p += 2;
					des.display_sucessfully_p("PASSWORD UPDATED", p);


				}
				else
				{
					//					des.display_file();
				}
			}
			else
			{
				p += 2;
				//				cout << "\nBoth Password Doesn't Match" << endl;
				des.display_side("Both Password Doesn't Match", p);
				cin.get();
			}

		}
		else if (value == 0)
		{
			p += 2;
			des.display_invalid_p("Password", p);
		}

		delete list;
	}


	void get_backup()
	{
		system("CLS");
		des.border();
		des.tab_setting_gb();
		des.display_line_slash();
		int p = 10;
		// List of file paths
		vector<string> files;
		string line;

		ifstream output(organization_files::group);
		if (output)
		{


			while (getline(output, line))
			{
				string group_id, group_name, group_admin;
				istringstream obj(line);
				obj >> group_id >> group_name >> group_admin;

				Components::get_decrypt_text(group_id);
				Components::get_decrypt_text(group_name);
				Components::get_decrypt_text(group_admin);

				if (group_admin == static_username)
				{
					group_name += ".txt";
					files.push_back(group_name);
				}
				else
				{
					ifstream output1(organization_files::group_members);
					if (output1)
					{
						while (getline(output1, line))
						{
							string file_group_id, file_name;
							istringstream obj1(line);

							obj1 >> file_group_id >> file_name;

							Components::get_decrypt_text(file_group_id);
							Components::get_decrypt_text(file_name);

							if (group_id == file_group_id && file_name == static_username)
							{
								group_name += ".txt";
								files.push_back(group_name);
								output1.close();
								break;
							}

						}
						output1.close();
					}
				}
			}
			output.close();
		}


		ifstream f_output(organization_files::friends);
		if (f_output)
		{
			while (getline(f_output, line))
			{
				string id, user1, user2, f_name;

				istringstream data(line);

				data >> id >> user1 >> user2 >> f_name;

				Components::get_decrypt_text(id);
				Components::get_decrypt_text(user1);
				Components::get_decrypt_text(user2);
				Components::get_decrypt_text(f_name);

				if (user1 == static_username || user2 == static_username)
				{
					files.push_back(f_name);
				}

			}
			f_output.close();
		}

		if (files.empty())
		{
			//				cout<<"You have no chats yet";
			des.display_center("You have no chats yet");
			cin.get();
		}
		else
		{
			string path;
			des.display_enter("Enter Path", p);

			getline(cin, path);

			// Create a temporary batch file
			string batchFilePath = "zip_files.bat";



			ofstream batchFile(batchFilePath);

			if (!batchFile) {
				p += 4;
				des.display_side("Error creating batch file.", p);
				cin.get();
				return;
			}


			batchFile << "@echo off" << endl; // Optional: Suppress command output
			batchFile << "\"C:\\Program Files\\7-Zip\\7z.exe\" a \"" + path + "\\" + static_username + ".zip\" ";


			for (const auto& file : files) {
				batchFile << "\"" << file << "\" "; // Enclose each path in quotes
			}

			batchFile.close(); // Close the batch file


			p += 2;
			des.display_side("Executing command from batch file", p);

			// Execute the batch file
			des.gotoxy((des.getTerminalWidth() / 3) * 2, p + 2);
			int result = system(batchFilePath.c_str());
			p += 2;
			if (result == 0) {
				p += 2;
				des.display_side("Files zipped successfully!", p);

			}
			else {

				p += 2;
				des.display_side("Error zipping files.", p);
				cin.get();
				return;
			}

			// delete the batch file after execution
			remove(batchFilePath.c_str());

			p += 2;
			//				cout<<"Chat Backup Successfully";
			des.display_sucessfully_p("Chat Backup", p);
			//				

		}
	}


	void view_profile()
	{
		system("CLS");
		des.border();
		des.tab_setting_vp();
		des.display_line_slash();

		int p = 10;
		//		cout << "Enter Password : ";
		des.display_enter("Enter Your Password", p);
		pass = Components::input_password();


		User_Credentials_List* list = new User_Credentials_List;
		list->get_values();

		list->display(static_username, pass);

		des.tab_setting_vp();
		des.display_line_slash();
		cin.get();

	}


	void get_premium(const string email)
	{
		string account;
		system("CLS");

		des.tab_setting_gp();
		des.display_line_slash();
		int p = 10;
		string m1 = "Unlock Premium Features for a Better Experience!";
		string m2 = "Upgrade to Premium now and elevate your experience!";
		string m3 = "Price : 10rs";
		//		des.gotoxy((des.getTerminalWidth()/2)-m1.length()/2,p);
		//		cout << m1;;
		//		cout << "Unlock Premium Features for a Better Experience!\n\n\t\t1. Change Theme: Personalize your interface with exclusive themes. \n\t\t2. Get Backup: Secure your data with advanced backup options.\n\t\t3. Multiple Device Login: Access your account seamlessly on multiple devices at the same time.\n\t\t4. Show Deleted Messages: Retrieve and view deleted messages effortlessly.\n\nUpgrade to Premium now and elevate your experience! ";

		vector<string> features = {
		"Personalize your interface with exclusive themes",
		"Secure your data with advanced backup options",
		"Access your account seamlessly on multiple devices at the same time",
		"Retrieve and view deleted messages effortlessly."
		};
		p = des.getPremium(features);
		des.tab_setting_gp();
		des.display_line_slash();

		p -= 2;
		des.gotoxy((des.getTerminalWidth() / 2) - m1.length() / 2, p);
		cout << m2;

		p += 2;
		des.gotoxy((des.getTerminalWidth() / 2) - m1.length() / 2, p);
		cout << m3;

		p += 2;
		des.display_do_you_p("want to get Premium", "Yes/No", p);
		//		cout << "Do You Want To Get Premium [Yes/No] : ";
		choice = Components::input_string_choice();
		if (choice == "Yes")
		{
			p += 2;
			des.display_enter("Enter Acoount Number", "16 digits", p);
			//			cout << "Enter Account Number [16-Digits] : ";
			account = Components::input_account_no();
			cout << endl;

			// Here is the email code

			ifstream output(organization_files::user_credentials);
			if (output)
			{
				string f_u, f_e, f_p, f_t, f_d;
				ofstream temp(organization_files::temp);
				while (getline(output, line))
				{
					istringstream data(line);
					data >> f_u;

					Components::get_decrypt_text(f_u);

					if (f_u == static_username)
					{
						data >> f_e >> f_p >> f_t >> f_d;

						f_t = "premium";
						Components::get_encrypt_text(f_u);
						Components::get_encrypt_text(f_t);

						temp << f_u << " " << f_e << " " << f_p << " " << f_t << " " << f_d << endl;

					}
					else
					{
						temp << line << endl;
					}

				}
				output.close();
				temp.close();
				remove(organization_files::user_credentials);
				rename(organization_files::temp, organization_files::user_credentials);
				static_tier = "premium";
			}
			else
			{
				//				cout << "File Doesn't Found";
				p += 2;
				des.display_file_p(p);
			}

		}

	}


	void change_theme()
	{
		char theme;

		while (1)
		{
			system("CLS");
			vector<string> menuItems = { "Switch Color Mode", "Advance Customization", "Back" };
			int position = des.displayMenu(menuItems);
			des.tab_setting_ct();
			des.display_line_slash();
			des.display_enter("Select", "1-3", position);

			//				cout<<"1. Switch Color Mode\n2. Advance Customization\n3. Back"<<endl;
			//				cout<<"\nSelect [1-3] : ";
			choice = Components::input_number_value();

			if (choice == "1")
			{
				// Here is the code for switch modes
				if (des.get_theme() == 0)
				{
					system("cls");

					des.set_theme(-1);

					des.border();

					system("cls");
					//							goto apply_theme;
				}
				else
				{
					//							int Design::theme = 1;
					system("cls");
					des.set_theme(0);
					des.border();
					system("cls");
					//							goto apply_theme;
				}
			}
			else if (choice == "2")
			{
				if (des.get_theme() != -1)
				{
					system("CLS");
					vector<string>colors = {
								"White",
								"Light Yellow",
								"Light Aqua",
								"Bright Purple",
								"Bright Blue"
					};

					int p = des.displayMenu(colors);
					des.display_enter("Select", "1-5", p);
					theme = Components::input_color();
					if (theme < '1' || theme>'5')
					{
						p += 2;
						des.display_invalid_p("Choice", p);
						break;
					}

					//						cout << "Do You Want To Change Color [Yes/No] : ";
					p += 1;
					des.display_do_you_p("Want To Change Color", "Yes/No", p);
					choice = Components::input_string_choice();

					if (choice == "Yes")
					{
						//							des.set_theme(0);
						des.set_theme(theme - '0');
					}
				}
				else
				{
					system("cls");
					des.display_center("Please Switch Color Mode To Default change Theme");
					cin.get();
				}
			}
			else if (choice == "3")
			{
				break;
			}
			else
			{
				position += 2;
				//						cout<<"Invalid Choice";
				des.display_invalid_p("Choice", position);
				cin.get();
			}

		}

	}



	bool delete_user()
	{
		string line;
		ifstream output(organization_files::user_credentials);
		if (output)
		{
			ofstream temp(organization_files::temp);
			while (getline(output, line))
			{
				istringstream data(line);
				string f_u;

				data >> f_u;

				Components::get_decrypt_text(f_u);

				if (f_u != static_username)
				{
					temp << line << endl;
				}
			}
			output.close();
			temp.close();

			remove(organization_files::user_credentials);
			rename(organization_files::temp, organization_files::user_credentials);
		}

		ifstream o1(organization_files::user_address);
		if (o1)
		{
			ofstream temp(organization_files::temp);
			while (getline(o1, line))
			{
				istringstream data(line);
				string f_i, f_u;

				data >> f_i >> f_u;

				Components::get_decrypt_text(f_u);

				if (f_u != static_username)
				{
					temp << line << endl;
				}
			}
			output.close();
			temp.close();

			remove(organization_files::user_address);
			rename(organization_files::temp, organization_files::user_address);

		}

		vector<string>* id = NULL;

		ifstream o2(organization_files::group);
		if (o2)
		{
			id = new vector<string>;
			ofstream temp(organization_files::temp);
			string f_i, f_n, f_a;
			while (getline(o2, line))
			{
				istringstream data(line);
				data >> f_i >> f_n >> f_a;

				Components::get_decrypt_text(f_a);

				if (f_a == static_username)
				{
					id->push_back(f_i);
					Components::get_decrypt_text(f_n);
					f_n += ".txt";
					const char* filename = f_n.c_str();
					remove(filename);
				}
				else
				{
					temp << line << endl;
				}

			}
			o2.close();
			temp.close();

			remove(organization_files::group);
			rename(organization_files::temp, organization_files::group);
		}

		ifstream o3(organization_files::group_members);
		if (o3)
		{
			ofstream temp(organization_files::temp);
			while (getline(o3, line))
			{
				string f_i, f_u;
				istringstream data(line);
				data >> f_i >> f_u;

				Components::get_decrypt_text(f_u);

				if (f_u != static_username && !check_id(id, f_i))
				{
					temp << line << endl;
				}
			}
			o3.close();
			temp.close();

			remove(organization_files::group_members);
			rename(organization_files::temp, organization_files::group_members);
		}

		ifstream o4(organization_files::friends);
		if (o4)
		{
			ofstream temp(organization_files::temp);
			string f_i, f_u1, f_u2, f_f;
			while (getline(o4, line))
			{
				istringstream data(line);
				data >> f_i >> f_u1 >> f_u2;

				Components::get_decrypt_text(f_u1);
				Components::get_decrypt_text(f_u2);

				f_f = f_u1 + f_u2 + ".txt";

				if (f_u1 == static_username || f_u2 == static_username)
				{
					const char* filename = f_f.c_str();
					remove(filename);
				}
				else
				{
					temp << line << endl;
				}

			}
			o4.close();
			temp.close();

			remove(organization_files::friends);
			rename(organization_files::temp, organization_files::friends);
		}

		ifstream o5(organization_files::friend_request);
		if (o5)
		{
			ofstream temp(organization_files::temp);
			string f_i, f_u1, f_u2, f_f;
			while (getline(o5, line))
			{
				istringstream data(line);
				data >> f_i >> f_u1 >> f_u2;

				Components::get_decrypt_text(f_u1);
				Components::get_decrypt_text(f_u2);

				f_f = f_u1 + f_u2 + ".txt";

				if (f_u1 != static_username && f_u2 != static_username)
				{
					temp << line << endl;
				}
			}
			o5.close();
			temp.close();

			remove(organization_files::friend_request);
			rename(organization_files::temp, organization_files::friend_request);
		}

		ifstream o6(organization_files::status);
		if (o6)
		{
			ofstream temp(organization_files::temp);
			while (getline(o6, line))
			{
				string f_i, f_u;
				istringstream data(line);
				data >> f_i >> f_u;

				Components::get_decrypt_text(f_u);

				if (f_u != static_username)
				{
					temp << line << endl;
				}
			}
			o6.close();
			temp.close();


			remove(organization_files::status);
			rename(organization_files::temp, organization_files::status);
		}

		return true;

	}


	bool check_id(vector<string>* id, string f_id)
	{
		for (const auto& value : *id)
		{
			if (value == f_id)
			{
				return true;
			}
		}
		return false;
	}

};

class Main
{

	User_Credentials_List* user_list;
	int login_value;
	bool running;

public:

	string username;
	string email;
	string tier;

	string choice;

	Main()
	{
		login_value = 0;
		while (1)
		{
			running = false;
			system("CLS");

			des.fullscreen();
			des.border();
			vector<string> menuItems = { "Login", "Signup", "Forget", "Exit" };
			int position = des.displayMenu(menuItems);
			des.display_enter("Your Choice", "1-4", position);
			//			cout << "\nSelect [1-4] : ";

			choice = Components::input_number_value();

			user_list = new User_Credentials_List();
			user_list->get_values();

			if (choice == "1")
			{
				if (login(user_list))
				{
					while (1)
					{
						system("CLS");

						vector<string> menuItems = { "Status Management", "Friends", "Groups", "Setting","Log Out" };
						//						cout << "\n1. Status Management\n2. Friends\n3. Groups\n4. Setting\n5. LogOut\n" << endl;
						//						cout << "\nSelect [1-5] : ";
						int position = des.displayMenu(menuItems);
						des.tab_dashboard();
						des.display_line_slash();
						des.display_enter("Select", "1-5", position);
						choice = Components::input_number_value();
						if (choice == "1")
						{
							Status obj;
						}
						else if (choice == "2")
						{
							while (1)
							{
								system("CLS");
								des.border();
								vector<string> menuItems = { "Friends Management", "Friend Chats", "Back" };
								int position = des.displayMenu(menuItems);
								des.tab_friends();
								des.display_line_slash();
								des.display_enter("Your Choice", "1-3", position);

								//								cout << "1. Friends Management\n2. Friend Chats\n3. Back";
								//								cout << "\nSelect [1-3] : ";
								choice = Components::input_number_value();

								if (choice == "1")
								{
									Friends_Management obj;
								}
								else if (choice == "2")
								{
									chat_management obj("Friend");
								}
								else if (choice == "3")
								{
									break;
								}
								else
								{
									cout << "Invalid Choice";
									cin.get();
								}

							}
						}
						else if (choice == "3")
						{
							while (1)
							{
								system("CLS");
								des.border();
								vector<string> menuItems = { "Groups Management", "Group Chats", "Back" };
								int position = des.displayMenu(menuItems);
								des.tab_groups();
								des.display_line_slash();
								des.display_enter("Select", "1-3", position);

								//								cout << "1. Groups Management\n2. Group Chats\n3. Back";
								//								cout << "\nSelect [1-3] : ";
								choice = Components::input_number_value();

								if (choice == "1")
								{
									Group_Management obj;
								}
								else if (choice == "2")
								{
									chat_management obj("Group");
								}
								else if (choice == "3")
								{
									break;
								}
								else
								{
									cout << "Invalid Choice";
									cin.get();
								}

							}
						}
						else if (choice == "4")
						{
							Setting obj;
						}
						else if (choice == "5")
						{
							break;
						}
						else
						{
							cout << "Invalid Choice";
							cin.get();
						}
					}

				}
			}
			else if (choice == "2")
			{
				signup(user_list);
				delete user_list;
			}
			else if (choice == "3")
			{
				forget(user_list);
				delete user_list;
			}
			else if (choice == "4")
			{
				running = false;
				delete user_list;
				break;
			}
			else
			{
				delete user_list;
				des.display_invalid_p("Choice", position + 1);
				cin.get();
			}

		}
	}

	void signup(User_Credentials_List* list)
	{
		system("CLS");
		des.border();
		des.tab_signup();
		des.display_line_slash();

		int p = 10;

		string update_username;
		des.display_enter("Enter Username", p);
		//		cout << "\nEnter Username : ";
		username = Components::input_text_value();
		update_username = username;

		check_username(list, username);
		if (!(update_username == username))
		{
			p = p + 6;
		}

		string update_email;
		p = p + 2;
		des.display_enter("Enter Email", p);
		//		cout << "Enter Email : ";
		email = Components::input_email();
		update_email = email;

		check_email(list, email);


		if (update_email != email)
		{
			p = p + 7;
		}
		p = p + 1;

		p = p + 2;
		des.display_enter("Enter Password", p);
		//		cout << "Enter Password : ";
		string password = Components::input_password();

		p = p + 2;
		//		des.display_enter(" Do you want to SignUp","Yes/No",16);
		des.display_do_you_p("want to Signup", "Yes/No", p);
		//		cout << "Do you want to SignUp [Yes/No] : ";
		choice = Components::input_string_choice();

		if (choice == "Yes")
		{
			
			string date = Components::get_current_date();
			Components::get_encrypt_text(username);
			Components::get_encrypt_text(email);
			Components::get_encrypt_text(password);
			tier = "simple";
			Components::get_encrypt_text(tier);
			Components::get_encrypt_text(date);


			ofstream file(organization_files::user_credentials, ios::app);
			file << username << " " << email << " " << password << " " << tier << " " << date << endl;
			file.close();

			p = p + 2;
			des.display_sucessfully_p("New User Added", p);
			//			cout << "New User Added Successfully" << endl;
			cin.get();


		}





	}

	void generate_username(User_Credentials_List* list, string name)
	{
		string values = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
		string next_name[3];
		srand(static_cast<unsigned int>(time(0)));
		for (int i = 0;i < 3;)
		{
			next_name[i] = name;

			for (int j = 0;j < 3;j++)
			{
				int n = rand() % values.length();
				next_name[i] += values[n];
			}

			if (list->check_username(next_name[i]))
			{
				cout << next_name[i];

				if (i != 2)
				{
					cout << ", ";
				}
				i++;
			}
		}
	}

	bool login(User_Credentials_List* list)
	{
		system("CLS");
		des.border();
		des.tab_login();
		des.display_line_slash();
		des.display_enter("Username", 10);
		//		cout << "Username : ";
		username = Components::input_text_value();
		des.display_enter("Password", 12);
		//		cout << "Password : ";
		string pass = Components::input_password();
		//		string pass = "12345678";

		int value = list->check_login(username, pass, tier);

		static_username = username;
		static_tier = tier;


		if (value == 1)
		{

			string address = Components::getMACAddress();


			if (!check_mac_address(address))
			{

				//cout << endl;
				string rand_code = Components::generate_OTP();
				des.display_enter("Your OTP", 13);
				cout << rand_code ;
				

				des.display_enter("Enter Verification Code", 15);
				
				string code = Components::input_OTP();

				if (code == rand_code)
				{
					insert_mac_address(address);
				}

			}
			delete list;
			if (static_tier == "simple")
			{
				des.set_theme(0);
			}
			des.display_sucessfully_p(username + " Logined", 16);
			//			cout << username << " Login Successfully" << endl;
			cin.get();
			login_value = 0;


			if (tier == "simple")
			{
				running = true;
				thread checkThread(&Main::check_login, this);
				checkThread.detach();  // Detach the thread to run independently
			}
			cin.get();
			return true;
		}
		else if (value == 0)
		{
			login_value++;
			//			cout << "Invalid Username OR Password" << endl;
			des.display_invalid_p("Username or Password", 17);
			cin.get();
			if (login_value == 3)
			{
				//				cout << "Wait Still 10s to retry" << endl;
				des.display_side("Wait Still 10s to retry", 18);
				BlockInput(TRUE);
				Sleep(10000);
				BlockInput(FALSE);
				//				cout << "Now you can Retry" << endl;
				des.display_side("Now you can Retry", 19);
				cin.get();
				login_value = 0;
			}
			return false;
		}
		else if (value == 2)
		{
			return false;
		}


	}

	void forget(User_Credentials_List* list)
	{
		system("CLS");
		des.border();
		des.tab_forget();
		des.display_line_slash();

		string code, rand_code;
		string password, date, file_email;

		des.display_enter("Enter Email", 10);
		//		cout << "Enter Email : ";
		email = Components::input_email();

		if (list->check_email(email))
		{
			cout << endl;
			rand_code = Components::generate_OTP();
			cout << rand_code << endl;
			// Send Emial Verification Code

			des.display_enter("Enter Verification Code", 12);
			//			cout << "Enter Verification Code : ";
			code = Components::input_OTP();

			if (code == rand_code)
			{
				ifstream output(organization_files::user_credentials);
				if (output)
				{
					string line;
					while (getline(output, line))
					{

						istringstream data(line);
						data >> username >> file_email >> password >> tier >> date;

						Components::get_decrypt_text(username);
						Components::get_decrypt_text(file_email);
						Components::get_decrypt_text(password);
						Components::get_decrypt_text(tier);
						Components::get_decrypt_text(date);


						if (email == file_email)
						{
							des.display("Username", 14);
							cout << username << endl;
							des.display("Password", 16);
							cout << password << endl;
							output.close();
							cin.get();
							return;
						}


					}
					output.close();

					//					cout << "Your Email Not Found in Record" << endl;
					des.display_side("Your Email Not Found in Record", 14);
					cin.get();

				}
				else
				{
					cout << "File Doesn't Found" << endl;
					cin.get();
				}
			}



		}
		else
		{
			//			cout << "Invalid Email" << endl;
			des.display_invalid_p("Email", 12);
			cin.get();
		}

	}

	bool check_mac_address(string pass_address)
	{
		ifstream output(organization_files::user_address);
		if (output)
		{
			string line;
			string file_user_name, file_address;

			while (getline(output, line))
			{
				istringstream data(line);
				data >> file_user_name >> file_address;

				Components::get_decrypt_text(file_user_name);
				Components::get_decrypt_text(file_address);

				if (static_username == file_user_name && file_address == pass_address)
				{
					output.close();
					return true;
				}
			}
			return false;
		}
		return false;
	}

	void insert_mac_address(string pass_address)
	{
		bool found = false;
		if (tier == "simple")
		{
			ifstream obj(organization_files::user_address);
			if (obj)
			{
				ofstream temp(organization_files::temp);
				string line;
				string file_user_name, file_address;

				while (getline(obj, line))
				{
					istringstream data(line);
					data >> file_user_name >> file_address;

					Components::get_decrypt_text(file_user_name);
					Components::get_decrypt_text(file_address);

					if (username == file_user_name)
					{
						found = true;
						Components::get_encrypt_text(file_user_name);
						Components::get_encrypt_text(pass_address);
						temp << file_user_name << " " << pass_address << endl;
					}
					else
					{
						temp << line << endl;
					}
				}

				obj.close();
				temp.close();
				remove(organization_files::user_address);
				rename(organization_files::temp, organization_files::user_address);
			}
			if (!found)
			{
				insert_mac_in_file(pass_address);
			}

		}
		else
		{
			insert_mac_in_file(pass_address);
		}
	}

	void insert_mac_in_file(string pass_address)
	{
		ofstream output(organization_files::user_address, ios::app);
		string name = static_username;
		Components::get_encrypt_text(name);
		Components::get_encrypt_text(pass_address);
		output << name << " " << pass_address << endl;
		output.close();
	}

	void check_login()
	{
		while (running)
		{
			if (!check_mac_address(Components::getMACAddress()))
			{
				des.display_center("Your Account Removed From Current System OR it may be Unauthorized Access");
				//				cout << "\n\nYour Account Removed From Current System OR it may be Unauthorized Access" << endl;

				BlockInput(TRUE);
				Sleep(3000);
				BlockInput(FALSE);

				running = false;

				char currentExecutablePath[1024];
				GetModuleFileNameA(NULL, currentExecutablePath, sizeof(currentExecutablePath));

				// Relaunch the executable
				string command = "\"" + string(currentExecutablePath) + "\"";
				system(command.c_str());

				// Exit the current process
				exit(0);
			}
			this_thread::sleep_for(chrono::seconds(1));
		}

	}

	void check_username(User_Credentials_List* list, string& pass_username)
	{
		bool check = true;
		while (1)
		{
			if (list->check_username(pass_username))
			{
				break;
			}

			if (check)
			{
				check = false;

				des.display_already_contained_p("This Username", 12);
				//				cout << "\nThis username already contained" << endl;
				des.display("Suggested Username", 14);
				//				cout << "Suggested Username : { ";
				generate_username(list, pass_username);

				des.display_side("Try Different Username", 15);
				//				cout << "\nTry Different Username : ";
				des.display_enter("Enter Username", 16);
			}
			else
			{
				for (int i = 0;i < pass_username.length();i++)
				{
					cout << "\b \b";
				}
			}
			pass_username = Components::input_text_value();
		}
	}

	void check_email(User_Credentials_List* list, string& pass_email)
	{
		bool check = true;
		while (1)
		{
			if (!list->check_email(pass_email))
			{
				break;
			}

			if (check)
			{
				check = false;
				des.display_already_contained_p("This Email", 19);
				//				cout << "\nThis email already contained" << endl;
				//				cout << "\nTry Different Email : ";
				des.display_side("Try Different Email", 20);
				des.display_enter("Enter Email", 21);
			}
			else
			{
				for (int i = 0;i < pass_email.length();i++)
				{
					cout << "\b \b";
				}
			}

			pass_email = Components::input_email();

		}
	}

};


// End Previous Here


int main()
{

	des.setTerminalZoom(1.25);
apply_theme:
	Main obj;
	return 0;
}



