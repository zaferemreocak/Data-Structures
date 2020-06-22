#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
FILE *writer;
struct node{
	int ID;
	char name[15];
	char surname[15];
	int day;
	int depth;
	int numberEntry;
	struct node *right;
	struct node *left;
};

int iDepth = 0;
int insertfirsttimecontroller = 0;
int counterDepth;
int c = 1;
int x = 0;
int firstnodesituation = 0;
int countersearch = 0;

void insert(struct node **tree, int ID , int entry , char name[15] , char surname[15] , int day , int depth){
		
    	struct node *temp = NULL;
    	temp = (struct node *)malloc(sizeof(struct node));
    	temp->left = temp->right = NULL;
    	temp->ID = ID;
    	strcpy(temp->name , name);
    	strcpy(temp->surname , surname);
    	temp->day = day;
    	if(counterDepth >= 4){
    		counterDepth = counterDepth % 4;
		}
    
    if(counterDepth == 0){ // RESPECT TO NAME
    	
		if(!(*tree)){
    		if(insertfirsttimecontroller == 0){
    		    temp->depth = iDepth;
				*tree = temp;
    		    insertfirsttimecontroller++;
    		    counterDepth = 0;
    		    iDepth = 0;
        		return;	
			}
			else if(insertfirsttimecontroller != 0){
				temp->depth = iDepth;
				*tree = temp;				
				counterDepth = 0;
				insertfirsttimecontroller++;
				iDepth = 0;
				return;
			}

    	}
    	
		int a;
    	a = strcmp(temp->name , (*tree)->name);
    	
    	if(a == -1){
			iDepth= iDepth + 1;
			if((*tree)->left != NULL){
				counterDepth = counterDepth + 1;
			}
			insert(&(*tree)->left, temp->ID , temp->numberEntry , temp->name , temp->surname , temp->day , iDepth);
		}
		
		else if(a == 1){
			iDepth = iDepth + 1;
			if((*tree)->right != NULL){
				counterDepth = counterDepth + 1;
			}
			insert(&(*tree)->right, temp->ID , temp->numberEntry , temp->name , temp->surname , temp->day , iDepth);
		}
	}
	
	else if(counterDepth == 1){ // RESPECT TO SURNAME	
		
		if(!(*tree)){
        	temp->depth = iDepth;
			*tree = temp;			
        	counterDepth = 0;
        	iDepth = 0;
        	return;
    	}
    	
    	int b;
    	b = strcmp(temp->surname , (*tree)->surname);
    	
    	if(b == -1){
    		iDepth = iDepth + 1;
    		if((*tree)->left != NULL){
    			counterDepth = counterDepth + 1;    			
			}
			insert(&(*tree)->left, temp->ID , temp->numberEntry , temp->name , temp->surname , temp->day , iDepth);
		}
		
		else if(b == 1){
    		iDepth = iDepth + 1;
    		if((*tree)->right != NULL){
    			counterDepth = counterDepth + 1;    			
			}
			insert(&(*tree)->right, temp->ID , temp->numberEntry , temp->name , temp->surname , temp->day , iDepth);
		}
	
		
	}
	
	else if(counterDepth == 2){ // RESPECT TO ID	
		
		if(!(*tree)){
			temp->depth = iDepth;			
        	*tree = temp;       	
        	counterDepth = 0;
        	iDepth = 0;
        	return;
    	}

    	if(temp->ID < (*tree)->ID){
    		iDepth = iDepth + 1;
    		if((*tree)->left != NULL){
    			counterDepth = counterDepth + 1;    			
			}
        	insert(&(*tree)->left, temp->ID , temp->numberEntry , temp->name , temp->surname , temp->day , iDepth);
    	}
    	else if(temp->ID > (*tree)->ID){
    		iDepth = iDepth + 1;
    		if((*tree)->right != NULL){
    			counterDepth = counterDepth + 1;    			
			}
        	insert(&(*tree)->right, temp->ID , temp->numberEntry , temp->name , temp->surname , temp->day , iDepth);
    	}
	
	}
	
	else if(counterDepth == 3){ // RESPECT TO DAY OF INTERNSHIP
		
		if(!(*tree)){
        	temp->depth = iDepth;       	
			*tree = temp;
        	counterDepth = 0;
        	iDepth = 0;
        	return;
    	}

    	if(temp->day < (*tree)->day){
    		iDepth = iDepth + 1;
    		if((*tree)->left != NULL){
    			counterDepth = counterDepth + 1;    			
			}
        	insert(&(*tree)->left, temp->ID , temp->numberEntry , temp->name , temp->surname , temp->day , iDepth);
    	}
    	else if(temp->day > (*tree)->day){
    		iDepth = iDepth + 1;
    		if((*tree)->right != NULL){
    			counterDepth = counterDepth + 1;    			
			}
        	insert(&(*tree)->right, temp->ID , temp->numberEntry , temp->name , temp->surname , temp->day , iDepth);
    	}		
		
	}
}

