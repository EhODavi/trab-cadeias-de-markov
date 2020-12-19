#include <iostream>
#include <fstream>
#include "MyMap.h"

// Função que lê os dados do arquivo ou do teclado ✓
void ler(istream &is, MyMap<string,int> &map1, MyMap<string,MyMap<string,int>> &map2, MyMap<string,MyMap<string,MyMap<string,int>>> &map3) {
    string linha; // Representa a linha lida
    string palavra1; // Representa a antepenúltima palavra lida
    string palavra2; // Representa a penúltima palavra lida
    string palavra3; // Representa a última palavra lida
    char letra; // Representa uma letra da linha

    // Lendo todas as linhas do texto de treino
    while(!is.eof()) {
        // Lendo a próxima linha do texto de treino
        getline(is,linha);

        // Se estivermos lendo do teclado, ignoramos a primeira linha
        if(linha == "COMECO_TREINO") continue;
        
        // Se estivermos lendo do teclado, ignoramos a última linha
        if(linha == "FINAL_TREINO") break;

        // Colocando o \n no final da linha pois o getline descarta o \n
        linha = linha + "\n";

        // Percorrendo todas as letras da linha
        for(int i = 0; i < linha.size(); i++) {
            // Pegando a letra atual e convertendo-a para minúscula
            letra = tolower(linha[i]);
            
            // Verificando se é uma letra do alfabeto ou se é um hífen
            if(isalpha(letra) || letra == '-') palavra3 = palavra3 + letra; // Concatenando a letra na palavra3
            else {
                if(!palavra3.empty()) map1[palavra3]++; // Se a palavra3 não for vazia, inserimos ela no map1
                if(!palavra2.empty() && !palavra3.empty()) map2[palavra2][palavra3]++; // Se a palavra2 e palavra3 não forem vazias, inserimos elas no map2
                if(!palavra1.empty() && !palavra2.empty() && !palavra3.empty()) map3[palavra1][palavra2][palavra3]++; // Se a palavra1, palavra2 e palavra3 não forem vazias, inserimos elas no map3

                // Verificando se a letra é um separador de palavras
                if(letra == ' ' || letra == '\t' || letra == '\n' || letra == '\'' || letra == '\"') {
                    if(!palavra3.empty()) { // Se a palavra3 não for vazia, deslocamos as palavras
                        palavra1 = palavra2;
                        palavra2 = palavra3;
                        palavra3 = "";
                    }
                } else palavra1 = palavra2 = palavra3 = ""; // Como a letra é um separador de sentenças, vamos atribuir vazio para palavra1, palavra2, palavra3
            }
        }
    }
}

// Função que realiza a consulta das palavras usando o map3 (FUNÇÃO SECUNDÁRIA) ✓
void consultar(const string &palavra1, const string &palavra2, const string &palavra3, MyMap<string,MyMap<string,MyMap<string,int>>> &map3) {
    // Verificando se a primeira palavra informada pelo usuário existe no map3
    MyMap<string,MyMap<string,MyMap<string,int>>>::iterator it1 = map3.find(palavra1);
        
    // Se o iterador não for NULO, quer dizer que a primeira palavra se encontra no map3
    if(it1 != map3.end()) {
        // Verificando se a segunda palavra informada pelo usuário existe no map3
        MyMap<string,MyMap<string,int>>::iterator it2 = (*it1).second.find(palavra2);

        // Se o iterador não for NULO, quer dizer que a segunda palavra se encontra no map3
        if(it2 != (*it1).second.end()) {
            // Verificando se a terceira palavra informada pelo usuário existe no map3
            MyMap<string,int>::iterator it3 = (*it2).second.find(palavra3);

            // Se o iterador não for NULO, quer dizer que a terceira palavra se encontra no map3. Com isso, basta informar o número de ocorrências
            if(it3 != (*it2).second.end()) cout << palavra1 << " " << palavra2 << " " << palavra3 << " (" << (*it3).second << ")" << endl;
            else cout << palavra1 << " " << palavra2 << " " << palavra3 << " (0)" << endl; // Como a terceira palavra não se encontra no map3, basta informar que há zero ocorrências      
        } else cout << palavra1 << " " << palavra2 << " " << palavra3 << " (0)" << endl; // Como a segunda palavra não se encontra no map3, basta informar que há zero ocorrências
    } else cout << palavra1 << " " << palavra2 << " " << palavra3 << " (0)" << endl; // Como a primeira palavra não se encontra no map3, basta informar que há zero ocorrências
}

