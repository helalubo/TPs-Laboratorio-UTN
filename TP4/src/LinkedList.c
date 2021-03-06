#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;

    this = (LinkedList*) malloc(sizeof(LinkedList));
    if(this!=NULL)
    {
        this->size = 0;
        this->pFirstNode = NULL;
    }

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList *this)
{
    int returnAux = -1;

    if (this != NULL)
    {
        returnAux = this->size;
    }
    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList *this, int nodeIndex)
{

    Node *pNode = NULL;

    if (this != NULL)
    {

        if (nodeIndex >= 0 && nodeIndex < ll_len(this))
        {

            pNode = this->pFirstNode;


            for (int i = 0; i < nodeIndex; i++)
            {
                pNode = pNode->pNextNode;
            }




        }
    }

    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* prev = NULL;
    Node* next= NULL;
    Node* nuevoNodo = NULL;

    if ( this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this) )
    {

        nuevoNodo = (Node*) malloc(sizeof(Node)); ///Creo con memoria dinamica

        if(nuevoNodo != NULL)
        {
            nuevoNodo->pElement = pElement; ///Le paso el elemento
///(1
            if(nodeIndex == 0 ) ///Si es el primer elemento /// 2 cosas ! => linkedlist
            {
                this->pFirstNode = nuevoNodo; /// paso a linkedlist la direccion de memoria del primer elemento
                if(ll_len(this) != 0)  ///En el caso de que la lista ya tenga elementos se le debe pasar a este la direccion del siguiente y en caso contraro seria NULL
                {
                    next = getNode(this,nodeIndex+1);
                    nuevoNodo->pNextNode = next;
                }
                else
                {

                    nuevoNodo->pNextNode = NULL;
                }
            }
            else
            {

                prev = getNode(this,nodeIndex-1); /// Si no me pide el nodo numero 0 entonces voy a necesitar saber cual es el nodo anterior al cual le tendre que pasar la direccion de memoria del siguiente
                prev->pNextNode = nuevoNodo; /// Si se creo el prev entonces le pasamos a este la posicion del nodo nuevo a su nextNode debido a que para linkedlist tenemos que ligar la memoria del anterior con la memoria del siguiente para ligarlo
                next = getNode(this,nodeIndex+1);
                nuevoNodo->pNextNode = next;

                if(nodeIndex == ll_len(this))
                {
                    nuevoNodo->pNextNode = NULL;
                }



            }
///(2









            this->size++;
            returnAux = 0;

        }







    }
    return returnAux;
}


/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    //int indice = 0;
    //Node* actual;



    if(this != NULL )
    {
        addNode(this,  ll_len(this),pElement);
        returnAux = 0;
    }



    return returnAux;
}

