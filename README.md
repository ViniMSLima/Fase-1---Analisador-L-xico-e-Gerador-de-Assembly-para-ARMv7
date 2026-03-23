**Disciplina:** Linguagens Formais e Compiladores - Engenharia de Computação  
**Grupo:** RA1 20  
**Autor:** Vinícius Matheus Sary de Lima (ViniMSLima)  

## 📌 Detalhes Essenciais
Este projeto implementa um compilador que traduz expressões matemáticas em Notação Polonesa Reversa (RPN) para código nativo em Assembly ARMv7. O sistema engloba:
- **Análise Léxica:** Identificação de números, variáveis, operadores matemáticos e palavras-chave.
- **Simulação Semântica:** Motor de cálculo RPN em C++ para validação lógica e tratamento de erros (ex: divisão por zero).
- **Geração de Código:** Transpilador para Assembly (`.s`) focado em precisão dupla (IEEE 754) e arquitetura de memória ARMv7.

## 🚀 Como Executar Localmente (C++)

1. **Compilação:** Abra o terminal na pasta do projeto e compile o código-fonte:
   ```bash
   g++ main.cpp -o tradutor
   ```

2. **Execução**: Rode o programa passando o arquivo de texto com as expressões como argumento:
    ```bash
    ./tradutor teste.txt
    ```
3. Saídas: O programa exibirá o relatório matemático no terminal e gerará dois arquivos na pasta:

- tokens.txt: Listagem do analisador léxico.
- saida.s: Código-fonte em Assembly gerado.