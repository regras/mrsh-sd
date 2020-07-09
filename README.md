# MRSH-SD
Ferramenta desenvolvida com base na função sdhash e a estratégia MRSH-NET


## Instruções
### Para compilar:
1.  Execute:
```  
$ make
```
### Para gerar um digest com base em uma lista:
1.  Colocar o path completo para os arquivos no arquivo cb_target_set.txt  
2.  Execute:
```
$./mrsh_net -d cb_target_set.txt > Digest
```
### Para comparar uma lista de arquivos com um digest gerado anteriormente:
1.  Coloque o path completo para os arquivos no arquivo cb_target_digest.txt  
2.  Execute:  
```
$ ./mrsh_net -i Digest cb_target_set.txt
```

## Parâmetros

### Para alterar o formato da saída:   
  Arquivo ./src/main.c  
  Função evaluation  
  Linha 383 para matches
  Linha 387 para não matches

### Para alterar o threshold de features consecutivas:   
Arquivo ./header/config.h  
Linha 16
  
### Para alterar o tamanho do filtro de bloom 
Arquivo ./header/config.h  
Linha 22  
Obs.:O tamanho deve estar em bytes
  
