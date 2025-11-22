// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Mariana Victoria Santos da Cruz
//  email: amary2572@gmail.com 
//  Matrícula: 20242160016
//  Semestre: 2025.2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################
#include <stdio.h>
#include "MarianaCruz20242160016.h" 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

DataQuebrada quebraData(char data[]) 

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int validarFormatoEDigitos(const char *data) {
    int i = 0;
    int etapa = 0;
    int digitoDia = 0;
    int digitoMes = 0;
    int digitoAno = 0;

    while (data[i] != '\0' && data[i] != '\n') {
        if (etapa == 0) {
            if (data[i] >= '0' && data[i] <= '9') digitoDia++;
            else if (data[i] == '/') etapa++;
            else return 0;
        }
        else if (etapa == 1) {
            if (data[i] >= '0' && data[i] <= '9') digitoMes++;
            else if (data[i] == '/') etapa++;
            else return 0;
        }
        else if (etapa == 2) {
            if (data[i] >= '0' && data[i] <= '9') digitoAno++;
            else return 0;
        }
        i++;
    }

    return (digitoDia >= 1 && digitoDia <= 2) &&
           (digitoMes >= 1 && digitoMes <= 2) &&
           (digitoAno == 2 || digitoAno == 4);
}


int validarData(int dia, int mes, int ano) {
    if(dia < 1 || dia > 31 || mes < 1 || mes > 12){
        return 0;
    }
    if(mes == 2) {
       int bissexto = (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
        if (bissexto && dia <= 29) return 1;
        else if (!bissexto && dia <= 28) return 1;
        else return 0;
    }
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        return dia <= 30;
    }
    return dia <= 31;
}

int q1(char data[])
{
   int datavalida = 1;
    if(!validarFormatoEDigitos(data)) {
        return 0;
    }
    DataQuebrada dq = quebraData(data);
    if(!dq.valido) {
        return 0;
}

if(!validarData(dq.iDia, dq.iMes, dq.iAno)) {
return 0;
}

return 1;
  
}

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    DiasMesesAnos dma;
    
    if(q1(datainicial) == 0) {
        dma.retorno = 2;
        return dma;
    }
    if(q1(datafinal) == 0) {
        dma.retorno = 3;
        return dma;
    }
    
    DataQuebrada ini = quebraData(datainicial);
    DataQuebrada fim = quebraData(datafinal);
    
   
    if ((ini.iAno > fim.iAno) ||
    (ini.iAno == fim.iAno && ini.iMes > fim.iMes) ||
    (ini.iAno == fim.iAno && ini.iMes == fim.iMes && ini.iDia > fim.iDia)) {
    dma.retorno = 4;
    return dma;
}
    int diferencaDia = fim.iDia - ini.iDia;
    int diferencaMes = fim.iMes - ini.iMes;
    int diferencaAno = fim.iAno - ini.iAno;
    
    if(diferencaDia < 0) {
        diferencaDia += 30;
        diferencaMes--;
    }
    
    if(diferencaMes < 0) {
        diferencaMes += 12;
        diferencaAno--;
    }
    
    dma.qtdDias = diferencaDia;
    dma.qtdMeses = diferencaMes;
    dma.qtdAnos = diferencaAno;

    dma.retorno = 1;
    return dma;
    
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */

