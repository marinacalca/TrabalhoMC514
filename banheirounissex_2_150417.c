#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
 
const int LARGURA_TELA = 900;
const int ALTURA_TELA = 600;

sem_t homem, mulher, banheiro;
int conta_homem, conta_mulher, conta_vetM, conta_vetH, ultimosair;
bool pmulher, phomem;
int conta_pessoas, conta_pessoae;
int vet_mulher_entrou[50];
void mulher_quer_entrar();
void mulher_sai();
void mulher_usa_banheiro();
void adiciona_mulher();
void homem_quer_entrar();
void homem_sai();
void homem_usa_banheiro();
void adiciona_homem();
int vet_mulher_saiu[50];


 
ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
 
bool inicializar();
void entrandoMulher();
void saindoMulher();
void entrandoHomem();
void saindoHomem();
void estadoVazio();

void mulher_quer_entrar() {
    sem_wait(&mulher);
    conta_mulher += 1;
	
    if (conta_mulher == 1) {
        sem_wait(&banheiro);
		if(phomem == false && pmulher == false){
		pmulher = true;
		conta_vetM = 0;
		vet_mulher_entrou[conta_vetM] = 0;
		ultimosair = conta_mulher;
	}else{
		conta_vetM += 1;
		vet_mulher_entrou[conta_vetM] = 0;
		conta_vetM += 1;
		vet_mulher_entrou[conta_vetM] = 0;
	}
    }
	if(conta_mulher > vet_mulher_entrou[conta_vetM] ){
	vet_mulher_entrou[conta_vetM] = conta_mulher;
	}else if(vet_mulher_entrou[conta_vetM] == conta_mulher){
		conta_vetM += 1;
		vet_mulher_entrou[conta_vetM] = conta_mulher - 1;
		}
    printf("Entrou mulher, total: %d\n", conta_mulher);
    sem_post(&mulher);
}
 
void mulher_sai() {
    sem_wait(&mulher);
    conta_mulher -= 1; 
    printf("Saiu mulher, total: %d\n", conta_mulher);

	if(ultimosair > conta_mulher){
			vet_mulher_saiu[conta_vetH] = 1 + vet_mulher_saiu[conta_vetH];
	}else if(ultimosair == 0){
		conta_vetH += 1;
		vet_mulher_saiu[conta_vetH] = 1;
	}else{
		conta_vetH += 1;
		vet_mulher_saiu[conta_vetH] = 1;
		}
	ultimosair = conta_mulher;
    if (conta_mulher == 0) {
	conta_vetH += 1;
	vet_mulher_saiu[conta_vetH] = 0;
	ultimosair = 0;
        sem_post(&banheiro);
    }
	
    sem_post(&mulher);
//saindoMulher();	
}
 
void mulher_usa_banheiro() {
    usleep(rand() % 900000);
}
 
void adiciona_mulher() {
    usleep(rand() % 400000);
    mulher_quer_entrar();
    mulher_usa_banheiro();
    mulher_sai();
    pthread_exit();
}
 
void homem_quer_entrar() {
    sem_wait(&homem);
    conta_homem += 1;
    if (conta_homem == 1) {
        sem_wait(&banheiro);
	if(pmulher == false && phomem == false){
		phomem = true;
		conta_vetM = 0;
		vet_mulher_entrou[conta_vetM] = 0;
		ultimosair = conta_homem;
	}else{
		conta_vetM += 1;
		vet_mulher_entrou[conta_vetM] = 0;
		conta_vetM += 1;
		vet_mulher_entrou[conta_vetM] = 0;
	}
     }
    
	if(conta_homem > vet_mulher_entrou[conta_vetM]){
		vet_mulher_entrou[conta_vetM] = conta_homem;
	}else if(vet_mulher_entrou[conta_vetM] == conta_homem){
			conta_vetM += 1;
			vet_mulher_entrou[conta_vetM] = 1;
		}
  
    printf("Entrou homem, total: %d\n", conta_homem);
    sem_post(&homem);
}
 
void homem_sai() {
    sem_wait(&homem);
    conta_homem -= 1;
    printf("Saiu homem, total: %d\n", conta_homem);
	if(conta_homem < ultimosair){
			vet_mulher_saiu[conta_vetH] = 1 + vet_mulher_saiu[conta_vetH];
	}else if(ultimosair == 0){
		conta_vetH += 1;
		vet_mulher_saiu[conta_vetH] = 1;
	}else{
		conta_vetH += 1;
		vet_mulher_saiu[conta_vetH] = 1;	
		}
	ultimosair = conta_homem;

if (conta_homem == 0) {
        sem_post(&banheiro);
	conta_vetH += 1;
	vet_mulher_saiu[conta_vetH] = 0;
	ultimosair = 0;
    }
    sem_post(&homem);
}
 
