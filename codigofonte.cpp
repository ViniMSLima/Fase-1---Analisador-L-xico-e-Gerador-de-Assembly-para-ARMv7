// Vinícius Matheus Sary de Lima - ViniMSLima
// Grupo RA1 20 

#include <iostream> // Printar no terminal
#include <fstream>  // Arquivos
#include <string>   // Linhas de texto lidas
#include <cctype>   // isdigit() e isalpha()
#include <vector>   // Para guardar os tokens em vetor e histórico RES
#include <stack>    // Pilha
#include <map>      // Dicionário
#include <cmath>    // pow() e fmod()
#include <set>      // Para criar o .s 

struct Token {
        std::string tipo; 
        std::string valor;
    };

// Variáveis globais
std::map<std::string, double> memoriaVariaveis;
std::vector<double> historicoRES;

void lerArquivo(std::string nomeArquivo, std::vector<std::string>& linhas) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cout << "ERRO: Nao foi possivel abrir o arquivo: " << nomeArquivo << std::endl;
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        if (!linha.empty()) {
            linhas.push_back(linha);
        }
    }
    arquivo.close();
}

//// ALUNO 1

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


//// ALUNO 2
void executarExpressao(const std::vector<Token>& tokens) {
    std::stack<double> pilha;
    int contadorParenteses = 0; // Validar parênteses

    for (size_t i = 0; i < tokens.size(); ++i) {
        Token t = tokens[i];

        // Validar parênteses
        if (t.tipo == "PARENTE") {
            if (t.valor == "(") contadorParenteses++;
            else contadorParenteses--;
            continue; // Parêntese não vai para a pilha
        }

        if (t.tipo == "NUMERO") {
            pilha.push(std::stod(t.valor));
        }
        else if (t.tipo == "OPERADOR") {
            if (pilha.size() < 2) {
                std::cout << "ERRO: Pilha insuficiente para operar " << t.valor << std::endl;
                return;
            }
            double b = pilha.top(); pilha.pop();
            double a = pilha.top(); pilha.pop();

            if (t.valor == "+") pilha.push(a + b);
            else if (t.valor == "-") pilha.push(a - b);
            else if (t.valor == "*") pilha.push(a * b);
            else if (t.valor == "/") {
                if (b == 0) { std::cout << "ERRO: Divisao real por zero!" << std::endl; return; }
                pilha.push(a / b);
            }
            else if (t.valor == "//") {
                if (b == 0) { std::cout << "ERRO: Divisao inteira por zero!" << std::endl; return; }
                pilha.push(std::floor(a / b));
            }
            else if (t.valor == "%") {
                if (b == 0) { std::cout << "ERRO: Resto por zero!" << std::endl; return; }
                pilha.push(std::fmod(a, b));
            }
            else if (t.valor == "^") {
                pilha.push(std::pow(a, b));
            }
        }
        else if (t.tipo == "VARIAVEL") {
            if (i + 1 < tokens.size() && tokens[i+1].valor == "MEM") {
                if (!pilha.empty()) {
                    memoriaVariaveis[t.valor] = pilha.top();
                    i++; 
                }
            } else {
                if (memoriaVariaveis.count(t.valor)) {
                    pilha.push(memoriaVariaveis[t.valor]);
                } else {
                    std::cout << "ERRO: Variavel " << t.valor << " nao iniciada." << std::endl;
                    return;
                }
            }
        }
        else if (t.tipo == "KEYWORD" && t.valor == "RES") {
            if (!pilha.empty()) {
                int indice = (int)pilha.top(); pilha.pop();
                if (indice >= 0 && indice < (int)historicoRES.size()) {
                    pilha.push(historicoRES[indice]);
                } else {
                    std::cout << "ERRO: Indice RES " << indice << " invalido." << std::endl;
                    return;
                }
            }
        }
    }

    // Checagem de parênteses no fim da linha
    if (contadorParenteses != 0) {
        std::cout << "ERRO: Parenteses desbalanceados na linha!" << std::endl;
        return;
    }

    if (!pilha.empty()) {
        double final = pilha.top();
        historicoRES.push_back(final);
        std::cout << "SIMULACAO: Resultado = " << final << std::endl;
    }
}

