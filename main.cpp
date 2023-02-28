#include <cmath>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cctype>



using namespace std;

// ligne pour désactiver les erreurs dans visual studio
#pragma warning(disable : 4996

void traiter_caractere2(char c, int tab[]){
  char a = 'a';
  for(int i = 0; i <26; i++){
    if(c == a+i)
    tab[i]+=1;
  }
}

// fonction traite caractere
void traiter_caractere(char c, int tab[]) {
  switch (c) {

  case 'a':
    tab[0] += 1;
    break;

  case 'b':
    tab[1] += 1;
    break;

  case 'c':
    tab[2] += 1;
    break;

  case 'd':
    tab[3] += 1;
    break;

  case 'e':
    tab[4] += 1;
    break;

  case 'f':
    tab[5] += 1;
    break;

  case 'g':
    tab[6] += 1;
    break;

  case 'h':
    tab[7] += 1;
    break;

  case 'i':
    tab[8] += 1;
    break;

  case 'j':
    tab[9] += 1;
    break;

  case 'k':
    tab[10] += 1;
    break;

  case 'l':
    tab[11] += 1;
    break;

  case 'm':
    tab[12] += 1;
    break;

  case 'n':
    tab[13] += 1;
    break;

  case 'o':
    tab[14] += 1;
    break;
    
  case 'p':
    tab[15] += 1;
    break;

  case 'q':
    tab[16] += 1;
    break;

  case 'r':
    tab[17] += 1;
    break;

  case 's':
    tab[18] += 1;
    break;

  case 't':
    tab[19] += 1;
    break;

  case 'u':
    tab[20] += 1;
    break;

  case 'v':
    tab[21] += 1;
    break;

  case 'w':
    tab[22] += 1;
    break;

  case 'x':
    tab[23] += 1;
    break;

  case 'y':
    tab[24] += 1;
    break;

  case 'z':
    tab[25] += 1;
    break;

  default:;
  }
}

// retire accent pour traiter les caractères spéciaux
string retireAccent(string message) {
  //on met des tableaux de références pour pouvoir avoir les accents et leur version sans accent respectifs
  string accent("ÀÁÂÃÄÅàáâãäåÒÓÔÕÖØòóôõöøÈÉÊËèéêëÌÍÎÏìíîïÙÚÛÜùúûüÑñÇç");
  string sansAccent("AAAAAAaaaaaaOOOOOOooooooEEEEeeeeIIIIiiiiUUUUuuuuNnCc");
  int i = 0, j = 0, k = 0, taille, tailleAccent;
  tailleAccent = accent.size();
  taille = message.size();

  for (i = 0; i <= taille; i++) {
    for (j = 0; j <= tailleAccent; j = j + 2) {
      //on vérifie si le caractère lu fait parti d'un des accents du string accent
      //étant donné que les accents sont codés sur 2 octets, on vérifie si 2 octets de la chaine
      //sont égaux à 2 octets d'un accent, au quel cas on dira que ce caractère est un accent.
      if ((message[i] == accent[j]) && (message[i + 1] == accent[j + 1])) {
        //on le remplace par son caractère sans accent dont l'emplacement est à j/2
        //car un caractère sans accent n'est codé que sur 1 octet
        message[i] = sansAccent[j / 2];
        //on décale tous les caractères suivant de la chaine vers la gauche 1 fois, pour combler le trou que le
        //remplacement a laissé
        for (k = i + 1; k < taille; k++) {
          message[k] = message[k + 1];
        }
      }
    }
  }

  return message;
}

// fonction calcul écart
float calcul_ecart(int tAnalyse[], int tRef[]) {
  float ecart = 0;
  float sommeTAnalyse = 0;
  float sommeTRef = 0;
  // on compte la somme des éléments de chaque tableau
  for (int i = 0; i < 26; i++) {
    sommeTAnalyse += tAnalyse[i];
    sommeTRef += tRef[i];
  }
  //on calcul l'écart sans la racine carré
  for (int i = 0; i < 26; i++) {
    ecart += pow(((tAnalyse[i] / sommeTAnalyse) - (tRef[i] / sommeTRef)), 2);
  }
  return sqrt(ecart);
}


// fonction occurrence_lettres
void Occurrencelettres(char* fichier, int tab[]) {
  // initialisation des éléments du tableau à 0
  for (int i = 0; i < 26; i++) {
    tab[i] = 0;
  }

  // lecture d'un fichier texte
  ifstream fich(fichier);

  if (fich.is_open()) {
    string line;
    while (getline(fich, line)) {
      //on retire les accents sur la ligne qu'on lit
      string sansAccent = retireAccent(line);
      for (char c : sansAccent) {
        //on met le caractère en minuscule avant de le traiter
        c = tolower(c);
        traiter_caractere(c, tab);
      }
    }
    fich.close();
  } else {
    std::cerr << "Impossible d'ouvrir le fichier." << std::endl;
  }


  //écriture dans le fichier le résultat de la recherche par occurence
  FILE *fic = NULL;
  fic = fopen(fichier, "a");
  fputc('\n', fic);
  char lettre = 'A';
  if (fic != NULL) {
    fputs("Occurrences du texte à analyser : ", fic);
    for (int i = 0; i < 26; i++) {
      if (i != 25)
        fprintf(fic, "%c:%d;", lettre + i, tab[i]);
      else
        fprintf(fic, "%c:%d\n", lettre + i, tab[i]);
    }
    fputs("Tableau d'occurence : [", fic);
    for (int i = 0; i < 26; i++) {
      if (i != 25)
        fprintf(fic, "%d, ", tab[i]);
      else
        fprintf(fic, "%d]\n", tab[i]);
    }
    fclose(fic);
  } else
    printf("Ouverture impossible");
}



