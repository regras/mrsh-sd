# mrsh-sd
A similarity search tool based on mrsh-v2 and modified to take advantage of sdhash characteristics.

## Instructions

### Boost:
1. Extract the library folder onto mrsh-sd's main folder
2. Inside the boost folder run:
```  
$ ./bootstrap.sh
```
3. Run:
```  
$ ./b2
```
4. Run and the setup is complete!
```  
$ ./b2 install
```
### Compiling:
1.  Run:
```  
$ make
```
### Generating a bloom filter based on a list of files:
1.  List the files into a .txt file <list.txt>
2.  Run:
```
$./mrsh_net -d <list.txt> > digest
```
### To compare a target list of files against a previously generated digest:

1.  List the target files into a .txt file <target.txt>
2.  Run:  
```
$ ./mrsh_net -i digest <target.txt>
```

## Additional configs

### To modify the output format: 
  File ./src/main.c  
  Function: evaluation  
  Line 383 for the matches
 
 ```
  printf("%s:%d of %d(Longest run %d)\n", name, found, total,longest_run);
  ```
  Line 387 for the non matches
  ```
  printf("%s not found, min long run not long enough \n",name);
  ```

### To modify the threshold of consecutive features  
File ./header/config.h  
Line 16 - min_run
```
#define MIN_RUN <number>
```
### Para alterar o tamanho do filtro de bloom 
Arquivo ./header/config.h  
Linha 22  
Obs.:O tamanho deve estar em bytes e deve ser uma potência de 2 obrigatoriamente.
  
