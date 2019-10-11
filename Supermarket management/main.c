#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>  // It's in order to use getch()
#include<unistd.h>
#define nbreuser 5
#include<time.h>
/*
                  Difference entre (fprintf,fscanf) et (fread, fwrite)
quand tu écris fprintf et fscanf, ça implique que tu utilisera des fichiers texte
quand tu écris fwrite et fread, ça implique que tu utilisera des fichiers binaire
*/
// I ended at the level of list of products( it's not OK)
void gotoxy(int x, int y)
{
HANDLE hConsoleOutput;
COORD dwCursorPosition;
dwCursorPosition.X=x;
dwCursorPosition.Y=y;
hConsoleOutput=GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

void horizontale(int x1,int x2,int y1, int y2)
{
int i;
  for(i=x1;i<=x2;i++)
  {
  gotoxy(i,y1);
  printf("%c",196);
  gotoxy(i,y2);
  printf("%c",196);
  }
}

void verticale(int x1,int x2,int y1, int y2)
{ int i;
 for(i=y1;i<=y2;i++)
  {
  gotoxy(x1,i);
  printf("%c",179);
  gotoxy(x2,i);
  printf("%c",179);
  }
}

void cadre(int x1,int x2,int y1, int y2)
{
int i;
// Je begin avec les lignes horizontales
  for(i=x1;i<=x2;i++)
  {
  gotoxy(i,y1);
  printf("%c",196);
  gotoxy(i,y2);
  printf("%c",196);
  }
  //Ensuite les lignes verticales
  for(i=y1;i<=y2;i++)
  {
  gotoxy(x1,i);
  printf("%c",179);
  gotoxy(x2,i);
  printf("%c",179);
  }
  //fin des verticales
  gotoxy(x1,y1);  printf("%c",218);
    gotoxy(x1,y2); printf("%c",192);
      gotoxy(x2,y1);
      printf("%c",191);
      gotoxy(x2,y2);
      printf("%c",217);
  }

void color(int t,int f)
{ //Il ya 256 code ASCI
HANDLE
H=GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(H,f*16+t);
}

int keyword1(int x,int y)
{  int d=0;
    char box[20];
    gotoxy(x+1,y);
    puts("Enter the password");
    gotoxy(x+2,y+2);
    printf("  ");
    box[d]=getch();  //à quoi ça sert??
     do{
      printf("*");
      x++;
      d++;
      box[d]=getch();
      }while(box[d]!=13);
      box[d]='\0';  //crucial

    if(strcmp(box,"yf")==0) // abeg don't write box[20] in strcmp ie,don't put the square brackets
      return 0;
      else{
        return 1;
      }
}


int keyword2(int x,int y) // seul le boss a ce mot de passe
{  int d=0;
    char box[20];
    gotoxy(x+1,y);
    puts("Enter the password");
    gotoxy(x+2,y+2);
    printf("  ");
    box[d]=getch();  //à quoi ça sert??
     do{
      printf("*");
      x++;
      d++;
      box[d]=getch();
      }while(box[d]!=13);
      box[d]='\0';  //crucial

    if(strcmp(box,"toi")==0) // abeg don't write box[20] in strcmp ie,don't put the square brackets
      return 0;
      else{
        return 1;
      }
}

void menu1(int x,int y)
{
    color(7,0);
    gotoxy(140,54); printf("copyrightYFWO2018");
    gotoxy(x+1,y+4); printf("1- ADMINISTRATOR");
    gotoxy(x+1,y+8); printf("2- USERS");
    gotoxy(x+1,y+12); printf("3- GO BACK");
    gotoxy(x+1,y+20); printf("Choose\t");
}

 void menu2(int x,int y)
{    color(7,0);
    gotoxy(x+1,y+4); printf("1- CUSTOMERS MANAGEMENT");
    gotoxy(x+1,y+8); printf("2- SALES MANAGEMENT");
    gotoxy(x+1,y+12); printf("3- LEAVE");
    gotoxy(x+1,y+20); printf("Choose\t");
    gotoxy(140,54); printf("copyrightYFWO2018");
    gotoxy(x+10,y+20);
}


// definissons toutes nos structures
typedef struct
   {

       char code[10];  // ie, le code d'une catégorie à au max 10 lettres
       char nom[20];  // ie, le nom d'une catégotie à au max 20 lettres
   }categorie;

typedef struct
{  char nom_client[20];    // chaque nom a une longueur maximale de 20
   char sex[10];
   char  typ_client[10];
   char code_client[10];
   float chiff_client;
}client;

typedef struct
{  char nameuser[20];
   char keyworduser[20];
   char matriculeuser[20];
   char accessuser[20];
}user;

typedef struct
{
int jour;
int mois;
int annee;
}date;

typedef struct
{
   char nom_client[20];
   char nom_vendeur[20];
   int qte;
   float PU;
   date dte;
  // float total;
  // time_t heure; // time_t est un type classique
}vente;



typedef struct
   {
       char nom[20];
       float PU;
       int Qte_stock;
       int Qte_seuil;
       char codeprod[10];
       char codecat[10];
   }prod;

    prod p; // c'est très important (comme ça je n'aurai plus besoin de déclarer ça dans mes fonctions void)
// de plus, si je déclarais ça en globale, à la fin de l'execution de mes fonctions void, le contenu sera effacé du disque dur


void sales()
{
FILE *f,*g,*h,*t;
char nomclient[20],nomproduit[20],nomvendeur[20];
int quantite;
user usr;
client cust;
vente v;
int j=0,l=0,m=0,y=0;
f=fopen("sales.pre","a");
g=fopen("products.txt","r+");
h=fopen("customers.txt","r");
t=fopen("users.txt","r");

if(f==NULL || g==NULL || h==NULL || t==NULL)
{
     system("cls");
     color(10,0); gotoxy(72,29); printf("FILE INEXISTENT!!"); color(7,0);
}
else{
//fread(&v,sizeof(v),1,f);
printf("Enter your name\t");
scanf("%s",nomvendeur); printf("\n");
 while(!feof(t) && fread(&usr,sizeof(usr),1,t)){
    if(strcmp(usr.nameuser,nomvendeur)==0){
        y=1;
    }
 }
 if(y==0){
    color(4,0); printf(" '%s' DOEN'T EXIST IN OUR SYSTEM",nomvendeur);
 }
 else{
printf("What's the name of the customer\t");
scanf("%s",nomclient);
 while(!feof(h) && fread(&cust,sizeof(cust),1,h)){
    if(strcmp(cust.nom_client,nomclient)==0){
        j=1;
    }
 }
 if(j==0){
    color(4,0); printf(" '%s' DOEN'T EXIST IN OUR SYSTEM",nomclient);
 }
 else{
        printf("Which product do you want?\t");
        scanf("%s",nomproduit);
        while(!feof(g) && fread(&p,sizeof(p),1,g)){
            if(strcmp(p.nom,nomproduit)==0)
                l=1;
          }
          fclose(g);
          if(l==0)
          {
           color(4,0); printf(" '%s' DOEN'T EXIST IN OUR SYSTEM",nomproduit);
          }
          else{
            do{
            printf("Which quantity do you want\t");
            scanf("%d",&quantite); printf("\n");
            }while(quantite<=0);

            //rewind(g); // crucial
             g=fopen("products.txt","r+");
            while((!feof(g)) && (fread(&p,sizeof(p),1,g))){
                 // printf("%d",l);
                if(strcmp(p.nom,nomproduit)==0){
                    if(p.Qte_stock>=quantite){
                        l=1;
                      p.Qte_stock=p.Qte_stock-quantite;
                      v.PU=p.PU;
                      fseek(g,-sizeof(p),SEEK_CUR);
                      fwrite(&p,sizeof(p),1,g);
                      fseek(g,0,SEEK_END);
                    }
            }
          }
          if(l==0)
          {
          color(4,0); printf(" THIS QUANTITY IS UNAVAILABLE");
          }
          else{
            //fread(&v,sizeof(v),1,f);
            v.qte =quantite;
            strcpy(v.nom_client,nomclient);
            strcpy(v.nom_vendeur,nomvendeur);
            printf("What's the date ? (in the form JJ-MM-AA\n");
            do{
            printf("JOUR\t"); scanf("%d",&v.dte.jour); printf("\n");
            }while(v.dte.jour<0 || v.dte.jour>31);

            do{
            printf("MOIS\t"); scanf("%d",&v.dte.mois); printf("\n");
            }while(v.dte.mois<=0 || v.dte.mois>12);

            do{
            printf("ANNEE\t"); scanf("%d",&v.dte.annee); printf("\n");
            }while(v.dte.annee<=0);

            fwrite(&v,sizeof(v),1,f);
            fclose(f);
            //rewind(f);
           //fseek(f,sizeof(v),SEEK_SET);
           // f=fopen("sales.pre","r"); // c'est "r" et nn "a" car tu veux lire maaintenant (et non ajouter)
           /* while(!feof(f) && fread(&v,sizeof(v),1,f))
            {   printf("HIIIIIIIIIII");
               printf("%s\n",v.nom_client);
               printf("%s\n",v.nom_vendeur);
               printf("%d\n",v.qte);
               printf("%d\n",v.dte.jour);
               printf("%d\n",v.dte.mois);
               printf("%d\n",v.dte.annee);


            } */
             }
          }
    }
 }
    fclose(g);
    fclose(h);
   // fclose(f);
}
 color(0,0); system("pause"); system("cls"); color(7,0) ;
}

void daily_invoice()
{
    FILE *f;
    vente v;
    int u=0,a,b,c,i=1;
    float total=0;
    f=fopen("sales.pre","r");
     if(f==NULL)
     {
     system("cls");
     color(10,0); gotoxy(72,29); printf("FILE INEXISTENT!!"); color(7,0);
     }
     else{
    printf("Enter the date (in the form JJ-MM-AA)\n");
    do{
    printf("JOUR\t"); scanf("%d",&a);
     }while(a<=0 || a>31);
    do{
    printf("MOIS\t"); scanf("%d",&b);
     }while(b<=0 || b>12);
   do{
    printf("ANNEE\t"); scanf("%d",&c);
     }while(c<=0);

     while(!feof(f) && fread(&v,sizeof(v),1,f))
     {
        if(v.dte.jour==a)
            if(v.dte.mois==b)
               if(v.dte.annee==c){
                      u=1;
                      fseek(f,0,SEEK_END);
               }
     }
     fclose(f);
     if(u==0)
     {
         gotoxy(72,29); color(4,0); printf(" NOTHING WAS SOLD ON THE %d-%d-%d\n",a,b,c); color(7,0);
     }
     else{
     system("cls"); color(2,1); cadre(1,164,0,57); color(7,0);
     gotoxy(72,2); printf("DATE:%d-%d-%d",a,b,c);
     gotoxy(5,5); color(10,0); printf("\t    NAME OF CUSTOMER\t\t\tUSER\t\t   QUANTITY BOUGHT\t\t    UNIT PRICE\t\t\tAMOUNT\n\n");
     printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
     color(7,0);
     //rewind(f);
     //fseek(f,sizeof(v),SEEK_SET);
     f=fopen("sales.pre","r+");
      while(!feof(f) && fread(&v,sizeof(v),1,f))
      {
           if((v.dte.jour==a)&&(v.dte.mois==b)&&(v.dte.annee==c)){
      printf("\n\t%10s\t\t\t%10s\t\t\t%d\t\t\t\t%f f\t\t\t%f f\n",v.nom_client,v.nom_vendeur,v.qte,v.PU,v.qte*v.PU);
      printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
      total=total+ v.qte*v.PU;
                  }
                }

   fclose(f);
     }
      gotoxy(72,40); printf("TOTAl=%f FCFA",total);
     }
    color(0,0); system("pause"); system("cls"); color(7,0) ;
}

void cadre1(int x1,int x2,int y1, int y2)
{
int i;
// Je begin avec les lignes horizontales
  for(i=x1;i<=x2;i++)
  {
  gotoxy(i,y1);
  printf("%c",'*');
  gotoxy(i,y2);
  printf("%c",'*');
  }
  Sleep(200);
  //Ensuite les lignes verticales
  for(i=y1;i<=y2;i++)
  {
  gotoxy(x1,i);
  printf("%c",'*');
  gotoxy(x2,i);
  printf("%c",'*');
  }
  Sleep(200);
  //fin des verticales
  gotoxy(x1,y1);
    printf("%c",218);
    gotoxy(x1,y2);
  printf("%c",192);
      gotoxy(x2,y1);
      printf("%c",191);
      gotoxy(x2,y2);
      printf("%c",217);
  }

void cadre2(int x1,int x2,int y1, int y2)
{
int i;
// Je begin avec les lignes horizontales
  for(i=x1;i<=x2;i++)
  {
  gotoxy(i,y1);
  printf("%c",'q');
  gotoxy(i,y2);
  printf("%c",'h');
  }
  Sleep(200);
  //Ensuite les lignes verticales
  for(i=y1;i<=y2;i++)
  {
  gotoxy(x1,i);
  printf("%c",'u');
  gotoxy(x2,i);
  printf("%c",'v');
  }
  Sleep(200);
  //fin des verticales
  gotoxy(x1,y1);
    printf("%c",218);
    gotoxy(x1,y2);
  printf("%c",192);
      gotoxy(x2,y1);
      printf("%c",191);
      gotoxy(x2,y2);
      printf("%c",217);
  }


void productsmanagement(int x,int y)
{ //prod p;
    cadre(70,120,10,50);
    gotoxy(x,y); puts("Enter the name of the new product");
    gotoxy(x,y+1); scanf("%s", p.nom);
    gotoxy(x,y+3); puts("What's its code?");
    gotoxy(x,y+4); scanf("%s", p.codeprod);
    gotoxy(x,y+6); puts("To which categorie does it belong?");
    gotoxy(x,y+7); scanf("%s", p.codecat); // on ne met pas "&" pour les chaines de caractère (car en mettant "&", cela impliquerai que tu veux mettre plusieurs caractères à la position reservé à un seul caractère normalement.
    gotoxy(x,y+9); puts("What's its unit price?");
    gotoxy(x,y+10); scanf("%f",&p.PU);
    gotoxy(x,y+12); puts("What's the quantity in stock?");
    gotoxy(x,y+13); scanf("%d", &p.Qte_stock);
    gotoxy(x,y+15); puts("What's the threshold quantity?");
    gotoxy(x,y+16); scanf("%d", &p.Qte_seuil);
}


int check_keyword_user()
{ user p;
int n=0,m=0;
char nme[10],key[10];
FILE *f;
f=fopen("users.txt","r");
if(f==NULL)
{
system("cls");
gotoxy(28,25);
printf("FILE INEXISTENT!!");
color(4,4); cadre(1,70,0,57); cadre(71,164,0,28);
cadre(71,164,28,57); color(7,0);
}
else{
   gotoxy(74,2); puts("What's your name??");
   gotoxy(74,4); scanf("%s",nme);
    gotoxy(74,6); puts("What's your keyword?");
     gotoxy(74,8); //scanf("%s",&key);
     //gotoxy(74,10);
     printf("  ");
    key[m]=getch();  //à quoi ça sert??
     do{
      printf("*");
//      x++;
      m++;
      key[m]=getch();
      }while(key[m]!=13);
      key[m]='\0';  //crucial

     while(!feof(f) && fread(&p,sizeof(p),1,f))
  {
      if(strcmp(p.nameuser,nme)==0)
          if(strcmp(p.keyworduser,key)==0)
              if(strcmp(p.accessuser,"GRANTED")==0)
                            n=1;
  }
}
return(n);
}

// start of fonctions for users
void adduser()
{
int a,i,b;
user usr;
      FILE *g;
      g=fopen("users.txt","a"); gotoxy(140,54); printf("copyrightYFWO2018");
      if(g==NULL){
        system("cls"); gotoxy(100,15);printf("FILE INEXISTENT!!");
        }
       else{
            do{
        system("cls");
        color(0,10); cadre(1,70,0,57); cadre(71,164,0,28); cadre(71,164,28,57);
        color(7,0); gotoxy(100,15);
        gotoxy(2,3); color(7,0); printf(" 1- ADD A USER");
        gotoxy(2,6); printf(" 2- MODIFY");
        gotoxy(2,9); printf(" 3- DELETE");
        gotoxy(2,12); printf(" 4- LIST");
        gotoxy(2,15); printf(" 5- GO BACK");
        gotoxy(2,20); printf("what's your choice?\t");
        gotoxy(140,54); printf("copyrightYFWO2018");
        gotoxy(74,2); puts("Enter the name of the new user!");
        gotoxy(74,3); scanf("%s",&usr.nameuser); gotoxy(74,4);
        //fwrite(&usr[i].nameuser,sizeof(usr[i].nameuser),1,g);  // si tu enregistre directement alors ça sera difficile d'écraser plutard quand l'utilisateur ne voudra pas enregistré
         puts("Enter his or her keyword");
        gotoxy(74,5); scanf("%s",&usr.keyworduser);
         gotoxy(74,6);
          //fwrite(&usr[i].keyworduser,sizeof(usr[i].keyworduser),1,g);
          puts("What's the user's matricule?");
        gotoxy(74,7); scanf("%s",&usr.matriculeuser);
        gotoxy(74,8);
        //fwrite(&usr[i].matriculeuser,sizeof(usr[i].matriculeuser),1,g);
        gotoxy(74,9); puts("ACCESS");
        gotoxy(74,10); scanf("%s",&usr.accessuser);
        color(2,0);
        gotoxy(82,16); printf("Should we save it?");
        gotoxy(74,18); printf("1- YES");
        gotoxy(100,18); printf("2- NO");
        gotoxy(90,19); scanf("%d",&a);
        if(a==1){
         fwrite(&usr,sizeof(usr),1,g); // j'enregistre uniquement quand il accepte!!
        gotoxy(82,20); printf("Are you done?");
        gotoxy(74,24); printf("1- YES");
        gotoxy(100,24); printf("2- NO");
        gotoxy(90,26); scanf("%d",&b);

      if(b==1){
        system("cls");
        //récitation
        color(0,10); cadre(1,70,0,57); cadre(71,164,0,28); cadre(71,164,28,57);
        color(7,0); gotoxy(100,15); gotoxy(2,3); color(7,0); printf(" 1- ADD A USER");
        gotoxy(2,6); printf(" 2- MODIFY"); gotoxy(2,9); printf(" 3- DELETE"); gotoxy(2,12); printf(" 4- LIST"); gotoxy(2,15); printf(" 5- GO BACK"); gotoxy(2,20); printf("what's your choice?\t");
                    //fin de la récitation
              }
              }
            }while(b==2);
        gotoxy(100,35);
        color(7,0);
        gotoxy(100,35);
        puts("INFORMATION SAVED CORRECTLY!!");
        fclose(g);
       gotoxy(74,37);
       color(0,0);  // c'est pour empêcher que le message "Appuyer sur une touche pour continuer puis s'afficher " je le fais en écrivant noir sur noir
        system("pause"); system("cls"); color(7,0);
       }
}

void modifyuser()
{   user p;
   char name[20];
    FILE *f;
    f=fopen("users.txt","r+");
    if(f==NULL){ system("cls"); gotoxy(100,15); printf("FILE INEXISTENT!!");        color(0,10); cadre(1,70,0,57); cadre(71,164,0,28); cadre(71,164,28,57);         color(7,0); gotoxy(100,15); gotoxy(2,3); color(7,0); printf(" 1- ADD A USER");
        gotoxy(2,6); printf(" 2- MODIFY"); gotoxy(2,9); printf(" 3- DELETE"); gotoxy(2,12); printf(" 4- LIST"); gotoxy(2,15); printf(" 5- GO BACK"); gotoxy(2,20); printf("what's your choice?\t");}
    else{color(0,10); cadre(1,70,0,57); cadre(71,164,0,28); cadre(71,164,28,57);
       gotoxy(74,2); puts("On which user do you want to carry out changes?");  gotoxy(74,4); scanf("%s",&name);
       while(!feof(f) && fread(&p,sizeof(p),1,f))
{      //fread(&p,sizeof(p),1,f);
        if(strcmp(p.nameuser,name)==0)
        {   gotoxy(74,6); puts("What's its new keyword?");
            gotoxy(74,8); scanf("%s",&p.keyworduser);
            gotoxy(74,10); puts("What's its new matricule number?");
            gotoxy(74,12); scanf("%s",&p.matriculeuser);
            gotoxy(74,14); puts("What's its status?");
            gotoxy(74,16); scanf("%s",&p.accessuser);
            fseek(f,-sizeof(p),SEEK_CUR);
             fwrite(&p,sizeof(p),1,f);
             fseek(f,0,SEEK_END);
       }
}fclose(f);
}
color(0,0); system("pause"); system("cls");
}


void deleteuser()  // ça supprime mais ça multiplie l'occurrence
{  user p;
int j=0;
char name[20];
    FILE *f,*g;  // g c'est le fichier temporaire
    f=fopen("users.txt","r");
    g=fopen("users2","w");
    if(f==NULL || g==NULL){
        system("cls");
         gotoxy(100,15);
         printf("FILE INEXISTENT!!");
         //récitation
        color(0,10); cadre(1,70,0,57); cadre(71,164,0,28); cadre(71,164,28,57);
        color(7,0); gotoxy(100,15);
        gotoxy(2,3); color(7,0); printf(" 1- ADD A USER");
        gotoxy(2,6); printf(" 2- MODIFY A USER");
         gotoxy(2,9); printf(" 3- DELETE A USER");
         gotoxy(2,12); printf(" 4- LIST OF USERS");
         gotoxy(2,15); printf(" 5- GO BACK");
         gotoxy(2,20); printf("what's your choice?\t");
              //fin de la récitation
    }
    else{
    color(0,10); cadre(1,70,0,57); cadre(71,164,0,28); cadre(71,164,28,57);
    color(7,0); gotoxy(100,15);
    gotoxy(2,3); color(7,0); printf(" 1- ADD A USER");
    gotoxy(2,6); printf(" 2- MODIFY A USER");
    gotoxy(2,9); printf(" 3- DELETE A USER");
    gotoxy(2,12); printf(" 4- LIST OF USERS");
    gotoxy(2,15); printf(" 5- GO BACK");
    gotoxy(2,20); printf("what's your choice?\t");
    color(7,0);
    gotoxy(74,2); printf("Which user do you want to delete?");
    gotoxy(74,4); scanf("%s",name);  // NB: quand tu use scanf, ta chaine de caractère ne doit pas contenir d'espace
    gotoxy(74,6);                 // "gets" est utilisable avec des chaînes de caractère contenant des espaces (si nn, ça ne marchera pas)
        while(!feof(f)&& fread(&p,sizeof(p),1,f)){
        if(strcmp(p.nameuser,name)!=0){
            fwrite(&p,sizeof(p),1,g);
            }
        if(strcmp(p.nameuser,name)==0)
            j=1;
        }
        if(j==0)
        {
            gotoxy(100,35); color(4,0); printf(" '%s' DOESN'T EXIST IN THE SYSTEM",name);
        }
        if(j==1){
        gotoxy(100,35); color(10,0);
        printf(" ' %s ' HAS BEEN DELETED FROM THE SYSTEM",name); color(7,0);
        }
        fclose(g);
        fclose(f);
        remove("users");
        rename("users2","users");

    }
    color(0,0);
    system("pause");
    system("cls"); color(7,0);
}

void listuser()
{   user p;
    FILE *f;
    f=fopen("users.txt","r");
if(f==NULL){
system("cls");
gotoxy(100,15); printf("FILE INEXISTENT!!");
color(0,10); cadre(1,70,0,57); cadre(71,164,0,28); cadre(71,164,28,57);
color(7,0);
gotoxy(2,3); color(7,0); printf(" 1- ADD A USER");
gotoxy(2,6); printf(" 2- MODIFY");
gotoxy(2,9); printf(" 3- DELETE");
gotoxy(2,12); printf(" 4- LIST");
gotoxy(2,15); printf(" 5- GO BACK");
gotoxy(2,20); printf("what's your choice?\t");}
    else
{ gotoxy(2,2); printf("\t      NAME\t\t\t      KEYWORD\t\t\t   MATRICULE\t\t\t     STATUS\n"); //printf(""); printf(""); printf("");
  printf(" ------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n\t");
   while(!feof(f) && fread(&p,sizeof(p),1,f))
      {
      //fread(&p,sizeof(p),1,f);  j'ai preferé mettre ça dans les parenthèses du while; car ça me doublait le dernier nom enregistré!
      printf("%10s\t\t\t%10s\t\t\t%10s\t\t\t%10s\n",p.nameuser,p.keyworduser,p.matriculeuser,p.accessuser);
            printf(" -------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\t");
      }
            verticale(30,30,0,57); verticale(60,60,0,57);  verticale(90,90,0,57); verticale(120,120,0,57);
      fclose(f);
    }
printf("\n\n\n\n\n"); color(0,0); system("pause");  system("cls"); color(7,0);
}


// end of fonctions for users

// start of fonctions for customers
void addcustomer()
{
int a,i,b;
client cust;
      FILE *g;
      g=fopen("customers.txt","a");
      gotoxy(140,54); printf("copyrightYFWO2018");
      if(g==NULL){ system("cls"); gotoxy(100,15);  printf("FILE INEXISTENT!!");}
       else{
            do{ system("cls");  horizontale(20,70,4,4); cadre(70,120,1,25);
            gotoxy(2,4); printf(" 1- ADD A CUSTOMER");   gotoxy(2,7); printf(" 2- MODIFY");  gotoxy(2,10); printf(" 3- DELETE");  gotoxy(2,13); printf(" 4- LIST"); gotoxy(2,16); printf(" 5- GO BACK"); gotoxy(2,22); printf("what's your choice?\t");
        gotoxy(140,54); printf("copyrightYFWO2018"); gotoxy(74,2); puts("Enter the name of the new customer!");gotoxy(74,3); scanf("%s",&cust.nom_client);
        gotoxy(74,4);
        //fwrite(&usr[i].nameuser,sizeof(usr[i].nameuser),1,g);  // si tu enregistre directement alors ça sera difficile d'écraser plutard quand l'utilisateur ne voudra pas enregistré
         puts("Enter his or her identifier number");
        gotoxy(74,5); scanf("%s",&cust.code_client);
         gotoxy(74,6);
          //fwrite(&usr[i].keyworduser,sizeof(usr[i].keyworduser),1,g);
          puts("type of client?"); gotoxy(74,7); scanf("%s",&cust.typ_client);

        gotoxy(74,8);
        //fwrite(&usr[i].matriculeuser,sizeof(usr[i].matriculeuser),1,g);
        gotoxy(74,9); puts("SEX");
        gotoxy(74,10); scanf("%s",&cust.sex);
        color(2,0);
        gotoxy(82,13); printf("Should we save it?");
        gotoxy(74,15); printf("1- YES");
        gotoxy(100,15); printf("2- NO");
        gotoxy(90,16); scanf("%d",&a);
        if(a==1){
         fwrite(&cust,sizeof(cust),1,g); // j'enregistre uniquement quand il accepte!!
        gotoxy(82,17); printf("Are you done?");
        gotoxy(74,19); printf("1- YES");
        gotoxy(100,19); printf("2- NO");
        gotoxy(90,20); scanf("%d",&b);

      if(b==1){color(7,0); gotoxy(0,0);
        system("cls");
        printf("**************************************************************************************************************************************************************************************************************************");
            gotoxy(2,4); printf(" 1- ADD A CUSTOMER");   gotoxy(2,7); printf(" 2- MODIFY");  gotoxy(2,10); printf(" 3- DELETE");  gotoxy(2,13); printf(" 4- LIST"); gotoxy(2,16); printf(" 5- GO BACK"); gotoxy(2,22); printf("what's your choice?\t");
              }}//color(0,0);
            }while(b==2); gotoxy(80,35);  color(10,0); gotoxy(100,35); puts("INFORMATION SAVED CORRECTLY!!");  color(7,0); fclose(g); gotoxy(74,37); color(0,0); system("pause"); system("cls");
}
}


void modifycustomer()
{ char name[20];
client p;
    FILE *f;
    f=fopen("customers.txt","r+");
    if(f==NULL){
        system("cls");
         gotoxy(100,15); printf("FILE INEXISTENT!!");
         color(0,10); cadre(1,70,0,57); cadre(71,164,0,28); cadre(71,164,28,57);
          color(7,0); gotoxy(100,15);
          gotoxy(2,3); color(7,0); printf(" 1- ADD");
         gotoxy(2,6); printf(" 2- MODIFY");
         gotoxy(2,9); printf(" 3- DELETE");
         gotoxy(2,12); printf(" 4- LIST");
         gotoxy(2,15); printf(" 5- GO BACK");
         gotoxy(2,20); printf("what's your choice?\t");
         gotoxy(140,54); printf("copyrightYFWO2018");
    }
    else{
    gotoxy(74,2); color(7,0);horizontale(12,70,7,7); cadre(70,125,1,30);
    color(7,0); gotoxy(74,3);
     puts("On which user do you want to carry out changes?"); gotoxy(74,4); scanf("%s",&name);
       while(!feof(f) && fread(&p,sizeof(p),1,f)){
        if(strcmp(p.nom_client,name)==0){
    gotoxy(74,6); puts("What's his or her status?");
    gotoxy(74,8); scanf("%s",&p.typ_client);
    gotoxy(74,10); puts("What's its new matricule number?");
    gotoxy(74,12); scanf("%s",&p.code_client);
    gotoxy(74,14); puts("What's his or her sex?");
    gotoxy(74,16); scanf("%s",&p.sex);
    fseek(f,-sizeof(p),SEEK_CUR);
    fwrite(&p,sizeof(p),1,f);
    fseek(f,0,SEEK_END);
                }
                }
fclose(f);
}
color(0,0); system("pause"); system("cls"); color(7,0);
}

void deletecustomer()
{
    int j=0;
    client p;
char name[20];
    FILE *f,*g;  // g c'est le fichier temporaire
    f=fopen("customers.txt","r");
    if(f==NULL){
        system("cls");
         gotoxy(100,15);
         printf("FILE INEXISTENT!!");
         //récitation
        color(0,10); cadre(1,70,0,57); cadre(71,164,0,28); cadre(71,164,28,57);
        color(7,0); gotoxy(100,15); gotoxy(2,3); color(7,0); printf(" 1- ADD A USER");
        gotoxy(2,6); printf(" 2- MODIFY"); gotoxy(2,9); printf(" 3- DELETE"); gotoxy(2,12); printf(" 4- LIST"); gotoxy(2,15); printf(" 5- GO BACK"); gotoxy(2,20); printf("what's your choice?\t");
              //fin de la récitation
    }
    else{           color(7,0); horizontale(12,70,10,10); cadre(70,125,5,15);

            gotoxy(74,6); printf("Which customer do you want to delete?");
    gotoxy(74,8); scanf("%s",&name);  // NB: quand tu use scanf, ta chaine de caractère ne doit pas contenir d'espace
    gotoxy(74,10);                 // "gets" est utilisable avec des chaînes de caractère contenant des espaces (si nn, ça ne marchera pas)
        g=fopen("customers2.txt","w");
        while(!feof(f)&& fread(&p,sizeof(p),1,f)){
            if(strcmp(p.nom_client,name)!=0){
            fwrite(&p,sizeof(p),1,g);
            }
            if(strcmp(p.nom_client,name)==0)
                 j=1;
        }
        if(j==0)
        {
        gotoxy(74,13); color(4,0);
        printf(" ' %s ' DOEN'T EXIST IN THE SYSTEM",name); color(7,0);
        }
        else{
            gotoxy(74,13); color(10,0);
        printf(" ' %s ' HAS BEEN DELETED FROM THE SYSTEM",name); color(7,0);
        }
        fclose(g);
        fclose(f);
        remove("customers.txt");
        rename("customers2.txt","customers.txt");

        color(0,0); system("pause"); system("cls"); color(7,0);
    }
}

void listcustomer()
{   client p;  FILE *f;  f=fopen("customers.txt","r");
    if(f==NULL){
    system("cls");
    gotoxy(100,15); printf("FILE INEXISTENT!!");
    color(0,10); cadre(1,70,0,57); cadre(71,164,0,28); cadre(71,164,28,57);
    color(7,0);  gotoxy(2,3); color(7,0); printf(" 1- ADD");
    gotoxy(2,6); printf(" 2- MODIFY");
    gotoxy(2,9); printf(" 3- DELETE");
    gotoxy(2,12); printf(" 4- LIST");
    gotoxy(2,15); printf(" 5- GO BACK");
    gotoxy(2,20); printf("what's your choice?\t");}
    else{
    system("cls"); color(2,11); cadre(1,164,0,57); color(7,0);
    gotoxy(2,2); printf("\t      NAME\t\t\t      STATUS\t\t\t   MATRICULE\t\t\t\t      SEX\n"); //printf(""); printf(""); printf("");
      printf(" -------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n\t");
      while(!feof(f) && fread(&p,sizeof(p),1,f))
      {
      //fread(&p,sizeof(p),1,f);  j'ai preferé mettre ça dans les parenthèses du while; car ça me doublait le dernier nom enregistré!
      printf("%10s\t\t\t%10s\t\t\t%10s\t\t\t%10s\n",p.nom_client,p.typ_client,p.code_client,p.sex);
      printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\t");
      }
      verticale(30,30,0,57); verticale(60,60,0,57);  verticale(90,90,0,57); verticale(120,120,0,57);
      fclose(f);
}
printf("\n\n\n\n\n"); gotoxy(10,20); color(0,0); system("pause");  system("cls"); color(7,0);
}

//end of foncctions for customers


// start of fonctions for products
void addproducts()
{
    int a,i,b;
//prod p;
FILE *g;
g=fopen("products.txt","a");
gotoxy(140,54); printf("copyrightYFWO2018");
if(g==NULL){
    system("cls");
gotoxy(100,15);  printf("FILE INEXISTENT!!");
gotoxy(140,54); printf("copyrightYFWO2018");
}
else{
   do{ color(7,0);
    system("cls"); gotoxy(0,3);
    puts("*****************************************************************");
    color (0,15); cadre(65,90,1,5); gotoxy(70,3); color(6,0);
    puts("PRODUCTS MANAGEMENT"); color(7,0); gotoxy(91,3);
    puts("*******************************************************************************************************************");
    gotoxy(2,8); printf(" 1- ADD A PRODUCT");
    gotoxy(2,11); printf(" 2- MODIFY A PRODUCT");
    gotoxy(2,14); printf(" 3- DELETE A PRODUCT");
    gotoxy(2,17); printf(" 4- LIST OF PRODUCTS");
    gotoxy(2,20); printf(" 5- PRODUCTS IN SHORTAGE");
    gotoxy(2,23); printf(" 6- SUPPLY");
    gotoxy(2,26); printf(" 7- GO BACK");
    gotoxy(2,35); printf("what's your choice?\t");
    gotoxy(140,54); printf("copyrightYFWO2018");
    gotoxy(74,2);
    horizontale(19,44,8,8);  gotoxy(44,8); printf("%c",191); verticale(44,44,9,25);
    gotoxy(44,25); printf("%c",192);horizontale(45,70,25,25);
    productsmanagement(71,11);
    color(2,0);
    gotoxy(82,28); printf("Should we save it?");
    gotoxy(74,30); printf("1- YES");
    gotoxy(100,30); printf("2- NO");
    gotoxy(90,31); scanf("%d",&a);
    if(a==1){
        fwrite(&p,sizeof(p),1,g); // j'enregistre uniquement quand il accepte!!
        gotoxy(82,33); printf("Are you done?");
        gotoxy(74,35); printf("1- YES");
        gotoxy(100,35); printf("2- NO");
        gotoxy(90,36); scanf("%d",&b);

      if(b==1){ system("cls");color(7,0); gotoxy(0,3);
        puts("*****************************************************************");color (0,15); cadre(65,90,1,5); gotoxy(70,3); color(6,0); puts("PRODUCTS MANAGEMENT"); color(7,0); gotoxy(91,3); puts("*******************************************************************************************************************");
        gotoxy(2,8); printf(" 1- ADD A PRODUCT");
    gotoxy(2,11); printf(" 2- MODIFY A PRODUCT");
    gotoxy(2,14); printf(" 3- DELETE A PRODUCT");
    gotoxy(2,17); printf(" 4- LIST OF PRODUCTS");
    gotoxy(2,20); printf(" 5- PRODUCTS IN SHORTAGE");
    gotoxy(2,23); printf(" 6- SUPPLY");
    gotoxy(2,26); printf(" 7- GO BACK");
    gotoxy(2,35); printf("what's your choice?\t");
              }
    }
}while(b==2);
gotoxy(85,35);  color(10,0); gotoxy(65,35); puts("INFORMATION SAVED CORRECTLY!!"); color(7,0);
fclose(g); gotoxy(74,37);
}
color(0,0);  system("pause"); system("cls"); color(7,0);
}


void modifyproducts()
{ char name[20];
//prod p;
int a,i,b,j=0;
    FILE *g;
    g=fopen("products.txt","r+");
    if(g==NULL){
    system("cls");
    gotoxy(0,3); gotoxy(100,15);  printf("FILE INEXISTENT!!");
    puts("*****************************************************************");
    color (0,15); cadre(65,90,1,5); gotoxy(70,3); color(6,0);
    puts("PRODUCTS MANAGEMENT"); color(7,0); gotoxy(91,3);
    puts("*******************************************************************************************************************");
    gotoxy(2,8); printf(" 1- ADD A PRODUCT");
    gotoxy(2,11); printf(" 2- MODIFY A PRODUCT");
    gotoxy(2,14); printf(" 3- DELETE A PRODUCT");
    gotoxy(2,17); printf(" 4- LIST OF PRODUCTS");
    gotoxy(2,20); printf(" 5- PRODUCTS IN SHORTAGE");
    gotoxy(2,23); printf(" 6- SUPPLY");
    gotoxy(2,26); printf(" 7- GO BACK");
    gotoxy(2,35); printf("what's your choice?\t");
    gotoxy(140,54); printf("copyrightYFWO2018");
    }
    else{ color(7,0);
    horizontale(22,44,11,11);  gotoxy(44,11); printf("%c",191); verticale(44,44,12,25);
    gotoxy(44,25); printf("%c",192);horizontale(45,70,25,25);
    productsmanagement(71,11);
    fseek(g,-sizeof(p),SEEK_CUR);
    fwrite(&p,sizeof(p),1,g);
    fseek(g,0,SEEK_END);
    color(10,0); gotoxy(75,35); puts("INFORMATION SAVED CORRECTLY!!");
    fclose(g);
    gotoxy(74,37);
}
color(0,0); system("pause"); system("cls"); color(7,0);
}

void deleteproducts()
{
    //prod p;
    int j=0;
char name[20];
    FILE *f,*g;
    f=fopen("products.txt","r");
    if(f==NULL){
        system("cls");
        color(4,0); gotoxy(72,29);
         printf("FILE INEXISTENT!!"); color(7,0);
    }
    else{ color(7,0); horizontale(22,70,14,14); cadre(70,125,8,20);
    gotoxy(74,10); printf("Which product do you want to delete?");
    gotoxy(74,12); scanf("%s",&name);  // NB: quand tu use scanf, ta chaine de caractère ne doit pas contenir d'espace
    gotoxy(74,14);                 // "gets" est utilisable avec des chaînes de caractère contenant des espaces (si nn, ça ne marchera pas)
        g=fopen("products2.txt","w");
        while(!feof(f)&& fread(&p,sizeof(p),1,f)){
            if(strcmp(p.nom,name)!=0){
            fwrite(&p,sizeof(p),1,g);
            }
            if(strcmp(p.nom,name)==0)
            j=1;
        }
        if(j==0)
        {
           gotoxy(74,16); color(4,0);
        printf(" '%s' DOESN'T EXIST IN THE SYSTEM",name); color(7,0) ;
        }
        else{
         gotoxy(74,16); color(10,0);
        printf(" ' %s ' HAS BEEN DELETED FROM THE SYSTEM",name);
        }
        fclose(g);
        fclose(f);
        remove("products.txt");
        rename("products2.txt","products.txt");

    }
color(0,0); system("pause"); system("cls"); color(7,0);
}

void listproducts()
{   //prod p;
    FILE *f;
    f=fopen("products.txt","r");
    if(f==NULL){
    system("cls");
     color(4,0); gotoxy(72,29); printf("FILE INEXISTENT!!"); color(7,0);
    }
    else{
     system("cls"); color(2,11); cadre(1,164,0,57); color(7,0);
    gotoxy(2,2); printf("\t    NAME\t\tUNIT PRICE\t\t   QUANTITY IN STOCK\t\t    THRESHOLD QUANTITY\t\t CODE \t\t CATEGORY\n");
    printf(" -------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n\t");
     //verticale(15,15,0,64); verticale(40,40,0,64);  verticale(70,70,0,64); verticale(120,120,0,64);
      while(!feof(f) && fread(&p,sizeof(p),1,f))
      {
      //fread(&p,sizeof(p),1,f);  j'ai preferé mettre ça dans les parenthèses du while; car ça me doublait le dernier nom enregistré!
    printf("%5s\t\t\t%5f f\t\t\t%5d\t\t\t\t%5d\t\t\t\t%5s\t\t  %5s\n",p.nom,p.PU,p.Qte_stock,p.Qte_seuil,p.codeprod,p.codecat);
    printf(" -------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\t");
      }
verticale(25,25,0,57); verticale(50,50,0,57); verticale(84,84,0,57);
verticale(115,115,0,57); verticale(130,130,0,57); verticale(160,160,0,57);
fclose(f);
}
printf("\n\n\n\n\n"); color(0,0); system("pause");  system("cls"); color(7,0);
}

void shortage_products(int a,int b)
{
    int i,j=0;
    FILE *f;
    f=fopen("products.txt","r");
    if(f==NULL )
    {
        system("cls");
     color(10,0); gotoxy(72,29); printf("FILE INEXISTENT!!"); color(7,0);
    }
    else{
    while(!feof(f) && fread(&p,sizeof(p),1,f))
    {
        if((p.Qte_stock)<=(p.Qte_seuil))
              { if(j==1)
                  b=b+2;
            gotoxy(a,b); printf("%s",p.nom); //printf("TA MAMANN");
            gotoxy(a+28,b);  printf("%d",p.Qte_stock); //printf("TON PAPA");
            j=1;
              }
    }
            if(j==0){ system("cls");
            gotoxy(26,20); horizontale(26,35,20,20); gotoxy(35,20); printf("%c",191);verticale(35,35,21,31);gotoxy(35,31); printf("%c",192); horizontale(36,110,31,31);
            cadre(110,160,20,57); horizontale(125,144,23,23);
            gotoxy(130,29);
            color(3,0); printf("NO PRODUCT IS IN SHORTAGE"); color(7,0);
            }
            else{ gotoxy(26,20); horizontale(26,35,20,20); gotoxy(35,20); printf("%c",191);verticale(35,35,21,31);gotoxy(35,31); printf("%c",192); horizontale(36,110,31,31);
                cadre(110,160,20,57); horizontale(125,144,23,23);
                         color(4,0); gotoxy(125,22); printf("PRODUCTS IN SHORTAGE"); color(7,0);
                         gotoxy(115,25); color(3,0); printf("PRODUCTS");
                         gotoxy(137,25); color(3,0); printf("QUANTITY REMAINING");
            }
    fclose(f);
}
color(0,0); system("pause");  system("cls"); color(7,0);
}

void supply_products()
{  char name[20];
int j=0,a;
    FILE *f;
    f=fopen("products.txt","r+"); // r+ car je veux modifier
    if(f==NULL )
    {
        system("cls");
     color(10,0); gotoxy(72,29); printf("FILE INEXISTENT!!"); color(7,0);
    }
    else{
    color(3,0);  horizontale(12,50,23,23); cadre(50,100,17,30);
    gotoxy(51,18);  printf("Enter the name of the product you want to supply");
    gotoxy(51,20); scanf("%s",name);
        while(!feof(f) && fread(&p,sizeof(p),1,f))
        {
           if(strcmp(name,p.nom)==0){
            j=1;
            gotoxy(51,23); printf("What's the quantity to be added?");
            gotoxy(51,25); scanf("%d",&a);
            p.Qte_stock = p.Qte_stock + a;
            color(10,0);
            gotoxy(51,27); printf(" '%s' has been updated",name);
             fseek(f,-sizeof(p),SEEK_CUR);
            fwrite(&p,sizeof(p),1,f);
            fseek(f,0,SEEK_END);
            fclose(f);
           }
        }
        if(j==0)
        {
             color(4,0); gotoxy(55,25); printf("'%s' DOEN'T EXIST IN THE SYSTEM",name);
        }
    }
color(0,0); system("pause");  system("cls"); color(7,0);
}

//end of foncctions for products


/*
t=(NULL);
time(&t); // a ce moment, l'heure se trouve dans la "t"
v.heure=t;
*/
 void main()
{
int choix1,s,t,n=0,m,choix2,choix3,L[20], choix4,name[15],choix5,choix6,choix7,choix8;
char *users;
do{ system("cls");
gotoxy(2,1); printf("\t\t\t\t\t'PERFECTION IS NOT ATTAINABLE BUT IF WE CHASE PERFECTION WE CAN CATCH EXCELLENCE'");
gotoxy(140,56); printf("copyrightYFWO2018");
color(0,15);         //      Quand tu as color(a,b), a représente la couleur du text et b représente la couleur du fond!
cadre(70,87,20,25);   gotoxy(72,22); printf("YY SUPERMARKET");
color(7,0);  // pour que ça me remette un fond noir et le texte en blanc
s=keyword1(69,27);

if(s==0){

system("cls");

do{
gotoxy(72,5);   printf("'WELCOME TARA!!!!'");
color(0,15); cadre(1,164,0,57);  menu1(4,7);
scanf("%d",&choix1);
system("cls");
switch(choix1){
     case 1:t=keyword2(69,27);
            system("cls");
            if(t==0){
            do{
            gotoxy(140,56); printf("copyrightYFWO2018");
            cadre1(50,110,15,40); color(10,0);
            gotoxy(57,20); printf("1- USERS MANAGEMENT");
            gotoxy(57,25); printf("2- PRODUCTS MANAGEMENT");
            gotoxy(57,30); printf("3- GO BACK");
            Sleep(300);
            cadre1(52,108,17,38);
            gotoxy(57,35); printf("CHOICE"); color(7,0); gotoxy(74,35);
            scanf("%d",&choix7);
            system("cls");
            switch(choix7)
            {
              case 1:
                   do{
                     gotoxy(140,56); printf("copyrightYFWO2018");
                     color(0,10); cadre(1,70,0,57); cadre(71,164,0,28); cadre(71,164,28,57);
                     color(7,0); gotoxy(100,15);
                     gotoxy(2,3); color(7,0); printf(" 1- ADD A USER");
                     gotoxy(2,6); printf(" 2- MODIFY A USER");
                     gotoxy(2,9); printf(" 3- DELETE A USER");
                     gotoxy(2,12); printf(" 4- LIST OF USERS");
                     gotoxy(2,15); printf(" 5- GO BACK");
                     gotoxy(2,20); printf("what's your choice?\t");
                     scanf("%d",&choix3); system("cls");
                     switch(choix3){
                             case 1:gotoxy(74,2);
                                    adduser();
                                    break;
                             case 2:modifyuser();
                                    break;
                             case 3:deleteuser();
                                    break;
                             case 4:system("cls");
                                    color(2,11); cadre(1,164,0,57); color(7,0);
                                    gotoxy(2,2);
                                    listuser();
                                    break;
                             case 5:break;
                             default:gotoxy(100,35); printf("INEXISTING CHOICE !!");
                                     color(0,0); // c'est empêcher que le message "Appuyer sur une touche pour continuer" puis s'afficher; je le fais en écrivant noir sur noir
                                     system("pause");
                                     system("cls");
                                      break;
                                     }
                     }while(choix3!=5);
                     system("cls");
                     break;
           case 2:
                 do{ system("cls");
                 gotoxy(0,3);
                 puts("*****************************************************************");color (0,15); cadre(65,90,1,5); gotoxy(70,3); color(6,0); puts("PRODUCTS MANAGEMENT"); color(7,0); gotoxy(91,3); puts("*******************************************************************************************************************");
                 gotoxy(2,8); printf(" 1- ADD A PRODUCT");
                 gotoxy(2,11); printf(" 2- MODIFY A PRODUCT");
                 gotoxy(2,14); printf(" 3- DELETE A PRODUCT");
                 gotoxy(2,17); printf(" 4- LIST OF PRODUCTS");
                 gotoxy(2,20); printf(" 5- PRODUCTS IN SHORTAGE");
                 gotoxy(2,23); printf(" 6- SUPPLY");
                 gotoxy(2,26); printf(" 7- GO BACK");
                 gotoxy(2,35); printf("what's your choice?\t");
                 scanf("%d",&choix6);
                 switch(choix6)
                 {
                  case 1:addproducts(); break;
                  case 2: modifyproducts(); break;
                  case 3: deleteproducts(); break;
                  case 4:color(0,0); listproducts(); break;
                  case 5:shortage_products(115,27); break;
                  case 6:supply_products(); break;
                  case 7:break;
                 }
                  }while(choix6!=7);
                  system("cls");
                break;
    case 3:break;
             }
     }while(choix7!=3);
     system("cls");
           break;
case 2:color(6,6); cadre(1,70,0,57); cadre(71,164,0,28); cadre(71,164,28,57);
             color(7,0); gotoxy(100,15);
             m=check_keyword_user();
             gotoxy(2,2);
             if(m==1)
             {
                 do{
                   system("cls");
                   color(6,6); cadre(1,70,0,57); cadre(71,164,0,28); cadre(71,164,28,57); color(7,0);
                  menu2(4,7);
                  scanf("%d",&choix4);
                  system("cls");
                  switch(choix4)
                  {
                      case 1:do{ color(7,0);
                        printf("**************************************************************************************************************************************************************************************************************************");
                        gotoxy(2,4); printf(" 1- ADD A CUSTOMER");   gotoxy(2,7); printf(" 2- MODIFY A CUSTOMER");  gotoxy(2,10); printf(" 3- DELETE A CUSTOMER");  gotoxy(2,13); printf(" 4- LIST OF CUSTOMERS"); gotoxy(2,16); printf(" 5- GO BACK"); gotoxy(2,22); printf("what's your choice?\t");
                        scanf("%d",&choix5);
                             switch(choix5)
                             {     case 1:addcustomer();  break;
                                   case 2: modifycustomer(); break;
                                   case 3: deletecustomer();  break;
                                   case 4: listcustomer(); break;
                                   case 5:break;
                                   default:gotoxy(100,35); printf("INEXISTING CHOICE !!");  color(0,0);  system("pause");system("cls"); break;
                             }
                      }while(choix5!=5);
                             break;
                      case 2:do{ color(7,0);
                             gotoxy(140,56); printf("copyrightYFWO2018");
                             cadre2(50,110,15,40); color(10,0);
                             gotoxy(57,20); printf("1- SELL");
                             gotoxy(57,25); printf("2- DAILY INVOICE");
                             gotoxy(57,30); printf("3- GO BACK");
                             Sleep(300);
                             cadre2(52,108,17,38);
                             gotoxy(57,35); printf("CHOICE"); color(7,0); gotoxy(74,35);
                             scanf("%d",&choix8);
                             system("cls");
                             switch(choix8)
                             {
                                 case 1:sales();
                                        break;
                                 case 2:daily_invoice();
                                        break;
                                 case 3:break;
                             }
                             }while(choix8!=3);
                             break;
                      case 3:break;
                  }
             }while(choix4!=3);
             }
             else{ color(6,6); cadre(1,70,0,57); cadre(71,164,0,28); cadre(71,164,28,57); color(7,0); gotoxy(28,25); puts("ACCESS DENIED!!"); color(0,0); system("pause"); system("cls");
             }
             break;
case 3:break;
}
}
}while(choix1!=3);
}
else{
          system("cls");
color(4,0); gotoxy(72,25); printf("INCORRECT PASSWORD");
color(0,0); system("pause"); system("cls"); color(7,0);
}
}while(s!=0);
}
