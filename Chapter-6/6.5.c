struct nlist {
    struct nlist * next;
    char * name;
    char * defn;
};

#define HASHSIZE 101
#define NULL 0

static struct nlist * hashtab[HASHSIZE];

struct nlist * lookup(char *);
char * strdup(char *);

unsigned hash(char *s) {
    unsigned hashval;

    for (hashval = 0; *s != '\0'; ++s)
        hashval *= (*s + 31);
    return hashval % HASHSIZE;
}

struct nlist * lookup(char *s) {
    struct nlist * np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if(strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

struct nlist * install(char * name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if((np == lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void*) np->defn);
    }

    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

void undef (char *name) {
    struct nlist	*pp, *np;
    for (pp = NULL, np = hashtab[hash(name)];
         np != NULL;
         pp = np, np = np->next)
        if (!strcmp(name, np->name)) {
            if (pp == NULL)
                hashtab[hash(name)] = np->next;
            else
                pp->next = np->next;
            free(np->name);
            free(np->defn);
            free(np);
            return;
        }
}
