#ifndef HIERARCHICALSTRUCTUREOFDATASTORAGE_CONSOLECP_H
#define HIERARCHICALSTRUCTUREOFDATASTORAGE_CONSOLECP_H


#include <windows.h>

class ConsoleCP
{
    int oldin;
    int oldout;

public:
    ConsoleCP(int cp)
    {
        oldin = GetConsoleCP();
        oldout = GetConsoleOutputCP();
        SetConsoleCP(cp);
        SetConsoleOutputCP(cp);
    }

    // поскольку мы изменили свойства внешнего объекта — консоли, нам нужно
    // вернуть всё как было (если программа вылетит, пользователю не повезло)
    ~ConsoleCP()
    {
        SetConsoleCP(oldin);
        SetConsoleOutputCP(oldout);
    }
};

#endif //HIERARCHICALSTRUCTUREOFDATASTORAGE_CONSOLECP_H
