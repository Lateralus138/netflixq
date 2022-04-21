//////////////////////////////////////////////////
// Netlflix Query                               //
// © 2022 Ian Pride - New Pride Software/       //
// Services                                     //
//////////////////////////////////////////////////
#include "Functions.h"
#include <Windows.h>
#include <iostream>
#include <filesystem>
#include <regex>
#include <vector>

int main(int argc, char * argv [])
{
  SetConsoleCtrlHandler(SignalControlCHandler, true);
  DWORD
    dwProcessIdMain,
    dwProcessIdThis = GetCurrentProcessId();
  HWND conHwnd = GetConsoleWindow();
  GetWindowThreadProcessId(conHwnd, &dwProcessIdMain);
  const bool isOwnConWin = (dwProcessIdThis == dwProcessIdMain);
  const std::string
    TITLE = "Netflix Query",
    TITLEESC = "\x1b]0;" + TITLE + "\007";
  bool
    isOwnWindow = IsOwnWindow();
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  SetConsoleTitleA(TITLE.c_str());
  if (isOwnConWin)
  {
    SetWindowTextA(conHwnd, TITLE.c_str());
  }
  std::string
    process_path_string = "C:\\Windows\\System32\\rundll32.exe",
    process_path_args = " https://www.netflix.com/",
    query_string;
  bool
    skipPrompt = false,
    hasQuery = false;
  const std::regex
    RGXHELP("^/([hH]|[hH][eE][lL][pP]|[\?])$"),
    RGXSKIP("^/([sS]|[sS][kK][iI][pP])$"),
    RGXQUER("^/([qQ]|[qQ][uU][eE][rR][yY])$"),
    RGXBROW("^/([bB]|[bB][rR][oO][wW][sS][eE][rR])$");
  auto wait_continue =
    [isOwnWindow](bool skipPrompt)
  {
    if (isOwnWindow && (!skipPrompt))
    {
      std::cout << "Press [Enter] to continue... ";
      std::cin.get();
      std::cout << '\n';
    }
  };
  const std::vector <std::string> BOX =
  {
    u8"\u250C", u8"\u2500", u8"\u2510", u8"\u2502",
    u8"\u2514", u8"\u2518", u8"\u251C", u8"\u2524"
  };
  const std::string CR = u8"\u00A9";
  std::string box_line;
  for (auto i = 0; i < 48; ++i)
  {
    box_line += BOX[1];
  }
  if (argc > 1)
  {
    std::string
      thisArg;
    bool skip = false;
    for (auto i = 1; i < argc; i++)
    {
      thisArg = argv[i];
      if (skip)
      {
        skip = false;
        continue;
      }
      if (std::regex_match(thisArg, RGXSKIP))
      {
        skipPrompt = true;
        continue;
      }
      if (std::regex_match(thisArg, RGXHELP))
      {
        std::cout <<
          '\n' +
          BOX[0] + box_line + BOX[2] + '\n' +
          BOX[3] + "                 Netflix Query                  " + BOX[3] + '\n' +
          BOX[6] + box_line + BOX[7] + '\n' +
          BOX[3] + " Load Netflix in a browser with search options. " + BOX[3] + '\n' +
          BOX[6] + box_line + BOX[7] + '\n' +
          BOX[3] + " netflixq [/H] [/B BROWERPATH] [/Q QUERY] [/S]  " + BOX[3] + '\n' +
          BOX[6] + box_line + BOX[7] + '\n' +
          BOX[3] + " /h,/HELP,/?     This help screen.              " + BOX[3] + '\n' +
          BOX[3] + " /b,/browser     Path to the browser. Defaults  " + BOX[3] + '\n' +
          BOX[3] + "                 to rundll32.exe url,OpenURL    " + BOX[3] + '\n' +
          BOX[3] + "                 which opens in your default    " + BOX[3] + '\n' +
          BOX[3] + "                 web browser.                   " + BOX[3] + '\n' +
          BOX[3] + " /q,/query       Force append to query. Any     " + BOX[3] + '\n' +
          BOX[3] + "                 arguments passed without a     " + BOX[3] + '\n' +
          BOX[3] + "                 switch [/q etc.] are query     " + BOX[3] + '\n' +
          BOX[3] + "                 arguments, but if you need to  " + BOX[3] + '\n' +
          BOX[3] + "                 force additional query strings " + BOX[3] + '\n' +
          BOX[3] + "                 then you can use this switch.  " + BOX[3] + '\n' +
          BOX[3] + "                 NO query by default.           " + BOX[3] + '\n' +
          BOX[3] + " /s,/skip        Skip any prompts.              " + BOX[3] + '\n' +
          BOX[6] + box_line + BOX[7] + '\n' +
          BOX[3] + " " + CR + " 2022 Ian Pride - New Pride Software/Services " + BOX[3] + '\n' +
          BOX[4] + box_line + BOX[5] + "\n\n";
        wait_continue(skipPrompt);
        return 0;
      }
      if (std::regex_match(thisArg, RGXBROW))
      {
        if ((i + 1) < argc)
        {
          std::string nextArg = argv[i + 1];
          if (nextArg.empty())
          {
            std::cerr << "Argument provided for '" << thisArg << "' is empty.\n";
            wait_continue(skipPrompt);
            return 2;
          }
          skip = true;
          process_path_string = nextArg;
          continue;
        }
        else
        {
          std::cerr << "No argument provided for '" << thisArg << "'.\n";
          wait_continue(skipPrompt);
          return 1;
        }
      }
      if (std::regex_match(thisArg, RGXQUER))
      {
        if ((i + 1) < argc)
        {
          std::string nextArg = argv[i + 1];
          if (nextArg.empty())
          {
            std::cerr << "Argument provided for '" << thisArg << "' is empty.\n";
            wait_continue(skipPrompt);
            return 4;
          }
          if (!query_string.empty())
          {
            query_string.push_back(' ');
          }
          query_string.append(nextArg);
          skip = true;
          continue;
        }
        else
        {
          std::cerr << "No argument provided for '" << thisArg << "'.\n";
          wait_continue(skipPrompt);
          return 3;
        }
      }
      if (!thisArg.empty())
      {
        if (!query_string.empty())
        {
          query_string.push_back(' ');
        }
        query_string.append(thisArg);
      }
    }
  }
  std::filesystem::path process_path (process_path_string);
  if (!std::filesystem::exists(process_path))
  {
    std::cerr << process_path << " does not exist.\n";
    return 5;
  }
  if (!std::filesystem::is_regular_file(process_path))
  {
    std::cerr << process_path << " is not a valid file.\n";
    return 6;
  }
  std::cout <<
    '\n' +
    BOX[0] + box_line + BOX[2] + '\n' +
    BOX[3] + "                 Netflix Query                  " + BOX[3] + '\n' +
    BOX[6] + box_line + BOX[7] + '\n' +
    BOX[3] + " Load Netflix in a browser with search options. " + BOX[3] + '\n' +
    BOX[6] + box_line + BOX[7] + '\n' +
    BOX[3] + " " + CR + " 2022 Ian Pride - New Pride Software/Services " + BOX[3] + '\n' +
    BOX[4] + box_line + BOX[5] + "\n\n";
  hasQuery = !query_string.empty();
  if (hasQuery)
  {
    process_path_args.append("search?q=");
    std::replace(query_string.begin(), query_string.end(), ' ', '+');
    process_path_args.append(query_string);
  }
  if (process_path_string == "C:\\Windows\\System32\\rundll32.exe")
  {
    process_path_args.insert(0, " url,OpenURL ");
  }
  STARTUPINFOA sinfo;
  PROCESS_INFORMATION pinfo;
  ZeroMemory(&sinfo, sizeof(sinfo));
  sinfo.cb = sizeof(sinfo);
  ZeroMemory(&pinfo, sizeof(pinfo));
  auto procResult = CreateProcessA
  (
    (LPCSTR)const_cast<char*>(process_path_string.c_str()),
    (LPSTR)const_cast<char*>(process_path_args.c_str()),
    NULL, NULL, FALSE, CREATE_NEW_CONSOLE,
    NULL, NULL, &sinfo, &pinfo
  );
  CloseHandle(pinfo.hProcess);
  CloseHandle(pinfo.hThread);
  if (!procResult)
  {
    int err = GetLastError();
    std::cerr
      << "Process did not return successfully.\n["
      << err << "]: " << GetLastErrorAsString() << '\n';
    wait_continue(skipPrompt);
    return err;
  }
  wait_continue(skipPrompt);
}
