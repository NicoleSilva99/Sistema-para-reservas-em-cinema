// Nomes: Nicole da Silva, Juliano França e Jonas Schneider

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

// definindo o tipo AssentoIndividual para conseguir passar como parametro para funções mais adiante
typedef struct {
    char nome[100];
    int idade;
    char sexo;
} AssentoIndividual;

////////////////////////////////////////////// CRIANDO AS FUNÇÔES

// Criando função para case 1 - opção 1 - verificar disponibilidade de UM assento
void statusAssento (int linha, int coluna, int linhaPessoa, int colunaPessoa, AssentoIndividual pessoa[linha][coluna]) {

    // Diminui uma unidade de linhaPessoa e colunaPessoa porque o cinema está numerado de 1 até 10, enquanto a matriz
    // está numerada de 0 até 9
    linhaPessoa -= 1;
    colunaPessoa -= 1;
    // If e else if verificam se aquela posição está disponível (idade = -1) ou está ocupada (idade != -1)
    if (pessoa[linhaPessoa][colunaPessoa].idade == -1) {
        printf ("O assento esta disponivel!\n");
        // Aqui ele vai printar os dados da pessoa caso o assento esteja ocupado
    } else if (pessoa[linhaPessoa][colunaPessoa].idade != -1) {
        printf ("Nome: %s\n", pessoa[linhaPessoa][colunaPessoa].nome);
        printf ("Idade: %d\n", pessoa[linhaPessoa][colunaPessoa].idade);
        printf ("Sexo: %c\n\n", pessoa[linhaPessoa][colunaPessoa].sexo);
    }
}


// Criando função pra case 2  - Consultar disponibilidade de X assentos

void consultarDisponibilidade (int linha, int coluna, int linhaPessoa, int X, AssentoIndividual pessoa[linha][coluna]) {

    int quantidade = 0;
    int posicaoAssento = 0;
    // Diminui uma unidade de linhaPessoa porque o cinema está numerado de 1 até 10, enquanto a
    // matriz está numerada de 0 até 9
    linhaPessoa -= 1;
    // Percorre a matriz
    for (int j = 0; j < coluna; j++) {
        if (pessoa[linhaPessoa][j].idade == -1) {
            if (quantidade == 0) {
                posicaoAssento = j+1; // revela a posição do assento inicial
            }
            quantidade++; // Se o assento estiver disponível incrementa quantidade em 1;
            if (quantidade == X) { // Quando quantidade for igual ao valor digitado pelo usuário, faz um printf e encerra
                printf ("Hoje e seu dia de sorte! Existem %d assentos disponiveis a partir da cadeira %d!\n", X, posicaoAssento);
                break;
            }
        } else if (pessoa[linhaPessoa][j].idade != -1) { // Sempre que o assento não estiver disponível
            //ele zera a quantidade, para garantir a sequencia de assentos
            quantidade = 0;
        }
    }
    if (quantidade < X) { // Se percorrer toda a matriz e quantidade terminar menor do que X, significa que não existem X assentos disponíveis
        printf ("Infelizmente nao ha %d assentos disponiveis.\n", X);
    }
}

// Criando função pra case 3  - Reservar X assentos a partir de um assento inicial

