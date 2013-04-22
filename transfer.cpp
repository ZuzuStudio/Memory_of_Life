#include "transfer.h"

bool Equality_Test_For_String(const char *first, const char *second)
{
   for(int i = 0; first[i] != '\0' || second[i] != '\0'; i++)
   {
      if(first[i] != second[i]) return false;
   }

   return true;
}

#if defined WINDOWS

namespace ccg
{
   const char *windS[] = {"\xcd", "\xda", "\xbf", "\xd9", "\xc0", "\xb3", "\xc4", "\xc5", "\xc2", "\xb4", "\xc1", "\xc3", "\xb0", "\xb1", "\xb2", "\x010", "\x01", "\xfd", "\x02a", "\x03", "\x07f", "\xdb", "\x12"};
   const char windC[] = {'\10', '\15', '\11', '\40'};
   const char *windA[] = {"\340\110", "\340\113", "\340\115", "\340\120"};

   void sleep(int time)
   {
      Sleep(time);
   }

   void Pause()
   {
      system("pause");
   }

   void CleanConsol()
   {
      system("cls");
   }

   int GetKey()
   {
      return _getch();
   }

   int kbhit()
   {
      return _kbhit();
   }

   char GetC(comand cm)
   {
      return windC[cm];
   }

   void OutS(symbol sm)
   {
      std::cout << windS[sm];
   }

   int Arrows()
   {
      char ch[] = "\0\0";
      ch[0] = GetKey();

      if(kbhit())
         ch[1] = GetKey();

      for(int i = UP; i < 4; i++)
      {
         if(Equality_Test_For_String(ch, windA[i])) return i;
      }

      for(int i = BACKSPACE; i <= SPACE; i++)
         if(ch[0] == windC[i]) return i + 5;

      return (int)ELSE;
   }

   static HANDLE _ConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);

   BOOL SetCurrentPos(SHORT x, SHORT y)
   {
      COORD pos = {x, y};
      return ::SetConsoleCursorPosition(_ConsoleOut, pos);
   }

   void ConsoleTitle()
   {
      system("title Memory of Life");
   }
}
#elif defined LINUX

namespace ccg
{
   char *linS[] = {"\342\225\220", "\342\224\217", "\342\224\223", "\342\224\233", "\342\224\227", "\342\224\203", "\342\224\201", "\342\225\213", "\342\224\263", "\342\224\253", "\342\224\273", "\342\224\243", "\342\226\221", "\342\226\222", "\342\226\223", "\342\226\266", "\342\230\272", "\302\244", "\342\216\210", "\342\231\245", "\342\226\262", "\342\226\210", "\xe2\x86\x95"};
   const char linC[] = {'\177', '\12', '\11', '\40'};
   const char *linA[] = {"\33\133\101", "\33\133\104", "\33\133\103", "\33\133\102"};
   void sleep(int time)
   {
      usleep(time);
   }
   int GetKey()
   {
      struct termios oldt,
            newt;
      char ch;
      tcgetattr(STDIN_FILENO, &oldt);
      newt = oldt;
      newt.c_lflag &= ~(ICANON | ECHO);
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
      ch = getchar();
      tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
      return ch;
   }
   void Pause()
{
      std::cout << "Press to continue...";
      GetKey();
      std::cout << '\n';
   }
   void CleanConsol()
   {
      system("clear");
   }
   char GetC(comand cm)
   {
      return linC[cm];
   }

   int kbhit()
   {
      struct termios oldt, newt;
      int ch;
      int oldf;

      tcgetattr(STDIN_FILENO, &oldt);
      newt = oldt;
      newt.c_lflag &= ~(ICANON | ECHO);
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
      oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
      fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

      ch = getchar();

      tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
      fcntl(STDIN_FILENO, F_SETFL, oldf);

      if(ch != EOF)
      {
         ungetc(ch, stdin);
         return 1;
      }

      return 0;
   }

   void OutS(symbol sm)
   {
      std::cout << linS[sm];
   }

   int Arrows()
   {
      char ch[] = "\0\0\0";
      ch[0] = GetKey();



      for(int i = 1; kbhit() && (i < 3); ++i)
         ch[i] = GetKey();


      for(int i = UP; i < 4; i++)
      {
         if(Equality_Test_For_String(ch, linA[i])) return i;
      }

      for(int i = BACKSPACE; i <= SPACE; i++)
         if(ch[0] == linC[i]) return i + 5;

      return (int)ELSE;
   }

   void SetCurrentPos(int x, int y)
   {
      std::cout << "\033[0;0H";

      for(; y; y--)
         std::cout << "\033[1B";

      for(; x; x--)
         std::cout << "\033[1C";

   }
   void ConsoleTitle()
   {
      std::cout << "\033]2;Memory of Life\007";
   }
}
#endif
