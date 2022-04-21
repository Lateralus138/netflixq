/////////////////////////////////////////////////
// Netflix Query                               //
// © 2022 Ian Pride - New Pride Software/      //
// Services                                    //
/////////////////////////////////////////////////
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <csignal>
#include <vector>
#include <regex>
#include <filesystem>
void signal_handler_ctrl_c(int signum)
{
  std::cerr << "\nError: [" << signum << "]\n";
  std::exit(signum);
}
int main(int argc, char *argv[])
{
  std::cout << "\x1b]0;Netflix Query\007" << std::flush;
  signal(SIGINT, signal_handler_ctrl_c);
  bool hasQuery = false;
  std::string
    process_path_string = "/usr/bin/open",
    process_path_args = " https://www.netflix.com/",
    query_string;
  if (!isatty(fileno(stdin)))
  {
    std::string input;
    while(std::getline(std::cin, input))
    {
      if (!query_string.empty())
      {
        query_string.push_back(' ');
      }
      query_string.append(input);
    }
  }
  const std::regex
    RGXHELP("^-([hH]|-[hH][eE][lL][pP])$"),
    RGXQUER("^-([qQ]|-[qQ][uU][eE][rR][yY])$"),
    RGXBROW("^-([bB]|-[bB][rR][oO][wW][sS][eE][rR])$");
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
      if (std::regex_match(thisArg, RGXHELP))
      {
        std::cout <<
          '\n' +
          BOX[0] + box_line + BOX[2] + '\n' +
          BOX[3] + "                 Netflix Query                  " + BOX[3] + '\n' +
          BOX[6] + box_line + BOX[7] + '\n' +
          BOX[3] + " Load Netflix in a browser with search options. " + BOX[3] + '\n' +
          BOX[6] + box_line + BOX[7] + '\n' +
          BOX[3] + " netflixq [-H] [-B BROWERPATH] [-Q QUERY]       " + BOX[3] + '\n' +
          BOX[6] + box_line + BOX[7] + '\n' +
          BOX[3] + " -h,--HELP       This help screen.              " + BOX[3] + '\n' +
          BOX[3] + " -b,--browser    Path to the browser. Defaults  " + BOX[3] + '\n' +
          BOX[3] + "                 to 'open' which opens in   " + BOX[3] + '\n' +
          BOX[3] + "                 your default web browser.      " + BOX[3] + '\n' +
          BOX[3] + " -q,--query      Force append to query. Any     " + BOX[3] + '\n' +
          BOX[3] + "                 arguments passed without a     " + BOX[3] + '\n' +
          BOX[3] + "                 switch [-q etc.] are query     " + BOX[3] + '\n' +
          BOX[3] + "                 arguments, but if you need to  " + BOX[3] + '\n' +
          BOX[3] + "                 force additional query strings " + BOX[3] + '\n' +
          BOX[3] + "                 then you can use this switch.  " + BOX[3] + '\n' +
          BOX[3] + "                 NO query by default.           " + BOX[3] + '\n' +
          BOX[6] + box_line + BOX[7] + '\n' +
          BOX[3] + " " + CR + " 2022 Ian Pride - New Pride Software/Services " + BOX[3] + '\n' +
          BOX[4] + box_line + BOX[5] + "\n\n";
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
            return 2;
          }
          skip = true;
          process_path_string = nextArg;
          continue;
        }
        else
        {
          std::cerr << "No argument provided for '" << thisArg << "'.\n";
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
  char * argsCmdA[] =
  {
    const_cast<char*>(process_path_string.c_str()),
    const_cast<char*>(process_path_args.c_str()),
    NULL
  };
  int sysResult;
  pid_t pid;
  pid = fork();
  if (pid >= 0)
  {
    if (pid == 0)
    {
      return execvp(argsCmdA[0], argsCmdA);
    }
    else
    {
      waitpid(pid,&sysResult, 0);
      if (WEXITSTATUS(sysResult))
      {
        std::string message = "Error: [";
        message.append(std::to_string(WEXITSTATUS(sysResult)));
        message.append("] in command: [");
        message.append(process_path_string);
        message.push_back(' ');
        message.append(process_path_args);
        message.append("]\n");
        std::cerr << message;
      }
      return WEXITSTATUS(sysResult);
    }
  }
  else
  {
    std::cerr << "Program failed to fork.\n";
    return 7;
  }
}
