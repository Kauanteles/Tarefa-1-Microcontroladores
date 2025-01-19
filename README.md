# Instruções de uso

Para uso do software, siga os seguintes passos:

- **1°:** clone o repositório para o seu computador.

    - Ao abrir o projeto com o **VSCode**, a extensão do **CMake** irá criar a pasta ``build`` para você com os arquivos de compilação.

    - Caso não seja gerada a pasta, crie uma pasta com nome `build` e execute o seguinte comando dentro da pasta criada:
        
        ``cmake ..``

        O comando acima irá criar os arquivos de compilação.

- **2°:** execute a compilação do firmware usando a extensão do ***Raspberry Pi Pico*** do ***VSCode***.

A partir daqui, seu firmware já está compilado e pronto para uso, a depende de onde será usado.

## Execução no ambiente de simulação Wokwi

Para utilizar o ***firmware*** no ambiente de simulação, basta ter a extensão do **Wokwi** instalada no seu ***VSCode***, além de ter configurado a sua licença.

Suprindo os requisitos citados acima, basta clicar no arquivo ``diagram.json``, e a simulação já abrirá com o esquemático pronto.

***Clique no botão de play, no canto superior esquerdo e simule!***

## Execução na *BitDogLab*

Para execução na placa de desenvolvimento ***BitDogLab***, é necessário possuir o teclado matricial mostrado abaixo.

![teclado matricial](/images/teclado.png)

Possuindo o teclado, conecte-o aos pinos de extensão da placa, de acordo com o diagrama do ***Wokwi*** presente no arquivo ``diagram.json`` e siga os passos a seguir:

- **1°:** coloque o seu ***Raspberry*** em modo de ***bootsel***, clicando no botão branco na placa e reiniciando a mesma.

- **2°:** copie o arquivo `.uf2` que foi gerado na pasta `build` para o seu ***Raspberry*** (ele aparecerá como um armazenamento externo, um Pen-Drive com nome de RPI-RP2).

    - Após isso, o seu código já vai está rodando na sua plaquinha ***BitDogLab***.

- **3°:** Está pronto, dê os comandos para executar as funcionalidades apertando nos botões do seu teclado matricial.


## Comandos disponívels:

  - `A`: liga LED vermelho por 1 segundo;
  - `B`: liga o LED verde por 1 segundo;
  - `D`: liga os três LEDs ao mesmo tempo por 1 segundo (cor branca);
  - `*`: ativa o buzzer, que toca as notas *dó, ré, mi, fá, sol, lá, si, DÓ*, alternando os LEDs junto com as notas;
  - `0`: toca o buzzer por 2 segundos;
  - `#`: acende os três LEDs alternadamente, um de cada vez.


## Vídeo Ensaio

Clique em ***[https://youtu.be/JWtNuQbO8Z0]()*** para visualizar o vídeo ensaio do projeto.
