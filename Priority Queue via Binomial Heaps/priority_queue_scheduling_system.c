       #include "binomial.h"
       #include "fatal.h"
       
       int SUM;
       int cputime;
	          
/* START: fig6_52.txt */
        typedef struct BinNode *Position;

        struct BinNode
        {
		    ElementType position;
		    ElementType constexetime;
		    double priorityValue;
		    ElementType arrivaltime;
		    ElementType firstcondition;
		    ElementType waitingtime;
            Position    LeftChild;
            Position    NextSibling;
        };

        struct Collection
        {
            int CurrentSize;
            BinTree TheTrees[ MaxTrees ];
        };

        BinQueue Initialize( void )
        {
            BinQueue H;
            int i;

            H = malloc( sizeof( struct Collection ) );
            if( H == NULL )
                FatalError( "Out of space!!!" );
            H->CurrentSize = 0;
            for( i = 0; i < MaxTrees; i++ )
                H->TheTrees[ i ] = NULL;
            return H;
        }

        static void DestroyTree( BinTree T )
        {
            if( T != NULL )
            {
                DestroyTree( T->LeftChild );
                DestroyTree( T->NextSibling );
                free( T );
            }
        }

        void Destroy( BinQueue H )
        {
            int i;

            for( i = 0; i < MaxTrees; i++ )
                DestroyTree( H->TheTrees[ i ] );
        }

        BinQueue MakeEmpty( BinQueue H )
        {
            int i;

            Destroy( H );
            for( i = 0; i < MaxTrees; i++ )
                H->TheTrees[ i ] = NULL;
            H->CurrentSize = 0;

            return H;
        }
        
        static void InsertWTtree(int waitingtime , BinTree T )
		{
			if( T != NULL){
				
				T->waitingtime = T->waitingtime + waitingtime;
				InsertWTtree(waitingtime , T->LeftChild);
				InsertWTtree(waitingtime , T->NextSibling);
			}
		}
		
		void InsertWT(int waitingtime , BinQueue H ){
		
			int i;
			for(i=0; i<MaxTrees; i++ ){
				
				InsertWTtree(waitingtime , H->TheTrees[ i ] );
			}
		}

        /* Not optimized for O(1) amortized performance */
        BinQueue Insert(ElementType position , ElementType constexetime , double priorityValue ,
		 ElementType arrivaltime , ElementType firstcondition , ElementType waitingtime , BinQueue H )
        {
            BinTree NewNode;
            BinQueue OneItem;
			int i;

            NewNode = malloc( sizeof( struct BinNode ) );
            if( NewNode == NULL )
                FatalError( "Out of space!!!" );
            NewNode->LeftChild = NewNode->NextSibling = NULL;
			
			NewNode->position = position;
			NewNode->constexetime = constexetime;
			NewNode->arrivaltime = arrivaltime;
			NewNode->priorityValue = priorityValue;
			NewNode->firstcondition = firstcondition;
			NewNode->waitingtime = waitingtime; 

            OneItem = Initialize( );
            OneItem->CurrentSize = 1;
            OneItem->TheTrees[ 0 ] = NewNode;

            return Merge( H, OneItem );
        }

/* START: fig6_56.txt */
        ElementType DeleteMin( BinQueue H )
        {
            int i, j;
            int MinTree;   /* The tree with the minimum item */
            BinQueue DeletedQueue;
            Position DeletedTree, OldRoot;
            double MinItem;

            if( IsEmpty( H ) )
            {
                Error( "Empty binomial queue" );
				MinItem=-Infinity;
                return MinItem;
            }

            MinItem = Infinity;
            for( i = 0; i < MaxTrees; i++ )
            {
                if( H->TheTrees[ i ] && H->TheTrees[ i ]->priorityValue < MinItem )
                {
                    /* Update minimum */
                    MinItem = H->TheTrees[ i ]->priorityValue;
					
                    MinTree = i;
                }
            }

            DeletedTree = H->TheTrees[ MinTree ];
            OldRoot = DeletedTree;
            DeletedTree = DeletedTree->LeftChild;
            free( OldRoot );

            DeletedQueue = Initialize( );
            DeletedQueue->CurrentSize = ( 1 << MinTree ) - 1;
            for( j = MinTree - 1; j >= 0; j-- )
            {
                DeletedQueue->TheTrees[ j ] = DeletedTree;
                DeletedTree = DeletedTree->NextSibling;
                DeletedQueue->TheTrees[ j ]->NextSibling = NULL;
            }

            H->TheTrees[ MinTree ] = NULL;
            H->CurrentSize -= DeletedQueue->CurrentSize + 1;

            Merge( H, DeletedQueue );
            return MinItem;
        }