void homem_usa_banheiro() {
    usleep(rand() % 300000);
}
 
void adiciona_homem() {
    usleep(rand() % 400000);
    homem_quer_entrar();
    homem_usa_banheiro();
    homem_sai();
    pthread_exit();
}


void estadoVazio(){
	// Carrega a imagem de fundo
	ALLEGRO_BITMAP *img = NULL;
	img = al_load_bitmap("banheiro_unissex.png");
	// Desenha a imagem na tela
	al_draw_bitmap(img, 0, 0, 0);
	al_rest(1.99);

}
void entrandoMulher(){
	bool sair = false;
	float parada = 50;
	int dir_x = 0, dir_y = 1;

	if(conta_pessoae == 1){
		// Variável representando a imagem
		ALLEGRO_BITMAP *imagem1 = NULL;
		float x1 = 550;
		float y1 = 650;
		while (!sair)
		{
			// Carrega a imagem
    			imagem1 = al_load_bitmap("boneca.png");
			al_set_target_bitmap (imagem1);
			al_set_target_bitmap(al_get_backbuffer(janela));

			// Desenha a imagem na tela
			al_draw_bitmap(imagem1, x1, y1, 0);
			al_flip_display();
      
			x1 += 1.0 * dir_x;
			y1 += 1.0 * dir_y;
			
			if (x1 >= LARGURA_TELA)
			{
			    dir_x = -1;
			    x1 = LARGURA_TELA ;
			} else if (x1 <= parada) {
			    dir_x = -1;
			    x1 = parada;
			}
		 
			if (y1 >= ALTURA_TELA )
			{
			    dir_y = -1;
			    y1 = ALTURA_TELA;
			} else if (y1 <= parada) {
			    dir_y = -1;
			    y1 = parada;
				sair=true;

			}
		}
		al_destroy_bitmap(imagem1);
			
	}else if(conta_pessoae == 2){
		ALLEGRO_BITMAP *imagem2 = NULL;
		float x2 = 750;
		float y2 = 650;
		while (!sair)
	    	{

			imagem2 = al_load_bitmap("boneca.png");
			al_set_target_bitmap (imagem2);

			al_set_target_bitmap(al_get_backbuffer(janela));

			// Desenha a imagem na tela
			al_draw_bitmap(imagem2, x2, y2, 0);

			
			al_flip_display();
			x2 += 1.0 * dir_x;
			y2 += 1.0 * dir_y;

			if (x2 >= LARGURA_TELA)
				{
				    dir_x = -1;
				    x2 = LARGURA_TELA ;
				} else if (x2 <= parada) {
				    dir_x = -1;
				    x2 = parada;
				}
			 
				if (y2 >= ALTURA_TELA )
				{
				    dir_y = -1;
				    y2 = ALTURA_TELA;
				} else if (y2 <= parada) {
				    dir_y = -1;
				    y2 = parada;
				    sair=true;

				}
			}
al_destroy_bitmap(imagem2);

	}else{
		// Variável representando a imagem    
		ALLEGRO_BITMAP *imagem3 = NULL;
		float x3 = 150;
	    	float y3 = 650;
		while (!sair)
    		{
			imagem3 = al_load_bitmap("boneca.png");
			al_set_target_bitmap (imagem3);
			al_set_target_bitmap(al_get_backbuffer(janela));

			// Desenha a imagem na tela
			al_draw_bitmap(imagem3, x3, y3, 0); 
			al_flip_display();
			x3 += 1.0 * dir_x;
			y3 += 1.0 * dir_y;        
			 
			if (x3 >= LARGURA_TELA)
				{
				    dir_x = -1;
				    x3 = LARGURA_TELA ;
				} else if (x3 <= parada) {
				    dir_x = -1;
				    x3 = parada;
				}
			 
				if (y3 >= ALTURA_TELA )
				{
				    dir_y = -1;
				    y3 = ALTURA_TELA;
				} else if (y3 <= parada) {
				    dir_y = -1;
				    y3 = parada;
				sair=true;

				}
		}
al_destroy_bitmap(imagem3);
			}
	al_set_target_bitmap (NULL);
        al_rest(0.005);
}

