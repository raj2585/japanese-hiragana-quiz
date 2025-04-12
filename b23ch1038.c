#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define q 48
#define op 4

typedef struct{
    char name[100];
    float accuracy;
}player;

void show_instructions(){
    printf("\nWelcome to the Japanese Hiragana Quiz!\n");
    printf("You will be shown a Hiragana character and asked to choose the correct English translation.\n");
    printf("Select the number corresponding to the correct option.\n");
    printf("Let's begin!\n\n");
}

void show_question(char hiragana[5], char options[op][20],int i, int n){
    printf("\nQUESTION %d / %d:\n", i+1, n);
    printf("What is the English translation of the Hiragana character '%s' ?\n\n", hiragana);
    printf("OPTIONS:\n");

    for (int i = 0; i < op; i++){
        printf(" %d. %s\n", i + 1, options[i]);
    }
}

int take_answer_input(){
    int answer;
    
    while (1) {
        printf("\nEnter the number corresponding to your answer: ");
        
        if (scanf("%d", &answer) != 1 || answer < 1 || answer > 4) {
            while (getchar() != '\n');
            
            printf("Invalid input. Please enter a number between 1 and 4.\n");
        } else {
            break;
        }
    }
    return answer;
}

int check_answer(int a, int b){
    int c = b + 1;
    if(a == c){
        return 1;
    }else{
        return 0;
    }
}

void give_feedback(int a, int b){
    int c = b + 1;
    if(a == c){
        printf("Correct Answer!\n\n");
    }else{
        printf("Wrong answer!!\n");
        printf("The correct answer is '%d'\n\n", c);
    }
}

void show_result(int s, int n, clock_t start){
    clock_t end = clock();
    double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Total Time taken: %.2f seconds\n", time_taken);
    printf("Average Time per question: %.2f seconds\n\n", time_taken / n);
    printf("Final Score: %d / %d\n", s, n);
}

//file handling to maintain a leaderboard
void show_leaderboard(){
    FILE *f = fopen("leaderfile.txt", "r");
    if (f == NULL) {
        printf("No leaderboard data\n");
        return;
    }
    player p;
    printf("\nLeaderboard:\n\n");
    while (fread(&p, sizeof(player), 1, f)) {
        printf("Name: %s, Accuracy: %.2f %%\n", p.name, p.accuracy);
    }
    fclose(f);
}

void addtoleaderboard(char name[], float accuracy){
    FILE *f = fopen("leaderfile.txt", "a");
    if (f == NULL) {
        return;
    }
    player p;
    strcpy(p.name, name);
    p.accuracy = accuracy;
    fwrite(&p, sizeof(player), 1, f);
    fclose(f);
}

void clearleaderboard(){
    FILE *f = fopen("leaderfile.txt", "w");
    fclose(f);
    printf("Leaderboard cleared.\n");
}

int main(){
    char hiragana[q][5] = {"あ", "い", "う", "え", "お", "か", "き", "く", "け", "こ", "さ", "し", "す", "せ", "そ", "た", "ち", "つ", "て", "と", "な", "に", "ぬ", "ね", "の", "は", "ひ", "ふ", "へ", "ほ", "ま", "み", "む", "め", "も", "や", "ゆ", "よ", "ら", "り", "る", "れ", "ろ", "わ", "ゐ", "ゑ", "を", "ん"};
    char options[q][op][20] = {
        {"me", "a", "ra", "i"}, {"i", "shi", "a", "ne"}, {"u", "mo", "chi", "wa"}, {"ri", "ne", "e", "a"}, {"o", "hi", "ma", "ke"}, {"ko", "ku", "ki", "ka"},
        {"ke", "ko", "ki", "ka"}, {"ka", "ke", "ku", "ki"}, {"ku", "ki", "ka", "ke"}, {"ki", "ke", "ka", "ko"}, {"se", "sa", "shi", "su"}, {"shi", "su", "se", "sa"},
        {"su", "se", "shi", "sa"}, {"sa", "su", "shi", "se"}, {"so", "shi", "sa", "su"}, {"to", "chi", "te", "ta"}, {"te", "ta", "chi", "to"}, {"tsu", "te", "to", "ta"},
        {"ta", "chi", "to", "te"}, {"to", "chi", "ta", "te"}, {"no", "ne", "ni", "na"}, {"ni", "na", "no", "ne"}, {"nu", "na", "ni", "no"}, {"ni", "no", "na", "ne"},
        {"na", "no", "ne", "ni"}, {"hi", "fu", "he", "ha"}, {"he", "ha", "hi", "fu"}, {"ha", "fu", "te", "he"}, {"he", "ne", "ha", "hi"}, {"he", "ho", "fu", "hi"},
        {"ha", "ho", "ma", "mi"}, {"mi", "ma", "mu", "me"}, {"o", "ne", "mu", "fu"}, {"ma", "mu", "mi", "me"}, {"ma", "mo", "ho", "ha"}, {"yu", "yo", "wa", "ya"},
        {"yu", "ya", "wa", "yo"}, {"wa", "yo", "yu", "ya"}, {"ri", "ru", "ra", "re"}, {"ru", "re", "ra", "ri"}, {"ru", "mo", "mu", "ra"}, {"a", "me", "nu", "re"},
        {"ru", "ro", "re", "ra"}, {"wo", "we", "wi", "wa"}, {"wi", "wa", "wo", "we"}, {"ro", "no", "we", "ri"}, {"ne", "ri", "wo", "o"}, {"me", "n", "ri", "re"}   
    };
    int correct_answers[q] = { 1, 0, 0, 2, 0, 3, 2, 2, 3, 3, 1, 0, 0, 3, 0, 3, 2, 0, 3, 0, 3, 0, 0, 3, 1, 3, 2, 1, 0, 1, 2, 0, 2, 3, 1, 3, 0, 1, 2, 3, 0, 3, 1, 3, 0, 2, 3, 1};

    show_instructions();

    int n;
    printf("Enter the number of questions you want to attempt: \n");
    scanf("%d", &n);

    if (n > q){
        printf("Number of questions exceeds max limit, setting the number of questions to 48. \n");
        n = q;
    }
    
    int score = 0;
    bool asked[q] = { false }; //to make sure that same question is not repeayed
    srand(time(NULL));
    clock_t start = clock();

    for (int i = 0; i < n; i++) {
        int r;
        do{
            r = rand() % q; //to genarate a random index between 0 and 47
        }while(asked[r]);
        asked[r] = true;
        
        show_question(hiragana[r], options[r], i, n);
        int user_answer = take_answer_input();
        switch (user_answer) {
            case 1:
            case 2:
            case 3:
            case 4:
                score += check_answer(user_answer, correct_answers[r]);
                give_feedback(user_answer, correct_answers[r]);
                break;
            default:printf("\nPlease enter a number between 1 and 4.\n");
                    i--; //to repeat the same question
        }
    }

    show_result(score, n, start);
    float accuracy = ((float)score / n) * 100.00;
    printf("Your Accuracy: %.2f %%\n", accuracy);

    char name[100];
    printf("\nEnter your name: ");
    scanf("%s", &name);
    
    addtoleaderboard(name, accuracy);

    show_leaderboard();

    return 0;
}
