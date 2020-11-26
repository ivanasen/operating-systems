// Напишете програма, която създава файла fff 
// и го отваря три пъти:
// • само за четене през fd1
// • само за писане през fd2
// • за четене и писане през fd3
// След това:
// А)
// • през fd2 записва “Hello world” в него
// • през fd3 прочита 6 байта и изписва прочетеното на $
// стандартния изход
// • през fd1 прочита 5 байта  и изписва прочетеното на
// стандартния изход
// • през fd3 записва “chil”  в него $
// • през fd2 записва “!!!”  в него
// • през fd1  прочита 9 байта  и изписва прочетеното 
// на стандартния изход
//              Б)
// • през fd3 записва “Hello” в него
// • през fd2 записва „worlds” в него
// • през fd1 прочита 6 байта  и изписва прочетеното 
// на стандартния изход $
// • затваря  fd2
// • през fd3 записва “oops”  в него
// • през fd1  прочита 6 байта  и изписва прочетеното на 
// стандартния изход
// Какво ще се изпише на стандартния изход и какво
// ще бъде съдържанието на файла
// във всеки от горните  случаи?

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const* argv[]) {
    char* name = "fff";
    int fd1 = open(name, O_RDONLY | O_CREAT);
    int fd2 = open(name, O_WRONLY);
    int fd3 = open(name, O_RDWR);

    write(fd2, "Hello world", 11);

    char buff[100];
    memset(buff, 0, 100);

    int count = read(fd3, buff, 6);
    write(1, buff, count);
    puts("");  // debug purposes, new line

    memset(buff, 0, 100);
    count = read(fd1, buff, 5);
    write(1, buff, count);
    puts("");

    write(fd3, "chill", 5);

    write(fd2, "!!!", 3);

    memset(buff, 0, 100);
    count = read(fd1, buff, 9);
    write(1, buff, count);

    //.......

    return 0;
}