/** \brief Retorna un puntero al elemento que se encuentra en el �ndice especificado.
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* auxNode;




    if(this != NULL && index <= ll_len(this) && index >= 0)
    {

        auxNode= getNode(this,index);
        if(auxNode != NULL)
        {
            returnAux = auxNode->pElement;
        }



    }



    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* actual;



    if ( this != NULL && index >= 0 && index < ll_len(this) )
    {

        actual = getNode(this,index);

        if(actual != NULL)
        {
            actual->pElement = pElement;
            returnAux = 0;

        }



    }


    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* actual;
    Node* next;
    Node* prev;



    if ( this != NULL && index >= 0 && index < ll_len(this) )
    {

        actual = getNode(this,index);




        if(actual != NULL)
        {
            next = getNode(this,index+1);
            if(next != NULL)
            {
                if(index !=0)
                {
                    prev = getNode(this,index-1);
                    prev->pNextNode = next;
                    free(actual);

                }
                else
                {

                    this->pFirstNode = next;
                    free(actual);
                }

            }





        }


        this->size--;
        returnAux = 0;
    }


    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    Node* nodo;
    int i;

    if(this != NULL)
    {

        for(i=0; i<ll_len(this); i++)
        {
            nodo = getNode(this,i);
            if(nodo != NULL)
            {
                nodo->pElement = NULL;

            }

        }
        this->size = 0;
        returnAux = 0;

    }



    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        free(this);
        returnAux = 0;
    }


    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    Node* nodo;

    if(this != NULL)
    {

        for(i = 0; i<ll_len(this); i++)
        {

            nodo = getNode(this,i);

            if(nodo->pElement == pElement)
            {

                returnAux = i;
                break;
            }



        }
    }




    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        if( ll_len(this) > 0 )
        {
            returnAux = 0;
        }
        else
        {
            returnAux = 1;
        }
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    Node* prev= NULL;
    Node* nuevoNodo= NULL;

    if(this!=NULL && index>=0 && index<=ll_len(this))
    {
        nuevoNodo= (Node*)malloc(sizeof(Node));

        if(nuevoNodo!=NULL)
        {
            nuevoNodo->pElement = pElement;
            nuevoNodo->pNextNode = NULL;

            prev= getNode(this, index-1);

            if(prev==NULL)
            {
                this->pFirstNode = nuevoNodo;
            }
            else
            {
                nuevoNodo->pNextNode = prev->pNextNode; /// importante
                prev->pNextNode = nuevoNodo;
            }
            this->size++;
            returnAux=0;
        }
    }

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;


    if(this!=NULL && index>=0 && index<=ll_len(this))
    {

        returnAux = ll_get(this,index);
        ll_remove(this,index);

    }





    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    Node* nodo = NULL;

    if(this != NULL)
    {
        returnAux = 0; //importancia del return fuera del for

        for(int i = 0; i<ll_len(this); i++)
        {

            nodo = getNode(this,i);


            if(nodo->pElement == pElement)
            {
                returnAux = 1;
                break;


            }

        }


    }



    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;

    void* Element1 = NULL;
    void* Element2 = NULL;


    if(this != NULL && this2 != NULL)
    {
        returnAux = 1;

        for(int i =0; i<ll_len(this); i++)
        {
            Element1 = ll_get(this,i);
            Element2 = ll_get(this2,i);


            if(Element1 != Element2)
            {
                returnAux = 0;
            }


        }

    }


    return returnAux;
}


/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int i;
    void* pElement;


    if(this != NULL && from >=0 && to> from && to<= ll_len(this))
    {

        cloneArray = ll_newLinkedList();

        if(cloneArray != NULL)
        {

            for(i = from; i<to; i++)
            {
                pElement = ll_get(this,i);


                if(pElement != NULL)
                {
                    ll_add(cloneArray,pElement);
                }

            }
        }


    }


    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    void* pElement = NULL;

    if(this != NULL)
    {
        cloneArray = ll_newLinkedList();

        if(cloneArray != NULL)
        {
            for(int i= 0; i<ll_len(this); i++)
            {
                pElement = ll_get(this,i);

                if(pElement != NULL)
                {
                    ll_add(cloneArray,pElement);
                }


            }
        }
    }



    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;
    void* pAux = NULL;
    void* elementoI = NULL;
    void* elementoJ = NULL;




    if(this != NULL && pFunc != NULL && (order == 0 || order == 1))
    {


        for(int i = 0; i< ll_len(this) - 1; i++)
        {
            for(int j = i+1; j<ll_len(this); j++)
            {
            elementoI = ll_get(this,i);
            elementoJ = ll_get(this,j);

            switch(order)
            {

          case 0:

            if(pFunc(elementoI,elementoJ)<0)
            {
                pAux = elementoI;
                ll_set(this,i,elementoJ);
                ll_set(this,j,pAux);

            }
            break;

             case 1:

            if(pFunc(elementoI,elementoJ)>0)
            {
                pAux = elementoI;
                ll_set(this,i,elementoJ);
                ll_set(this,j,pAux);
            }
            break;

            }



            }
        }

         returnAux = 0;
    }




    return returnAux;
}

