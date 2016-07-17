// Dijkstra 
#include <stdio.h>
#include <limits.h> //defines!
 
// Numero de vértices
#define V 8
 
// Função para encontrar o vértice com menor distancia que ainda esta aberto
int minDistancia(int dist[], bool fechado[]){
   // Inicializar valor minimo
   int min = INT_MAX, min_index; //INT_MAX: maior valor de int, e min_index: menor indice
 
   for (int v = 0; v < V; v++)
     if (fechado[v] == false && dist[v] <= min) //se o Vérticie ainda não estiver "fechado, ok" E distancia for menor ou igual a min (que inicia com infinito)
         min = dist[v], min_index = v; //atualiza o vestice encontrado e a distancia minima
 
   return min_index; //retorna o vértice com a menor ditância
}
 
int imprime(int dist[], int anterior[V]){
   printf("Predio   Distancia da Origem	 Predio Anterior\n");
   for (int i = 0; i < V; i++)
      printf("%d \t\t %d \t\t    %d\n", i+1, dist[i], anterior[i]+1);
}

int rota(int dist[], int anterior[], int origem, int destino){
	//TRABALHA SÓ COM INDICES E NÃO NUMERO DE PREDIOS
	//origem já vem descontada com -1
	int temp = origem;
	while (temp != destino){
		//quando damos em predio temos que somar 1, pois estamos trabalhando com os indices
		printf ("\nSiga do predio %d para o predio %d\n", temp+1, anterior[temp]+1); //
		temp = anterior[temp]; //temp = proximo predio (indice) --- exemplo, predio 1 esta no indice 0
	}
}
 
// Função que implementa o algoritmo de menor caminho DIJKSTRA
// Usando matriz de adjacencia para representação do grafo
void dijkstra(int grafo[V][V], int origem, int anterior[V], int dist[]){
     
 	
     bool fechado[V]; //guarda quais vértices já tiveram suas distancias calculadas
     
     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, fechado[i] = false; // Inicializa todas as distãncias como infinito e aberto "fechado=false", pois estará aberto para passagem 
 
     // Distancia do vértice origem é 0
     dist[origem] = 0;
 
     // Encontrar o caminho mais curto para todos os vértices 
     for (int cont = 0; cont < V-1; cont++){ //percorre todos os vétices menos o ultimo (pois já tera sido calculada sua distancia)
       
       int atual = minDistancia(dist, fechado); //pega o vértice aberto com menor distancia (primeira iteração é a origem)
 
       // marque o vértice escolhido como processado ("ok");
       fechado[atual] = true;
 
       // atualiza os valores de distancia dos vértices adjacentes (irmaos) ao atual
       for (int irmao = 0; irmao < V; irmao++) //V é total de vértice 
		 //o vértice "irmao" está aberto? 
         if (fechado[irmao] == false){ 
         	//existe um camiho entre o vértice atual e o vértice adjacente (imrão)?
         	if (grafo[atual][irmao] != 0){
         		//a distancia do vértice atual + arestaAtual é menor que minha distancia adjacente (vértice v) TODOS INICIAM COM INFINITO?
         		if (dist[atual] + grafo[atual][irmao] < dist[irmao]){
         			//atualizando minha distancia atual para distancia do vértice atual + arestaAtual -- 
         			dist[irmao] = dist[atual] + grafo[atual][irmao];
         			//salva o anterior do vértice atualizado
         			anterior[irmao] = atual;
				 }
			 }
		 }
     }
 
     
}
 
int main(){
	//melhor caminho de um prédio a qualquer outro:
	int predioOrigem, predioDestino;
	printf ("Digite o predio de origem: ");
	scanf("%d", &predioOrigem);
	printf ("Digite o predio de destino: ");
	scanf ("%d", &predioDestino);
	
	int origem = predioOrigem -1;
	int destino = predioDestino -1;
	
	if (origem >= V || destino >= V || origem < 0 || destino < 0){
		printf ("\nRelacao de predios invalida!\n");
		return 0;
	}
	
    int dist[V];     	//guarda distancia de cada vértice da origem
    int anterior [V]; 	//guarda o vértice anterior no caminho para o destino (origem djiskra)
    int grafo[V][V] =  
    {		// 1   2    3    4    5    6    7    8
			{  0, 54,  22, 108,   0,   0,   0,   0},// predio 1 (indice 0)
			{ 54,  0,   0,  54,   0,   0,   0,   0},// predio 2
			{ 22,  0,   0,  89,  40,   0,   0,   0},// predio 3
			{108, 54,  89,   0,  65,  68,   0,   0},// predio 4
			{  0,  0,  40,  65,   0,  29,  45,   3},// predio 5
			{  0,  0,   0,  68,  29,   0,   0,   0},// predio 6
			{  0,  0,   0,   0,  46,   0,   0,  38},// predio 7
			{  0,  0,   0,   0,   3,   0,  38,   0} // predio 8
	};
 
 	anterior[destino] = destino;
 	
 	//trabalha com os indices
    dijkstra(grafo, destino, anterior, dist); //grafo, destino(numero do predio-1 = indice)
 	
 	if (origem == destino){
 		printf ("Voce ja se encontra no predio!\n");
	 }else{
		rota (dist, anterior, origem, destino); 	
	 }
	 
	//imprime(dist, anterior);
    
	return 0;
}
