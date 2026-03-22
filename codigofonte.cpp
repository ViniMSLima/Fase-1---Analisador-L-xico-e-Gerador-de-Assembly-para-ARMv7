// Vinícius Matheus Sary de Lima - ViniMSLima
// Grupo RA1 20 

#include <iostream> // Printar no terminal
#include <fstream> // Arquivos
#include <string>  // Linhas de texto lidas
#include <cctype> // isdigit() e isalpha()
#include <vector> // Para guardar os tokens em vetor

struct Token {
        std::string tipo; 
        std::string valor;
    };


Token estadoLendoNumero(const std::string& linha, int& posicao) {
    std::string valor = "";
    int qtdPontos = 0;

    // Enquanto for dígito ou um ponto decimal
    while (posicao < linha.length() && (isdigit(linha[posicao]) || linha[posicao] == '.')) {
        
        if (linha[posicao] == '.') {
            qtdPontos++;
        }
        
        valor += linha[posicao];
        posicao++; 
    }

    // Validação
    if (qtdPontos > 1) {
        std::cout << "ERRO: Numero errado = " << valor << std::endl;
        return {"ERRO", valor}; // Retorna erro
    }

    // Retornar o valor
    return {"NUMERO", valor};
}

Token estadoLendoPalavra(const std::string& linha, int& posicao) {
    std::string valor = "";
    bool temMinuscula = false;

    // Enquanto for letra
    while (posicao < linha.length() && isalpha(linha[posicao])) {
        // Procurar letra minuscula
        if (islower(linha[posicao])) {
            temMinuscula = true;
        }
        
        valor += linha[posicao];
        posicao++; 
    }

    // Validação de letra minuscula
    if (temMinuscula) {
        std::cout << "ERRO: Variaveis devem ser maiusculas -> " << valor << std::endl;
        return {"ERRO", valor};
    }

    // Validação do RES
    if (valor == "RES") {
        return {"KEYWORD", valor};
    }

    // Retornar o valor
    return {"VARIAVEL", valor};
}

Token estadoLendoBarra(const std::string& linha, int& posicao) {
    posicao++; 
    if(posicao < linha.length() && linha[posicao] == '/') {
        posicao++; 
        return {"OPERADOR", "//"};
    }
    return {"OPERADOR", "/"};
}

// Estado Inicial
Token estadoInicial(const std::string& linha, int& posicao) {
    // Ignorar espaços
    while (posicao < linha.length() && isspace(linha[posicao])) {
        posicao++;
    }

    // Final da linha pulando espaços = acabou
    if (posicao >= linha.length()) {
        return {"FIM", ""};
    }

    char atual = linha[posicao];

    // É um número?
    if (isdigit(atual)) { return estadoLendoNumero(linha, posicao); }

    // É uma letra?
    else if (isalpha(atual)) { return estadoLendoPalavra(linha, posicao); }

    // É a barra de divisão?
    else if (atual == '/') { return estadoLendoBarra(linha, posicao); }

    // São operadores simples ou parênteses?
    else if (atual == '+' || atual == '-' || atual == '*' || atual == '%' || atual == '^' || atual == '(' || atual == ')') {
        posicao++; // Anda uma casa, pois já lemos o caractere
        
        // Transforma o char em string para guardar no Token
        std::string valor_str(1, atual); 
        
        if (atual == '(' || atual == ')') return {"PARENTE", valor_str};
        else return {"OPERADOR", valor_str};
    }
    // Se não for nada disso, é um caractere inválido (Erro Léxico!)
    else {
        std::cout << "ERRO LEXICO: Caractere invalido encontrado: " << atual << std::endl;
        posicao++; // Pula o caractere inválido para não travar num loop infinito
        return {"ERRO", ""};
    }
}

// Função do Aluno 1
void parseExpressao(std::string linha, std::vector<Token>& tokensDaLinha) {
    int posicao = 0;
    
    while (posicao < linha.length()) {
        Token t = estadoInicial(linha, posicao);
        
        if (t.tipo != "FIM" && t.tipo != "ERRO") {
            tokensDaLinha.push_back(t);
        }
    }
}

void testarAnalisadorLexico() {
    std::cout << "Criar funcoes de teste para o analisador lexico, cobrindo entradas validas e invalidas" << std::endl;
    
    std::vector<Token> tokensTeste;
    
    // Teste 1: Entrada Válida
    std::cout << "Teste 1 (Valido): (3.14 2.0 //)" << std::endl;
    parseExpressao("(3.14 2.0 //)", tokensTeste);
    
    // Teste 2: Número malformado
    std::cout << "\nTeste 2 (Invalido - Numero): 3.14.5" << std::endl;
    parseExpressao("3.14.5", tokensTeste);

    // Teste 3: Variável minúscula
    std::cout << "\nTeste 3 (Invalido - Variavel): (var 5 +)" << std::endl;
    parseExpressao("(var 5 +)", tokensTeste);

    // Teste 4: Caractere estranho
    std::cout << "\nTeste 4 (Invalido - Caractere estranho): (3.14 2.0 &)" << std::endl;
    parseExpressao("(3.14 2.0 &)", tokensTeste);

    // Teste 5: Uso de vírgula em número
    std::cout << "\nTeste 5 (Invalido - Uso de virgula): 3,45" << std::endl;
    parseExpressao("3,45", tokensTeste);

    // Teste 6: Parênteses desbalanceados
    std::cout << "\nTeste 6 (Invalido - Parenteses desbalanceados): ( ( 3.14 2.0 + )" << std::endl;
    parseExpressao("( ( 3.14 2.0 + )", tokensTeste);

    // Teste 7: Expressão válida com operadores e variáveis
    std::cout << "\nTeste 7 (Valido - Operadores e Memoria): ( ( 2.0 3.0 ^ ) RES CONTADOR )" << std::endl;
    parseExpressao("( ( 2.0 3.0 ^ ) RES CONTADOR )", tokensTeste);
    
    std::cout << "FIM DO TESTE" << std::endl;
}

int main(int argc, char* argv[]) {

    if(argc != 2) {
        std::cout << "Erro! Para executar esse codigo e necessario escrever da seguinte forma: ./codigofonte <arquivo_de_teste.txt>" << std::endl;
        return 1;
    }

    std::ifstream arquivo(argv[1]);

    if (!arquivo.is_open()) {
        std::cout << "Erro: Nao foi possivel abrir o arquivo " << argv[1] << std::endl;
        return 1;
    }

    std::string linha;
    std::vector<Token> listaDeTokens; // Lista de tokes vazia

    while (std::getline(arquivo, linha)) {
        parseExpressao(linha, listaDeTokens);
    }

    arquivo.close();

    std::ofstream arquivoSaida("tokens.txt");

    if (arquivoSaida.is_open()) {
        // Cada token da lista
        for (int i = 0; i < listaDeTokens.size(); i++) {
            // Escreve no arquivo
            arquivoSaida << listaDeTokens[i].tipo << "," << listaDeTokens[i].valor << "\n";
        }
        arquivoSaida.close();
        std::cout << "Tokens salvos em 'tokens.txt'!" << std::endl;
    } else {
        std::cout << "Erro ao criar arquivo de saida." << std::endl;
    }

    //testarAnalisadorLexico();

    return 0;
}