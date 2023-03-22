/*
	TP5 - IA
	Taquin 4x4
	Duc Viet Nguyen Théo Gayant M1 Informatique
	25/11/20
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "file.c"

int t = 0;

char * dep[]= {
	"H", //0
	"B", //1
	"G",//2
	"D"//3
};
int n_parcours = 0;

void afficheTaquin(int tbl[]) {
	printf("%2d %2d %2d %2d\n",tbl[0],tbl[1],tbl[2],tbl[3]);
	printf("%2d %2d %2d %2d\n",tbl[4],tbl[5],tbl[6],tbl[7]);
	printf("%2d %2d %2d %2d\n",tbl[8],tbl[9],tbl[10],tbl[11]);
	printf("%2d %2d %2d %2d\n\n",tbl[12],tbl[13],tbl[14],tbl[15]);
}

int estTaquinBut(int Taquin[], int n) {
	int i = 0;
	for (i = 0; i < (n*n); i++) {
		if (Taquin[i] != i) return 0;
	}
	return 1;
}

int estTaquinButPartiel(int Taquin[],int TaquinPartiel[]) {
	int i;
	for(i = 0; i < 16; i++) {
		if (TaquinPartiel[i] != -1 && Taquin[i] != TaquinPartiel[i]) return 0;
	}
	return 1;
}

int taquin4x4Solvable(int Taquin[]) {
	int nbInversion = 0;
	int lig_vide = -1;//Ligne où est le vide
	int i,j;
	for (i = 0; i < (4*4); i++)  {//Pour chaque nombre du taquin on regarde son nombre d'inversion pour qu'il soit a sa place		
		for (j = i + 1; j < (4*4); j++) {
			if (Taquin[i] == 0 || Taquin[j] == 0) {//On ne compare pas avec la case vide
				if (lig_vide == -1 && Taquin[i] == 0)	lig_vide = i/4;
				else if (lig_vide == -1) lig_vide = j/4;
				continue;
			}
			if (Taquin[i] > Taquin[j]) {
				nbInversion++;
				//printf("i : %d & j : %d\n",Taquin[i],Taquin[j]);
			}
		}
	}
	printf("Le vide est sur la ligne %d\n",lig_vide);
	printf("nbInversion : %d\n",nbInversion);
	return (((nbInversion % 2) == 0 && (lig_vide%2) == 0) || ((nbInversion%2) != 0 && (lig_vide%2) != 0)) ;
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

int ** taquinsSuccesseur(int * taq) {
	int ** lesTaquinSucc = (int **) calloc(4,sizeof(int*)*4);
	int * taquin;
	int indVide = indiceCaseVide(taq,4);
	
	if(testDeplacement(taq,"H",4)) {
		taquin = (int *) calloc(16,sizeof(int));
		memcpy(taquin,taq,sizeof(int)*16);
		taquin[indVide] = taquin[indVide-4];
		taquin[indVide-4] = 0;
		lesTaquinSucc[0] = taquin;
	}
	if (testDeplacement(taq,"B",4)) {
		taquin = (int *) calloc(16,sizeof(int));
		memcpy(taquin,taq,sizeof(int)*16);
		taquin[indVide] = taquin[indVide+4];
		taquin[indVide+4] = 0;
		lesTaquinSucc[1] = taquin;
	}
	if (testDeplacement(taq,"G",4)) {
		taquin = (int *) calloc(16,sizeof(int));
		memcpy(taquin,taq,sizeof(int)*16);
		taquin[indVide] = taquin[indVide-1];
		taquin[indVide-1] = 0;
		lesTaquinSucc[2] = taquin;
	}
	if (testDeplacement(taq,"D",4)) {
		taquin = (int *) calloc(16,sizeof(int));
		memcpy(taquin,taq,sizeof(int)*16);
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
	for(i = 0; i < 16; i++) {
		if (taquin[i] == 0) continue;
		x = i/4;
		y = i%4;

		x_fin = taquin[i]/4;
		y_fin = taquin[i]%4;

		cout = abs(x-x_fin) + abs(y-y_fin);

		//printf("%d : (%d,%d) & (%d,%d) ==> %d\n",taquin[i],x,y,x_fin,y_fin,cout);
		somme+=cout;
	}
	return somme;
}

//Indique si d dans dans le taquin but partiel
int estDansTaquinPartiel(int taquin_partiel[],int d) {
	int i;
	for(i=0;i<16;i++) {
		if(taquin_partiel[i] == d) return 1;
	}
	return 0;
}

int h_manhattan_partiel(int taquin[], int taquin_partiel[]) {
	int i,somme,cout,x,y,x_fin,y_fin;
	somme = 0;
	for(i = 0; i < 16; i++) {
		if (taquin[i] == 0 || taquin[i] == -1) continue;
		if (!estDansTaquinPartiel(taquin_partiel,taquin[i])) continue;
		x = i/4;//Position x actuel
		y = i%4;//Position y actuel

		x_fin = taquin[i]/4;//Position x taquin but
		y_fin = taquin[i]%4;//Position y taquin but

		cout = abs(x-x_fin) + abs(y-y_fin);

		//printf("%d : (%d,%d) & (%d,%d) ==> %d\n",taquin[i],x,y,x_fin,y_fin,cout);
		somme+=cout;
	}
	return somme;
}

int estRetour(char c1, char c2) {
	return (c1 == 'H' && c2 =='B') || (c1 == 'B' && c2 == 'H') || (c1 == 'G' && c2 == 'D') || (c1 == 'D' && c2 == 'G');
}

void remplace_inutile(int * taquin, int taquin_partiel[]) {
	int i;
	for(i = 0; i < 16; i++) {
		if(!estDansTaquinPartiel(taquin_partiel,taquin[i])) taquin[i] = -1;
	}
}

Element * rechercheIDA(int * taquin, int taquin_partiel[]) {
	int * tq_tmp, **tq_succ, i,j=0;
	char * chemin_tmp,c;
	Element * e, *e2;
	Pile p;
	Pile deja_vu;
	initialiserP(&deja_vu);
	initialiserP(&p);

	tq_tmp = (int *) calloc(16,sizeof(int));
	memcpy(tq_tmp,taquin,sizeof(int)*16);
	remplace_inutile(tq_tmp,taquin_partiel);
	afficheTaquin(tq_tmp);
	n_parcours = 0;
	chemin_tmp = (char *) malloc(sizeof(char)*1);
	chemin_tmp[0]='\0';
	empiler(&p,tq_tmp,chemin_tmp,h_manhattan_partiel(tq_tmp,taquin_partiel),0);
	empiler(&deja_vu,tq_tmp,"",0,0);

	int seuil = h_manhattan_partiel(tq_tmp,taquin_partiel);
	int min = -1;
	int f;
	while(1) {
		printf("seuil : %d\n",seuil);
		while(!estVideP(&p)) {
			n_parcours++;
			e = depiler(&p);
			if(estTaquinButPartiel(e->taquin,taquin_partiel)) {
				while(!estVideP(&p)) {
					e2 = depiler(&p);
					free(e2->chemin);
					free(e2);
				}
				return e;
			}
			tq_succ = taquinsSuccesseur(e->taquin);
			for(i = 0; i < 4; i++) {
				if(tq_succ[i] != NULL && (strlen(e->chemin) == 0 || !estRetour(e->chemin[strlen(e->chemin)-1],dep[i][0]))) {
					f = (strlen(e->chemin)+1+h_manhattan_partiel(tq_succ[i],taquin_partiel));
					if ( f <= seuil) {
						if (estDansPile(&p,tq_succ[i])) 
						{
							free(tq_succ[i]);
							continue;
						}
						chemin_tmp = (char *)malloc(sizeof(char)*(strlen(e->chemin)+2));
						memcpy(chemin_tmp,e->chemin,strlen(e->chemin)+1);
						strcat(chemin_tmp,dep[i]);
						empiler(&p,tq_succ[i],chemin_tmp,h_manhattan_partiel(tq_succ[i],taquin_partiel),0);
						empiler(&deja_vu,tq_succ[i],"",0,0);
					}
					else {
						free(tq_succ[i]);
						if(f < min) min = f;
						else if  (min == -1) min = f;
					}
				}
			}
			free(e->chemin);
			free(e);
		}
		seuil = min;
		min = -1;
		tq_tmp = (int *) calloc(16,sizeof(int));
		memcpy(tq_tmp,taquin,sizeof(int)*16);
		chemin_tmp = (char *) malloc(sizeof(char)*1);
		chemin_tmp[0]='\0';
		remplace_inutile(tq_tmp,taquin_partiel);
		empiler(&p,tq_tmp,chemin_tmp,h_manhattan_partiel(tq_tmp,taquin_partiel),0);
		videPile(&deja_vu);
		initialiserP(&deja_vu);
		empiler(&deja_vu,tq_tmp,"",0,0);
	}
	return NULL;
}

int deplacementG2(int taquin[], char c) {
	int pos_vide = indiceCaseVide(taquin,4);
	if ((c == 'H') && (taquin[pos_vide+4] != -1)) return 1;
	else if ((c == 'B') && (taquin[pos_vide-4] != -1)) return 1;
	else if ((c == 'G') && (taquin[pos_vide+1] != -1)) return 1;
	else if ((c == 'D') && (taquin[pos_vide-1] != -1)) return 1;
	return 0;
}

Element * rechercheIDAg2(int * taquin, int taquin_partiel[]) {
	int * tq_tmp, **tq_succ, i,j=0;
	char * chemin_tmp,c;
	Element * e;
	Pile p;
	Pile deja_vu;
	initialiserP(&p);
	initialiserP(&deja_vu);

	tq_tmp = (int *) calloc(16,sizeof(int));
	memcpy(tq_tmp,taquin,sizeof(int)*16);
	remplace_inutile(tq_tmp,taquin_partiel);
	afficheTaquin(tq_tmp);
	n_parcours = 0;
	chemin_tmp = (char *) malloc(sizeof(char)*1);
	chemin_tmp[0]='\0';
	empiler(&p,tq_tmp,chemin_tmp,h_manhattan_partiel(tq_tmp,taquin_partiel),0);
	empiler(&deja_vu,tq_tmp,"",0,0);

	int seuil = h_manhattan_partiel(tq_tmp,taquin_partiel);
	int min = -1;
	int f,g,h;
	while(1) {
		printf("seuil : %d\n",seuil);
		while(!estVideP(&p)) {
			n_parcours++;
			e = depiler(&p);
			//afficheTaquin(e->taquin);
			if(estTaquinButPartiel(e->taquin,taquin_partiel)) return e;
			tq_succ = taquinsSuccesseur(e->taquin);
			for(i = 0; i < 4; i++) {
				//printf("Successeur :");
				//printf("Succ --> %c\n",dep[i][0]);
				if(tq_succ[i] != NULL && (strlen(e->chemin) == 0 || !estRetour(e->chemin[strlen(e->chemin)-1],dep[i][0]))) {
					g = e->g + deplacementG2(tq_succ[i],dep[i][0]);
					h = h_manhattan_partiel(tq_succ[i],taquin_partiel);
					f = g+h;
					//afficheTaquin(tq_succ[i]);
					//printf("G : %d et H : %d\n",g,h);
					if ( f <= seuil) {
						if (estDansPile(&deja_vu,tq_succ[i])) 
						{
							//printf("deja vu\n");
							free(tq_succ[i]);
							continue;
						}
						//printf("AJOUTER\n");
						chemin_tmp = (char *)malloc(sizeof(char)*(strlen(e->chemin)+2));
						memcpy(chemin_tmp,e->chemin,strlen(e->chemin)+1);
						strcat(chemin_tmp,dep[i]);
						empiler(&p,tq_succ[i],chemin_tmp,h,g);
						empiler(&deja_vu,tq_succ[i],"",0,0);
					}
					else {
						free(tq_succ[i]);
						if(f < min)	min = f;
						else if (min == -1) min = f;
					}
				}
			}
			//printf("\n\n");
			free(e->chemin);
			free(e);
		}
		seuil = min;
		min = -1;
		tq_tmp = (int *) calloc(16,sizeof(int));
		memcpy(tq_tmp,taquin,sizeof(int)*16);
		remplace_inutile(tq_tmp,taquin_partiel);
		chemin_tmp = (char *) malloc(sizeof(char)*1);
		chemin_tmp[0]='\0';
		empiler(&p,tq_tmp,chemin_tmp,h_manhattan_partiel(tq_tmp,taquin_partiel),0);
		videPile(&deja_vu);
		initialiserP(&deja_vu);
		empiler(&deja_vu,tq_tmp,"",0,0);
	}
	return NULL;
}

void taquinTxtToTaquin(char * taquinTxt, int * taquin) {
	int i;
	char * ch = strtok(taquinTxt," ");
	for(i = 0; i < 15; i++) {
		taquin[i] = atoi(ch);
		ch = strtok(NULL," ");
	}
	taquin[15] = atoi(ch);
	//afficheTaquin(taquin);
}
int bp1[16] = {0,-1,-1,3,-1,-1,-1,7,-1,-1,-1,11,12,13,14,15};
int bp2[16] = {0,1,2,-1,4,5,6,-1,8,9,10,-1,-1,-1,-1,-1};

int main(int argc, char const *argv[])
{
	Element *e;
	if(argc != 2 || (strcmp(argv[1],"entree.txt") != 0)) printf("Il faut le fichier 'entree.txt' en parametre\n"),exit(0);
	char unTaquinTxt[40];
	printf("UOOO\n");
	FILE * fichier = fopen("entree.txt","r");
	FILE * sortie = fopen("resultat.txt","w");
	int unTaquin[16];
	while(fgets(unTaquinTxt,40,fichier)) {
		if (strcmp(unTaquinTxt,"\n") == 0) break;
		unTaquinTxt[37] = '\0';
		fprintf(sortie,"Taquin initial : %s\n",unTaquinTxt);
		printf("Voici le taquin : '%s'\n",unTaquinTxt);
		
		taquinTxtToTaquin(unTaquinTxt,unTaquin);
		printf("Taquin initial :\n");
		afficheTaquin(unTaquin);
		
		if(!taquin4x4Solvable(unTaquin)) {
			printf("Ce taquin n'est pas solvable\n");
			printf("##############\n");
			fprintf(sortie,"Pas Solvable\n");
			fprintf(sortie,"\n\n\n");
			continue;
		}
		

		int h_p1 = h_manhattan_partiel(unTaquin,bp1);
		int h_p2 = h_manhattan_partiel(unTaquin,bp2);
		printf("Manhattan partiel 1 : %d\n",h_p1);
		printf("Manhattan partiel 2 : %d\n",h_p2);
		int h_manhattan = h_p1 + h_p2;
		fprintf(sortie,"Distance de Manhattan : %d\n",h_manhattan);

		Element * e;
		printf("\nIDA PARTIEL 1 G1:\n");
		e = rechercheIDA(unTaquin,bp1);
		afficheTaquin(e->taquin);
		printf("%s --> %ld\n",e->chemin,strlen(e->chemin));
		printf("N parcours : %d\n",n_parcours);
		fprintf(sortie,"BP1 - G1 : %ld\t %s\n",strlen(e->chemin),e->chemin);

		printf("\nIDA PARTIEL 1 G2:\n");
		e = rechercheIDAg2(unTaquin,bp1);
		afficheTaquin(e->taquin);
		printf("%s --> %ld\n",e->chemin,strlen(e->chemin));
		printf("N parcours : %d\n",n_parcours);
		fprintf(sortie,"BP1 - G2 : %d\t %s\n",e->g+e->h,e->chemin);

		printf("\nIDA PARTIEL 2 G1:\n");
		t= 1;
		e = rechercheIDA(unTaquin,bp2);
		afficheTaquin(e->taquin);
		printf("%s --> %ld\n",e->chemin,strlen(e->chemin));
		printf("N parcours : %d\n",n_parcours);
		fprintf(sortie,"BP2 - G1 : %ld\t %s\n",strlen(e->chemin),e->chemin);


		printf("\nIDA PARTIEL 2 G2:\n");
		t= 1;
		e = rechercheIDAg2(unTaquin,bp2);
		afficheTaquin(e->taquin);
		printf("%s --> %ld\n",e->chemin,strlen(e->chemin));
		printf("N parcours : %d\n",n_parcours);
		fprintf(sortie,"BP2 - G2 : %d\t %s\n",e->g+e->h,e->chemin);


		printf("##############\n");
		fprintf(sortie,"\n\n\n");
		
	}
	fclose(fichier);
	fclose(sortie);
	return 0;
}
