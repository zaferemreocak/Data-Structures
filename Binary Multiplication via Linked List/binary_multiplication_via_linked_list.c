#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct node{
	int data;
	struct node *next;
};

void getNumber(struct node **head1 , struct node **head2);
int  Length(struct node *head);
void Push(struct node **head, int data);
void Multiplication(struct node *head1, struct node *head2);
void Reverse(struct node **head);
void printList(struct node *head);

int main(){
	struct node *Number1 = NULL;
	struct node *Number2 = NULL;
	getNumber(&Number1,&Number2);
	Reverse(&Number1);
	Reverse(&Number2);
	Multiplication(Number1 , Number2);
}

void getNumber(struct node **head1 , struct node **head2){
    int c=0;
    int d=0;
    int x = 0;
    int y = 0;
    struct node *controller1 = NULL;
    struct node *controller2 = NULL;
    
	printf("Please enter the first number in binary: ");
    while((c=getchar())!=EOF){
    	
		x = (int) c;
    	if(x != 48 && x != 49 && x != 10){
    		printf("\nNumber that you entered includes non-binary digit!\n");
    		printf("\nProgram exits now!");
    		exit(0);
		}
		else if(x == 48){
    		x = 0;
			Push(&*head1,x);		
		}
		
    	else if(x == 49){
    		x = 1;
			Push(&*head1,x);
		}

		else{
			break;
		}
	}
	
	printf("\nPlease enter the second number in binary: ");
    while((d=getchar())!=EOF){
    	
    	y = (int) d;

    	if(y != 48 && y != 49 && y != 10){
    		printf("\nNumber that you entered includes non-binary digit!\n");
    		printf("\nProgram exits now!");
    		exit(0);
		}
    	
    	else if(y == 48){
    		y = 0;
    		Push(&*head2,y);
		}
		
    	else if(y == 49){
			y = 1;
			Push(&*head2,y);		
		}
		
		else{
			break;
		}
	}
}

void Multiplication(struct node *head1 , struct node *head2){
	
	struct node *temp1 = head1;
	struct node *temp2 = head2;
	struct node *head3 = NULL;
	struct node *temp3 = head3;
	int lengthNumber1 = Length(head1);
	int lengthNumber2 = Length(head2);
	int sum = 0;
	int carry = 0;
	int i = 0;
	int digit = 0;
	int x = 0;
	int count2 = 0;
	int y = 0;
	
	if(lengthNumber2 == 1 && head2->data == 0){
		Push(&head3,0);
		printList(head3);
		free(head1);
		free(head2);
		return;
	}
	else if(lengthNumber2 == 1 && head2->data == 1){
		printList(head1);
		free(head1);
		free(head2);
		return;
	}
	
	while(head1 != NULL && head2 !=NULL){
		while(temp2 != NULL){
			while(temp1 != NULL){
					if(head3 == NULL){
						while(temp1 != NULL){
							sum = (temp1->data) * (temp2->data);
							Push(&head3, sum);
							temp1 = temp1->next;
													
						}
					temp3 = head3;
					temp3 = temp3->next;
					temp1 = head1;
					temp2 = temp2->next;		
					}
				
					if(head3 != NULL){
							if(temp3 == NULL){
								Push(&head3,0);
								temp3 = head3;
								while(temp3->next != NULL){
									temp3 = temp3->next;
								}
								sum = (temp1->data * temp2->data)+ carry;
							}
							if(temp3 != NULL){
								sum = (temp1->data * temp2->data) + (temp3->data) + carry;
							}
							if(sum >= 2){
								if(digit == 0){
									carry = (sum / 2);
									i = (sum % 2);
									temp3->data = i;								
								}
								else if(digit != 0){
									carry = (sum / 2);
									i = (sum % 2);
									temp3->data = i;									
								}
							}
							else{
								if(digit == 0){
									temp3->data = sum;
								}
								else if(digit != 0){
									temp3->data = sum;
									carry = carry/2;
								}

							}
							
							if(temp3->next == NULL){
								if(carry > 0 && temp1->next != NULL){
									temp1 = temp1->next;
									y = (temp1->data * temp2->data) + carry;
									if(y < 2){
										Push(&head3,y);
										carry = 0;
									}
									if(y >= 2){
										y = (y%2);
										Push(&head3,y);
									}
								}
								if(carry >= 0 && carry < 2 && temp1->next == NULL){
									if(carry == 0){
									}
									else{
										if(temp1->next == NULL){
											Push(&head3,carry);
											carry = 0;
										}
										if((temp1->data * temp2->data) + carry >= 2 && temp2->next == NULL){
											y = (temp1->data * temp2->data) + carry;
											y = y%2;
											Push(&head3,y);
										}
										if(carry > 0){
											Push(&head3,carry);
										}									
									}
								}
								y = 0;
							}
							temp3 = temp3->next;
					}
			digit++;		
			temp1 = temp1->next;		
			}
			if(temp2 != NULL){
				temp2 = temp2->next;
			}
		temp1 = head1;
		temp3 = head3;
		count2++;
		for(x = 0; x <= count2; x++){
			temp3 = temp3->next;
		}
		digit = 0;
		carry = 0;
		}
		if(temp2 == NULL){
			Reverse(&head3);
			printf("\nResult is: ");
			printList(head3);
			free(head1);
			free(head2);
			free(head3);
			break;
		}
	}
}

void Push(struct node **head,int data){
	
 struct node *newnode=(struct node*)malloc(sizeof(struct node));

 newnode->data=data;
 newnode->next=NULL;
 struct node *temp = *head;
 if(*head == NULL){
	*head = newnode;
	temp = newnode;
 }
 
 else{
	while(temp->next != NULL){
		temp = temp->next;
	}
 temp->next = newnode;
 }
}

int Length(struct node *head){
	int count1 = 0;
	while(head != NULL){
		count1++;
		head = head->next;
	}
	return count1;
}
void Reverse(struct node **head){
    struct node *currentNode = *head;
    struct node *prevNode = NULL;
    struct node *nextNode;

    while (currentNode != NULL){
        nextNode = currentNode->next;
        currentNode->next = prevNode;
        prevNode = currentNode;
        currentNode = nextNode;
    }
    *head = prevNode;
}
void printList(struct node *head){
	struct node *temp = head;
	while(temp != NULL){
		printf("%d" , temp->data);
		temp = temp->next;
	}
}
