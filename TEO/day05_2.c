#include <stdio.h>
#include <stdbool.h>
#define BUFF_LEN 2048
#define RG_DEBUT(i) (liste_ranges[i].debut)
#define RG_FIN(i) (liste_ranges[i].debut + liste_ranges[i].longueur)

struct range {
  int debut;
  int longueur;
};

struct fonction {
  int in_debut;
  int out_debut;
  int longueur;
};

/* renvoie la nouvelle taille de la liste des ranges */
int appliquer_fonction (struct range liste_ranges[BUFF_LEN],
                         int liste_taille,
                         bool deja_traites[BUFF_LEN],
                         struct fonction fonction) {
  for (int i = 0; i < liste_taille; i++) {
    if (deja_traites[i] == false) {
      /* on découpe le range actuel pour matcher celui
       * défini par la fonction. On ajoute les nouveaux
       * ranges à la liste et on applique la fonction sur le
       * range courant si nécéssaire */

      if (RG_DEBUT(i) < fonction.in_debut) {
        if (RG_FIN(i) > (fonction.in_debut + fonction.longueur)) {
          /* le range de la fonction est inclu
           * dans le range actuel : découpage */
        }
        else if (RG_FIN(i) > fonction.in_debut) {
          /* intersection avec la fonction : découpage */
        }
      }
    }
  }
}

int main() {
  FILE* fd = fopen("input.txt", "r");

  struct range liste_ranges[BUFF_LEN];
  /* permet de savoir qu'on a déjà appliqué
  * la fonction de la passe courante au range d'indice i */
  bool deja_traites[BUFF_LEN] = {false};
  int liste_taille = 0;

  char lettre;
  do {
    lettre = fgetc(fd);
  }while (lettre != EOF);
}