// Função que realiza a consulta das palavras usando o map2 e map3 (FUNÇÃO SECUNDÁRIA) ✓
void consultar(const string &K, const string &palavra1, const string &palavra2, MyMap<string,MyMap<string,int>> &map2, MyMap<string,MyMap<string,MyMap<string,int>>> &map3) {
    // Verificando se a primeira palavra informada pelo usuário existe no map2
    MyMap<string,MyMap<string,int>>::iterator it1 = map2.find(palavra1);

    // Se o iterador não for NULO, quer dizer que a primeira palavra se encontra no map2
    if(it1 != map2.end()) {
        // Verificando se a segunda palavra informada pelo usuário existe no map2
        MyMap<string,int>::iterator it2 = (*it1).second.find(palavra2);

        // Se o iterador não for NULO, quer dizer que a segunda palavra se encontra no map2
        if(it2 != (*it1).second.end()) {
            // Imprimindo o número de ocorrências
            cout << palavra1 << " " << palavra2 << " (" << (*it2).second << ")" << endl;

            // Verificando se a primeira palavra informada pelo usuário existe no map3
            MyMap<string,MyMap<string,MyMap<string,int>>>::iterator it3 = map3.find(palavra1);
                
            // Se o iterador não for NULO, quer dizer que a primeira palavra se encontra no map3
            if(it3 != map3.end()) {
                // Verificando se a segunda palavra informada pelo usuário existe no map3
                MyMap<string,MyMap<string,int>>::iterator it4 = (*it3).second.find(palavra2);

                // Se o iterador não for NULO, quer dizer que a segunda palavra se encontra no map3
                if(it4 != (*it3).second.end()) {
                    // Criando um vetor que armazena todas as palavras que ocorrem após a palavra1 e a palavra2 e quantas vezes essas palavras ocorrem
                    pair<int,string> palavras[(*it4).second.size()];

                    // Copiando os valores da árvore para o vetor de palavras
                    int i = 0;
                    for(MyMap<string,int>::iterator it5 = (*it4).second.begin(); it5 != (*it4).second.end(); it5++) {
                        palavras[i].first = -(*it5).second;
                        palavras[i].second = (*it5).first;
                        i++;
                    }

                    // Ordenando o vetor de palavras
                    sort(palavras,palavras + (*it4).second.size());

                    // Imprimindo as ocorrências mais frequentes de palavras que aparecem após as palavras informadas pelo usuário
                    for(i = 0; i < min(stoi(K),(*it4).second.size()); i++) cout << palavra1 << " " << palavra2 << " " << palavras[i].second << " (" << -palavras[i].first << ")" << endl;
                }
            }
        } else cout << palavra1 << " " << palavra2 << " (0)" << endl; // Como a segunda palavra não se encontra no map2, basta informar que há zero ocorrências
    } else cout << palavra1 << " " << palavra2 << " (0)" << endl; // Como a primeira palavra não se encontra no map2, basta informar que há zero ocorrências
}

