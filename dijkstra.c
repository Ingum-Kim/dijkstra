#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

typedef struct{
	int start;
	int end;
}edge;

void dijkstra(int n, int **W, edge *F){
	int i;
	int count = 0;
	int min;
	edge e;
	int vnear;
	int touch[n+1];
	int length[n+1];

	for(i = 2; i <= n; i++){
		touch[i] = 1;
		length[i] = W[1][i];
	}
	
	while(count < n - 1){
		min = INT_MAX;
		for(i = 2; i <= n; i++)
			if(length[i] > 0 && length[i] < min){
				min = length[i];
				vnear = i;
			}
		e.start = touch[vnear]; 
		e.end = vnear;
		F[count] = e;

		for(i = 2; i <= n; i++)
			if(W[vnear][i] != INT_MAX && length[vnear] + W[vnear][i] < length[i]){
				length[i] = length[vnear] + W[vnear][i];
				touch[i] = vnear;
			}
		length[vnear] = -1;

		count++;
	}
}

void main(){
	int i,j;
	int n;
	int **W;
	int num;
	edge *F;

	printf("Directed graph?(Yes : 1, No : 0) : ");
	scanf("%d",&num);
	
	printf("노드의 수 : ");
	scanf("%d",&n);
	W = (int**)malloc(sizeof(int*) * (n + 1));
	for(i = 0; i < n+1; i++)
		W[i] = (int*)malloc(sizeof(int) * (n+1));
	F = (edge*)malloc(sizeof(edge) * (n-1));

	printf("edge 정보 입력 : ");
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			scanf("%d",&W[i][j]);
			if(W[i][j] == -1)
				W[i][j] = INT_MAX;
		}
	}
	
	printf("\n입력 그래프 edge :\n");
	if(num){
		for(i = 1; i <=n; i++){
			for(j = 1; j <= n; j++){
				if(W[i][j] != 0 && W[i][j] != INT_MAX)
					printf("(%d , %d), weight: %d\n",i,j,W[i][j]);
			}
		}
	}else{
		for(i = 1; i <=n; i++){
			for(j = i + 1; j <= n; j++){
				if(W[i][j] != 0 && W[i][j] != INT_MAX)
					printf("(%d , %d), weight: %d\n",i,j,W[i][j]);
			}
		}
	}

	dijkstra(n,W,F);
	printf("\n결과 edge :\n");
	for(i = 0; i < n-1; i++)
		printf("(%d , %d), weight: %d\n",F[i].start,F[i].end,W[F[i].start][F[i].end]);
	
	for(i = 0; i < n+1; i++)
		free(W[i]);
	free(W);
	free(F);
}