void testarExecucao() {
    std::cout << "TESTES DE EXECUCAO" << std::endl;
    
    // Resetando para o teste
    memoriaVariaveis.clear();
    historicoRES.clear();

    // Matemática básica e histórico
    std::cout << "Teste 1: ( 5 2 + )" << std::endl;
    std::vector<Token> t1 = {{"PARENTE","("}, {"NUMERO","5"}, {"NUMERO","2"}, {"OPERADOR","+"}, {"PARENTE",")"}};
    executarExpressao(t1); // Deve dar 7

    // Memória
    std::cout << "\nTeste 2: ( 10 X MEM )" << std::endl;
    std::vector<Token> t2 = {{"PARENTE","("}, {"NUMERO","10"}, {"VARIAVEL","X"}, {"VARIAVEL","MEM"}, {"PARENTE",")"}};
    executarExpressao(t2); // X vira 10

    // Uso de variável e RES
    std::cout << "\nTeste 3: ( X 0 RES * )" << std::endl;
    std::vector<Token> t3 = {{"PARENTE","("}, {"VARIAVEL","X"}, {"NUMERO","0"}, {"KEYWORD","RES"}, {"OPERADOR","*"}, {"PARENTE",")"}};
    executarExpressao(t3); // 10 * 7 = 70

    std::cout << "FIM DOS TESTE" << std::endl;
}

//// ALUNO 3
std::string gerarAssembly(const std::vector<std::vector<Token>>& todasAsLinhas) {
    std::string code = ".text\n.global _start\n\n_start:\n";
    std::set<std::string> literais; // Para guardar todos os números únicos

    // --- 1. GERAR INSTRUÇÕES ---
    for (int i = 0; i < todasAsLinhas.size(); i++) {
        code += "\n    @ --- Linha " + std::to_string(i) + " ---\n";
        
        for (size_t j = 0; j < todasAsLinhas[i].size(); j++) {
            Token t = todasAsLinhas[i][j];

            if (t.tipo == "NUMERO") {
                literais.insert(t.valor); // Guarda o número para o .data
                
                // Nome da label (ex: 3.14 -> lit_3_14)
                std::string labelNum = t.valor;
                for(char &c : labelNum) if(c == '.') c = '_';

                code += "    LDR R0, =lit_" + labelNum + "    @ Carrega o endereço da label\n";
                code += "    VLDR.F64 D0, [R0]               @ Busca o valor double no endereço\n";
                code += "    VPUSH {D0}\n";
            }
            else if (t.tipo == "OPERADOR") {
                code += "    VPOP {D1}    @ B\n";
                code += "    VPOP {D0}    @ A\n";

                if (t.valor == "+")      code += "    VADD.F64 D2, D0, D1\n";
                else if (t.valor == "-") code += "    VSUB.F64 D2, D0, D1\n";
                else if (t.valor == "*") code += "    VMUL.F64 D2, D0, D1\n";
                else if (t.valor == "/") code += "    VDIV.F64 D2, D0, D1\n";
                else if (t.valor == "//")
                {
                    code += "    VDIV.F64 D2, D0, D1\n";
                    code += "    VCVT.S32.F64 S4, D2    @ Trunca as casas decimais\n";
                    code += "    VCVT.F64.S32 D2, S4    @ Converte de volta para Double\n";
                }
                else if (t.valor == "%") 
                {
                    code += "    VDIV.F64 D2, D0, D1    @ a / b\n";
                    code += "    VCVT.S32.F64 S4, D2    @ floor(a/b)\n";
                    code += "    VCVT.F64.S32 D2, S4    \n";
                    code += "    VMUL.F64 D2, D2, D1    @ (floor(a/b) * b)\n";
                    code += "    VSUB.F64 D2, D0, D2    @ a - (resultado acima)\n";
                }
                else if (t.valor == "^")
                {
                    std::string label_id = std::to_string(i) + "_" + std::to_string(j);
                    code += "    VMOV.F64 D2, #1.0      @ Acumulador da potencia\n";
                    code += "    VCVT.S32.F64 S4, D1    @ Converte expoente para int\n";
                    code += "    VMOV R1, S4            @ R1 = contador do loop\n";
                    code += "    CMP R1, #0\n";
                    code += "    BEQ pow_end_" + label_id + "\n";
                    code += "    pow_loop_" + label_id + ":\n";
                    code += "    VMUL.F64 D2, D2, D0    @ acc = acc * base\n";
                    code += "    SUBS R1, R1, #1        @ decrementa contador\n";
                    code += "    BNE pow_loop_" + label_id + "\n";
                    code += "    pow_end_" + label_id + ":\n";
                }
                
                code += "    VPUSH {D2}\n";
            }
            else if (t.tipo == "VARIAVEL") {
                // Atribuição: (10.0 X MEM)
                if (j + 1 < todasAsLinhas[i].size() && todasAsLinhas[i][j+1].valor == "MEM") {
                    code += "    VPOP {D0}            @ Tira da pilha para salvar\n";
                    code += "    VPUSH {D0}           @ DEVOLVE para a pilha (para o RES_HISTORY no final)\n";
                    code += "    LDR R0, =" + t.valor + "\n";
                    code += "    VSTR.F64 D0, [R0]    @ Salva na variavel " + t.valor + "\n";
                    j++; // Pula o token MEM
                } 
                // Busca: (X 5.0 +)
                else {
                    code += "    LDR R0, =" + t.valor + "\n";
                    code += "    VLDR.F64 D0, [R0]    @ Busca o valor de " + t.valor + "\n";
                    code += "    VPUSH {D0}           @ Coloca na pilha para a conta\n";
                }
            }
            else if (t.tipo == "KEYWORD" && t.valor == "RES") {
                code += "    VPOP {D0}            @ Indice do RES\n";
                code += "    VCVT.S32.F64 S0, D0  @ Double para Int\n";
                code += "    VMOV R1, S0\n";
                code += "    LSL R1, R1, #3       @ Indice * 8 bytes\n";
                code += "    LDR R0, =res_history\n";
                code += "    VLDR.F64 D0, [R0, R1]\n";
                code += "    VPUSH {D0}\n";
            }
        }
        // Salva resultado final da linha no histórico
        code += "    VPOP {D0}\n";
        code += "    LDR R0, =res_history\n";
        code += "    VSTR.F64 D0, [R0, #" + std::to_string(i * 8) + "]\n";
    }

    // Fim do programa
    code += "\n    MOV R7, #1\n    SWI 0\n";

    // --- 2. SEÇÃO DE DADOS (.data) ---
    code += "\n.data\n.align 3\n";
    
    // Histórico RES
    code += "res_history: .skip " + std::to_string(todasAsLinhas.size() * 8) + "\n";

    // Variáveis MEM (do mapa global)
    for (auto const& [nome, valor] : memoriaVariaveis) {
        code += nome + ": .double 0.0\n";
    }

    // Literais (Números únicos coletados)
    code += "@ Literais Numericos\n";
    for (const std::string& num : literais) {
        std::string labelNum = num;
        for(char &c : labelNum) if(c == '.') c = '_';
        code += "lit_" + labelNum + ": .double " + num + "\n";
    }

    return code;
}