void saindoMulher(){
al_flip_display();
	bool sair = false;
	float parada = 50;
	int dir_x = 0, dir_y = 1;

	if(conta_pessoas == 1){
		// Variável representando a imagem
		ALLEGRO_BITMAP *imagem1 = NULL;
		float x1 = 550;
		float y1 = 50;
	while (!sair)
	{
		// Carrega a imagem
		imagem1 = al_load_bitmap("boneca.png");
		al_set_target_bitmap (imagem1);
		al_set_target_bitmap(al_get_backbuffer(janela));

		// Desenha a imagem na tela
		al_draw_bitmap(imagem1, x1, y1, 0);
		al_flip_display();       
		x1 += 1.0 * dir_x;
		y1 += 1.0 * dir_y;

		if (x1 >= LARGURA_TELA)
		{
		    dir_x = -1;
		    x1 = LARGURA_TELA ;
		} else if (x1 <= parada) {
		    dir_x = -1;
		    x1 = parada;
		}

		if (y1 >= ALTURA_TELA )
		{
		    dir_y = 0;
		    y1 = ALTURA_TELA;
	            sair = true;

		} else if (y1 <= parada) {
		    dir_y = -1;
		    y1 = parada;
		}
	}
al_destroy_bitmap(imagem1);

	}else if(conta_pessoas == 2){
		ALLEGRO_BITMAP *imagem2 = NULL;
		float x2 = 750;
		float y2 = 50;
		while (!sair)
		{
		// Carrega a imagem
		imagem2 = al_load_bitmap("boneca.png");
		al_set_target_bitmap (imagem2);
		al_set_target_bitmap(al_get_backbuffer(janela));

		al_draw_bitmap(imagem2, x2, y2, 0);
		al_flip_display();
		x2 += 1.0 * dir_x;
		y2 += 1.0 * dir_y;

		if (x2 >= LARGURA_TELA)
			{
			    dir_x = -1;
			    x2 = LARGURA_TELA ;
			} else if (x2 <= parada) {
			    dir_x = -1;
			    x2 = parada;
			}
		 
			if (y2 >= ALTURA_TELA )
			{
			    dir_y = 0;
			    y2 = ALTURA_TELA;
			    sair = true;

			} else if (y2 <= parada) {
			    dir_y = -1;
			    y2 = parada;
			}
		}
al_destroy_bitmap(imagem2);
	}else{
		ALLEGRO_BITMAP *imagem3 = NULL;
		float x3 = 150;
		float y3 = 50;
		while (!sair)
		{
		// Carrega a imagem
		imagem3 = al_load_bitmap("boneca.png");
		al_set_target_bitmap (imagem3);
		al_set_target_bitmap(al_get_backbuffer(janela));

		al_draw_bitmap(imagem3, x3, y3, 0);
		al_flip_display();
		x3 += 1.0 * dir_x;
		y3 += 1.0 * dir_y;  

		if (x3 >= LARGURA_TELA)
			{
			    dir_x = -1;
			    x3 = LARGURA_TELA ;
			} else if (x3 <= parada) {
			    dir_x = -1;
			    x3 = parada;
			}
		 
			if (y3 >= ALTURA_TELA )
			{
			    dir_y = 0;
			    y3 = ALTURA_TELA;
			    sair = true;

			} else if (y3 <= parada) {
			    dir_y = -1;
			    y3 = parada;
			}
		}
al_destroy_bitmap(imagem3);
	}
al_set_target_bitmap (NULL);
	al_rest(0.005);

}

