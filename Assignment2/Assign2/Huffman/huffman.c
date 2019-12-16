//Name: Olu Owolabi
//Huffman coding


//This program will get the huffman coding for three diffrent novels in three diffrent languagees and at the end it will take the huffman coding
//of each novel and use the codes to get the original(english) translation
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define MAX_CHAR_VALUE 200
#define MAXWORTH 2147482647
#define MAXNODE 200

struct Huffman_node{
	char character;
	char* worth;
	int times;
	struct Huffman_node* left;
	struct Huffman_node* right;
};

int root;  
int types = 0;  
int label[MAX_CHAR_VALUE];  
char* coding[MAX_CHAR_VALUE];  
struct Huffman_node* tree[MAXNODE]; 

void init(char * input_file){
	
	FILE *fp;
	char c;
	int i;
	
	if ((fp = fopen(input_file , "r" )) == NULL){
		printf("Open Failed!");
		exit(1);
	}
	for ( i = 1 ; i <= MAXNODE ; i++){
		tree[i] = malloc(sizeof(struct Huffman_node));
		tree[i]->left = NULL;
		tree[i]->right = NULL;
		tree[i]->worth = NULL;
		tree[i]->times = 0;
		tree[i]->character = '\0';
	}
	memset( label , 0 , sizeof(label));
	while ((c = fgetc(fp)) != EOF){
		if (label[c+0] == 0){
			label[c+0] = ++types;
			tree[label[c+0]]->character = c;
		}
		tree[label[c+0]]->times++;
	}
	fclose(fp);
} /* init */

struct Huffman_node* combine(struct Huffman_node** Left_node , struct Huffman_node** Right_node){
	struct Huffman_node *ans;
	ans = malloc(sizeof(struct Huffman_node));
	ans->character = '\0';
	ans->left = *Left_node;
	ans->right = *Right_node;
	ans->times = (*Left_node)->times+(*Right_node)->times;
	ans->worth = NULL;
	return ans;	
} /* combine */

void swap(struct Huffman_node** xx , struct Huffman_node** yy){
	struct Huffman_node temp;
	temp = **xx;
	**xx = **yy;
	**yy = temp;
} /* swap */

void Build_Huffman(){
	int i,j;
	int last = types;
	int first_min_position,second_min_position;
	int first_min_value,second_min_value;
	int v[MAXNODE];
	
	memset( v , 0 , sizeof(v));
	for ( i = 1 ; i < types ; i++){
		first_min_value = MAXWORTH;
		second_min_value = MAXWORTH;
		for ( j = 1 ; j <= last ; j++){
			if ((!v[j]) && (tree[j]->times < first_min_value)){
				second_min_value = first_min_value;
				second_min_position = first_min_position;
				first_min_value = tree[j]->times;
				first_min_position = j;
			}
			else if ((!v[j]) && (tree[j]->times < second_min_value)){
				second_min_value = tree[j]->times;
				second_min_position = j;
			}
		}
		tree[++last] = combine(&tree[first_min_position] , &tree[second_min_position]);
		v[first_min_position] = 1;
		v[second_min_position] = 1;
	}
	root = last;
} /* Build_huffman_tree */

void calc_the_code(struct Huffman_node** now , char* parent_code , char* color){
	if ((*now) == NULL)
		return;
	(*now)->worth = malloc(sizeof(char)*(strlen(parent_code)+5));
	strcpy((*now)->worth , parent_code);
	(*now)->worth = strcat((*now)->worth , color);
	calc_the_code(&((*now)->left) , (*now)->worth , "0");
	calc_the_code(&((*now)->right) , (*now)->worth , "1");
} /* calc the huffman code for every leaves node */

void print_coding_schedule(struct Huffman_node* now , FILE *fp){
	if (now->character != '\0'){
		switch (now->character){
		 case '\n' : fprintf(fp , "\\n -> %s\n" , now->worth); break;
		 case '\t' : fprintf(fp , "\\t -> %s\n" , now->worth); break;
		 case ' '  : fprintf(fp , "Space -> %s\n" , now->worth); break;
		 default   : fprintf(fp , "%c -> %s\n" , now->character , now->worth); break;
		}
		coding[label[now->character+0]] = malloc(sizeof(now->worth));
		strcpy(coding[label[now->character+0]] , now->worth);
		return;
	}
	print_coding_schedule(now->left , fp);
	print_coding_schedule(now->right , fp);
} /*print the coding schedule */

void change(char *input_file , char *output_file){
	FILE *fp_in;
	FILE *fp_out;
	char c;
	fp_in = fopen(input_file , "r");
	fp_out = fopen(output_file , "w");
	while ((c = fgetc(fp_in)) != EOF)
		fprintf(fp_out , "%s" , coding[label[c+0]]);
	fclose(fp_in);
	fclose(fp_out);
} /* change */

void get_original_text(char *input_file , char *output_file){
	FILE *fp_in;
	FILE *fp_out;
	char c;
	struct Huffman_node *now = tree[root]; 
	fp_in = fopen(input_file , "r");
	fp_out = fopen(output_file , "w");
	while ((c = fgetc(fp_in)) != EOF){
		if (c == '0')
			now = now->left;
		else if (c == '1')
			now = now->right;
		if (now->character != '\0'){
			fprintf(fp_out , "%c" , now->character);
			now = tree[root];
		}
	}
	fclose(fp_in);
	fclose(fp_out);
} /* get original text */

int main(){
	FILE *fpo;
	init("TheThreeMuskSpan.txt"); 	//where to read the text from
	Build_Huffman(); 
	calc_the_code(&tree[root] , "" , ""); 
	
	fpo = fopen("Coding_schedule_TheThreeMuskSpan.txt","w");  
	print_coding_schedule(tree[root],fpo);   
	fclose(fpo);
	
	change("TheThreeMuskSpan.txt" , "output_for_TheThreeMuskSpan.txt"); 	//change the novel text into huffman coding
	get_original_text("output_for_TheThreeMuskSpan.txt" , "English_for_TheThreeMuskSpan.txt"); //translate the huffman encoding into the original language
	return 0;
}