//// MAIN
int main(int argc, char* argv[]) {
    // 1. Validação de Argumentos
    if(argc != 2) {
        std::cout << "Erro! Use: ./codigofonte <arquivo.txt>" << std::endl;
        return 1;
    }

    // --- MUDANÇA AQUI: Usando a função lerArquivo ---
    std::vector<std::string> linhasDoArquivo;
    lerArquivo(argv[1], linhasDoArquivo); 

    // Se o arquivo estiver vazio ou não abrir, a função lerArquivo já avisa
    if (linhasDoArquivo.empty()) return 1;

    std::vector<Token> listaGeralParaArquivo;
    std::vector<std::vector<Token>> todasAsLinhas; 

    // 2. Processamento das Linhas (Agora percorrendo o vetor de strings)
    for (const std::string& linha : linhasDoArquivo) {
        std::vector<Token> tokensDaLinha;
        
        parseExpressao(linha, tokensDaLinha);

        if (!tokensDaLinha.empty()) {
            executarExpressao(tokensDaLinha); // Simulação do Aluno 2
            
            todasAsLinhas.push_back(tokensDaLinha); // Guarda para o Aluno 3

            for (const auto& t : tokensDaLinha) {
                listaGeralParaArquivo.push_back(t);
            }
        }
    }

    // 3. Geração do Assembly (Aluno 3)
    std::string assemblyFinal = gerarAssembly(todasAsLinhas);
    
    std::ofstream arqAsm("saida.s");
    if (arqAsm.is_open()) {
        arqAsm << assemblyFinal;
        arqAsm.close();
        std::cout << "\n[OK] Arquivo Assembly 'saida.s' gerado!" << std::endl;
    }

    // 4. Salvar Tokens (Relatório do Aluno 1)
    std::ofstream arquivoSaida("tokens.txt");
    if (arquivoSaida.is_open()) {
        for (const auto& t : listaGeralParaArquivo) {
            arquivoSaida << t.tipo << "," << t.valor << "\n";
        }
        arquivoSaida.close();
        std::cout << "[OK] Tokens salvos em 'tokens.txt'!" << std::endl;
    }

    return 0;
}