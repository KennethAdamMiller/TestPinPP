#include <stdio.h>
#include <inttypes.h>

int main(int argc, char **argv, char **envp)
{
    printf("&argc = 0x%.8" PRIXPTR "\n", (uintptr_t)&argc);
    printf("&argv = 0x%.8" PRIXPTR "\n", (uintptr_t)&argv);
    printf("&envp = 0x%.8" PRIXPTR "\n", (uintptr_t)&envp);
    while (*argv != 0)
        printf("*argv = 0x%.8" PRIXPTR "\n", (uintptr_t)*argv++);
    while (*envp != 0)
        printf("*envp = 0x%.8" PRIXPTR "\n", (uintptr_t)*envp++);
    return 0;
}
