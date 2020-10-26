#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int wynik, wynik2, wynik3, wynik5;
    int pid2, pid3, pid5;
    int desc_zrod;

    if ((pid2 = fork()) == 0)
    {
        execl("./silnia", "silnia", "2", "plik2", NULL);
        perror("Blad uruchmienia silnia(2)");
        exit(1);
    }
    if ((pid3 = fork()) == 0)
    {
        execl("./silnia", "silnia", "3", "plik3", NULL);
        perror("Blad uruchmienia silnia(3)");
        exit(1);
    }
    if ((pid5 = fork()) == 0)
    {
        execl("./silnia", "silnia", "5", "plik5", NULL);
        perror("Blad uruchmienia silnia(5)");
        exit(1);
    }
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);
    waitpid(pid5, NULL, 0);

    desc_zrod = open("plik2", O_RDONLY);
    if (desc_zrod == -1)
    {
        perror("Blad otwarcia plik2");
        exit(1);
    }
    if (read(desc_zrod, &wynik2, sizeof(int)) == -1)
    {
        perror("Blad odczytu plik2");
        exit(1);
    }
    if (close(desc_zrod) == -1)
    {
        perror("Blad zamkniecia pliku2");
        exit(1);
    }
    printf("wynik2=%d\n", wynik2);


    desc_zrod = open("plik3", O_RDONLY);
    if (desc_zrod == -1)
    {
        perror("Blad otwarcia plik3");
        exit(1);
    }
    if (read(desc_zrod, &wynik3, sizeof(int)) == -1)
    {
        perror("Blad odczytu plik3");
        exit(1);
    }
    if (close(desc_zrod) == -1)
    {
        perror("Blad zamkniecia pliku3");
        exit(1);
    }
    printf("wynik3=%d\n", wynik3);


    desc_zrod = open("plik5", O_RDONLY);
    if (desc_zrod == -1)
    {
        perror("Blad otwarcia plik5");
        exit(1);
    }
    if (read(desc_zrod, &wynik5, sizeof(int)) == -1)
    {
        perror("Blad odczytu plik5");
        exit(1);
    }
    if (close(desc_zrod) == -1)
    {
        perror("Blad zamkniecia pliku3");
        exit(1);
    }
    printf("wynik5=%d\n", wynik5);
    wynik = wynik5 / (wynik3 * wynik2);
    printf("wynik=%d\n", wynik);
    return 0;
}