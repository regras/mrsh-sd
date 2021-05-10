# mrsh-sd
A similarity search tool based on mrsh-v2 and modified to take advantage of sdhash characteristics.

## Instructions

### Dependencies
- Boost
- OpenSSL (for sha1 hash)
- CMake

#### Boost
1. Extract the library folder onto mrsh-sd's main folder
 
2. Inside boost folder Run:
```
$ ./bootstrap.sh --prefix = /usr/local/  
$ ./b2 install
```
3. The setup is complete!


### Compiling:
1.  Run:
```  
$ cmake .
$ make
```
## Additional configs
### To modify the threshold of consecutive features  
File ./header/config.h  
```
#define MIN_RUN <number>
```
### To change the Bloom Filter size
File ./header/config.h  
```
#define BF_SIZE_IN_BYTES <number>
```
Obs.: The size must be power of two and expressed in bytes.

### Options 
There are two main options:
-Create BF 
-Search the given bf for files

And there are two ways of making such operations:
-With a list 
-With a dir/file name

To create a bf with a dir/filename:
```
./mrsh_sd -g DIR/FILE > filter.sdbf
```

To create a bf with a list:
```
./mrsh_sd -d LIST.TXT > filter.sdbf
```

To search a file/dir into a given bf digest:
```
./mrsh_sd -c filter.sdbf DIR/FILE > resultados.txt
```
To search a list of files into a given bf digest:
```
./mrsh_sd -i filter.sdbf list.txt > resultados.txt
```

Obs.: I have not tested using a dir inside the given dir, so if you are going to use it please check for possible erros.