void fazerReserva (int linha, int coluna, int linhaPessoa, int X, AssentoIndividual pessoa[linha][coluna], int assentoInicial) {

    // Diminui uma unidade de linhaPessoa e assentoInicial porque o cinema está numerado de 1 até 10, enquanto a
    // matriz está numerada de 0 até 9
    assentoInicial -= 1;
    linhaPessoa -= 1;
    int quantidade = 0;
    for (int j = assentoInicial; j < (assentoInicial + X); j++) { // Percorre toda a matriz e soma um em quantidade se o assento
        // estiver disponível
        if (pessoa[linhaPessoa][j].idade == -1) {
            quantidade++;
            if (quantidade == X) { // Quando quantidade for igual a X, pede para salvar os dados da pessoa dentro das posições da matriz
                for (int j = assentoInicial; j < (assentoInicial + X); j++) {
                    fflush(stdin);
                    printf ("Informe o nome completo do ocupante: ");
                    gets (pessoa[linhaPessoa][j].nome);
                    fflush (stdin);
                    printf ("Informe a idade do ocupante: ");
                    scanf ("%d", &pessoa[linhaPessoa][j].idade);
                    fflush (stdin);
                    printf ("Informe o sexo do ocupante: ");
                    scanf ("%c", &pessoa[linhaPessoa][j].sexo);
                    fflush(stdin);
                }
                break;
            }
        } else if (pessoa[linhaPessoa][j].idade != -1) {  // Se o assento seguinte não estiver disponível, zera a quantidade
            // para garantir sequencia de assentos
            quantidade = 0;
        }
    }
    if (quantidade < X) { // Se quantidade for menor do que X após percorrer toda matriz, significa que não há X assentos disponíveis
        printf ("Infelizmente nao ha %d assentos disponiveis nessa fileira.\n", X);
    }

}

// Criando função pra case 4 - cancelar a reserva

void cancelarReserva (int linha, int coluna, int linhaPessoa, int X, AssentoIndividual pessoa[linha][coluna], int assentoInicial) {

    // Diminui uma unidade de linhaPessoa e assentoInicial porque o cinema está numerado de 1 até 10, enquanto a
    // matriz está numerada de 0 até 9
    assentoInicial -= 1;
    linhaPessoa -= 1;
    for (int j = assentoInicial; j < (assentoInicial + X); j++) { // Substitui a idade armazenada dentro da matriz por -1,
        // indicando que o lugar está disponível para reserva novamente
        pessoa[linhaPessoa][j].idade = -1;
    }
}

// Criando função pra case 5 - Imprimir tabela

void imprimirTabela (int linha, int coluna, AssentoIndividual pessoa[linha][coluna]) {
    // Mostrando a numeração das colunas
    printf ("  "); // espaço para garantir alinhamento de coluna x linha
    for (int j = 0; j < coluna; j++) {
        printf ("%02d ", j+1);
    }
    printf ("\n"); // nova linha para garantir formatação

    // Mostrando a numeração das linhas
    for (int i = 0; i < linha; i++) {
        printf ("%02d", i+1);
        for (int j = 0; j < coluna; j++) { // Preenchendo a tabela
            if (pessoa[i][j].idade == -1) { // Se idade for igual a -1, preenche ponto pois está disponível
                printf (" . ");
            } else if (pessoa[i][j].idade != -1) { // Se idade for diferente de -1, preenche X pois o lugar está reservado
                printf (" X ");
            }
        }
        printf ("\n\n"); // nova linha 2x para garantir formatação
    }
}

// Criando função porcentagem
float porcentagem (int x, int total) {

    float resultado = ((x * 100)/(float)total);
    return resultado;
}

// Criando função gráfico

void grafico (int x, int total) {

    float percentual = 0, escala = 0, virgula = 0;
    int vetor[20]; // Cria vetor para fazer gráfico
    percentual = (x*100)/total; // Transforma em percentual
    escala = percentual*0.2; // Transforma o percentual (100) para a escala do gráfico (20)
    virgula = escala - (floor(escala)); // Cálculo que verifica se o valor é numero quebrado ou não

    for(int i = 0; i < escala; i++) {
        vetor[i] = 61; // Recebe o caractere =
    }
    if(virgula != 0) {
        for(int i= escala; i < escala + 1; i++) {
            vetor[i] = 45; // Recebe o caractere - quando há numero quebrado
        }
        for(int i = escala + 1; i < 20; i++) {
            vetor[i] = 250; // A próxima posição recebe o caractere . indicando a porcentagem que falta ser preenchida
        }
    } else {
        for(int i = escala; i < 20; i++) {
            vetor[i] = 250;  // As demais posições recebem o caractere . indicando a porcentagem que falta ser preenchida
        }
    }
    printf("|"); // lateral do gráfico
    for(int i = 0; i < 20; i++) {
        printf("%c", vetor[i]);
    } // printando o gráfico
    printf("|"); // lateral do gráfico
    printf("\n"); // nova linha para melhor organização e visualização
}