void printPreorder(struct node *tree){ //PRINT PREORDER TRAVERSAL
	
    if (tree){    	
        fprintf(writer ,"%d %d %d %s %s %d \n",tree->depth,tree->numberEntry,tree->ID,tree->name,tree->surname,tree->day);
        printPreorder(tree->left);
        printPreorder(tree->right);
    }
}

void printInorder(struct node *tree){//PRINT INORDER TRAVERSAL

    if (tree){
        printInorder(tree->left);
        fprintf(writer ,"%d %d %d %s %s %d \n",tree->depth,tree->numberEntry,tree->ID,tree->name,tree->surname,tree->day);
        printInorder(tree->right);
    }
}

void printPostorder(struct node *tree){//PRINT POSTORDER TRAVERSAL
	
    if (tree){
        printPostorder(tree->left);
        printPostorder(tree->right);
        fprintf(writer ,"%d %d %d %s %s %d \n",tree->depth,tree->numberEntry,tree->ID,tree->name,tree->surname,tree->day);			
		
    }
}

void count(struct node *tree){//COUNTING Nth NODE FROM THE BEGINNING OF THE ROOT 
    if(tree == NULL){
		}
    else{
        if((tree->left) != NULL){
        	if(firstnodesituation == 0){
        		tree->numberEntry = 1;
        		firstnodesituation++;
			}
        	if(x != 0){
        		c = tree->numberEntry;
			}
			c = 2*c;
        	tree->left->numberEntry = c;
        	count(tree->left);
        	x++;
		}
        if((tree->right) != NULL){
        	if(x != 0){
        		c = tree->numberEntry;
        		if(c == 1){
        			c = 1;
				}
			}
			c = 2*c+1;
        	tree->right->numberEntry = c;
        	count(tree->right);
        	x++;
		}
    }		
}

