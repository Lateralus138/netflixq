#include "functions.h"
bool IsOwnWindow()
{
  HWND hwndConsole = GetConsoleWindow();
  DWORD dwProcessId;
  GetWindowThreadProcessId(hwndConsole, &dwProcessId);
  return (GetCurrentProcessId() == dwProcessId);
}
BOOL WINAPI SignalControlCHandler(DWORD ctrlEvent)
{
  switch (ctrlEvent)
  {
    case CTRL_C_EVENT: exit(127);
    default: exit(0);
  }
}

std::string GetLastErrorAsString()
{
  DWORD errorMessageID = ::GetLastError();
  if (errorMessageID == 0)
  {
    return std::string();
  }
  LPSTR messageBuffer = nullptr;
  size_t size =
    FormatMessageA
    (
      FORMAT_MESSAGE_ALLOCATE_BUFFER |
      FORMAT_MESSAGE_FROM_SYSTEM |
      FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL, errorMessageID,
      MAKELANGID
      (
        LANG_NEUTRAL,
        SUBLANG_DEFAULT
      ),
      (LPSTR)&messageBuffer, 0, NULL
    );
  std::string message(messageBuffer, size);
  LocalFree(messageBuffer);
  return message;
}