// Criando função de listagem

void listagem (int linha, int coluna, AssentoIndividual pessoa[linha][coluna]) {

    int quantidade = 0;
    printf ("Listagem com informacoes dos ingressos reservados:\n");
    for (int i = 0; i < linha; i++) { // Percorre a matriz
        for (int j = 0; j < coluna; j++) {
            if (pessoa[i][j].idade != -1) { // Se o assento estiver reservado, mostra os dados da pessoa
                printf ("Fileira %d, assento %d -> ", (i+1), (j+1));
                printf ("Nome: %s, ", pessoa[i][j].nome);
                printf ("idade: %d, ", pessoa[i][j].idade);
                printf ("sexo: %c\n\n", pessoa[i][j].sexo);
                quantidade++; // Incrementa quantidade
            }
        }
    }
    if (quantidade == 0) { // Se não tiver incrementado nenhuma vez quantidade (ou seja, quantidade = 0)
        printf ("Ainda nao foram feitas reservas!\n\n");
    }
    printf ("\n"); // Organização
    printf ("--------------------------------------------------------------------\n\n"); // Organização
}

// Criando função de quantidade total de assentos divididos entre ocupados e liberados

void assentosLiberadosOcupados (int linha, int coluna, AssentoIndividual pessoa[linha][coluna], int totalAssentos) {
    printf ("Quantidade de assentos do cinema:\n");
    int quantidadeReservados = 0, quantidadeLiberados = 0;
    for (int i = 0; i < linha; i++) { // Percorre a matriz
        for (int j = 0; j < coluna; j++) {
            if (pessoa[i][j].idade != -1) { // Se estiver reservado, incrementa variável
                quantidadeReservados++;
            } else if (pessoa[i][j].idade == -1) { // Se estiver liberado, incrementa variável
                quantidadeLiberados++;
            }
        }
    }
    printf ("A quantidade total de ingressos do cinema e %d - %.2f%%!\n", totalAssentos, porcentagem(totalAssentos, totalAssentos));
    grafico (totalAssentos, totalAssentos);
    printf ("A quantidade de ingressos reservados e %d - %.2f%%!\n", quantidadeReservados, porcentagem(quantidadeReservados,totalAssentos));
    grafico (quantidadeReservados, totalAssentos);
    printf ("A quantidade de ingressos liberados e %d - %.2f%%!\n",quantidadeLiberados, porcentagem(quantidadeLiberados, totalAssentos));
    grafico (quantidadeLiberados, totalAssentos);
    printf ("\n\n");
    printf ("--------------------------------------------------------------------\n\n");
}

// Criando função de quantidade de reservas, divididas por sexo

void reservasPorSexo (int linha, int coluna, AssentoIndividual pessoa [linha][coluna]) {
    printf ("Quantidade de reservas, dividas por sexo:\n");
    int quantidadeMulheres = 0, quantidadeHomens = 0, total = 0;
    for (int i = 0; i < linha; i++) { // Percorre a matriz
        for (int j = 0; j < coluna; j++) {
            if (pessoa[i][j].idade != -1 && pessoa[i][j].sexo == 'f') { // Se for mulher e estiver reservado, incrementa variável
                quantidadeMulheres++;
            } else if (pessoa[i][j].idade != -1 && pessoa[i][j].sexo == 'm') { // Se for homem e estiver reservado, incrementa variável
                quantidadeHomens++;
            }
        }
    }
    total = (quantidadeMulheres + quantidadeHomens); // Soma reserva de homens e de mulheres para ter o total
    printf ("A quantidade total de reservas do cinema e %d - %.2f%%!\n", total, porcentagem(total, total));
    grafico (total, total);
    printf ("A quantidade de ingressos reservados por mulheres e %d - %.2f%%!\n", quantidadeMulheres, porcentagem(quantidadeMulheres,total));
    grafico (quantidadeMulheres, total);
    printf ("A quantidade de ingressos reservados por homens e %d - %.2f%%!\n", quantidadeHomens, porcentagem(quantidadeHomens, total));
    grafico (quantidadeHomens, total);
    printf ("\n\n");
    printf ("--------------------------------------------------------------------\n\n");
}

