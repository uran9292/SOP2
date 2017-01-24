#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>


struct stan
{
long mtype;
int robotnicy;
int lekka;
int ciezka;
int jazda;
int zloto;
short wynik1;
short wynik2;
short ID;
int result; // WIN = 2, LOSE = 1 , UNDEFINED = 0
int informacja;// 1 – zatak. Przeg, 2 – zaatak wyg, 3 -atak udany, 4- atak nieudany, 5 – za
//malo zasobow
} stan;
struct rozkaz
{
long mtype;
int ID;
int numer_roz; // 1- atak, 2 – lekka, 3- ciężka, 4 – jazda, 5 - robol
int num_lek;
int num_cie;
int num_kaw;
} rozkaz;

struct numer_gracza {
	long mtype;
	int numer;
};

int main()
{	
  
  struct stan resources;
  struct rozkaz order;
  struct numer_gracza moj_numer = {1, 0};
  key_t k = 1234;
  key_t k1 = 4321;
  
  
  int msgid1 = msgget(k, 0);
  int msgid2 = msgget(k1, 0);
  
  msgsnd(msgid1, &moj_numer, sizeof(int), 0);
  
  printf("Oczekiwanie na drugiego gracza...\n");
  
  msgrcv(msgid1, &moj_numer, sizeof(int), 2, 0);
  
  printf("Jestem graczem: %d\n", moj_numer.numer);

  order.mtype = 3;
  int numer_kolejki;
    if(moj_numer.numer == 1)
    {
      order.ID = 1;
      numer_kolejki = 1;
    }
    else if(moj_numer.numer == 2)
    {
      order.ID = 2;
      numer_kolejki = 2;
    }
  
  
  
  
  
  msgrcv(msgid2, &resources, sizeof(struct stan), numer_kolejki, 0);
  
  order.numer_roz = 0;
 
  
  if(fork() == 0)
  {
          
      while(1)
      {
// 	printf("Podaj rozkaz! ");
	scanf("%d", &order.numer_roz);
	if(order.numer_roz == 1)
	{
// 	  printf("Podaj ile wojsk wysłać! ");
	  scanf("%d %d %d", &order.num_lek, &order.num_cie, &order.num_kaw);
	}
	msgsnd(msgid2, &order, sizeof(struct rozkaz) - sizeof(long), 0);
	order.num_lek = 0;
	order.num_cie = 0;
	order.num_kaw = 0;

	
      }
      
  }
  else
  {
    
    while(1)
    {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
    msgrcv(msgid2, &resources, sizeof(struct stan), numer_kolejki, 0);
    
    printf("Złoto: %d, lekki %d, ciężki %d, jazda %d, robotnicy %d\n", resources.zloto, resources.lekka, resources.ciezka, resources.jazda, resources.robotnicy);
    printf("Wynik gracz 1 = %d || %d = gracz 2\n", resources.wynik1, resources.wynik2);
    
    if(resources.informacja == 5)
    {
      printf("Masz za mało zasobów");
    }
    else if(resources.informacja == 4)// 1 – zatak. Przeg, 2 – zaatak wyg, 3 -atak udany, 4- atak nieudany, 5 – za
//malo zasobow
    {
      printf("atak nieudany");
    }
    else if(resources.informacja == 3)
    {
      printf("atak udany");
    }
    else if(resources.informacja == 2)
    {
      printf("zostałeś zaatakowny i przegrałeś");
    }
    else if(resources.informacja == 1)
    {
      printf("zostałeś zaatakowany i sie obroniłeś");
    }
    resources.informacja = 0;
      if(resources.result == 1)
	{

	  printf("Przegrałeś\n");
  	  fflush(stdout);
	  kill(0, SIGKILL);
	  return 0;
	}
	if(resources.result == 2)
	{

	  printf("Wygrałeś\n");
	  fflush(stdout);
	  kill(0, SIGKILL);
	  return 0;
	}
    }
    
  
  }
  return 0;
}
