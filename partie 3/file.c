typedef struct Element Element;
struct Element
{
    int * taquin;
    char * chemin;
    int h;
    int g;
    Element *suivant;
};

typedef struct File File;
struct File
{
    Element *premier;
};

void enfiler(File *file, int *nvTaquin, char * nvChemin, int h)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if (file == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->taquin = nvTaquin;
    nouveau->chemin = nvChemin;
    nouveau->h = h;
    nouveau->suivant = NULL;

    if (file->premier != NULL) /* La file n'est pas vide */
    {
        /* On se positionne à la fin de la file */
        Element *elementActuel = file->premier;
        while (elementActuel->suivant != NULL)
        {
            elementActuel = elementActuel->suivant;
        }
        elementActuel->suivant = nouveau;
    }
    else /* La file est vide, notre élément est le premier */
    {
        file->premier = nouveau;
    }
}

Element * defiler(File *file)
{
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element * e = NULL;

    /* On vérifie s'il y a quelque chose à défiler */
    if (file->premier != NULL)
    {
        e = file->premier;

        file->premier = e->suivant;
        e->suivant = NULL;
    }

    return e;
}

Element * defilerH(File *file) {
    if(file == NULL){
        exit(EXIT_FAILURE);
    }
    int min;
    Element * res = NULL;
    Element *e = file->premier;
    if (e == NULL) return res;
    if (e->suivant == NULL) { //Si on a que un seul element
        res = e;
        file->premier = NULL;
        return res;
    }

    min = strlen(e->chemin) + e->h;//On initialise le min au premier element
    res = e;
    Element *p_res = NULL;

    Element * e_pere = e; //le pere de e
    e = e->suivant;
    int i=1;
    while(e != NULL) {//On parcours toute la file
        if((strlen(e->chemin) + e->h) < min) {
            res = e;
            p_res = e_pere;
        }
        e_pere = e;
        e = e->suivant;
        i++;
    }
    if (p_res == NULL) {
        file->premier = res->suivant;
    }
    else {
        p_res->suivant = res->suivant;
    }
    //printf("i : %d\n",i);
    //printf("min : %d\n",min);
    
    res->suivant = NULL;
    return res;
}

int estDansFile(File * f, int * tb_e) {
    if (f == NULL)
    {
        exit(EXIT_FAILURE);
    }
    int * tb_tmp, res;
    Element * tmp = f->premier;
    while(tmp != NULL) {
        tb_tmp = tmp->taquin;
        res = 1;
        for (int i = 0; i < 9; i++) {
            if (tb_tmp[i] != tb_e[i]) res = 0;
        }
        if(res) return 1;
        tmp = tmp->suivant;
    }
    return 0;
}

int estVide(File * f) {
    return (f->premier == NULL);
}

void initialiser(File * f){
	f->premier = NULL;
}






// PILE --------------------
typedef struct Pile Pile;
struct Pile
{
    Element *premier;
};

void empiler(Pile *pile, int *nvTaquin, char * nvChemin, int h, int g)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if (pile == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->taquin = nvTaquin;
    nouveau->chemin = nvChemin;
    nouveau->h = h;
    nouveau->g = g;
    nouveau->suivant = pile->premier;
    pile->premier = nouveau;
}

Element * depiler(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Element * e = pile->premier;

    /* On vérifie s'il y a quelque chose à dépiler */
    if (pile != NULL && pile->premier != NULL)
    {
    	pile->premier = e->suivant;
    	e->suivant = NULL;
    }

    return e;
}

void initialiserP(Pile * p){
	p->premier = NULL;
}

int estVideP(Pile * p) {
    return (p->premier == NULL);
}
int estDansPile(Pile * p, int * tb_e) {
    if (p == NULL)
    {
        exit(EXIT_FAILURE);
    }
    int * tb_tmp, res;
    Element * tmp = p->premier;
    while(tmp != NULL) {
        tb_tmp = tmp->taquin;
        res = 1;
        for (int i = 0; i < 16; i++) {
            if (tb_tmp[i] != tb_e[i]) {
                res = 0;
                break;
            }
        }
        if(res) {
            /*printf("TQ1 :\n");
            afficheTaquin(tb_e);
            printf("TQ2 :\n");
            afficheTaquin(tmp->taquin);
            printf("chemin tq2 : '%s'\n",tmp->chemin);*/
            return 1;
        }
        tmp = tmp->suivant;
    }
    return 0;
}

void videPile(Pile * p) {
    Element * tmp;
    while (!estVideP(p)) {
        tmp = depiler(p);
        free(tmp->taquin);
        free(tmp);
    }
}

void affichePile(Pile * p) {
    Element * tmp = p->premier;
    while (tmp != NULL) {
        //afficheTaquin(tmp->taquin);
        tmp = tmp->suivant;
    }
}