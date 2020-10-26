#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int wynik, wynik2, wynik3, wynik5;
    int desc_zrod;

    if (fork() == 0)
    {
        execl("./silnia", "silnia", "2", "plik2", NULL);
        perror("Blad uruchmienia silnia(2)");
        exit(1);
    }
    wait(NULL);

    if (fork() == 0)
    {
        execl("./silnia", "silnia", "3", "plik3", NULL);
        perror("Blad uruchomienia silnia(3)");
        exit(1);
    }
    wait(NULL);

    if (fork() == 0)
    {
        execl("./silnia", "silnia", "5", "plik5", NULL);
        perror("Blad uruchmienia silnia(5)");
        exit(1);
    }
    wait(NULL);

    // Plik 2
    if (close(0) == -1)
    {
        perror("Blad zamkniecia stdi");
        exit(1);
    }
    if (open("plik2", O_RDONLY) == -1)
    {
        perror("Blad otwarcia plik2");
        exit(1);
    }
    scanf("%d", &wynik2);

    // Plik 3
    if (close(0) == -1)
    {
        perror("Blad zamkniecia stdi");
        exit(1);
    }
    if (open("plik3", O_RDONLY) == -1)
    {
        perror("Blad otwarcia plik2");
        exit(1);
    }
    scanf("%d", &wynik3);

    // Plik 5
    if (close(0) == -1)
    {
        perror("Blad zamkniecia stdi");
        exit(1);
    }
    if (open("plik5", O_RDONLY) == -1)
    {
        perror("Blad otwarcia plik2");
        exit(1);
    }
    scanf("%d\n", &wynik5);

    wynik = wynik5 / (wynik3 * wynik2);
    printf("Wynik = %d\n", wynik);
    exit(0);
}