#include <stdio.h>
#include<stdlib.h>
typedef struct HorlogeScalaire
{
  int val;
} HorlogeScalaire;


typedef HorlogeScalaire * pHorlogeScalaire;

int
max(int a, int b)
{
  if (a <= b)
    return a;
  else
    return b;
}

HorlogeScalaire
new_horloge_scalaire()
{
  HorlogeScalaire h = {0};
  return h;
}

void
update_horloge_scalaire(pHorlogeScalaire hlocale, pHorlogeScalaire hmessage)
{
  hlocale->val = max(hlocale->val, hmessage->val);
}

int
comp_horloge_scalaire(pHorlogeScalaire hlocale, pHorlogeScalaire hmessage)
{
  return hlocale->val <= hmessage->val;
}

void
increment_horloge_scalaire(pHorlogeScalaire h)
{
  h->val++;
}

typedef struct HorlogeMatricielle
{
  int nsites;
  int* matrice;
} MatHorloge;

typedef MatHorloge * pMatHorloge;

MatHorloge
MatHorloge_new(int nsites)
{
  int* mat = malloc(sizeof(int)*nsites*nsites);
  MatHorloge h = {nsites, mat};
  return h;
}

