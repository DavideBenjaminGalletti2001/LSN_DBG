for((l = 0; l <10; l++))
do
    mapfile -t myArray < "inputT.dat"
    for line in "${myArray[@]}"; do
        echo "$line"
    done
    rm "OUTPUT/ENERGIE/outputT${myArray[l]}.dat"
    rm "OUTPUT/SIGMA_MU/outputT${myArray[l]}_SM.dat"
done
