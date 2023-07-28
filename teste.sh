#!/bin/bash

# Imprimir o valor inicial da variável $SHLVL
echo "Valor de SHLVL: $SHLVL"

# Definir o valor máximo de SHLVL
max_shlvl=999

# Verificar se SHLVL é menor que 1000 usando o comando "if"
if [ "$SHLVL" -lt "$max_shlvl" ]; then
    # Imprimir o valor da variável $SHLVL na iteração atual
    echo "Valor de SHLVL: $SHLVL"
    # Chamar o script teste.sh
    bash ./teste.sh  # Substitua "bash" por "./teste.sh" se necessário
else
    # Se SHLVL for maior ou igual a 1000, imprimir o valor final
    echo "Valor de SHLVL FINAL: $SHLVL"
	bash
fi
