#include<stdlib.h>
#include<stdio.h>

void function(int &first, int second, int *third);
void procedure(int *&first, int *second, int *third);
int main(int argc, char **argv)
{
int *first = (int *)malloc(3 * sizeof(int));
first[0] = 4;
first[1] = 3;
first[2] = 6;
int *second = &first[0];
int third = 2;
int fourth = first[2];
int *fifth = &first[1];
function(*second, third, &first[2]);
printf("%d, %d, %d\n", *second, third, fourth);
function(*second, *second, second);
printf("%d, %d, %d, %d\n", *second, first[0], first[1], first[2]);
procedure(first, second, fifth);
printf("%d, %d, %d\n", third, fourth, *fifth);
printf("%d, %d, %d\n", first[0], first[1], first[2]);
free(first);
return 0;
}
void function(int &first, int second, int *third)
{
first = second;
second += 2;
*third += first;
second += first;
first = *third + second;
}
void procedure(int *&first, int *second, int *third)
{
*second = first[2];
(*(first + 1))++;
first[0] = *second + first[1];
first++;
}