void search(struct node *tree, int keyID , char keyname[50] , char keysurname[50] , int keyday , int IDcontrol , int namecontrol , int surnamecontrol , int daycontrol){
	
	if(tree){
	
		if(IDcontrol == 1 && namecontrol == 1 && surnamecontrol == 1 && daycontrol == 1){
			if(keyID < tree->ID && strcmp(keyname , tree->name) == 1 && strcmp(keysurname , tree->surname) == 1 && keyday < tree->day){
				printf("%d %s %s %d\n" , tree->ID , tree->name , tree->surname , tree->day);
				countersearch++;
			}
			search(tree->left , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
			search(tree->right , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
		}
		else if(IDcontrol == 1 && namecontrol == 0 && surnamecontrol == 0 && daycontrol == 0){
			if(keyID < tree->ID && strcmp(keyname , tree->name) == -1 && strcmp(keysurname , tree->surname) == -1 && keyday > tree->day){
				printf("%d %s %s %d\n" , tree->ID , tree->name , tree->surname , tree->day);
				countersearch++;
			}
			search(tree->left , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
			search(tree->right , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);		
		}
		else if(IDcontrol == 0 && namecontrol == 1 && surnamecontrol == 0 && daycontrol == 0){
			if(keyID > tree->ID && strcmp(keyname , tree->name) == 1 && strcmp(keysurname , tree->surname) == -1 && keyday > tree->day){
				printf("%d %s %s %d\n" , tree->ID , tree->name , tree->surname , tree->day);
				countersearch++;
			}
			search(tree->left , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
			search(tree->right , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);		
		}
		else if(IDcontrol == 0 && namecontrol == 0 && surnamecontrol == 1 && daycontrol == 0){
			if(keyID > tree->ID && strcmp(keyname , tree->name) == -1 && strcmp(keysurname , tree->surname) == 1 && keyday > tree->day){
				printf("%d %s %s %d\n" , tree->ID , tree->name , tree->surname , tree->day);
				countersearch++;
			}
			search(tree->left , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
			search(tree->right , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);		
		}
		else if(IDcontrol == 0 && namecontrol == 0 && surnamecontrol == 0 && daycontrol == 1){
			if(keyID > tree->ID && strcmp(keyname , tree->name) == -1 && strcmp(keysurname , tree->surname) == -1 && keyday < tree->day){
				printf("%d %s %s %d\n" , tree->ID , tree->name , tree->surname , tree->day);
				countersearch++;
			}
			search(tree->left , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
			search(tree->right , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);		
		}
		else if(IDcontrol == 1 && namecontrol == 1 && surnamecontrol == 0 && daycontrol == 0){
			if(keyID < tree->ID && strcmp(keyname , tree->name) == 1 && strcmp(keysurname , tree->surname) == -1 && keyday > tree->day){
				printf("%d %s %s %d\n" , tree->ID , tree->name , tree->surname , tree->day);
				countersearch++;
			}
			search(tree->left , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
			search(tree->right , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);		
		}
		else if(IDcontrol == 0 && namecontrol == 1 && surnamecontrol == 1 && daycontrol == 0){
			if(keyID > tree->ID && strcmp(keyname , tree->name) == 1 && strcmp(keysurname , tree->surname) == 1 && keyday > tree->day){
				printf("%d %s %s %d\n" , tree->ID , tree->name , tree->surname , tree->day);
				countersearch++;
			}
			search(tree->left , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
			search(tree->right , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);		
		}
		else if(IDcontrol == 0 && namecontrol == 0 && surnamecontrol == 1 && daycontrol == 1){
			if(keyID > tree->ID && strcmp(keyname , tree->name) == -1 && strcmp(keysurname , tree->surname) == 1 && keyday < tree->day){
				printf("%d %s %s %d\n" , tree->ID , tree->name , tree->surname , tree->day);
				countersearch++;
			}
			search(tree->left , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
			search(tree->right , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);		
		}
		else if(IDcontrol == 1 && namecontrol == 1 && surnamecontrol == 1 && daycontrol == 0){
			if(keyID < tree->ID && strcmp(keyname , tree->name) == 1 && strcmp(keysurname , tree->surname) == 1 && keyday > tree->day){
				printf("%d %s %s %d\n" , tree->ID , tree->name , tree->surname , tree->day);
				countersearch++;
			}
			search(tree->left , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
			search(tree->right , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);		
		}
		else if(IDcontrol == 1 && namecontrol == 1 && surnamecontrol == 0 && daycontrol == 1){
			if(keyID < tree->ID && strcmp(keyname , tree->name) == 1 && strcmp(keysurname , tree->surname) == -1 && keyday < tree->day){
				printf("%d %s %s %d\n" , tree->ID , tree->name , tree->surname , tree->day);
				countersearch++;
			}
			search(tree->left , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
			search(tree->right , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);	
		}
		else if(IDcontrol == 1 && namecontrol == 0 && surnamecontrol == 1 && daycontrol == 1){
			if(keyID < tree->ID && strcmp(keyname , tree->name) == -1 && strcmp(keysurname , tree->surname) == 1 && keyday < tree->day){
				printf("%d %s %s %d\n" , tree->ID , tree->name , tree->surname , tree->day);
				countersearch++;
			}
			search(tree->left , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
			search(tree->right , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);		
		}
		else if(IDcontrol == 0 && namecontrol == 1 && surnamecontrol == 1 && daycontrol == 1){
			if(keyID > tree->ID && strcmp(keyname , tree->name) == 1 && strcmp(keysurname , tree->surname) == 1 && keyday < tree->day){
				printf("%d %s %s %d\n" , tree->ID , tree->name , tree->surname , tree->day);
				countersearch++;
			}
			search(tree->left , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
			search(tree->right , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);		
		}
		else if(IDcontrol == 0 && namecontrol == 0 && surnamecontrol == 0 && daycontrol == 0){
			if(keyID > tree->ID && strcmp(keyname , tree->name) == -1 && strcmp(keysurname , tree->surname) == -1 && keyday > tree->day){
				printf("%d %s %s %d\n" , tree->ID , tree->name , tree->surname , tree->day);
				countersearch++;
			}
			search(tree->left , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
			search(tree->right , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);		
		}
		else if(IDcontrol == 1 && namecontrol == 0 && surnamecontrol == 1 && daycontrol == 0){
			if(keyID < tree->ID && strcmp(keyname , tree->name) == -1 && strcmp(keysurname , tree->surname) == 1 && keyday > tree->day){
				printf("%d %s %s %d\n" , tree->ID , tree->name , tree->surname , tree->day);
				countersearch++;
			}
			search(tree->left , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
			search(tree->right , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);			
		}
		else if(IDcontrol == 1 && namecontrol == 0 && surnamecontrol == 0 && daycontrol == 1){
			if(keyID < tree->ID && strcmp(keyname , tree->name) == -1 && strcmp(keysurname , tree->surname) == -1 && keyday < tree->day){
				printf("%d %s %s %d\n" , tree->ID , tree->name , tree->surname , tree->day);
				countersearch++;
			}
			search(tree->left , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
			search(tree->right , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);			
		}
		else if(IDcontrol == 0 && namecontrol == 1 && surnamecontrol == 0 && daycontrol == 1){
			if(keyID > tree->ID && strcmp(keyname , tree->name) == 1 && strcmp(keysurname , tree->surname) == -1 && keyday < tree->day){
				printf("%d %s %s %d\n" , tree->ID , tree->name , tree->surname , tree->day);
				countersearch++;
			}
			search(tree->left , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
			search(tree->right , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);			
		}
	}
}

int main(){
	struct node *data = NULL;
	int ID;
	char name[15];
	char surname[15];
	int day;
	int depth;
	int entry;
	FILE *reader;	
	char filelocation[100];
	printf("Enter your file location please: ");
	scanf("%s" , filelocation);
	reader = fopen(filelocation , "r");
	writer = fopen("C:/Users/Emre/Desktop/output.txt" , "w");
	while(!feof(reader)){
		fscanf(reader , "%d %s %s %d" , &ID , name , surname , &day);
		insert(&data , ID , entry , name , surname , day , depth);
	}
	count(data);
	fprintf(writer , "-----------------Preorder Version Of Binary Search Tree-----------------\n");
	printPreorder(data);
	fprintf(writer , "\n-----------------");
	fprintf(writer , "Inorder Version Of Binary Search Tree-----------------\n");
	printInorder(data);
	fprintf(writer , "\n-----------------");
	fprintf(writer , "Postorder Version Of Binary Search Tree-----------------\n");
	printPostorder(data);
	fprintf(writer , "\n----------------------------------\n");
	fclose(writer);
	int IDcontrol;// ID controller
	printf("Enter 1 to search for GREATER ID or enter 0 to search for LESS ID: ");
	scanf("%d" , &IDcontrol);
	if(IDcontrol != 1 && IDcontrol != 0){
		printf("CANNOT SEARCH!");
		exit(0);
	}
	int keyID;
	printf("Enter an ID to compare with the tree members please: ");
	scanf("%d" , &keyID);
	int namecontrol;//name controller
	printf("Enter 1 to search for FORMER NAME or enter 0 to search for SUBSEQUENT NAME: ");
	scanf("%d" , &namecontrol);
	if(namecontrol != 1 && namecontrol != 0){
		printf("CANNOT SEARCH!");
		exit(0);
	}
	char keyname[50];
	printf("Enter a NAME to compare with the tree members please: ");
	scanf("%s" , keyname);
	int surnamecontrol;//surname controller
	printf("Enter 1 to search for FORMER SURNAME or enter 0 to search for SUBSEQUENT SURNAME: ");
	scanf("%d" , &surnamecontrol);
	if(surnamecontrol != 1 && surnamecontrol != 0){
		printf("CANNOT SEARCH!");
		exit(0);
	}
	char keysurname[50];
	printf("Enter a SURNAME to compare with the tree members please: ");
	scanf("%s" , keysurname);
	int daycontrol;//internship controller
	printf("Enter 1 to search for GREATER INTERNSHIP or enter 0 to search for LESS INTERNSHIP: ");
	scanf("%d" , &daycontrol);
	if(daycontrol != 1 && daycontrol != 0){
		printf("CANNOT SEARCH!");
		exit(0);
	}
	int keyday;
	printf("Enter a INTERNSHIP to compare with the tree members please: ");
	scanf("%d" , &keyday);
	printf("Search result:\n");	
	search(data , keyID , keyname , keysurname , keyday , IDcontrol , namecontrol , surnamecontrol , daycontrol);
	if(countersearch == 0){
		printf("NO MATCH!");
	}
	fclose(reader);
}
