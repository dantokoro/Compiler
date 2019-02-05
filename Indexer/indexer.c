#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Link list node */
struct Node
{	
	char word[30];
    int n;
    char dong[100];
    struct Node* next;
};

/* Given a reference (pointer to pointer) to the head
  of a list and an int, push a new node on the front
  of the list. */
void sortedInsert(struct Node** head_ref, struct Node* new_node) 
{ 
    struct Node* current; 
    /* Special case for the head end */
    if (*head_ref == NULL || strcmp((*head_ref)->word, new_node->word) >0 ) 
    { 
        new_node->next = *head_ref; 
        *head_ref = new_node; 
    } 
    else
    { 
        /* Locate the node before the point of insertion */
        current = *head_ref; 
        while (current->next!=NULL && strcmp(current->next->word, new_node->word) <0) 
        { 
            current = current->next; 
        } 
        new_node->next = current->next; 
        current->next = new_node; 
    } 
} 
void insert_word(struct Node** head_ref, char word[], int line)
{
	int len;
    struct Node* cur = (struct Node*) malloc(sizeof(struct Node));
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    cur = (*head_ref);
	while(cur!=NULL && strcmp(cur->word, word)!=0){
		cur = cur->next;
	}
	if(cur == NULL){			// Neu tu chua xuat hien -> tao node chua thong tin cua tu do
		strcpy(node->word, word);
		node->n = 1;
		node->dong[0] = line;
		node->dong[1] = '\0';
		sortedInsert(head_ref, node);
    /*	node->next = (*head_ref);
    	(*head_ref) = node;*/
	}else{						// Neu tu da xuat hien  -> chinh la cur
		cur->n = cur->n +1;
		len = strlen(cur->dong);
		if(cur->dong[len-1]!=line){
			cur->dong[len]=line;
			cur->dong[len+1]='\0';
		}
	}
}
int luu_stopw(char stopword[][30]){		// Luu stopw vao mang
  FILE *fp;	
  fp=fopen("stopw.txt", "r+");
  if(fp==NULL){
		printf("k mo duoc file.\n");
		return 0;
	}
  char stopw[30];
  char c;
  int i=0, len=0,j;
  while(fscanf(fp,"%s",stopw)!=EOF){
    c=fgetc(fp);
    for(j=0;j<strlen(stopw);j++){
    	stopword[i][j]=stopw[j];
	}
    i++;
  }
  len=i;
  fclose(fp);
  return len;
}

int luu_word(struct Node **head, char stopword[][30], int len){	// Lay du lieu va luu vao linked list
	FILE *fp;	
  	fp=fopen("vanban.txt", "r+");
  	if(fp==NULL){
		printf("k mo duoc file.\n");
		return 0;
	}
	char cpre = '.', c = '.';
	char word[30];
	int i=0, j, intc, is_in_stopw=0, line=1;
	c = fgetc(fp) ;
	while(c !=EOF){
		if(c=='\n'){
			line++;
		}
	    intc = (int) c;
	    if(isalpha(c)){
	    	if(intc>=65 && intc<=90 && cpre==' '){
	    		while(c!=' ' && c!='\n'){
	    			cpre=c;
	    			c=fgetc(fp);
	    			if(c=='\n'){
					line++;
					}
				}
			}
	    	else if(intc>=65 && intc<=90){
	    		c = tolower(c);
			}
			if(isalpha(c)){
				word[i]=c;
	    		i++;	
			}
		}
		else{
			word[i]='\0';
			if(strlen(word)){
			 	for(i=0;i<len;i++){		
					if(strcmp(stopword[i], word) == 0){
						is_in_stopw = 1;
						break;
					}
	 			}
	 			if(is_in_stopw==0){
	 				insert_word(head, word, line);
	 				
				 }
				else{
					is_in_stopw=0;
				}
			}
			i=0;
			word[0]='\0';
		}
	cpre=c;		
	c = fgetc(fp) ;

    }
	fclose(fp);
	return 1;
}

void printList(struct Node *head) 
{ 
	int i;
  while (head != NULL) 
  { 
    printf("%s %d", head->word, head->n);
   	for(i=0;i<strlen(head->dong);i++){
	 printf(",%d", head->dong[i]);
 	 }
 	 printf("\n");
     head = head->next; 
  } 
} 

int ghi_file_index(struct Node *head){
	FILE *fp;	
  	fp=fopen("index.txt", "w+");
  	if(fp==NULL){
		printf("k mo duoc file.\n");
		return 0;
	}
	int i;
  	while (head != NULL) 
	  { 
	    fprintf(fp,"%s %d", head->word, head->n);
	   	for(i=0;i<strlen(head->dong);i++){
		 fprintf(fp,",%d", head->dong[i]);
	 	 }
	 	 fprintf(fp,"\n");
	     head = head->next; 
	  } 
	fclose(fp);
	return 1;
}

int main()
{
	int i,j,len;
	char stopword[1000][30];
    struct Node* head = NULL;

    len = luu_stopw(stopword);
    /*for(i=0;i<len;i++){		// In stopw.txt
     	printf("%s\n", stopword[i]);
	 }*/
	luu_word(&head, stopword, len);

     printList(head);
	 if(ghi_file_index(head)) printf("Da luu Index vao file index.txt!!\n");
   
    return 0;
}