/* END */

        BinTree FindMin( BinQueue H )//Find the minimum execution time value in Binomial Heap
        {
            int i;
            BinTree MinNode;
            MinNode = malloc( sizeof( struct BinNode ) );

            if( IsEmpty( H ) )
            {
                Error( "Empty binomial queue" );
				MinNode->priorityValue = 0;
                return MinNode;
            }

            MinNode->priorityValue = Infinity;
			
            for( i = 0; i < MaxTrees; i++ )
            {
                if( H->TheTrees[ i ] && H->TheTrees[ i ]->priorityValue < MinNode->priorityValue ) {
                    MinNode = H->TheTrees[i];
				}	
            }

            return MinNode;
        }

        int IsEmpty( BinQueue H )
        {
            return H->CurrentSize == 0;
        }

        int IsFull( BinQueue H )
        {
            return H->CurrentSize == Capacity;
        }

/* START: fig6_54.txt */
        /* Return the result of merging equal-sized T1 and T2 */
        BinTree CombineTrees( BinTree T1, BinTree T2 )
        {
            if( T1->priorityValue > T2->priorityValue )
                return CombineTrees( T2, T1 );
            if(T1->priorityValue == T2->priorityValue){
            	if(T1->arrivaltime > T2->arrivaltime){
            		return CombineTrees( T2 , T1 );
				}           	
			}
            T2->NextSibling = T1->LeftChild;
            T1->LeftChild = T2;
            return T1;
        }
/* END */

