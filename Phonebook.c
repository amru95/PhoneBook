/*
Phonebook project
Programming I
Fall 2014
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
typedef struct{
    char first_name[16],last_name[16],city[16];
    char phone_number[16],street_address[32];
}USER;
int Num_Entries=0,len_Entries=0;
USER *Entries;
int main(){
    system("COLOR 0F");
    Phone();
    return 0;
}
void Phone(){
    char response;
    while(response != '9'){
        system("CLS");
        printf( "\t    _____  _                      ____              _            \n"
                "\t   |  __ \\| |                    |  _ \\            | |         \n"
                "\t   | |__| | |__   ___  _ __   ___| |_| | ___   ___ | | __        \n"
                "\t   |  ___/| '_ \\ / _ \\| '_ \\ / _ \\  _ < / _ \\ / _ \\| |/ /  \n"
                "\t   | |    | | | | |_| | | | |  __/ |_| | |_| | |_| |   <         \n"
                "\t   |_|    |_| |_|\\___/|_| |_|\\___|____/ \\___/ \\___/|_|\\_\\  \n"
                "\t\t                           _                   \n"
                "\t\t   |\\/|  /\\  | |\\ |  |\\/| |_  |\\ | | |    \n"
                "\t\t   |  | /--\\ | | \\|  |  | |_  | \\| |_|      \n\n"
                "\t   (1) Add new contact.    |\t(2) Delete contact.\n"
                "\t   (3) Modify contact.     |\t(4) Search contact.\n"
                "\t   (5) Print contacts.     |\t(6) Load an existing phone book.\n"
                "\t   (7) Save.\t\t   |\t(8) Delete All.\n"
                "\t   (9) Exit.\n"
                "\t   >>>> " );
        response = getch();
        system("CLS");
        switch(response){
            case '1': add(NULL); break;
            case '2': del_Entrys(); break;
            case '3': Modify(); break;
            case '4': Search(); break;
            case '5': printall(); break;
            case '6': Load(); break;
            case '7': Save(); break;
            case '8': deleteAll(); break;
            case '9': exit(0); break;
            default : printf("\nWrong Command!\n"); system("PAUSE");
        }
    }
}
void add(USER *u){
    Num_Entries++;
    if (u==NULL){
        u = (USER*)malloc(sizeof(USER));
        set_User(u);
    }
    Dynamic_Allocation();
    int index = place_finder(*u);
    Shifter_Right(index,Num_Entries);
    Entries[index]=*u;
    system("PAUSE");
}
void del_Entrys(){
    fflush(stdin);
    char last_name[16],first_name[16];
    printf("Enter Last Name:\n");
    gets(last_name);
    printf("Enter First Name:\n");
    gets(first_name);
    int index = Finder(last_name, first_name);
    if (index == -1){
        printf("CONTACT NOT FOUND !!!\n");
        system("PAUSE");
        return;
    }else{
        int i= index;
        int Choose;
        while(!strcmp(Entries[index].last_name,last_name) && !strcmp(Entries[index].first_name,first_name)&& index< Num_Entries){
            printf("Contact #%d\n",index+1);
            print_user(Entries[index]);
            index++;
        }
        printf("Which contact do you want to delete? \nIf you don't want to delete enter '0'.\n");
        scanf("%d",&Choose);
        Choose-=1;
        if(Choose==-1) return;
        while(Choose< 0  || Choose > index-1 ||  Choose < i){
            printf("Wrong Input:\n");
            fflush(stdin);
            scanf("%d",&Choose);
            fflush(stdin);
            Choose-=1;
            if(Choose==-1) return;
        }
        Shifter_left(Choose,Num_Entries);
        Num_Entries--;
        printf("\nContact deleted.\n");
        system("PAUSE");
    }
}
void deleteAll(){
    Num_Entries=0,len_Entries=0;
    Entries = NULL;
    printf("All Contacts deleted.\n");
    system("PAUSE");
}
void Search(){
    fflush(stdin);
    char last_name[16];
    printf("Enter last name:\n");
    gets(last_name);
    int i=Finder(last_name,NULL);
    if (i== -1){printf("No Contact with last name: %s\n",last_name); system("PAUSE"); return;}
    while(!strcmp(Entries[i].last_name,last_name) && i < Num_Entries){
        printf("Contact #%d\n",i+1);
        print_user(Entries[i]);
        i++;
    }
    system("PAUSE");
}
void Modify(){
    fflush(stdin);
    char last_name[16],first_name[16];
    printf("Enter Last Name:\n");
    gets(last_name);
    printf("Enter First Name:\n");
    gets(first_name);
    int index = Finder(last_name,first_name);
    if (index==-1){
        printf("CONTACT NOT FOUND !!!\n");
        system("PAUSE");
        return;
    }else{
        int i= index;
        int Choose;
        while(!strcmp(Entries[index].last_name,last_name) && !strcmp(Entries[index].first_name,first_name)&& index<Num_Entries){
            printf("Contact #%d\n",index+1);
            print_user(Entries[index]);
            index++;
        }
        printf("Which contact do you want to Modify? \nIf you don't want to modify enter '0'.\n");
        scanf("%d",&Choose);
        Choose-=1;
        if(Choose==-1) return;
        while(Choose< 0  || Choose > index-1 ||  Choose < i){
            printf("Wrong Input:\n");
            fflush(stdin);
            scanf("%d",&Choose);
            fflush(stdin);
            Choose-=1;
            if(Choose==-1) return;
        }
        USER m;
        set_User(&m);
        Shifter_left(Choose,Num_Entries);
        Num_Entries--;
        add(&m);
    }
}
void Shifter_Right(int index,int num_element){
    int i;
    if (index < num_element-1)
        for (i = 1; i < num_element-index; i++ ){
            Entries[num_element-i] = Entries[num_element-1-i];}
}
void Shifter_left(int index,int num_element){
    int i;
    for (i = index; i <= num_element-2; i++ ){
           Entries[i] = Entries[i+1];}
}
void set_User(USER *user){
    fflush(stdin);
    printf("ENTER FIRST NAME:\n");
    gets(user->first_name);
    validString(user->first_name);
    printf("ENTER LAST NAME:\n");
    gets(user->last_name);
    validString(user->last_name);
    printf("ENTER PHONE NUMBER:\n");
    gets(user->phone_number);
    ValidNum(user->phone_number);
    printf("ENTER STREET ADDRESS:\n");
    gets(user->street_address);
    validString(user->street_address);
    printf("ENTER CITY:\n");
    gets((user->city));
    validString(user->city);
}
void Dynamic_Allocation(){
    if (Num_Entries == 1){
        Entries = (USER*) malloc(2*sizeof(USER));
        len_Entries = 2;
    }else if (Num_Entries >= len_Entries - 2){
        USER * E = malloc(2*(len_Entries)*sizeof(USER));
        if (E!= NULL){
            int i;
            for (i=0;i<Num_Entries;i++){
                E[i]=Entries[i];
            }
            free(Entries);
            Entries = E;
            len_Entries=(len_Entries)*2;
        }else {
            printf("MEMORY ERROR!!!");
            Num_Entries--;
            exit(-1);
        }
    }
}
int Finder(char* last_name, char* first_name){
    int i;
    if(Num_Entries <= 0) return -1;
    if(first_name == NULL){
        for(i=0;i<Num_Entries;i++)
            if(!strcmp(Entries[i].last_name, last_name))
                return i;
    }
    else{
        for(i=0; i<Num_Entries; i++)
            if(!strcmp(Entries[i].first_name, first_name) && !strcmp(Entries[i].last_name, last_name))
                return i;
    }
    return -1;
}
int place_finder(USER u){
    int i=0;
    if (Num_Entries > 1){
        while(strcmp(Entries[i].last_name, u.last_name) == -1 &&
            i < Num_Entries-1) i++;
        while(strcmp(Entries[i].last_name, u.last_name) == 0 &&
            strcmp(Entries[i].first_name, u.first_name)== -1 &&
            i < Num_Entries-1) i++;
        while (strcmp(Entries[i].last_name, u.last_name) == 0 &&
            strcmp(Entries[i].first_name, u.first_name) == 0  &&
            strcmp(Entries[i].phone_number, u.phone_number) == -1 &&
            i < Num_Entries-1) i++;
    }
    return i;
}
void print_user(USER u){
    printf("First Name: %s\n",u.first_name);
    printf("Last Name: %s\n",u.last_name);
    printf("City: %s\n",u.city);
    printf("Address: %s\n",u.street_address);
    printf("Phone Number: +2%s\n\n",u.phone_number);
}
void printall(){
    int i;
    for(i=0;i<Num_Entries;i++){printf("Contact #%d\n",i+1);print_user(Entries[i]);}
    if(i==0) printf("NO CONTACTS!\n");
    system("PAUSE");
}
void Save(){
    FILE* F = fopen("Contacts.txt","w");
    fprintf(F,"%d,%d\n",len_Entries,Num_Entries);
    int i;
    for(i=0;i < Num_Entries; i++){
        fprintf(F,"%s,",Entries[i].last_name);
        fprintf(F,"%s,",Entries[i].first_name);
        fprintf(F,"%s,",Entries[i].street_address);
        fprintf(F,"%s,",Entries[i].city);
        fprintf(F,"%s\n",Entries[i].phone_number);
    }
    fclose(F);
    printf("Saved successfully.\n");
    system("PAUSE");
}
void Load(){
    FILE* F = fopen("Contacts.txt","r");
    if(F == NULL){printf("File does not exist.\n"); Sleep(750); return;}
    fscanf(F,"%d,%d\n",&(len_Entries),&(Num_Entries));
    if(Num_Entries == 0){printf("Loading unsuccessful.\n"); Sleep(750); return;}
    printf("Loaded successfully.\n"); Sleep(750);
    Entries=malloc((len_Entries)*sizeof(USER));
    int i;
    for (i=0;i<Num_Entries;i++){
        fscanf(F,"%[^,],",(Entries[i].last_name));
        fscanf(F,"%[^,],",(Entries[i].first_name));
        fscanf(F,"%[^,],",(Entries[i].street_address));
        fscanf(F,"%[^,],",(Entries[i].city));
        fscanf(F,"%[^\n]\n",(Entries[i].phone_number));
    }
    fclose(F);
}
void validString(char* x){
        while (strlen(x)<1){
            printf("Wrong Input, Enter again:\n");
            gets(x);
    }
}
void ValidNum(char* x){
    int i=-1;
    validString(x);
    while(x[++i]!='\0'){
        if (x[i]<'0' || x[i]>'9'){
            printf("Please enter numbers only:\n");
            gets(x);
            ValidNum(x);
        }
    }
    return ;
}
