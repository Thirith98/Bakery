#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>



#define N 3 // # of apprentices
#define MAX_A 20  // max # of apprentices
#define MAX_BREAD 100 // max # of breads to be made by the A.
int nbOfA = N;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int flour = INT_MAX;
int oil = INT_MAX;
int bp = INT_MAX; //baking powder

int breads = 0;


/* NODE STRUCTURE */
struct Node {

    int apprNb; //apprentice
    
    struct Node *next;
    struct Node *prev; 

};


/* NEW NODE FUNCTION */
struct Node* newNode(int i) {

    // Allocate Memory
    struct Node *node = (struct Node *) malloc(sizeof(struct Node));

    // Init data
    node->apprNb = i;
    node->next = NULL;
    node->prev = NULL; 

    return node;
}


struct Node *linkedList; // Kinda the Current node

/* CREATING NEW APPRENTICE AND ADDING TO LL */
void newApprentice(int apprentice) {

    if (!linkedList){
        linkedList = newNode(apprentice);
        
        return;
    }

    struct Node *newAppr = newNode(apprentice);

    newAppr->prev = linkedList;
    newAppr->next = linkedList->next;
    linkedList->next = newAppr;
    linkedList = newAppr;

    return;
}


void fireApprentice(int apprentice){


}



void *apprentice(void *j){
    int i = *(int*) j; // fix cast error

    while (1){
        
        pthread_mutex_lock(&mutex);
        if (breads == MAX_BREAD){
            pthread_mutex_unlock(&mutex);
            pthread_exit(j);
        }

        pthread_cond_wait(&cond, &mutex);

        /* pseudo code 
        if (array[i] == TRUE){ */   // PROBABLY NOT THE MOST PERFORMANT SOLUTION   
            flour -= 1;             // OTHER APPROACH: *MAYBE* have multiple condition 
            oil -= 1;               //      variables and specifically release the correct one
            bp -= 1;

            breads += 1;
            printf("Apprentice %d just made some bread.\n",i);    
    /*    }   */
        
    
    }
    
    
}




int main() {



    /* CREATING THREADS */
    pthread_t threads[MAX_A];

    for (int i = 0; i < N ; i++){
        if(pthread_create(&threads[i], NULL, apprentice, (void *)&i)){ // must get address of i first, before casting to void-ptr
            printf("Error in thread creation!\n");
            exit(1);
        } else {
            printf("Thread %d created!\n", i);
            newApprentice(i);


        }

    }

    /* LOGIC HANDLING ROUND ROBIN WITH LL */

    //HOW??
    // Multiple Mutexes and Conditions?
    // Array with value for specific apprentice set to true? 





    /* JOINING THREADS */

    for (int i = 0; i < N; i++){
        int val;
        pthread_join(threads[i], (void **)&val);
        printf("Thread is %d \n", val);
    }
    


    return 0;
}