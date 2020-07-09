# MRSH-SD
Ferramenta desenvolvida com base na função sdhash e a estratégia MRSH-NET


Para compilar:

$ make

Para gerar um digest com base em uma lista:

colocar o path completo para os arquivos no arquivo cb_target_set.txt
execute:
$./mrsh_net -d cb_target_set.txt > Digest

Para comparar uma lista de arquivos com um digest gerado anteriormente: -colocar o path completo para os arquivos no arquivo cb_target_digest.txt -execute:

$ ./mrsh_net -i Digest cb_target_set.txt

Para alterar o formato da saída: -./src/main.c -função evaluation -linha 383 para matches -linha 387 para não matches

Para alterar o threshold de features consecutivas: -./header/config.h

linha 16
Para alterar o tamanho do filtro de bloom -./header/config.h -linha 22 -o tamanho deve estar em bytes!