void entrandoHomem(){
al_set_target_bitmap(al_get_backbuffer(janela));
	bool sair = false;
	float parada = 50;
	int dir_x = 0, dir_y = 1;

	if(conta_pessoae ==1){
		// Variável representando a imagem
		ALLEGRO_BITMAP *imagem1 = NULL;
		float x1 = 550;
		float y1 = 650;
	

		while (!sair)
		{
			// Carrega a imagem
    			imagem1 = al_load_bitmap("boneco.jpg");
			al_set_target_bitmap (imagem1);
			// Desenha a imagem na tela
			al_set_target_bitmap(al_get_backbuffer(janela));
			al_draw_bitmap(imagem1, x1, y1, 0);
			al_flip_display();
      
			x1 += 1.0 * dir_x;
			y1 += 1.0 * dir_y;
			
			if (x1 >= LARGURA_TELA)
			{
			    dir_x = -1;
			    x1 = LARGURA_TELA ;
			} else if (x1 <= parada) {
			    dir_x = -1;
			    x1 = parada;
			}
		 
			if (y1 >= ALTURA_TELA )
			{
			    dir_y = -1;
			    y1 = ALTURA_TELA;
			} else if (y1 <= parada) {
			    dir_y = -1;
			    y1 = parada;
				sair=true;

			}
		}

			
	}else if(conta_pessoae == 2){
		ALLEGRO_BITMAP *imagem2 = NULL;
		float x2 = 750;
		float y2 = 650;
		while (!sair)
	    	{
			imagem2 = al_load_bitmap("boneco.jpg");
			al_set_target_bitmap (imagem2);
			al_set_target_bitmap(al_get_backbuffer(janela));

			// Desenha a imagem na tela
			al_draw_bitmap(imagem2, x2, y2, 0);
			
			al_flip_display();
			x2 += 1.0 * dir_x;
			y2 += 1.0 * dir_y;

			if (x2 >= LARGURA_TELA)
				{
				    dir_x = -1;
				    x2 = LARGURA_TELA ;
				} else if (x2 <= parada) {
				    dir_x = -1;
				    x2 = parada;
				}
			 
				if (y2 >= ALTURA_TELA )
				{
				    dir_y = -1;
				    y2 = ALTURA_TELA;
				} else if (y2 <= parada) {
				    dir_y = -1;
				    y2 = parada;
					sair=true;

				}
			}


	}else{
		// Variável representando a imagem    
		ALLEGRO_BITMAP *imagem3 = NULL;
		float x3 = 150;
    		float y3 = 650;
		while (!sair)
    		{
			imagem3 = al_load_bitmap("boneco.jpg");
			al_set_target_bitmap (imagem3);
			al_set_target_bitmap(al_get_backbuffer(janela));

			// Desenha a imagem na tela
			al_draw_bitmap(imagem3, x3, y3, 0); 
			al_flip_display();
			x3 += 1.0 * dir_x;
			y3 += 1.0 * dir_y;        
			 
			if (x3 >= LARGURA_TELA)
				{
				    dir_x = -1;
				    x3 = LARGURA_TELA ;
				} else if (x3 <= parada) {
				    dir_x = -1;
				    x3 = parada;
				}
			 
				if (y3 >= ALTURA_TELA )
				{
				    dir_y = -1;
				    y3 = ALTURA_TELA;
				} else if (y3 <= parada) {
				    dir_y = -1;
				    y3 = parada;
					sair=true;
					
				}

		}
			}
al_set_target_bitmap (NULL);
        al_rest(0.005);
}

