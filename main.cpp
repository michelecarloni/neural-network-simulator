#include "header/shell.h"
#include <iostream>
#include <vector>
#include <string>



int main() {

    Shell shell;
    shell.startContext();

    while(1)
    {
        shell.readCommand();
    }

}