// Criando função quantidade de reservas, dividido por idade e agrupados a cada faixa de 10 anos

void reservasPorIdade (int linha, int coluna, AssentoIndividual pessoa[linha][coluna]) {
    printf ("Quantidade de reservas, dividas por sexo:\n");
    int total = 0, quantidade10 =0, quantidade20 = 0, quantidade30 = 0, quantidade40 = 0, quantidade50 = 0, quantidade60 = 0, quantidade70 =0,quantidade80 = 0, quantidade90 = 0, quantidade100 = 0;
    for (int i = 0; i < linha; i++) { // Percorre a matriz
        for (int j = 0; j < coluna; j++) {
            if (pessoa[i][j].idade >= 0 && pessoa[i][j].idade <= 10) {
                quantidade10++; // Se estiver dentro da faixa de idade, incrementa a variável
            } else if (pessoa[i][j].idade > 10 && pessoa[i][j].idade <= 20) {
                quantidade20++;
            } else if (pessoa[i][j].idade > 20 && pessoa[i][j].idade <= 30) {
                quantidade30++;
            } else if (pessoa[i][j].idade > 30 && pessoa[i][j].idade <= 40) {
                quantidade40++;
            } else if (pessoa[i][j].idade > 40 && pessoa[i][j].idade <= 50) {
                quantidade50++;
            } else if (pessoa[i][j].idade > 50 && pessoa[i][j].idade <= 60) {
                quantidade60++;
            } else if (pessoa[i][j].idade > 60 && pessoa[i][j].idade <= 70) {
                quantidade70++;
            } else if (pessoa[i][j].idade > 70 && pessoa[i][j].idade <= 80) {
                quantidade80++;
            } else if (pessoa[i][j].idade > 80 && pessoa[i][j].idade <= 90) {
                quantidade90++;
            } else if (pessoa[i][j].idade > 90) {
                quantidade100++;
            }
        }
    }
    // Abaixo soma todas as variáveis para ter o total
    total = (quantidade10 + quantidade20 + quantidade30 + quantidade40 + quantidade50 + quantidade60 + quantidade70 + quantidade80 + quantidade90 +quantidade100);
    printf ("O numero de reservas por idade e:\nPessoas de 0 a 10 anos: %d - %.2f%%\n", quantidade10, porcentagem (quantidade10, total));
    grafico (quantidade10, total);
    printf ("Pessoas de 11 a 20 anos: %d - %.2f%%\n", quantidade20, porcentagem (quantidade20, total));
    grafico (quantidade20, total);
    printf ("Pessoas de 21 a 30 anos: %d - %.2f%%\n", quantidade30, porcentagem (quantidade30, total));
    grafico (quantidade30, total);
    printf ("Pessoas de 31 a 40 anos: %d - %.2f%%\n", quantidade40, porcentagem (quantidade40, total));
    grafico (quantidade40, total);
    printf ("Pessoas de 41 a 50 anos: %d - %.2f%%\n", quantidade50, porcentagem (quantidade50, total));
    grafico (quantidade50, total);
    printf ("Pessoas de 51 a 60 anos: %d - %.2f%%\n", quantidade60, porcentagem (quantidade60, total));
    grafico (quantidade60, total);
    printf ("Pessoas de 61 a 70 anos: %d - %.2f%%\n", quantidade70, porcentagem (quantidade70, total));
    grafico (quantidade70, total);
    printf ("Pessoas de 71 a 80 anos: %d - %.2f%%\n", quantidade80, porcentagem (quantidade80, total));
    grafico (quantidade80, total);
    printf ("Pessoas de 81 a 90 anos: %d - %.2f%%\n", quantidade90, porcentagem (quantidade90, total));
    grafico (quantidade90, total);
    printf ("Pessoas acima de 91 anos: %d - %.2f%%\n", quantidade100, porcentagem (quantidade100, total));
    grafico (quantidade100, total);
    printf ("\n\n");
    printf ("--------------------------------------------------------------------\n\n");
}

