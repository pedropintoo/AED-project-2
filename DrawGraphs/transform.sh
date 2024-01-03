#!/bin/bash

# Verifique se o número de argumentos é correto
if [ "$#" -ne 1 ]; then
    echo "Uso: $0 <arquivo_de_entrada>"
    exit 1
fi

# Nome do arquivo de entrada
input_file=$1

# Nome do arquivo de saída (mesmo nome do arquivo de entrada com extensão .dot)
output_file="${input_file%.*}.dot"

# Escreva o cabeçalho do arquivo DOT
echo "digraph G {" > "$output_file"

# Processamento das linhas do arquivo de entrada
awk '/^[[:space:]]*[0-9]/ {
    # Imprime o vértice atual
    printf "    %s -> {", $1;

    # Imprime as arestas saindo do vértice
    for (i = 3; i <= NF; i++) {
        printf "%s", $i;
        if (i < NF) {
            printf " ";
        }
    }

    # Imprime o fechamento do conjunto e uma quebra de linha
    print "};"
}' "$input_file" >> "$output_file"

# Adiciona o rodapé do arquivo DOT
echo "}" >> "$output_file"

echo "Transformação concluída. O arquivo DOT foi salvo em $output_file."

dot -Tpng -o grafo.png teste.dot