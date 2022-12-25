typedef struct Block
{
    struct Block *prev, *next;
    uint32_t TAG;
      
} Block;
 
typedef struct Set
{
    unsigned count;  
    unsigned ways; 
    Block *front, *rear;
    Block* *array;
} Set;
 
typedef struct cache
{
    int capacity; 
    Set* *array;
} cache;
 
Block* newBlock( uint32_t TAG )
{
    Block* temp = (Block *)malloc( sizeof( Block ) );
    temp->TAG = TAG;
    temp->data = data;
    temp->prev = temp->next = NULL;
    return temp;
}
 
Set* createSet( int ways )
{
    Set* temp = (Set *)malloc( sizeof( Set ) ); 
    temp->count = 0;
    temp->front = temp->rear = NULL;
    temp->ways = ways;
    int i;
    temp->array = (Block **) malloc( temp->ways * sizeof( Block* ) );
    for( i = 0; i < temp->ways; ++i )
        temp->array[i] = NULL;
    return temp;
}
 

cache* createcache( int capacity, int ways )
   {

    cache* temp = (cache *) malloc( sizeof( cache ) );
    temp->capacity = capacity;
    temp->array = (Set **) malloc( temp->capacity * sizeof( Set* ) );
    int i;
    for( i = 0; i < temp->capacity; ++i )
        temp->array[i] = createSet(ways);
 
    return temp;
}
 
int AreAllFramesFull( Set* set )
{
    return set->count == set->ways;
}
 

int isSetEmpty( Set* set )
{
    return set->rear == NULL;
}
 
void deQueue( Set* set )
{
    if( isSetEmpty( set ) )
        return;
 
    if (set->front == set->rear)
        set->front = NULL;
 
    Block* temp = set->rear;
    set->rear = set->rear->prev;
 
    if (set->rear)
        set->rear->next = NULL;

    for(int i=0;i<set->ways;i++){
	if(set->array[i]->TAG == temp->array[i]->TAG) {
		set->array[i] = NULL;
	}
    }

    free( temp );

    set->count--;
}
 
void Enqueue( Set *set, uint32_t TAG )
{
 
    if ( AreAllFramesFull ( set ) )
    {   deQueue( set );
    }
 
    Block* temp = newBlock( TAG );
    temp->next = set->front;
 
    if ( isSetEmpty( queue ) )
        set->rear = set->front = temp;
    else 
    {
        set->front->prev = temp;
        set->front = temp;
    }
    set->array[count] = temp;
    set->count++;
}
 

int ReferenceBlock( cache* L1, uint32_t PC, int TAG_size, int offset, int BlockNo_size )
{   uint32_t TAG, Block_no;
    
    Block_no = (PC<<TAG_size)>>(TAG_size+offset);
    TAG = PC>>(BlockNo_size+offset);
    
    Set* set = L1->array[ Block_no ];
    
    for(int i=0;i<set->ways;i++) {
	if(TAG == set->array[i]->TAG) {
		Block* block = set->array[i];
		break;
	}		
		
    }
    if ( block == NULL )
        Enqueue( set, TAG );
 
    else if (block != set->front)
    {
        block->prev->next = block->next;
        if (block->next)
           block->next->prev = block->prev;
         if (block == set->rear)
        {
           set->rear = block->prev;
           set->rear->next = NULL;
        }
        block->next = set->front;
        block->prev = NULL;
        block->next->prev = block;
 
        block->front = block;
    }
}


