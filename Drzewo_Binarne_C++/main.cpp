#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

struct BST{
    int dane; //g³ówny korzeñ
    BST* lewa; //lewa strona
    BST* prawa; //prawa strona
};

typedef struct BST wezel;

void wyswietl(struct BST *korzen, int h)
{
    if (korzen != NULL)
    {
        wyswietl(korzen ->lewa, ++h);
        int i;
        for(i=1;i<h;i++)
        printf("...");
        printf("%d\n", korzen->dane);
        wyswietl(korzen->prawa, h++);
    }
}
//generowanie drzewa
wezel* utworzWezel(int n)
{
    wezel* nowywezel;
    nowywezel = (wezel*)malloc(sizeof(wezel));
    nowywezel -> dane = n;
    nowywezel -> lewa = nowywezel -> prawa = NULL;
    return nowywezel;
}
//funkcja odpowiadaj¹ca za wstawianie do drzewa kolejnych liczb
wezel* wstaw(wezel* korzen,int n)
{
    if(korzen==NULL)//jesli puste
    {
        korzen = utworzWezel(n); //ustaw korzen jako rodzica
    }
    else if(n<=korzen->dane)
    {
        korzen->lewa=wstaw(korzen->lewa,n); //jesli wieksze wstaw na lewo
    }
    else
    {
        korzen->prawa=wstaw(korzen->prawa,n); //jesli mniejsze wstaw na prawo
    }
    return korzen;
}

//funkcja szukajaca danej liczby w drzewie
int szukaj(wezel* korzen, int liczba)
{
    if(korzen==NULL) //jesli korzenia nie ma to zwracam 0
    {
        return 0;
    }
    else if(liczba==korzen->dane) //jest liczba jest w drzewie i jest korzeniem zwracam 1
    {
        return 1;
    }
    else if(liczba<=korzen->dane)
    {
        return szukaj(korzen->lewa,liczba); //jesli liczba jest w drzewie ale nie jest korzeniem ale jest wieksza od niego to szukam
    }
    else
        return szukaj(korzen->prawa,liczba); //tutaj szukam liczb mniejszych
}

//definiuje funkcje ktora szuka minimum
BST* szukamMinimum(BST* korzen)
{
 while(korzen->lewa != NULL)
 {
    korzen = korzen->lewa;
 }
 return korzen;
}

//fukcja ktora usuwa z drzewa
struct BST* usuwanie(struct BST* korzen, int dane)
{
    if(korzen == NULL)
        return korzen;
    else if(dane < korzen->dane)
        korzen->lewa = usuwanie(korzen->lewa,dane);
    else if(dane > korzen->dane)
        korzen->prawa = usuwanie(korzen->prawa,dane);
    else//w tym momencie usuwamy
    {
        if(korzen->lewa==NULL && korzen->prawa==NULL)
        {
            //nie ma dziecka !
            delete korzen; //usuwamy pamiec i oznaczamy root nullem
            korzen = NULL;
            return korzen;
        }
        else if(korzen->lewa==NULL)
        {
            // tylko jedno dziecko po lewej stronie
            struct BST *x = korzen;
            korzen = korzen -> prawa;
            delete x;
            return korzen;
        }
        else if(korzen->prawa==NULL)
        {
            // tylko jedno dziecko po prawej stronie
            struct BST *x = korzen;
            korzen = korzen -> lewa;
            delete x;
        }
        else
        {
            struct BST *x = szukamMinimum(korzen->prawa);
            korzen -> dane = x -> dane;
            korzen -> prawa = usuwanie(korzen->prawa,x->dane);
        }
    }
    return korzen;
};


int main()
{
    clock_t start,stop;
    double czas;
    wezel* korzen=NULL;
    srand(time(NULL));
    int i,j,x;

    korzen = wstaw(korzen, 50);
    //printf("ile razy ma sie wywolac");
    //scanf("%d",&x);
    //printf("ile razy ma sie wywolac");
    //for(j=0;j<5;j++){
        //printf("ile razy ma sie wywolac");
        //scanf("%d",&x);
        for(i=0;i<1000000;i++)
        {
            wstaw(korzen, rand()%100000+1);

        }
        //start = clock();
        //wyswietl(korzen, 0);
        //stop = clock();
        //czas = (double)(stop-start)/CLOCKS_PER_SEC;
        //printf("%d",czas);
    //}
    start = clock();
    for(i=0;i<1000000;i++)
    {
        szukaj(korzen,rand()%100000+1);
    }
    stop = clock();
    czas = (double)(stop-start)/CLOCKS_PER_SEC;
    printf("%f",czas,"s ");
    int n;
    char ch;
    //wyswietl(korzen, 0);
    printf("Drzewo binarne \n");
    printf("Aby zakonczyc dodawanie kolejnych liczb do drzewa wpisz n\n");
    printf("Wpisz liczbe i dodaj ja do drzewa: \n");
    do{
        scanf("%d",&n);
        korzen = wstaw(korzen,n);
        ch = getchar();
    }while(ch=='y'||ch!='n');
    int usun;
    do{
        printf("wpisz liczbe ktora ma byc usunieta z drzewa, aby zakonczyc wpisz 'n' ");
        scanf("%d",&usun);
        korzen = usuwanie(korzen,usun);
        ch = getchar();
    }while(ch!='n');
    int liczba;
    /*do{
        printf("Wpisz liczbe ktora ma byc szukana w drzewie, aby zakonczyc wpisz 'n': ");
        scanf("%d",&liczba);
        if(szukaj(korzen,liczba)==1)
        {
        printf("Ta liczba znajduje sie w drzewie.");
        }
        else if(szukaj(korzen,liczba)==0)
        {
        printf("Tej liczby nie ma w drzewie.");
        }
        else
        {
        printf("wpisz liczbe");
        }
        ch = getchar();
    }while(ch!='n');*/
    getchar();
    return 0;
}
