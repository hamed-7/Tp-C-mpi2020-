#include <stdio.h>
#include <malloc.h>
#include <string.h>

char io[100];

typedef struct
{
  char ville[31];
} DATA_VILLE;

typedef struct
{
  int code;
  char nom[31];
  char prenom[31];
  int age;
  char ville[30];
} DATA_PERSONNE;

struct liste_ville
{
  DATA_VILLE d;
  struct liste_ville *next;
};
typedef struct liste_ville LISTE_VILLE;

struct liste_personne
{
  DATA_PERSONNE d;
  struct liste_personne *next;
};
typedef struct liste_personne LISTE_PERSONNE;


int get_choix();
void view_ville(LISTE_VILLE *first);
void insert_ville(LISTE_VILLE **first, DATA_VILLE d);
DATA_VILLE get_data_ville(char *s);
LISTE_VILLE *load_ville();
LISTE_PERSONNE *load_personne();
DATA_PERSONNE get_data_personne(char *s);
void insert_personne(LISTE_PERSONNE **first, DATA_PERSONNE d);
void view_personne(LISTE_PERSONNE *first);
int get_code_personne();
void delete_personne(LISTE_PERSONNE **first, int code);


void main()
{
  LISTE_VILLE *first_ville;
  LISTE_PERSONNE *first_personne;
  int choix, code;

  first_ville = load_ville();
  first_personne = load_personne();
  while ((choix = get_choix()))
  {
    switch (choix)
    {
    case 1:
      view_ville(first_ville);
      break;
    case 2:
      view_personne(first_personne);
      break;

    case 3:
      code = get_code_personne();
      delete_personne(&first_personne, code);
      break;
      /*
       case 4:
         save_personne(first_personne);
         break;
      */
    }
  }

  //free_ville   (first_ville);
  //free_personne(first_personne);
}

LISTE_VILLE *load_ville()
{
  FILE        *fp;
  LISTE_VILLE *first;
  DATA_VILLE  d;
  char        s[100];

  fp=fopen("ville.txt","r");
  if(fp==NULL)
  {
    printf("\nProbleme Fichier Ville ");
    return(NULL);
  }

  for(first=NULL;fgets(s,100,fp);)
  {
    d=get_data_ville(s);
    insert_ville(&first,d);
  }
  return(first);

  
}

DATA_VILLE get_data_ville(char *s)
{
  DATA_VILLE d;

  memcpy(d.ville, s, 30);
  *(d.ville + 30) = '\0';
  return (d);
}

void insert_ville(LISTE_VILLE **first, DATA_VILLE d)
{
  LISTE_VILLE *p;
  p = (LISTE_VILLE *)malloc(sizeof(LISTE_VILLE));
  p->d = d;
  p->next = *first;
  *first = p;
}

void view_ville(LISTE_VILLE *first)
{
  if(first)
  {
    printf("\n%s", first->d.ville);
    view_ville(first->next);
  }
  else
  {
    printf("\n");
  }
}

int get_choix()
{
  int choix;

  printf("\n 1:Liste       Villes\n");
  printf("\n 2:Liste       Personnes\n");
  printf("\n 3:Suppression Personne\n");
  printf("\n 4:Sauvegarde  Personne\n");
  printf("\n 0:Quitte\n");

  gets(io);
  sscanf(io, "%d", &choix);
  return (choix);
}
LISTE_PERSONNE *load_personne()
{
  FILE *fp;
  LISTE_PERSONNE *first;
  DATA_PERSONNE d;
  char s[200];

  fp = fopen("personne.txt", "r");
  if (fp == NULL)
  {
    printf("\nProbleme Fichier Personne ");
    return (NULL);
  }

  for (first = NULL; fgets(s, 200, fp);)
  {
    d = get_data_personne(s);
    insert_personne(&first, d);
  }
  return (first);
}

DATA_PERSONNE get_data_personne(char *s)
{
  DATA_PERSONNE d;

  sscanf(s, "%3d", &d.code);

  memcpy(d.nom, s + 4, 30);
  *(d.nom + 30) = '\0';

  memcpy(d.prenom, s + 35, 30);
  *(d.prenom + 30) = '\0';

  sscanf(s + 66, "%2d", &d.age);

  memcpy(d.ville, s + 69, 30);
  *(d.ville + 30) = '\0';
  return (d);
}

void insert_personne(LISTE_PERSONNE **first, DATA_PERSONNE d)
{
  LISTE_PERSONNE *p;
  p = (LISTE_PERSONNE *)malloc(sizeof(LISTE_PERSONNE));
  p->d = d;
  p->next = *first;
  *first = p;
}

void view_personne(LISTE_PERSONNE *first)
{
  if(first)
  {
    printf("\n%3d %s %s %2d %s", first->d.code, first->d.nom, first->d.prenom, first->d.age, first->d.ville);
    view_personne(first->next);
  }
  else
  {
    printf("\n");
  }
}

int get_code_personne()
{
  int code;
  printf("\n Code Personne a Supprimer:");
  gets(io);
  sscanf(io, "%d", &code);
  return (code);
}

void delete_personne(LISTE_PERSONNE **first, int code)
{
  LISTE_PERSONNE *p;
  if (*first)
  {
    if ((*first)->d.code == code)
    {
      p = *first;
      *first = (*first)->next;
      free(p);
    }
    else
      delete_personne(&((*first)->next), code);
  }
}