// Criando função quantidade de pagantes inteira, meia adolescente e meia idoso

void pagantesFaixa (int linha, int coluna, AssentoIndividual pessoa[linha][coluna]) {
    int quantidadeInteira = 0, quantidadeMeiaJovens = 0, quantidadeMeiaIdosos = 0, total = 0;
    for (int i = 0; i < linha; i++) { // Percorre toda a matriz
        for (int j = 0; j < coluna; j++) {
            if (pessoa[i][j].idade >= 18 && pessoa[i][j].idade <= 59) {
                quantidadeInteira++; // Se estiver dentro da faixa de idade, incrementa a variável
            } else if (pessoa[i][j].idade >= 0 && pessoa[i][j].idade <= 17) {
                quantidadeMeiaJovens++; // Se estiver dentro da faixa de idade, incrementa a variável
            } else if (pessoa[i][j].idade >= 60) {
                quantidadeMeiaIdosos++; // Se estiver dentro da faixa de idade, incrementa a variável
            }
        }
    }
    total = (quantidadeInteira + quantidadeMeiaJovens + quantidadeMeiaIdosos); // Soma para ter o total de pagantes
    printf ("Quantidade de pagantes meia entrada de 0 a 17 anos: %d - %.2f%%\n", quantidadeMeiaJovens, porcentagem (quantidadeMeiaJovens, total));
    grafico (quantidadeMeiaJovens, total);
    printf ("Quantidade de pagantes meia entrada acima de 60 anos: %d - %.2f%%\n", quantidadeMeiaIdosos, porcentagem (quantidadeMeiaIdosos, total));
    grafico (quantidadeMeiaIdosos, total);
    printf ("Quantidade de pagantes inteira: %d - %.2f%%\n", quantidadeInteira, porcentagem (quantidadeInteira, total));
    grafico (quantidadeInteira, total);
    printf ("\n\n");
    printf ("--------------------------------------------------------------------\n\n");

}

//////////////////////////////////////// FUNÇÃO MAIN

int main() {

// Declaração de variáveis!
    int assentoInicial = 0;
    float valorIngresso = 0;
    int linha = 0; // Dimensões da matriz
    int coluna = 0; // Dimensões da matriz
    int totalAssentos = 0; // Total de assentos do cinema
    int opcao = 0, opcao2; // menu e submenu
    int linhaPessoa = 0, colunaPessoa = 0; // Assento digitado pelo usuário para verificar disponibilidade
    int X = 0; // Numero X de assentos que o usuário deseja reservar ou cancelar reserva

// Informando os dados do valor do ingresso!
    printf("Seja bem-vindo(a)!\nPor favor informe o valor do ingresso: ");
    scanf ("%f", &valorIngresso);
    printf ("Por favor, informe o numero total de assentos do cinema: ");
    scanf ("%d", &totalAssentos);

// Informando os dados das linhas(fileiras) e colunas(numero de assentos) da matriz
    printf ("Muito bem! Agora por favor informe o numero de fileiras que o cinema possui: ");
    scanf ("%d", &linha);
    printf ("Por favor, informe o numero de assentos por fileira: ");
    scanf ("%d", &coluna);
    system("pause");
    system("cls");

// Quando não fechar a multiplicação de linhas e colunas com o numero total de assentos, entra num loop pra consertar o erro
    while (linha * coluna != totalAssentos) {
        printf ("Erro!!!!\n");
        printf ("Informe o numero total de assentos do cinema: ");
        scanf ("%d", &totalAssentos);
        printf ("Informe o numero correto de fileiras que o cinema possui: ");
        scanf ("%d", &linha);
        printf ("Informe o numero correto de assentos por fileira: ");
        scanf ("%d", &coluna);
        system("pause");
        system("cls");
    }

// Criando a matriz

    AssentoIndividual pessoa[linha][coluna];

// Inicializando a matriz com a variável idade em -1 para ter todos os assentos como disponíveis
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            pessoa[i][j].idade = -1;
        }
    }