/* START: fig6_55.txt */
        /* Merge two binomial queues */
        /* Not optimized for early termination */
        /* H1 contains merged result */

        BinQueue Merge( BinQueue H1, BinQueue H2 )
        {
            BinTree T1, T2, Carry = NULL;
            int i, j;

            if( H1->CurrentSize + H2->CurrentSize > Capacity )
                Error( "Merge would exceed capacity" );

            H1->CurrentSize += H2->CurrentSize;
            for( i = 0, j = 1; j <= H1->CurrentSize; i++, j *= 2 )
            {
                T1 = H1->TheTrees[ i ]; T2 = H2->TheTrees[ i ];

                switch( !!T1 + 2 * !!T2 + 4 * !!Carry )
                {
                    case 0: /* No trees */
                    case 1: /* Only H1 */
                        break;
                    case 2: /* Only H2 */
                        H1->TheTrees[ i ] = T2;
                        H2->TheTrees[ i ] = NULL;
                        break;
                    case 4: /* Only Carry */
                        H1->TheTrees[ i ] = Carry;
                        Carry = NULL;
                        break;
                    case 3: /* H1 and H2 */
                        Carry = CombineTrees( T1, T2 );
                        H1->TheTrees[ i ] = H2->TheTrees[ i ] = NULL;
                        break;
                    case 5: /* H1 and Carry */
                        Carry = CombineTrees( T1, Carry );
                        H1->TheTrees[ i ] = NULL;
                        break;
                    case 6: /* H2 and Carry */
                        Carry = CombineTrees( T2, Carry );
                        H2->TheTrees[ i ] = NULL;
                        break;
                    case 7: /* All three */
                        H1->TheTrees[ i ] = Carry;
                        Carry = CombineTrees( T1, T2 );
                        H2->TheTrees[ i ] = NULL;
                        break;
                }
            }
            return H1;
        }
		
		void preMechaSchedule(BinQueue H , int eMax , int q){
			if(!IsEmpty(H)){
				int ei;
				double tempei;
				double priorityValue = 0;
				BinTree minNode = FindMin(H);
				ei= minNode->constexetime;
						if(ei - q <= 0){
							SUM = SUM + minNode->waitingtime;
							DeleteMin(H);
							if(q-ei > 0){
								InsertWT(ei , H );
								cputime = cputime + ei;
							}
							else if(q-ei == 0){
								InsertWT(q , H);
								cputime = cputime + q;
							}
						}
						else{
							ei = ei - q;
							ei = ei * 2;
							eMax = 3 * eMax * (-1);
							tempei =  1 /exp(pow((ei/(double)eMax),3.0));
							ei = ei / 2;
							priorityValue = tempei * ei;
							cputime = cputime + q;
							ElementType a = minNode->position;
							ElementType b = minNode->arrivaltime;
							ElementType c = minNode->waitingtime;
							DeleteMin(H);
							InsertWT(q , H);
							Insert(a , ei , priorityValue , b , 1 , c , H);
						}
			}
		}
		main(){
			double AWT;
			int minq;
			double minAWT = Infinity;
			BinQueue H1 , H2;	
			BinTree p, r[20]={NULL};
			int position;
			double tempexetime;
			int constexetime = 0;			
			int arrivaltime = 0;
			int waitingtime = 0;
			int firstcondition = 0;
			int eMax = 0;
			int time = 0;
			int q = 1;
			int counter = 0;
			H1 = Initialize();
			FILE *reader , *find_eMax;
			find_eMax = fopen("C:/Users/Emre/Desktop/input.txt" , "r");
			while(!feof(find_eMax)){
				fscanf(find_eMax , "%d %d %d" , &position , &constexetime , &arrivaltime);
				if(constexetime > eMax){
					eMax = constexetime;
				}
			}
			fclose(find_eMax);
			for(q=1; q <= 10; q++){
				SUM = 0; time = 0; counter = 0; cputime = 0;
				reader = fopen("C:/Users/Emre/Desktop/input.txt" , "r");
				fscanf(reader , "%d %d %d" , &position , &constexetime , &arrivaltime);
					while(!feof(reader)){
						if(arrivaltime == time){
							if(cputime != time){
								waitingtime = cputime - arrivaltime;
							}
							else{
								waitingtime = 0;
							}
							Insert(position , constexetime , constexetime , arrivaltime , firstcondition , waitingtime , H1);
							counter++;
							if(cputime == time){
								preMechaSchedule(H1 , eMax , q);
							}
							fscanf(reader , "%d %d %d" , &position , &constexetime , &arrivaltime);
							time = time+1;					
						}
						else{
							if(!IsEmpty(H1)){
								if(cputime == time){
									preMechaSchedule(H1 , eMax , q);
								}
							}					
							time = time+1;
						}
					}
					fclose(reader);
					
					while(!IsEmpty(H1)){
						if(arrivaltime == time){
							if(cputime == time){
								preMechaSchedule(H1 , eMax , q);
							}
							if(cputime != time){
								waitingtime = cputime - arrivaltime;
							}
							Insert(position , constexetime , constexetime , arrivaltime , firstcondition , waitingtime , H1);
							counter++;
						}
						else{
							if(cputime == time){
								preMechaSchedule(H1 , eMax , q);
							}

						}
						time = time + 1;
					}
					if(IsEmpty(H1)){
						AWT = ((double)SUM / counter);
						if(AWT < minAWT){minAWT = AWT; minq = q;}
						printf("q%d %lf\n" , q , AWT);							
					}			
			}
			printf("\nOptimal quantum value is %d as considering your input with %lf average waiting time!" , minq , minAWT);
			MakeEmpty(H1);
		}
