#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Date {
    char jour[3];
    char mois[3];
    char annee[5];
} date;

typedef struct Produit {
    char nom_produit[50];
    char reference[3];
    float montant;
    date Dateachat;
} produit;

typedef struct List {
    produit cellule;
    struct List* suiv;
} liste;

liste* cree() {
    return NULL;
}

int est_vide(liste* debut) {
    return (debut == NULL);
}

liste* cree_produit() {
    liste* newE = (liste*)malloc(sizeof(liste));
    if (newE == NULL) {
        printf("Erreur d'allocation.\n");
        return NULL;
    }

    printf("Saisir le nom du produit: ");
    scanf("%s", newE->cellule.nom_produit);
    printf("Entrez la reference du produit: ");
    scanf("%s", newE->cellule.reference);
    printf("Saisir le montant du produit: ");
    scanf("%f", &newE->cellule.montant);
    printf("Entrez la date: \n");
    printf("Entrez le jour: ");
    scanf("%s", newE->cellule.Dateachat.jour);
    printf("Entrez le mois: ");
    scanf("%s", newE->cellule.Dateachat.mois);
    printf("Entrez l'annee: ");
    scanf("%s", newE->cellule.Dateachat.annee);
    newE->suiv = NULL;
    return newE;
}

void afficher_produit(liste* produit) {
    printf("\nNom du produit: %s", produit->cellule.nom_produit);
    printf("\nReference du produit: %s", produit->cellule.reference);
    printf("\nMontant du produit: %.2f", produit->cellule.montant);
    printf("\nDate d'achat: %s/%s/%s\n", produit->cellule.Dateachat.jour, produit->cellule.Dateachat.mois, produit->cellule.Dateachat.annee);
}

liste* ajouter_debut(liste* debut) {
    liste* newE = cree_produit();
    if (newE == NULL) {
        return debut;
    }
    newE->suiv = debut;
    debut = newE;
    return debut;
}

liste* ajouter_fin(liste* debut) {
    liste* newE = cree_produit();
    if (newE == NULL) {
        return debut;
    }
    if (debut == NULL) {
        debut = newE;
    } else {
        liste* ptr = debut;
        while (ptr->suiv != NULL) {
            ptr = ptr->suiv;
        }
        ptr->suiv = newE;
    }
    return debut;
}

int longueur(liste* debut) {
    int lg = 0;
    liste* ptr = debut;
    while (ptr != NULL) {
        ptr = ptr->suiv;
        lg++;
    }
    return lg;
}

void filtrerdate(liste* debut, date dt) {
    liste* temp = debut;
    int trouve = 0;
    while (temp != NULL) {
        if (strcmp(temp->cellule.Dateachat.jour, dt.jour) == 0 &&
            strcmp(temp->cellule.Dateachat.mois, dt.mois) == 0 &&
            strcmp(temp->cellule.Dateachat.annee, dt.annee) == 0) {
            afficher_produit(temp);
            trouve = 1;
        }
        temp = temp->suiv;
    }
    if (!trouve) {
        printf("Aucun produit trouve pour la date specifiee.\n");
    }
}

liste* supprimer_debut(liste* debut) {
    if (debut == NULL) {
        printf("\nLa liste est vide.\n");
        return NULL;
    }
    liste* temp = debut;
    debut = debut->suiv;
    free(temp);
    return debut;
}

liste* supprimer_fin(liste* debut) {
    if (debut == NULL) {
        printf("\nLa liste est vide.\n");
        return NULL;
    }
    liste* ptr = debut;
    if (ptr->suiv == NULL) {
        free(ptr);
        return NULL;
    }
    while (ptr->suiv->suiv != NULL) {
        ptr = ptr->suiv;
    }
    free(ptr->suiv);
    ptr->suiv = NULL;
    return debut;
}

liste* rembourser(liste* debut, char* refer) {
    if (est_vide(debut)) {
        return debut;
    }
    liste* temp = debut;
    liste* prev = NULL;
    while (temp != NULL) {
        if (strcmp(temp->cellule.reference, refer) == 0) {
            if (prev == NULL) {
                debut = temp->suiv;
            } else {
                prev->suiv = temp->suiv;
            }
            free(temp);
            printf("Produit rembourse avec succes.\n");
            return debut;
        }
        prev = temp;
        temp = temp->suiv;
    }
    printf("Aucun produit trouve avec cette reference.\n");
    return debut;
}

void afficher_liste(liste* debut) {
    liste* ptr = debut;
    while (ptr != NULL) {
        afficher_produit(ptr);
        ptr = ptr->suiv;
    }
}

int main() {
    liste* debut = cree();
    int choix;
    date dt;
    char refer[3];

    do {
        printf("\n    GESTION STOCK    \n");
        printf("\n1. Ajouter un produit au debut\n");
        printf("\n2. Ajouter un produit a la fin\n");
        printf("\n3. Afficher la liste des produits\n");
        printf("\n4. Afficher le nombre de produits\n");
        printf("\n5. Filtrer par date\n");
        printf("\n6. Supprimer le premier produit\n");
        printf("\n7. Supprimer le dernier produit\n");
        printf("\n8. Rembourser un produit\n");
        printf("\n0. Fin\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                debut = ajouter_debut(debut);
                break;
            case 2:
                debut = ajouter_fin(debut);
                break;
            case 3:
                afficher_liste(debut);
                break;
            case 4:
                printf("Nombre de produits : %d\n", longueur(debut));
                break;
            case 5:
                printf("Entrez la date: ");
                scanf("%s %s %s", dt.jour, dt.mois, dt.annee);
                filtrerdate(debut, dt);
                break;
            case 6:
                debut = supprimer_debut(debut);
                break;
            case 7:
                debut = supprimer_fin(debut);
                break;
            case 8:
                printf("Entrez la reference du produit rembourser : ");
                scanf("%s", refer);
                debut = rembourser(debut, refer);
                break;
            case 0:
                printf("\nFin\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    return 0;
}
