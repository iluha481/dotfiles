#include <stdio.h>
#define AR_SIZE 100

typedef struct {
    int year, month, day;
} date;

typedef struct {
    int id;
    char dept[20];
    char name[20];
    int salary;
    date begin;
    date end;
} person;

int scan_file(const char* filename, person *ar) {
    FILE *f_in = fopen(filename, "r");
    int count = 0;
    while (fscanf(f_in, "%d %s %s %d %d.%d.%d %d.%d.%d",
        &ar[count].id, ar[count].dept,
        ar[count].name, &ar[count].salary,
        &ar[count].begin.year,
        &ar[count].begin.month,
        &ar[count].begin.day,
        &ar[count].end.year,
        &ar[count].end.month,
        &ar[count].end.day) == 10) {
            count++;
    }
    fclose(f_in);
    return count;
}

void write_file(const char* filename, person *ar, int lines_count){
    FILE *f_out = fopen(filename, "w");
    for (int i = 0; i < lines_count; ++i) {
    fprintf(f_out, "%d %s %s %d %d.%d.%d %d.%d.%d\n",
        ar[i].id, ar[i].dept, 
        ar[i].name, ar[i].salary, 
        ar[i].begin.year, ar[i].begin.month, ar[i].begin.day,
        ar[i].end.year, ar[i].end.month, ar[i].end.day);
    }
    fclose(f_out);
}

void add_line(person *ar, person added, int *lines_count) {
    ar[*lines_count] = added;
    *lines_count++;
}

void swap(person *pa, person *pb) {
    person t = *pa;
    *pa = *pb;
    *pb = t;
}

void sort(int (*func)(person, person), person *ar, int lines_count ) {
    for(int i = 0; i < lines_count; i++){
        for(int j = 0; j < lines_count; j++) {
            if(i != j) {
                if(func(ar[i], ar[j])) {
                    swap(&ar[i], &ar[j]);
                }
            }
        }
    }
} 

int lt_id(person a, person b){
    return a.id < b.id;
}






void menu(){
    while (1) {
        printf("\
            1.      \n\
            2.      \n\
            3.      \n\
            4.      \n\
            5.      \n\
            6.      \n\
            7.      \n\
            8.      \n\
            9.      \n\
            0.      \n\
            \
            ");

        int input;
        scanf("%d", &input);

        switch (input)
        {
        case 1:
            
            break;
        
        case 0:
            return 0;
        default:
            break;
        }


    }

}




int main() {
    person ar[AR_SIZE];


    return 0;
}





void asdas() {
    char str[5] = "1234";
    int sum = 0;
    int len = strlen(str);
    for(int i = len - 1; i >=0; i--){
        sum += (str[i] - '0') * pow(10, len - i - 1);
    }
    printf("%d\n", sum);
}