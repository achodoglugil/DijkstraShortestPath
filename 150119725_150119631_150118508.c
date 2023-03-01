// Enes Sagiroglu 150119725
// Ahmet Cagri Hodoglugil 150118508
// Utku Bayguven 150119631
//Finding shortest path with dijkstra's algorithm

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define INFINITY 10000

int graph[325][325]; //stores the graph
char node[500]; // stores the all vertices in the input file
int num_edge; // number of unique vertices

void dijkstra(int graph[325][325], int vertices, int start, int dest){
	
	
	int cost[325][325];
	int distance[325];
	int visited[325];
	int path[325];
	int i,j,count;
	int mindistance,nextnode;
	
	//in this nested loop we store the costs in cost array, the cost is INF if there is no direct path.
	for(i = 0; i<vertices; i++){
		
		for(j = 0; j<vertices; j++){
			
			if(graph[i][j] == 0){
				cost[i][j] = INFINITY;
			}
			else{
				cost[i][j] = graph[i][j];
			}
		}
	}
	//we store the distance in distance array.
	for(i = 0; i < vertices; i++){
		distance[i] = cost[start][i];
		path[i] = start;
		visited[i] = 0;
	}
	distance[start] = 0;
	visited[start] = 1;
	count = 1;
	
	while(count < vertices-1){
		mindistance = INFINITY;
		
		for(i = 0; i<vertices ; i++){
			
			if(distance[i] < mindistance && !visited[i]){
				mindistance = distance[i];
				nextnode = i;
			}
		}
		visited[nextnode] = 1;
		
		for(i = 0; i<vertices ; i++){
			if(!visited[i]){
				if((mindistance + cost[nextnode][i]) < distance[i]){
					distance[i] = mindistance + cost[nextnode][i];
					path[i] = nextnode;
				}
			}
		}
		count++;
	}
	// we print distance from source to destination and the shortest path.
	if(dest != start){
		printf("The distance from node %c to node %c is %d\n",start+65,dest+65,distance[dest]);
		printf("The path is %c",dest+65);
			
		j = dest;
		do{
			j = path[j];
			printf("<-%c", j+65);
		}while(j != start);
	}
	printf("\n");
}


int count_edges(char* str) {

    int ASCII[128] = { 0 }; //ASCII keeps ASCII values
    int i, num_edge = 0;

    //we read each character of str[]
    for (i = 0; i < strlen(str); ++i) {
        //set the position corresponding 
        ASCII[str[i]] = 1;
    }
    //we are counting number of vertices, repeated elements are only counted once
    for (i = 0; i < 128; ++i) {
        num_edge += ASCII[i];
    }

    return num_edge;

}


void read_File(){
	
	char input[50];
	int distance;
	char *source;
	int count = 0;
	FILE *inpf;
	int i = 0,j = 0;
	
	//we take file name as a input from user and we read
	printf("Enter the name of input file:");
	scanf("%s",input);
	
	inpf = fopen(input, "r");
	char line[50];
	if (inpf == NULL){
    puts("\nThere is no such a file...");
    exit(0);
	}
	
	
	printf("File Content:\n");
	//we printing the file.
	while (fgets(line , 1000 , inpf) != NULL){
    char *temp;
    char *dest;
    //we read the info separated with ' , ' keep them in variables.
	source = strtok(line , ",");
    temp =strtok(NULL, ",");
    
    dest = temp;
    
    //we convert distance to integer.
    distance = atoi(strtok(NULL, ","));
    
	printf("%s %s %d\n", source, dest, distance);
	
	//we store all the vertices in an array to count the number of vertices.
	node[i] = source[0];
	i += 1;
	node[i] = dest[0];
	i += 1;
	
	//Since source and dest is chars, we take their ASCII codes and keep them in graph_source and graph_dest.
	//Since we have to store them in an array, we substract 65 from the values. (capital letters' ASCII codes starts form 65)
	int graph_source = *source-65;
	int graph_dest = *dest-65;
	 
	//We crate our graph by storing the distance values in an adjacency matrix.
	graph[graph_source][graph_dest] = distance;
	graph[graph_dest][graph_source] = distance;

	
	
}
	fclose(inpf);
	
	//we store the num of vertices in num_edge
	num_edge = count_edges(node);
} 
void print_matrix(){
	
	int i,j;
	printf("%6c",65);
	for(i = 1; i<num_edge; i++){
		
		printf("%5c",65+i);	
		
	}
	printf("\n");
	
	
	for(i = 0; i<num_edge ; i++){
		printf("%c",65+i);
		for(j = 0; j<num_edge; j++){
			printf("%5d",graph[i][j]);
		}
		printf("\n");
	}
}



void find_path(){
	
	char destination;
	char source;

	printf("Enter the starting point:");
	scanf("%s",&source);

	printf("Enter the ending point:");
	scanf("%s",&destination);
	
	destination = toupper(destination);
	source = toupper(source);
	
	int start = source-65;
	int stop = destination-65;
	printf("\n");
	
	//we take source and destination from the user then we call the dijkstra's algorithm.
	dijkstra(graph, num_edge, start, stop);
	
	
}

void menu(){
	int choice;
	
	printf("----------Welcome----------\n");
	printf("[1] Read file\n");
	printf("[2] Print matrix\n");
	printf("[3] Find the shortest path\n");
	printf("[4] Quit\n");
	printf("Selection:");
	scanf("%d",&choice);
	
	switch (choice){
		case 1:
			read_File();
			menu();
			break;
		case 2:
			print_matrix();
			menu();
			break;
		case 3:
			find_path();
			menu();	
			break;
		case 4:
			printf("\nHave a nice day....\n");
			break;
			
		default:
			printf("\nInvalid choice...\n");
			menu();
			break;
					
	}
	
}
int main(){
	
	menu();

	

	return 0;
}
