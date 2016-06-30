
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

```c
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
```
Percebe-se que todas operações estão dentro de um laço, que coresponde à uma matriz, dessa forma, paralelizar o algoritmo significa escolher um intervalo para cada processador calcular os pontos. 

Para cada pixel, existe uma série de cálculos para definir a sua cor na figura final. Como em muitos casos o tamanho da janela é pequeno, estes número acabam sendo definidos como double. 

Nesse ponto que o periférico de ponto flutuante entra em ação, sendo responsável por otimizar todas as contas que envolvem ponto flutuante na nossa aplicação (soma, subtração, mod, logaritmo).

Dessa forma definimos o conjunto de experimento variando entre com ou sem aceleração em hardware e variando o número de processadores.


# Implementação

## Mandelbrot

## Periféricos (FPU)

O periférico implementado é um periférico acelerador de contas com números complexos. O periférico aceita por vez dois números complexos, cada um com um double para a parte real e um double para a parte imaginária. Uma vez escritos os valores dos dois números, basta ler certos endereços específicos para recuperar os valores de contas feitas com esses números: soma, subtração, módulo, dentre outras operações indicadas na tabela de datasheet do periférico (neste mesmo relatório). A seguir, uma figura explicativa de uma operação feita usando o periférico:

![Image of FPU Functioning](contents/Function%20FPU.png)

Note que o archc por padrão tem arquitetura 32 bits, portanto as instruções de leitura e escrita de palavras conseguem manipular apenas 32 bits de cada vez. Como as operações do periférico são de variáveis *double* (que tem 64 bits), é necessário que toda variável de leitura e de escrita seja quebrada em duas partes de 32 bits e, somente assim, seja lida ou escrita com duas instruções (uma para cada parte de 32 bits). 

Se o código com a variável *double* que se deseja passar ou receber do periférico roda em um processador *big endian*, você pode obter o endereço da primeira e segunda parte do double com os seguintes macros:

``` c
// 64bit breaking into 32bit
// x -> double value to be broken
#define DOUBLE_PART1(addr_double) \
	((uint32_t*)(addr_double))

// x -> double value to be broken
#define DOUBLE_PART2(addr_double) \
	(((uint32_t*)(addr_double))+1)
```

#### Datasheet
##### Endereços de escrita

<center>

|Addresses|Value|
|:--:|:--:|
|0x04</br>0x08|Re(Z1) part 1</br>Re(Z1) part 2|
|0x0C</br>0x10|Im(Z1) part 1</br>Im(Z1) part 2|
|0x14</br>0x18|Re(Z2) part 1</br>Re(Z2) part 2|
|0x1C</br>0x20|Im(Z2) part 1</br>Im(Z2) part 2|

</center>


##### Endereços de leitura
|Addresses|Value|Op|Uses Re(Z1)|Uses Im(Z1)|Uses Re(Z2)|Uses Im(Z2)
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|0x24</br>0x28</br>0x2C</br>0x30| Re(Zr)</br>Re(Zr)</br>Im(Zr)</br>Im(Zr) | Zr = Z1 + Z2 | YES | YES | YES | YES |
|0x34</br>0x38</br>0x3C</br>0x40| Re(Zr)</br>Re(Zr)</br>Im(Zr)</br>Im(Zr) | Zr = Z1 - Z2 | YES | YES | YES | YES |
|0x44</br>0x48| R</br>R | R = \|Z1\| | YES | YES | NO | NO |
|0x4C</br>0x50</br>0x54</br>0x58| Re(Zr)</br>Re(Zr)</br>Im(Zr)</br>Im(Zr) | Zr = dot( Z1, Z2 )</br>or</br> Zr = Re(Z1)\*Re(Z2) + j\*Im(Z1)\*Im(Z2) | YES | YES | YES | YES |
|0x5C</br>0x60| R</br>R | R = ln( Re(Z1) ) | YES | NO | NO | NO |
|0x64</br>0x68| R</br>R | R= frac( Re(Z1) ) | YES | NO | NO | NO |
|0x6C</br>0x70| R</br>R | R= floor( Re(Z1) ) | YES | NO | NO | NO |
|0x74</br>0x78| R</br>R | R= random[0,1] | NO | NO | NO | NO |
|0x7C</br>0x80</br>0x84</br>0x88| Re(Zr)</br>Re(Zr)</br>Im(Zr)</br>Im(Zr) | Zr = Z1 * Z2 | YES | YES | YES | YES |

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