// Função que realiza a consulta das palavras o map1 e map2 (FUNÇÃO SECUNDÁRIA) ✓
void consultar(const string &K, const string &palavra1, MyMap<string,int> &map1, MyMap<string,MyMap<string,int>> &map2) {
    // Verificando se a primeira palavra informada pelo usuário existe no map1
    MyMap<string,int>::iterator it1 = map1.find(palavra1);

    // Se o iterador não for NULO, quer dizer que a primeira palavra se encontra no map1
    if(it1 != map1.end()) {
        // Imprimindo o número de ocorrências
        cout << palavra1 << " (" << (*it1).second << ")" << endl;
            
        // Verificando se a primeira palavra informada pelo usuário existe no map2
        MyMap<string,MyMap<string,int>>::iterator it2 = map2.find(palavra1);
            
        // Se o iterador não for NULO, quer dizer que a primeira palavra se encontra no map2
        if(it2 != map2.end()) {
            // Criando um vetor que armazena todas as palavras que ocorrem após a palavra1 e quantas vezes essas palavras ocorrem
            pair<int,string> palavras[(*it2).second.size()];

            // Copiando os valores da árvore para o vetor de palavras
            int i = 0;
            for(MyMap<string,int>::iterator it3 = (*it2).second.begin(); it3 != (*it2).second.end(); it3++) {
                palavras[i].first = -(*it3).second;
                palavras[i].second = (*it3).first;
                i++;
            }

            // Ordenando o vetor de palavras
            sort(palavras,palavras + (*it2).second.size());

            // Imprimindo as ocorrências mais frequentes de palavras que aparecem após as palavras informadas pelo usuário
            for(i = 0; i < min(stoi(K),(*it2).second.size()); i++) cout << palavra1 << " " << palavras[i].second << " (" << -palavras[i].first << ")" << endl;
        }
    } else cout << palavra1 << " (0)" << endl; // Como a primeira palavra não se encontra no map1, basta informar que há zero ocorrências
}

// Função que realiza a consulta das palavras (FUNÇÃO PRINCIPAL) ✓
void consultar(const string &linha, MyMap<string,int> &map1, MyMap<string,MyMap<string,int>> &map2, MyMap<string,MyMap<string,MyMap<string,int>>> &map3) {
    int qtdPalavras = 1; // Representa a quantidade de palavras do comando
    string K; // Representa as K palavras mais frequentes que aparecem após as palavras informadas pelo usuário
    string palavra1; // Representa a primeira palavra informada pelo usuário
    string palavra2; // Representa a segunda palavra informada pelo usuário
    string palavra3; // Representa a terceira palavra informada pelo usuário
    
    // Armazenando K e as palavras informadas pelo usuário nas variáveis acima
    for(int i = 10; i < linha.size(); i++) {
        if(linha[i] != ' ') {
            if(qtdPalavras == 1) K = K + linha[i];
            else if(qtdPalavras == 2) palavra1 = palavra1 + (char)tolower(linha[i]);
            else if(qtdPalavras == 3) palavra2 = palavra2 + (char)tolower(linha[i]);
            else palavra3 = palavra3 + (char)tolower(linha[i]);
        } else qtdPalavras++;
    }
    
    if(!palavra1.empty() && !palavra2.empty() && !palavra3.empty()) consultar(palavra1,palavra2,palavra3,map3); // Verificando se o usuário informou três palavras
    else if(!palavra1.empty() && !palavra2.empty()) consultar(K,palavra1,palavra2,map2,map3); // Verificando se o usuário informou duas palavras
    else consultar(K,palavra1,map1,map2); // Se o usuário não informou três/duas palavras, quer dizer que ele informou apenas uma palavra
}

