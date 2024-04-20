# Esercitazione 6

Per **compilare** il codice, entrare nella cartella Ising_1D e comandare
```bash
make
```


Per semplificare l'**esecuzione dell'intera simulazione**, ho scritto un file `bash` eseguibile con
```bash
./run.sh
```
il quale esegue 10 simulazioni su 10 temperature diverse tra $T=0.1$ e $T=3$. per ogni campo esterno
- ad $h=0$
- ad $h=0.02$
e per ambo gli algortimi:
- Metropolis
- Gibbs
 

Per focalizzarsi sull'esecuzione a varie T ma per campo esterno fissato, si puo' pure usare
```bash
./run_all_temp.sh
```
Comanda che e' gia contenuto in ./run.sh
In questo caso si dovra' ripetere l'esecuzione per 4 volte cambiando ripetutamente i valori del file di input:
**post_equilibrazione**
```bash
./post_equilibrazione.sh
```
**mv_config**: serva spostare tutti i file .config
```bash
./mv_config_metropolis.sh
./mv_config_gibbs.sh
```

Per pulire i file dei plot, eseguire
```bash
./clean_plots.sh
```

