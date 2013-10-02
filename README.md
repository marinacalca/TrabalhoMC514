Projeto 01 - Sistemas operacionais, professora: Islene C. Garcia.
Marina Calça, 150417

Problema do banheiro unissex
A história do banheiro unissex, é de uma funcionária que precisava subir dois andares para usar o banheiro feminino, então ela sugeriu utilizar o banheiro masculino que ficava em seu andar, como banheiro unissex. Foi concordado com algumas restrições:
- Não pode ter mais de três funcionários no banheiro disperdiçando tempo
- Não pode ter homem e mulheres juntos no banheiro

Para solucionar o problema, foi implementado utilizando semaforo e allegro em C.
Primeiro precisa digitar o número de pessoas, onde é sorteada a quantidade de mulheres e homens, através do rand()%2, onde se for igual a 0 é mulher, senão é homem.

As mulheres e homens são as threads, e existe três semaforos, mulher, homem e banheiro.
Quando o banheiro está vazio e um dos dois entram, o semaforo do banheiro é marcado que está sendo usado, nisso, todas as mulheres podem utilizar, até o próximo homem querer entrar no banheiro, então as mulheres saem e entra os homens. Também funciona se o homem for o primeiro. Quando um dos dois saem, o banheiro fica vazio para o proximo sexo entrar.

A primeira implementação, foi feita com a animação junto com os métodos do semaforo, porém deu esse problema "radeon: The kernel rejected CS, see dmesg for more information.", então  a minha segunda solução, foi fazer todo o processamento das threads, a adicionando nos vetores entrando e saindo, quantas pessoas estão entrando e quantas estão saindo para cada passo da execução.
Assim que terminar de processar as threads, então a animação é executada.

A animação funciona da seguinte maneira, o primeiro a pegar a ficha do banheiro, começa a entrar no banheiro, após ele começa a entrar e sair outras pessoas do mesmo sexo, até que a outra pessoa do sexo também precisa entrar no banheiro, quando o ultimo sair, a ficha do banheiro é liberada para o outro sexo. Quando alguém está entrando, a tela é atualizada sempre, pois conforme o personagem vai entrando na tela, precisa ir apagando a posição anterior e mostrar a nova.

Para rodar o código precisa ter a biblioteca allegro5 instalada, não pode ser anteriores, pois muda um pouco o código. E o comando para compilar no linux é "gcc -pthread banheirounissex_2_150417.c -o banheiro -lallegro_image -lallegro" e para executar a animação é "./banheiro".

