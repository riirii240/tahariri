#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contratLocation {
    int numContrat;
    int idVoiture;
    int idClient;
    char debut[11];
    char fin[11];
    int cout;
} contrat;

typedef struct Client {
    int idClient;
    char nom[20];
    char prenom[20];
    int cin;
    char adresse[15];
    int telephone;
} client;

typedef struct Voiture {
    int idVoiture;
    char marque[15];
    char nom[15];
    char transmission[50];
    char couleur[7];
    int nbplaces;
    int prixJour;
    char EnLocation[4];
} voiture;

void menu();
void Gestion_Client();
void Gestion_Voitures();
void Gestion_Location();
int checkVoiture(int b);
void affichVoitures();
voiture infoVoiture();
void suppVoiture();
void modifierVoiture();
void ajouterVoiture();
int checkClient(int a);
void afficheClient();
client infoClient();
void suppClient();
void modifierClient();
void ajouterClient();
void visualiserContrat(FILE *F3, int num);
void louerVoiture(FILE *F1, FILE *F3);
void retournerVoiture(FILE *F3, FILE *F5, int num);
void modifierContrat();
void supprimerContrat(FILE *F3, int num);

void menu() {
    int choix;
    do {
        printf("\n                             \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
        printf("\n                             \xb3 Menu Principale \xb3");
        printf("\n                             \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
        printf("\n\n");
        printf("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
        printf("\n               \xba                                              \xba");
        printf("\n               \xba    Gestion clients.......................1   \xba");
        printf("\n               \xba    Gestion voitures......................2   \xba");
        printf("\n               \xba    Gestion locations.....................3   \xba");
        printf("\n               \xba    Quitter...............................9   \xba");
        printf("\n               \xba                                              \xba");
        printf("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
        printf("\n\n                                Votre choix  :  ");
        scanf("%d", &choix);
        printf("\n\n");

        switch (choix) {
            case 1:
                Gestion_Client();
                break;
            case 2:
                Gestion_Voitures();
                break;
            case 3:
                Gestion_Location();
                break;
            case 9:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide!\n");
                break;
        }
    } while (choix != 9);
}

void afficheClient() {
    FILE *F;
    client c;
    F = fopen("clients.csv", "r");

    printf("idClient,nom,prenom,cin,adresse,telephone\n");

    while (fscanf(F, "%d,%[^,],%[^,],%d,%[^,],%d\n", &c.idClient, c.nom, c.prenom, &c.cin, c.adresse, &c.telephone) != EOF) {
        printf("%d,%s,%s,%d,%s,%d\n", c.idClient, c.nom, c.prenom, c.cin, c.adresse, c.telephone);
    }
    fclose(F);
    menu();
}

client infoClient() {
    client x;
    printf("saisir idClient: "); scanf("%d", &x.idClient);
    printf("saisir le nom: "); scanf("%s", x.nom);
    printf("saisir le prenom: "); scanf("%s", x.prenom);
    printf("saisir le cin: "); scanf("%d", &x.cin);
    printf("saisir l'adresse: "); scanf("%s", x.adresse);
    printf("saisir le telephone: "); scanf("%d", &x.telephone);

    return x;
}

void suppClient() {
    int x;
    printf("saisir le id du client pour le supprimer: ");
    scanf("%d", &x);
    if (checkClient(x)) {
        FILE *F, *F1;
        client c;
        F = fopen("clients.csv", "r");
        F1 = fopen("temp_clients.csv", "w");
        while (fscanf(F, "%d,%[^,],%[^,],%d,%[^,],%d\n", &c.idClient, c.nom, c.prenom, &c.cin, c.adresse, &c.telephone) != EOF) {
            if (x != c.idClient) {
                fprintf(F1, "%d,%s,%s,%d,%s,%d\n", c.idClient, c.nom, c.prenom, c.cin, c.adresse, c.telephone);
            }
        }
        fclose(F);
        fclose(F1);
        remove("clients.csv");
        rename("temp_clients.csv", "clients.csv");
        printf("la suppression est bien faite\n");
    }
    menu();
}

void modifierClient() {
    FILE *F, *F1;
    client c;
    int x;
    printf("saisir le idClient: ");
    scanf("%d", &x);
    if (checkClient(x)) {
        F = fopen("clients.csv", "r");
        F1 = fopen("temp_clients.csv", "w");
        while (fscanf(F, "%d,%[^,],%[^,],%d,%[^,],%d\n", &c.idClient, c.nom, c.prenom, &c.cin, c.adresse, &c.telephone) != EOF) {
            if (c.idClient == x) {
                printf("pour modifier ce client\n");
                c = infoClient();
            }
            fprintf(F1, "%d,%s,%s,%d,%s,%d\n", c.idClient, c.nom, c.prenom, c.cin, c.adresse, c.telephone);
        }
        fclose(F);
        fclose(F1);
        remove("clients.csv");
        rename("temp_clients.csv", "clients.csv");
        printf("la modification est bien faite");
    }
    menu();
}

void ajouterClient() {
    FILE *F;
    client c;
    F = fopen("clients.csv", "a");
    c = infoClient();
    fprintf(F, "%d,%s,%s,%d,%s,%d\n", c.idClient, c.nom, c.prenom, c.cin, c.adresse, c.telephone);
    fclose(F);
    printf("le client est ajouté\n");
    menu();
}

void Gestion_Client() {
    int x;
    do {
        printf("\n                             \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
        printf("\n                             \xb3 Gestion client  \xb3");
        printf("\n                             \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
        printf("\n\n");
        printf("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
        printf("\n               \xba                                              \xba");
        printf("\n               \xba    liste des clients.....................1   \xba");
        printf("\n               \xba    ajouter client........................2   \xba");
        printf("\n               \xba    modifier client.......................3   \xba");
        printf("\n               \xba    supprimer client......................4   \xba");
        printf("\n               \xba    Retour................................5   \xba");
        printf("\n               \xba                                              \xba");
        printf("\n               \xba                                              \xba");
        printf("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
        printf("\n\n                                Votre choix  :  ");
        scanf("%d", &x);
    } while (x <= 0 || x > 5);

    switch (x) {
        case 1:
            afficheClient();
            break;
        case 2:
            ajouterClient();
            break;
        case 3:
            modifierClient();
            break;
        case 4:
            suppClient();
            break;
        case 5:
            menu();
            break;
        default:
            printf("error!");
            break;
    }
}

int checkVoiture(int b) {
    FILE *F;
    voiture v1;
    int i = 0;
    F = fopen("voitures.csv", "r");

    while (fscanf(F, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%[^,]\n", &v1.idVoiture, v1.marque,v1.transmission, v1.nom, v1.couleur, &v1.nbplaces, &v1.prixJour, v1.EnLocation) != EOF) {
        if (v1.idVoiture == b) {
            i = 1;
            break;
        }
    }
    if (i == 0) { printf("\nCette voiture n'existe pas"); }
    fclose(F);
    return i;
}

void affichVoitures() {
    FILE *F;
    voiture v1;
    F = fopen("voitures.csv", "r");

    printf("idVoiture,marque,nom,couleur,nbplaces,prixJour,EnLocation\n");

    while (fscanf(F, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%[^,]\n", &v1.idVoiture, v1.marque, v1.nom, v1.couleur,v1.transmission, &v1.nbplaces, &v1.prixJour, v1.EnLocation) != EOF) {
        printf("%d,%s,%s,%s,,%s,%d,%d,%s\n", v1.idVoiture, v1.marque, v1.nom, v1.couleur,v1.transmission, v1.nbplaces, v1.prixJour, v1.EnLocation);
    }
    fclose(F);
    menu();
}

voiture infoVoiture() {
    voiture x;
    printf("saisir idvoitures: "); scanf("%d", &x.idVoiture);
    printf("saisir le nom: "); scanf("%s", x.nom);
    printf("saisir la marque: "); scanf("%s", x.marque);
    printf("saisir la couleur: "); scanf("%s", x.couleur);
     printf("saisir la transmission: "); scanf("%s", x.transmission);
    printf("saisir le nombre de places: "); scanf("%d", &x.nbplaces);
    printf("saisir le prix du jour: "); scanf("%d", &x.prixJour);
    printf("En location: "); scanf("%s", x.EnLocation);

    return x;
}

void suppVoiture() {
    int x;
    printf("saisir le id du voitures pour le supprimer: ");
    scanf("%d", &x);
    if (checkVoiture(x)) {
        FILE *F, *F2;
        voiture v1;
        F = fopen("voitures.csv", "r");
        F2 = fopen("temp_voitures.csv", "w");
        while (fscanf(F, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%[^,]\n", &v1.idVoiture, v1.marque, v1.nom,v1.transmission, v1.couleur, &v1.nbplaces, &v1.prixJour, v1.EnLocation) != EOF) {
            if (x != v1.idVoiture) {
                fprintf(F2, "%d,%s,%s,%s,%s,%d,%d,%s\n", v1.idVoiture, v1.marque, v1.nom,v1.transmission, v1.couleur, v1.nbplaces, v1.prixJour, v1.EnLocation);
            }
        }
        fclose(F);
        fclose(F2);
        remove("voitures.csv");
        rename("temp_voitures.csv", "voitures.csv");
        printf("la suppression est bien faite\n");
    }
    menu();
}

void modifierVoiture() {
    FILE *F, *F2;
    voiture v1, v2;
    int x;
    printf("saisir le idVoiture: ");
    scanf("%d", &x);

    if (checkVoiture(x)) {
        F = fopen("voitures.csv", "r");
        F2 = fopen("temp_voitures.csv", "w");

        printf("pour modifier cette voiture\n");
        v2 = infoVoiture();

        while (fscanf(F, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%[^,]\n", &v1.idVoiture, v1.marque, v1.nom,v1.transmission, v1.couleur, &v1.nbplaces, &v1.prixJour, v1.EnLocation) != EOF) {
            if (v1.idVoiture == x) {
                fprintf(F2, "%d,%s,%s,%s,%s,%d,%d,%s\n", v2.idVoiture, v2.marque, v2.nom, v2.couleur, v1.transmission,v2.nbplaces, v2.prixJour, v2.EnLocation);
            } else {
                fprintf(F2, "%d,%s,%s,%s,%s,%d,%d,%s\n", v1.idVoiture, v1.marque, v1.nom, v1.couleur,v1.transmission, v1.nbplaces, v1.prixJour, v1.EnLocation);
            }
        }

        fclose(F);
        fclose(F2);
        remove("voitures.csv");
        rename("temp_voitures.csv", "voitures.csv");
        printf("la modification est bien faite\n");
    }
    menu();
}

void ajouterVoiture() {
    FILE *F;
    voiture v1;
    F = fopen("voitures.csv", "a");
    v1 = infoVoiture();
    fprintf(F, "%d,%s,%s,%s,%s,%d,%d,%s\n", v1.idVoiture, v1.marque, v1.nom, v1.couleur,v1.transmission, v1.nbplaces, v1.prixJour, v1.EnLocation);
    fclose(F);
    printf("la voiture est bien ajoutée\n");
    menu();
}

void Gestion_Voitures() {
    int x;
    do {
        printf("\n                               \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
        printf("\n                               \xb3 Menu Principale \xb3");
        printf("\n                               \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
        printf("\n\n");
        printf("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
        printf("\n               \xba                                              \xba");
        printf("\n               \xba    Liste des voitures....................1   \xba");
        printf("\n               \xba    ajouter voiture.......................2   \xba");
        printf("\n               \xba    modifier voiture......................3   \xba");
        printf("\n               \xba    supprimer voiture.....................4   \xba");
        printf("\n               \xba    retour................................5   \xba");
        printf("\n               \xba                                              \xba");
        printf("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
        printf("\n\n                                Votre choix  :  ");
        scanf("%d", &x);

        switch (x) {
            case 1:
                affichVoitures();
                break;
            case 2:
                ajouterVoiture();
                break;
            case 3:
                modifierVoiture();
                break;
            case 4:
                suppVoiture();
                break;
            case 5:
                menu();
                break;
            default:
                printf("erreur!");
                break;
        }
    } while (x <= 0 || x > 5);
}

int checkClient(int a) {
    FILE *F;
    client c;
    int i = 0;
    F = fopen("clients.csv", "r");
    while (fscanf(F, "%d,%[^,],%[^,],%d,%[^,],%d\n", &c.idClient, c.nom, c.prenom, &c.cin, c.adresse, &c.telephone) != EOF) {
        if (c.idClient == a) {
            i = 1;
            break;
        }
    }
    if (i == 0) { printf("\nCe client n'existe pas"); }
    fclose(F);
    return i;
}

void visualiserContrat(FILE *F3, int num) {
    contrat c;
    int find = 0;

    printf("Donnez le numero du contrat : ");
    scanf("%d", &num);
    fseek(F3, 0, SEEK_SET);
    while (fread(&c, sizeof(c), 1, F3) != 0 && find == 0) {
        if (c.numContrat == num) {
            find = 1;
            break;
        }
    }

    if (find == 0) {
        printf("Contrat introuvable\n");
    } else {
        fseek(F3, -(long)sizeof(c), SEEK_CUR);
        printf("Numero du contrat : %d\n", c.numContrat);
        printf("ID voiture : %d\n", c.idVoiture);
        printf("ID client : %d\n", c.idClient);
        printf("Date de debut : %s\n", c.debut);
        printf("Date de fin : %s\n", c.fin);
        printf("Cout : %d\n", c.cout);
    }
    fseek(F3, 0, SEEK_SET);
}

void louerVoiture(FILE *F1, FILE *F3) {
    voiture voitureALouer;
    contrat nouveauContrat;
    int idVoiture;
    int trouve = 0;

    printf("Entrez l'ID de la voiture à louer : ");
    scanf("%d", &idVoiture);

    fseek(F1, 0, SEEK_SET);
    while (fread(&voitureALouer, sizeof(voitureALouer), 1, F1) != 0) {
        if (voitureALouer.idVoiture == idVoiture) {
            trouve = 1;
            if (strcmp(voitureALouer.EnLocation, "Non") == 0) {
                strcpy(voitureALouer.EnLocation, "Oui");
                nouveauContrat.numContrat = rand(); // Générer un numéro de contrat unique
                nouveauContrat.idVoiture = idVoiture;
                // Demandez d'autres détails du contrat à l'utilisateur (ID client, dates, etc.)
                printf("Entrez l'ID du client : ");
                scanf("%d", &nouveauContrat.idClient);
                printf("Entrez la date de début (format JJ/MM/AAAA) : ");
                scanf("%s", nouveauContrat.debut);
                printf("Entrez la date de fin (format JJ/MM/AAAA) : ");
                scanf("%s", nouveauContrat.fin);
                printf("Entrez le coût : ");
                scanf("%d", &nouveauContrat.cout);

                fseek(F3, 0, SEEK_END);
                fwrite(&nouveauContrat, sizeof(nouveauContrat), 1, F3);
                fseek(F1, -sizeof(voitureALouer), SEEK_CUR);
                fwrite(&voitureALouer, sizeof(voitureALouer), 1, F1);
                printf("La voiture a été louée avec succès.\n");
            } else {
                printf("La voiture est déjà louée.\n");
            }
            break;
        }
    }

    if (!trouve) {
        printf("Aucune voiture avec cet ID n'a été trouvée.\n");
    }
}

void retournerVoiture(FILE *F3, FILE *F5, int num) {
    contrat c;
    int find = 0;

    printf("Numéro de contrat : ");
    scanf("%d", &num);

    fseek(F3, 0, SEEK_SET);
    while (fread(&c, sizeof(c), 1, F3) != 0 && find == 0) {
        if (c.numContrat == num) {
            find = 1;
            break;
        }
    }

    if (find == 0) {
        printf("Ce numéro de contrat n'existe pas.\n");
    } else {
        fseek(F3, -sizeof(c), SEEK_CUR);
        voiture v;
        FILE *F1 = fopen("voitures.csv", "r+");
        while (fscanf(F1, "%d,%[^,],%[^,],%[^,],%[^,],%d,%d,%[^,]\n", &v.idVoiture, v.marque, v.nom, v.couleur,v.transmission, &v.nbplaces, &v.prixJour, v.EnLocation) != EOF) {
            if (v.idVoiture == c.idVoiture) {
                strcpy(v.EnLocation, "Non");
                fseek(F1, -sizeof(v), SEEK_CUR);
                fwrite(&v, sizeof(v), 1, F1);
                break;
            }
        }
        fclose(F1);
        FILE *F4 = fopen("temp_contrats.csv", "w");
        rewind(F3);
        while (fread(&c, sizeof(c), 1, F3) != 0) {
            if (c.numContrat != num) {
                fwrite(&c, sizeof(c), 1, F4);
            }
        }
        fclose(F3);
        fclose(F4);
        remove("ContratsLocations.csv");
        rename("temp_contrats.csv", "ContratsLocations.csv");
        printf("La voiture a été retournée avec succès.\n");
    }
}

void modifierContrat() {
    FILE *F3;
    int num;
    contrat c;
    int find = 0;
    char test;

    printf("Donnez l'ID du contrat : ");
    scanf("%d", &num);

    F3 = fopen("ContratsLocations.csv", "r+");
    fseek(F3, 0, SEEK_SET);
    while (fread(&c, sizeof(c), 1, F3) != 0 && find == 0) {
        if (c.numContrat == num) {
            find = 1;
            break;
        }
    }

    if (find == 0) {
        printf("Ce contrat n'existe pas.\n");
    } else {
        printf("Ancienne date de début : %s\n", c.debut);
        printf("Ancienne date de fin : %s\n");

        printf("\n\n Que voulez-vous changer ?\n");
        printf("Début ? (o/n) : ");
        scanf(" %c", &test);
        if (test == 'o') {
            printf("Nouvelle date de début (format JJ/MM/AAAA) : ");
            scanf("%s", c.debut);
        }

        printf("Fin ? (o/n) : ");
        scanf(" %c", &test);
        if (test == 'o') {
            printf("Nouvelle date de fin (format JJ/MM/AAAA) : ");
            scanf("%s", c.fin);
        }

        fseek(F3, -sizeof(c), SEEK_CUR);
        fwrite(&c, sizeof(c), 1, F3);
        printf("Le contrat a été modifié avec succès.\n");
    }
    fclose(F3);
}

void supprimerContrat(FILE *F3, int num) {
    FILE *temp;
    contrat c;
    int find = 0;

    temp = fopen("temp_contrats.csv", "w");
    fseek(F3, 0, SEEK_SET);
    while (fread(&c, sizeof(c), 1, F3) != 0) {
        if (c.numContrat != num) {
            fwrite(&c, sizeof(c), 1, temp);
        } else {
            find = 1;
        }
    }
    fclose(F3);
    fclose(temp);
    remove("ContratsLocations.csv");
    rename("temp_contrats.csv", "ContratsLocations.csv");
    if (find) {
        printf("Le contrat a été supprimé avec succès.\n");
    } else {
        printf("Le contrat n'existe pas.\n");
    }
}

void Gestion_Location() {
    int choix;
    do {
        printf("\n                             \xda\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xbf");
        printf("\n                                  \xb3 Gestion d'une voiture  \xb3");
        printf("\n                             \xc0\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xc4\xd9");
        printf("\n\n");
        printf("\n               \xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
        printf("\n               \xba                                              \xba");
        printf("\n               \xba    visualiser contrat....................1   \xba");
        printf("\n               \xba    louer voiture.........................2   \xba");
        printf("\n               \xba    retourner voiture.....................3   \xba");
        printf("\n               \xba    modifier contrat......................4   \xba");
        printf("\n               \xba    supprimer contrat.....................5   \xba");
        printf("\n               \xba    Retour................................6   \xba");
        printf("\n               \xba                                              \xba");
        printf("\n               \xba                                              \xba");
        printf("\n               \xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
        printf("\n\n                                Votre choix  :  ");
        scanf("%d", &choix);
        printf("\n\n");
    } while (choix <= 0 || choix > 6);
    if (choix == 6)
        menu();
    else {
        FILE *F1 = fopen("voitures.csv", "r+");
        FILE *F3 = fopen("ContratsLocations.csv", "r+");
        switch (choix) {
            case 1:
                visualiserContrat(F3, choix);
                break;
            case 2:
                louerVoiture(F1, F3);
                break;
            case 3:
                retournerVoiture(F3, F1, choix);
                break;
            case 4:
                modifierContrat();
                break;
            case 5:
                supprimerContrat(F3, choix);
                break;
        }
        fclose(F1);
        fclose(F3);
    }
}

int main() {
    menu();
    return 0;
}