// fonction trouve langue
void trouve_langue(char* nomfic) { 
  int tab[26];

  // on calcule le nombre d'occurrences du texte à analyser
  Occurrencelettres(nomfic, tab);
  // les tableaux d'occurence de référence
  int tabRefFR[26] = {2204, 198,  828,  1040, 4371, 266,  234, 178, 2102,
                      75,   8,    1576, 742,  1910, 1406, 778, 246, 1866,
                      2152, 1939, 1573, 442,  4,    94,   47,  13};
  int tabRefEN[26] = {1732, 352,  756,  1299, 3467, 493,  547, 820, 1903,
                      64,   112,  1097, 746,  1909, 1841, 683, 36,  1666,
                      1852, 1789, 770,  264,  407,  97,   567, 12};
  int tabRefES[26] = {3496, 462,  1078, 1068, 2698, 240,  310, 305, 1971,
                      138,  4,    1264, 753,  1685, 2580, 554, 78,  1805,
                      1921, 1121, 822,  316,  0,    57,   169, 121};
  int tabRefDE[26] = {1785, 696,  760,  875, 4021, 486, 972, 1378, 1502,
                      103,  429,  1099, 635, 2139, 727, 192, 0,    1699,
                      1585, 1690, 1240, 188, 433,  2,   0,   295};

  int tabRefIT[26] = {3046, 295,  1057, 796, 2715, 341,  463, 293, 2677,
                      0,    2,    1117, 728, 1487, 2489, 727, 55,  1849,
                      1525, 1646, 815,  701, 0,    13,   0,   193};

  // chaine qui va contenir le nom de la langue trouvée pour l'afficher
  const char *langueTrouvee = "";



  // on calcule les différents écarts avec les 5 langues
  float ecartFR = calcul_ecart(tab, tabRefFR);
  float ecartES = calcul_ecart(tab, tabRefES);
  float ecartEN = calcul_ecart(tab, tabRefEN);
  float ecartDE = calcul_ecart(tab, tabRefDE);
  float ecartIT = calcul_ecart(tab, tabRefIT);
  
  // tableau des langues dans l'ordre pour l'affichage des différents écarts
  const char *tabLangue[5]{"Français", "Espagnol", "Anglais", "Allemand",
                           "Italien"};
  //tableau des écarts pour pouvoir déterminer le plus petit écart, et l'afficher
  float tabEcart[5]{ecartFR, ecartES, ecartEN, ecartDE, ecartIT};

  // on détermine quel est le plus petit écart, dont on stock l'indice dans index
  float petit = tabEcart[0];
  int index = 0;
  for (int i = 1; i < 5; i++) {
    if (tabEcart[i] < petit) {
      petit = tabEcart[i];
      index = i;
    }
  }
  // on détermine la langue trouvée, celle qui avait le plus petit écart
  switch (index) {
  case 0:
    langueTrouvee = "français";
    break;
  case 1:
    langueTrouvee = "espagnol";
    break;
  case 2:
    langueTrouvee = "anglais";
    break;
  case 3:
    langueTrouvee = "allemand";
    break;
  case 4:
    langueTrouvee = "italien";
    break;
  default : 
    langueTrouvee = "??? Cela ne devrait pas arriver";
  }

  // on écrit dans le fichier la langue trouvée et les écarts
  FILE *fic = NULL;
  fic = fopen(nomfic, "a");
  if (fic != NULL) {
    fprintf(fic, "Langue trouvée : %s\n", langueTrouvee);
    for (int i = 0; i < 5; i++) {
      fprintf(fic, "%s ; écart : %.2f\n", tabLangue[i], tabEcart[i]);
    }
    fclose(fic);
  } else
    printf("Ouverture impossible");
}

int main() {
  // on demande à l'utilisateur ce qu'il veut faire
  int choix;
  char nomfichier[100] = "";
  do {
    cout << "Bonjour, quel traitement voulez-vous effectuer ? : \n1) "
            "Obtenir les occurrences de lettres d'un texte\n2) Trouver la langue d'un texte\n";
    cin >> choix;
  } while (choix != 1 && choix != 2);
  switch (choix) {
  case 1:
    int tab[26];
    cout << "Entrez le chemin vers le fichier texte : ";
    cin >> nomfichier;
    Occurrencelettres(nomfichier, tab);
    break;
  case 2:
    cout << "Entrez le chemin vers le fichier texte : ";
    cin >> nomfichier;
    trouve_langue(nomfichier); 
    break;
  default:
    cout << "cela ne devrait pas arriver";
  }

  // affichage du contenu du fichier texte
  FILE *fic = NULL;
  char c;
  // lecture du fichier caractères 1 à 1
  fic = fopen(nomfichier, "r");
  if (fic != NULL) {
    do {
      c = fgetc(fic);
      cout << c;
    } while (c != EOF);

    fclose(fic);
  }
}


