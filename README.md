# Projeto 3 - Multicore e Aceleração em Hardware

## Grupo

**Pedro De Nigris Vasconcellos RA:147623**

**Victor Seixas Souza RA:118896**

**Felipe de Oliveira Emos RA:146009**

**Renan Gomes Pereira RA:103927**

**Mateus Bellomo RA:147338**

## Software 

Utilizaremos para esse projeto o algoritmo de Mandelbrot, no qual consiste em gerar imagens no plano complexo que representam o conjunto de Mandelbrot. A especificação completa é encontrada neste [link][1].

## Funções / Blocos para otimizar

Pretendemos acelerar, através do uso de periféricos, as operações de ponto flutuante (soma, multiplicação, logaritmo, divisão, subtração) e de cálculo dos números complexos.

Como a aplicação gera uma imagem, o paralelismo provém em dividir a tela de acordo com o número de cores, assim, cada um é responsável por calcular os seus próprios pontos.

## Estimativa do ganho de desempenho

A estimativa inicial do ganho de desempenho é linear no número de cores. Também esperamos obter um desempenho bastante considerável nas operações de ponto flutuante e de números complexos, visto que essas operações são as mais utilizadas pelo algoritmo.

## Experimentos

A fim de testar os ganhos de desempenho propostos, temos um conjunto de 3 experimentos. 

O primeiro, no qual a aplicação será executada de forma serial.

O segundo, no qual consiste em utilizar mais *cores* na execução (por exemplo, com 2, 4 e 8 cores).

O terceiro, consiste em utilizar a aceleração de hardware no conjunto de cores que apresentou melhor desempenho.

[1]: https://pt.wikipedia.org/wiki/Conjunto_de_Mandelbrot