// Função que adiciona uma palavra na frase (FUNÇÃO SECUNDÁRIA) ✓
void gerar(const string &modo, string &palavra1, string &palavra2, MyMap<string,int> &map) {
    string palavra; // Representa a palavra que será adicionada na frase
    
    // Verificando o modo de escolha da palavra. Se for no modo padrao, iremos pegar a palavra que mais aparece no map
    if(modo == "padrao") {
        int qtd = 0; // Representa quantas vezes a palavra aparece no map

        // Percorrendo todo o map para pegar a palavra que mais aparece
        for(MyMap<string,int>::iterator it = map.begin(); it != map.end(); it++) {
            if((*it).second > qtd) {
                palavra = (*it).first;
                qtd = (*it).second;
            } else if((*it).second == qtd) {
                if((*it).first < palavra) {
                    palavra = (*it).first;
                    qtd = (*it).second;
                }
            }
        }
    } else { // Se for no modo aleat, a palavra será escolhida de modo aleatório (DANDO PREFERÊNCIA AS PALAVRAS QUE MAIS APARECEM)
        pair<int,string> palavras[map.size()]; // Representa todas as palavras que ocorrem no map e quantas vezes essas palavras ocorrem
        int qtdTotal = 0; // Representa a quantidade total de palavras do map

        // Copiando os valores da árvore para o vetor de palavras e determinando a quantidade total de palavras do map
        int i = 0;
        for(MyMap<string,int>::iterator it = map.begin(); it != map.end(); it++) {
            palavras[i].first = -(*it).second;
            palavras[i].second = (*it).first;
            qtdTotal = qtdTotal + (*it).second;
            i++;
        }

        // Inicializando a semente e sorteando um número de 1 a qtdTotal
        srand(rand());
        int numEscolhido = rand() % qtdTotal + 1;

        // Ordenando o vetor de palavras
        sort(palavras,palavras + map.size());

        // Verificando qual palavra foi escolhida. Por exemplo, se as palavras mais frequentes são “agora” 
        // (com frequência 10), “amanha" (com frequência 4) e “caminhar” (com frequência 1), os possíveis 
        // números sorteados seriam: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 ou 15, sendo que se fossem 
        // sorteados os números 1, 2, 3, 4, 5, 6, 7, 8, 9 ou 10, a palavra escolhida seria "agora". 
        // Se fosse sorteado os números 11, 12, 13 ou 14, a palavra escolhida seria "amanha". 
        // E se fosse 15, a palavra escolhida seria "caminhar"
        qtdTotal = 0;
        for(i = 0; i < map.size(); i++) {
            qtdTotal = qtdTotal + (-palavras[i].first);
            if(numEscolhido <= qtdTotal) {
                palavra = palavras[i].second;
                break;
            }
        }
    }

    // Caso encontremos a palavra, deslocamos as últimas duas palavras da frase e imprimimos a palavra escolhida
    if(!palavra.empty()) {
        palavra1 = palavra2;
        palavra2 = palavra;
        cout << palavra << " ";
    }
}

// Função que adiciona uma palavra na frase usando o map2 ou map1 (FUNÇÃO SECUNDÁRIA) ✓
void gerar(const string &modo, string &palavra1, string &palavra2, MyMap<string,int> &map1, MyMap<string,MyMap<string,int>> &map2) {
    // Verificando se a última palavra da frase existe no map2
    MyMap<string,MyMap<string,int>>::iterator it1 = map2.find(palavra2);

    // Se o iterador não for NULO, quer dizer que a última palavra da frase se encontra no map2
    if(it1 != map2.end()) gerar(modo,palavra1,palavra2,(*it1).second); // Como a última palavra da frase se encontra no map2, basta achar a próxima palavra usando o map associado a última palavra da frase
    else gerar(modo,palavra1,palavra2,map1); // Como a última palavra da frase não se encontra no map2, basta achar a próxima palavra usando o map1
}

// Função que adiciona uma palavra na frase usando o map3, map2 ou map1 (FUNÇÃO SECUNDÁRIA) ✓
void gerar(const string &modo, string &palavra1, string &palavra2, MyMap<string,int> &map1, MyMap<string,MyMap<string,int>> &map2, MyMap<string,MyMap<string,MyMap<string,int>>> &map3) {
    // Verificando se a penúltima palavra da frase existe no map3
    MyMap<string,MyMap<string,MyMap<string,int>>>::iterator it1 = map3.find(palavra1);

    // Se o iterador não for NULO, quer dizer que a penúltima palavra da frase se encontra no map3
    if(it1 != map3.end()) {
        // Verificando se a última palavra da frase existe no map associado a penúltima palavra da frase
        MyMap<string,MyMap<string,int>>::iterator it2 = (*it1).second.find(palavra2);

        // Se o iterador não for NULO, quer dizer que a última palavra da frase se encontra no map associado a penúltima palavra da frase
        if(it2 != (*it1).second.end()) gerar(modo,palavra1,palavra2,(*it2).second); // Como a última palavra da frase se encontra no map associado a penúltima palavra da frase, basta achar a próxima palavra usando o map associado a última palavra da frase
        else gerar(modo,palavra1,palavra2,map1,map2); // Como a última palavra da frase não se encontra no map associado a penúltima palavra da frase, basta achar a próxima palavra usando o map2
    } else gerar(modo,palavra1,palavra2,map1,map2); // Como a penúltima palavra da frase não se encontra no map3, basta achar a próxima palavra usando o map2
}

