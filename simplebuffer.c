#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAPACITY 100
//src https://towardsdatascience.com/circular-queue-or-ring-buffer-92c7b0193326
unsigned char buffer[CAPACITY];
unsigned int head = 0;
unsigned int tail = -1;
unsigned int numberOfItems = 0;

void add(char buffer[CAPACITY], char item){
    if(numberOfItems == CAPACITY){ //full
        printf("queue je plna\n");
    }else{
        tail = (tail + 1) % CAPACITY;
        buffer[tail] = item;
        numberOfItems++;
    }
}

char dequeue(char buffer[CAPACITY]){
    printf("zavolane, %d\n", numberOfItems);
    if(numberOfItems == 0){
        printf("fronta prazdnay\n");
    }else{
        char item = buffer[head];
        head = (head + 1) % CAPACITY;
        numberOfItems--;
        return item;
    }
}
int isEmpty(){
    return numberOfItems == 0;
}
int main(){
    add(buffer, 'a');
    add(buffer, 'b');
    add(buffer, 'c');

    printf("%c\n", dequeue(buffer));
    printf("%c\n", dequeue(buffer));
    printf("%c\n", dequeue(buffer));
    // while(!isEmpty()){
    //     char result = dequeue(buffer);
    //     printf("character is %c\n", result);
    // }
}
