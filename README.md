# pi-20261
# Análise de Desempenho: Busca Sequencial (Fase I)

## Objetivo
Este projeto consiste na implementação e análise de performance do algoritmo de Busca Sequencial. O objetivo é estabelecer uma base de referência (baseline) empírica sobre o custo computacional de buscas em dados não ordenados, servindo de comparativo direto para futuras implementações estruturadas (como Tabelas Hash na Fase II).

## Caracterização do Dataset
Os testes foram realizados sobre uma base de dados real providenciada pelo escopo do projeto, garantindo variação de categorias, preços e volumes de dados.

* **Arquivo utilizado:** `dataset3.csv`
* **Quantidade total de registros carregados na memória:** 300.007 produtos.
* **Estrutura de Memória:** Vetor de blocos contíguos alocado dinamicamente (`malloc`), contendo campos de ID (int), Nome (char[51]), Categoria (char[31]) e Valor (float).

##  Metodologia de Testes (Protocolo)
Para assegurar o isolamento de variáveis ambientais e neutralizar as oscilações pontuais do SO, automatizamos os testes com o seguinte protocolo:
1. O vetor é totalmente carregado antes de instanciar o cronômetro.
2. Cada "bateria" consiste em **4.000 buscas sequenciais consecutivas**.
3. O conjunto de busca abrangeu perfeitamente os quatro casos de estresse propostos:
   - 1.000 buscas no **início** do vetor.
   - 1.000 buscas no **meio** do vetor.
   - 1.000 buscas no **final** do vetor.
   - 1.000 buscas de um elemento **inexistente** (provocando travessia total).
4. O protocolo inteiro foi repetido em 3 rodadas isoladas, extraindo-se a média aritmética dos tempos de execução da CPU (`clock()`).

## Tabela de Resultados

| Rodada Experimental | Operações de Busca | Tempo de Execução (s) |
| :--- | :--- | :--- |
| Rodada 1 | 4.000 | 9.650000 |
| Rodada 2 | 4.000 | 9.010000 |
| Rodada 3 | 4.000 | 8.670000 |
| **Média Final por Bateria** | **4.000** | **9.110000 s** |

**Métricas Consolidadas:**
* **Tempo Total de Testes (3 baterias / 12.000 buscas):** 27.330000 s
* **Tempo Médio de uma Busca Individual:** ~ 0.002277500 s (2.27 ms)

## Análise Interpretativa

O comportamento observado atende precisamente à complexidade de tempo linear $O(n)$ ditada pela teoria de estruturas de dados. 

**Comportamento e Custos:**
A Busca Sequencial lida de maneira cruel com volumes massivos. A disparidade entre os cenários é gritante: buscar o ID que se encontra no início do vetor ocorre em ordem constante $O(1)$, contudo, buscar IDs no final ou inexistentes obriga a CPU a iterar, linha a linha, todos os 300.007 registros. Essa média de 2.27 milissegundos por busca é matematicamente inaceitável em um sistema de produção onde múltiplas requisições simultâneas ocorrem.

**Relação Tamanho vs Tempo:**
O algoritmo varre bloco por bloco contíguo na memória RAM. Quanto maior o conjunto $n$, o limite assintótico exige um tempo de processamento estritamente proporcional. Uma base 10x maior custaria linearmente 10x mais tempo no pior caso.

**Limitações:**
A fragilidade principal da busca sequencial documentada neste experimento reside no "caso médio e pior caso". Não possuindo chaves de indexação ou mapeamento de endereço direto, ela gasta ciclo de processamento lendo dados irrelevantes até colidir (match) com o ID desejado. Esta evidência justifica fortemente a implementação de Tabelas Hash (Fase II) com complexidade de busca tendendo a $O(1)$ para estancar o tempo de resposta deste dataset.
