
# Relatório do Projeto 3 - Multicore e Aceleração em Hardware

## Integrantes

**Pedro De Nigris Vasconcellos RA:147623**

**Victor Seixas Souza RA:118896**

**Felipe de Oliveira Emos RA:146009**

**Renan Gomes Pereira RA:103927**

**Mateus Bellomo RA:147338**

# Metodologia

Com o intuito de avaliar o ganho de desempenho providenciado pela aceleração em hardware e paralelização escolhemos uma aplicação que apresenta um conjunto bastante grande de operações que podem ser otimizadas e também uma aplicação que pode ser facilmente dividida. 

A aplicação escolhida foi o algoritmo de Mandelbrot, que consiste em gerar o conjunto de Mandelbrot com base em uma janela do plano complexo. Mais informações podem ser encontradas no [link][1].

A seguir segue o pseudo-código utilzado em nosso projeto.

	For each pixel (Px, Py) on the screen, do:
	{
  		x0 = scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale)
  		y0 = scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale)
  		x = 0.0
	  	y = 0.0
  		iteration = 0
  		max_iteration = 1000

	  	while ( x*x + y*y < (1 << 16)  AND  iteration < max_iteration ) {
   			xtemp = x*x - y*y + x0
    		y = 2*x*y + y0
    		x = xtemp
			iteration = iteration + 1
  		}
  		
 		// Used to avoid floating point issues with points inside the set.
  		if ( iteration < max_iteration ) {

    		log_zn = log( x * x + y * y ) / 2
    		nu = log( log_zn / log(2) ) / log(2)
    		iteration = iteration + 1 - nu
  		}
  		
	  	color1 = palette[floor(iteration)]
  		color2 = palette[floor(iteration) + 1]
  		
  		// iteration % 1 = fractional part of iteration.
  		
  		color = linear_interpolate(color1, color2, iteration % 1)
  		plot(Px, Py, color)
	}

Percebe-se que todas operações estão dentro de um laço, que coresponde à uma matriz, dessa forma, paralelizar o algoritmo significa escolher um intervalo para cada processador calcular os pontos. 

Para cada pixel, existe uma série de cálculos para definir a sua cor na figura final. Como em muitos casos o tamanho da janela é pequeno, estes número acabam sendo definidos como double. 

Nesse ponto que o periférico de ponto flutuante entra em ação, sendo responsável por otimizar todas as contas que envolvem ponto flutuante na nossa aplicação (soma, subtração, mod, logaritmo).

Dessa forma definimos o conjunto de experimento variando entre com ou sem aceleração em hardware e variando o número de processadores.


# Implementação

## Mandelbrot

## Periféricos

EXPLICAR COMO QUE FOI FEITO. 

## Instanciação de processadores e periféricos

EXPLICAR COMO QUE FOI FEITO

# Experimentos

Para obter um conjunto de dados significativos a respeito da paralelização e da acelerão em hardaware da aplicação definimos estes 6 experimentos:

|Experimento|Número de processadores|Aceleração em Hardware (S/N)|
|:--:|:--:|:-------:|
|0| 1 | N|
|1| 1 | S|
|2| 2 | N|
|3| 2 | S|
|4| 4 | N|
|5 | 4 | S|

# Resultados

FALAR DO GANHO OBTIDO em termos de processador (quão rápido fica considerando 1, 2 ou 4 processadores), e também  mostrando os resultados obtidos através da aceleração em hardware

## Experimento 0

## Experimento 1

## Experimento 2

## Experimento 3

## Experimento 4

## Experimento 5

# Conclusão

Falar do desempenho em geral e como os processadores e a aceleração influência.

[1]: https://pt.wikipedia.org/wiki/Conjunto_de_Mandelbrot
