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
