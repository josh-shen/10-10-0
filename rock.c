#include <stdio.h>

typedef struct Stone {
    int chance;
    char nodes[3][10];
    int rolls;
} Stone;

void init_stone(Stone *stone){
    stone->chance = 75;
    stone->rolls = 30;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 10; j++){
            stone->nodes[i][j] = '*';
        }
    }
}

void success(Stone *stone, int line, int node){
    stone->nodes[line][node] = 'O';

    if (stone->chance > 25){
        stone->chance -= 10;
    }

    stone->rolls--;
}

void failure(Stone *stone, int line, int node){
    stone->nodes[line][node] = 'X';

    if (stone->chance < 75){
        stone->chance += 10;
    }
    
    stone->rolls--;
}

void show_stone(Stone *stone){
    printf("\n");
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 10; j++){
            printf("%c ", stone->nodes[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char** argv){
    Stone stone;

    init_stone(&stone);

    int line; //engraving option
    int positions[3] = {0, 0, 0}; //save number of taps for each line

    //faceting
    while (stone.rolls <= 30){
        char result;

        printf("current percentage: %d\npick line: ", stone.chance);
        scanf("%d", &line);
        
        if (positions[line] >= 10){
            printf("line maxed\n");
            continue;
        }

        printf("succeed? y/n");
        scanf(" %c", &result);

        if (result == 'y'){
            success(&stone, line, positions[line]);
            positions[line]++;
        }
        else{
            failure(&stone, line, positions[line]);
            positions[line]++;
        }

        show_stone(&stone);
        printf("rolls left: %d\n", stone.rolls);
    }
}