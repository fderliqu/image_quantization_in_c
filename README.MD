# Quantification d'image

## Features

Ce repo contient plusieurs techniques de quantification d'images, nous avons dedans : 

- Quantification uniforme
- Quantification adaptive
- Quantification de floyd-steinberg

#### Important

Les fichiers d'images pris en compte sont en format .pgm (noir et blanc) et .ppm (couleur)
 
#### uniform_quantization.c 

__Usage :__ 
```sh
    ./<exec_file> <src_file> <dest_file>
```
Le programme demandera un chiffre n désignant la largeur de l’interval de quantification (plus ce nombre augmente, plus le nombre de valeur possibles au résultat, à partir de la valeur initiale comprise entre 0 et 255, diminue).

**Résultat exemple**

![uniform_quantization](/images_git/uniform_quantization.png)
![uniform_quantization](/images_git/nb_uniform_quantization.png)

#### adaptive_quantization.c 

__Usage :__ 
```sh
    ./<exec_file> <src_file> <dest_file>
```
Le programme demandera un chiffre n désignant le nombre d’intervalles de quantification (pour une taille d'image de X*Y, idéalément XY/n bits par intervalles)

**Résultat exemple**

![adaptive_quantization](/images_git/adaptive_quantization.png)
![adaptive_quantization](/images_git/nb_adaptive_quantization.png)

#### floyd_steinberg.c 

__Usage :__ 
```sh
    ./<exec_file> <src_file> <dest_file>
```
Le programme effectue une quantification floyd-steinberg 2 bits par canaux (soit 8 couleurs possible en RGB et 2 couleurs en N/B)
**Résultat exemple**

![floyd_steinberg_quantization](/images_git/floyd_steinberg.png)
![floyd_steinberg_quantization](/images_git/nb_floyd_steinberg.png)

#### histogramme.c

__Usage :__ 
```sh
    ./<exec_file> <src_file>
```
Le programme print les valeurs comme un histogramme

#### histogramme_on_csv.c

__Usage :__ 
```sh
    ./<exec_file> <src_file> <dest_file.csv>
```
Le programme envoie les valeurs dans un csv

## Compilation

Pour compiler : 
```sh
    gcc <file.c> 
```

Florian Derlique 2023
