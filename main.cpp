#include <fifteen_application.h>

int main()
{
    fifteen::fifteen_application application;
    while (application.run());
    return application.exit_code();
}