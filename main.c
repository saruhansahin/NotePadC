#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>



void menu(void){
    int a=0;
    char note[100];
    while(1){
        printf("---------\n1-Add\n2-List\n3-Exit\n4-Delete\n---------\nChoice:");
        scanf("%d",&a);
        getchar();
        if(a==1){
            printf("Add Your Note:");
            scanf(" %99[^\n]", note);
            FILE *f = fopen("notes.dat", "ab");
            if(f == NULL){
                printf("File cannot be opened!\n");
                return;
            }
            fwrite(note, sizeof(char), 100, f);
            fclose(f);
            printf("Saved: %s\n", note);
        } else if (a==2){
            printf("---------List---------\n");
            int i=1;
            FILE *f = fopen("notes.dat", "rb");
            if(f == NULL){
                printf("File does not exist!\n");
                return;
            }
            char temp[100];
            while(fread(temp, sizeof(char), 100, f)){
                temp[99] = '\0';
                printf("%d- %s\n", i, temp);
                i++;
            }
            fclose(f);
        } else if(a==3){
            printf("Notes are closing.");
            break;
        } else if(a==4){
            char temp[100];
            int i = 1;
            printf("--------Delete--------\n");
            int del;
            printf("Enter note number to delete: ");
            scanf("%d", &del);
            FILE *f = fopen("notes.dat", "rb");
            FILE *tempFile = fopen("temp.dat", "wb");
            if(f == NULL || tempFile == NULL){
                printf("File Error!\n");
                return;
            }
            while(fread(temp, sizeof(char), 100, f)){
                if(i != del){
                    fwrite(temp, sizeof(char), 100, tempFile);
                }
                i++;
            }
            fclose(f);
            fclose(tempFile);
            remove("notes.dat");
            rename("temp.dat", "notes.dat");
            printf("Note %d deleted!\n", del);
        }else{
            printf("Enter a valid choise!");
        }
    }
}
int main(void) {
    menu();
    return EXIT_SUCCESS;
}