// Criando o menu

    while(1) {
        printf("Menu:\n");
        printf("Opcao 1 - Consultar situacao do assento\n");
        printf("Opcao 2 - Consultar disponibilidade de numero X de assentos numa fileira\n");
        printf("Opcao 3 - Fazer reserva de X assentos\n");
        printf("Opcao 4 - Cancelar reserva de assentos\n");
        printf("Opcao 5 - Visualizar mapa do cinema\n");
        printf("Opcao 6 - Mostrar relatorio\n");
        printf("Opcao 7 - Encerrar o programa\n");
        printf("-----------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d",&opcao);
        system("cls");

        switch (opcao) {
        // Opção 1 - verificar disponibilidade de um ingresso
        case 1:
            printf("Voce escolheu opcao 1!\n");
            printf ("Digite a fileira e a coluna do seu assento: ");
            scanf ("%d%d", &linhaPessoa, &colunaPessoa);
            // Aqui ele testa para ver se a pessoa digitou um assento válido ou não
            while (linhaPessoa > linha || colunaPessoa > coluna || linhaPessoa == 0 || colunaPessoa == 0) {
                printf ("\nErro!!! O cinema possui apenas %d fileiras e %d assentos por fileira!!!\n", linha, coluna);
                printf ("Digite a fileira e a coluna do seu assento: ");
                scanf ("%d%d", &linhaPessoa, &colunaPessoa);
            }
            // Chamando a função statusAssento para verificar a disponibilidade de um assento
            statusAssento (linha, coluna, linhaPessoa, colunaPessoa, pessoa);
            break;
        // Opção 2 - Verificar disponibilidade de mais de um ingresso
        case 2:
            printf("Voce escolheu opcao 2!\n");
            // Interação com o usuário a respeito dos lugares que ele deseja verificar se estão disponíveis
            printf ("Informe a fileira e a quantidade de assentos que deseja verificar disponibilidade: ");
            scanf ("%d %d", &linhaPessoa, &X);
            // Aqui ele testa para ver se a pessoa digitou um assento válido ou não
            while (linhaPessoa > linha || X > coluna || linhaPessoa == 0) {
                printf ("\nErro!!! O cinema possui apenas %d fileiras e %d assentos por fileira!!!\n", linha, coluna);
                printf ("Informe a fileira e a quantidade de assentos que deseja verificar disponibilidade: ");
                scanf ("%d %d", &linhaPessoa, &X);
            }
            // Chamando a função consultarDisponibilidade
            consultarDisponibilidade (linha, coluna, linhaPessoa, X, pessoa);
            break;
        // Opção 3 - Fazer reserva
        case 3:
            // Interação com o usuário a respeito dos lugares que ele deseja reservar
            printf("Voce escolheu opcao 3!\n");
            printf ("Informe a fileira, o assento inicial e a quantidade de assentos que deseja reservar: ");
            scanf ("%d %d %d", &linhaPessoa, &assentoInicial, &X);
            // Aqui ele testa para ver se a pessoa digitou um assento válido ou não
            while (linhaPessoa > linha || X > coluna || linhaPessoa == 0 || assentoInicial > coluna || (assentoInicial + X) > (coluna+1)) {
                printf ("\nErro!!! O cinema possui apenas %d fileiras e %d assentos por fileira!!!\n", linha, coluna);
                printf ("Informe a fileira, o assento inicial e a quantidade de assentos que deseja reservar: ");
                scanf ("%d %d %d", &linhaPessoa, &assentoInicial, &X);
            }
            // Chamando a função fazerReserva
            fazerReserva (linha, coluna, linhaPessoa, X, pessoa, assentoInicial);
            break;
        // Opção 4 - Cancelar reserva
        case 4:
            printf("Voce escolheu opcao 4!\n");
            printf ("Informe a fileira, o assento inicial e a quantidade de assentos que deseja cancelar a reserva: ");
            scanf ("%d %d %d", &linhaPessoa, &assentoInicial, &X);
            // Aqui ele testa para ver se a pessoa digitou um assento válido ou não
            while (linhaPessoa > linha || X > coluna || linhaPessoa == 0 || assentoInicial > coluna || (assentoInicial + X)> (coluna+1)) {
                printf ("\nErro!!! O cinema possui apenas %d fileiras e %d assentos por fileira!!!\n", linha, coluna);
                printf ("Informe a fileira, o assento inicial e a quantidade de assentos que deseja reservar: ");
                scanf ("%d %d %d", &linhaPessoa, &assentoInicial, &X);
            }
            // Chamando função para cancelar a reserva
            cancelarReserva (linha, coluna, linhaPessoa, X, pessoa, assentoInicial);
            break;
        // Opção 5 - Mapa do cinema
        case 5:
            printf("Voce escolheu opcao 5!\n");
            // Criando o mapa do cinema
            imprimirTabela (linha, coluna, pessoa);
            break;
        // Opção 6 - Resultados
        case 6:
            do {
                printf("Menu:\n");
                printf("Opcao 1 - Listagem apresentando as informações das reservas do cinema (nome, sexo, idade e assento)\n");
                printf("Opcao 2 - Quantidade total de assentos do cinema, divididos entre liberados e reservados\n");
                printf("Opcao 3 - Quantidade de reservas, dividido por sexo\n");
                printf("Opcao 4 - Quantidade de reservas, dividido por idade e agrupados a cada faixa de 10 anos\n");
                printf("Opcao 5 - Quantidade de pagantes meia entrada e inteira\n");
                printf("Opcao 6 - Voltar\n");
                printf("-----------------------\n");
                printf("Escolha uma opcao: ");
                scanf("%d",&opcao2);
                system("cls");

                switch (opcao2) {

                case 1:
                    // Listagem apresentando as informações das reservas do cinema (nome, sexo, idade e assento)
                    listagem (linha, coluna, pessoa);
                    break;
                case 2:
                    // Quantidade total de assentos do cinema, divididos entre liberados e reservados
                    assentosLiberadosOcupados (linha, coluna, pessoa, totalAssentos);
                    break;
                case 3:
                    // Quantidade de reservas, dividido por sexo
                    reservasPorSexo (linha, coluna, pessoa);
                    break;
                case 4:
                    // Quantidade de reservas, dividido por idade e agrupados a cada faixa de 10 anos
                    reservasPorIdade (linha, coluna, pessoa);
                    break;
                case 5:
                    // Quantidade de pagamentes de entrada inteira, meia entrada adolescentes e meia entrada idosos
                    pagantesFaixa (linha, coluna, pessoa);
                    break;
                }
            } while (opcao2 != 6); // Sai do laço do while do submenu e volta ao menu principal
            break;
        // Opçcão 7 - Sair
        case 7:
            return 0; // Encerra o programa
        default:
            printf("Opcao invalida!");
        }

    }
    return 0;
}