void saindoHomem(){
	al_set_target_bitmap(al_get_backbuffer(janela));
	bool sair = false;
	float parada = 50;
	int dir_x = 0, dir_y = 1;

	if(conta_pessoas == 1){
		// Variável representando a imagem
		ALLEGRO_BITMAP *imagem1 = NULL;
		float x1 = 550;
		float y1 = 50;

	while (!sair)
	{
		// Carrega a imagem
		imagem1 = al_load_bitmap("boneco.jpg");
		// Desenha a imagem na tela
		al_set_target_bitmap (imagem1);
		al_set_target_bitmap(al_get_backbuffer(janela));

		al_draw_bitmap(imagem1, x1, y1, 0);
		al_flip_display();       
		x1 += 1.0 * dir_x;
		y1 += 1.0 * dir_y;

		if (x1 >= LARGURA_TELA)
		{
		    dir_x = -1;
		    x1 = LARGURA_TELA ;
		} else if (x1 <= parada) {
		    dir_x = -1;
		    x1 = parada;
		}

		if (y1 >= ALTURA_TELA )
		{
		    dir_y = 0;
		    y1 = ALTURA_TELA;
	            sair = true;

		} else if (y1 <= parada) {
		    dir_y = -1;
		    y1 = parada;
		}
	}


	}else if(conta_pessoas == 2){
		ALLEGRO_BITMAP *imagem2 = NULL;
		float x2 = 750;
		float y2 = 50;

		while (!sair)
		{
		// Carrega a imagem
		imagem2 = al_load_bitmap("boneco.jpg");
		al_set_target_bitmap (imagem2);
		al_set_target_bitmap(al_get_backbuffer(janela));

		al_draw_bitmap(imagem2, x2, y2, 0);
		al_flip_display();
		x2 += 1.0 * dir_x;
		y2 += 1.0 * dir_y;

		if (x2 >= LARGURA_TELA)
			{
			    dir_x = -1;
			    x2 = LARGURA_TELA ;
			} else if (x2 <= parada) {
			    dir_x = -1;
			    x2 = parada;
			}
		 
			if (y2 >= ALTURA_TELA )
			{
			    dir_y = 0;
			    y2 = ALTURA_TELA;
			    sair = true;

			} else if (y2 <= parada) {
			    dir_y = -1;
			    y2 = parada;
			}
		}

	}else{
		ALLEGRO_BITMAP *imagem3 = NULL;
		float x3 = 150;
		float y3 = 50;
		while (!sair)
		{
		// Carrega a imagem
		imagem3 = al_load_bitmap("boneco.jpg");
		al_set_target_bitmap (imagem3);
		al_set_target_bitmap(al_get_backbuffer(janela));

		al_draw_bitmap(imagem3, x3, y3, 0);
		al_flip_display();
		x3 += 1.0 * dir_x;
		y3 += 1.0 * dir_y;  

		if (x3 >= LARGURA_TELA)
			{
			    dir_x = -1;
			    x3 = LARGURA_TELA ;
			} else if (x3 <= parada) {
			    dir_x = -1;
			    x3 = parada;
			}
		 
			if (y3 >= ALTURA_TELA )
			{
			    dir_y = 0;
			    y3 = ALTURA_TELA;
			    sair = true;

			} else if (y3 <= parada) {
			    dir_y = -1;
			    y3 = parada;
			}
		}
	}
al_set_target_bitmap (NULL);
al_rest(0.005);
}

 
int main(void)
{
	conta_mulher = 0;
	conta_homem = 0;
	conta_vetM = 0;
	pmulher = false;
	phomem = false;
	
	int quntidade_pessoas;
	printf("Digite a quantidade de pessoas:");
	scanf("%d", &quntidade_pessoas);
	vet_mulher_entrou[quntidade_pessoas];
	
    pthread_t thread[quntidade_pessoas];
 
    /* Inicializando os semaforos */
    int i, res_parc, res = 0;
    res_parc = sem_init(&homem, 0, 1);
    res += res_parc;
    res_parc = sem_init(&mulher, 0, 1);
    res += res_parc;
    res_parc = sem_init(&banheiro, 0, 1);
    res += res_parc;
    if (res != 0) {
        perror("Falha na inicializacao dos semaforos\n");
        exit(EXIT_FAILURE);
    }
 
    /* Inicializando threads */
    for (res = 0, i = 0; i < quntidade_pessoas; i++) {
        usleep(rand() % 300000);
        if (rand() % 2 != 0)
            res_parc = pthread_create(&thread[i], NULL,
                    (void*) adiciona_mulher, (int*) (i + 1));
        else
            res_parc = pthread_create(&thread[i], NULL, (void*) adiciona_homem,
                    (int*) (i + 1));
        res += res_parc;
    }
    if (res != 0) {
        perror("Erro em criacao de threads\n");
        exit(EXIT_FAILURE);
    }
    /* Juntando threads */
    for (i = 0; i < quntidade_pessoas; i++) {
        res_parc = pthread_join(thread[i], NULL);
        res += res_parc;
    }
    if (res != 0) {
        perror("Erro em join threads\n");
        exit(EXIT_FAILURE);
    }

	if (!inicializar())
	{
		printf("nao deu certo!");
		return -1;
	}
 	
	estadoVazio();
	
	int prox = 0;
	if(phomem == true){
		prox = 0;
	}else{
		prox = 1;
	}
	  
	//rodando a animação!!
	int m = 0, n = 1, l, j, k; 
	while (m <= conta_vetM && n < conta_vetH){
	l = vet_mulher_entrou[m];
	k = vet_mulher_saiu[n];

	if(l == 0 && k == 0){
		if(prox == 1){
			prox = 0;
		}else{
			prox = 1;
		}
		m++;
		n++;
	}else{
	 
	conta_pessoae = 0;
	conta_pessoas = 0;
	if(prox == 1){
			//Entrou na mulher
			if(l != 0){
				for(i = 0; i < l; i++){
				conta_pessoae =  i + 1;
				entrandoMulher();
				}
			m++;
			}
			if(k != 0){
				for(i = 0; i < k; i++){
				conta_pessoas = i + 1;
				saindoMulher();
				}
			n++;
			}
		}else{
			//Entrou no homem
			if(l != 0){
				for(i = 0; i < l; i++){
				conta_pessoae =  i + 1;
				entrandoHomem();
				}
			m++;
			}
			if(k != 0){
				for(i = 0; i < k; i++){
				conta_pessoas = i + 1;
				saindoHomem();
				}
			n++;
			}
		}
	}
	}


    al_rest(1.99);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);
    return 0;
}
 
bool inicializar()
{
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar Allegro.\n");
        return false;
    }
 
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return false;
    }

     // Inicializa o add-on para utilização de imagens
     if(!al_init_image_addon()){
        fprintf(stderr, "Falha ao criar imagens.\n");
        return false;
     }
 
    al_set_window_title(janela, "Problema do banheiro unissex!");
 
    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return false;
    }
	
 
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
 
    return true;
}