int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;
    int i;
    char caractereAtual;

    if (!isCaseSensitive && c >= 'A' && c <= 'Z') {
        c += 32;
    }

    for(i = 0; texto[i] != '\0'; i++){
        caractereAtual = texto[i];

        if(!isCaseSensitive && caractereAtual >= 'A' && caractereAtual <= 'Z') {
            caractereAtual += 32;
        }

        if(caractereAtual == c) {
            qtdOcorrencias++;
        }
    }

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */

 void removerAcentos(char *texto) {
    const char *comAcentos[] = {
        "Ä", "Å", "Á", "Â", "À", "Ã", "ä", "á", "â", "à", "ã",
        "É", "Ê", "Ë", "È", "é", "ê", "ë", "è",
        "Í", "Î", "Ï", "Ì", "í", "î", "ï", "ì",
        "Ö", "Ó", "Ô", "Ò", "Õ", "ö", "ó", "ô", "ò", "õ",
        "Ü", "Ú", "Û", "ü", "ú", "û", "ù",
        "Ç", "ç"
    };
    
    const char *semAcentos[] = {
        "A", "A", "A", "A", "A", "A", "a", "a", "a", "a", "a",
        "E", "E", "E", "E", "e", "e", "e", "e",
        "I", "I", "I", "I", "i", "i", "i", "i",
        "O", "O", "O", "O", "O", "o", "o", "o", "o", "o",
        "U", "U", "U", "u", "u", "u", "u",
        "C", "c"
    };
    
    
    char temp[256];
    int index = 0;
    int i, j, c;
    
    for (i = 0; texto[i] != '\0'; ) {
        int substituido = 0;
        
        for (j = 0; j < (int)(sizeof(comAcentos) / sizeof(comAcentos[0])); j++) {
            int tamanho = strlen(comAcentos[j]);
            
            if (strncmp(&texto[i], comAcentos[j], tamanho) == 0) {
                int len = strlen(semAcentos[j]);
                for (c = 0; c < len; c++) {
                    temp[index++] = semAcentos[j][c];
                }
                i += tamanho;
                substituido = 1;
                break;
            }
        }
        
        if (!substituido) {
            temp[index++] = texto[i++];
        }
    }
    temp[index] = '\0';
    strcpy(texto, temp);
}

int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int indicePosicao = 0;
    int tamBusca = strlen(strBusca);
    int i, j;

    removerAcentos(strTexto);
    removerAcentos(strBusca);

    for (i = 0; i < (int)strlen(strTexto); ) {
        int encontrou = 1;

        if (strTexto[i] == strBusca[0]) {
            for (j = 0; j < tamBusca; j++) {
                if (strTexto[i + j] != strBusca[j]) {
                    encontrou = 0;
                    break;
                }
            }

            if (encontrou) {
                qtdOcorrencias++;
                posicoes[indicePosicao++] = i + 1;             
                posicoes[indicePosicao++] = i + tamBusca; 
                i += tamBusca;
               
            }
        }

        i++;
    }

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num) {
    int inv = 0;
    while (num > 0) { inv = inv*10 + num%10; num /= 10; }
    return inv;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca) {
    char base[20], busca[20];
    sprintf(base, "%d", numerobase);
    sprintf(busca, "%d", numerobusca);

    int tB = strlen(base), tP = strlen(busca), i, j, qtd = 0;

    for (i = 0; i <= tB - tP; i++) {
        int ok = 1;
        for (j = 0; j < tP; j++) {
            if (base[i+j] != busca[j]) { ok = 0; break; }
        }
        if (ok) qtd++;
    }

    return qtd;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

int q7(char matriz[8][10], char palavra[5]) {
    int i,j,dir,k,tam = strlen(palavra);
    int dLinha[8]={-1,-1,-1,0,0,1,1,1};
    int dCol[8]={-1,0,1,-1,1,-1,0,1};

    for (i=0;i<8;i++){
        for (j=0;j<10;j++){
            if (matriz[i][j] == palavra[0]) {
                for (dir=0;dir<8;dir++){
                    int ok=1;
                    for (k=1;k<tam;k++){
                        int nl=i+dLinha[dir]*k;
                        int nc=j+dCol[dir]*k;
                        if(nl<0||nl>=8||nc<0||nc>=10){ ok=0; break; }
                        if(matriz[nl][nc]!=palavra[k]){ ok=0; break; }
                    }
                    if (ok) return 1;
                }
            }
        }
    }
    return 0;
}
 
