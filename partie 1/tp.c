/*
	TP2 - IA
	Taquin 3x3
	Duc Viet Nguyen, Théo Gayant M1 Informatique
	23/09/20
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "file.c"

char * dep[]= {
	"H", //0
	"B", //1
	"G",//2
	"D"//3
};
int n_parcours = 0;

void afficheTaquin(int tbl[]) {
	printf("%d %d %d\n",tbl[0],tbl[1],tbl[2]);
	printf("%d %d %d\n",tbl[3],tbl[4],tbl[5]);
	printf("%d %d %d\n\n",tbl[6],tbl[7],tbl[8]);
}

int estTaquinBut(int Taquin[], int n) {
	int i = 0;
	for (i = 0; i < (n*n); i++) {
		if (Taquin[i] != i) return 0;
	}
	return 1;
}

int taquin3x3Solvable(int Taquin[]) {
	int nbInversion = 0;
	int i,j;
	for (i = 0; i < (3*3); i++)  {//Pour chaque nombre du taquin on regarde son nombre d'inversion pour qu'il soit a sa place		
		for (j = i + 1; j < (3*3); j++) {
			if (Taquin[i] == 0 || Taquin[j] == 0) continue;//On ne compare pas avec la case vide
			if (Taquin[i] > Taquin[j]) {
				nbInversion++;
				//printf("i : %d & j : %d\n",Taquin[i],Taquin[j]);
			}
		}
	}
	//printf("nbInversion : %d\n",nbInversion);
	return (nbInversion % 2) == 0;
}

int indiceCaseVide(int Taquin[], int n) {
	int i;
	for (i = 0; i < n*n; i++) {
		if (Taquin[i] == 0) return i;
	}
	return -1;
}

int testDeplacement(int leTaquin[], char * dep, int n) {
	int i, res = 0;
	int indCaseVide;
	int * Taquin = (int *) malloc(sizeof(int)*(n*n));
	memcpy(Taquin,leTaquin,sizeof(int)*(n*n));

	indCaseVide = indiceCaseVide(Taquin,n);
	//printf("Indice case vide : %d\n",indCaseVide);
	for (i = 0; i < strlen(dep); i++) {
		if (dep[i] == 'H') {
			if (indCaseVide >= n) { //Si on n'est pas sur la bordure du haut
				Taquin[indCaseVide] = Taquin[indCaseVide - n];
				Taquin[indCaseVide - n] = 0;
				indCaseVide = indCaseVide -n;
				res=1;
			}
		}
		else if (dep[i] == 'B') {
			if (indCaseVide < n*(n-1)) { //Si on n'est pas sur la bordure du bas
				Taquin[indCaseVide] = Taquin[indCaseVide + n];
				Taquin[indCaseVide + n] = 0;
				indCaseVide = indCaseVide + n;
				res=1;
			}
		}
		else if (dep[i] == 'G') {
			if ((indCaseVide % n) != 0) { //Si on n'est pas sur la bordure de gauche
				Taquin[indCaseVide] = Taquin[indCaseVide - 1];
				Taquin[indCaseVide - 1] = 0;
				indCaseVide-=1;
				res=1;
			}
		}
		else if (dep[i] == 'D') {
			if ((indCaseVide % n) != (n-1)) { //Si on n'est pas sur la bordure de droite
				Taquin[indCaseVide] = Taquin[indCaseVide + 1];
				Taquin[indCaseVide + 1] = 0;
				indCaseVide+=1;
				res = 1;
			}
		}
		//afficheTaquin(Taquin);
	}
	//afficheTaquin(Taquin);
	//res = estTaquinBut(Taquin,n);
	free(Taquin);
	return res;
}

void faire_combi(int tab[],int taq[],int n, int ind, int * nb_tab, int ** lesTaquins) {
	int i;
	int * tab_tmp = (int*) malloc(sizeof(int)*n);
	int * taq_tmp = (int*) malloc(sizeof(int)*n);

	if (ind >= n) {
		for(i=0;i<n;i++) {
			if (tab[i] == 0) taq[ind] = i;
		}
		if (taquin3x3Solvable(taq)) {
			//afficheTaquin(taq);
			lesTaquins[*nb_tab] = taq;
			(*nb_tab)++;
		} else {
			free(taq_tmp);
		}
		free(tab_tmp);
	}
	else {
		for(i=0;i<n;i++) {
			//printf("i : %d\n",i);
			if (tab[i] == 0) {//Si on l'a pas pris ce nb
				memcpy(tab_tmp,tab,sizeof(int)*n);
				memcpy(taq_tmp,taq,sizeof(int)*n);
				tab_tmp[i] = 1;
				taq_tmp[ind] = i;
				faire_combi(tab_tmp,taq_tmp,n,ind+1,nb_tab,lesTaquins);
			}
		}
	}
}

int ** genererTaquin3x3(int * size) {
	int i;
	int ** tab = (int**) calloc(9*8*7*6*5*4*3*2,sizeof(int*));//On crée un tableau qui peut stocker tout les taquins 3x3 possible ou non
	int *nb = (int*) calloc(9,sizeof(int));
	int * tq = (int*) calloc(9,sizeof(int));

	faire_combi(nb,tq,9,0,size,tab);
	
	printf("Nombre de taquin généré : %d\n",*size);
	tab = (int **) realloc(tab,sizeof(int*)*(*size));

	return tab;
}

int ** taquinsSuccesseur(int * taq) {
	int ** lesTaquinSucc = (int **) calloc(4,sizeof(int*)*9);
	int * taquin;
	int indVide = indiceCaseVide(taq,3);
	
	if(testDeplacement(taq,"H",3)) {
		taquin = (int *) calloc(9,sizeof(int));
		memcpy(taquin,taq,sizeof(int)*9);
		taquin[indVide] = taquin[indVide-3];
		taquin[indVide-3] = 0;
		lesTaquinSucc[0] = taquin;
	}
	if (testDeplacement(taq,"B",3)) {
		taquin = (int *) calloc(9,sizeof(int));
		memcpy(taquin,taq,sizeof(int)*9);
		taquin[indVide] = taquin[indVide+3];
		taquin[indVide+3] = 0;
		lesTaquinSucc[1] = taquin;
	}
	if (testDeplacement(taq,"G",3)) {
		taquin = (int *) calloc(9,sizeof(int));
		memcpy(taquin,taq,sizeof(int)*9);
		taquin[indVide] = taquin[indVide-1];
		taquin[indVide-1] = 0;
		lesTaquinSucc[2] = taquin;
	}
	if (testDeplacement(taq,"D",3)) {
		taquin = (int *) calloc(9,sizeof(int));
		memcpy(taquin,taq,sizeof(int)*9);
		taquin[indVide] = taquin[indVide+1];
		taquin[indVide+1] = 0;
		lesTaquinSucc[3] = taquin;
	}
	return lesTaquinSucc;
}

int h_malplacees(int taquin[]) {
	int cpt = 0,i = 0;
	for (i = 0; i < 9; i++) {
		if (taquin[i] != i && taquin[i] != 0) cpt++;
	}
	return cpt;
}

int h_manhattan(int taquin[]) {
	int i,somme,cout,x,y,x_fin,y_fin;
	somme = 0;
	for(i = 0; i < 9; i++) {
		if (taquin[i] == 0) continue;
		x = i/3;
		y = i%3;

		x_fin = taquin[i]/3;
		y_fin = taquin[i]%3;

		cout = abs(x-x_fin) + abs(y-y_fin);

		//printf("%d : (%d,%d) & (%d,%d) ==> %d\n",taquin[i],x,y,x_fin,y_fin,cout);
		somme+=cout;
	}
	return somme;
}

int estRetour(char c1, char c2) {
	return (c1 == 'H' && c2 =='B') || (c1 == 'B' && c2 == 'H') || (c1 == 'G' && c2 == 'D') || (c1 == 'D' && c2 == 'G');
}

Element * rechercheIDA(int * taquin, int (*h)(int *)) {
	int * tq_tmp, **tq_succ, i,j=0;
	char * chemin_tmp,c;
	Element * e;
	Pile p;
	initialiserP(&p);

	tq_tmp = (int *) calloc(9,sizeof(int));
	memcpy(tq_tmp,taquin,sizeof(int)*9);
	n_parcours = 0;
	chemin_tmp = (char *) malloc(sizeof(char)*1);
	chemin_tmp[0]='\0';
	empiler(&p,tq_tmp,chemin_tmp,h(tq_tmp));

	int seuil = h(tq_tmp);
	int min = -1;
	int f;
	while(1) {
		printf("seuil : %d\n",seuil);
		while(!estVideP(&p)) {
			e = depiler(&p);
			if(estTaquinBut(e->taquin,3)) return e;
			tq_succ = taquinsSuccesseur(e->taquin);
			for(i = 0; i < 4; i++) {
				if(tq_succ[i] != NULL && (strlen(e->chemin) == 0 || !estRetour(e->chemin[strlen(e->chemin)-1],dep[i][0]))) {
					f = (strlen(e->chemin)+1+h(tq_succ[i]));
					if ( f <= seuil) {
						chemin_tmp = (char *)malloc(sizeof(char)*(strlen(e->chemin)+2));
						memcpy(chemin_tmp,e->chemin,strlen(e->chemin)+1);
						strcat(chemin_tmp,dep[i]);
						empiler(&p,tq_succ[i],chemin_tmp,h(tq_succ[i]));
					}
					else {
						if((min != -1) && (f < min)) {
							min = f;
						}
						else if  (min == -1) {
							min = f;
						}
					}
				}
			}
			free(e->taquin);
			free(e->chemin);
			free(e);
		}
		seuil = min;
		min = -1;
		tq_tmp = (int *) calloc(9,sizeof(int));
		memcpy(tq_tmp,taquin,sizeof(int)*9);
		chemin_tmp = (char *) malloc(sizeof(char)*1);
		chemin_tmp[0]='\0';
		empiler(&p,tq_tmp,chemin_tmp,h(tq_tmp));
	}
	return NULL;
}

void taquinTxtToTaquin(char * taquinTxt, int * taquin) {
	int i;
	for(i = 0; i < 9; i++) {
		taquin[i] = taquinTxt[i*2] - '0';
	}
}

int main(int argc, char const *argv[])
{
	Element *e;
	if(argc != 2 || (strcmp(argv[1],"entree.txt") != 0)) printf("Il faut le fichier 'entree.txt' en parametre\n"),exit(0);
	char unTaquinTxt[50];
	FILE * fichier = fopen("entree.txt","r");
	FILE * sortie = fopen("sortie.txt","w");
	int i = 1;
	int unTaquin[9];
	while(fgets(unTaquinTxt,50,fichier)) {
		//printf("Voici la ligne : '%s'\n",unTaquinTxt);
		if (strcmp(unTaquinTxt,"\n") == 0) break;
		unTaquinTxt[17] = '\0';
		taquinTxtToTaquin(unTaquinTxt,unTaquin);
		if (i == 1) {
			printf("Voici le Taquin but :\n");
			i++;
			afficheTaquin(unTaquin);
			printf("~~~~~~~~~~~~~~~\n");
			continue;
		}
		printf("Taquin initial :\n");
		afficheTaquin(unTaquin);

		fprintf(sortie,"%s\t",unTaquinTxt);
		if(!taquin3x3Solvable(unTaquin)) {
			printf("Ce taquin n'est pas solvable\n");
			printf("##############\n");
			fprintf(sortie,"Pas Solvable\n");
			continue;
		}
		e = rechercheIDA(unTaquin,h_manhattan);
		printf("Nombre de déplacement : %ld\n",strlen(e->chemin));
		printf("Chemin : '%s'\n",e->chemin);
		printf("##############\n");
		fprintf(sortie,"%ld\t%s\n",strlen(e->chemin),e->chemin);
	}
	fclose(fichier);
	fclose(sortie);

	return 0;
}
