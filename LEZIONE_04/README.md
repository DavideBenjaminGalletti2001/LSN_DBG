# Esercitazione 4



**Compilare:**
```bash
make
```
**eseguire:**
```bash
./NVE_NVT.exe <phase>
```
**Organizzazione file:**  
- `frames`: scommentando la linea di codice `ConfXYZ()`, raccoglie le configurazioni istantanee in formato XYZ, per la generazione di eventuali animazioni
- `input`: contiene file che servono per avviare la simulazione (eccetto `config.out` e `velocity.out`, necessari per il *restart* dopo l'equilibrazione), tra cui `input.<phase>` nei quali si settano le proprietà del sistema.  
- `output`: contiene i file scritti durante la simulazione, raggruppati per fase. Per ogni fase c'è una ulteriore sottocartella dedicata all'equilibrazione, contenente i file `config.out` e `velocity.out` letti per il *restart*.
**eseguire_tutto:**
```bash
./run_phases.exe
```
**post_equilibrazione:**
```bash
./post_equilibrazione.exe 
```
serve per l'equilibrazione e spostare file config.dat, velocity.dat e output_temp.dat in una opprtuna sottodirectory 
**Pulizie:**  
`./clean.sh`: rimuove *forzatamente* tutti i file dalla cartella `frames` e invoce ./clean<phase> 
`./clean<phase>.sh`: rimuove *forzatamente* tutti i file `.dat` dalla directory `<phase>`  
`make clean`: rimuove tutti i file `.o` ed `.exe` 
