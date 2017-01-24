#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>





 int shmid1;
 int shmid2;

 int semid1;
 int semid2;
 int semid11;
 int semid22;
  void podnies(int);
  void oposc(int);
void walka(int*, int*, int*, int*, int*, int*, short*, short*);
  
 
  struct sembuf operacja;
  
void podnies(int id) //to V
{
	    operacja.sem_num = 0;
            operacja.sem_op = 1;
            operacja.sem_flg = 0;
	    semop(id, &operacja, 1);

}
void oposc(int id) //to P
{
	    operacja.sem_num = 0;
            operacja.sem_op = -1;
            operacja.sem_flg = 0;
	    semop(id, &operacja, 1);
             
}

void walka(int *atak_lekka, int *atak_ciezka, int *atak_jazda, int *obrona_lekka, int *obrona_ciezka, int *obrona_jazda, short *win, short *win2)
{
  float sila_atk_1 = (*atak_lekka) * 1 + (*atak_ciezka) * 1.5 + (*atak_jazda) * 3.5;
  float sila_obr_2 = (*obrona_lekka) * 1.2 + (*obrona_ciezka) * 3 + (*obrona_jazda) * 1.2;
  float sila_obr_1 = (*atak_lekka) * 1.2 + (*atak_ciezka) * 3 + (*atak_jazda) * 1.2;
  float sila_atk_2 = (*obrona_lekka) * 1 + (*obrona_ciezka) * 1.5 + (*obrona_jazda) * 3.5;
  

    if(sila_atk_1 - sila_obr_2 > 0)
    {
      *obrona_lekka = 0;
      *obrona_ciezka = 0;
      *obrona_jazda = 0;
      *win += 1; //zwiększenie wartości wygranych w strukturze gracza atakującego
      *win2 += 1; //zwiększenie wartości wygranych gracza atakującego w strukturze gracza broniącego
      printf("atakujący zdobywa punkt\n");
    }
    else
    {
      *obrona_lekka = (int)((*obrona_lekka) - ((*obrona_lekka) * (sila_atk_1 / sila_obr_2)));
      *obrona_ciezka = (int)((*obrona_ciezka) - ((*obrona_ciezka) * (sila_atk_1 / sila_obr_2)));
      *obrona_jazda = (int)((*obrona_jazda) - ((*obrona_jazda) * (sila_atk_1 / sila_obr_2)));
      if(*obrona_lekka < 0) *obrona_lekka = 0;
      if(*obrona_ciezka < 0) *obrona_ciezka = 0;
      if(&obrona_jazda < 0) *obrona_jazda = 0;
    }

    if(sila_atk_2 - sila_obr_1 > 0)
    {
      *atak_lekka = 0;
      *atak_ciezka = 0;
      *atak_jazda = 0;
    }
    else
    {
      *atak_lekka = (int)((*atak_lekka) - ((*atak_lekka) * (sila_atk_2 / sila_obr_1)));
      *atak_ciezka = (int)((*atak_ciezka) - ((*atak_ciezka) * (sila_atk_2 / sila_obr_1)));
      *atak_jazda = (int)((*atak_jazda) - ((*atak_jazda) * (sila_atk_2 / sila_obr_1)));
      if(*atak_lekka < 0) *atak_lekka = 0;
      if(*atak_ciezka < 0) *atak_ciezka = 0;
      if(*atak_jazda < 0) *atak_jazda = 0;
    }

  
  
}

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
int informacja;// 1 – zatak. Przeg, 2 – zaatak wyg, 3 -atak udany, 4- atak nieudany, 5 – za malo zasobow
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
} numer_gracza;
 
 
int main()
{
  int shmid1 = shmget(777, sizeof(struct stan), IPC_CREAT | 0666);
  int shmid2 = shmget(888, sizeof(struct stan), IPC_CREAT | 0666);
  int semid1 = semget(111, 1, IPC_CREAT | 0600); //gracz 1 budowa
  int semid2 = semget(222, 1, IPC_CREAT | 0600);	//gracz 2 budowa
  int semid11 = semget(333, 1, IPC_CREAT | 0600); //gracz 1 stan
  int semid22 = semget(444, 1, IPC_CREAT | 0600);	//gracz 2 stan
  
  char* addr1;
  char* addr2;
  struct stan resources_1;
  struct stan resources_2;
  struct rozkaz order;
  struct numer_gracza gracz_1;
  struct numer_gracza gracz_2;
  key_t k = 1234;
  key_t k1 = 4321;

  
  gracz_1.numer = 1;
  gracz_1.mtype = 1;
  gracz_2.numer = 2;
  gracz_2.mtype = 1;
  
  int msgid1;
  int msgid2;
  
  short pkt1 = 0;
  short pkt2 = 0;
  
  msgid1 = msgget(k, IPC_CREAT | 0600);
  msgid2 = msgget(k1, IPC_CREAT | 0600);
  
  
  msgrcv(msgid1, &gracz_1, sizeof(int), 1, 0);
  msgrcv(msgid1, &gracz_2, sizeof(int), 1, 0);
  gracz_1.numer = 1;
  gracz_1.mtype = 2; 
  gracz_2.numer = 2;
  gracz_2.mtype = 2;
  msgsnd(msgid1, &gracz_1, sizeof(int), 0);
  msgsnd(msgid1, &gracz_2, sizeof(int), 0);
   
  
  resources_1.lekka = 0;
  resources_1.ciezka = 0;
  resources_1.jazda = 0;
  resources_1.robotnicy = 0;
  resources_1.zloto = 300;
  resources_1.mtype = 1;
  resources_1.result = 0;
  resources_1.wynik1 = 0;
  resources_1.wynik2 = 0;
   resources_1.informacja = 0;
  
  resources_2.lekka = 0;
  resources_2.ciezka = 0;
  resources_2.jazda = 0;
  resources_2.robotnicy = 0;
  resources_2.zloto = 300;
  resources_2.mtype = 2;
  resources_2.result = 0;
  resources_2.wynik1 = 0;
  resources_2.wynik2 = 0;
   resources_2.informacja = 0;
 
//  struct stan resources_test;
  

  
  addr1 = shmat(shmid1, 0, 0);  
  addr2 = shmat(shmid2, 0, 0);
  semctl(semid1, 0, SETVAL, 1);
  semctl(semid11, 0, SETVAL, 1);
  semctl(semid2, 0, SETVAL, 1);
  semctl(semid22, 0, SETVAL, 1);
  
  memcpy(addr1, &resources_1, sizeof(resources_1)); //przekazuje do shm początkowe wartości
  memcpy(addr2, &resources_2, sizeof(resources_2));
  
//   memcpy(addr1,&resources_1,sizeof(resources_1));
//   memcpy(&resources_test,addr1,sizeof(resources_test));
//   printf("%d", resources_test.zloto);
  
  
 
  
  msgsnd(msgid2, &resources_1, sizeof(struct stan) - sizeof(long), 0);
  msgsnd(msgid2, &resources_2, sizeof(struct stan) - sizeof(long), 0);
  
  if(fork() == 0)
  {
    
    while(1)
    {
     
      msgrcv(msgid2, &order, sizeof(struct rozkaz) - sizeof(long), 3, 0);
      
//      printf("gracz %d wybrał opcję %d\n", order.ID, order.numer_roz);
//      fflush(stdout);
      
      
	if(order.ID == 1)
	{
	switch(order.numer_roz)
	{
	  case 1:
	    if(fork() == 0)
	      {
	    
	    if(order.num_lek == 0 && order.num_cie == 0 && order.num_kaw == 0) break;
	    
	    
	    oposc(semid11);
	    memcpy(&resources_1, addr1, sizeof(resources_1));
	   	    
	    if(resources_1.lekka <= order.num_lek)
	    {
	      order.num_lek = resources_1.lekka;
	      resources_1.lekka = 0;
	    }
	    else
	    {
	      resources_1.lekka -= order.num_lek;
	    }
	    if(resources_1.ciezka <= order.num_cie)
	    {
	      order.num_cie = resources_1.ciezka;
	      resources_1.ciezka = 0;
	    }
	    else
	    {
	      resources_1.ciezka -= order.num_cie;
	    }
	    if(resources_1.jazda <= order.num_kaw)
	    {
	      order.num_kaw = resources_1.jazda;
	      resources_1.jazda = 0;
	    }
	    else
	    {
	      resources_1.jazda -= order.num_kaw;
	    }
	    memcpy(addr1, &resources_1, sizeof(resources_1));
	    
	    podnies(semid11);
	    
	    sleep(5);
	    
	   
	    oposc(semid22);
	    memcpy(&resources_2, addr2, sizeof(resources_2));
	    walka(&order.num_lek, &order.num_cie, &order.num_kaw, &resources_2.lekka, &resources_2.ciezka, &resources_2.jazda, &pkt1, &resources_2.wynik2);
	    memcpy(addr2, &resources_2, sizeof(resources_2));
	    
	    podnies(semid22);
	    
	    
	    oposc(semid11);
	    memcpy(&resources_1, addr1, sizeof(resources_1));
	    resources_1.wynik1 += pkt1;
	    printf("%d\n", resources_1.wynik1);
	    resources_1.lekka += order.num_lek;
	    resources_1.ciezka += order.num_cie;
	    resources_1.jazda += order.num_kaw;
	    memcpy(addr1, &resources_1, sizeof(resources_1));
	    
	    podnies(semid11);
	      exit(0);
	      }
	    break;
	      
	  case 2:
	    if(fork() == 0)
	      {
		
		
	      
	      
	      oposc(semid11);
	      memcpy(&resources_1, addr1, sizeof(resources_1));
	      memcpy(addr1, &resources_1, sizeof(resources_1));
	      podnies(semid11);
	      
	    if(resources_1.zloto >= 100)
	    {  
	      
	      oposc(semid1);
	      oposc(semid11);
	      memcpy(&resources_1, addr1, sizeof(resources_1));
	      resources_1.zloto -= 100;
	      memcpy(addr1, &resources_1, sizeof(resources_1));
	      podnies(semid1);
	      podnies(semid11);
	      
	      sleep(2);
	      oposc(semid1);
	      oposc(semid11);
	      memcpy(&resources_1, addr1, sizeof(resources_1));
	      resources_1.lekka += 1;
	      memcpy(addr1, &resources_1, sizeof(resources_1));
	      podnies(semid1);
	      podnies(semid11);
	      
	    }
	    else
	    {
	        
	      oposc(semid11);
	      memcpy(&resources_1, addr1, sizeof(resources_1));
	      resources_1.informacja = 5;
	      memcpy(addr1, &resources_1, sizeof(resources_1));
	      podnies(semid11);
	    }
	      
	      exit(0);
	      }
	    break;
	      
	  case 3:
	    if(fork() == 0)
	      {
	      
	      oposc(semid11);
	      memcpy(&resources_1, addr1, sizeof(resources_1));
	      memcpy(addr1, &resources_1, sizeof(resources_1));
	      podnies(semid11);
	      
	    if(resources_1.zloto >= 250)
	    {
	      oposc(semid1);
	      oposc(semid11);
	      memcpy(&resources_1, addr1, sizeof(resources_1));
	      resources_1.zloto -= 250;
	      memcpy(addr1, &resources_1, sizeof(resources_1));
	      podnies(semid1);
	      podnies(semid11);
	      sleep(3);
	      oposc(semid1);
	      oposc(semid11);
	      memcpy(&resources_1, addr1, sizeof(resources_1));
	      resources_1.ciezka += 1;
	      memcpy(addr1, &resources_1, sizeof(resources_1));
	      podnies(semid1);
	      podnies(semid11);
	    }
	     else
	    {
	      oposc(semid11);
	      memcpy(&resources_1, addr1, sizeof(resources_1));
	      resources_1.informacja = 5;
	      memcpy(addr1, &resources_1, sizeof(resources_1));
	      podnies(semid11);
	    }
	      exit(0);
	      }
	    break;
	      
	  case 4:
	    if(fork() == 0)
	      {

	      oposc(semid11);
	      memcpy(&resources_1, addr1, sizeof(resources_1));
	      memcpy(addr1, &resources_1, sizeof(resources_1));
	      podnies(semid11);
	    if(resources_1.zloto >= 550)
	    {
	      oposc(semid1);
	      oposc(semid11);
	      memcpy(&resources_1, addr1, sizeof(resources_1));
	      resources_1.zloto -= 550;
	      memcpy(addr1, &resources_1, sizeof(resources_1));
	      podnies(semid1);
	      podnies(semid11);
	      sleep(5);
	      oposc(semid1);
	      oposc(semid11);
	      memcpy(&resources_1, addr1, sizeof(resources_1));
	      resources_1.jazda += 1;
	      memcpy(addr1, &resources_1, sizeof(resources_1));
	      podnies(semid1);
	      podnies(semid11);
	    }
	     else
	    {
	     oposc(semid11);
	      memcpy(&resources_1, addr1, sizeof(resources_1));
	      resources_1.informacja = 5;
	      memcpy(addr1, &resources_1, sizeof(resources_1));
	      podnies(semid11);
	    }
	      exit(0);
	      }
	    break;
	      
	  case 5:
	    if(fork() == 0)
	      {
	       oposc(semid11);
	      memcpy(&resources_1, addr1, sizeof(resources_1));
	      memcpy(addr1, &resources_1, sizeof(resources_1));
	      podnies(semid11);
	    
	    if(resources_1.zloto >= 150)
	    {
	      oposc(semid1);
	      oposc(semid11);
	      memcpy(&resources_1, addr1, sizeof(resources_1));
	      resources_1.zloto -= 150;
	      memcpy(addr1, &resources_1, sizeof(resources_1));
	      podnies(semid1);
	      podnies(semid11);
	      sleep(2);
	      oposc(semid1);
	      oposc(semid11);
	      memcpy(&resources_1, addr1, sizeof(resources_1));
	      resources_1.robotnicy += 1;
	      memcpy(addr1, &resources_1, sizeof(resources_1));
	      podnies(semid1);
	      podnies(semid11);
	    }
	     else
	    {
	      oposc(semid11);
	      memcpy(&resources_1, addr1, sizeof(resources_1));
	      resources_1.informacja = 5;
	      memcpy(addr1, &resources_1, sizeof(resources_1));
	      podnies(semid11);
	    }
	      exit(0);
	      }
	    break;
	   
	  
	}
	printf("gracz %d wybrał opcję %d\n", order.ID, order.numer_roz);
	fflush(stdout);
	  
	msgsnd(msgid2, &resources_1, sizeof(resources_1) - sizeof(long), 0);
	
	      oposc(semid11);
	      memcpy(&resources_1, addr1, sizeof(resources_1));
	      resources_1.informacja = 0;
	      memcpy(addr1, &resources_1, sizeof(resources_1));
	      podnies(semid11);
	  
	}
    
    
	  else
	  {
	
	  
	  switch(order.numer_roz)
	{
	  case 1:
	    if(fork() == 0)
	    {
	    
	    oposc(semid22);
	    memcpy(&resources_2, addr2, sizeof(resources_2));
	    
	    if(resources_2.lekka <= order.num_lek)
	    {
	      order.num_lek = resources_2.lekka;
	      resources_2.lekka = 0;
	    }
	    else
	    {
	      resources_2.lekka -= order.num_lek;
	    }
	    if(resources_2.ciezka <= order.num_cie)
	    {
	      order.num_cie = resources_2.ciezka;
	      resources_2.ciezka = 0;
	    }
	    else
	    {
	      resources_2.ciezka -= order.num_cie;
	    }
	    if(resources_2.jazda <= order.num_kaw)
	    {
	      order.num_kaw = resources_2.jazda;
	      resources_2.jazda = 0;
	    }
	    else
	    {
	      resources_2.jazda -= order.num_kaw;
	    }
	    memcpy(addr2, &resources_2, sizeof(resources_2));
	    
	    podnies(semid22);
	    
	    sleep(5);
	    
	   
	    oposc(semid11);
	    memcpy(&resources_1, addr1, sizeof(resources_1));
	    walka(&order.num_lek, &order.num_cie, &order.num_kaw, &resources_1.lekka, &resources_1.ciezka, &resources_1.jazda, &pkt2, &resources_1.wynik2);
	    printf("wynik 2 = %d\n", pkt2);
	    memcpy(addr1, &resources_1, sizeof(resources_1));
	    podnies(semid11);
	    
	    
	    oposc(semid22);
	    memcpy(&resources_2, addr2, sizeof(resources_2));
	    resources_2.wynik1 += pkt2;
	    printf("%d\n", resources_2.wynik1); 
	    resources_2.lekka += order.num_lek;
	    resources_2.ciezka += order.num_cie;
	    resources_2.jazda += order.num_kaw;
	    memcpy(addr2, &resources_2, sizeof(resources_2));
	    podnies(semid22);
	    exit(0);
	    }
	    break;
	    
	  case 2:
	      if(fork() == 0)
	      {

	      oposc(semid22);
	      memcpy(&resources_2, addr2, sizeof(resources_2));
	      memcpy(addr2, &resources_2, sizeof(resources_2));
	      podnies(semid22);
	    
	    if(resources_2.zloto >= 100)
	    {  
	      oposc(semid2);
	      oposc(semid22);
	      memcpy(&resources_2, addr2, sizeof(resources_2));
	      resources_2.zloto -= 100;
	      memcpy(addr2, &resources_2, sizeof(resources_2));
	      podnies(semid2);
	      podnies(semid22);
	      sleep(2);
	      oposc(semid2);
	      oposc(semid22);
	      memcpy(&resources_2, addr2, sizeof(resources_2));
	      resources_2.lekka += 1;
	      memcpy(addr2, &resources_2, sizeof(resources_2));
	      podnies(semid2);
	      podnies(semid22);
	    }
	     else
	    {
	      oposc(semid22);
	      memcpy(&resources_2, addr2, sizeof(resources_2));
	      resources_2.informacja = 5;
	      memcpy(addr2, &resources_2, sizeof(resources_2));
	      podnies(semid22);
	    }
	      exit(0);
	      }
	    break;
	      
	  case 3:
	    if(fork() == 0)
	      {
	      oposc(semid22);
	      memcpy(&resources_2, addr2, sizeof(resources_2));
	      memcpy(addr2, &resources_2, sizeof(resources_2));
	      podnies(semid22);
	    
	    
	    if(resources_2.zloto >= 250)
	    {
	      oposc(semid2);
	      oposc(semid22);
	      memcpy(&resources_2, addr2, sizeof(resources_2));
	      resources_2.zloto -= 250;
	      memcpy(addr2, &resources_2, sizeof(resources_2));
	      podnies(semid2);
	      podnies(semid22);
	      sleep(3);
	      oposc(semid2);
	      oposc(semid22);
	      memcpy(&resources_2, addr2, sizeof(resources_2));
	      resources_2.ciezka += 1;
	      memcpy(addr2, &resources_2, sizeof(resources_2));
	      podnies(semid2);
	      podnies(semid22);
	    }	
	      else
	    {
	      oposc(semid22);
	      memcpy(&resources_2, addr2, sizeof(resources_2));
	      resources_2.informacja = 5;
	      memcpy(addr2, &resources_2, sizeof(resources_2));
	      podnies(semid22);
	    }
	      exit(0);
	      }
	    break;
	      
	  case 4:
	    if(fork() == 0)
	      {
	      oposc(semid22);
	      memcpy(&resources_2, addr2, sizeof(resources_2));
	      memcpy(addr2, &resources_2, sizeof(resources_2));
	      podnies(semid22);
	    
	    
	    if(resources_2.zloto >= 550)
	    {
	      oposc(semid2);
	      oposc(semid22);
	      memcpy(&resources_2, addr2, sizeof(resources_2));
	      resources_2.zloto -= 550;
	      memcpy(addr2, &resources_2, sizeof(resources_2));
	      podnies(semid2);
	      podnies(semid22);
	      sleep(5);
	      oposc(semid2);
	      oposc(semid22);
	      memcpy(&resources_2, addr2, sizeof(resources_2));
	      resources_2.jazda += 1;
	      memcpy(addr2, &resources_2, sizeof(resources_2));
	      podnies(semid2);
	      podnies(semid22);
	    }
	      else
	    {
	      oposc(semid22);
	      memcpy(&resources_2, addr2, sizeof(resources_2));
	      resources_2.informacja = 5;
	      memcpy(addr2, &resources_2, sizeof(resources_2));
	      podnies(semid22);
	    }
	      exit(0);
	      }
	    break;
	      
	  case 5:
	    if(fork() == 0)
	      {
	     oposc(semid22);
	      memcpy(&resources_2, addr2, sizeof(resources_2));
	      memcpy(addr2, &resources_2, sizeof(resources_2));
	      podnies(semid22);
	    
	    
	    if(resources_2.zloto >= 150)
	    {
	      oposc(semid2);
	      oposc(semid22);
	      memcpy(&resources_2, addr2, sizeof(resources_2));
	      resources_2.zloto -= 150;
	      memcpy(addr2, &resources_2, sizeof(resources_2));
	      podnies(semid2);
	      podnies(semid22);
	      sleep(2);
	      oposc(semid2);
	      oposc(semid22);
	      memcpy(&resources_2, addr2, sizeof(resources_2));
	      resources_2.robotnicy += 1;
	      memcpy(addr2, &resources_2, sizeof(resources_2));
	      podnies(semid2);
	      podnies(semid22);
	    }
	      else
	    {
	      oposc(semid22);
	      memcpy(&resources_2, addr2, sizeof(resources_2));
	      resources_2.informacja = 5;
	      memcpy(addr2, &resources_2, sizeof(resources_2));
	      podnies(semid22);
	    }
	      exit(0);
	      }
	    break;
	      
	
	}
	   printf("gracz %d wybrał opcję %d\n", order.ID, order.numer_roz);
	   fflush(stdout);
	    
	  msgsnd(msgid2, &resources_2, sizeof(resources_2) - sizeof(long), 0);
	  
	  
	      oposc(semid22);
	      memcpy(&resources_2, addr2, sizeof(resources_2));
	      resources_2.informacja = 0;
	      memcpy(addr2, &resources_2, sizeof(resources_2));
	      podnies(semid22);
	}
	  
// 	printf("jestem tutaj!\n");   
      
      
//       else 
//       wait(0);
      }
  }
  else
  {
    if(fork())
    {
      while(1)
      {
// 	printf("ten proces działa");
	
	oposc(semid11);
	memcpy(&resources_1, addr1, sizeof(resources_1));
	resources_1.zloto += 50 + resources_1.robotnicy * 5;
	if(resources_1.wynik1 == 5)
      {
	resources_1.result = 2;
	resources_2.result = 1;
	printf("wygrał gracz numer 1");
	msgsnd(msgid2, &resources_1, sizeof(resources_1) - sizeof(long), 0);
	msgsnd(msgid2, &resources_2, sizeof(resources_2) - sizeof(long), 0);
	msgctl(msgid1, IPC_RMID, NULL);
	msgctl(msgid2, IPC_RMID, NULL);
// 	semctl(semid1, 0, IPC_RMID);
// 	semctl(semid11, 0, IPC_RMID);
// 	semctl(semid2, 0, IPC_RMID);
// 	semctl(semid22, 0, IPC_RMID);
	kill(0, SIGKILL);
	return 0;
      }
	memcpy(addr1, &resources_1, sizeof(resources_1));
	
	podnies(semid11);
	 msgsnd(msgid2, &resources_1, sizeof(resources_1) - sizeof(long), 0);
	sleep(1);
// 	fflush(stdout);
      }
    }
    else
    {
      while(1)
      {
	
	oposc(semid22);
	memcpy(&resources_2, addr2, sizeof(resources_2));
	resources_2.zloto += 50 + resources_2.robotnicy * 5;
	if(resources_2.wynik1 == 5)
      {
	resources_1.result = 1;
	resources_2.result = 2;
	printf("wygrał gracz numer 2");
	msgsnd(msgid2, &resources_2, sizeof(resources_2) - sizeof(long), 0);
	msgsnd(msgid2, &resources_1, sizeof(resources_1) - sizeof(long), 0);
	msgctl(msgid1, IPC_RMID, NULL);
	msgctl(msgid2, IPC_RMID, NULL);
// 	semctl(semid1, 0, IPC_RMID);
// 	semctl(semid11, 0, IPC_RMID);
// 	semctl(semid2, 0, IPC_RMID);
// 	semctl(semid22, 0, IPC_RMID);
	kill(0, SIGKILL);
	return 0;
      }
	memcpy(addr2, &resources_2, sizeof(resources_2));
	
	podnies(semid22);
	msgsnd(msgid2, &resources_2, sizeof(resources_2) - sizeof(long), 0);
	sleep(1);
      }
    }
    }
  
  
  wait(0);
  
  semctl(semid1, 0, IPC_RMID);
  semctl(semid11, 0, IPC_RMID);
  semctl(semid2, 0, IPC_RMID);
  semctl(semid22, 0, IPC_RMID);
  
  return 0;
}