// Função que gera uma frase de forma automática (FUNÇÃO PRINCIPAL) ✓
void gerar(const string &linha, MyMap<string,int> &map1, MyMap<string,MyMap<string,int>> &map2, MyMap<string,MyMap<string,MyMap<string,int>>> &map3) {
    int qtdPalavras = 1; // Representa a quantidade de palavras do comando
    string K; // Representa quantas palavras serão adicionadas na frase informada pelo usuário
    string modo; // Representa o modo de escolha das palavras (PADRÃO|ALEATÓRIO)
    string palavra1; // Representa a penúltima palavra da frase
    string palavra2; // Representa a última palavra da frase

    // Armazenando K, modo e as duas ultimas palavras informadas pelo usuário. Além disso, imprimimos a frase inicial escrita pelo usuário
    for(int i = 6; i < linha.size(); i++) {
        if(linha[i] != ' ') {
            if(qtdPalavras == 1) K = K + linha[i];
            else if(qtdPalavras == 2) modo = modo + linha[i];
            else palavra2 = palavra2 + (char)tolower(linha[i]);
        } else {
            qtdPalavras++;
            
            if(qtdPalavras > 3 && !palavra2.empty()) {
                cout << palavra2 << " ";
                palavra1 = palavra2;
                palavra2 = "";
            }
        }
    }
    
    // Imprimindo a última palavra da frase informada pelo usuário
    if(!palavra2.empty()) cout << palavra2 << " ";

    // Inserindo K palavras na frase informada pelo usuário
    for(int i = 0; i < stoi(K); i++) {
        if(!palavra1.empty() && !palavra2.empty()) gerar(modo,palavra1,palavra2,map1,map2,map3); // Se há pelo menos duas palavras na frase, adicionamos mais uma palavra na frase usando o map3, map2 ou map1
        else if(!palavra2.empty()) gerar(modo,palavra1,palavra2,map1,map2); // Se há apenas uma palavra na frase, adicionamos mais uma palavra na frase usando o map2 ou map1
        else gerar(modo,palavra1,palavra2,map1); // Se há não há palavras na frase, adicionamos mais uma palavra na frase usando o map1
    }
    
    // Quebrando a linha
    cout << endl;
}

// Função principal do programa ✓
int main(int argc, char **argv) {
    MyMap<string,int> map1; // Representa o map de nível 1
    MyMap<string,MyMap<string,int>> map2; // Representa o map de nível 2
    MyMap<string,MyMap<string,MyMap<string,int>>> map3; // Representa o map de nível 3
    string linha; // Representa a linha lida
    string opcao; // Representa a opção informada pelo usuário (CONSULTAR|GERAR)

    // Inicializando a semente
    srand(time(NULL));

    // Verificando se vamos ler de um arquivo ou se vamos ler do teclado
    if(argc == 2) {
        // Abrindo o arquivo
        ifstream fin(argv[1]);

        // Lendo os dados a partir do arquivo
        ler(fin,map1,map2,map3);

        // Fechando o arquivo
        fin.close();
    } else ler(cin,map1,map2,map3); // Lendo os dados a partir do teclado
    
    // Lendo todos os comandos informados pelo usuário
    while(getline(cin,linha)) {
        // Pegando a opção informada pelo usuário
        for(int i = 0; i < linha.size(); i++) {
            if(linha[i] == ' ') break;
            opcao = opcao + linha[i];
        }
        
        // Verificando se a opção informada foi "consultar"
        if(opcao == "consultar") consultar(linha,map1,map2,map3); // Chamando a função consultar
        else gerar(linha,map1,map2,map3); // Chamando a função gerar

        // Apagando o conteúdo da opção
        opcao = "";

        // Imprimindo uma linha em branco
        cout << endl;
    }

    // Informando que o programa executou sem nenhum problema
    return 0;
}