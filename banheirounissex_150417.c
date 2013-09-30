#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
 
#include <stdio.h>
#include <stdbool.h>
 
const int LARGURA_TELA = 900;
const int ALTURA_TELA = 600;
 
ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

sem_t homem, mulher, banheiro;
int conta_homem, conta_mulher;
void mulher_quer_entrar();
void mulher_sai();
void mulher_usa_banheiro();
void adiciona_mulher();
void homem_quer_entrar();
void homem_sai();
void homem_usa_banheiro();
void adiciona_homem();
bool inicializar();
void estadoVazio();
void entrandoMulher(int n);
void saindoMulher(int n);
void entrandoHomem(int n);
void saindoHomem(int n);
 
int main() {
    conta_mulher = 0;
    conta_homem = 0;
   int quntidade_pessoas = 0;
	printf("Digite a quantidade de pessoas:");
	scanf("%d", &quntidade_pessoas);
	
	if (!inicializar())
		{
			return -1;
		}
	estadoVazio();
ALLEGRO_BITMAP *img = NULL;
	img = al_load_bitmap("banheiro_unissex.png");
	// Desenha a imagem na tela
	al_draw_bitmap(img, 0, 0, 0);
    /*pthread_t thread[quntidade_pessoas];
 
    /* Inicializando os semaforos */
    /*int i, res_parc, res = 0;
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
    /*for (res = 0, i = 0; i < quntidade_pessoas; i++) {
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
    /*for (i = 0; i < quntidade_pessoas; i++) {
        res_parc = pthread_join(thread[i], NULL);
        res += res_parc;
    }
    if (res != 0) {
        perror("Erro em join threads\n");
        exit(EXIT_FAILURE);
    }*/
	al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela); 
    exit(EXIT_SUCCESS);
}
 
void mulher_quer_entrar() {
    sem_wait(&mulher);
    conta_mulher += 1;
    if (conta_mulher == 1) {
        sem_wait(&banheiro);
	entrandoMulher((int*)conta_mulher);

    }else if(conta_mulher == 2){
	entrandoMulher((int*)conta_mulher);

}else if(conta_mulher == 3){
	entrandoMulher((int*)conta_mulher);
}else{
	mulher_sai();
	entrandoMulher((int*)conta_mulher);
}
    printf("Entrou mulher, total: %d\n", conta_mulher);
    sem_post(&mulher);
}
 
void mulher_sai() {
    sem_wait(&mulher);
    conta_mulher -= 1;
    printf("Saiu mulher, total: %d\n", conta_mulher);
    if (conta_mulher == 0) {
        sem_post(&banheiro);

        estadoVazio();

    }else if(conta_mulher == 1){
	saindoMulher(conta_mulher);
}else if(conta_mulher == 2){
saindoMulher(conta_mulher);
}else{
saindoMulher(conta_mulher);
}
    sem_post(&mulher);
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
        entrandoHomem(&conta_homem);
    }else if(conta_homem == 2){
	entrandoHomem(&conta_homem);
	
	}else if(conta_homem == 3){
		entrandoHomem(&conta_homem);
	}else {
		homem_sai();
		entrandoHomem(&conta_homem);
	}
    printf("Entrou homem, total: %d\n", conta_homem);
    sem_post(&homem);
}
 
void homem_sai() {
    sem_wait(&homem);
    conta_homem -= 1;
    printf("Saiu homem, total: %d\n", conta_homem);
if (conta_homem == 0) {
        sem_post(&banheiro);
        estadoVazio();
    }else if(conta_homem == 1){
	saindoHomem(&conta_homem);
}else if(conta_homem == 2){
	saindoHomem(&conta_homem);
}else{
	saindoHomem(&conta_homem);
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

void entrandoMulher(int n){
	bool sair = false;
	float parada = 50;
	int dir_x = 0, dir_y = 1;

	if(n ==1){
		// Variável representando a imagem
		ALLEGRO_BITMAP *imagem1 = NULL;
		float x1 = 550;
		float y1 = 650;
		while (!sair)
		{
			// Carrega a imagem
    			imagem1 = al_load_bitmap("boneca.png");
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

			
	}else if(n == 2){
		ALLEGRO_BITMAP *imagem2 = NULL;
		float x2 = 750;
		float y2 = 650;
		while (!sair)
	    	{
			imagem2 = al_load_bitmap("boneca.png");
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
			imagem3 = al_load_bitmap("boneca.png");
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
        al_rest(0.005);
}

void saindoMulher(int n){
	bool sair = false;
	float parada = 50;
	int dir_x = 0, dir_y = 1;

	if(n == 1){
		// Variável representando a imagem
		ALLEGRO_BITMAP *imagem1 = NULL;
		float x1 = 550;
		float y1 = 50;
	while (!sair)
	{
		// Carrega a imagem
		imagem1 = al_load_bitmap("boneca.png");
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


	}else if(n == 2){
		ALLEGRO_BITMAP *imagem2 = NULL;
		float x2 = 750;
		float y2 = 50;
		while (!sair)
		{
		// Carrega a imagem
		imagem2 = al_load_bitmap("boneca.png");
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
		imagem3 = al_load_bitmap("boneca.png");
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
	al_rest(0.005);

}

void entrandoHomem(int n){
	bool sair = false;
	float parada = 50;
	int dir_x = 0, dir_y = 1;

	if(n ==1){
		// Variável representando a imagem
		ALLEGRO_BITMAP *imagem1 = NULL;
		float x1 = 550;
		float y1 = 650;

		while (!sair)
		{
			// Carrega a imagem
    			imagem1 = al_load_bitmap("boneco.jpg");
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

			
	}else if(n == 2){
		ALLEGRO_BITMAP *imagem2 = NULL;
		float x2 = 750;
		float y2 = 650;
		while (!sair)
	    	{
			imagem2 = al_load_bitmap("boneco.jpg");
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
        al_rest(0.005);
}

void saindoHomem(int n){
	bool sair = false;
	float parada = 50;
	int dir_x = 0, dir_y = 1;

	if(n == 1){
		// Variável representando a imagem
		ALLEGRO_BITMAP *imagem1 = NULL;
		float x1 = 550;
		float y1 = 50;
	while (!sair)
	{
		// Carrega a imagem
		imagem1 = al_load_bitmap("boneco.jpg");
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


	}else if(n == 2){
		ALLEGRO_BITMAP *imagem2 = NULL;
		float x2 = 750;
		float y2 = 50;
		while (!sair)
		{
		// Carrega a imagem
		imagem2 = al_load_bitmap("boneco.jpg");
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
	al_rest(0.005);
}

void estadoVazio(){
	// Carrega a imagem de fundo
	ALLEGRO_BITMAP *img = NULL;
	img = al_load_bitmap("banheiro_unissex.png");
	// Desenha a imagem na tela
	al_draw_bitmap(img, 0, 0, 0);
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
